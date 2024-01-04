#include <iostream>
using namespace std;
#include "Wavefile.h"

int main()
{
    Wavfile wavfile;

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

}