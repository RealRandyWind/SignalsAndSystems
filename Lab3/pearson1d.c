#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct fseq_t { int N; double *d; } fseq_t;
typedef struct seq_t { int N, *d; } seq_t;

int scanseq(seq_t* pseq)
{
	int n;
	seq_t seq;
	
	if(!pseq) { exit(EXIT_FAILURE); }
	if(!scanf("%d: [", &seq.N)) { return 0; }
	seq.d = (int *) malloc(seq.N * sizeof(int));
	if(!seq.d) { exit(EXIT_FAILURE); }
	scanf("%d", &seq.d[n = 0]);
	while((++n < seq.N) && scanf(",%d", &seq.d[n])) { /* do nothing */ }
	if(getchar()!=']') { return 0; }
	(*pseq) = seq;
	return 1;
}

void printseq(const seq_t seq)
{
	int n;

	if(!seq.d || seq.N < 0 ) { exit(EXIT_FAILURE); }
	printf("%d: [", seq.N);
	if(seq.N) { printf("%d", seq.d[0]); }
	for(n = 1; n < seq.N; ++n) { printf(",%d", seq.d[n]); }
	printf("]\n");
}

void printfseq(const fseq_t seq)
{
	int n;

	if(!seq.d || seq.N < 0 ) { exit(EXIT_FAILURE); }
	printf("%d: [", seq.N);
	if(seq.N) { printf("%.5f", seq.d[0]); }
	for(n = 1; n < seq.N; ++n) { printf(",%.5f", seq.d[n]); }
	printf("]\n");
}

/* place holder, see problem one for ntt implementation */
void corr1d(const seq_t h, const seq_t x, seq_t *py)
{
	int n, k, v;
	seq_t y;

	if(!py || h.N > x.N) { exit(EXIT_FAILURE); }
	y = (*py);
	/* compute size of y[] and allocate y[] */
	y.N = x.N - h.N + 1;
	y.d = (int *) malloc(y.N * sizeof(int));
	if(!y.d) { exit(EXIT_FAILURE); }
	/* compute foreach y[n] = h[k] x[n + k] over h[] */
	for (n = 0; n < y.N; ++n)
	{
		v = 0;
		for (k = 0; k < h.N; ++k) { v += h.d[k] * x.d[n + k]; }
		y.d[n] = v;
	}
	/* ref return y[] */
	(*py) = y;
}

/* assignment */
void pearson1d(const seq_t h, const seq_t x, fseq_t* py)
{
	int k, n; 
	double vh, vh1, vh2, vx, vx1, vx2, vz, v, alpha, a;
	seq_t z;
	fseq_t y;
	
	if(!py) { exit(EXIT_FAILURE); }
	y = (*py);
	/* compute size of y[] and allocate y[] */
	y.N = x.N - h.N + 1;
	y.d = (double *) malloc(y.N * sizeof(double));
	if(!y.d) { exit(EXIT_FAILURE); }
	/* compute sum of h, x, h^2 and x^2 initial */
	vh1 = 0; vx1 = 0; vh2 = 0; vx2 = 0;
	for (k = 0; k < h.N; ++k)
	{
		vh = (double) h.d[k]; vx = (double) x.d[k];
		vh1 += vh; vx1 += vx;
		vh2 += vh * vh; vx2 += vx * vx;
	}
	/* compute constants */
	alpha = (1.0 / h.N);
	a = (vh2 - vh1 * vh1 * alpha);
	/* compute y[n] = (corr1d[n] - alpha vh1 vx2) / sqrt(a (vx2 - alpha vx1^2)) */
	corr1d(h, x, &z);
	for (n = 0; n < y.N; ++n)
	{
		vx1 -= vx; vx2 -= vx * vx;
		v = (double) x.d[n + h.N - 1];
		vx1 += v; vx2 += v * v;
		vz = (double) z.d[n];
		y.d[n] = (vz - alpha * vh1 * vx1) / sqrt((vx2 - vx1 * vx1 * alpha) * a) ;
		vx = x.d[n];
	}
	free(z.d);
	/* ref return y[] */
	(*py) = y;
}

int main()
{
	int nscan;
	seq_t h, x;
	fseq_t y;

	nscan = scanseq(&h);
	nscan += scanseq(&x);
	if(nscan != 2) { exit(EXIT_FAILURE); }
	pearson1d(h, x, &y);
	printfseq(y);

	free(h.d); free(x.d); free(y.d);
	return EXIT_SUCCESS;
}