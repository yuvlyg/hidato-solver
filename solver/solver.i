%module solver
%include "carrays.i"
%array_class(int, intArray);

%{
    extern bool solveFromVec(int vec[61 * 3]);
%}
extern bool solveFromVec(int vec[61 * 3]);
