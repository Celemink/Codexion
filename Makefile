NAME = codexion
CC = cc	
CFLAGS = -Wall -Wextra -Werror -pthread
#codexion = codexion/libftprintf.a  #CAMBIAR LUEGO

SRC = src/main.c 

OBJ = $(SRC:.c=.o)

all: $(NAME)

#$(PRINTF):
	#make -C codexion

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c include/codexion.h
	$(CC) $(CFLAGS) -I include -c $< -o $@

clean:
	rm -f $(OBJ)
	make clean -C codexion

fclean: clean
	rm -f $(NAME)
	make fclean -C codexion

re: fclean all

.PHONY: all clean fclean re