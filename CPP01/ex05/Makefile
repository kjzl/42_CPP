NAME := harl

CXX := clang++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98 -MMD -MP
CXXFLAGS += -O3 -march=native
# CXXFLAGS += -g3

SRCS := main.cpp Harl.cpp
OBJS := $(SRCS:.cpp=.o)
DEPS := $(OBJS:.o=.d)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)
