P_SRC			= 	src

SRC				=	$(P_SRC)/linked_list_append.c	\
					$(P_SRC)/linked_list_clear.c	\
					$(P_SRC)/linked_list_concat.c	\
					$(P_SRC)/linked_list_get.c		\
					$(P_SRC)/linked_list_insert.c	\
					$(P_SRC)/linked_list_new.c		\
					$(P_SRC)/linked_list_map.c		\
					$(P_SRC)/linked_list_map_arg.c	\
					$(P_SRC)/linked_list_pop.c		\
					$(P_SRC)/linked_list_push.c		\
					$(P_SRC)/linked_list_remove.c	\
					$(P_SRC)/linked_list_rotate.c	\
					$(P_SRC)/linked_list_size.c		\
					$(P_SRC)/linked_list_split.c

OBJ				=	$(SRC:.c=.o)

CPPFLAGS		=	-I./include

CFLAGS			=	-Wall -Wextra

NAME			=	liblist.a

all:			$(NAME)

$(NAME):		$(OBJ)
				ar rc $(NAME) $(OBJ)

clean:
				rm -rf $(OBJ)

fclean:			clean
				rm -rf $(NAME)

re:				fclean all

.PHONY:			all clean fclean re