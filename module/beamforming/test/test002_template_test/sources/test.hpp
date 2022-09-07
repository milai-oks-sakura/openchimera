#ifndef _TEST_HPP_
#define _TEST_HPP_

#include "common/FlowInterface.hpp"
#include <vector>

enum class Key {
    a
};

using CSM_t = BmTools::Flow::CrossCorrelation::Interface::Calculator<
    Key,
    const std::vector<float> &,
    const std::vector<float> &
>;

#endif