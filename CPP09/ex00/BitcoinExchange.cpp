#include "BitcoinExchange.hpp"

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>

static bool isAllWhitespace(const std::string &s) {
  for (std::string::size_type i = 0; i < s.size(); ++i) {
    if (s[i] != ' ' && s[i] != '\t' && s[i] != '\r')
      return false;
  }
  return true;
}

static bool parseDate(const std::string &s,
                      int &year, int &month, int &day) {
  if (s.size() != 10)
    return false;
  if (s[4] != '-' || s[7] != '-')
    return false;
  for (std::string::size_type i = 0; i < 10; ++i) {
    if (i == 4 || i == 7)
      continue;
    if (s[i] < '0' || s[i] > '9')
      return false;
  }
  year = std::atoi(s.substr(0, 4).c_str());
  month = std::atoi(s.substr(5, 2).c_str());
  day = std::atoi(s.substr(8, 2).c_str());
  return true;
}

static bool isValidDate(int year, int month, int day) {
  if (year < 1 || month < 1 || month > 12 || day < 1)
    return false;

  std::tm t;
  t.tm_year = year - 1900;
  t.tm_mon = month - 1;
  t.tm_mday = day;
  t.tm_hour = 12;
  t.tm_min = 0;
  t.tm_sec = 0;
  t.tm_isdst = -1;

  std::tm copy = t;
  if (std::mktime(&copy) == static_cast<std::time_t>(-1))
    return false;

  return copy.tm_year == t.tm_year
      && copy.tm_mon == t.tm_mon
      && copy.tm_mday == t.tm_mday;
}

// OCF

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const char *datafile) {
  std::ifstream file(datafile);
  if (!file.is_open())
    throw std::runtime_error("could not open database file");

  std::string line;
  std::getline(file, line); // skip header

  while (std::getline(file, line)) {
    if (line.empty() || isAllWhitespace(line))
      continue;

    std::string::size_type comma = line.find(',');
    if (comma == std::string::npos)
      throw std::runtime_error("bad database format");

    std::string date = line.substr(0, comma);
    std::string rateStr = line.substr(comma + 1);

    char *end;
    double rate = std::strtod(rateStr.c_str(), &end);
    if (*end != '\0' && *end != '\r')
      throw std::runtime_error("bad rate in database");

    _rates[date] = rate;
  }
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src) {
  *this = src;
}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rhs) {
  if (this != &rhs)
    _rates = rhs._rates;
  return *this;
}

// evaluation

void BitcoinExchange::evaluate(const char *inputfile) const {
  std::ifstream file(inputfile);
  if (!file.is_open()) {
    std::cerr << "Error: could not open file." << std::endl;
    return;
  }

  std::string line;
  std::getline(file, line); // skip header

  while (std::getline(file, line)) {
    if (line.empty() || isAllWhitespace(line))
      continue;

    std::string::size_type sep = line.find(" | ");
    if (sep == std::string::npos) {
      std::cerr << "Error: bad input => " << line << std::endl;
      continue;
    }

    std::string date = line.substr(0, sep);
    std::string valStr = line.substr(sep + 3);

    int year, month, day;
    if (!parseDate(date, year, month, day) || !isValidDate(year, month, day)) {
      std::cerr << "Error: bad input => " << date << std::endl;
      continue;
    }

    char *end;
    double value = std::strtod(valStr.c_str(), &end);
    if (*end != '\0' && *end != '\r') {
      std::cerr << "Error: bad input => " << date << std::endl;
      continue;
    }

    if (value < 0) {
      std::cerr << "Error: not a positive number." << std::endl;
      continue;
    }

    if (value > 1000) {
      std::cerr << "Error: too large a number." << std::endl;
      continue;
    }

    // find closest lower-or-equal date
    std::map<std::string, double>::const_iterator it = _rates.upper_bound(date);
    if (it == _rates.begin()) {
      std::cerr << "Error: bad input => " << date << std::endl;
      continue;
    }
    --it;

    double result = value * it->second;
    std::cout << date << " => " << value << " = " << result << std::endl;
  }
}
