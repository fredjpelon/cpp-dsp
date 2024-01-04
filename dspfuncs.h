#include <complex>
using namespace std;
//#define M_PI 3.1415926535897932384
#define MAX 200

// Numerical Recipes in C, 1988
void four1(double *data, unsigned long nn, int isign);
// some coder on the internet
void FFT(complex<double>* f, int N, double d);
int log2(int N);
int check(int n);
int reverse(int N, int n);
void ordina(complex<double>* f1, int N);
void transform(complex<double>* f, int N);
