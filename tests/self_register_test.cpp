//          Copyright Ted Middleton 2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include <iostream>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "self_register.hpp"
#include "aclass.hpp"
#include "sr_test_1.hpp"
#include "sr_test_2.hpp"

using namespace std;

class test_cls : public self_register<test_cls>
{
public:

    int var() const { return m_ivar2; }
    void setvar(int var) { m_ivar2 = var; }

private:
    int m_ivar2 = -20;
};

TEST_CASE("test_cls", "[self_register]")
{
    test_cls t1;
    REQUIRE(t1.num_instances() == 1);
    {
        test_cls t2;
        REQUIRE(test_cls::s_num_instances() == 2);
        REQUIRE(test_cls::s_num_instances() == 2);
        {
            test_cls t3;
            REQUIRE(t3.num_instances() == 3);
            REQUIRE(t2.num_instances() == 3);
            REQUIRE(t1.num_instances() == 3);
        }
        REQUIRE(t2.num_instances() == 2);
        REQUIRE(t1.num_instances() == 2);
    }
    REQUIRE(t1.num_instances() == 1);
}

TEST_CASE("test_cls inherit", "[self_register]")
{
    test_cls t0;
    test_cls t1;
    test_cls t2;
    test_cls t3;

    test_cls* t = t2.get_instance(0);
    REQUIRE(t != nullptr);
    REQUIRE(t == &t0);

    t = test_cls::s_get_instance(2);
    REQUIRE(t != nullptr);
    REQUIRE(t == &t2);
}

TEST_CASE("aclass", "[self_register]")
{
    // These both have a global instance
    REQUIRE(sr_test_1_main() == 2);
    REQUIRE(sr_test_2_main() == 2);
    {
        aclass ainst1;
        REQUIRE(sr_test_1_main() == 3);
        REQUIRE(sr_test_2_main() == 3);
        REQUIRE(ainst1.num_instances() == 3);
        {
            aclass ainst2;
            REQUIRE(sr_test_1_main() == 4);
            REQUIRE(sr_test_2_main() == 4);
            REQUIRE(ainst1.num_instances() == 4);
            REQUIRE(ainst2.num_instances() == 4);
            {
                auto ainst3 = std::make_shared<aclass>();
                REQUIRE(sr_test_1_main() == 5);
                REQUIRE(sr_test_2_main() == 5);
                REQUIRE(ainst1.num_instances() == 5);
                REQUIRE(ainst2.num_instances() == 5);
                REQUIRE(ainst3->num_instances() == 5);
            }
            REQUIRE(sr_test_1_main() == 4);
            REQUIRE(sr_test_2_main() == 4);
            REQUIRE(ainst1.num_instances() == 4);
            REQUIRE(ainst2.num_instances() == 4);
        }
        REQUIRE(sr_test_1_main() == 3);
        REQUIRE(sr_test_2_main() == 3);
        REQUIRE(ainst1.num_instances() == 3);
    }
    REQUIRE(sr_test_1_main() == 2);
    REQUIRE(sr_test_2_main() == 2);
}


