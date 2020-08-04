#define MAIN_C
/* main.c by Adam Rogoyski <apoc@laker.net> Temperanc on EFNet irc
 * Copyright (C) 1998, 1999 Adam Rogoyski
 * --- GNU General Public License Disclamer ---
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */


#include "hexedit.h"
#include <assert.h>


unsigned char EBCDIC[] = {
'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.',
' ', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '<', '(', '+', '|',
'&', '.', '.', '.', '.', '.', '.', '.', '.', '.', '!', '$', '*', ')', ';', '^',
'-', '/', '.', '.', '.', '.', '.', '.', '.', '.', '|', ',', '%', '_', '>', '?',
'.', '.', '.', '.', '.', '.', '.', '.', '.', '`', ':', '#', '@', '\'', '=','"',
'.', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', '.', '{', '.', '.', '.', '.',
'.', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', '.', '}', '.', '.', '.', '.',
'.', '~', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '.', '.', '.', '[', '.', '.',
'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', ']', '.', '.',
'{', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', '.', '.', '.', '.', '.', '.',
'}', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', '.', '.', '.', '.', '.', '.',
'\\', '.', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '.', '.', '.', '.', '.','.',
'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.', '.', '.', '.', '.', '.',
};


/* Table for translating an ASCII character into an EBCDIC char.  Index into
 * the array with an ASCII char value, at that index is the EBCDIC char value
 * of that character.
 */
unsigned char ASCII_to_EBCDIC[] = {
0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,
0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,0x2e,
0x40,0x5a,0x7f,0x7b,0x5b,0x6c,0x50,0x7d,0x4d,0x5d,0x5c,0x4e,0x6b,0x60,0x00,0x61,
0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,0xf8,0xf9,0x7a,0x5e,0x4c,0x7e,0x6e,0x6f,
0x7c,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xd1,0xd2,0xd3,0xd4,0xd5,0xd6,
0xd7,0xd8,0xd9,0xe2,0xe3,0xe4,0xe5,0xe6,0xe7,0xe8,0xe9,0xad,0xe0,0xbd,0x5f,0x6d,
0x79,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x91,0x92,0x93,0x94,0x95,0x96,
0x97,0x98,0x99,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0x8b,0x4f,0x9b,0xa1,0x2e
};


int calc_pointer( int location, int header_offset, int pointer_offset)
{
	location = (location & 0x00FFFF) + pointer_offset + header_offset;
	return( (((location & 0xFF00)/0x100)+((location & 0x00FF)*0x100)));
}

int
main (int argc, char **argv)
{

   wchar_t in = 0;
   FILE * fp;
   int num;
   int i;
   char letter;

if ( argv[1] && argv[2])
{

   for ( i = 0 ; i != 256 ; i++ ) EBCDIC[i] = NULL;
   for ( i = 0 ; i != 128 ; i++ ) ASCII_to_EBCDIC[i] = NULL;

fp = fopen(argv[2], "rt");
 while (!feof(fp))
 {
	fscanf(fp, "%2x=%c", &num, &letter);
	ASCII_to_EBCDIC[letter] = num;
	EBCDIC[num] = letter;
 } 
fclose(fp);

}
   init (argc, argv);
   while (1)
   {
      in = getch ();
      switch (Globals.mode)
      {
         case HEX_MODE:
            hexMode (in);
            break;

         case ASCII_MODE:
            asciiMode (in);
            break;

         assert (1);  /* This would be a programming error. */
      }
   }
      /* Control never reaches here. */
   exitProgram ();
   return EXIT_SUCCESS;
}

