CC = gcc
CFLAGS = -Wall -Wextra -Iheaders

SRC = main.c \
	src/ad_stack.c \
	src/image_work.c \
	src/lodepng.c \
	src/search_ships.c \
	src/transformation.c \
	src/visualisation.c

OBJ = $(SRC:.c=.o)

TARGET = tankers

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
