# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/16 11:47:12 by faventur          #+#    #+#              #
#    Updated: 2022/07/07 10:28:48 by faventur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c libftools.c utils.c life.c death.c time.c happy_hour.c

OBJS = $(addprefix srcs/, ${SRCS:.c=.o})

FLAGS = -Wall -Wextra -Werror -g3
DANGER = -fsanitize=address

RM = rm -f

NAME = philo_bonus

NONE = \033[0m
HIGREEN = \033[92m
HIBLUE = \033[94m
CURSIVE = \033[3m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(HIGREEN)No! Try not! Do! Or do not! There is no try.$(NONE)"
	@echo "$(CURSIVE)Master Yoda$(NONE)"
	@gcc $(DANGER) $(OBJS) -o $(NAME)
	@echo "$(HIBLUE)Philosopher, c'est apprendre à mourir.$(NONE)"
	@echo "Montaigne, $(CURSIVE)Les Essais$(NONE)"

.c.o:
	gcc $(FLAGS) -c -I./includes $< -o ${<:.c=.o}

exe: all
	@./$(NAME)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
