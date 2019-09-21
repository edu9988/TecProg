#include <stdio.h>
#include <math.h>
#include "GLOBAL.H"
#include "ODE.H"

#define ARRAY_SIZE 100
#define NUM_SIMUL 2

void pressAnyKey(void);

double deriv(double x, double y)
{
	return -x * y * y;
}

double f1(double x, double* y)
{
	return *(y+1);
}

double f2(double x, double* y)
{
	return *y + x;
}

int main(){
	double yArr[ARRAY_SIZE];
	double x00 = 2;
	double y00 = 1;
	double x0;
	double xn = 3;
	double y0;
	double deltaX = 0.001;

	double (*ffx[NUM_SIMUL])(double, double*);
	double yArr0[NUM_SIMUL];
	double yArr1[NUM_SIMUL];
	int i;

	printf("Testing RK\n");
	x0 = x00;
	y0 = y00;

	printf("x = %lg, y= %lg, x0, y)");
	do{
		RungeKutta4(x0, y0, deltaX, yArr, ARRAY_SIZE,deriv);
		x0 += ARRAY_SIZE * deltaX;
		y0 = *(yArr + ARRAY_SIZE -1);
		printf(" x = %lg, y = %lg\n", x0, y0);
	}while(x0 < xn);

	pressAnyKey();

	return 0;
}

void pressAnyKey()
{
	printf("\nPress any key to continue...");
	getchar();
	puts("\n\n");
}
