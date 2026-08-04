NAME = codexion
CC = cc	
CFLAGS = -Wall -Wextra -Werror -pthread
codexion = codexion/libftprintf.a  #CAMBIAR OPCIONALMENTE

SRC = #no sabemos aun

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(PRINTF):
	make -C codexion

$(NAME): $(PRINTF) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(PRINTF) -o $(NAME)

%.o: %.c push_swap.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make clean -C codexion

fclean: clean
	rm -f $(NAME)
	make fclean -C codexion

re: fclean all

.PHONY: all clean fclean re