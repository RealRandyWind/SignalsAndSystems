#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* assignment */
void car2pol(double x, double y, double* pr, double* ptheta)
{ 
	if (!pr | !ptheta) { exit(EXIT_FAILURE); }
	(*pr) = sqrt(x * x + y * y);
	(*ptheta) = atan2(y, x);
}

int main(int argc, char const *argv[])
{
	int nscan;
	double x, y, r, theta;

	nscan = scanf("%lf %lf", &x, &y);
	if (nscan != 2) { exit(EXIT_FAILURE); }
	car2pol(x, y, &r, &theta);
	printf("%.2f %.2f\n", r, theta);

	return EXIT_SUCCESS;
}