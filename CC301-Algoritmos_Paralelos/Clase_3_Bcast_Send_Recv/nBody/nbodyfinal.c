#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include "mpiRing.h"

/*
   VERY simple version of an n-body code.  This uses the simple but highly
   suboptimal n^2 algorithm, and does not take advantage of symmetry.

   The time integrator is a simple leapfrog scheme.

   
 */

extern void   srand48();
extern double drand48();

/* Pipeline version of the algorithm... */
/* we really need the velocities as well... */
typedef struct {
    double x, y, z;
    double mass;
    } Particle;

/* Save the forces and old velocities */
typedef struct {
    double xold, yold, zold;
    double fx, fy, fz;
    } ParticleV;

#define MAX_PARTICLES 4000

/* This is 2-D only */
void ComputeForces( particles, pv, npart, 
		    recvbuf, rlen, max_f )
Particle  *particles, *recvbuf;
ParticleV *pv;
int       npart, rlen;
double    *max_f;
{
int i, j;
double xi, yi, mi, rx, ry, mj, r, fx, fy;
double xnew, ynew, rmin;

/* Compute forces (2D only) */
for (i=0; i<npart; i++) {
    rmin = 100.0;
    xi   = particles[i].x;
    yi   = particles[i].y;
    fx   = 0.0;
    fy   = 0.0;
    for (j=0; j<rlen; j++) {
	rx = xi - recvbuf[j].x;
	ry = yi - recvbuf[j].y;
	mj = recvbuf[j].mass;
	r  = rx * rx + ry * ry;
	/* ignore overlap and same particle */
	if (r == 0.0) continue;
	if (r < rmin) rmin = r;
	/* compute forces */
	r  = r * sqrt(r);
	fx += mj * rx / r;
	fy += mj * ry / r;
	}
    pv[i].fx -= fx;
    pv[i].fy -= fy;
    /* Compute a rough estimate of (1/m)|df / dx| */
    fx		      = sqrt(fx*fx + fy*fy)/rmin;
    if (fx > *max_f) *max_f = fx;
    }
}

void PrintParticles( particles, npart, t )
Particle *particles;
int      npart;
double   t;
{
int i;

for (i=0; i<npart; i++) {
/*     printf( "[%f] (%f,%f)\n", t, particles[i].x, particles[i].y ); */
    printf( "%f %f\n", particles[i].x, particles[i].y );
    }
}

int main( argc, argv )
int  argc;
char **argv;
{
Particle  particles[MAX_PARTICLES];   /* Particles on LOCAL node */
ParticleV pv[MAX_PARTICLES];          /* Particle velocity */
Particle  *recvbuf;
int       rank, size, npart, i, j;    /* location of local particles */
int       step, rlen;
int       totpart,                    /* total number of particles */
          cnt;                        /* number of times in loop */
MPI_Datatype particletype;
double    time;                       /* Computation time */
double    dt, dt_old;                 /* Integration time step */
double    t;                          /* Time actually integrated to */
double    a0, a1, a2;
void      *pipe;                      /* Opaque structure for communication 
					 pipe */
int       debug_flag = 1;

MPI_Init( &argc, &argv );
MPI_Comm_rank( MPI_COMM_WORLD, &rank );
MPI_Comm_size( MPI_COMM_WORLD, &size );

/* Everyone COULD have a different size ... */
npart = 2 * size;
if (argc > 1) 
    npart = atoi(argv[1]) / size;
if (npart > MAX_PARTICLES) 
    MPI_Abort( MPI_COMM_WORLD, 1 );

MPI_Allreduce( &npart, &totpart, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD );

cnt    = 100;

MPI_Type_contiguous( 4, MPI_DOUBLE, &particletype );
MPI_Type_commit( &particletype );

/* Generate the initial values */
srand48( rank * 117 );
for (i=0; i<npart; i++) {
    particles[i].x    = drand48();
    particles[i].y    = drand48();
    particles[i].z    = drand48();
    /* Normalize the mass with respect to the gravitational constant 
       (multiply by sqrt(G), G = 6.668E-8 dyne-cm^2/gm^2 or 
        6.668E-16 Joule-m^2/kg^2, sqrt(G) = 2.582e-8 
     */
    particles[i].mass = 1 * 2.582e-8;
    /* This is the zero initial velocity case */
    pv[i].xold	      = particles[i].x;
    pv[i].yold	      = particles[i].y;
    pv[i].zold	      = particles[i].z;
    pv[i].fx	      = 0;
    pv[i].fy	      = 0;
    pv[i].fz	      = 0;
    }

/* Add a particle in the center with much larger mass */
if (rank == 0) {
    particles[0].x    = 0.5;
    particles[0].y    = 0.5;
    particles[0].z    = 0.5;
    particles[0].mass = 1000 * 2.582e-8;
    pv[0].xold	      = particles[0].x;
    pv[0].yold	      = particles[0].y;
    pv[0].zold	      = particles[0].z;
    pv[0].fx	      = 0;
    pv[0].fy	      = 0;
    pv[0].fz	      = 0;
    }

if (debug_flag && rank == 0) 
    PrintParticles( particles, npart, 0.0 );

dt     = 0.001;
dt_old = 0.001;

/* Create a communication pipe */
MPE_Pipe_create( MPI_COMM_WORLD, particletype, npart, &pipe );

time = MPI_Wtime();
t    = 0.0;
while (cnt--) {
    double max_f, dt_est, new_dt, dt_new;
    
    /* Load the initial sendbuffer */
    MPE_Pipe_start( pipe, particles, npart, 1 );

    /* integation is a0 * x^+ + a1 * x + a2 * x^- = f / m */
    a0   = 2.0 / (dt * (dt + dt_old));
    a2   = 2.0 / (dt_old * (dt + dt_old));
    a1   = -(a0 + a2);      /* also -2/(dt*dt_old) */

    /* Compute self forces (on same processor) */
    max_f = 0;
    ComputeForces( particles, pv, npart, particles, npart, &max_f );
    
    /* For other particles, compute interaction forces */
    for (step=1; step<size; step++) {

	/* Push pipe, get new data */
	MPE_Pipe_push( pipe, &recvbuf, &rlen );

	/* Compute forces */
	ComputeForces( particles, pv, npart, recvbuf, rlen, &max_f );
	}

    /* Once we have the forces, we compute the changes in position */
    for (i=0; i<npart; i++) {
	double xi, yi;
	/* Very, very simple leapfrog time integration.  We use a variable 
	   step version to simplify time-step control. */
	xi	       = particles[i].x;
	yi	       = particles[i].y;
	particles[i].x = (pv[i].fx - a1 * xi - a2 * pv[i].xold) / a0;
	particles[i].y = (pv[i].fy - a1 * yi - a2 * pv[i].yold) / a0;
	pv[i].xold     = xi;
	pv[i].yold     = yi;
	pv[i].fx       = 0;
	pv[i].fy       = 0;
	}

    t += dt;

    if (debug_flag && rank == 0) 
	PrintParticles( particles, npart, t );

    /* Recompute a time step. Stability criteria is roughly 
       2 = dt * sqrt(1/m |df/dx|), or
       2/sqrt(1/m |df/dx|) >= dt.  We leave a little room */
    dt_est = 1.0/sqrt(max_f);
    /* Set a minimum: */
    if (dt_est < 1.0e-6) dt_est = 1.0e-6;
    MPI_Allreduce( &dt_est, &dt_new, 1, MPI_DOUBLE, MPI_MIN, MPI_COMM_WORLD );
    /* Modify time step */
    if (dt_new < dt) {
	dt_old = dt;
	dt     = dt_new;
	if (debug_flag && rank == 0) 
	    printf( "#New time step is %f\n", dt );
	}
    else if (dt_new > 4.0 * dt) {
	dt_old = dt;
	dt    *= 2.0;
	if (debug_flag && rank == 0) 
	    printf( "#New time step is %f\n", dt );
	}

    /* We could do graphics here (move particles on the display) */
    }
time = MPI_Wtime() - time;
if (rank == 0) {
    printf( "#Computed %d particles in %f seconds\n", totpart, time );
    }

MPE_Pipe_free( &pipe );
MPI_Type_free( &particletype );

MPI_Finalize();
}
