CC = gcc
CFLAGS = -std=c11 -Werror -Wall -Wno-vla-parameter

TARGET = main

SRCS = main.c global.c game_init.c game.c map_handler.c utility.c render.c items.c

OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lncurses -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
