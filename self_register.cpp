//          Copyright Ted Middleton 2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "self_register.hpp"

self_register * self_register::g_baseobj = nullptr;

self_register::self_register()
    : m_nextobj(0)
{
    self_register ** ptrptr = &g_baseobj;
    while (true) {
        self_register * ptr = *ptrptr;
        if (ptr == nullptr) {
            *ptrptr = this;
            m_nextobj = nullptr;
            break;
        }
        else if (ptr == this) {
            break;
        }
        else {
            ptrptr = &(ptr->m_nextobj);
        }
    }
}

self_register::~self_register()
{
    self_register ** ptrptr = &g_baseobj;
    while (true) {
        self_register * ptr = *ptrptr;
        if (ptr == this) {
            *ptrptr = m_nextobj;
            m_nextobj = nullptr;
            break;
        }
        else {
            ptrptr = &(ptr->m_nextobj);
        }
    }
}

size_t self_register::num_instances() const
{
    size_t Num = 0;
    self_register * ptr = g_baseobj;
    while (ptr != nullptr)
    {
        Num++;
        ptr = ptr->m_nextobj;
    }
    return Num;
}


