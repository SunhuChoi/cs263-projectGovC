# Compiler
CC = clang
CFLAGS = -Wall -Wextra -g
SHELL := cmd.exe

# Source files
SRC = test.c
OBJ = $(SRC:.c=.o)

# Output executable
TARGET = test

# Default rule
all: $(TARGET)

# Linking
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Compiling source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean compiled files
# Below is for Windows PWSH because PWSH sucks
clean:
	del -rf $(OBJ) $(TARGET).exe

# Rebuild from scratch
rebuild: clean all
