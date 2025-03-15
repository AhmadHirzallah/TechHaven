# ============================================================================ #
#                             FT_PRINTF Module Makefile                      #
# ============================================================================ #

# Library Output
NAME        := ../../../libs/libftprintf.a

# Directories
FT_PRINTF_ROOT := .
OBJS_DIR       := ../../../objs/ft_printf
INCLUDE_DIR    := ../../../include

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

FILES := ft_flush_buffer      ft_itoa_base_into_bfr  ft_parse_fmt \
         ft_printf            ft_render_char_to_buf   ft_render_into_buffer \
         ft_render_nbrs_to_buf  ft_render_str_to_buf    ft_set_pad_spaces_nbr_cases \
         ft_set_pad_zeros_nbr_cases

# ============================================================================ #
#                             Path Construction                                #
# ============================================================================ #

# Full source file paths (adding .c extension)
SRCS := $(addprefix $(FT_PRINTF_ROOT)/, $(addsuffix .c, $(FILES)))

# Corresponding object file paths (adding .o extension)
OBJS := $(patsubst $(FT_PRINTF_ROOT)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

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

# Generic rule for compiling ft_printf sources
$(OBJS_DIR)/%.o: $(FT_PRINTF_ROOT)/%.c
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

.PHONY: all clean fclean re bonus