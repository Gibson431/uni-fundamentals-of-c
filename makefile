#https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
#https://www.gnu.org/software/make/manual/make.html#Simple-Makefile

CC = gcc -Wall -Werror -ansi
CFLAGS = -lm

IDIR = include
LDIR = src
ODIR = obj

_DEPS = member_linked_list.h member.h date.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o member_linked_list.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_SRC = main.c member_linked_list.c
SRC = $(patsubst %,$(LDIR)/%,$(_SRC))

main: $(OBJ)
	$(CC) -o main.out $(OBJ) $(CFLAGS)

obj/main.o: $(SRC) $(DEPS)
	$(CC) -c src/main.c -o obj/main.o

obj/member_linked_list.o: $(SRC) $(DEPS)
	$(CC) -c src/member_linked_list.c -o obj/member_linked_list.o

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~ 
