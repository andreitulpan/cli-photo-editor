// Tulpan Andrei - 314CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functions.h"

//---------------------------ESSENTIALS--------------------------------------//
// Am creat o functie pentru alocarea dinamica a matricelor
uchar **my_alloc(int width, int height)
{
	uchar **image;
	image = malloc(height * sizeof(uchar *));
	if (!image) {
		fprintf(stderr, "Memory error\n");
		exit(-1);
	}
	for (int i = 0; i < height; i++) {
		image[i] = malloc(width * sizeof(uchar));
		if (!image[i]) {
			fprintf(stderr, "Memory error\n");
			while (--i >= 0)
				free(image[i]);
			free(image);
			exit(-1);
		}
	}
	return image;
}

// Am creat o functie pentru rotunjirea numerelor
int my_round(double number)
{
	double x = number - (int)number;
	if (x < 0.5)
		return (int)number;
	return (int)(number + 1);
}

// Functie pentru eliberarea memoriei alocata dinamic unei matrice
void free_matrix(uchar **image, int height)
{
	for (int i = 0; i < height; i++)
		free(image[i]);
	free(image);
}

//---------------------------COMMANDS----------------------------------------//
// Functie pentru elibererea fiecarei comenzi
void free_commands(command *cmd)
{
	if (cmd->counter >= 1) { // verific daca a existat o comanda anterioara
		for (int i = 0; i < cmd->counter; i++)
			free(cmd->args[i]);
		free(cmd->args);
	}
}

// Functie pentru parsarea comenzilor
void commands(command *cmd, char *input)
{
	free_commands(cmd); // eliberez vechea comanda
	cmd->args = malloc(sizeof(char *));
	if (!cmd->args) {
		fprintf(stderr, "malloc() failed");
		exit(-1);
	}
	char *aux;
	cmd->counter = 1;
	aux = strtok(input, "\n ");
	cmd->args[0] = strdup(aux);
	aux = strtok(NULL, "\n ");
	while (aux) {
		cmd->args = realloc(cmd->args, (1 + cmd->counter) * sizeof(char *));
		cmd->args[cmd->counter] = strdup(aux);
		cmd->counter++;
		aux = strtok(NULL, "\n ");
	}
}

//---------------------------EXIT----------------------------------------//
// Functie pentru comanda EXIT
void exit_editor(imginfo *image, images *img, command *cmd)
{
	if (image->max_value == -1) // se verifica daca exista imagine incarcata
		printf("No image loaded\n");
	free_commands(cmd);	// se eliberaza memoria alocata comenzilor
	free_image(img, image); // se elibereaza memoria alocata imaginii
	exit(0);
}
