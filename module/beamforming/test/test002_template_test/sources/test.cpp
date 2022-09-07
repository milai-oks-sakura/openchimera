#include "test.hpp"

class Test_t : public CSM_t
{
    struct _Register;
    static _Register _register;
    static CSM_t * _Instance(void *);

    private:
        std::vector<float> mResult;
    public:
        Test_t(void *data);

        virtual ~Test_t() = default;

        virtual const std::vector<float> & run(const std::vector<float> &);
};

struct Test_t::_Register {
    _Register() {
        Register(
            Key::a,
            _Instance
        );
    }

    ~_Register() = default;
} Test_t::_register;

CSM_t * Test_t::_Instance(void *data)
{
    return new Test_t(data);
}

Test_t::Test_t(void *data)
{
    return;
}

const std::vector<float> & Test_t::run(const std::vector<float> &)
{
    return mResult;
}