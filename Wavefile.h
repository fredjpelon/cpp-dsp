#ifndef Wavfile_H
#define Wavfile_H

class Wavfile
{
public:
    string fname;
    int16_t *data;
    void ReadHeader();
    void ReadData();
private:
    char *m_buf;
    char *m_d_buf;
    int m_file_len;
    int m_data_len, m_data_len_in_bytes;
    int m_header_len;
};

#endif