#!/usr/bin/env python3

import setuptools
import pdb
from distutils.core import setup, Extension

import distutils.core

import os
os.environ["CC"] = "/opt/openmpi/bin/mpicc"
os.environ["LDFLAGS"] = " -L/opt/openmpi/lib -lmpi -Wl,-rpath,/opt/openmpi/lib"  # -Wl, -Bsymbolic-functions - Wl, -z, relro" + \

distutils.core.setup(
    name="libpympi",
    version="1.0",
    ext_modules=[distutils.core.Extension(
        "libpympi", ["src/pybind.c", "src/mpiex.c"])]
)
