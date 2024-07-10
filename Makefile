P_SRC				= 	src
P_D_EDIT			= 	$(P_SRC)/d_edit
P_D_EDIT_CMD		= 	$(P_D_EDIT)/cmd
P_D_EDIT_CMD_BLOCK	= 	$(P_D_EDIT_CMD)/block
P_D_EDIT_CMD_DIR	= 	$(P_D_EDIT_CMD)/dir
P_D_EDIT_CMD_INODE	= 	$(P_D_EDIT_CMD)/inode
P_TUI				= 	$(P_SRC)/tui
P_TUI_CMD			= 	$(P_TUI)/cmd
P_TUI_CMD_DIR		= 	$(P_TUI_CMD)/directory
P_TUI_CMD_FILE		= 	$(P_TUI_CMD)/file
P_TUI_DIR			= 	$(P_TUI)/directory
P_TUI_FILE			= 	$(P_TUI)/file
P_TUI_DRAW			= 	$(P_TUI)/draw

SRC					=	$(P_SRC)/main.c							\
						$(P_D_EDIT)/cache.c						\
						$(P_D_EDIT)/d_edit.c					\
						$(P_D_EDIT_CMD)/d_load.c				\
						$(P_D_EDIT_CMD_BLOCK)/block_create.c	\
						$(P_D_EDIT_CMD_BLOCK)/block_edit.c		\
						$(P_D_EDIT_CMD_BLOCK)/block_load.c		\
						$(P_D_EDIT_CMD_DIR)/dir_change.c		\
						$(P_D_EDIT_CMD_DIR)/dir_edit.c			\
						$(P_D_EDIT_CMD_DIR)/dir_load.c			\
						$(P_D_EDIT_CMD_DIR)/touch.c				\
						$(P_D_EDIT_CMD_DIR)/mkdir.c				\
						$(P_D_EDIT_CMD_DIR)/rm.c				\
						$(P_D_EDIT_CMD_DIR)/rmdir.c				\
						$(P_D_EDIT_CMD_INODE)/inode_create.c	\
						$(P_D_EDIT_CMD_INODE)/inode_edit.c		\
						$(P_D_EDIT_CMD_INODE)/inode_load.c		\
						$(P_TUI)/d_edit_tui.c					\
						$(P_TUI_CMD)/get_cmd.c					\
						$(P_TUI_CMD_DIR)/fopen_cmd.c			\
						$(P_TUI_CMD_DIR)/dir_move_cmd.c			\
						$(P_TUI_CMD_FILE)/file_edit.c			\
						$(P_TUI_CMD_FILE)/file_extract.c		\
						$(P_TUI_CMD_FILE)/file_move_cmd.c		\
						$(P_TUI_DIR)/dir_cli.c					\
						$(P_TUI_DIR)/dir_tui.c					\
						$(P_TUI_DRAW)/draw.c					\
						$(P_TUI_DRAW)/dir_draw.c				\
						$(P_TUI_DRAW)/file_draw.c				\
						$(P_TUI_FILE)/file_cli.c				\
						$(P_TUI_FILE)/file_tui.c

OBJ					=	$(SRC:.c=.o)

P_LIB				=	lib
P_LIB_LIST			=	$(P_LIB)/list

CPPFLAGS			=	-I include -I $(P_LIB_LIST)/include

CFLAGS				=	-Wall -Wextra

LDFLAGS				=	-lncurses -L $(P_LIB_LIST)/ -llist

NAME				=	diskEdit

all:				$(NAME)

$(NAME):			list.a $(OBJ)
					gcc -o $(NAME) $(OBJ) $(CPPFLAGS) $(LDFLAGS)

list.a:
					make -C $(P_LIB_LIST)

clean:
					rm -rf $(OBJ)
					$(MAKE) -C $(P_LIB_LIST) clean

fclean:				clean
					rm -rf $(NAME)
					$(MAKE) -C $(P_LIB_LIST) fclean

re:					fclean all

debug: 				CFLAGS += -g
debug: 				re

.PHONY:				all clean fclean re debug list.a