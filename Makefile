NAME = codexion
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -I include

SRC =	src/main.c \
	src/parser.c \
	src/parser_utils.c \
	src/utils.c \
	src/init.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

#$(PRINTF):
#make -C codexion

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)
	make clean -C codexion

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re