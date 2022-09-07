#ifndef _COMMON_FLOW_INTERFACE_
#define _COMMON_FLOW_INTERFACE_

#include "util/Macro.hpp"
#include "util/Factory.hpp"

#ifndef _COMMON_FLOW_INTERFACE_CODE_MESSAGE_
#define _COMMON_FLOW_INTERFACE_CODE_MESSAGE_
#define _COMMON_FLOW_INTERFACE_CODE_AUTHOR_ "milai_oks_sakura"
#define _COMMON_FLOW_INTERFACE_CODE_EMAIL_ CONCAT_STR(_COMMON_FLOW_INTERFACE_CODE_AUTHOR_, "@163.com")
#define _COMMON_FLOW_INTERFACE_CODE_VERSION_ "1.0.0.1"
#endif

namespace BmTools {
    namespace Flow {
        namespace CrossCorrelation {
            namespace Interface {
                template<typename Key, typename CrossCorrelation_t, typename ChannelData_t>
                class Calculator;
            };
        };
    };
};

template<typename Key, typename CrossCorrelation_t, typename ChannelData_t>
class BmTools::Flow::CrossCorrelation::Interface::Calculator
{
    public:
        using Factory = BmTools::Util::Factory::Simple<Key, Calculator, void *>;

        friend Factory;
    protected:
        static void Register(Key type, typename Factory::stdConstructor _instance)
        {
            Factory::FactoryMap.emplace(
                type,
                _instance
            );
        }

        Calculator() = default;

        Calculator(const Calculator &) = default;

        Calculator(Calculator &&) = default;

        Calculator & operator= (const Calculator &) = default;

        Calculator & operator= (Calculator &&) = default;
        
    public:
        
        virtual ~Calculator() = default;

        virtual CrossCorrelation_t run(ChannelData_t) = 0;
};

#endif