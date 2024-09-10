NAME = winkey.exe
CC = cl
CFLAGS = /Wall /Iinc
LDFLAGS = user32.lib kernel32.lib

SRC_DIR = src
OBJ_DIR = obj

SRCS = $(SRC_DIR)\main.c $(SRC_DIR)\log.c
OBJS = $(OBJ_DIR)\main.obj $(OBJ_DIR)\log.obj

all: checkdir $(NAME)

$(NAME): $(OBJS)
    $(CC) $(CFLAGS) $(OBJS) /Fe$@ $(LDFLAGS)

checkdir:
    if not exist $(OBJ_DIR) mkdir $(OBJ_DIR)

$(OBJ_DIR)\main.obj: $(SRC_DIR)\main.c
    $(CC) $(CFLAGS) /c $(SRC_DIR)\main.c /Fo$@

$(OBJ_DIR)\log.obj: $(SRC_DIR)\log.c
    $(CC) $(CFLAGS) /c $(SRC_DIR)\log.c /Fo$@

clean:
    del /Q $(OBJ_DIR)\*.obj

fclean: clean
    del /Q $(NAME)

re: fclean all

.PHONY: all clean fclean re
