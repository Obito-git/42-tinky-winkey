NAME = winkey.exe
CC = C:\build_vs.bat
CFLAGS = /Wall /WX /Iinc
SRCS = src/main.c src/file2.c
OBJS = $(SRCS:src/%.c=obj/%.obj)

all: obj $(NAME)

$(NAME): $(OBJS)
        $(CC) $(CFLAGS) $(OBJS) /Fe$@

obj:
        @if not exist obj mkdir obj

./obj/%.obj: ./src/%.c obj
        $(CC) $(CFLAGS) /c /Fo$@ $<

clean:
        del /Q obj\*.obj

fclean: clean
        del /Q $(NAME)

re: fclean all

.PHONY: all clean fclean re obj