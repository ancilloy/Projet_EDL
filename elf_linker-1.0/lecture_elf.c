#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <byteswap.h>
#include "lecture_elf.h"


Elf32_Ehdr header;
Elf32_Shdr section;
section_n *sct;

int IsElf(unsigned char *str) {
    if(str[0] == 0x7f && str[1] == 'E' && str[2] == 'L' && str[3] == 'F')
    	return 1;
    else
    	return 0;
}


void lectureHead(FILE *f){
	fread(&header, 1, sizeof(Elf32_Ehdr), f);

	if (IsElf(header.e_ident) != 1) {
		printf("ERREUR ! Fichier non ELF\n");
		exit(1);
	}
}

void lectureSection(FILE *f){

	fseek(f, bswap_32(header.e_shoff) + bswap_16(header.e_shentsize) * bswap_16(header.e_shstrndx), SEEK_SET);

	fread(&section, 1, sizeof(section), f);

	char* sect_nom = malloc(bswap_32(section.sh_size));

	fseek(f, bswap_32(section.sh_offset), SEEK_SET);

	fread(sect_nom, 1, bswap_32(section.sh_size), f);

	for (int i=0; i<bswap_16(header.e_shnum); i++) {

		sct[i].nom = "";
		printf("\n%s\n", sct[i].nom);

		fseek(f, bswap_32(header.e_shoff) + i * sizeof(Elf32_Shdr), SEEK_SET);
		fread(&sct[i].sect, 1, sizeof(section), f);

		if (bswap_32(sct[i].sect.sh_name)) {
			sct[i].nom = sect_nom + bswap_32(sct[i].sect.sh_name);
		}

		// printf("\n%d\n", i);

	}
} 


void print_header() {

    printf("En-tête ELF: \n");
    printf("    Magic: ");
    for(int i = 0 ; i < 16 ; i++) {
    	printf("%02x ",header.e_ident[i]);
    }
        
    printf("\n    Class: 						");

    switch (header.e_ident[4]) { //Faire des switch case pour chaque print avec les resultats possibles comme fait dans l'ancien code.
    	case 1 : 
    		printf("ELF32");
            break;

       case 2 : 
       		printf("ELF64");
            break;

       default : 
       		printf("TYPE ELF INCONNU");
    }

    printf("\n    Data: 						");

    switch (header.e_ident[5]) { //Faire des switch case pour chaque print avec les resultats possibles comme fait dans l'ancien code.
    	case 1 : 
    		printf("Complément à deux, petit boutisme");
            break;

       case 2 : 
       		printf("Complément à deux, gros boutisme");
            break;

       default : 
       		printf("Format de données inconnu");
    }

    printf("\n    Version: 						");

    switch (header.e_ident[6]) { //Faire des switch case pour chaque print avec les resultats possibles comme fait dans l'ancien code.
       case 1 : 
       		printf("1 (current)");
            break;

       default : 
       		printf("0 (Invalid version)");

   	}

   	printf("\n    OS/ABI: 						");

   	switch (header.e_ident[7]) {
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

   	printf("\n    Version ABI: 					%x", header.e_ident[8]);

   	printf("\n    Type: 						");
    		
	switch (bswap_16(header.e_type)) {
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

   	printf("\n    Machine: 						");
	switch (bswap_16(header.e_machine)) {
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

    printf("\n    Version Machine: 					");

    switch (bswap_32(header.e_version)) {
       case 0 : 
       		printf("0x0 (aucune)");
       		break;
        
        case 1 : 
    		printf("0x1 (current)");
    		break;

       default : 
       		printf("Version Machine non reconnue");
   	}

   	printf("\n    Adresse du point d'entrée: 				");

	if (bswap_32(header.e_entry) == 0) {
		printf("no entry point");
	} 
	else {		
        printf("0x%x", bswap_32(header.e_entry));
	}

	printf("\n    Début des en-têtes de programme:			%d (octets dans le fichier)", bswap_32(header.e_phoff));

    printf("\n    Début des en-têtes de section:			%d (octets dans le fichier)", bswap_32(header.e_shoff));

    printf("\n    Flags: 						0x%02x, Version5 EABI, soft-float ABI", bswap_32(header.e_flags));

    printf("\n    Taille de cet en-tete: 				%d (octets)", bswap_16(header.e_ehsize));

    printf("\n    Taille de l'en-tete du programme: 			%d (octets)", bswap_16(header.e_phentsize));

    printf("\n    Nombre d'en-tête du programme: 			%d", bswap_16(header.e_phnum));
    
    printf("\n    Taille des en-têtes de section: 			%d (octets) ",bswap_16(header.e_shentsize));
    
    printf("\n    Nombre d'en-têtes de section: 		   	%d", bswap_16(header.e_shnum));
    
    printf("\n    Table d'indexes des chaînes d'en-tête de section: 	%d \n", bswap_16(header.e_shstrndx));
    
}

void print_section() {

	printf("Il y a %d en-têtes de section, débutant à l'adresse de décalage 0x%x:\n", bswap_16(header.e_shnum), bswap_32(header.e_shoff));

	printf("\n[NR]	Nom			Type		Adr		Décala	Taille	ES	Fan	LN	Inf	Al\n");

	for (int i=0; i<bswap_16(header.e_shnum); i++) {
		printf("[%d]	%s		\n", i, sct[i].nom);
	}
}


int main(int argc , char **argv)
{
    FILE *f;

	sct = malloc(sizeof(section_n) * bswap_16(header.e_shnum));

    f = fopen(argv[1],"r");
    lectureHead(f);
    print_header();
    fclose(f);

    f = fopen(argv[1],"r");
    lectureSection(f);
    print_section();
    fclose(f);
    return 0;
}
