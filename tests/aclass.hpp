#include "self_register.hpp"

class baseclass
{
public:
    baseclass() = default;

protected:
    int m_ivar1 = 0;
};

class aclass : public baseclass, public self_register<aclass>
{
public:
    aclass() = default;
    virtual ~aclass() = default;

private:
};
