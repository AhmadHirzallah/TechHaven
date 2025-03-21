# Set the paths for mlx and custom libraries
INCLUDE_DIR = /usr/local/include

# Compiler flags
CFLAGS = -Wall -Werror -Wextra -I$(INCLUDE_DIR) -g

# Linker flags - Use the local `libs` directory for libmlx.a
LDFLAGS = -L./libs -lmlx -lXext -lX11 -lm




# List of source files (you can specify it like `make SRCS=main.c`)
# SRCS = 01_DrawPollockPainting.c
# SRCS = 02_IntroductionToMinilibX.c
# SRCS = 03_mlx_hooks_masks.c
# SRCS = 04_mlx_loop_hook.c
# SRCS = 05_mlx_put_pixel.c
# SRCS =  06_mlx_buffered_put_pixel.c
# SRCS =  07_mlx_put_imgs.c
SRCS =  08_my_pixel_put_in_specific_point.c







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
