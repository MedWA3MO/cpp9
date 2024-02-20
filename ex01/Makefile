NAME  = RPN

FILE  =  main.cpp RPN.cpp

RM    = rm -f

CC    = c++

FLAGS = -Wall -Werror -Wextra  -std=c++98

OBJS  = $(FILE:.cpp=.o)



all     : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o  $(NAME)

%.o : %.cpp RPN.hpp
	$(CC) $(FLAGS) -c $< -o $@

clean   :
	$(RM) $(OBJS)

fclean  : clean
	$(RM) $(NAME)

re      : fclean all

.PHONY  : all clean fclean re