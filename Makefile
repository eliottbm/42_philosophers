# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/13 11:16:00 by ebengtss          #+#    #+#              #
#    Updated: 2024/08/22 15:17:31 by ebengtss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS 			+=	--no-print-directory

NAME				=	philo

CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -g -pthread -I

SRCS_DIR			=	srcs/
OBJS_DIR			=	objs/
INCS_DIR			=	incs

SRCS_FILES			=	main.c				\
						free.c				\
						utils.c				\
						locks.c				\
						locks2.c			\
						init.c				\
						threads.c			\
						philo_routine.c		\
						monitor_routine.c

OBJS				=	$(addprefix $(OBJS_DIR), $(SRCS_FILES:.c=.o))

DEF_COLOR			=	\033[0;39m
GREEN				=	\033[0;92m
DEF_STYLE			=	\e[0m
BOLD_OPACITY		=	\e[1m\e[2m
RESET_LINE			=	\033[A\033[K

OBJSF				=	.objs_exists

all					:	$(NAME)

$(NAME)				:	$(OBJS)
	@echo "$(RESET_LINE)$(BOLD_OPACITY)[ PHILO ]$(DEF_STYLE)	compiling:	$(GREEN) ✔ $(DEF_COLOR)"
	@$(CC) -o $(NAME) $(CFLAGS) $(INCS_DIR) $(OBJS)
	@echo "$(BOLD_OPACITY)[ PHILO ]$(DEF_STYLE)	make:		$(GREEN) ✔ $(DEF_COLOR)"

$(OBJS_DIR)%.o		:	$(SRCS_DIR)%.c | $(OBJSF)
	@$(CC) $(CFLAGS) $(INCS_DIR) -c $< -o $@
	@echo "$(RESET_LINE)$(BOLD_OPACITY)[ PHILO ]$(DEF_STYLE)	compiling:	$(GREEN) $< $(DEF_COLOR)"

$(OBJSF)	:
	@echo "$(BOLD_OPACITY)[ PHILO ]$(DEF_STYLE)	nothing to do"
	@mkdir -p $(OBJS_DIR)

clean			:
	@rm -rf $(OBJS_DIR)
	@echo "$(BOLD_OPACITY)[ PHILO ]$(DEF_STYLE)	clean:		$(GREEN) ✔ $(DEF_COLOR)"

fclean			:	clean
	@rm -f $(NAME)
	@echo "$(BOLD_OPACITY)[ PHILO ]$(DEF_STYLE)	fclean:		$(GREEN) ✔ $(DEF_COLOR)"

re				:	fclean all

.PHONY			:	all clean fclean re 