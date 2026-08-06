NAME = codexion
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -I include

SRC =	src/main.c \
	src/parser.c \
	src/parser_utils.c \
	src/utils.c \
	src/init.c \
	src/time.c \
	src/coders/routine.c \
	src/simulation.c

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# COLORS
GREEN  = \033[0;32m
BLUE   = \033[0;34m
CYAN   = \033[0;36m
YELLOW = \033[1;33m
RED    = \033[0;31m
WHITE  = \033[1;37m
RESET  = \033[0m

all: $(NAME)

#$(PRINTF):
#make -C codexion

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "$(BLUE)[CC]$(RESET) %-35s\n" "$<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@clear
	@echo "$(CYAN)"
	@echo "▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀"
	@echo "▄▀                                                                    ▄▀"
	@echo "▄▀    ██████╗ ██████╗ ██████╗ ███████╗██╗  ██╗██╗ ██████╗ ███╗   ██╗  ▄▀"
	@echo "▄▀   ██╔════╝██╔═══██╗██╔══██╗██╔════╝╚██╗██╔╝██║██╔═══██╗████╗  ██║  ▄▀"
	@echo "▄▀   ██║     ██║   ██║██║  ██║█████╗   ╚███╔╝ ██║██║   ██║██╔██╗ ██║  ▄▀"
	@echo "▄▀   ██║     ██║   ██║██║  ██║██╔══╝   ██╔██╗ ██║██║   ██║██║╚██╗██║  ▄▀"
	@echo "▄▀   ╚██████╗╚██████╔╝██████╔╝███████╗██╔╝ ██╗██║╚██████╔╝██║ ╚████║  ▄▀"
	@echo "▄▀    ╚═════╝ ╚═════╝ ╚═════╝ ╚══════╝╚═╝  ╚═╝╚═╝ ╚═════╝ ╚═╝  ╚═══╝  ▄▀"
	@echo "▄▀                                                                    ▄▀"
	@echo "▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀▄▀"
	@echo ""
	@echo "$(WHITE) ✓ Parser loaded $(RESET)"
	@sleep 0.1
	@echo "$(WHITE) ✓ Memory manager loaded$(RESET)"
	@sleep 0.1
	@echo "$(WHITE) ✓ Thread engine loaded$(RESET)"
	@sleep 0.1
	@echo "$(WHITE) ✓ Dongle manager loaded$(RESET)"
	@sleep 0.1
	@echo "$(WHITE) ✓ Scheduler loaded$(RESET)"
	@sleep 0.1
	@echo "$(WHITE) ✓ Game lost$(RESET)"
	@sleep 0.1
	@echo ""
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)✔ Build completed successfully.$(RESET)"
	@echo "$(CYAN)══════════════════════════════════════════════════════════════$(RESET)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(YELLOW)🧹 Removed object files.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)🗑 Removed executable.$(RESET)"

re: fclean all

.PHONY: all clean fclean re