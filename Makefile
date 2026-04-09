CC = gcc
CFLAGS = -Wall -Wextra -g

SRC = main.c da_token.c lexer.c parser.c
OBJ = $(SRC:.c=.o)
TARGET = minisql

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
