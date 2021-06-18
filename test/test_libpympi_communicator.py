#!/usr/bin/env python3
'''
Test functions below are correct:
- all_reduce SUM with crypten
- all_reduce BXOR with crypten
'''
import libpympi_communicator as mpi_comm
import torch
import numpy as np


def main():
    a = torch.tensor([[1, 2, 3], [4, 5, 6]])
    result = mpi_comm.mpi_all_reduce_sum(a)
    print(result)


if __name__ == "__main__":
    main()
