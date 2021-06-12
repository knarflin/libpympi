#!/usr/bin/env python3

import pdb
from distutils.core import setup, Extension

import os
os.environ["CC"] = "/opt/openmpi/bin/mpicc"
os.environ["LDFLAGS"] = " -L/opt/openmpi/lib -lmpi -Wl,-rpath,/opt/openmpi/lib"  # -Wl, -Bsymbolic-functions - Wl, -z, relro" + \

setup(
    name="libpympi",
    version="1.0",
    ext_modules=[Extension("libpympi", ["pybind.c", "mpiex.c"])]
)
