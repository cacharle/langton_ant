NAME = ant
CC = gcc
CCFLAGS = -Wall -Wextra -Werror
LDFLAGS = $(shell sdl2-config --libs --cflags)

HEADER = header.h
SRC = main.c graphics.c world.c
OBJ = $(SRC:.c=.o)

RM = rm -f

.PHONY: all
all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(LDFLAGS) $(CCFLAGS) -o $@ $(OBJ)

%.o: %.c
	$(CC) $(LDFLAGS) $(CCFLAGS) -c -o $@ $<

.PHONY: debug
debug: CCFLAGS += -g
debug: re

.PHONY: clean
clean:
	$(RM) $(OBJ)

.PHONY: fclean
fclean: clean
	$(RM) $(NAME)

.PHONY: re
re: fclean all
