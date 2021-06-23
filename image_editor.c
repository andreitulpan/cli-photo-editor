// Tulpan Andrei - 314CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functions.h"

int main(void)
{
	int true = 1;	// programul ruleaza
	images img;		// structura cu imaginile
	imginfo image;	// structura cu informatiile imaginilor
	command cmd;	// structura pentru comenzi
	coords coord;	// structura coordonatelor selectate
	cmd.counter = 0;	// se initializeaza numarul comenzilor cu 0
	image.max_value = -1;	// nu avem imagine incarcata
	char input[128];	// se stocheaza comanda curenta
	while (true) {
		fgets(input, 128, stdin);	// citim inputul
		commands(&cmd, input);	// se recunosc comenzile
		if (!strcmp(cmd.args[0], "LOAD"))
			load(&img, &image, &cmd, &coord);
		else if (!strcmp(cmd.args[0], "SAVE"))
			save(&img, &image, &cmd);
		else if (!strcmp(cmd.args[0], "SELECT"))
			select_img(&coord, &cmd, &image);
		else if (!strcmp(cmd.args[0], "CROP"))
			crop(&image, &coord, &img);
		else if (!strcmp(cmd.args[0], "SEPIA"))
			sepia(&image, &img, &coord);
		else if (!strcmp(cmd.args[0], "GRAYSCALE"))
			grayscale(&image, &img, &coord);
		else if (!strcmp(cmd.args[0], "ROTATE"))
			rotate(&image, &coord, &img, &cmd);
		else if (!strcmp(cmd.args[0], "EXIT"))
			exit_editor(&image, &img, &cmd);
		else
			printf("Invalid command\n");
	}
	return 0;
}
