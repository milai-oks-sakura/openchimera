#ifndef _READER_
#define _READER_

#include <string>
#include <vector>

struct FileHeader {
    int headerSize;
    int majorVersion;
    int minorVersion;
    int saveCount;
    int dataSize;
    int nChannel;
};

class VoiceReader
{
    private:
        std::vector<long long> mIndexs;

        std::vector<std::vector<float>> mOrigins;

        std::vector<std::vector<float>> mDatas;

    public:
        FileHeader mHeader;

        VoiceReader(const char *fileName);
        
        VoiceReader(const std::string &fileName);

        const std::vector<std::vector<float>> & get() const;

        const std::vector<std::vector<float>> & origin() const;
    
        ~VoiceReader() = default;

        std::string version() const;

        std::string shape() const;
};

#endif