#ifndef __LECTURE_HEADER_H__
#define __LECTURE_HEADER_H__

typedef struct Header Header;
struct Header
{
    char Magic[4];
    char Class;
    char Data;
    char Version;
    char Pad[7];
    char OS_ABI;
    char ABI_V;
    char Type[2];
    char Machine[2];
    char Version_Machine[4];
    char Entry_point_adress[4];
    // char *Start_of_program_headers;
    // char *Start_of_section_headers;
    // char *Flags;
    // char *Size_of_this_header;
    // char *Size_of_program_header;
    // char *Number_of_headers;
    // char *Number_of_program_headers;
    // char *Size_of_section_headers;
    // char *Number_of_section_headers;
    // char *Section_header_string_table_index;
};


#endif
