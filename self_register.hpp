//          Copyright Ted Middleton 2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef INCLUDED_self_register_hpp
#define INCLUDED_self_register_hpp

#include <cstddef>

template<typename T>
class self_register
{
public:
    self_register()
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

    virtual ~self_register()
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

    size_t num_instances() const
    {
        size_t num = 0;
        self_register * ptr = g_baseobj;
        while (ptr != nullptr)
        {
            num++;
            ptr = ptr->m_nextobj;
        }
        return num;
    }

private:
    self_register * m_nextobj = nullptr;
    static self_register * g_baseobj;
};

template<typename T>
self_register<T> * self_register<T>::g_baseobj = nullptr;

#endif //INCLUDED_self_register_hpp

