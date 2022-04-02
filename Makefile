# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: manuelbeeler <manuelbeeler@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/17 15:54:37 by jjuntune          #+#    #+#              #
#    Updated: 2022/04/02 18:04:57 by manuelbeele      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = mbeeler.filler

FILES = ./sources/filler.c
FILES += ./sources/ft_read_input.c
FILES += ./sources/ft_get_heat.c
FILES += ./sources/ft_place_piece.c

OFILES = $(FILES:.c=.o)

LIBRERY = libft/libft.a

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OFILES)
	make -C libft/
	gcc $(FLAGS) -o $(NAME) $(OFILES) $(LIBRERY)

/%.o:%.c
	gcc $(FLAGS) -c $(FILES) $<

clean:
	make -C libft/ clean
	find ./sources/ -type f -name "*.o" -delete
	
fclean: clean
	rm -rf $(NAME)
	make -C libft/ fclean

re: fclean all
