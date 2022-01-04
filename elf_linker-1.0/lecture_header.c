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

        c =fgetc(f);
		h->OS_ABI = c;

        c =fgetc(f);
		h->ABI_V = c;

		for (compteur = 0;compteur < 7; compteur++) {
			c = fgetc(f);
			h->Pad[compteur] = c;
		}

        c =fgetc(f);
		h->Type[0] = c;
        c =fgetc(f);
		h->Type[1] = c;

        c =fgetc(f);
		h->Machine[0] = c;
        c =fgetc(f);
		h->Machine[1] = c;

        c =fgetc(f);
		h->Version_Machine[0] = c;
        c =fgetc(f);
		h->Version_Machine[1] = c;
        c =fgetc(f);
		h->Version_Machine[2] = c;
        c =fgetc(f);
		h->Version_Machine[3] = c;
        printf(" debug : %02X \n",c);
        c =fgetc(f);
        printf(" debug : %02X \n",c);
		h->Entry_point_adress[0] = c;
        c =fgetc(f);
        printf(" debug : %02X \n",c);
		h->Entry_point_adress[1] = c;
        c =fgetc(f);
        printf(" debug : %02X \n",c);
		h->Entry_point_adress[2] = c;
        c =fgetc(f);
        printf(" debug : %02X \n",c);
		h->Entry_point_adress[3] = c;
        
    


	}

	else {
		printf("ERREUR ! Fichier non ELF\n");
		exit(1);
	}
}


char *traitement_class(char src){
   switch (src) {
       case 01 : return "ELF32";
                break;

       case 02 : return "ELF64";
                break;

       default : return "TYPE ELF INCONNU";

   }
}

char *traitement_data(char src){
   switch (src) {
       case 01 : return "Complément à deux, petit boutisme";
                break;

       case 02 : return "Complément à deux, gros boutisme";
                break;

       default : return "Format de données inconnu";

   }
}

char *traitement_version(char src){
   switch (src) {
       case 01 : return "1 (current)";
                break;

       default : return "0 (Invalid version)";

   }
}

char *traitement_OS_ABI(char src){
   switch (src) {
       case 00 : return "UNIX - System V";

       case 01 : return "UNIX - System V";

       default : return "Autre Systéme";

   }
}

char *traitement_ABI_V(char src){
   char *ptr = malloc(2*sizeof(char));
   ptr[0] = src;
   ptr[1] = '\0';
   /* Ici 2 cas 
    => soit la valeur est 00 : je retourne directement la chaine de caractére "0" et je fais un free sur mon ptr qui sert a rien
    => Valeur differente de 00 : je crée une chaine de caractére avec le caractére que je met dans ptr et je le return dans le default
   */
    
   switch (src) {
       case 00 : free(ptr);
                 return "0";
       default : return ptr;


   }
}

char *traitement_Type(char *src){

    switch (src[0]) {
       case 00 : 
                switch (src[1])
                {
                case 00 :
                    return "Aucun";
                case 01 :
                    return "Repositionable";
                case 02 :
                   return "Executable";
                case 03 :
                    return "Objet partagé";
                case 04 :
                    return "Fichier Core";

                default:
                    return "Type non reconnu";
                }
        default : return "Type non reconnu";


   }

}

char *traitement_Machine(char *src){
    switch (src[0]) {
       case 00 :  ;   

                int convertion = src[1];
                switch (convertion)
                {
                    
                case 0 :
                    return "Aucune";
                case 2 :
                    return "SPARC";
                case 3 :
                   return "Intel 80386";
                case 4 :
                    return "Motorola 68000";
                case 7 :
                    return "Intel i860";
                case 8 :
                    return "MIPS I";
                case 19 :
                    return "Intel i960";
                case 20 :
                    return "PowerPC";
                case 40 :
                    return "ARM";
                case 50 :
                    return "Intel IA64";
                case 62 :
                    return "x64";
                case 243 :
                    return "RISC-V";
                default:
                    return "Machine non reconnue";
                }
        default : return "Machine non reconnu";


   }

}

char *traitement_Version_Machine(char *src){
    if(src[0] != 0 || src[1] != 0 || src[2] != 0)
        return "Version Machine non reconnue";
   
    switch (src[3]) {
       case 00 : return "0x0 (aucune)";
        
        case 01 : return "0x1 (current)";

       default : return "Version Machine non reconnue";


   }
}



char *traitement_Entry_point_adress(char *src){
    char *res = malloc(sizeof(char)*16);
    sprintf(res, "%x%x%x%x",(int) src[0],(int) src[1],(int) src[2], (int) src[3]);
    int test_convertion = atoi(res);
    sprintf(res, "0x%d",test_convertion);
    return res;

}

void print_header(Header *h) {

    printf("En-tête ELF:: \n");
    printf("    Magic: ");
        for(int i = 0 ; i < 4 ; i++) {
        	printf("%02x ",h->Magic[i]);
        }
        
    printf("\n");
    printf("    Class: %s \n",traitement_class(h->Class)); //Faire des switch case pour chaque print avec les resultats possibles comme fait dans l'ancien code.
    printf("    Data: %s \n",traitement_data(h->Data)); //Faire des switch case pour chaque print avec les resultats possibles comme fait dans l'ancien code.
    printf("    Version: %s \n",traitement_version(h->Version)); //Faire des switch case pour chaque print avec les resultats possibles comme fait dans l'ancien code.
    printf("    Pad: ");
        for(int i = 0 ; i < 7 ; i++) {
            printf("%02x ",h->Pad[i]);
        }
    printf("\n");
    printf("    OS/ABI: %s \n",traitement_OS_ABI(h->OS_ABI));
    printf("    ABI Version: %s \n",traitement_ABI_V(h->ABI_V));
    printf("    Type: %s \n",traitement_Type(h->Type));
    printf("    Machine: %s \n",traitement_Machine(h->Machine));
    printf("    Version: %s \n",traitement_Version_Machine(h->Version_Machine));
    printf("    Adresse du point d'entrée: %s \n", traitement_Entry_point_adress(h->Entry_point_adress));
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
