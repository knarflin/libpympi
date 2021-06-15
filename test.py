import libpympi
import torch
import numpy as np


def tensor_allreduce(tensor):
    # a = torch.randint(low=0, high=2**63-1, size=(2, 3), dtype=torch.int64)
    nparray = tensor.cpu().detach().numpy()
    npbytes = nparray.tobytes()
    npshape = nparray.shape

    ret_bytes = libpympi.mpi_allreduce(npbytes)

    ret = np.frombuffer(ret_bytes, dtype=np.int64)
    ret = ret.reshape(npshape)
    return ret


def main():
    a = torch.tensor([[1, 2, 3], [4, 5, 6]])
    a = tensor_allreduce(a)
    print(a)


if __name__ == "__main__":
    libpympi.mpi_init()
    main()
    libpympi.mpi_finalize()
