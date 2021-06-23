// Tulpan Andrei - 314CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functions.h"

//----------------------------ROTATE-----------------------------------------//
// Functie pentru rotirea imaginilor grayscale
void rotate_grayscale(coords *coord, images *img)
{
	// aloc o copie pentru dimensiunea selectata
	int counter = (coord->y2 - coord->y1);
	uchar **copy = my_alloc(counter, counter);
	// copiez elementele selectate
	int a = 0;
	int b = 0;
	for (int i = coord->y1; i < coord->y2; i++) {
		for (int j = coord->x1; j < coord->x2; j++) {
			copy[a][b] = img->grayscale[i][j];
			b++;
		}
		b = 0;
		a++;
	}
	// rotesc elementele si le copiez inapoi
	a = 0;
	b = counter - 1;
	for (int i = coord->y1; i < coord->y2; i++) {
		for (int j = coord->x1; j < coord->x2; j++) {
			img->grayscale[i][j] = copy[a][b];
			a++;
		}
		a = 0;
		b--;
	}
	free_matrix(copy, counter); // eliberez memoria alocata copiei
}

// Functie pentru rotirea imaginilor rgb
void rotate_rgb(coords *coord, images *img)
{
	// aloc o copie pentru dimensiunea selectata
	int counter = (coord->y2 - coord->y1);
	uchar **copy = my_alloc(3 * counter, counter);
	// copiez elementele selectate
	int a = 0;
	int b = 0;
	for (int i = coord->y1; i < coord->y2; i++) {
		for (int j = coord->x1; j < coord->x2; j++) {
			copy[a][3 * b] = img->rgb[i][3 * j];
			copy[a][3 * b + 1] = img->rgb[i][3 * j + 1];
			copy[a][3 * b + 2] = img->rgb[i][3 * j + 2];
			b++;
		}
		b = 0;
		a++;
	}
	// rotesc elementele si le copiez inapoi
	int cnt = counter;
	a = 0;
	b = 3 * (cnt - 1);
	for (int i = coord->y1; i < coord->y2; i++) {
		for (int j = coord->x1; j < coord->x2; j++) {
			img->rgb[i][3 * j] = copy[a][b];
			img->rgb[i][3 * j + 1] = copy[a][b + 1];
			img->rgb[i][3 * j + 2] = copy[a][b + 2];
			a++;
		}
		a = 0;
		cnt--;
		b = 3 * (cnt - 1);
	}
	free_matrix(copy, counter); // eliberez memoria alocata copiei
}

// Functie pentru rotirea totala a imaginilor rgb
void rotate_all_rgb(imginfo *image, coords *coord, images *img)
{
	// aloc o copie pentru dimensiunea selectata
	uchar **copy = my_alloc(3 * coord->x2, coord->y2);
	// copiez elementele selectate
	int a = 0;
	int b = 0;
	for (int i = coord->y1; i < coord->y2; i++) {
		for (int j = coord->x1; j < coord->x2; j++) {
			copy[a][3 * b] = img->rgb[i][3 * j];
			copy[a][3 * b + 1] = img->rgb[i][3 * j + 1];
			copy[a][3 * b + 2] = img->rgb[i][3 * j + 2];
			b++;
		}
		b = 0;
		a++;
	}
	free_matrix(img->rgb, image->height); // eliberez matricea imaginii
	img->rgb = my_alloc(3 * coord->y2, coord->x2); // aloc o noua matrice
	// rotesc elementele si le copiez inapoi
	a = 0;
	int counter = coord->x2;
	b = 3 * (counter - 1);
	for (int i = coord->x1; i < coord->x2; i++) {
		for (int j = coord->y1; j < coord->y2; j++) {
			img->rgb[i][3 * j] = copy[a][b];
			img->rgb[i][3 * j + 1] = copy[a][b + 1];
			img->rgb[i][3 * j + 2] = copy[a][b + 2];
			a++;
		}
		a = 0;
		counter--;
		b = 3 * (counter - 1);
	}
	free_matrix(copy, coord->y2); // eliberez copia
	// schimb dimensiunile intre ele
	int aux = coord->y2;
	coord->y2 = coord->x2;
	coord->x2 = aux;
	image->width = coord->x2;
	image->height = coord->y2;
}

// Functie pentru rotirea totala a imaginilor grayscale
void rotate_all_grayscale(imginfo *image, coords *coord, images *img)
{
	// aloc o copie pentru dimensiunea selectata
	uchar **copy = my_alloc(coord->x2, coord->y2);
	// copiez elementele selectate
	int a = 0;
	int b = 0;
	for (int i = coord->y1; i < coord->y2; i++) {
		for (int j = coord->x1; j < coord->x2; j++) {
			copy[a][b] = img->grayscale[i][j];
			b++;
		}
		b = 0;
		a++;
	}
	free_matrix(img->grayscale, image->height); // eliberez matricea imaginii
	img->grayscale = my_alloc(coord->y2, coord->x2); // aloc o noua matrice
	// rotesc elementele si le copiez inapoi
	a = 0;
	b = coord->x2 - 1;
	for (int i = coord->x1; i < coord->x2; i++) {
		for (int j = coord->y1; j < coord->y2; j++) {
			img->grayscale[i][j] = copy[a][b];
			a++;
		}
		a = 0;
		b--;
	}
	free_matrix(copy, coord->y2); // eliberez copia
	// schimb dimensiunile intre ele
	int aux = coord->y2;
	coord->y2 = coord->x2;
	coord->x2 = aux;
	image->width = coord->x2;
	image->height = coord->y2;
}

// Functie pentru rotirea imaginii in functie de valoarea unghiului
void rotate_val(imginfo *image, coords *coord, images *img, command *cmd)
{
	if (!strcmp(cmd->args[1], "-90")) {
		if (image->rgb == 0)
			rotate_grayscale(coord, img);
		else
			rotate_rgb(coord, img);
		printf("Rotated %s\n", cmd->args[1]);
	} else if (!strcmp(cmd->args[1], "270")) {
		if (image->rgb == 0)
			rotate_grayscale(coord, img);
		else
			rotate_rgb(coord, img);
		printf("Rotated %s\n", cmd->args[1]);
	} else if (!strcmp(cmd->args[1], "90")) {
		if (image->rgb == 0) {
			rotate_grayscale(coord, img);
			rotate_grayscale(coord, img);
			rotate_grayscale(coord, img);
		} else {
			rotate_rgb(coord, img);
			rotate_rgb(coord, img);
			rotate_rgb(coord, img);
		}
		printf("Rotated %s\n", cmd->args[1]);
	} else if (!strcmp(cmd->args[1], "-270")) {
		if (image->rgb == 0) {
			rotate_grayscale(coord, img);
			rotate_grayscale(coord, img);
			rotate_grayscale(coord, img);
		} else {
			rotate_rgb(coord, img);
			rotate_rgb(coord, img);
			rotate_rgb(coord, img);
		}
		printf("Rotated %s\n", cmd->args[1]);
	} else if  (!strcmp(cmd->args[1], "180")) {
		if (image->rgb == 0) {
			rotate_grayscale(coord, img);
			rotate_grayscale(coord, img);
		} else {
			rotate_rgb(coord, img);
			rotate_rgb(coord, img);
		}
		printf("Rotated %s\n", cmd->args[1]);
	} else if (!strcmp(cmd->args[1], "-180")) {
		if (image->rgb == 0) {
			rotate_grayscale(coord, img);
			rotate_grayscale(coord, img);
		} else {
			rotate_rgb(coord, img);
			rotate_rgb(coord, img);
		}
		printf("Rotated %s\n", cmd->args[1]);
	} else if (!strcmp(cmd->args[1], "360")) {
		printf("Rotated %s\n", cmd->args[1]);
	} else if (!strcmp(cmd->args[1], "-360")) {
		printf("Rotated %s\n", cmd->args[1]);
	} else if (!strcmp(cmd->args[1], "0")) {
		printf("Rotated %s\n", cmd->args[1]);
	} else {
		printf("Unsupported rotation angle\n");
	}
}

// Functie pentru rotirea intregii imagini in functie de valoarea unghiului
void rotate_all_val(imginfo *image, coords *coord, images *img, command *cmd)
{
	if (!strcmp(cmd->args[1], "-90")) {
		if (image->rgb == 0)
			rotate_all_grayscale(image, coord, img);
		else
			rotate_all_rgb(image, coord, img);
		printf("Rotated %s\n", cmd->args[1]);
	} else if (!strcmp(cmd->args[1], "270")) {
		if (image->rgb == 0)
			rotate_all_grayscale(image, coord, img);
		else
			rotate_all_rgb(image, coord, img);
		printf("Rotated %s\n", cmd->args[1]);
	} else if (!strcmp(cmd->args[1], "90")) {
		if (image->rgb == 0) {
			rotate_all_grayscale(image, coord, img);
			rotate_all_grayscale(image, coord, img);
			rotate_all_grayscale(image, coord, img);
		} else {
			rotate_all_rgb(image, coord, img);
			rotate_all_rgb(image, coord, img);
			rotate_all_rgb(image, coord, img);
		}
		printf("Rotated %s\n", cmd->args[1]);
	} else if (!strcmp(cmd->args[1], "-270")) {
		if (image->rgb == 0) {
			rotate_all_grayscale(image, coord, img);
			rotate_all_grayscale(image, coord, img);
			rotate_all_grayscale(image, coord, img);
		} else {
			rotate_all_rgb(image, coord, img);
			rotate_all_rgb(image, coord, img);
			rotate_all_rgb(image, coord, img);
		}
		printf("Rotated %s\n", cmd->args[1]);
	} else if (!strcmp(cmd->args[1], "180")) {
		if (image->rgb == 0) {
			rotate_all_grayscale(image, coord, img);
			rotate_all_grayscale(image, coord, img);
		} else {
			rotate_all_rgb(image, coord, img);
			rotate_all_rgb(image, coord, img);
		}
		printf("Rotated %s\n", cmd->args[1]);
	} else if (!strcmp(cmd->args[1], "-180")) {
		if (image->rgb == 0) {
			rotate_all_grayscale(image, coord, img);
			rotate_all_grayscale(image, coord, img);
		} else {
			rotate_all_rgb(image, coord, img);
			rotate_all_rgb(image, coord, img);
		}
		printf("Rotated %s\n", cmd->args[1]);
	} else if (!strcmp(cmd->args[1], "360")) {
		printf("Rotated %s\n", cmd->args[1]);
	} else if (!strcmp(cmd->args[1], "-360")) {
		printf("Rotated %s\n", cmd->args[1]);
	} else if (!strcmp(cmd->args[1], "0")) {
		printf("Rotated %s\n", cmd->args[1]);
	} else {
		printf("Unsupported rotation angle\n");
	}
}

// Functie pentru comanda ROTATE
void rotate(imginfo *image, coords *coord, images *img, command *cmd)
{
	if (image->max_value == -1) { // verific daca am o imagine incarcata
		printf("No image loaded\n");
		return;
	}
	// verific daca execut select all sau select pe o matrice patratica
	if ((coord->x2 - coord->x1) == (coord->y2 - coord->y1)) {
		if (cmd->counter > 1)
			rotate_val(image, coord, img, cmd);
		else
			printf("Invalid command\n");
	} else if ((coord->x2 == image->width) && (coord->y2 == image->height)) {
		if (cmd->counter > 1)
			rotate_all_val(image, coord, img, cmd);
		else
			printf("Invalid command\n");
	} else {
		printf("The selection must be square\n");
	}
}
