# **************************************************************************** #
#                                                                              #
#                            Pipex Project Makefile                            #
#                                                                              #
# **************************************************************************** #

CC          := cc
CFLAGS      := -Wall -Wextra -Werror -g -I../include
# CFLAGS      := -g -I../include
LDFLAGS     := -L../libs -lft -lftprintf -lds

# Directories
SRCDIR      := ./mandatory
OBJDIR      := ../objs/srcs/mandatory

# List source files manually (update the list below as you add more files)
SRCS        :=	main.c \
				init_pipex.c \
				termination.c

OBJS        := $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))




# # Manually list object files corresponding to each source file
# OBJS        := $(OBJDIR)/main.o  $(OBJDIR)/init_pipex.o




# Final executable (placed in the parent directory)
TARGET      := ../pipex




all: $(TARGET)




$(TARGET): $(OBJS)
	@$(CC) $(CFLAGS) $(^) $(LDFLAGS) -o $(@)
	@echo "Executable $(@) built successfully."

# Rule to compile each source file into an object file
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# $(OBJDIR)/main.o: $(SRCDIR)/main.c | $(OBJDIR)
# 	@$(CC) $(CFLAGS) -c $(SRCDIR)/main.c -o $(OBJDIR)/main.o

# $(OBJDIR)/ft_get_path_var.o: $(SRCDIR)/get_path_var.c | $(OBJDIR)
# 	@$(CC) $(CFLAGS) -c $(SRCDIR)/ft_get_path_var.c -o $(OBJDIR)/ft_get_path_var.o

$(OBJDIR)/init_pipex_managing.o: $(SRCDIR)/init_pipex_managing.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $(SRCDIR)/init_pipex_managing.c -o $(OBJDIR)/init_pipex_managing.o

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	@rm -rf $(OBJS)
	@echo "Object files cleaned."

fclean: clean
	@rm -rf $(TARGET)
	@echo "Executable cleaned."

re: fclean all

.PHONY: all clean fclean re bonus
