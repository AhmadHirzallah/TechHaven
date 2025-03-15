# **************************************************************************** #
#                                                                              #
#                            Pipex Project Makefile                            #
#                                                                              #
# **************************************************************************** #

CC          := cc
CFLAGS      := -Wall -Wextra -Werror -g -I../include
# CFLAGS      := -g -I../include
# CFLAGS      := -g -I../include
LDFLAGS     := -L../libs -lft -lftprintf -lds -lgnl

# Directories
SRCDIR      := ./mandatory
OBJDIR      := ../objs/srcs/mandatory

# List source files manually (update the list below as you add more files)
# SRCS        :=	main.c \
# 				init_pipex.c \
# 				termination.c \
# 				utils.c \
# 				path_helpers.c \
# 				io_files_handler.c \
# 				execution.c \
# 				execution_utils.c

SRCS        :=	cmds_args.c	initialization.c  perform_cmds.c		pipe.c		termination.c\
				files.c		main.c		perform_cmds_utils.c		utils.c		free_all.c

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

$(OBJDIR)/initialize_pipex.o: $(SRCDIR)/initialize_pipex.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $(SRCDIR)/initialize_pipex.c -o $(OBJDIR)/initialize_pipex.o

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
