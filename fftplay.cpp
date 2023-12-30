// a C++ project to learn C++, implement some DSP functions
// get an fft going
// 12/28/2023; First pass use four1 directly out of the book
// note that complex numbers not explicitly used here (TO DO)
// though there is a complex type defined later in the book.
// use C++ complex (TO DO)
// replace hard-coded trigv values with calculation (TO DO)
// make 0-origin uindexing (TO DO)

#include <iostream>
#include <complex>
#include <math.h>
using namespace std ;

// Numerical Recipes in C, 1988
void four1(float *data, int nn, int isign);

int main()
{
    //float data[16] ={0, 0, 1, 0, 2, 0, 1, 0, 0, 0, -1, 0, -2, 0, -1, 0};
    //x = np.array([1.0, 2.0, 1.0, -1.0, 1.5])
    float data[16] ={1, 0, 2, 0, 1, 0, -1, 0, 1.5, 0, 0, 0, 0, 0, 0, 0};

    cout << "FFT module test" << endl;
    const   complex<double> i(0.0,1.0);    
    cout << "Complex vals test " << i << endl;
    cout << "FFT test" << endl << "data =";
    for (int i = 0; i < 18; i += 2)
    {
        cout << " " << data[i] << " " << data[i+1];
    }
    cout << endl;

    four1(data-1, 8, 1); // zero-origin indexing

    cout << "New data =";
    for (int i = 0; i < 18; i += 2)
    {
        cout << " " << data[i] << " " << data[i+1];
    }
    cout << endl;

}

// from Numerical Recipes in C
#define SWAP(a,b) tempr = (a); (a) = (b); (b) = tempr

void four1(float *data, int nn, int isign)
// Replaces data by its discrete Fourier transform, if isign is input as 1; or replaces data by
// nn time its inverse discrete transform , if isign is input as -1. data is a complex array
// of length nn, input as a real array data[1..2*nn].
// nn MUST be an iteger power of 2 (this is not checked for!).
// make 0-origin indexing (FFS), first make 1-indexing work with data shifted by 1
{
    int n, mmax, m, j, istep, i;
    double wtemp, wr, wpr, wpi, wi, theta; // Double precision for the trigonometric recurrences.
    float tempr, tempi;

    n = nn << 1;
    j = 1;
    for (i=1; i < n; i+=2) // This is the bit-reversal section of the routine.
    {
        if (j > i)
        {
            SWAP(data[j], data[i]);     // Exchange the two complex numbers.
            SWAP(data[j+1], data[i+1]);
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
        istep = 2*mmax;
        theta = 6.28318530717959/(isign*mmax); // Initialize for the trigionometric recurrence.
        wtemp = sin(0.5*theta);
        wpr = -2.0*wtemp*wtemp;
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
#undef SWAP