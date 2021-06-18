#!/usr/bin/env python3
'''
Test functions below are correct:
- all_reduce SUM
- all_reduce BXOR
[TODO]
- rank, world_size
- with python unittest module
'''
import atexit
import libpympi
import torch
import numpy as np


def tensor_all_reduce_sum(tensor):
    # a = torch.randint(low=0, high=2**63-1, size=(2, 3), dtype=torch.int64)
    nparray = tensor.cpu().detach().numpy()
    npbytes = nparray.tobytes()
    npshape = nparray.shape

    ret_bytes = libpympi.mpi_all_reduce_sum(npbytes)

    ret = np.frombuffer(ret_bytes, dtype=np.int64)
    ret = ret.reshape(npshape)
    return ret


def tensor_all_reduce_bxor(tensor):
    # a = torch.randint(low=0, high=2**63-1, size=(2, 3), dtype=torch.int64)
    nparray = tensor.cpu().detach().numpy()
    npbytes = nparray.tobytes()
    npshape = nparray.shape

    ret_bytes = libpympi.mpi_all_reduce_bxor(npbytes)

    ret = np.frombuffer(ret_bytes, dtype=np.int64)
    ret = ret.reshape(npshape)
    return ret


def main():
    a = torch.tensor([[1, 2, 3], [4, 5, 6]])
    b = tensor_all_reduce_sum(a)
    print(b)
    c = tensor_all_reduce_bxor(a)
    print(c)


if __name__ == "__main__":
    libpympi.mpi_init()
    main()
    libpympi.mpi_finalize()
