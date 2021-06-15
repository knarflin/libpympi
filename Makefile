all:
	python setup.py build_ext --inplace

clean:
	rm -rf *.out *.bin *.exe *.o *.a *.so test build

run:
	/opt/openmpi/bin/mpirun -n 3 python3 test.py
