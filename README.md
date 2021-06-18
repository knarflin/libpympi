### Introduction

A Python C extension that provides MPI functions.

### Prerequisites
- MPICH
```
apt install mpich
```

### Build
```
make
```

### Install

Default install in current system-env / user-env / virtual-env / conda-env.
```
make install
```

### Example
```
make run
```

### Combining with CrypTen

If MPI library enabled, crypten applications must be run with:
- torch.distributed parameter set: MASTER_ADDR, MASTER_IP, RANK, ENV, etc. 
- launch python from the correct conda envs: ~/miniconda/envs/.../bin/python3
- Better write a bash script to manage above 2 things.
- At last wrap with /opt/openmpi/bin/mpirun and perhaps a rankfile.
