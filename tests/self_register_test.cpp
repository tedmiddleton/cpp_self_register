//          Copyright Ted Middleton 2022.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include <iostream>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "self_register.hpp"

using namespace std;

class test_cls : public self_register
{
public:
};

TEST_CASE("happy path", "[sr]")
{
    test_cls t1;
    REQUIRE(t1.num_instances() == 1);
    {
        test_cls t2;
        REQUIRE(t2.num_instances() == 2);
        REQUIRE(t1.num_instances() == 2);
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

