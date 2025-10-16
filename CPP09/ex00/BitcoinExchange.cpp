#include "BitcoinExchange.hpp"
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>

static std::map<std::string, float> parseData(const char *file,
                                              bool isInput = false);

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src) { *this = src; }

BitcoinExchange::BitcoinExchange(const char *datafile)
    : _data(parseData(datafile)) {}

/*
** -------------------------------- DESTRUCTOR
* --------------------------------
*/

BitcoinExchange::~BitcoinExchange() {}

/*
** --------------------------------- OVERLOAD
* ---------------------------------
*/

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &rhs) {
  if (this != &rhs) {
    this->_data = rhs._data;
  }
  return *this;
}

/*
** --------------------------------- METHODS
* ----------------------------------
*/

bool BitcoinExchange::isEmpty() const { return _data.empty(); }

void BitcoinExchange::printExchange(const char *inputfile) const {
  std::map<std::string, float> input = parseData(inputfile, true);

  for (std::map<std::string, float>::const_iterator it = input.begin();
       it != input.end(); ++it) {
    std::map<std::string, float>::const_iterator dataIt = _data.find(it->first);
    if (dataIt != _data.end()) {
      std::cout << it->first << " => " << it->second << " = "
                << it->second * dataIt->second << std::endl;
    } else {
      // find closest previous date
      dataIt = _data.lower_bound(it->first);
      if (dataIt == _data.begin()) {
        std::cerr << "Error: no earlier date available for " << it->first
                  << std::endl;
      } else {
        --dataIt;
        std::cout << it->first << " => " << it->second << " = "
                  << it->second * dataIt->second << std::endl;
      }
    }
  }
}

/**
 * Check if the given date string is valid (format: YYYY-MM-DD)
 * Returns true if valid, false otherwise.
 */
static bool isDateValid(const std::string &date) {
  int i = 0;
  while (date[i]) {
    // loop shouldnt run if i is already 10
    if (i == 10)
      return false;
    if (!std::isdigit(date[i])) {
      if (date[i] == '-' && (i == 4 || i == 7)) {
        i++;
        continue;
      } else
        return false;
    }
    i++;
  }
  if (i != 10)
    return false;

  int year = std::atoi(date.substr(0, 4).c_str());
  int month = std::atoi(date.substr(5, 2).c_str());
  int day = std::atoi(date.substr(8, 2).c_str());

  // obviously wrong dates
  if (month < 1 || month > 12 || day < 1 || day > 31)
    return false;

  // First date of Bitcoin exchange rate is 2009-01-02
  if (year < 2009 || (year == 2009 && month == 1 && day < 2))
    return false;

  // Return false if normalization changes the date
  std::tm t = {};
  std::memset(&t, 0, sizeof(t));
  t.tm_year = year - 1900; // tm_year is years since 1900
  t.tm_mon = month - 1;    // tm_mon is 0-11
  t.tm_mday = day;
  t.tm_isdst = -1; // Let mktime determine if DST is in effect
  const std::tm before = t;
  std::mktime(&t);
  if (t.tm_year != before.tm_year || t.tm_mon != before.tm_mon ||
      t.tm_mday != before.tm_mday)
    return false;

  return true;
}
static std::map<std::string, float> parseData(const char *file, bool isInput) {
  std::map<std::string, float> result;

  std::ifstream in(file);
  if (!in.is_open()) {
    std::cerr << "Error: could not open file: " << file << std::endl;
    return result;
  }

  std::string line;
  int i = 0;
  while (std::getline(in, line)) {
    if (++i == 1) // skip header line
      continue;

    if (line.empty())
      continue;

    std::string::size_type comma = line.find(',');
    if (comma == std::string::npos) {
      std::cerr << file << ":" << i << " -> Bad CSV line: [" << line << "]"
                << std::endl;
      continue;
    }

    std::string dateToken = line.substr(0, comma);
    std::string numberToken = line.substr(comma + 1);

    if (dateToken.empty() || numberToken.empty()) {
      std::cerr << file << ":" << i << " -> Bad CSV line: [" << line << "]"
                << std::endl;
      continue;
    }

    if (!isDateValid(dateToken)) {
      std::cerr << file << ":" << i << " -> Bad date: [" << dateToken << "]"
                << std::endl;
      continue;
    }

    char *endptr = 0;
    float value = static_cast<float>(std::strtod(numberToken.c_str(), &endptr));
    if (*endptr != '\0' || value < 0.0f || (isInput && value > 1000.0f)) {
      std::cerr << file << ":" << i << " -> Bad numeric value: [" << numberToken
                << "]" << std::endl;
      continue;
    }

    result[dateToken] = value;
  }

  if (result.empty()) {
    std::cerr << "Error: no valid data loaded from file: " << file << std::endl;
  }

  return result;
}
