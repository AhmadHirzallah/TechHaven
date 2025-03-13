# **************************************************************************** #
#                                LIBFT Makefile                                #
# **************************************************************************** #

# === Directories (relative to this Makefile's location) ===
LIBFT_DIR    := .
OBJS_DIR     := ../objs
LIBS_DIR     := ../libs
INCLUDE_DIR  := ../include

# === Final Archive Target (placed in the project root's libs/) ===
NAME         := $(LIBS_DIR)/libft.a

# === Compiler Settings ===
CC           := cc
CFLAGS       := -Wall -Wextra -Werror -g
ARCHIVING           := ar rcs

# === Color Definitions for Messages ===
RESET        := \033[0;39m
RED          := \033[0;91m
GREEN        := \033[0;92m
MAGENTA      := \033[0;95m
YELLOW       := \033[0;93m

# === Base Filenames (without extensions) ===

# I/O Functions (located in libft/io/)
FILES_IO   := ft_putchar_fd ft_putendl_fd ft_putnbr_fd ft_putstr_fd

# Memory Functions (located in libft/mem/)
FILES_MEM  := ft_bzero ft_calloc ft_memchr ft_memcmp ft_memcpy ft_memmove ft_memset

# String Functions (located in libft/str/)
FILES_STR  := ft_atoi ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint \
              ft_itoa ft_split ft_strchr ft_strdup ft_striteri ft_strjoin ft_strlcat \
              ft_strlcpy ft_strlen ft_strmapi ft_strncmp ft_strnstr ft_strrchr \
              ft_strtrim ft_substr ft_tolower ft_toupper split_multi ft_atol \
              is_str_space str_tok_sttc str_nullify_delimiters ft_atoint128 nbr_to_str \
			  str_cmpr free_2d_arr print_2d_arr

FILES_DATA_TYPES := data_types

# === Construct Source File Paths using addprefix & addsuffix ===
SRCS_IO   := $(addprefix $(LIBFT_DIR)/io/, $(addsuffix .c, $(FILES_IO)))
SRCS_MEM  := $(addprefix $(LIBFT_DIR)/mem/, $(addsuffix .c, $(FILES_MEM)))
SRCS_STR  := $(addprefix $(LIBFT_DIR)/str/, $(addsuffix .c, $(FILES_STR)))
SRCS_DATA_TYPES  := $(addprefix $(LIBFT_DIR)/data_types/, $(addsuffix .c, $(FILES_DATA_TYPES)))

# All source files (for reference)
SRCS      := $(SRCS_IO) $(SRCS_MEM) $(SRCS_STR)

# === Construct Object File Paths ===
OBJS_IO   := $(patsubst $(LIBFT_DIR)/io/%.c, $(OBJS_DIR)/io/%.o, $(SRCS_IO))
OBJS_MEM  := $(patsubst $(LIBFT_DIR)/mem/%.c, $(OBJS_DIR)/mem/%.o, $(SRCS_MEM))
OBJS_STR  := $(patsubst $(LIBFT_DIR)/str/%.c, $(OBJS_DIR)/str/%.o, $(SRCS_STR))
OBJS_DATA_TYPES  := $(patsubst $(LIBFT_DIR)/data_types/%.c, $(OBJS_DIR)/data_types/%.o, $(SRCS_DATA_TYPES))

OBJS      := $(OBJS_IO) $(OBJS_MEM) $(OBJS_STR) $(OBJS_DATA_TYPES)


bonus: all

all: $(NAME)

$(NAME): $(OBJS)
	@mkdir -p $(LIBS_DIR)
	@echo "$(MAGENTA)Creating/Updating archive $(NAME)$(RESET)"
	$(ARCHIVING) $(NAME) $(OBJS)
	@echo "$(MAGENTA)Archive updated: $(NAME)$(RESET)"

# --- Pattern Rule: I/O Sources ---
$(OBJS_DIR)/io/%.o: $(LIBFT_DIR)/io/%.c
	@mkdir -p $(dir $@)
	@echo "$(GREEN)Compiling I/O: $< $(RESET)"
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# --- Pattern Rule: Memory Sources ---
$(OBJS_DIR)/mem/%.o: $(LIBFT_DIR)/mem/%.c
	@mkdir -p $(dir $@)
	@echo "$(GREEN)Compiling MEM: $< $(RESET)"
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# --- Pattern Rule: String Sources ---
$(OBJS_DIR)/str/%.o: $(LIBFT_DIR)/str/%.c
	@mkdir -p $(dir $@)
	@echo "$(GREEN)Compiling STR: $< $(RESET)"
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(OBJS_DIR)/data_types/%.o: $(LIBFT_DIR)/data_types/%.c
	@mkdir -p $(dir $@)
	@echo "$(GREEN)Compiling Data Types: $< $(RESET)"
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	@echo "$(YELLOW)Cleaning objects in $(OBJS_DIR)...$(RESET)"
	@rm -rf $(OBJS_DIR)

fclean: clean
	@echo "$(YELLOW)Removing archive $(NAME)...$(RESET)"
	@rm -f $(NAME)

re: fclean all


.PHONY: all clean fclean re bonus