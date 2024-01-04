#include <math.h>
#include "dspfuncs.h"
using namespace std;
// from someone on stackoverflow
//#include <iostream>
//#include <complex>
//#define MAX 200

//using namespace std;

//#define M_PI 3.1415926535897932384

int log2(int N)    // function to calculate the log2(.) of int numbers
{
  int k = N, i = 0;
  while(k)
  {
    k >>= 1;
    i++;
  }
  return i - 1;
}

int check(int n)    // checking if the number of element is a power of 2
{
  return n > 0 && (n & (n - 1)) == 0;
}

int reverse(int N, int n)    //calculating revers number
{
  int j, p = 0;
  for(j = 1; j <= log2(N); j++) {
    if(n & (1 << (log2(N) - j)))
      p |= 1 << (j - 1);
  }
  return p;
}

void ordina(complex<double>* f1, int N) //using the reverse order in the array
{
  complex<double> f2[MAX];
  for(int i = 0; i < N; i++)
    f2[i] = f1[reverse(N, i)];
  for(int j = 0; j < N; j++)
    f1[j] = f2[j];
}

void transform(complex<double>* f, int N) //
{
  ordina(f, N);    //first: reverse order
  complex<double> *W;
  W = (complex<double> *)malloc(N / 2 * sizeof(complex<double>));
  W[1] = polar(1., -2. * M_PI / N);
  W[0] = 1;
  for(int i = 2; i < N / 2; i++)
    W[i] = pow(W[1], i);
  int n = 1;
  int a = N / 2;
  for(int j = 0; j < log2(N); j++) {
    for(int i = 0; i < N; i++) {
      if(!(i & n)) {
        complex<double> temp = f[i];
        complex<double> Temp = W[(i * a) % (n * a)] * f[i + n];
        f[i] = temp + Temp;
        f[i + n] = temp - Temp;
      }
    }
    n *= 2;
    a = a / 2;
  }
  free(W);
}

void FFT(complex<double>* f, int N, double d)
{
  transform(f, N);
  for(int i = 0; i < N; i++)
    f[i] *= d; //multiplying by step
}

// from Numerical Recipes in C, but the imaginary part is the wrong sign
// The imnplications of this are that the first part of the spectrum is really
// the negative freq flip
void four1(double *data, unsigned long nn, int isign)
// Replaces data by its discrete Fourier transform, if isign is input as 1; or replaces data by
// nn time its inverse discrete transform, if isign is input as -1. data is a complex array
// of length nn, input as a real array data[1..2*nn].
// nn MUST be an integer power of 2 (this is not checked for!).
// make 0-origin indexing (FFS), first make 1-indexing work with data shifted by 1
// per NumRinC (see text ahead of function)
{
    unsigned long n, mmax, m, j, istep, i;
    double wtemp, wr, wpr, wpi, wi, theta; // Double precision for the trigonometric recurrences.
    double tempr, tempi;

    n = nn << 1;
    j = 1;
    for (i=1; i < n; i+=2) // This is the bit-reversal section of the routine.
    {
        if (j > i)
        {
            swap(data[j], data[i]);     // Exchange the two complex numbers.
            swap(data[j+1], data[i+1]);
        }

        m = n >> 1;
        while (m >= 2 && j > m) 
        {
            j -= m;
            m >>= 1;
        }
        j += m;
    }

    mmax = 2;           // Here begins the Danielson-Lanczos section of the routine.
    while (n > mmax)    // Outer loop executed log<sub 2^nn> times.
    {
        istep = mmax << 1;
        theta = isign * (6.28318530717959/mmax); // Initialize for the trigionometric recurrence.
        wtemp = sin(0.5*theta);
        wpr = -2.0*wtemp*wtemp;
        //wpi = -sin(theta); // make this negative here to match the scipy (python) FFT implementation
        wpi = sin(theta);
        wr = 1.0;
        wi = 0.0;

        for (m = 1; m < mmax; m += 2) // Here are the two nested inner loops.
        {
            for (i = m; i <= n; i += istep)
            {
                j = i + mmax; // This is the Danielson-Lanczos formula:
                tempr = wr*data[j] - wi*data[j+1];
                tempi = wr*data[j+1] + wi*data[j];
                data[j] = data[i] - tempr;
                data[j+1] = data[i+1] - tempi;
                data[i] += tempr;
                data[i+1] += tempi;
            }

            wr = (wtemp = wr)*wpr - wi*wpi + wr;
            wi = wi*wpr + wtemp*wpi + wi;
        }
        mmax = istep;
    }
}
//#undef SWAP

