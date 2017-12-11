#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void car2pol(double x, double y, double* pr, double* ptheta)
{ 
	if (!pr | !ptheta) { exit(EXIT_FAILURE); }
	(*pr) = sqrt(x * x + y * y);
	(*ptheta) = atan2(y, x);
}

void pol2car(double r, double theta, double* px, double* py)
{ 
	if (!px | !py) { exit(EXIT_FAILURE); }
	(*px) = r * cos(theta);
	(*py) = r * sin(theta);
}

/* assignment */
void addoids(double f, double A0, double phi0, double A1, double phi1, double* pA, double* pphi)
{ 
	double x0, y0, x1, y1, x, y;

	if (!pA | !pphi) { exit(EXIT_FAILURE); }
	pol2car(A0, phi0, &x0, &y0);
	pol2car(A1, phi1, &x1, &y1);
	car2pol(x0 + x1, y0 + y1, pA, pphi);
}

int main(int argc, char const *argv[])
{
	int nscan;
	double f, A0, phi0, A1, phi1, A, phi;

	nscan = scanf("%lf %lf %lf %lf %lf", &f, &A0, &phi0, &A1, &phi1);
	if (nscan != 5) { exit(EXIT_FAILURE); }
	addoids(f, A0, phi0, A1, phi1, &A, &phi);

	if(A < 0.01) { printf("x(t)=%.2f\n", A); }
	else { printf("x(t)=%.2f*cos(2*pi*%.2f*t+%.2f)\n", A, f, phi); }
	
	return EXIT_SUCCESS;
}