CC=gcc
#CFLAGS=-g -O2 -Wall -Werror `sdl2-config --cflags`
CFLAGS=-O2 -Wall `sdl2-config --cflags`
LDLIBS=`sdl2-config --libs` -lm -lSDL2_ttf

# $@ : le nom de la cible
# $^ : les noms des dépendances
# $< : la première dépendance

% : %.c uvsqgraphics_2.o
	$(CC) $(CFLAGS) -o $@ $< uvsqgraphics_2.o $(LDLIBS)  

all: demo0 demo1 demo2 demo3 demo4 horloge
	./demo0
	./demo1
	./demo2
	./demo3
	./demo4
	./horloge

uvsqgraphics_2.o: uvsqgraphics_2.c uvsqgraphics_2.h uvsqcouleur_2.h 

	$(CC) $(CFLAGS) -c uvsqgraphics_2.c -o uvsqgraphics_2.o


.PHONY: clean
clean:
	rm -f uvsqgraphics_2.o
	rm -f *.o
	rm -f demo0
	rm -f demo1
	rm -f demo2
	rm -f demo3
	rm -f demo4
	rm -f horloge
	rm -f morpion


.PHONY: installmac
installmac:
	/bin/bash -c `curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh`
	brew install sdl2
	brew install sdl2_ttf


.PHONY: install
install:
	sudo apt install libsdl2-dev
	sudo apt install libsdl2-ttf


.PHONY: zip
ZIPNAME=IN304_Projet
zip:
	rm -rf ${ZIPNAME}
	mkdir ${ZIPNAME}
	cp demo*.c ${ZIPNAME}
	cp horloge.c ${ZIPNAME}
	cp uvsqgraphics_2.c ${ZIPNAME}
	cp *.h ${ZIPNAME}
	cp doc_uvsqgraphics_SDL2.pdf ${ZIPNAME}
	cp Makefile ${ZIPNAME}
	cp -r POL ${ZIPNAME}
	zip -r ${ZIPNAME}.zip ${ZIPNAME}
#	rm -rf ${ZIPNAME}
	ls -l
