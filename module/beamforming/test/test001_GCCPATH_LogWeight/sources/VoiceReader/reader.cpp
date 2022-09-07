#include "VoiceReader/reader.hpp"
#include <cstdio>
#include <fstream>
#include <algorithm>

VoiceReader::VoiceReader(const char *fileName)
{
    std::fstream reader(fileName, std::ios::in | std::ios::binary);

    if (!reader.is_open()) {
        return;
    }

    reader.read((char *)&mHeader, sizeof(mHeader));

    mIndexs = std::vector<long long>(mHeader.saveCount, 0ll);
    
    mOrigins = std::vector<std::vector<float>>(
        mHeader.saveCount,
        std::vector<float>(mHeader.dataSize * mHeader.nChannel, 0.0f)
    );

    mDatas = std::vector<std::vector<float>>(
        mHeader.saveCount * mHeader.nChannel,
        std::vector<float>(mHeader.dataSize, 0.0f)
    );

    for (int cnt_save = 0; cnt_save < mHeader.saveCount; ++cnt_save)
    {
        reader.read((char *)(mIndexs.data() + cnt_save), sizeof(long long));
        
        reader.read((char*)(mOrigins[cnt_save].data()), sizeof(float) * mOrigins[cnt_save].size());
    }

    for (int cnt_save = 0; cnt_save < mHeader.saveCount; ++cnt_save)
    {
        for (int cnt_col = 0; cnt_col < mHeader.nChannel; ++cnt_col)
        {
            for (int cnt_time = 0; cnt_time < mHeader.dataSize; ++cnt_time)
            {
                mDatas[cnt_save * mHeader.nChannel + cnt_col][cnt_time] = mOrigins[cnt_save][cnt_time * mHeader.nChannel + cnt_col];
            }
        }
    }

    reader.close();

    return;
}

VoiceReader::VoiceReader(const std::string &fileName):
VoiceReader(fileName.c_str())
{
    return;
}

const std::vector<std::vector<float>> & VoiceReader::get() const
{
    return mDatas;
}

const std::vector<std::vector<float>> & VoiceReader::origin() const
{
    return mOrigins;
}

std::string VoiceReader::version() const
{
    return std::to_string(mHeader.majorVersion) + "." + std::to_string(mHeader.minorVersion);
}

std::string VoiceReader::shape() const
{
    return "(" + std::to_string(mHeader.saveCount) + ", " + std::to_string(mHeader.nChannel) + ", " + std::to_string(mHeader.dataSize) + ")";
}