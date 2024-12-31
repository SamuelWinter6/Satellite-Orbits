CC = gcc
CFLAGS = -Wall -Wextra
OBJ = src/main.o src/physics.o
TARGET = satellite_simulation

all: $(TARGET)

$(TARGET): $(OBJ)
    $(CC) $(CFLAGS) -o $@ $^

src/%.o: src/%.c include/%.h
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    rm -f src/*.o $(TARGET)