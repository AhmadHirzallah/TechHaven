# **************************************************************************** #
#                                                                              #
#                            Pipex Project Makefile                            #
#                                                                              #
# **************************************************************************** #

CC          := cc
CFLAGS      := -Wall -Wextra -Werror -g -I../include
LDFLAGS     := -L../libs -lft -lftprintf -lds -lgnl
LDFLAGS_BONUS := -L../libs -lftprintf -lft -lds -lgnl

SRCDIR            := ./mandatory
SRC_BONUS_DIR     := ./bonus
OBJDIR            := ../objs/srcs/mandatory
OBJDIR_BONUS      := ../objs/srcs/bonus

SRCS := \
	close_all.c \
	cmds_args.c \
	files.c \
	free_all.c \
	initialization.c \
	main.c \
	perform_cmds.c \
	perform_cmds_utils.c \
	pipe.c \
	termination.c \
	utils.c

SRCS_BONUS := \
	close_all_bonus.c \
	cmds_args_bonus.c \
	files_bonus.c \
	free_all_bonus.c \
	initialization_bonus.c \
	main_bonus.c \
	perform_cmds_bonus.c \
	perform_cmds_utils_bonus.c \
	pipe_bonus.c \
	termination_bonus.c \
	utils_bonus.c

OBJS        := $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
OBJS_BONUS  := $(addprefix $(OBJDIR_BONUS)/, $(SRCS_BONUS:.c=.o))

TARGET       := ../pipex
BONUS_TARGET := ../pipex_bonus

all: $(TARGET)

bonus: $(BONUS_TARGET)

$(TARGET): $(OBJS)
	@$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@
	@echo "Executable $(TARGET) built successfully."

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BONUS_TARGET): $(OBJS_BONUS)
	@$(CC) $(CFLAGS) $^ $(LDFLAGS_BONUS) -o $@
	@echo "Executable $(BONUS_TARGET) built successfully."

$(OBJDIR_BONUS)/%.o: $(SRC_BONUS_DIR)/%.c | $(OBJDIR_BONUS)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR_BONUS):
	mkdir -p $(OBJDIR_BONUS)

clean:
	@rm -f $(OBJS)
	@rm -f $(OBJS_BONUS)
	@echo "Object files cleaned."

fclean: clean
	@rm -f $(TARGET)
	@rm -f $(BONUS_TARGET)
	@echo "Executables cleaned."

re: fclean all

re_bonus: fclean bonus

.PHONY: all bonus clean fclean re re_bonus
