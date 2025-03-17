# Set the paths for mlx and custom libraries
INCLUDE_DIR = /usr/local/include

# Compiler flags
CFLAGS = -Wall -Werror -Wextra -I$(INCLUDE_DIR) -g

# Linker flags - Use the local `libs` directory for libmlx.a
LDFLAGS = -L./libs -lmlx -lXext -lX11 -lm

# List of source files (you can specify it like `make SRCS=main.c`)
SRCS = 01_DrawPollockPainting.c  # You can add more files like `main.c` here

# Define the object files from the source files
OBJS = $(SRCS:.c=.o)

# Target to create the program
all: program

# Compile source files into object files
obj/%.o: %.c
	mkdir -p obj
	cc $(CFLAGS) -c $^ -o $@

# Link the object files into the final executable
program: $(OBJS)
	cc $(OBJS) -o program $(LDFLAGS)

# Clean object files and the program
clean:
	rm -f obj/*.o program

# Full clean (including target files)
fclean: clean
	rm -f program

# Rebuild everything
re: fclean all
