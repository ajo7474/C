#include <stdio.h>
#include <string.h>
#include <stdlib.h>
main() {
       
  char *pt1, *pt2;
  
  pt1 = (char *) malloc (10);
  pt2 = (char *) malloc (8);

  system ("cls");
  strcpy (pt1, "012345678");
  strcpy (pt2, "1234567");
  
   int i=0;
   
  fprintf (stdout, "\nCaractere  ---   Endereco Virtual\n\n");
   for (i;i<= strlen (pt1);++i)
          printf ("%c          -->   %x\n", pt1[i], &pt1[i]);
   
   puts ("");       
   for (i=0;i<= strlen (pt2);++i)
          printf ("%c          -->   %p\n", pt2[i], &pt2[i]); 
    
}

