#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double c = 343;
const double pi2 = 6.283185307179586476925286766559005768;


/* assignment */
void sum2mul(double f0, double f1, double* pf2, double* pf3)
{
	double fc, fd;
	
	if(!pf2 || !pf3) { exit(EXIT_FAILURE); }
	(*pf2) = 0.5 * (f0 - f1);
	(*pf3) = 0.5 * (f1 + f0);
}

int main(int argc, char const *argv[])
{
	int nscan;
	double f0, f1, f2, f3;
	
	nscan = scanf("%lf %lf", &f0, &f1);
	if (nscan != 2) { exit(EXIT_FAILURE); }
	sum2mul(f0, f1, &f2, &f3);

	printf("%.2lf %.2lf\n", f2, f3);

	return EXIT_SUCCESS;
}