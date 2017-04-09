#include <string_calculator.h>

#include <algorithm>
#include <cassert>
#include <numeric>
#include <stdexcept>
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
    if (pos == std::string::npos) {
      break;
    }
    s->erase(pos, search.length());
    s->insert(pos, replace);
  }
}

static auto NormalizeToDefaultDelimeter(
    std::string s,
    const std::string& default_delim,
    const std::vector<std::string>& delimeters) {
  for (const auto& delimeter : delimeters) {
    ReplaceAll(delimeter, default_delim, &s);
  }
  return s;
}

static auto CutOffDelimiters(std::string* s) {
  assert(s);
  std::vector<std::string> delimiter{{','}};
  if (s->size() > 2 && s->at(0) == '/' && s->at(1) == '/') {
    auto new_line = std::find(std::begin(*s), std::end(*s), '\n');
    if (new_line != std::end(*s)) {
      std::string clean_delimiters(std::begin(*s), new_line + 1);
      s->erase(0, clean_delimiters.size());
      clean_delimiters.erase(0, 2);
      clean_delimiters.erase(clean_delimiters.size() - 1);
      if (clean_delimiters.at(0) == '[') {
        clean_delimiters.erase(0, 1);
      }
      if (clean_delimiters.at(clean_delimiters.size() - 1) == ']') {
        clean_delimiters.erase(clean_delimiters.size() - 1);
      }
      return SplitByDelim(clean_delimiters, "][");
    }
  }

  return delimiter;
}

static auto NorlmalizedSplit(std::string s) {
  const auto delims = CutOffDelimiters(&s);
  static const auto kDefaultDelim = '\n';
  return SplitByDelim(NormalizeToDefaultDelimeter(s, {kDefaultDelim}, delims),
                      {kDefaultDelim});
}

static auto ToIntNumbers(const std::vector<std::string>& numbers) {
  std::vector<int> int_numbers(numbers.size());
  static const auto kStringToInt = [](const std::string& s) {
    return std::stoi(s);
  };
  transform(std::begin(numbers), std::end(numbers), std::begin(int_numbers),
            kStringToInt);
  return int_numbers;
}

static auto CollectNegativeNumbers(const std::vector<int>& numbers) {
  std::vector<int> invalid_numbers;
  static const auto kLessThanZero = [](int value) { return value < 0; };
  std::copy_if(std::begin(numbers), std::end(numbers),
               std::back_inserter(invalid_numbers), kLessThanZero);
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
    const std::vector<int>& negative_numbers) {
  if (!negative_numbers.empty()) {
    throw std::logic_error(MessageAboutNegativeNumbers(negative_numbers));
  }
}

static void ReportErrorIfFoundNegativeNumbers(const std::vector<int>& numbers) {
  ReportErrorAboutNegativeNumbers(CollectNegativeNumbers(numbers));
}

static auto WithoutGraterThanThousandElements(std::vector<int> numbers) {
  static const auto kGreater = [](int value) { return value > 1000; };
  numbers.erase(
      std::remove_if(std::begin(numbers), std::end(numbers), kGreater),
      std::end(numbers));
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
