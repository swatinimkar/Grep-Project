CC=gcc
OBJECTS=project.o \
        functions.o \
        commands.o
        
CFLAGS=-O3 -Wall 

project: $(OBJECTS) 
	$(CC) $(CFLAGS) $(OBJECTS) -o project

install:
	mkdir -p $(DESTDIR)/usr/bin
	cp project $(DESTDIR)/usr/bin/project

uninstall:
	rm $(DESTDIR)/usr/bin/project

clean:
	-rm -rf project core *.o tags
