# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jivan-de <jivan-de@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/29 11:23:43 by jivan-de       #+#    #+#                 #
#    Updated: 2020/02/20 15:49:56 by jivan-de      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

COM_COLOR   = \033[1;31m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m
OK_STRING    = "[OK]"
ERROR_STRING = "[ERROR]"
WARN_STRING  = "[WARNING]"
COM_STRING   = "Compiling"

NAME = libft.a
FLAGS = -Wall -Werror -Wextra

SOURCES = ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_get_next_line.c \
			ft_getnumlen.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_itoa.c \
			ft_lotoa.c \
			ft_lstadd_back.c \
			ft_lstadd_front.c \
			ft_lstclear.c \
			ft_lstdelone.c \
			ft_lstiter.c \
			ft_lstlast.c \
			ft_lstmap.c \
			ft_lstnew.c \
			ft_lstsize.c \
			ft_memccpy.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_base.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			ft_split.c \
			ft_strchr.c \
			ft_strcmp.c \
			ft_strdup.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strmapi.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_uitoa.c \
			ft_uitohex.c

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	@printf "%-57b" "$(COM_COLOR)Building library: $(NO_COLOR)"
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)
	@printf "%b" "$(OK_COLOR)$(OK_STRING)\n$(NO_COLOR)"

%.o: %.c
	@$(CC) -c $(FLAGS) $< -o $@; \
        RESULT=$$?; \
        if [ $$RESULT -ne 0 ]; then \
            printf "%b %b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" \
				"$(ERROR_COLOR)$(ERROR_STRING)$(NO_COLOR)\n"; \
		else  \
            printf "%-60b %b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $(@F)" \
				"$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"; \
        fi; \
        exit $$RESULT

clean:
	@printf "%-57b" "$(COM_COLOR)Cleaning up object files: $(NO_COLOR)"
	@$(RM) $(OBJECTS) a.out
	@printf "%b" "$(OK_COLOR)$(OK_STRING)\n$(NO_COLOR)"

fclean: clean
	@printf "%-57b" "$(COM_COLOR)Cleaning up $(NAME): $(NO_COLOR)"
	@$(RM) $(NAME)
	@printf "%b" "$(OK_COLOR)$(OK_STRING)\n$(NO_COLOR)"

re: fclean all

.PHONY: all clean fclean re
