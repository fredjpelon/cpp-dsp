#include <iostream>
#include <complex>
using namespace std;
#include "Wavefile.h"
#include "dspfuncs.h"


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

    cout << "New data =";
    for(int j = 0; j < n; j++)
    {
        cout << " " << vec[j];
    }
    cout << endl;

    cout << "mag =";
    for(int j = 0; j < n; j++)
    {
        cout << " " << abs(vec[j]);
    }
    cout << endl;

    cout << "angle =";
    for(int j = 0; j < n; j++)
    {
        cout << " " << arg(vec[j]);
    }
    cout << endl;

}