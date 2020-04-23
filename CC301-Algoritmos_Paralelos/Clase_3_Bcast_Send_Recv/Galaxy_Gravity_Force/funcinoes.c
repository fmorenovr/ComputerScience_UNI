/* Creating MPI Datatype of struct 
int
mpi_struct_init(MPI_Datatype *mpi_struct,int count)
{
  int i = 0;                   // temporary loop indexer 
  Particle _info;
  //count = 7;               // number of blocks in the struct 
  int blocks[1] = {count};   // set up 7 blocks 
  MPI_Datatype types[1] = {    // pixel internal types 
          MPI_DOUBLE};
  MPI_Aint address1,address2;
  MPI_Get_address(&_info,&address1);
  MPI_Get_address(&_info.x,&address2);
  MPI_Aint dis[1] = {          /* internal displacements 
          (address2 - address1)
  };

  MPI_Type_create_struct(count, blocks, dis, types, mpi_struct);
  MPI_Type_commit(mpi_struct);

  return(EXIT_SUCCESS);
}*/

int malloc2ddouble(double ***array, int n, int m) {
  int i;
  /* allocate the n*m contiguous items */
  double *p = (double *)malloc(n*m*sizeof(double));
  if (!p) return -1;

  /* allocate the row pointers into the memory */
  (*array) = (double **)malloc(n*sizeof(double*));
  if (!(*array)) {
     free(p);
     return -1;
  }

  /* set up the pointers into the contiguous memory */
  for (i=0; i<n; i++) 
     (*array)[i] = &(p[i*m]);

  return 0;
}

int free2ddouble(double ***array) {
    /* free the memory - the first element of the array is at the start */
    free(&((*array)[0][0]));

    /* free the pointers into the memory */
    free(*array);

    return 0;
}
