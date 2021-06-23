# Tulpan Andrei - 314CA
CC=gcc
CFLAGS=-Wall -Wextra

FUNCTIONS = essentials.c select_and_crop.c filters.c load.c rotate.c save.c
TARGETS=main

build: $(TARGETS)

main: image_editor.c
	$(CC) $(CFLAGS) -o image_editor image_editor.c $(FUNCTIONS)

pack:
	zip -FSr 314CA_AndreiTulpan_Tema3.zip README Makefile *.c *.h

clean:
	rm -f $(TARGETS)

.PHONY: pack clean
