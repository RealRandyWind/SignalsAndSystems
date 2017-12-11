#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double pi = 3.141592653589793238462643383279502884;

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

/* assignment */
void unisoid(int fs, int n, double A, double f, double phi, int* samples)
{
	int k;
	double Ts;
	
	if(!samples) { exit(EXIT_FAILURE); }
	Ts = 1.0 / fs;
	for (k = 0; k < n; ++k)
	{
		samples[k] = (int)(A * cos(2.0 * pi * f * k * Ts + phi));
	}
}

int main(int argc, char const *argv[])
{
	int nscan, n, fs, *samples;
	double A, f, phi;

	nscan = scanf("%i %i %lf %lf %lf", &fs, &n, &A, &f, &phi);
	if (nscan != 5) { exit(EXIT_FAILURE); }
	samples = newsamples(n);
	unisoid(fs, n, A, f, phi, samples);

	printsamples(samples, n);

	free(samples);
	return EXIT_SUCCESS;
}