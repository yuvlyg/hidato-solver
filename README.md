# hidato-solver

This is a hexagonal [Hidato](https://en.wikipedia.org/wiki/Hidato) Solver

The solver is written in C++ and is called from a simple flask web-server

An instance of the server can be found [here](http://yuvlyg.pythonanywhere.com)
Developed and tested on Ubuntu 16.04
## Building
```
cd solver
make
```
## Running
```
export FLASK_APP=hid_server.py
flask run --host=0.0.0.0
```
