#include "BitcoinExchange.hpp"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <datafile> <inputfile>" << std::endl;
    return 1;
  }

  BitcoinExchange btcExchange(argv[1]);
  if (btcExchange.isEmpty())
    return 1;

  btcExchange.printExchange(argv[2]);
  return 0;
}
