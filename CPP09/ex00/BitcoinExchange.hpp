#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange {
public:
  BitcoinExchange();
  BitcoinExchange(const char *datafile);
  BitcoinExchange(const BitcoinExchange &src);
  ~BitcoinExchange();

  BitcoinExchange &operator=(const BitcoinExchange &rhs);

  void evaluate(const char *inputfile) const;

private:
  std::map<std::string, double> _rates;
};

#endif
