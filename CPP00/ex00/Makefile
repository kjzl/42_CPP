NAME := megaphone

CXX := clang++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98 -MMD -MP
CXXFLAGS += -O3 -march=native
# CXXFLAGS += -g3

SRCS := megaphone.cpp
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

test: $(NAME)
	./$(NAME) "shhhhh... I think the students are asleep..."
	./$(NAME) Damnit " ! " "Sorry students, I thought this thing was off."
	./$(NAME)

val: $(NAME)
	valgrind --leak-check=full -s ./$(NAME)

.PHONY: all clean fclean re test val

-include $(DEPS)
