#ifndef _CHANNEL_LOG_WEIGHT_HPP_
#define _CHANNEL_LOG_WEIGHT_HPP_

#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>

#ifndef NDEBUG
#include <iostream>
#endif

namespace Beamforming
{
    namespace Weight
    {
        template<typename T>
        class LogPower;
    };
};

template<typename T>
class Beamforming::Weight::LogPower
{
    private:
        std::vector<T> mWeight;

    public:
        LogPower(int numChannels):
            mWeight(numChannels, 0) {return;};
        
        ~LogPower() = default;

        LogPower(const LogPower &) = default;
        
        template<typename T2>
        LogPower(const LogPower<T2> &copy):
            mWeight(copy.mWeight.size(), 0) {
                std::copy(copy.mWeight.begin(), copy.mWeight.end(), mWeight.begin());
                return;
            };

        LogPower(LogPower &&) = default;

        LogPower & operator= (const LogPower &) = default;

        template<typename T2>
        LogPower & operator= (const LogPower<T2> &copy) {
            mWeight.resize(copy.mWeight.size()); 
            std::copy(copy.mWeight.begin(), copy.mWeight.end(), mWeight.begin());
            return *this;
        }

        LogPower & operator= (LogPower &&) = default;

        bool run(
            const std::vector<std::vector<T>> &originData,
            T threshold = 0,
            T gain = 1,
            T bias = 1
        )
        {
            if (originData.size() != mWeight.size()) return false;
            
            T sum = 0;

            for (int idx = 0; idx < mWeight.size(); ++idx) {
                mWeight[idx] = std::accumulate(
                    originData[idx].begin(),
                    originData[idx].end(),
                    mWeight[idx],
                    [](T result, T input) {result += std::abs(input); return result;}
                );

            }

            sum = std::accumulate(
                mWeight.begin(),
                mWeight.end(),
                sum,
                [](T result, T input) {result += (input * input); return result;}
            );

            sum /= mWeight.size();

            std::transform(
                mWeight.begin(),
                mWeight.end(),
                mWeight.begin(),
                [&](T input) {T result = std::log10(input * input / sum); return result > threshold ? gain * result + bias : 1;}
            );

            return true;
        }

        const std::vector<T> & get() const
        {
            return mWeight;
        }
};

#endif