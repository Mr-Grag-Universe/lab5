CC=gcc
CFLAGS=-c -Wall -Wextra

LDFLAGS=

SRCS=main.c ReadFromTerminal.c String.c MenuCreation.c FGetLine.c KGetLine.c Generate.c PrintData.c SaveToFile.c ReadFromFile.c WorkWithData.c

OBJS=$(SRCS:.c=.o)

EXE=app

all: $(SRCS) $(EXE)

$(EXE): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -Iheaders -o $@
	rm -rf $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -Iheaders $< -o $@

clean:
	rm -rf $(OBJS) $(EXE)
