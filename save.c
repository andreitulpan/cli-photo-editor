// Tulpan Andrei - 314CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functions.h"

//-----------------------------SAVE------------------------------------------//
void information(imginfo *image, command *cmd)
{
	int type, ascii;
	FILE *info = fopen(cmd->args[1], "w");
	ascii = 0; // default se salveaza binar
	if (cmd->counter > 2) {
		// verific daca primesc parametrul ascii
		if (!strcmp(cmd->args[2], "ascii"))
			ascii = 1;
		else
			ascii = 0;
	}
	if (ascii == 1) {
		if (image->rgb == 0)
			type = 2; // ascii & grayscale
		else
			type = 3; // ascii & rgb
	} else {
		if (image->rgb == 0)
			type = 5;	// binar & grayscale
		else
			type = 6;	// binar & rgb
	}
	// Printez in fisier datele imaginii
	fprintf(info, "P%d\n", type);
	fprintf(info, "%d %d\n", image->width, image->height);
	fprintf(info, "%d\n", image->max_value);
	fclose(info);
}

// Functie pentru salvarea in format ascii
void save_ascii(images *img, imginfo *image, command *cmd)
{
	information(image, cmd); // aduc informatiile
	char *filename = cmd->args[1];
	FILE *out_text = fopen(filename, "at");
	if (!out_text) {
		fprintf(stderr, "Cannot open %s file", filename);
		exit(-1);
	}
	// Printez matricea imaginii in continuarea informatiilor
	for (int i = 0; i < image->height; i++) {
		for (int j = 0; j < image->width; j++) {
			if (image->rgb == 0) {
				fprintf(out_text, "%d ", img->grayscale[i][j]);
			} else {
				fprintf(out_text, "%d ", img->rgb[i][3 * j]);
				fprintf(out_text, "%d ", img->rgb[i][3 * j + 1]);
				fprintf(out_text, "%d ", img->rgb[i][3 * j + 2]);
			}
		}
		fprintf(out_text, "\n");
	}
	printf("Saved %s\n", filename);
	fclose(out_text);
}

// Functie pentru salvarea in format binar
void save_binary(images *img, imginfo *image, command *cmd)
{
	information(image, cmd); // aduc informatiile
	char *filename = cmd->args[1];
	FILE *out_binary = fopen(filename, "ab");
	if (!out_binary) {
		fprintf(stderr, "Cannot open %s file", filename);
		exit(-1);
	}
	// Printez matricea imaginii in continuarea informatiilor
	for (int i = 0; i < image->height; i++) {
		for (int j = 0; j < image->width; j++) {
			if (image->rgb == 0)
				fwrite((&img->grayscale[i][j]), sizeof(uchar), 1, out_binary);
			else
				fwrite((&img->rgb[i][3 * j]), sizeof(uchar), 3, out_binary);
		}
	}
	printf("Saved %s\n", filename);
	fclose(out_binary);
}

// Functie pentru comanda SAVE
void save(images *img, imginfo *image, command *cmd)
{
	if (image->max_value != -1) { // verific daca am imagine incarcata
		if (cmd->counter > 1) {
			if (cmd->counter < 3) {
				save_binary(img, image, cmd); // salvez in format binar
			} else {
				if (strcmp(cmd->args[2], "ascii") == 0)
					save_ascii(img, image, cmd); // salvez in format ascii
				else
					save_binary(img, image, cmd); // salvez in format binar
			}
		} else {
			printf("Invalid command\n");
		}
	} else {
		printf("No image loaded\n");
	}
}
