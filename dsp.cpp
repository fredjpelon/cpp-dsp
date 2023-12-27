// a C++ project to learn C++, implement some DSP functions
// JFJF_2023126_11158_2.wav - Jasper Farms prairie dog recording

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;
class Wavfile
{
public:
    void ReadHeader();
};

#define BUF_SIZE 4
#define D_BUF_SIZE 2

int main()
{
    char *buf;
    buf = new char [BUF_SIZE];

    string fname = "JFJF_2023126_11158_2.wav";
    string playcmd = "aplay " + fname;

    //wavfile.ReadHeader(fname);

    cout << "Digital Signal Processing in C++\n";
    //system(playcmd.c_str()); // system() expects a constant

    // read in a wav file
    ifstream ifs(fname,ios::binary);
    if(!ifs)
    {
        cout << "couldn't open target for input\n";
        return 1;
    }

    //for (auto i = 0; i < 5; i++)
    //{
    //    ifs.read(buf,1);
    //    cout << "char = " << *buf << " as dec " << +(*buf) << endl; // + = unary cast char -> int
    //}

    // read header
    ifs.read(buf,BUF_SIZE); // RIFF
    cout << string(&buf[0], BUF_SIZE) << endl;
    ifs.read(buf,BUF_SIZE); // file size
    int file_len = *reinterpret_cast<int*>(buf);
    file_len += 8; // size on disk
    cout << "file_len = " << file_len << endl;
    ifs.read(buf,BUF_SIZE); // WAVE
    cout << string(&buf[0], BUF_SIZE) << endl;
    ifs.read(buf,BUF_SIZE); // fmt chunk marker
    cout << string(&buf[0], BUF_SIZE) << endl;
    ifs.read(buf,BUF_SIZE); // length of format data
    cout << "len of format data = " << *reinterpret_cast<int*>(buf) << endl;
    ifs.read(buf,BUF_SIZE); // data format and number of channels
    int d = *reinterpret_cast<int*>(buf);
    int data_format = d >> 16;
    int num_channels = d & 0xffff;
    cout << "data format = " << data_format << endl;
    cout << "number of channels = " << num_channels << endl;
    ifs.read(buf,BUF_SIZE); // sample rate
    int sample_rate = *reinterpret_cast<int*>(buf);
    cout << "sample rate = " << sample_rate << " Hz" << endl;
    ifs.read(buf,BUF_SIZE); // byte rate
    int byte_rate = *reinterpret_cast<int*>(buf);
    cout << "byte_rate = " << byte_rate << endl;
    ifs.read(buf,BUF_SIZE); // rec type and bps
    d = *reinterpret_cast<int*>(buf);
    int bits_per_sample = d >> 16;
    int rec_type= d & 0xffff;
    cout << "recording type = " << rec_type << endl;
    cout << "bits per sample = " << bits_per_sample << endl;
    ifs.read(buf,BUF_SIZE); // data
    cout << string(&buf[0], BUF_SIZE) << endl;
    ifs.read(buf,BUF_SIZE); // data len
    int data_len_in_bytes = *reinterpret_cast<int*>(buf);
    int data_len = data_len_in_bytes/(bits_per_sample/8);
    cout << "data_len = " << data_len << endl;

    char *d_buf;
    d_buf = new char [D_BUF_SIZE];
    int16_t *data;
    data = new int16_t [data_len];
    cout << "addy = " << &data << endl;

    //ifs.read(data,data_len_in_bytes); // data
    //int16_t d_;
    for(int i=0; i < data_len; i+=2)
    {
        ifs.read(d_buf,D_BUF_SIZE); // data
        data[i/2] = (((int)*(d_buf+1)) << 8) | (int)*(d_buf);
        if(i < 12)
        {
            cout << data[i/2] << endl;
        }
    }


    ifs.close();
}