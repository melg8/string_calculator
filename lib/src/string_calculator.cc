#include <string_calculator.h>

#include <algorithm>
#include <cassert>
#include <exception>
#include <regex>
#include <sstream>
#include <vector>

static auto SplitByDelim(std::string s, const std::string& delim) {
  std::vector<std::string> elems;
  size_t pos = 0;
  while ((pos = s.find(delim)) != std::string::npos) {
    auto elem = s.substr(0, pos);
    elems.push_back(elem);
    s.erase(0, pos + delim.length());
  }
  if (!s.empty()) {
    elems.push_back(s);  // if no delim occured should return whole string
  }

  return elems;
}

static void ReplaceAll(const std::string& search,
                       const std::string& replace,
                       std::string* s) {
  for (size_t pos = 0;; pos += replace.length()) {
    pos = s->find(search, pos);
    if (pos == std::string::npos) break;
    s->erase(pos, search.length());
    s->insert(pos, replace);
  }
}

static auto NormalizeToDelim(std::string s, const std::string& delim) {
  ReplaceAll({'\n'}, delim, &s);
  return s;
}

static auto CutOfDelimiter(std::string* s) {
  assert(s);
  std::string delimiter{','};
  static const auto kDelimiterStarter = "//";
  const auto delimiter_starter_pos = s->find(kDelimiterStarter);
  if (delimiter_starter_pos == 0) {
    static const auto kDelimiterPos = 2;
    delimiter = s->at(kDelimiterPos);

    static const auto kSizeToCut = 4;
    s->erase(delimiter_starter_pos, kSizeToCut);
  }
  return delimiter;
}

static auto NorlmalizedSplit(std::string s) {
  const auto delim = CutOfDelimiter(&s);
  return SplitByDelim(NormalizeToDelim(s, delim), delim);
}

static auto ToIntNumbers(const std::vector<std::string>& numbers) {
  using namespace std;
  vector<int> int_numbers(numbers.size());
  static const auto s_to_int = [](const string& s) { return stoi(s); };
  transform(begin(numbers), end(numbers), begin(int_numbers), s_to_int);
  return int_numbers;
}

static auto CollectNegativeNumbers(const std::vector<int> numbers) {
  using namespace std;
  vector<int> invalid_numbers;
  static const auto less_than_zero = [](int value) { return value < 0; };
  std::copy_if(begin(numbers), end(numbers), back_inserter(invalid_numbers),
               less_than_zero);
  return invalid_numbers;
}

static auto MessageAboutNegativeNumbers(
    const std::vector<int> negative_numbers) {
  std::string message = "negatives not allowed: ";
  for (const auto number : negative_numbers) {
    message += std::to_string(number) + ' ';
  }
  return message;
}

static void ReportErrorAboutNegativeNumbers(
    const std::vector<int> negative_numbers) {
  if (!negative_numbers.empty()) {
    throw std::logic_error(MessageAboutNegativeNumbers(negative_numbers));
  }
}

static void ReportErrorIfFoundNegativeNumbers(const std::vector<int> numbers) {
  ReportErrorAboutNegativeNumbers(CollectNegativeNumbers(numbers));
}

static auto WithoutGraterThanThousandElements(std::vector<int> numbers) {
  using namespace std;
  static const auto greater = [](int value) { return value > 1000; };
  numbers.erase(remove_if(begin(numbers), end(numbers), greater), end(numbers));
  return numbers;
}

static auto SplitToSmallIntNumbers(const std::string& numbers) {
  return WithoutGraterThanThousandElements(
      ToIntNumbers(NorlmalizedSplit(numbers)));
}

int StringCalculator::Add(const std::string& numbers) {
  auto small_numbers = SplitToSmallIntNumbers(numbers);
  ReportErrorIfFoundNegativeNumbers(small_numbers);
  return std::accumulate(std::begin(small_numbers), std::end(small_numbers), 0);
}
