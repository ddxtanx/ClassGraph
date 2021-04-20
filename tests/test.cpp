#include "../cs225/catch/catch.hpp"

TEST_CASE("test")
{
    int i=5;
    i++;
    REQUIRE(i==6);
}