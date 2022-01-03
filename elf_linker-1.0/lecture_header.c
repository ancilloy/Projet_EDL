#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lecture_header.h"

int IsElf(char *str) {
    if(str[0] == 0x7f && str[1] == 'E' && str[2] == 'L' && str[3] == 'F')
       return 0;
    else
      return 1;
}

int print_header(Header *h) {

    printf("ELF Header: \n");
    printf("Magic: ");
        for(int i = 0 ; i < strlen(h->Magic) ; i++) {
                
                if(h->Magic[i] == '#') {
                     printf("00 ");
                }
                else {
                    printf("%02x ",h->Magic[i]);
                }

        }
        
    printf("\n");
    printf("Class: %s \n",h->Class);
    printf("Data: %s \n",h->Data);
    printf("Version: %s \n",h->Version);
    printf("OS/ABI: %s \n",h->OS_ABI);
    printf("ABI Version: %s \n",h->ABI_V);
    printf("Type: %s \n",h->Type);
    printf("Machine: %s \n",h->Machine);
    printf("Version: %s \n",h->Version_Machine);
    printf("Entry point address: %s \n", h->Entry_point_adress);
    printf("Start of program headers: %s \n",h->Start_of_program_headers);
    printf("Start of section headers: %s \n",h->Start_of_section_headers);
    printf("Flags: %s \n",h->Flags);
    printf("Size of this header: %s \n",h->Size_of_this_header);
    printf("Size of program headers: %s \n",h->Size_of_program_header);
    printf("Number of program headers: %s \n",h->Number_of_program_headers);
    printf("Size of section headers: %s \n",h->Size_of_section_headers);
    printf("Number of section headers: %s \n",h->Number_of_section_headers);
    printf("Section header string table index: %s \n",h->Section_header_string_table_index);
    
}

void lectureHead(FILE *f,Header *h){
    
    int compteur = 0;
    char c ;
    char type[9];
    if(f!=NULL){
       c =  fgetc(f);
       type[compteur] = c;
       compteur++;
       while(compteur <= 7) {
           
           //printf("%x",c);
           c =  fgetc(f);
           if(c == '\0') {
                c = '#';
            }
            if(compteur == 4) {
                if(c == '#') {
                    h-> Class = malloc(sizeof(char )*strlen("INVALID ELF"));
                    strcpy(h->Class,"INVALID ELF");

                }
                else if ( c == 01) {
                    h-> Class = malloc(sizeof(char )*strlen("ELF32"));
                    strcpy(h->Class,"ELF32");

                }
                else if (c == 02 ) {
                    h-> Class = malloc(sizeof(char )*strlen("ELF64"));
                    strcpy(h->Class,"ELF64");
                }

            }
           type[compteur] = c;
           compteur++;
    }
     

    if(IsElf(type) != 0) {
        printf("[Erreur] Fichier non ELF \n");
        exit(1);
        }
    else
      {
          printf("[Type] Fichier de type ELF \n");
          h-> Magic = malloc(sizeof(char )*strlen(type));
          strcpy(h->Magic,type);
          
      }

        while(compteur < 16) {
          
            c =  fgetc(f);
            if(c == '\0') {
                c = '#';
            }

            h-> Magic = realloc( h-> Magic , sizeof(char )*( strlen(h-> Magic  ) +1 ) );
            h-> Magic[compteur ] = c ;

           // printf("DEBUG : compteur = %d , valeur magic : %c , valeur de c : %x  , taille de magic : %ld  ,  \n" , compteur ,h-> Magic[compteur] , c , strlen(h->Magic));
            compteur++;

        }
    }
    fclose(f);
}



void main(int argc , char **argv)
{
    FILE *f;
    Header *Header = malloc(sizeof(*Header));
    f = fopen(argv[1],"r");
    lectureHead(f,Header);
    print_header(Header);
}
