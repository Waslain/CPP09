NAME		= PmergeMe

# Files
SRCS		= main.cpp
OBJS		:= $(SRCS:.cpp=.o)
DEPS		:= $(OBJS:.o=.d)

# Compilator
CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98
# CXXFLAGS	+= -MMD -g3

# Rules
all		: $(NAME)

$(NAME)	: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

leak	: $(NAME)
	valgrind --leak-check=full --track-origins=yes ./$(NAME)

exec	: $(NAME) clean
	./$(NAME)

clean	:
	rm -rf $(OBJS_PATH) $(OBJS) $(DEPS)

fclean	: clean
	rm -rf $(NAME)

re		: fclean all

# Rules for .o files
%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY : all clean fclean re

-include $(DEPS)