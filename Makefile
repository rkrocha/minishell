NAME 			= minishell

SRCS_DIR 		= ./src
OBJS_DIR 		= ./obj
INCLUDES_DIR 	= ./includes

LIBFT_DIR 		= ./libft
LIBFT 			= $(LIBFT_DIR)/libft.a

CC 				= gcc
CFLAGS 			= -Wall -Wextra -Werror $(LEAKCHECK)
LEAKCHECK 		= -g -fsanitize=address
LFLAGS 			= -L./libft -lft -lreadline
IFLAGS			= -I$(LIBFT_DIR) -I$(INCLUDES_DIR)

RM 				= rm -f
NORM			= norminette

INCLUDES_FILES =	minishell.h

INCLUDES 		= $(addprefix $(INCLUDES_DIR)/, $(INCLUDES_FILES))

# **************************************************************************** #
#                                 MINISHELL                                    #
# **************************************************************************** #

SRCS = 				minishell.c \
					parser.c \
					router.c \
					utils.c \
					builtin_env.c \
					builtin_exit.c

OBJS 			= $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))

# **************************************************************************** #
#                                   MAKE                                       #
# **************************************************************************** #

$(NAME): 		$(LIBFT) $(OBJS) $(INCLUDES)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LFLAGS) $(IFLAGS)

all: 			$(NAME)

bonus: 			all

$(LIBFT):
				@make -C $(LIBFT_DIR) --no-print-directory

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(INCLUDES_DIR) $(INCLUDES)
				@mkdir -p $(OBJS_DIR)
				@$(CC) $(CFLAGS) -I $(INCLUDES_DIR) -c $< -o $@ $(IFLAGS)

.PHONY:			all bonus

# **************************************************************************** #
#                                   CLEAN                                      #
# **************************************************************************** #

clean:
				@make -C $(LIBFT_DIR) clean --no-print-directory
				@$(RM) $(OBJS)

fclean: 		clean
				@make -C $(LIBFT_DIR) fclean --no-print-directory
				@$(RM) $(NAME)
				@rm -rf $(OBJS_DIR)

re: 			fclean all

.PHONY:			clean fclean re

# **************************************************************************** #
#                                NORMINETTE                                    #
# **************************************************************************** #

norm:
				@$(NORM) $(SRCS_DIR)/*.c $(INCLUDES_DIR)/*.h

.PHONY:			norm
