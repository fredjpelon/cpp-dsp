// a C++ project to learn C++, implement some DSP functions
// get an fft going

#include <iostream>
#include <complex>
using namespace std ;

int main()
{
    const   complex<double> i(0.0,1.0);    
    cout << i << endl ;
}

// from Numerical Recipes in C
#define SWAP(a,b) tempr=(a);(a)=(b);(b)=tempr

void four1_in_C(double *data,unsigned long nn,int isign)
{
        unsigned long n,mmax,m,j,istep,i;
        double wtemp,wr,wpr,wpi,wi,theta;
        double tempr,tempi;

        n=nn << 1;
        j=1;
        for (i=1;i<n;i+=2) {
                if (j > i) {
                        SWAP(data[j],data[i]);
                        SWAP(data[j+1],data[i+1]);
                }
                m=n >> 1;
                while (m >= 2 && j > m) {
                        j -= m;
                        m >>= 1;
                }
                j += m;
        }
        mmax=2;
        while (n > mmax) {
                istep=mmax << 1;
                theta=isign*(6.28318530717959/mmax);
                wtemp=sin(0.5*theta);
                wpr = -2.0*wtemp*wtemp;
                wpi=sin(theta);
                wr=1.0;
                wi=0.0;
                for (m=1;m<mmax;m+=2) {
                        for (i=m;i<=n;i+=istep) {
                                j=i+mmax;
                                tempr=wr*data[j]-wi*data[j+1];
                                tempi=wr*data[j+1]+wi*data[j];
                                data[j]=data[i]-tempr;
                                data[j+1]=data[i+1]-tempi;
                                data[i] += tempr;
                                data[i+1] += tempi;
                        }
                        wr=(wtemp=wr)*wpr-wi*wpi+wr;
                        wi=wi*wpr+wtemp*wpi+wi;
                }
                mmax=istep;
        }
}
#undef SWAP

// Numerical recipes in C++
 void four1(Doub *data, const Int n, const Int isign) {
//Replaces data[0..2*n-1] by its discrete Fourier transform, if isign is input as 1; or replaces
//data[0..2*n-1] by n times its inverse discrete Fourier transform, if isign is input as 1. data
//is a complex array of length n stored as a real array of length 2*n. n must be an integer power
//of 2.
Int nn,mmax,m,j,istep,i;
Doub wtemp,wr,wpr,wpi,wi,theta,tempr,tempi;
if (n<2 || n&(n-1)) throw("n must be power of 2 in four1");
nn = n << 1;
j = 1;
for (i=1; i<nn; i+=2) { //This is the bit-reversal section of the
if (j > i) { //routine.
SWAP(data[j-1],data[i-1]); //Exchange the two complex numbers.
SWAP(data[j],data[i]);
}
m=n;
while (m >= 2 && j > m) {
j -= m
12.2 Fast Fourier Transform (FFT) 613
m >>= 1;
}
j += m;
}
//Here begins the Danielson-Lanczos section of the routine.
mmax=2;
while (nn > mmax) { //Outer loop executed log2 n times.
istep=mmax << 1;
theta=isign*(6.28318530717959/mmax); //Initialize the trigonometric recurrence.
wtemp=sin(0.5*theta);
wpr = -2.0*wtemp*wtemp;
wpi=sin(theta);
wr=1.0;
wi=0.0;
for (m=1;m<mmax;m+=2) { //Here are the two nested inner loops.
for (i=m;i<=nn;i+=istep) {
j=i+mmax; //This is the Danielson-Lanczos for
tempr=wr*data[j-1]-wi*data[j]; //mula:
tempi=wr*data[j]+wi*data[j-1];
data[j-1]=data[i-1]-tempr;
data[j]=data[i]-tempi;
data[i-1] += tempr;
data[i] += tempi;
}
wr=(wtemp=wr)*wpr-wi*wpi+wr; //Trigonometric recurrence.
wi=wi*wpr+wtemp*wpi+wi;
}
mmax=istep;
}
}