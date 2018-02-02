#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct seq_t { int N, *d; } seq_t;

int scanseq(seq_t* pseq)
{
	int n;
	seq_t seq;
	
	if(!pseq) { exit(EXIT_FAILURE); }
	if(!scanf("%d: [", &seq.N)) { return 0; }
	seq.d = (int*) malloc(seq.N * sizeof(int));
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

void lfir(const seq_t h, const seq_t x, seq_t* py)
{
	int k, n, v, q;
	seq_t y;
	
	if(!py) { exit(EXIT_FAILURE); }
	y = (*py);
	/* compute size of y[] and allocate y[] */
	y.N = h.N - 1 + x.N;
	y.d = (int*) malloc(y.N * sizeof(int));
	if(!y.d) { exit(EXIT_FAILURE); }
	/* convolute what is left into y[] ignorant approach */
	for (n = 0; n < y.N; ++n)
	{
		v = 0;
		for (k = 0; k < h.N; ++k)
		{
			q = n - k;
			if( q < 0 || q >= x.N) { continue; }
			v += h.d[k] * x.d[q];
		}
		y.d[n] = v;
	}
	/* ref return y[] */
	(*py) = y;
}

/* assignment */
void lnfir(const seq_t* hs, int M, const seq_t x, seq_t* py)
{
	int m;
	seq_t z, h;

	if(!M || !hs) { exit(EXIT_FAILURE); }
	
	h = hs[0];

	for (m = 1; m < M; ++m)
	{
		lfir(h, hs[m], &z);
		free(h.d);
		h = z;
	}
	lfir(h, x, py);
}

int main()
{
	int nscan, M, m;
	seq_t *hs, x, y;

	if(!scanf("%d",&M)) { exit(EXIT_FAILURE); }
	hs = (seq_t*) malloc(M * sizeof(seq_t));
	if(!hs) { exit(EXIT_FAILURE); }
	for (m = 0; m < M && scanseq(&hs[m]); ++m) { /* do nothing */ }
	if(M != m || !scanseq(&x)) { exit(EXIT_SUCCESS); }
	lnfir(hs, M, x, &y);
	printseq(y);

	while(--M) { free(hs[M].d); } free(x.d); free(y.d);
	return EXIT_SUCCESS;
}