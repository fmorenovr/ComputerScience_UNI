/* matrix.c: Matrix operations

   Copyright 2003, 2005 Bjoern Butscher, Hendrik Weimer

   This file is part of libquantum

   libquantum is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published
   by the Free Software Foundation; either version 3 of the License,
   or (at your option) any later version.

   libquantum is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with libquantum; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
   MA 02110-1301, USA

*/

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#include "matrix.h"
#include "config.h"
#include "complex.h"
#include "error.h"

/* Statistics of the memory consumption */

unsigned long quantum_memman(long change)
{
  static long mem = 0, max = 0;

  mem += change;

  if(mem > max)
    max = mem;

  return mem;
}

/* Create a new COLS x ROWS matrix */

void quantum_matrix_scanf(quantum_matrix *m){
  int i, j, z=0;
  /* int l; */
  while ((1 << z++) < m->rows);
  z--;
  for(i=0; i<m->rows; i++) 
    {
      for(j=0; j<m->cols; j++){
  	    //scanf("%f %f", m->t, m->t+1);
  	  }
      printf("\n");
    }
  printf("\n");
}

quantum_matrix quantum_new_matrix(int cols, int rows) 
{
  quantum_matrix m;

  m.rows = rows;
  m.cols = cols;
  m.t = calloc(cols * rows, sizeof(COMPLEX_FLOAT));

#if (DEBUG_MEM)
  printf("allocating %i bytes of memory for %ix%i matrix at 0x%X\n",
	 sizeof(COMPLEX_FLOAT) * cols * rows, cols, rows, (int) m.t);
#endif  

  if(!m.t)
    quantum_error(QUANTUM_ENOMEM);

  quantum_memman(sizeof(COMPLEX_FLOAT) * cols * rows);

  return m;
}

/* Delete a matrix */

void
quantum_delete_matrix(quantum_matrix *m)
{
#if (DEBUG_MEM)	
  printf("freeing %i bytes of memory for %ix%i matrix at 0x%X\n",
	 sizeof(COMPLEX_FLOAT) * m->cols * m->rows, m->cols, m->rows,
	 (int) m->t);	
#endif  

  free(m->t);
  quantum_memman(-sizeof(COMPLEX_FLOAT) * m->cols * m->rows);
  m->t=0;
}

/* Print the contents of a matrix to stdout */

void quantum_print_matrix(quantum_matrix m) 
{
  int i, j, z=0;
  /* int l; */

  while ((1 << z++) < m.rows);
  z--;

  #pragma omp parallel for
    {
      /* for (l=z-1; l>=0; l--) 
	{
	  if ((l % 4 == 3))
	    printf(" ");
	  printf("%i", (i >> l) & 1);
	  } */
      #pragma omp parallel for
      for(j=0; j<m.cols; j++)
	printf("%g %+gi ", quantum_real(M(m, j, i)), quantum_imag(M(m, j, i)));
      printf("\n");
    }
  printf("\n");
}

/* Matrix multiplication */

quantum_matrix quantum_mmult(quantum_matrix A, quantum_matrix B)
{
  int i, j, k;
  quantum_matrix C;

  if(A.cols != B.rows)
    quantum_error(QUANTUM_EMSIZE);
  C = quantum_new_matrix(B.cols, A.rows);

  #pragma omp parallel for
  for(i=0; i<B.cols; i++)
    {
      for(j=0; j<A.rows; j++)
	{
	  for(k=0; k<B.rows; k++)
	    M(C, i, j) += M(A, k, j) * M(B, i, k);
	}
    }

  return C;
}
	    
