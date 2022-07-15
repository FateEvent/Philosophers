# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: faventur <faventur@student.42mulhouse.fr>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/28 17:51:01 by albaur            #+#    #+#              #
#    Updated: 2022/07/15 15:45:15 by faventur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_FILES = libftools.c philosophers.c sanity_check.c init.c manage.c

SRCS_PATH = srcs/

SRCS +=	$(addprefix $(SRCS_PATH), $(SRCS_FILES))

OBJS_PATH = bin/

OBJS = 	$(addprefix $(OBJS_PATH), $(SRCS_FILES:.c=.o))

FLAGS = -Wall -Wextra -Werror

LIBLINKS = -I./includes

LINKS = -lpthread

RM = rm -f

NAME = philo

NONE = \033[0m
HIGREEN = \033[92m
HIBLUE = \033[94m
CURSIVE = \033[3m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(HIGREEN)No! Try not! Do! Or do not! There is no try.$(NONE)"
	@echo "$(CURSIVE)Master Yoda$(NONE)"
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LINKS)
	@echo "$(HIBLUE)Philosopher, c'est apprendre à mourir.$(NONE)"
	@echo "Montaigne, $(CURSIVE)Les Essais$(NONE)"

.c.o:
	gcc $(FLAGS) $(LIBLINKS) -c $< -o ${<:.c=.o}

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c 
	@mkdir -p $(dir $@)
	${CC} ${CFLAGS} $(LIBLINKS) -c $< -o $@

clean:
	@$(RM) -r $(OBJS_PATH)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
