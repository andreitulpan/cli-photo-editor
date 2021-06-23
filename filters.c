// Tulpan Andrei - 314CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functions.h"

//---------------------------GRAYSCALE---------------------------------------//
// Functie pentru comanda GRAYSCALE
void grayscale(imginfo *image, images *imgs, coords *coord)
{
	if (image->max_value == -1) { // verific daca am imagine incarcata
		printf("No image loaded\n");
		return;
	}
	if (image->rgb == 1)  { // verific daca imaginea este rgb
	// Execut calculele pentru modificarea pixelilor
		for (int i = coord->y1; i < coord->y2; i++) {
			for (int j = coord->x1; j < coord->x2; j++) {
				double aux = (double)(imgs->rgb[i][j * 3]);
				aux += (double)(imgs->rgb[i][j * 3 + 1]);
				aux += (double)(imgs->rgb[i][j * 3 + 2]);
				aux /= 3;
				imgs->rgb[i][j * 3] = my_round(aux);
				imgs->rgb[i][j * 3 + 1] = my_round(aux);
				imgs->rgb[i][j * 3 + 2] = my_round(aux);
			}
		}
		printf("Grayscale filter applied\n");
	}
	if (image->rgb == 0)
		printf("Grayscale filter not available\n");
}

//----------------------------SEPIA------------------------------------------//
// Functie pentru comanda SEPIA
void sepia(imginfo *image, images *imgs, coords *coord)
{
	if (image->max_value == -1) { // verific daca am imagine incarcata
		printf("No image loaded\n");
		return;
	}
	if (image->rgb == 1) { // verific daca imaginea este rgb
	// Execut calculele pentru modificarea pixelilor
		for (int i = coord->y1; i < coord->y2; i++) {
			for (int j = coord->x1; j < coord->x2; j++) {
				double R = (double)imgs->rgb[i][3 * j];
				double G = (double)imgs->rgb[i][3 * j + 1];
				double B = (double)imgs->rgb[i][3 * j + 2];
				int new1 = my_round(0.393 * R + 0.769 * G + 0.189 * B);
				int new2 = my_round(0.349 * R + 0.686 * G + 0.168 * B);
				int new3 = my_round(0.272 * R + 0.534 * G + 0.131 * B);
				// se verifica daca se trece de valoarea maxima
				if (new1 > image->max_value)
					new1 = image->max_value;
				if (new2 > image->max_value)
					new2 = image->max_value;
				if (new3 > image->max_value)
					new3 = image->max_value;
				imgs->rgb[i][3 * j] = new1;
				imgs->rgb[i][3 * j + 1] = new2;
				imgs->rgb[i][3 * j + 2] = new3;
			}
		}
		printf("Sepia filter applied\n");
	}
	if (image->rgb == 0)
		printf("Sepia filter not available\n");
}
