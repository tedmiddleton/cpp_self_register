//          Copyright Ted Middleton 2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef INCLUDED_self_register_hpp
#define INCLUDED_self_register_hpp

#include <cstddef>

///
/// self_register - a small class for keeping track of derived instances.
///
///     class some_class : public some_other_class, self_register<some_class>
///     {};
///
///     some_class sc1;
///     ...
///     some_class sc2;
///     ...
///     some_class sc3;
///     //  some_class::s_num_instances() will return 3 at this point
///
/// All of the usual caveats about multi-threading and virtual inheritance apply 
/// - self_register is not thread-safe and can't be used with virtual inheritance
///
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
        return T::s_num_instances();
    }

    static size_t s_num_instances()
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

    T * get_instance(size_t ind)
    {
        return T::s_get_instance(ind);
    }

    static T * s_get_instance(size_t ind)
    {
        size_t curr = 0;
        self_register * ptr = g_baseobj;
        while (curr < ind && ptr != nullptr)
        {
            curr++;
            ptr = ptr->m_nextobj;
        }
        if (curr == ind) {
            return static_cast<T*>(ptr);
        }
        else {
            return nullptr;
        }
    }

private:
    self_register * m_nextobj = nullptr;
    static self_register * g_baseobj;
};

template<typename T>
self_register<T> * self_register<T>::g_baseobj = nullptr;

#endif //INCLUDED_self_register_hpp

