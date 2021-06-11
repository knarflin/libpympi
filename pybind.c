#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "mpiex.h"
#include "structmember.h"

typedef struct {
  PyObject_HEAD;  // Must added line
  PyObject *first;
  PyObject *last;
  int number;
} CustomObject;

static void Custom_dealloc(CustomObject *self) {
  Py_XDECREF(self->first);
  Py_XDECREF(self->last);
  Py_TYPE(self)->tp_free((PyObject *)self);
}

static PyObject *Custom_new(PyTypeObject *type, PyObject *args,
                            PyObject *kwds) {
  CustomObject *self;
  self = (CustomObject *)type->tp_alloc(type, 0);
  if (self != NULL) {
    // Init with empty value
    self->first = PyUnicode_FromString("");
    if (self->first == NULL) {
      Py_DECREF(self);  // TODO: Why Decrease Ref-count
      return NULL;
    }
    // Init with empty value
    self->last = PyUnicode_FromString("");
    if (self->last == NULL) {
      Py_DECREF(self);  // TODO: Why Decrease Ref-count
      return NULL;
    }
    self->number = 0;
  }
  return (PyObject *)self;
}

static int Custom_init(CustomObject *self, PyObject *args, PyObject *kwds) {
  static char *kwlist[] = {"first", "last", "number", NULL};
  PyObject *first = NULL, *last = NULL, *tmp;

  if (!PyArg_ParseTupleAndKeywords(args, kwds, "|OOi", kwlist, &first, &last,
                                   &self->number))
    return -1;

  if (first) {
    tmp = self->first;
    Py_INCREF(first);
    self->first = first;
    Py_XDECREF(tmp);
  }
  if (last) {
    tmp = self->last;
    Py_INCREF(last);
    self->last = last;
    Py_XDECREF(tmp);
  }
  return 0;
}

static PyMemberDef Custom_members[] = {
    {"first", T_OBJECT_EX, offsetof(CustomObject, first), 0, "first name"},
    {"last", T_OBJECT_EX, offsetof(CustomObject, last), 0, "last name"},
    {"number", T_INT, offsetof(CustomObject, number), 0, "custom number"},
    {NULL} /* Sentinel */
};

static PyObject *Custom_name(CustomObject *self, PyObject *Py_UNUSED(ignored)) {
  if (self->first == NULL) {
    PyErr_SetString(PyExc_AttributeError, "first");
    return NULL;
  }
  if (self->last == NULL) {
    PyErr_SetString(PyExc_AttributeError, "last");
    return NULL;
  }
  return PyUnicode_FromFormat("%S %S", self->first, self->last);
}

static PyMethodDef Custom_methods[] = {
    {"name", (PyCFunction)Custom_name, METH_NOARGS,
     "Return the name, combining the first and last name"},
    {NULL} /* Sentinel */
};

PyMethodDef mpiex_funcs[] = {
    {"mpientry", (PyCFunction)mpientry, METH_NOARGS, "Custom MPI entry point"},
    {"mpi_init", (PyCFunction)mpi_init, METH_NOARGS, "Call C MPI_INIT"},
    {"mpi_finalize", (PyCFunction)mpi_finalize, METH_NOARGS,
     "Call C MPI_FINALIZE"},
    {"mpipassa", (PyCFunction)mpipassa, METH_VARARGS, "Passing args"},
    {"mpi_allreduce", (PyCFunction)mpi_allreduce, METH_VARARGS,
     "Call C MPI_ALLREDUCE"},
    {NULL}};

static PyTypeObject CustomType = {
    PyVarObject_HEAD_INIT(NULL, 0).tp_name = "libpympi.Custom",
    .tp_doc                                = "Custom objects",
    .tp_basicsize                          = sizeof(CustomObject),
    .tp_itemsize                           = 0,
    .tp_flags   = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,
    .tp_new     = Custom_new,
    .tp_init    = (initproc)Custom_init,
    .tp_dealloc = (destructor)Custom_dealloc,
    .tp_members = Custom_members,
    .tp_methods = Custom_methods,
};

static PyModuleDef custommodule = {
    PyModuleDef_HEAD_INIT,
    .m_name     = "libpympi",
    .m_doc      = "Example module that creates an extension type.",
    .m_size     = -1,
    .m_methods  = mpiex_funcs,
    .m_slots    = NULL,
    .m_traverse = NULL,
    .m_clear    = NULL,
    .m_free     = NULL,
};

PyMODINIT_FUNC PyInit_libpympi(void) {
  PyObject *m;
  if (PyType_Ready(&CustomType) < 0) return NULL;

  m = PyModule_Create(&custommodule);
  if (m == NULL) return NULL;

  Py_INCREF(&CustomType);
  if (PyModule_AddObject(m, "Custom", (PyObject *)&CustomType) < 0) {
    Py_DECREF(&CustomType);
    Py_DECREF(m);
    return NULL;
  }

  return m;
}
