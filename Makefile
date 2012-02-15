DEBUG=1
CC=gcc
CFLAGS=-Wall -pedantic
PROG=monochrome
SRCDIR=.
OBJDIR=.

SOURCES=$(wildcard $(SRCDIR)/*.c)
OBJECTS=$(addprefix $(OBJDIR)/,$(notdir $(SOURCES:.c=.o)))

ifeq ($(DEBUG),1)
	CFLAGS+=-g
endif

.PHONY: all clean

all: $(PROG)

$(PROG): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJECTS) $(PROG)