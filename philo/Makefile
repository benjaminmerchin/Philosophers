NAME	=	philo
CC		=	clang
OBJDIR	=	objects
SRC		=	philosophers.c libft_0.c libft_1.c utils_0.c utils_1.c
OBJ 	=	$(addprefix $(OBJDIR)/, $(SRC:.c=.o))
CFLAGS	=	-Wall -Wextra -Werror -pthread#-g3  -fsanitize=thread#-fsanitize=address

ifneq (,$(findstring xterm,${TERM}))
	GREEN := $(shell tput -Txterm setaf 2)
	RESET := $(shell tput -Txterm sgr0)
else
	GREEN := ""
	RESET := ""
endif

all: $(NAME)

bonus: all

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "${GREEN}Compilation Done${RESET}"

$(OBJDIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re bonus
