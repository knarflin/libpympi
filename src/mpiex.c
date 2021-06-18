#include "mpiex.h"
#include <mpi.h>
#include <stddef.h>
#include <stdio.h>

PyObject *mpi_init(PyObject *self) {
  MPI_Init(NULL, NULL);
  return PyUnicode_FromFormat("MPI_INIT sucessfully!");
}

PyObject *mpi_finalize(PyObject *self) {
  MPI_Finalize();
  return PyUnicode_FromFormat("MPI_FINALIZE sucessfully!");
}

int mpiex(void) {
  int world_size;

  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  char processor_name[MPI_MAX_PROCESSOR_NAME];
  int name_len;

  MPI_Get_processor_name(processor_name, &name_len);

  printf("Hello world from process %s, rank %d out of %d processors\n",
         processor_name, world_rank, world_size);

  return 0;
}

PyObject *mpientry(PyObject *self) {
  mpiex();
  return PyUnicode_FromFormat("Invoke mpi sucessfully!");
}

PyObject *mpipassa(PyObject *self, PyObject *args) {
  int64_t *array_ptr = NULL;
  Py_buffer py_buf;
  // PyArg_ParseTuple(args, "y*", &void_ptr);
  PyArg_ParseTuple(args, "y*", &py_buf);

  printf("buf_size %ld\n", py_buf.len);
  array_ptr = (int64_t *)py_buf.buf;

  size_t len = py_buf.len / sizeof(int64_t);

  for (size_t i = 0; i < len; i++) {
    printf("buf_to_int64 %ld\n", array_ptr[i]);
  }

  char buf[] = "abcd";

  PyObject *py_obj = Py_BuildValue("y", buf);

  return py_obj;
}

PyObject *mpi_all_reduce_sum(PyObject *self, PyObject *args) {
  Py_buffer py_buf;

  PyArg_ParseTuple(args, "y*", &py_buf);
  size_t buf_size = py_buf.len;
  size_t count    = buf_size / sizeof(int64_t);

  const int64_t *sendbuf = py_buf.buf;
  int64_t *recvbuf       = (int64_t *)malloc(buf_size);

  int status = MPI_Allreduce(sendbuf, recvbuf, (int)count, MPI_UINT64_T,
                             MPI_SUM, MPI_COMM_WORLD);

  if (status != 0) {
    printf("MPI_Allreduce retval: %d\n", status);
  }

  PyObject *py_obj = Py_BuildValue("y#", recvbuf, (int)buf_size);
  free(recvbuf);

  return py_obj;
}

PyObject *mpi_all_reduce_bxor(PyObject *self, PyObject *args) {
  Py_buffer py_buf;

  PyArg_ParseTuple(args, "y*", &py_buf);
  size_t buf_size = py_buf.len;
  size_t count    = buf_size / sizeof(int64_t);

  const int64_t *sendbuf = py_buf.buf;
  int64_t *recvbuf       = (int64_t *)malloc(buf_size);

  int status = MPI_Allreduce(sendbuf, recvbuf, (int)count, MPI_UINT64_T,
                             MPI_BXOR, MPI_COMM_WORLD);

  if (status != 0) {
    printf("MPI_Allreduce retval: %d\n", status);
  }

  PyObject *py_obj = Py_BuildValue("y#", recvbuf, (int)buf_size);
  free(recvbuf);

  return py_obj;
}
