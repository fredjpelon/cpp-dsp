class Wavfile
{
public:
    string fname;
    int16_t *data;
    void ReadHeader();
    void ReadData();
};