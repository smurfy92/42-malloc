
LIB = srcs/libft/libft.a

SRC = srcs/malloc.c
SRC += srcs/malloc_lib.c
SRC += srcs/realloc.c
SRC += srcs/free.c
SRC += srcs/print_mem.c
SRC += srcs/print_lib.c


INC = -I ./includes/
ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = malloc.so
OBJ = $(SRC:.c=.o)
FLAG = -Wall -Werror -Wextra
CG = \033[92m
CY =  \033[93m
CE = \033[0m
CB = \033[34m

all: start $(NAME)

$(NAME): $(OBJ)
	@echo "\033[K$(CY)[MALLOC] :$(CE) $(CG)Compiling Malloc ...$(CE)";
	-@make -C srcs/libft nohd
	@gcc -shared -fsanitize=address -o $(NAME)_$(HOSTTYPE) $(FLAG) $(INC) $(SRC) $(LIB);
	@ln -sf $(NAME)_$(HOSTTYPE) "libft_malloc.so"

%.o: %.c
	@echo "\033[K$(CY)[MALLOC] :$(CE) $(CG)Compiling $<$(CE) \033[1A";
	@gcc $(FLAG) -c $< -o $@ $(INC)

start:
	@echo "\n";
	@echo "			$(CG)        :::   :::       :::     :::        :::        ::::::::   :::::::: $(CE)";
	@echo "			$(CG)      :+:+: :+:+:    :+: :+:   :+:        :+:       :+:    :+: :+:    :+: $(CE)";
	@echo "			$(CG)    +:+ +:+:+ +:+  +:+   +:+  +:+        +:+       +:+    +:+ +:+         $(CE)";
	@echo "			$(CG)   +#+  +:+  +#+ +#++:++#++: +#+        +#+       +#+    +:+ +#+          $(CE)";
	@echo "			$(CG)  +#+       +#+ +#+     +#+ +#+        +#+       +#+    +#+ +#+           $(CE)";
	@echo "			$(CG) #+#       #+# #+#     #+# #+#        #+#       #+#    #+# #+#    #+#     $(CE)";
	@echo "			$(CG)###       ### ###     ### ########## ########## ########   ########       $(CE)";
	@echo "\n";

clean: start
	@echo "\033[K$(CY)[MALLOC] :$(CE) $(CG)Cleaning Malloc objects$(CE)\033[1A";
	@/bin/rm -rf $(OBJ);
	-@make -C srcs/libft nohdclean;

fclean: start clean
	@echo "\033[K$(CY)[MALLOC] :$(CE) $(CG)Cleaning 42sh ...$(CE)\033[1A";
	@/bin/rm -f $(NAME)_$(HOSTTYPE) "libft_malloc.so";
	-@make -C srcs/libft nohdfclean;

re: fclean all

.PHONY: all clean fclean re