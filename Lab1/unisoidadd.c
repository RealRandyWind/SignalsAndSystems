#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double pi2 = 6.283185307179586476925286766559005768;

int* newsamples(int n)
{
	int* samples;

	samples = (int*) malloc(n * sizeof(int));
	if (!samples) { exit(EXIT_FAILURE); }
	return samples;
}

void printsamples(const int* samples, int n)
{
	int k;

	if(!samples) { exit(EXIT_FAILURE); }
	printf("[");
	if(n > 0)
	{
		printf("%i", samples[0]);
		for (k = 1; k < n; ++k) { printf(",%i", samples[k] ); }
	}
	printf("]\n");
}


void unisoid(int fs, int n, double A, double f, double phi, int* samples)
{
	int k;
	double Ts;
	
	if(!samples) { exit(EXIT_FAILURE); }
	Ts = 1.0 / fs;
	for (k = 0; k < n; ++k)
	{
		samples[k] = (int)(A * cos(pi2 * f * k * Ts + phi));
	}
}

/* assignment */
void unisoidadd(int fs, int n, double A, double f, double phi, int* samples)
{
	int k;
	double Ts;
	
	if(!samples) { exit(EXIT_FAILURE); }
	Ts = 1.0 / fs;
	for (k = 0; k < n; ++k)
	{
		samples[k] += (int)(A * cos(pi2 * f * k * Ts + phi));
	}
}

int main(int argc, char const *argv[])
{
	int nscan, n, m, fs, *samples;
	double A, f, phi;

	nscan = scanf("%i %i", &fs, &n);
	nscan += scanf("%i", &m);
	if (nscan != 3) { exit(EXIT_FAILURE); }
	if (m <= 0) { return EXIT_SUCCESS; }
	samples = newsamples(n);
	
	nscan = scanf("%lf %lf %lf", &A, &f, &phi);
	if (nscan != 3) { exit(EXIT_FAILURE); }
	unisoid(fs, n, A, f, phi, samples);
	while(1 < m--)
	{
		nscan = scanf("%lf %lf %lf", &A, &f, &phi);
		if (nscan != 3) { exit(EXIT_FAILURE); }
		unisoidadd(fs, n, A, f, phi, samples);
	}
	
	printsamples(samples, n);

	free(samples);
	return EXIT_SUCCESS;
}