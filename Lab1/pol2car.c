#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* assignment */
void pol2car(double r, double theta, double* px, double* py)
{ 
	if (!px | !py) { exit(EXIT_FAILURE); }
	(*px) = r * cos(theta);
	(*py) = r * sin(theta);
}

int main(int argc, char const *argv[])
{
	int nscan;
	double x, y, r, theta;

	nscan = scanf("%lf %lf", &r, &theta);
	if (nscan != 2) { exit(EXIT_FAILURE); }
	pol2car(r, theta, &x, &y);
	printf("%.2f %.2f\n", x, y);
	
	return EXIT_SUCCESS;
}