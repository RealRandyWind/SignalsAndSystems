#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double pi2 = 6.283185307179586476925286766559005768;

typedef struct sinusoid_t { double A, f, phi; } sinusoid_t;

int* newsamples(int n)
{
	int* samples;

	samples = (int*) malloc(n * sizeof(int));
	if (!samples) { exit(EXIT_FAILURE); }
	return samples;
}

sinusoid_t* newsinusoids(int n)
{
	sinusoid_t* sinusoids;

	sinusoids = (sinusoid_t*) malloc(n * sizeof(sinusoid_t));
	if (!sinusoids) { exit(EXIT_FAILURE); }
	return sinusoids;
}

void printsamples(const int* samples, int n)
{
	int k;

	if(!samples) { exit(EXIT_FAILURE); }
	printf("[");
	if(n > 0)
	{
		printf("%i", samples[0]);
		for (k = 1; k < n; ++k) { printf(",%i", samples[k]); }
	}
	printf("]\n");
}

/* assignment */
void unisoidadd(int fs, int n, int m, sinusoid_t* sinusoids, int* samples)
{
	int k, p;
	double Ts, sample, omega;
	sinusoid_t so;
	
	if(!samples || !sinusoids || n <= 0 || m <= 0) { exit(EXIT_FAILURE); }
	Ts = 1.0 / fs;
	
	for (k = 0; k < n; ++k)
	{
		sample = 0.0;
		omega = k * pi2 * Ts;
		for (p = 0; p < m; ++p)
		{
			so = sinusoids[p];
			sample += so.A * cos(omega * so.f  + so.phi);
		}
		/* to prevent early convresion to integer */
		samples[k] = (int) sample;
	}
}

int main(int argc, char const *argv[])
{
	int nscan, n, m, fs, p, *samples;
	sinusoid_t so, *sinusoids;

	nscan = scanf("%i %i", &fs, &n);
	nscan += scanf("%i", &m);
	if (nscan != 3) { exit(EXIT_FAILURE); }
	if (m <= 0) { return EXIT_SUCCESS; }
	samples = newsamples(n);
	sinusoids = newsinusoids(m);
	for (p = 0; p < m; ++p)
	{
		nscan = scanf("%lf %lf %lf", &sinusoids[p].A, &sinusoids[p].f, &sinusoids[p].phi);
		if (nscan != 3) { exit(EXIT_FAILURE); }
	}
	unisoidadd(fs, n, m, sinusoids, samples);
	printsamples(samples, n);

	free(samples);
	free(sinusoids);
	return EXIT_SUCCESS;
}