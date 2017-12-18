#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double pi2 = 6.283185307179586476925286766559005768;
#define true 1
#define false 0


/* assignment */
void aliases(int fs, double A0, double f0, double phi0, double A1, double f1, double phi1, int* pisalias)
{
	int k, n, sample0, sample1;
	double alpha, omega;
	
	if(!pisalias) { exit(EXIT_FAILURE); }
	(*pisalias) = true;
	omega =  (1.0 / fs) * pi2;
	k = 0;

	/* ignorant easy solution */
	while (k < fs)
	{
		alpha = omega * k++;
		sample0 = (int)(A0 * cos(alpha * f0 + phi0));
		sample1 = (int)(A1 * cos(alpha * f1 + phi1));
		if(sample0 != sample1) { (*pisalias) = false; return; }
	}
}

int main(int argc, char const *argv[])
{
	int nscan, fs, isalias;
	double A0, f0, phi0, A1, f1, phi1;
	
	nscan = scanf("%i", &fs);
	nscan += scanf("%lf %lf %lf", &A0, &f0, &phi0);
	nscan += scanf("%lf %lf %lf", &A1, &f1, &phi1);
	if (nscan != 7) { exit(EXIT_FAILURE); }
	aliases(fs, A0, f0, phi0, A1, f1, phi1, &isalias);

	printf("%s\n", isalias ? "YES" : "NO");

	return EXIT_SUCCESS;
}
