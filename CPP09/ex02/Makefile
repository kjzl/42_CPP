NAME := PmergeMe

CXX := c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98
# CXXFLAGS += -g3

SRCS := main.cpp PmergeMe.cpp
OBJS := $(SRCS:.cpp=.o)
DEPS := PmergeMe.hpp

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

debug: CXXFLAGS += -g3 -DDEBUG
debug: re

.PHONY: all clean fclean re debug
