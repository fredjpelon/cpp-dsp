#include <iostream>
#include <fstream>
using namespace std;
#include "Wavefile.h"

using namespace std;

void Wavfile::ReadHeader()
{
    {
        // read in a wav file
        cout << fname << endl;
        ifstream ifs(fname.c_str(),ios::binary);
        if(!ifs)
        {
            cout << "couldn't open target for input\n";
            //return 1;
        }

        // read header
        ifs.read(m_buf,BUF_SIZE); // RIFF
        cout << string(&m_buf[0], BUF_SIZE) << endl;
        ifs.read(m_buf,BUF_SIZE); // file size
        m_file_len = *reinterpret_cast<int*>(m_buf);
        m_file_len += 8; // size on disk
        cout << "file_len = " << m_file_len << endl;
        ifs.read(m_buf,BUF_SIZE); // WAVE
        cout << string(&m_buf[0], BUF_SIZE) << endl;
        ifs.read(m_buf,BUF_SIZE); // fmt chunk marker
        cout << string(&m_buf[0], BUF_SIZE) << endl;
        ifs.read(m_buf,BUF_SIZE); // length of format data
        cout << "len of format data = " << *reinterpret_cast<int*>(m_buf) << endl;
        ifs.read(m_buf,BUF_SIZE); // data format and number of channels
        int d = *reinterpret_cast<int*>(m_buf);
        int data_format = d >> 16;
        int num_channels = d & 0xffff;
        cout << "data format = " << data_format << endl;
        cout << "number of channels = " << num_channels << endl;
        ifs.read(m_buf,BUF_SIZE); // sample rate
        int sample_rate = *reinterpret_cast<int*>(m_buf);
        cout << "sample rate = " << sample_rate << " Hz" << endl;
        ifs.read(m_buf,BUF_SIZE); // byte rate
        int byte_rate = *reinterpret_cast<int*>(m_buf);
        cout << "byte_rate = " << byte_rate << endl;
        ifs.read(m_buf,BUF_SIZE); // rec type and bps
        d = *reinterpret_cast<int*>(m_buf);
        int bits_per_sample = d >> 16;
        int rec_type= d & 0xffff;
        cout << "recording type = " << rec_type << endl;
        cout << "bits per sample = " << bits_per_sample << endl;
        ifs.read(m_buf,BUF_SIZE); // data
        cout << string(&m_buf[0], BUF_SIZE) << endl;
        ifs.read(m_buf,BUF_SIZE); // data len
        m_data_len_in_bytes = *reinterpret_cast<int*>(m_buf);
        data_len = m_data_len_in_bytes/(bits_per_sample/8);
        cout << "data_len = " << data_len << endl;        

        ifs.close();
    }
}

void Wavfile::ReadData()
{

        data = new int16_t [data_len];

        ifstream ifs(fname.c_str(),ios::binary);
        if(!ifs)
        {
            cout << "couldn't open target for input\n";
            //return 1;
        }
        for(int i =0; i < m_header_len; i++) // move the file pointer to the start of data
        {
            ifs.read(m_d_buf,D_BUF_SIZE); // data len
        }
        for(int i=0; i < data_len; i+=2)
        {
            ifs.read(m_d_buf,D_BUF_SIZE); // data
            data[i/2] = (((int)*(m_d_buf+1)) << 8) | (int)*(m_d_buf);
        }

        ifs.close();
}