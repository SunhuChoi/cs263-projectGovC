# Compiler
CC = clang
CFLAGS = -Wall -Wextra -g

# Sorting files (inside sorting/)
SORTING_DIR = sorting
SORTING_SRC = $(wildcard $(SORTING_DIR)/*.c)
SORTING_OBJ = $(SORTING_SRC:.c=.o)
SORTING_EXECS = $(SORTING_SRC:.c=)

# Default rule: Compile all sorting algorithms
all: $(SORTING_EXECS)

# Compile each sorting algorithm into an executable
$(SORTING_DIR)/%: $(SORTING_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

# Clean compiled files
clean:
	rm -f $(SORTING_EXECS)

# Rebuild everything
rebuild: clean all