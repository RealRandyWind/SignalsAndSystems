#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double c = 343;
const double pi2 = 6.283185307179586476925286766559005768;

/* assignment */
void mics(double A, double f, double phi, double x0, double x1, double x2, double* py)
{
	double l0, l1, omega, alpha;

	if(!py) { exit(EXIT_FAILURE); }
	l0 = x0 - x2;
	l1 = x1 - x2;
	omega = pi2 * f * (1.0 / c);
	(*py) =  A * (cos(omega * l0 + phi) + cos(omega * l1 + phi));
}

int main(int argc, char const *argv[])
{
	int nscan;
	double A, f, phi, x0, x1, x2, y;
	
	nscan = scanf("%lf %lf %lf", &A, &f, &phi);
	nscan += scanf("%lf %lf %lf", &x0, &x1, &x2);
	if (nscan != 6) { exit(EXIT_FAILURE); }
	mics(A, f, phi, x0, x1, x2, &y);

	printf("%.2lf\n", y);

	return EXIT_SUCCESS;
}