NAME := btc

CXX := c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98
# CXXFLAGS += -g3

SRCS := main.cpp BitcoinExchange.cpp
OBJS := $(SRCS:.cpp=.o)
DEPS := BitcoinExchange.hpp

all: $(NAME)

$(NAME): $(OBJS) $(DEPS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
