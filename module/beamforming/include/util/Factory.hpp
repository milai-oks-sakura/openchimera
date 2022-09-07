#ifndef _UTIL_FACTORY_
#define _UTIL_FACTORY_

#include <map>
#include <functional>
#include <memory>

namespace BmTools {
    namespace Util {
        namespace Factory {
            template<typename Key_t, typename Object_t, typename ... Arg_t>
            class Simple;
        };
    };
};

template<typename Key, typename Object_t, typename ... Arg_t>
class BmTools::Util::Factory::Simple {

    using Key_t = Key;

    using Constructor = Object_t *(Arg_t ... arg);

    using stdConstructor = std::function<Constructor>;

    using Pointer_t = std::shared_ptr<Object_t>;

    friend Object_t;

    protected:
        static std::map<Key_t, stdConstructor> FactoryMap;

    public:
        Simple() = delete;
        
        ~Simple() = delete;

        Simple(const Simple&) = delete;

        Simple(Simple &&) = delete;

        Simple & operator= (const Simple&) = delete;

        Simple & operator= (Simple &&) = delete;

        template<Key_t key>
        static Pointer_t Instance(Arg_t ... arg) {

            return Pointer_t(FactoryMap[key](arg ...));
        };

        static Pointer_t Instance(Key_t key, Arg_t ... arg) {
            return Pointer_t(FactoryMap[key](arg ...));
        }
};

template<typename Key, typename Object_t, typename ... Arg_t>
std::map<
    typename BmTools::Util::Factory::Simple<Key, Object_t, Arg_t ...>::Key_t,
    typename BmTools::Util::Factory::Simple<Key, Object_t, Arg_t ...>::stdConstructor
>
BmTools::Util::Factory::Simple<Key, Object_t, Arg_t ...>::FactoryMap;

#endif