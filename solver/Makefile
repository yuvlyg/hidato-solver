CC=g++
CFLAGS=-I. -O2 -Wall -fPIC

solver.so:
	swig -c++ -python -py3 solver.i
	$(CC) $(CFLAGS) $(shell pkg-config --cflags --libs python3) solve.cc solver_wrap.cxx -shared -o _solver.so

clean:
	rm solver_wrap.cxx _solver.so solver.py
