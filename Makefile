CC = clang

SRC = main.c ft_event.c ft_init.c ft_wallhit.c ft_wallhitv.c \
	ft_drawslice.c ft_turnleft.c ft_turnright.c ft_moveplayer.c

OBJ = $(SRC:.c=.o)

FLAGS = -Werror -Wextra -Wall

DEPS = wolf3d.h

MATH = -lm

cSDL := $(shell sdl2-config --cflags) $(shell pkg-config --cflags SDL2_Image)

SDL := $(shell sdl2-config --cflags --libs) $(shell pkg-config --cflags --libs SDL2_Image)

.PHONY : all clean fclean re

all : $(OBJ)
	make -C libft/
	$(CC) $(OBJ) -o wolf3d $(SDL) libft/libft.a $(FLAGS) $(MATH)

%.o : %.c $(DEPS)
	@$(CC) -c -o $@ $< $(cSDL) $(FLAGS)
	echo "Compiled Successfully"

clean :
	make clean -C libft/
	rm -f $(OBJ)

fclean : clean
	rm -f libft/libft.a
	rm -f wolf3d

re : fclean all
