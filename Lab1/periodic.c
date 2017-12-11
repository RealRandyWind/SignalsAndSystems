#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double c = 343;
const double pi2 = 6.283185307179586476925286766559005768;


/* assignment */
void periodic(double A, int T, double phi, int* pT0)
{
	int T0, q;

	if(!pT0) { exit(EXIT_FAILURE); }
	/* ensure T0 >= T */
	if ((T0 = (*pT0)) < T) { T0 = T; T = (*pT0); }
	/* compute fundamental period if T0 not already is */
	if (q = T0 % T) { T0 = (T % q) ? T0 * T : (T / q) * T0; }
	/* return fundamental period */
	(*pT0) = T0;
}

int main(int argc, char const *argv[])
{
	int nscan, n, T, T0;
	double A, phi;
	
	nscan = scanf("%i", &n);
	if (nscan != 1 || n <= 0) { exit(EXIT_FAILURE); }
	T0 = 1;

	while (n--)
	{
			nscan = scanf("%lf %i %lf", &A, &T, &phi);
			if(nscan != 3) { exit(EXIT_FAILURE); }
			periodic(A, T, phi, &T0);
	}

	printf("%i\n", T0);

	return EXIT_SUCCESS;
}