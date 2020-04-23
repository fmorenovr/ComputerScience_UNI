#include <mpi.h>
#include <stdio.h>
#include <memory.h>

typedef struct {
    MPI_Comm     mycomm;
    int          left, right;
    MPI_Datatype type;
    void         *buf1, *buf2, *buf;
    MPI_Request  requests[2];
    int          stage, last_stage, maxlen;
    int          typesize;
    } MPE_Pipe;

void MPE_Pipe_create( MPI_Comm comm,MPI_Datatype type,int maxsize,void **pipe)
{
  MPE_Pipe *new;
  int true = 1, size, dsize, dextent, maxbuf;

  new = (MPE_Pipe *)malloc( sizeof(MPE_Pipe) );

  /* Create a ring of processes, allowing MPI to pick a good ordering  */
  MPI_Comm_size( comm, &size );
  MPI_Cart_create( comm, 1, &size, &true, 1, &new->mycomm );
  MPI_Cart_shift( new->mycomm, 0, 1, &new->left, &new->right );

  /* Create the double buffers.  Currently, require that the 
   datatype be contiguous. */
  MPI_Type_size( type, &dsize );
  MPI_Type_extent( type, &dextent );
  if (2 * dsize <= dextent) {
    fprintf( stderr, "Datatype needs to be (nearly) contiguous; size = %d and extent = %d\n",dsize, dextent );
    free( new );
    *pipe = 0;
    return; 
  }
  new->typesize	= dextent;
  MPI_Allreduce( &maxsize, &maxbuf, 1, MPI_INT, MPI_MAX, comm );
  new->maxlen	= maxbuf;
  maxbuf	       *= dextent;
  new->buf	= (void *)malloc( 2 * maxbuf );
  new->buf1	= new->buf;
  new->buf2	= (void *)( (char *)new->buf1 + maxbuf );
  new->type	= type;
  new->stage	= 0;
  new->last_stage	= size - 1;
  *pipe		= (void *)new;
}

/* 
 * This is one algorithm for sending data in the pipe.  Others could 
 * use MPI_Sendrecv,  persistent send/recv operations, or alltoall.
 */
void MPE_Pipe_start( void *pipe,void *mybuf,int len, qcopy)
{
  MPE_Pipe *p = (MPE_Pipe *)pipe;

  if (p->stage != 0) {
    fprintf( stderr, "Can only start pipe when pipe is empty\n" );
    return;
  }

  if (p->last_stage == 0) {
    return;
  }

  /* Start the pipe */
  MPI_Irecv( p->buf1, p->maxlen, p->type, p->left, 0, p->mycomm, &p->requests[0] ); 
  /* If qcopy is 1, we might choose to use MPI_Send instead */
  if (qcopy) {
    memcpy( p->buf2, mybuf, len * p->typesize );
    mybuf = p->buf2;
  }
  MPI_Isend( mybuf, len, p->type, p->right, 0, p->mycomm, &p->requests[1] );
}

void MPE_Pipe_push(void *pipe,void **recvbuf,int *recvlen)
{
  MPE_Pipe *p = (MPE_Pipe *)pipe;
  MPI_Status  statuses[2];
  void *tmp;

  if (p->last_stage == 0) return;

  MPI_Waitall( 2, p->requests, statuses );
  MPI_Get_count( &statuses[0], p->type, recvlen );
  *recvbuf = p->buf1;

  if (++p->stage == p->last_stage) {
    p->stage = 0;
    return;
  }

  /* Start next cycle */
  tmp	= p->buf1;
  p->buf1	= p->buf2;
  p->buf2	= tmp;
  MPI_Irecv( p->buf1, p->maxlen, p->type, p->left, 0, p->mycomm, &p->requests[0] );
  MPI_Isend( p->buf2, *recvlen, p->type, p->right, 0, p->mycomm,&p->requests[1] );
}

void MPE_Pipe_free(void **pipe)
{
  MPE_Pipe *p = (MPE_Pipe *)*pipe;

  if (p->stage != 0) {
    fprintf( stderr, "Can not free PIPE until %d more stages complete\n",p->last_stage - p->stage );
    return;
  }
  MPI_Comm_free( &p->mycomm );
  free( p->buf );
  *pipe = 0;
}
