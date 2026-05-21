CC = gcc

CFLAGS = -Wall -Wextra -I include

LIBS = -lsqlite3

SRC = src/main.c src/db.c src/enrollee.c src/menu.c

OBJ = obj/main.o obj/db.o obj/enrollee.o obj/menu.o

TARGET = bin/enrollee_app


all: dirs $(TARGET)

dirs:
	mkdir -p bin obj

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

obj/main.o: src/main.c
	$(CC) $(CFLAGS) -c $< -o $@

obj/db.o: src/db.c
	$(CC) $(CFLAGS) -c $< -o $@

obj/enrollee.o: src/enrollee.c
	$(CC) $(CFLAGS) -c $< -o $@

obj/menu.o: src/menu.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf bin obj
