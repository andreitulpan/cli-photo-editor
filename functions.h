// Tulpan Andrei - 314CA
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef unsigned char uchar;

// structura in care se stocheaza informatiile imaginilor
typedef struct {
	int width, height, binary, rgb, max_value;
	long counter;
} imginfo;

// structura in care se stocheaza argumentele comenzilor
typedef struct {
	char **args;
	int counter;
} command;

// structura in care se stocheaza imaginile
typedef struct {
	unsigned char **grayscale;
	unsigned char **rgb;
} images;

// structura in care se salveaza selectiile
typedef struct {
	int x1, x2;
	int y1, y2;
} coords;

//------------------------------FUNCTIONS------------------------------------//
unsigned char **my_alloc(int width, int height);

void read_line(char *line, FILE *file);

int my_round(double arg);

int image_info(imginfo *img, char *filename);

void read_grayscale(char *filename, images *image, imginfo *img);

void read_rgb(char *filename, images *image, imginfo *img);

void free_matrix(unsigned char **image, int height);

void free_image(images *img, imginfo *image);

void load(images *imgs, imginfo *image, command *cmd, coords *coord);

void select_coord(coords *coord, command *cmd, imginfo *image);

void select_img(coords *coord, command *cmd, imginfo *image);

void crop_grayscale(imginfo *image, coords *coord, images *img);

void crop_rgb(imginfo *image, coords *coord, images *img);

void crop(imginfo *image, coords *coord, images *img);

void rotate_rgb(coords *coord, images *img);

void rotate_grayscale(coords *coord, images *img);

void rotate_all_rgb(imginfo *image, coords *coord, images *img);

void rotate_all_grayscale(imginfo *image, coords *coord, images *img);

void rotate_val(imginfo *image, coords *coord, images *img, command *cmd);

void rotate_all_val(imginfo *image, coords *coord, images *img, command *cmd);

void rotate(imginfo *image, coords *coord, images *img, command *cmd);

void grayscale(imginfo *image, images *imgs, coords *coord);

void sepia(imginfo *image, images *imgs, coords *coord);

void information(imginfo *image, command *cmd);

void save_ascii(images *img, imginfo *image, command *cmd);

void save_binary(images *img, imginfo *image, command *cmd);

void save(images *img, imginfo *image, command *cmd);

void free_commands(command *cmd);

void commands(command *cmd, char *input);

void exit_editor(imginfo *image, images *img, command *cmd);
