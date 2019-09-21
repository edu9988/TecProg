#ifndef _ODE_H_
#define _ODE_H_

#include <math.h>

void RungeKutta4(double x, double y0, double deltaX, double* yArr, int numElem, double (*fx)(double, double));

void VectRungeKuttta4(double x0, double* y0, double deltaX, double* y1, int numYVar, double (*fx[])(double, double*));

#endif
