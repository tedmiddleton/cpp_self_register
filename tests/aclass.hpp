#include "self_register.hpp"

class baseclass1
{
public:
    baseclass1() = default;

protected:
    int m_ivar1 = 0;
};

class baseclass2
{
public:
    baseclass2() = default;

protected:
    int m_ivar2 = 0;
};

class baseclass3
{
public:
    baseclass3() = default;

protected:
    int m_ivar3 = 0;
};

class aclass : public baseclass1, public baseclass2, public self_register<aclass>, public baseclass3
{
public:
    aclass() = default;

private:
};

