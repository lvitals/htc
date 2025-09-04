# 1 "tests/atan.c"

# 1 "/home/leandro/workspaces/estudos-compiladores/new-hitech-c/libc/include/math.h"



extern double fabs(double), floor(double), ceil(double), modf(double, double *);
extern double sqrt(double), atof(char *);
extern double sin(double), cos(double), tan(double);
extern double asin(double), acos(double), atan(double), atan2(double, double);
extern double frexp(double, int *), ldexp(double, int);
extern double log(double), log10(double), pow(double, double), exp(double);
extern double sinh(double), cosh(double), tanh(double);



# 2 "tests/atan.c"





double
atan(f)
double	f;
{
	static double	coeff_a[] =
	{
		33.058618473989548,
		58.655751569001961,
		32.390974856200445,
		5.8531952112628600,
		0.19523741936234277,
		-.0024346033004411264
	};
	static double	coeff_b[] =
	{
		33.058618473992416,
		69.675291059524653,
		49.004348218216250,
		12.975578862709239,
		1.0
	};
	int	recip;
	extern double	eval_poly(), fabs();
	double		val, val_squared;

	if((val = fabs(f)) == 0.0)
		return 0.0;
	if(recip = (val > 1.0))
		val = 1.0/val;
	val_squared = val * val;
	val *= eval_poly(val_squared, coeff_a, 5)/eval_poly(val_squared, coeff_b, 4);
	if(recip)
		val = 1.570796326794895 - val;
	return f < 0.0 ? -val : val;
}
