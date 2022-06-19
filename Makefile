MY		= my
STD		= std
FLAGS	= -Wall -Wextra -Werror -std=c++98
INCLUDES= -I. -I./utils -I./utils/iterators
SRCS_M	= stack_my_test.cpp
SRCS_S	= stack_std_test.cpp
CC		= c++
RES_STD	= resstd.txt
RES_MY	= resmy.txt

all: $(MY) $(STD)

$(MY):
	$(CC) $(FLAGS) $(INCLUDES) $(SRCS_M) -o $(MY)

$(STD):
	$(CC) $(FLAGS) $(INCLUDES) $(SRCS_S) -o $(STD)

test: $(MY) $(STD)
	time ./$(MY) 0 > $(RES_MY)
	time ./$(STD) 0 > $(RES_STD)
	diff $(RES_MY) $(RES_STD)

clean:
	rm -f $(RES_MY) $(RES_STD)

fclean: clean
	rm -f $(MY) $(STD)

re: fclean all

.PHONY: all clean fclean re