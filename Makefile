all:
	python setup.py build_ext --inplace

clean:
	rm -rf *.out *.bin *.exe *.o *.a *.so build

install:
	python setup.py install

run:
	/opt/openmpi/bin/mpirun -n 3 python3 test/test_basic.py

test_libpympi_communicator:
	/opt/openmpi/bin/mpirun -n 3 python3 test/test_libpympi_communicator.py

test_check_crypten_works:
	/opt/openmpi/bin/mpirun -n 3 python3 test/test_check_crypten_works.py

# For C only
c:
	/opt/openmpi/bin/mpicc -O3 purec_all_reduce.c
c-run:
	/opt/openmpi/bin/mpirun -n 3 ./a.out
c-clean:
	rm ./a.out
