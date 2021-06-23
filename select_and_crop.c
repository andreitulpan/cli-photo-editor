// Tulpan Andrei - 314CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functions.h"

//----------------------------SELECT-----------------------------------------//
// Functie pentru setarea coordonatelor selectiei
void select_coord(coords *coord, command *cmd, imginfo *image)
{
	if (cmd->counter > 4) { // verific daca am toate argumentele
		int a = atoi(cmd->args[1]);
		int b = atoi(cmd->args[2]);
		int c = atoi(cmd->args[3]);
		int d = atoi(cmd->args[4]);
		// verific daca coordonatele sunt numere intregi
		if (a == 0 && strcmp(cmd->args[1], "0")) {
			printf("Invalid command\n");
			return;
		}
		if (b == 0 && strcmp(cmd->args[2], "0")) {
			printf("Invalid command\n");
			return;
		}
		if (c == 0 && strcmp(cmd->args[3], "0")) {
			printf("Invalid command\n");
			return;
		}
		if (d == 0 && strcmp(cmd->args[4], "0")) {
			printf("Invalid command\n");
			return;
		}
		// schimb ordinea coordonatelor daca primele sunt mai mari
		if (a > c) {
			int aux1 = a;
			a = c;
			c = aux1;
		}
		if (b > d) {
			int aux2 = b;
			b = d;
			d = aux2;
		}
		// verific limitele si restrictiile coordonatelor
		if (a >= 0 && b >= 0 && c <= image->width && d <= image->height) {
			if (a == b && d == a) {
				printf("Invalid set of coordinates\n");
				return;
			} else if (b == c && c == d) {
				printf("Invalid set of coordinates\n");
				return;
			} else if (c == a || b == d || c <= 0 || d <= 0) {
				printf("Invalid set of coordinates\n");
				return;
			}
			// se face selectia
			coord->x1 = a;
			coord->y1 = b;
			coord->x2 = c;
			coord->y2 = d;
			printf("Selected %d %d ", coord->x1, coord->y1);
			printf("%d %d\n", coord->x2, coord->y2);
		} else {
			printf("Invalid set of coordinates\n");
		}
	} else {
		printf("Invalid command\n");
	}
}

// Functie pentru comanda SELECT
void select_img(coords *coord, command *cmd, imginfo *image)
{
	// verific daca exista o imagine incarcata
	if (image->max_value != -1) {
		if (cmd->counter > 1) {
			if (!strcmp(cmd->args[1], "ALL")) { // SELECT ALL
				coord->x1 = 0;
				coord->x2 = image->width;
				coord->y1 = 0;
				coord->y2 = image->height;
				printf("Selected ALL\n");
			} else {
				select_coord(coord, cmd, image); // SELEXT x1 y1 x2 y2
			}
		} else {
			printf("Invalid command\n");
			return;
		}
	} else {
		printf("No image loaded\n");
	}
}

//-----------------------------CROP------------------------------------------//
// Functie pentru taiarea imaginilor grayscale
void crop_grayscale(imginfo *image, coords *coord, images *img)
{
	int x = coord->x2 - coord->x1;
	int y = coord->y2 - coord->y1;
	// aloc o copie pentru dimensiunea selectata
	uchar **copy = my_alloc(x, y);
	int a = 0;
	int b = 0;
	for (int i = coord->y1; i < coord->y2; i++) {
		for (int j = coord->x1; j < coord->x2; j++) {
			copy[a][b] = img->grayscale[i][j]; // copiez elementele selectate
			b++;
		}
		b = 0;
		a++;
	}
	free_matrix(img->grayscale, image->height); // eliberez matricea imaginii
	img->grayscale = copy; // ii atribui adresa copiei
	// setez noile dimensiuni
	image->width = x;
	image->height = y;
	// select all pe noile dimensiuni
	coord->x1 = 0;
	coord->x2 = image->width;
	coord->y1 = 0;
	coord->y2 = image->height;
}

// Functie pentru taiarea imaginilor rgb
void crop_rgb(imginfo *image, coords *coord, images *img)
{
	int x = coord->x2 - coord->x1;
	int y = coord->y2 - coord->y1;
	// aloc o copie pentru dimensiunea selectata
	uchar **copy = my_alloc(3 * x, y);
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
	img->rgb = copy; // ii atribui adresa copiei
	// setez noile dimensiuni
	image->width = x;
	image->height = y;
	// select all pe noile dimensiuni
	coord->x1 = 0;
	coord->x2 = image->width;
	coord->y1 = 0;
	coord->y2 = image->height;
}

// Functia pentru comanda CROP
void crop(imginfo *image, coords *coord, images *img)
{
	if (image->max_value != -1) { // verific daca am o imagine incarcata
		if (image->rgb == 0)
			crop_grayscale(image, coord, img);
		if (image->rgb == 1)
			crop_rgb(image, coord, img);
		printf("Image cropped\n");
	} else {
		printf("No image loaded\n");
	}
}
