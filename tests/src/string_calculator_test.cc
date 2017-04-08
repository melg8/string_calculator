#include <string>

#include <doctest.h>

#include <string_calculator.h>

SCENARIO("StringCalculator add numbers in string") {
  GIVEN("empty string") {
    const std::string empty_string;
    REQUIRE(empty_string.empty());

    WHEN("call add with that string as argument") {
      const auto result = StringCalculator::Add(empty_string);

      THEN("result should be equal to zero") { REQUIRE_EQ(result, 0); }
    }
  }

  GIVEN("string with single number") {
    static const auto kSingleNumber = "1";

    WHEN("call add with that string as argument") {
      const auto result = StringCalculator::Add(kSingleNumber);

      THEN("result should be equal to that number") { REQUIRE_EQ(result, 1); }
    }
  }

  GIVEN("string with two comma separated numbers as argument") {
    static const auto kTwoCommaSeparatedNumbers = "1,2";

    WHEN("call add with that string") {
      const auto result = StringCalculator::Add(kTwoCommaSeparatedNumbers);

      THEN("result should be equal to sum of this numbers") {
        REQUIRE_EQ(result, 3);
      }
    }
  }

  GIVEN("string with some number of comma separated numbers") {
    static const auto kCommaSeparatedNumbers = "22,0,1,5,11";

    WHEN("call add with that string as argument") {
      const auto result = StringCalculator::Add(kCommaSeparatedNumbers);

      THEN("result should be equal to summ of this numbers") {
        static const auto kSumOfNumbers = 22 + 0 + 1 + 5 + 11;
        REQUIRE_EQ(result, kSumOfNumbers);
      }
    }
  }

  GIVEN("string with \\n symbols as separators") {
    static const auto kNSeparatedNumbers = "1\n2,3";

    WHEN("call add with that string as argument") {
      const auto result = StringCalculator::Add(kNSeparatedNumbers);

      THEN("result should be equal to summ of this numbers") {
        REQUIRE_EQ(result, 6);
      }
    }
  }

  GIVEN("string starts with custom delimiter as \"//;\n1;2\"") {
    static const auto kCustomDelimiter = "//;\n1;2";

    WHEN("call add with that string as argument") {
      const auto result = StringCalculator::Add(kCustomDelimiter);

      THEN("result should be calculated as ; is default delimiter") {
        REQUIRE_EQ(result, 3);
      }
    }
  }

  GIVEN("string with \"*\" custom delimiter") {
    static const auto kCustomDelimiter = "//*\n1*2\n5";

    WHEN("call add with that string as argument") {
      const auto result = StringCalculator::Add(kCustomDelimiter);

      THEN("result should be calculated as * is default delimiter") {
        REQUIRE_EQ(result, 8);
      }
    }
  }

  GIVEN("string with negative number") {
    static const auto kNegativeNumber = "-5";
    WHEN("call add with that string as argument") {
      THEN("exception should be thrown") {
        REQUIRE_THROWS_AS(StringCalculator::Add(kNegativeNumber),
                          std::exception);
      }
    }
  }

  GIVEN("string with negative number") {
    static const auto kNegativeNumber = "-5";
    WHEN("call add with that string as argument and exception is thrown") {
      try {
        StringCalculator::Add(kNegativeNumber);
      } catch (const std::exception& e) {
        THEN("exception should contain \"negatives not allowed: -5\" text") {
          REQUIRE(std::string("negatives not allowed: -5 ") == e.what());
        }
      }
    }
  }

  GIVEN("string with multiple negative numbers") {
    static const auto kMultipleNegativeNumbers = "1,-5,4,-3,6,-1";
    WHEN("call add with that string as argument and exception is thrown") {
      try {
        StringCalculator::Add(kMultipleNegativeNumbers);
      } catch (const std::exception& e) {
        THEN(
            "exception should contain message with all negative numbers with "
            "same order as they appear in original string") {
          REQUIRE(std::string("negatives not allowed: -5 -3 -1 ") == e.what());
        }
      }
    }
  }

  GIVEN("string with number bigger than 1000") {
    static const auto kBigNumbers = "2,1001";

    WHEN("call add with that string as argument") {
      const auto result = StringCalculator::Add(kBigNumbers);

      THEN("number bigger than 1000 is ignored") { REQUIRE_EQ(result, 2); }
    }
  }

  GIVEN("string with delimiter of any length") {
    static const auto kDelimiterWithLength3 = "//[***]\n1***2***3";

    WHEN("call add with that string as argument") {
      const auto result = StringCalculator::Add(kDelimiterWithLength3);

      THEN("this delimiter used as default") { REQUIRE_EQ(result, 6); }
    }
  }
}
