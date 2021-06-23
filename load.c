// Tulpan Andrei - 314CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functions.h"

//-----------------------------LOAD------------------------------------------//
// Functia citeste inputul si sare peste liniile comentate
void read_line(char *line, FILE *file)
{
	fgets(line, 128, file);
	while (line[0] == '#')
		fgets(line, 128, file);
}

// Functia salveaza informatiile imaginii
int image_info(imginfo *img, char *filename)
{
	FILE *file = fopen(filename, "r");
	if (!file)
		return 1;
	char line[128];
	read_line(line, file);
	switch (line[1]) {
	case '2':
		img->binary = 0;
		img->rgb = 0;
		break;
	case '3':
		img->binary = 0;
		img->rgb = 1;
		break;
	case '5':
		img->binary = 1;
		img->rgb = 0;
		break;
	case '6':
		img->binary = 1;
		img->rgb = 1;
		break;
	}

	read_line(line, file);
	char *aux = strtok(line, "\n ");
	img->width = atoi(aux);
	aux = strtok(NULL, "\n ");
	img->height = atoi(aux);
	read_line(line, file);
	aux = strtok(line, "\n ");
	img->max_value = atoi(aux);
	img->counter = ftell(file);

	fclose(file);
	return 0;
}

// Functia citeste imaginile grayscale si le salveaza intr-o matrice
void read_grayscale(char *filename, images *image, imginfo *img)
{
	FILE *grayscale;
	if (img->binary == 0)
		grayscale = fopen(filename, "rt");
	else
		grayscale = fopen(filename, "rb");
	// se loca matricea corespunzatoare
	image->grayscale = my_alloc(img->width, img->height);
	// se marcheaza inceputul imaginii
	fseek(grayscale, img->counter, SEEK_SET);
	// se copiaza imaginea in matrice
	for (int i = 0; i < img->height; i++) {
		for (int j = 0; j < img->width; j++) {
			if (img->binary == 0)
				fscanf(grayscale, "%hhu", &image->grayscale[i][j]);
			else
				fread(&image->grayscale[i][j], sizeof(uchar), 1, grayscale);
		}
	}
	fclose(grayscale);
}

// Functia citeste imaginile rgb si le salveaza intr-o matrice
void read_rgb(char *filename, images *image, imginfo *img)
{
	FILE *rgb;
	if (img->binary == 0)
		rgb = fopen(filename, "rt");
	else
		rgb = fopen(filename, "rb");
	// se loca matricea corespunzatoare
	image->rgb = my_alloc(3 * img->width, img->height);
	// se marcheaza inceputul imaginii
	fseek(rgb, img->counter, SEEK_SET);
	// se copiaza imaginea in matrice
	for (int i = 0; i < img->height; i++) {
		for (int j = 0; j < 3 * img->width; j++) {
			if (img->binary == 0)
				fscanf(rgb, "%hhu", &image->rgb[i][j]);
			else
				fread(&image->rgb[i][j], sizeof(uchar), 1, rgb);
		}
	}
	fclose(rgb);
}

// Functie pentru eliberarea memoriei matricelor grayscale & rgb
void free_image(images *img, imginfo *image)
{
	if (image->max_value != -1) {
		if (image->rgb == 0)
			free_matrix(img->grayscale, image->height);
		if (image->rgb == 1)
			free_matrix(img->rgb, image->height);
		image->max_value = -1;
	}
}

// Functie pentru incarcarea fisierului in program
void load(images *imgs, imginfo *image, command *cmd, coords *coord)
{
	if (cmd->counter > 1) {
		char *filename = cmd->args[1];
		free_image(imgs, image);
		int aux = image_info(image, filename);
		// Selectez intreaga imagine (SELECT ALL)
		coord->x1 = 0;
		coord->x2 = image->width;
		coord->y1 = 0;
		coord->y2 = image->height;
		if (aux == 0) {
			if (image->rgb == 0)
				read_grayscale(filename, imgs, image);
			else
				read_rgb(filename, imgs, image);
			printf("Loaded %s\n", filename);
		} else {
			printf("Failed to load %s\n", filename);
		}
	} else {
		printf("Invalid command\n");
	}
}
