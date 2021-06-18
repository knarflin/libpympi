
#!/usr/bin/env python3
'''
Test functions below are correct:
- all_reduce SUM with crypten
- all_reduce BXOR with crypten
'''
# import libpympi_communicator as mpi_comm
import torch
import numpy as np
import crypten

from crypten import mpc


def test_all_reduce_sum():
    a = torch.tensor([[1, 2, 3], [4, 5, 6]])
    a_enc = crypten.cryptensor(a, src=0)
    a_dec = a_enc.get_plain_text()
    print(a_dec)


# @mpc.run_multiprocess(world_size=3)
def test_all_reduce_bxor():
    from crypten.mpc.primitives.binary import BinarySharedTensor
    a = torch.tensor([[1, 2, 3], [4, 5, 6]], dtype=torch.int64) * 65536
    a_binary_enc = BinarySharedTensor.from_shares(a)
    a_dec = a_binary_enc.get_plain_text()
    print(a_dec)


def main():
    crypten.init()
    test_all_reduce_bxor()


if __name__ == "__main__":
    main()
