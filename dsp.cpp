// a C++ project to learn C++, implement some DSP functions
// JFJF_2023126_11158_2.wav - Jasper Farms prairie dog recording

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

int main()
{
    string fname = "JFJF_2023126_11158_2.wav";
    string playcmd = "aplay " + fname;

    cout << "Digital Signal Processing in C++\n";
    system(playcmd.c_str());

    // read in a wav file
    ifstream ifs(fname,ios::binary);
    if(!ifs)
    {
        cout << "couldn't open target for input\n";
        return 1;
    }

    ifs.close();
}