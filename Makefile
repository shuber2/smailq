PREFIX ?= /usr
# Where the script binary should go
BINPATH = $(DESTDIR)$(PREFIX)/bin
SBINPATH = $(DESTDIR)$(PREFIX)/sbin
MANPATH = $(DESTDIR)$(PREFIX)/share/man/man1
SHAREDIR = $(DESTDIR)$(PREFIX)/share/smailq
CONFFILE = $(SHAREDIR)/smailq.conf.sample

######################################################################

all: manpage

install: all
	mkdir -p $(BINPATH) $(SBINPATH) $(MANPATH) $(SHAREDIR)
	install -m 0755 smailq $(BINPATH)/smailq
	install -m 0755 mailq $(BINPATH)/mailq
	install -m 0755 sendmail $(SBINPATH)/sendmail
	install -m 0644 smailq.conf $(CONFFILE)
	install -m 0644 smailq.1 $(MANPATH)/smailq.1

manpage: smailq.1

smailq.1: smailq.docbook
	docbook2x-man $<
	#groff -t -e -mandoc -Tps smailq.1 > smailq.ps
