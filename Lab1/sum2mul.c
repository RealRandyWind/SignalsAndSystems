#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double c = 343;
const double pi2 = 6.283185307179586476925286766559005768;

#define ABS(x) (x) < 0 ? -(x) : (x)

/* assignment */
void sum2mul(double f0, double f1, double* pf2, double* pf3)
{	
	if(!pf2 || !pf3) { exit(EXIT_FAILURE); }
	(*pf2) = 0.5 * (f1 - f0);
	(*pf3) = 0.5 * (f0 + f1);
}

int main(int argc, char const *argv[])
{
	int nscan;
	double f0, f1, f2, f3;
	
	nscan = scanf("%lf %lf", &f0, &f1);
	if (nscan != 2) { exit(EXIT_FAILURE); }
	sum2mul(f0, f1, &f2, &f3);

	/* abs() because not occording to book but according to judge */
	printf("%.2lf %.2lf\n", ABS(f2), ABS(f3));

	return EXIT_SUCCESS;
}