#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ntt.h"

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

/*
uint *conv(uint lenx, int *x, uint leny, int *y, uint *lenxy) {
  uint i, omega, lenz, *tmp, *z;

  *lenxy = lenx + leny - 1;  
  lenz = findRoot(*lenxy, &omega);
  z = calloc(lenz, sizeof(uint));
  tmp = calloc(lenz, sizeof(uint));
  memcpy(tmp, x, lenx*sizeof(uint));
  memcpy(z, y, leny*sizeof(uint));

  ntt(prime, omega, lenz, tmp);
  ntt(prime, omega, lenz, z);

  for (i=0; i<lenz; i++) {
    z[i] = (z[i]*tmp[i])%prime;
  }
  free(tmp);
  intt(prime, omega, lenz, z);
  return (uint*)z;
}
*/

/* assignment */
void corr1d(const seq_t h, const seq_t x, seq_t *py)
{
	int n;
	seq_t y, g, z;
	
	if(!py || h.N > x.N) { exit(EXIT_FAILURE); }
	/* compute size of y[] and allocate y[] */
	y.N = x.N - h.N + 1; g.N = h.N;
	y.d = (int *) malloc(y.N * sizeof(int));
	g.d = (int *) malloc(g.N * sizeof(int));
	if(!y.d || !g.d) { exit(EXIT_FAILURE); }
	
	/* conv{n-k} = corr{n+k} same as flipping h[] */
	for(n = 0; n < g.N; ++n) { g.d[n] = h.d[h.N - 1 - n]; }
	/* compute conv into z[] */
	z.d = conv(g.N, g.d, x.N, x.d, &z.N);
	/* copy interesting part of z[] into y[] */
	for(n = 0; n < y.N; ++n) { y.d[n] = z.d[h.N - 1 + n]; }

	free(g.d); free(z.d);
	/* ref return y[] */
	(*py) = y;
}

int main()
{
	int nscan;
	seq_t h, x, y;

	nscan = scanseq(&h);
	nscan += scanseq(&x);
	if(nscan != 2) { exit(EXIT_FAILURE); }
	corr1d(h, x, &y);
	printseq(y);

	free(h.d); free(x.d); free(y.d);
	return EXIT_SUCCESS;
}
