#ifndef Wavfile_H
#define Wavfile_H

#define BUF_SIZE 4
#define D_BUF_SIZE 2
#define WAV_HEADER_SIZE 44 // bytes

class Wavfile
{
public:
    string fname;
    int16_t *data;
    void ReadHeader();
    void ReadData();
private:
    //char *m_buf;
    //char *m_d_buf;
    char m_buf[BUF_SIZE]={0,0};
    char m_d_buf[D_BUF_SIZE]={0};
    int m_file_len;
    int m_data_len, m_data_len_in_bytes;
    int m_header_len = WAV_HEADER_SIZE/2; // in double bytes
};

#endif