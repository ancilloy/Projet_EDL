#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lecture_header.h"

int IsElf(char *str) {
    if(str[0] == 0x7f && str[1] == 'E' && str[2] == 'L' && str[3] == 'F')
    	return 1;
    else
    	return 0;
}


void lectureHead(FILE *f,Header *h){
	int compteur;
	char c;

	for (compteur = 0;compteur < 4; compteur++) {
		c = fgetc(f);
		h->Magic[compteur] = c;
	}

	if (IsElf(h->Magic) == 1) {
		c =fgetc(f);
		h->Class = c;

		c =fgetc(f);
		h->Data = c;

		c =fgetc(f);
		h->Version = c;

		for (compteur = 0;compteur <= 9; compteur++) {
			c = fgetc(f);
			h->Pad[compteur] = c;
		}
	}

	else {
		printf("ERREUR ! Fichier non ELF\n");
		exit(1);
	}
}


int print_header(Header *h) {

    printf("ELF Header: \n");
    printf("Magic: ");
        for(int i = 0 ; i < 4 ; i++) {
        	printf("%02x ",h->Magic[i]);
        }
        
    printf("\n");
    printf("Class: %02x \n",h->Class); //Faire des switch case pour chaque print avec les resultats possibles comme fait dans l'ancien code.
    printf("Data: %02x \n",h->Data); //Faire des switch case pour chaque print avec les resultats possibles comme fait dans l'ancien code.
    printf("Version: %02x \n",h->Version); //Faire des switch case pour chaque print avec les resultats possibles comme fait dans l'ancien code.
    printf("Pad: ");
        for(int i = 0 ; i < 9 ; i++) {
            printf("%02x ",h->Pad[i]);
        }
    printf("\n");
    // printf("OS/ABI: %s \n",h->OS_ABI);
    // printf("ABI Version: %s \n",h->ABI_V);
    // printf("Type: %s \n",h->Type);
    // printf("Machine: %s \n",h->Machine);
    // printf("Version: %s \n",h->Version_Machine);
    // printf("Entry point address: %s \n", h->Entry_point_adress);
    // printf("Start of program headers: %s \n",h->Start_of_program_headers);
    // printf("Start of section headers: %s \n",h->Start_of_section_headers);
    // printf("Flags: %s \n",h->Flags);
    // printf("Size of this header: %s \n",h->Size_of_this_header);
    // printf("Size of program headers: %s \n",h->Size_of_program_header);
    // printf("Number of program headers: %s \n",h->Number_of_program_headers);
    // printf("Size of section headers: %s \n",h->Size_of_section_headers);
    // printf("Number of section headers: %s \n",h->Number_of_section_headers);
    // printf("Section header string table index: %s \n",h->Section_header_string_table_index);
    
}


void main(int argc , char **argv)
{
    FILE *f;
    Header *Header = malloc(sizeof(*Header));
    f = fopen(argv[1],"r");
    lectureHead(f,Header);
    print_header(Header);
    fclose(f);
}
