#include <Python.h>
PyObject *mpientry(PyObject *self);
PyObject *mpi_init(PyObject *self);
PyObject *mpi_finalize(PyObject *self);
PyObject *mpipassa(PyObject *self, PyObject *args);
PyObject *mpi_allreduce(PyObject *self, PyObject *args);
int mpiex(void);
