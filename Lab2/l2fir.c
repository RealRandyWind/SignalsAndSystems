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
void l2fir(const seq_t h1, const seq_t h2, const seq_t x, seq_t* py)
{
	seq_t z;

	lfir(h1, h2, &z);
	lfir(z, x, py);
	free(z.d);
}

int main()
{
	int nscan;
	seq_t h1, h2, x, y;

	nscan = scanseq(&h1);
	nscan += scanseq(&h2);
	nscan += scanseq(&x);
	if(nscan != 3) { exit(EXIT_SUCCESS); }
	l2fir(h1, h2, x, &y);
	printseq(y);

	free(h1.d); free(h2.d); free(x.d); free(y.d);
	return EXIT_SUCCESS;
}