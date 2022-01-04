#ifndef __LECTURE_HEADER_H__
#define __LECTURE_HEADER_H__

typedef struct Header Header;
struct Header
{
    char Magic[4];
    char Class;
    char Data;
    char Version;
    unsigned char ABI;
    char ABI_V;
    char Pad[7];
    char Type[2];
    unsigned char Machine[2];
    unsigned char Version_Machine[4];
    unsigned char Entry_point_adress[4];
    unsigned char Start_of_program_headers[4];
    unsigned char Start_of_section_headers[4];
    unsigned char Flags[4];
    unsigned char Size_of_this_header[2];
    unsigned char Size_of_program_header[2];
    unsigned char Number_of_headers[2];
    unsigned char Size_of_section_headers[2];
    char Number_of_section_headers[2];
    char Section_header_string_table_index[2];
};


#endif
