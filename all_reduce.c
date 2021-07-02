#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #define COUNT 1000000
#define COUNT 2408448  // 2408448 // 2 * 2 * 2 * 6 * 224 * 224

void test_mpi_allreduce() {
  const size_t count = COUNT;
  int repeat_time    = 100;
  // long int sendbuf[COUNT] = {0};
  // long int recvbuf[3] = {0, 0, 0};
  long int *recvbuf = (long int *)malloc(sizeof(long int) * COUNT);
  memset(recvbuf, 0, sizeof(long int) * COUNT);

  // int status = MPI_Allreduce(sendbuf, recvbuf, (int)count, MPI_UINT64_T,
  //                            MPI_SUM, MPI_COMM_WORLD);

  int status = 0;
  for (int i = 0; i < repeat_time; i++) {
    status = MPI_Allreduce(MPI_IN_PLACE, recvbuf, (int)count, MPI_UINT64_T,
                           MPI_SUM, MPI_COMM_WORLD);
  }

  if (status != 0) {
    printf("MPI_Allreduce retval: %d\n", status);
  }

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  // for (int i = 0; i < count; i++) {
  //   printf("rank %d: num[%d] = %ld\n", world_rank, i, recvbuf[i]);
  // }

  return;
}

int main(void) {
  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int name_len;
  int world_size;
  int world_rank;

  MPI_Init(NULL, NULL);

  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  MPI_Get_processor_name(processor_name, &name_len);

  printf("Hello world from process %s, rank %d out of %d processors\n",
         processor_name, world_rank, world_size);
  test_mpi_allreduce();

  MPI_Finalize();

  return 0;
}
