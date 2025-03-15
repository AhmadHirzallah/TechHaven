SUBDIRS := libft	libft/io/ft_printf	libft/io/get_next_line  libft/DS 

define make_all_modules
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir $(1); \
	done
endef

all:
	@$(call make_all_modules, all)
	@$(MAKE) -C srcs

bonus:
	@$(call make_all_modules, bonus)
	@$(MAKE) -C srcs bonus

clean:
	@$(call make_all_modules, clean)
	@$(MAKE) -C srcs clean

fclean:
	@$(call make_all_modules, fclean)
	@$(MAKE) -C srcs fclean

re:
	@$(call make_all_modules, re)
	@$(MAKE) -C srcs re


.PHONY: re fclean clean bonus all