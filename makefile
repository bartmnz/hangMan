
CFLAGS+= -std=c11 -Wall -Wextra -pedantic -Wno-deprecated -Werror -Wstack-usage=1024 -o

hangMan: hangMan.c
	gcc $(CFLAGS) hangMan hangMan.c
