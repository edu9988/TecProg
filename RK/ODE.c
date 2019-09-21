#include <stdlib.h>
//#include "mode.h"
#include "global.h"

void RungeKutta4(double x0, double y0, double deltaX, double* yArr, int numElem, double (*fx)(double, double)){
	double x, y, halfDelta;
	double k1, k2, k3, k4;
	int i;

	if(numElem < 1)
		return;

	x = x0;
	y = y0;

	halfDelta = deltaX / 2;

	for(i=0; i<numElem; i++){
		k1 = deltaX * (*fx)(x,y);
		k2 = deltaX * (*fx)(x + halfDelta, y + k1/2);
		k3 = deltaX * (*fx)(x + halfDelta, y + k2/2);
		k4 = deltaX * (*fx)(x + deltaX, y + k3);
		y += (k1 + 2 * (k2 + k3) + k4) / 6;
		*(yArr +i) = y;
		x += deltaX;
	}
}

void VectRungeKuttta4(double x0, double* y0, double deltaX, double* y1, int numYVar, double (*fx[])(double, double*)){
	double x, *y, halfDelta;
	double *k1, *k2, *k3, *k4;
	int i;

	if(numYVar < 1)
		return;

	k1 = malloc(numYVar * sizeof(double));
	k2 = malloc(numYVar * sizeof(double));
	k3 = malloc(numYVar * sizeof(double));
	k4 = malloc(numYVar * sizeof(double));
	y = malloc(numYVar * sizeof(double));

	x = x0;
	for(i=0; i<numYVar; i++)
		*(y + i) = *(y0 +i);
	halfDelta = deltaX / 2;
	for(i=0; i<numYVar; i++)
		*(k1 + i) = deltaX * (*fx[i])(x,y);
	for(i=0; i<numYVar; i++)
		*(y+i) += *(k1 + i) / 2;
	for(i=0;  i < numYVar; i++)
		*(k2+i) = deltaX * (*fx[i])(x + halfDelta, y);
	for(i=0; i < numYVar; i++)
		*(y+i) = *(y0 + i) + *(k2+i) / 2;
	for(i=0;  i < numYVar; i++)
		*(k3+i) = deltaX * (*fx[i])(x + halfDelta, y);
	for(i=0;  i < numYVar; i++)
		*(y+i) = *(y0 + i) + *(k3+i);
	for(i=0;  i < numYVar; i++)
		*(k4+i) = deltaX * (*fx[i])(x + deltaX, y);
	for(i=0;  i < numYVar; i++)
		*(y1 + i) = *(y0 +i) + (* (k1 +i) + 2*(*(k2 + i) + *(k3 + i)) + *(k4+i)) / 6;

	free(k1);
	free(k2);
	free(k3);
	free(k4);
	free(y);
}






















