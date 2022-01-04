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
	unsigned char c;

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

		c =fgetc(f);
		h->ABI = c;

		c =fgetc(f);
		h->ABI_V = c;

		for (compteur = 0;compteur < 7; compteur++) {
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
            //printf("Coucou c'est du debug tkt : %x \n",c);
			h->Start_of_section_headers[compteur] = c;
		}

        for (compteur = 0;compteur < 4; compteur++) {
	        c =fgetc(f);
            //printf("Coucou c'est du debug tkt : %02x \n",c);
			h->Flags[compteur] = c;
		}

        for (compteur = 0;compteur < 2; compteur++) {
	        c =fgetc(f);
            //printf("Coucou c'est du debug tkt : %02x \n",c);
			h->Size_of_this_header[compteur] = c;
		}

        for (compteur = 0;compteur < 2; compteur++) {
	        c =fgetc(f);
            //printf("Coucou c'est du debug tkt : %02x \n",c);
			h->Size_of_program_header[compteur] = c;
		}

        for (compteur = 0;compteur < 2; compteur++) {
	        c =fgetc(f);
            //printf("Coucou c'est du debug tkt : %02x \n",c);
			h->Number_of_headers[compteur] = c;
		}

        for (compteur = 0;compteur < 2; compteur++) {
	        c =fgetc(f);
            //printf("Coucou c'est du debug tkt : %02x \n",c);
			h->Size_of_section_headers[compteur] = c;
		}

        for (compteur = 0;compteur < 2; compteur++) {
	        c =fgetc(f);
            //printf("Coucou c'est du debug tkt : %02x \n",c);
			h->Number_of_section_headers[compteur] = c;
		}

        for (compteur = 0;compteur < 2; compteur++) {
	        c =fgetc(f);
            //printf("Coucou c'est du debug tkt : %02x \n",c);
			h->Section_header_string_table_index[compteur] = c;
		}

	}

	else {
		printf("ERREUR ! Fichier non ELF\n");
		exit(1);
	}
}


int hextodec(char *hex,int taille) {
     long long decimal = 0, base = 1;
    int i = 0, length;
    length = taille;
    for(i = length--; i >= 0; i--)
    {
        if(hex[i] >= '0' && hex[i] <= '9')
        {
            decimal += (hex[i] - 48) * base;
            base *= 16;
        }
        else if(hex[i] >= 'A' && hex[i] <= 'F')
        {
            decimal += (hex[i] - 55) * base;
            base *= 16;
        }
        else if(hex[i] >= 'a' && hex[i] <= 'f')
        {
            decimal += (hex[i] - 87) * base;
            base *= 16;
        }
    }
    return decimal;
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

    for(int i = 0 ; i < 7 ; i++) {
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

   	printf("\n    OS/ABI: ");

   	switch (h->ABI) {
   		case 0:
   			printf("UNIX System V");
   			break;
   		case 1:
   			printf("HP-UX");
   			break;
   		case 2:
   			printf("NetBSD");
   			break;
   		case 3:
   			printf("Linux");
   			break;
   		case 6:
   			printf("Sun Solaris");
   			break;
   		case 7:
   			printf("IBM AIX");
   			break;
   		case 8:
   			printf("SGI Irix");
   			break;
   		case 9:
   			printf("FreeBSD");
   			break;
   		case 10:
   			printf("Compaq TRU64");
   			break;
   		case 11:
   			printf("Novell Modesto");
   			break;
   		case 12:
   			printf("OpenBSD");
   			break;
   		case 64:
   			printf("ARM EABI");
   			break;
   		case 97:
   			printf("ARM");
   			break;
   		case 255:
   			printf("Standalone");
   			break;
   	}

   	printf("\n    Version ABI: 0x%x", h->ABI_V);

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
				case 19:
					printf("Intel i960");
					break;
				case 20:
					printf("Power PC");
					break;
				case 40:
					printf("ARM");
					break;
				case 50:
					printf("Intel IA64");
					break;
				case 62:
					printf("x64");
					break;
				case 243:
					printf("RISC-V");
					break;
				default:
					printf("Reserved for future use");
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
    char res[16];
    int test_convertion;
    uint32_t result;

	if (h->Entry_point_adress[3] == 0) {
		printf("no entry point");
	}
	else {
        sprintf(res, "%02x%02x%02x%02x",(int) h->Entry_point_adress[0],(int) h->Entry_point_adress[1],(int) h->Entry_point_adress[2], (int) h->Entry_point_adress[3]);
        test_convertion = atoi(res);
        sprintf(res, "0x%d",test_convertion);
        printf("%s", res);
	}

    result = (h->Start_of_program_headers[0]<<24) | (h->Start_of_program_headers[1]<<16) | (h->Start_of_program_headers[2]<<8) | h->Start_of_program_headers[3];
	printf("\n    Size of program headers: %d (octets dans le fichier)", result);

    
    result = (h->Start_of_section_headers[0]<<24) | (h->Start_of_section_headers[1]<<16) | (h->Start_of_section_headers[2]<<8) | h->Start_of_section_headers[3];
    printf("\n    Size of section headers: %d (octets dans le fichier)", result);


    printf("\n    Flags: ");
    sprintf(res, "%02x%02x%02x%02x",(int) h->Flags[0],(int) h->Flags[1],(int) h->Flags[2], (int) h->Flags[3]);
    test_convertion = atoi(res);
    sprintf(res, "0x%d",test_convertion);
    printf("%s, Version5 EABI, soft-float ABI", res);

    result = (h->Size_of_this_header[0]<<8) | h->Size_of_this_header[1];
    printf("\n    Taille de cet en-tete: %d (octets)", result);

    result = (h->Size_of_program_header[0]<<8) | h->Size_of_program_header[1];
    printf("\n    Taille de l'en-tete du programme: %d (octets)", result);

    result = (h->Number_of_headers[0]<<8) | h->Number_of_headers[1];
    printf("\n    Nombre d'en-tête du programme: %d", result);
    
    result = (h->Size_of_section_headers[0]<<8) | h->Size_of_section_headers[1];
    printf("\n    Taille des en-têtes de section: %d (octets) ", result);
    
    result = (h->Number_of_section_headers[0]<<8) | h->Number_of_section_headers[1];
    printf("\n    Nombre d'en-têtes de section: %d", result);
    
    result = (h->Section_header_string_table_index[0]<<8) | h->Section_header_string_table_index[1];
    printf("\n    Table d'indexes des chaînes d'en-tête de section: %d \n", result);
    
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
