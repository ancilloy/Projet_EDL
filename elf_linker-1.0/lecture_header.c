#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
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

		for (compteur = 0;compteur < 9; compteur++) {
			c = fgetc(f);
			h->Pad[compteur] = c;
		}

		for (compteur = 0;compteur < 2; compteur++) {
	        c =fgetc(f);
			h->Type[compteur] = c;
		}

		for (compteur = 0;compteur < 2; compteur++) {
	        c =fgetc(f);
			h->Machine[compteur] = c;
		}

		for (compteur = 0;compteur < 4; compteur++) {
	        c =fgetc(f);
			h->Version_Machine[compteur] = c;
		}

		for (compteur = 0;compteur < 4; compteur++) {
	        c =fgetc(f);
			h->Entry_point_adress[compteur] = c;
		}

		for (compteur = 0;compteur < 4; compteur++) {
	        c =fgetc(f);
			h->Start_of_program_headers[compteur] = c;
		}

		for (compteur = 0;compteur < 4; compteur++) {
	        c =fgetc(f);
			h->Start_of_section_headers[compteur] = c;
		}

	}

	else {
		printf("ERREUR ! Fichier non ELF\n");
		exit(1);
	}
}


void print_header(Header *h) {

    printf("En-tête ELF: \n");
    printf("    Magic: ");
    for(int i = 0 ; i < 4 ; i++) {
    	printf("%02x ",h->Magic[i]);
    }

    printf("%02x ", h->Class);
    printf("%02x ", h->Data);
    printf("%02x ", h->Version);

    for(int i = 0 ; i < 9 ; i++) {
        printf("%02x ",h->Pad[i]);
    }
        
    printf("\n    Class: ");

    switch (h->Class) { //Faire des switch case pour chaque print avec les resultats possibles comme fait dans l'ancien code.
    	case 1 : 
    		printf("ELF32");
            break;

       case 2 : 
       		printf("ELF64");
            break;

       default : 
       		printf("TYPE ELF INCONNU");
    }

    printf("\n    Data: ");

    switch (h->Data) { //Faire des switch case pour chaque print avec les resultats possibles comme fait dans l'ancien code.
    	case 1 : 
    		printf("Complément à deux, petit boutisme");
            break;

       case 2 : 
       		printf("Complément à deux, gros boutisme");
            break;

       default : 
       		printf("Format de données inconnu");
    }

    printf("\n    Version: ");

    switch (h->Version) { //Faire des switch case pour chaque print avec les resultats possibles comme fait dans l'ancien code.
       case 1 : 
       		printf("1 (current)");
            break;

       default : 
       		printf("0 (Invalid version)");

   	}

   	printf("\n    Type: ");

    switch (h->Type[0]) {
    	case 0:
    		switch (h->Type[1]) {
		        case 0 :
		            printf("Aucun");
		            break;
		        case 1 :
		            printf("Repositionable");
		            break;
		        case 2 :
		           printf("Executable");
		           break;
		        case 3 :
		            printf("Objet partagé");
		            break;
		        case 4 :
		            printf("Fichier Core");
			    	break;
				default:
		            printf("Processor-specific");
		    }
		    break;
    }

   	printf("\n    Machine: ");

    switch (h->Machine[0]) {
    	case 0:
	    	switch (h->Machine[1]) {
				case 0:
					printf("No machine");
					break;
				case 1:
					printf("AT&T WE 32100");
					break;
				case 2:
					printf("SPARC");
					break;
				case 3:
					printf("Intel Architecture");
					break;
				case 4:
					printf("Motorola 68000");
					break;
				case 5:
					printf("Motorola 88000");
					break;
				case 7:
					printf("Intel 80860");
					break;
				case 8:
					printf("MIPS RS3000 Big-Endian");
					break;
				case 10:
					printf("MIPS RS4000 Big-Endian");
					break;
				case 11 ... 16:
					printf("Reserved for future use");
					break;
				case 40:
					printf("ARM");
					break;
				}
				break;
    }

    printf("\n    Version Machine: ");

    switch (h->Version_Machine[3]) {
       case 0 : 
       		printf("0x0 (aucune)");
       		break;
        
        case 1 : 
    		printf("0x1 (current)");
    		break;

       default : 
       		printf("Version Machine non reconnue");
   	}

   	printf("\n    Adresse du point d'entrée: ");

	if (h->Entry_point_adress[3] == 0) {
		printf("no entry point");
	}
	else {
		printf("0x%02x", h->Entry_point_adress[3]);
	}

	printf("\n    Size of program headers: %d", h->Start_of_program_headers[3]);

	printf("\n    Size of section headers: %d", (int) h->Start_of_section_headers[2] << 4 | h->Start_of_section_headers[3]);

	printf("\n");

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


int main(int argc , char **argv)
{
    FILE *f;
    Header *Header = malloc(sizeof(*Header));
    f = fopen(argv[1],"r");
    lectureHead(f,Header);
    print_header(Header);
    fclose(f);
    return 0;
}
