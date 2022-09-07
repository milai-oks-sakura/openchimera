#include "VoiceReader/reader.hpp"
#include "SignalAnalysis/PowerSpecturm/ChannelLogWeight.hpp"
#include <iostream>


int main(int argc, char **argv)
{
    if (argc < 2) return 0;

    VoiceReader reader(argv[1]);

    auto logPower = Beamforming::Weight::LogPower<float>(reader.mHeader.nChannel);

    std::cout << "Voice file version: " <<  reader.version() << std::endl;

    std::cout << "data shape: " <<  reader.shape() << std::endl;

    for (int cnt_save = 0; cnt_save < reader.mHeader.saveCount; ++cnt_save)
    {
        std::vector<std::vector<float>> temp(
            reader.get().begin() + cnt_save * reader.mHeader.nChannel,
            reader.get().begin() + cnt_save * reader.mHeader.nChannel + reader.mHeader.nChannel
        );

        if(!logPower.run(temp)) exit(-1);

        std::cout << "cnt_save = " << cnt_save << std::endl;

        for (auto &item : logPower.get())
        {
            std::cout << item << " ";
        }

        std::cout << std::endl;
    }

    return 0;
}