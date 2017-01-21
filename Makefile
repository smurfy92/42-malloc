NAME = malloc.so

SRC =  srcs/main.c
SRC += srcs/malloc.c


INC = -I ./includes/

OBJ = $(SRC:.c=.o)
FLAG = -Wall -Werror -Wextra
#-fsanitize=address
CG = \033[92m
CY =  \033[93m
CE = \033[0m
CB = \033[34m

all: start $(NAME)

$(NAME): $(OBJ)
	@echo "\033[K$(CY)[MALLOC] :$(CE) $(CG)Compiling Malloc ...$(CE)";
	@gcc -shared -o $(NAME) $(FLAG) $(INC) $(SRC) $(LIB)

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
	@/bin/rm -rf $(OBJ)

fclean: start clean
	@echo "\033[K$(CY)[MALLOC] :$(CE) $(CG)Cleaning 42sh ...$(CE)\033[1A";
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re