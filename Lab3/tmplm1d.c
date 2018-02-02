#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DEFAULT_MATCH_CNT 4
#define EPS 0.000001

typedef struct fseq_t { int N; double *d; } fseq_t;
typedef struct seq_t { int N, *d; } seq_t;
typedef struct entry_t { int n; double r; } entry_t;
typedef struct match_t { int N, _N; entry_t *d; } match_t;

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

void printmatch(const match_t match)
{
	int n;

	if(!match.d || match.N < 0 ) { exit(EXIT_FAILURE); }
	for(n = 0; n < match.N; ++n) { printf("%d %.5f\n", match.d[n].n, match.d[n].r); }
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
		y.d[n] = (vz - alpha * vh1 * vx1) / sqrt((vx2 - vx1 * vx1 * alpha) * a);
		vx = x.d[n];
	}
	free(z.d);
	/* ref return y[] */
	(*py) = y;
}

/* assignment */
void tmplm1d(const double T, const seq_t h, const seq_t x, match_t *py)
{
	int n;
	match_t y;
	fseq_t z;
	entry_t e;

	if(!py) { exit(EXIT_FAILURE); }
	y = (*py);

	pearson1d(h, x, &z);
	y.N = 0; y._N = DEFAULT_MATCH_CNT;
	y.d = (entry_t *) malloc(y._N * sizeof(entry_t));
	if(!y.d) { exit(EXIT_FAILURE); }
	/* find matches (could have print directly in ajusted pearson1d but i choce this way) */
	for (n = 0; n < z.N; ++n)
	{
		if(z.d[n] < T - EPS) { continue; }
		if(++y.N > y._N)
		{ 
			y._N <<= 1;
			y.d = (entry_t*) realloc(y.d, y._N * sizeof(entry_t));
			if(!y.d) { exit(EXIT_FAILURE); }
		}
		y.d[y.N - 1].n = n; y.d[y.N - 1].r = z.d[n];
	}
	free(z.d);
	(*py) = y;
}

int main()
{
	double T;
	int nscan;
	seq_t h, x;
	match_t y;

	nscan = scanf("%lf", &T);
	nscan += scanseq(&h);
	nscan += scanseq(&x);
	if(nscan != 3 || T < -1.0 || T > 1.0) { exit(EXIT_FAILURE); }
	tmplm1d(T, h, x, &y);
	printmatch(y);

	free(h.d); free(x.d); free(y.d);
	return EXIT_SUCCESS;
}