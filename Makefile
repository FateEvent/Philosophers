# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/16 11:47:12 by faventur          #+#    #+#              #
#    Updated: 2022/05/06 15:39:07 by faventur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c

OBJS	= $(addprefix srcs/, ${SRCS:.c=.o})

FLAGS = -Wall -Wextra -Werror

LINKS = -lpthread

RM =	rm -f

NAME = philo

NONE = \033[0m
HIGREEN = \033[92m
HIBLUE = \033[94m
CURSIVE = \033[3m

all: $(NAME)

$(NAME): $(OBJS)
	@gcc $(FLAGS) $(OBJS) $(LINKS) -o $(NAME)
	@echo "$(HIBLUE)Carneade! Chi era costui?$(NONE)"
	@echo "Don Abbondio, $(CURSIVE)I promessi sposi$(NONE)"
	@echo "$(HIGREEN)No! Try not! Do! Or do not! There is no try.$(NONE)"
	@echo "$(CURSIVE)Master Yoda$(NONE)"
	@rm $(OBJS)

.c.o:
	gcc -Wall -Wextra -Werror -c $< -o ${<:.c=.o}

exe: all
	@./$(NAME)

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all