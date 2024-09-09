NAME = winkey.exe
CC = cl
#CFLAGS = /Wall /WX /Iinc
CFLAGS = /Wall /Iinc
LDFLAGS = user32.lib kernel32.lib
SRCS = src/main.c src/log.c
OBJS = $(SRCS:src/%.c=obj/%.obj)

all: obj $(NAME)

$(NAME): $(OBJS)
        $(CC) $(CFLAGS) $(OBJS) /Fe$@ $(LDFLAGS)

obj:
        @if not exist obj mkdir obj

obj/%.obj: src/%.c | obj
        $(CC) $(CFLAGS) /c /Fo$@ $<

clean:
        del /Q obj\*.obj

fclean: clean
        del /Q $(NAME)

re: fclean all

.PHONY: all clean fclean re obj
