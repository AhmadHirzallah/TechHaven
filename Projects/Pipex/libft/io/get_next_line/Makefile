# ============================================================================ #
#                           GET_NEXT_LINE Module Makefile                    #
# ============================================================================ #

# Library Output
NAME        := ../../../libs/libgnl.a

# Directories
GNL_ROOT    := .
OBJS_DIR    := ../../../objs/get_next_line
INCLUDE_DIR := ../../../include

# Toolchain
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -g
ARCHIVE_CREATE := ar rcs

# Color Definitions
RESET       := \033[0m
GREEN       := \033[0;92m
MAGENTA     := \033[0;95m
YELLOW      := \033[0;93m

# ============================================================================ #
#                                File Lists                                    #
# ============================================================================ #

FILES := get_next_line get_next_line_utils

# ============================================================================ #
#                             Path Construction                                #
# ============================================================================ #

# Full source file paths (with .c extension)
SRCS := $(addprefix $(GNL_ROOT)/, $(addsuffix .c, $(FILES)))

# Corresponding object file paths (with .o extension)
OBJS := $(patsubst $(GNL_ROOT)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

# ============================================================================ #
#                                Build Rules                                   #
# ============================================================================ #

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(OBJS)
	@mkdir -p $(dir $(NAME))
	@echo "$(MAGENTA)Creating/Updating archive $(NAME)$(RESET)"
	$(ARCHIVE_CREATE) $(NAME) $(OBJS)
	@echo "$(MAGENTA)Library created: $(NAME)$(RESET)"

# Generic rule for compiling get_next_line sources
$(OBJS_DIR)/%.o: $(GNL_ROOT)/%.c
	@mkdir -p $(dir $@)
	@echo "$(GREEN)Compiling: $< $(RESET)"
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	@echo "$(YELLOW)Cleaning objects in $(OBJS_DIR)...$(RESET)"
	@rm -rf $(OBJS_DIR)

fclean: clean
	@echo "$(YELLOW)Removing archive $(NAME)...$(RESET)"
	@rm -f $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re
