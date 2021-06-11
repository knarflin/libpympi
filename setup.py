#!/usr/bin/env python3

import pdb
from distutils.core import setup, Extension

import os
os.environ["CC"] = "mpicc"
os.environ["LDFLAGS"] = " -L/usr/lib/x86_64-linux-gnu -lmpich"  # "-Wl,-Bsymbolic-functions -Wl,-z,relro" + \

setup(
    name="libpympi",
    version="1.0",
    ext_modules=[Extension("libpympi", ["pybind.c", "mpiex.c"])]
)
