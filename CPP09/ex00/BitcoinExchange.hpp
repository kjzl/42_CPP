#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <string>

class BitcoinExchange {

public:
  BitcoinExchange();
  BitcoinExchange(BitcoinExchange const &src);
  BitcoinExchange(const char *datafile);
  ~BitcoinExchange();

  BitcoinExchange &operator=(BitcoinExchange const &rhs);

  bool isEmpty() const;
  void printExchange(const char *inputfile) const;

private:
  std::map<std::string, float> _data;
};

#endif /* ************************************************* BITCOINEXCHANGE_H  \
        */
