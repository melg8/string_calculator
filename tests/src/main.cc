#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

SCENARIO("breathing test") {
  GIVEN("all setup correctly") {
    WHEN("check for sanity") {
      THEN("true equals to true") { REQUIRE_EQ(true, true); }
    }
  }
}
