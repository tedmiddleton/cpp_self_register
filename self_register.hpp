//          Copyright Ted Middleton 2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef INCLUDED_self_register_hpp
#define INCLUDED_self_register_hpp

#include <cstddef>

class self_register
{
public:
    self_register();
    virtual ~self_register();

    size_t num_instances() const;

private:
    self_register * m_nextobj = nullptr;
    static self_register * g_baseobj;
};

#endif //INCLUDED_self_register_hpp

