#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange {
public:
  BitcoinExchange(const char *datafile);
  BitcoinExchange(const BitcoinExchange &src);
  ~BitcoinExchange();

  BitcoinExchange &operator=(const BitcoinExchange &rhs);

  void evaluate(const char *inputfile) const;

private:
  std::map<std::string, double> _rates;

  static bool parseDate(const std::string &s, int &year, int &month, int &day);
  static bool isValidDate(int year, int month, int day);
  static bool isLeapYear(int year);
};

#endif
