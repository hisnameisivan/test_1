NAME = test
SRC = test.c\
	  str_func.c\
	  lst_func.c\
	  vld_func.c
OBJ = $(SRC:%.c=%.o)
INCLUDES = test.h
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(OBJ): %.o : %.c
	gcc $(FLAGS) -c -I.$(INCLUDES) $< -o $@

$(NAME): $(OBJ)
	gcc $(FLAGS) $(OBJ) -o $(NAME)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY : all, clean, flcean, re
