#include <iostream>
#include <complex>
#include <fstream>
#include <math.h>
using namespace std;
#include "Wavefile.h"
#include "dspfuncs.h"
#include "constants.h"


int main()
{
    // read in wavfile
    Wavfile wavfile;
    // fft play
    unsigned long n = 8;
    int step_size = 1; 
    complex<double> vec[n]={{1, 0}, {2, 0}, {1, 0}, {-1, 0}, {1.5, 0}, {0, 0}, {0, 0}, {0, 0}};

    // read in wavfile
    string fname = "JFJF_2023126_11158_2.wav";
    string playcmd = "aplay " + fname;

    wavfile.fname = fname;
    wavfile.ReadHeader();
    wavfile.ReadData();
    for (int i = 0; i < 5; i++)
    {
        cout << wavfile.data[i] << endl;
    }


    cout << "Digital Signal Processing in C++\n";
    system(playcmd.c_str()); // system() expects a constant

    // play with DSP funcs now. Start with FFT
    cout << "FFT test" << endl;
    cout << "Input vector = " << endl;
    for(int j = 0; j < n; j++)
    {
        cout << " " << vec[j];
    }
    cout << endl;

    FFT(vec, n, step_size);

    display_data(vec,n);

    // Now, let's play with the wav data
    // start with a small vector
    cout << "data_len = " << wavfile.data_len << endl;
    n = wavfile.data_len;
    long nn = 131072;
    cout << "FFT length = " << nn << endl;
    complex<double> xformdata[nn];
    for(int i = 0; i < nn; i++)
    {
        //creating the complex number, let's normalize that pup while we're here
        xformdata[i] = complex <double> ((double)wavfile.data[i]/BIT16_MAX, 0);
    }

    cout << "Prairie dog data before " << endl;
    display_data(xformdata,8);
    FFT(xformdata, nn, step_size);
    cout << "Prairie dog data after " << endl;
    display_data(xformdata,8);

    // Create a file stream object.
    ofstream outfile("fftmag.bin", ios::binary);
    // write FFT mag data to a file for display
    double tmp = 0.0;
    cout << "size of tmp = " << sizeof tmp << endl;
    for (unsigned long i = 0; i < nn/2; i++)
    {
        tmp = abs(xformdata[i]);
        outfile.write( reinterpret_cast<char*>( &tmp ), sizeof tmp );
    }
    outfile.close();
}