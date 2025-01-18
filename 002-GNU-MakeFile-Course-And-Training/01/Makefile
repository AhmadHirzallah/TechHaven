# This is my first makefile
all: make_dirs create_files

make_dirs:
	mkdir -p d1 d2 d3

create_files:
	touch f1.c f2.c f3.c

clear:
	-rm f3.c
	rm -rf d3

clean_all:
	rm f*.c d* -rf
