#include <complex>
using namespace std;
//#define M_PI 3.1415926535897932384
//#define MAX 200

// Numerical Recipes in C, 1988
void four1(double *data, unsigned long nn, int isign);
// some coder on the internet
void FFT(complex<double>* f, unsigned long N, double d);
int log2(unsigned long N);
int check(unsigned long n);
int reverse(unsigned long N, unsigned long n);
void ordina(complex<double>* f1, unsigned long N);
void transform(complex<double>* f, unsigned long N);
void display_data(complex<double>* data, int n);
