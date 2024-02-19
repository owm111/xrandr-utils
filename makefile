CFLAGS = -g -Os -std=c99 -Wall -Wextra -Wpedantic
CPPFLAGS = -D_XOPEN_SOURCE=700
LDLIBS = -lc -lX11 -lXinerama
PREFIX ?= /usr/share
BINDIR ?= $(PREFIX)/bin
MANDIR ?= $(PREFIX)/man

all: qog

clean:
	$(RM) qog

install: qog qog.1
	install -m755 -D -t $(BINDIR) qog
	install -m644 -D -t $(MANDIR)/man1 qog.1

uninstall:
	$(RM) $(BINDIR)/qog $(MANDIR)/man1/qog.1

.PHONY: all clean install uninstall
