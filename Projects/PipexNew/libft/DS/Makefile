# ============================================================================ #
#                                DS Module Makefile                          #
# ============================================================================ #

# Library Output
NAME        := ../../libs/libds.a

# Directories
DS_ROOT     := .
OBJS_DIR    := ../../objs/ds
INCLUDE_DIR := ../../include

# Toolchain
CC          := cc
CFLAGS      := -Wall -Wextra -Werror -g
AR          := ar
ARFLAGS     := rcs

# Color Definitions
RESET       := \033[0m
GREEN       := \033[0;92m
MAGENTA     := \033[0;95m
YELLOW      := \033[0;93m

# ============================================================================ #
#                                File Lists                                  #
# ============================================================================ #

# DList Files
FILES_DLIST := dlist/dlist_back     dlist/dlist_clear    dlist/dlist_del_end \
				dlist/dlist_del_front dlist/dlist_del_node dlist/dlist_destroy \
				dlist/is_dlist_empty  dlist/dlist_find_node dlist/dlist_foreach_on_data \
				dlist/dlist_front     dlist/dlist_init     dlist/dlist_insert_after \
				dlist/dlist_insert_before dlist/dlist_insert_begining dlist/dlist_insert_end \
				dlist/dlist_merge     dlist/dlist_remove_node dlist/dlist_reverse \
				dlist/dlist_size

# List Files
FILES_LST   := lst/ft_lstnew_bonus        lst/ft_lstadd_front_bonus  \
				lst/ft_lstsize_bonus       lst/ft_lstlast_bonus       \
				lst/ft_lstadd_back_bonus   lst/ft_lstdelone_bonus     \
				lst/ft_lstclear_bonus      lst/ft_lstiter_bonus       \
				lst/ft_lstmap_bonus

# Stack Files
FILES_STACK := stack/is_stack_empty       stack/stack_clear      \
				stack/stack_clone          stack/stack_create     \
				stack/stack_destroy        stack/stack_iter_on_data \
				stack/stack_peek           stack/stack_pop        \
				stack/stack_push           stack/stack_size

# Circular List Files
FILES_CIRC  := circular_list/circ_list_swap_first_2 circular_list/circ_list_clear \
				circular_list/circ_list_foreach        circular_list/circ_list_front \
				circular_list/circ_list_init           circular_list/circ_list_insert_beginning \
				circular_list/circ_list_insert_end      circular_list/circ_list_is_empty \
				circular_list/circ_list_remove_node     circular_list/circ_list_size \
				circular_list/circ_lst_push_front_into_other \
				circular_list/circ_lst_rev_rotate       circular_list/circ_lst_rotate


# ============================================================================ #
#                             Path Construction                                #
# ============================================================================ #

# Build full source paths (adding .c extension)
SRC_CIRC       := $(addprefix $(DS_ROOT)/, $(addsuffix .c, $(FILES_CIRC)))
SRC_DLIST      := $(addprefix $(DS_ROOT)/, $(addsuffix .c, $(FILES_DLIST)))
SRC_LST        := $(addprefix $(DS_ROOT)/, $(addsuffix .c, $(FILES_LST)))
SRC_STACK      := $(addprefix $(DS_ROOT)/, $(addsuffix .c, $(FILES_STACK)))

# Aggregate DS sources
SRCS_DS := $(SRC_DLIST) $(SRC_LST) $(SRC_STACK) $(SRC_QUEUE) $(SRC_CIRC) $(SRC_CIRC_STACK)

# Generate corresponding object paths
OBJS_DS := $(patsubst $(DS_ROOT)/%.c, $(OBJS_DIR)/%.o, $(SRCS_DS))

# ============================================================================ #
#                                Build Rules                                 #
# ============================================================================ #

.PHONY: all clean fclean re bonus

all: $(NAME)

bonus: all


$(NAME): $(OBJS_DS)
	@mkdir -p $(dir $(NAME))
	@echo "$(MAGENTA)Creating DS library: $(NAME)$(RESET)"
	$(AR) $(ARFLAGS) $(NAME) $(OBJS_DS)
	@echo "$(MAGENTA)DS library created: $(NAME)$(RESET)"

# Generic compilation rule for DS sources
$(OBJS_DIR)/%.o: $(DS_ROOT)/%.c
	@mkdir -p $(dir $@)
	@echo "$(GREEN)Compiling DS: $< $(RESET)"
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	@echo "$(YELLOW)Cleaning DS objects...$(RESET)"
	@rm -rf $(OBJS_DIR)

fclean: clean
	@echo "$(YELLOW)Removing DS library...$(RESET)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus