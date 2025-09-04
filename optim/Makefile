TARGET = optim
SRCS = optim.c

CC = gcc
CFLAGS = -std=c89 -g -Wall -Wextra -O2

OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
