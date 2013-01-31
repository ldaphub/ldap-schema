#include <stdio.h>
#include <string.h>
int main(int argc, char * argv[]);
int main(int argc, char * argv[])
{
   int    c;
   int    x;
   size_t y;
   size_t len;

   // checks arguments
   if (argc < 2)
   {
      printf("Usage: %s <alpha-oid>\n", argv[0]);
      return(1);
   };

   // verifies that the object identifiers only contain letters
   for(x = 1; x < argc; x++)
   {
      for(y = 0; y < strlen(argv[x]); y++)
      {
         c = argv[x][y];
         if (c == '-')
         {
            if (!(strcasecmp(&argv[x][y], "-oid")))
               y += strlen(argv[x]);
         }
         else if ( ((c < '0') || (c > '9')) &&
                   ((c < 'A') || (c > 'Z')) &&
                   ((c < 'a') || (c > 'z')) )
         {
            fprintf(stderr, "%s: invalid object identifier \"%s\"\n", argv[0], argv[x]);
            return(1);
         };
      };
   };

   // loops through oids
   for(x = 1; x < argc; x++)
   {
      // adjusts first letter
      c = argv[x][0];
      if ((c >= '0') && (c <= '9'))
         c -= '0';
      else if ((c >= 'a') && (c <= 'z'))
         c -= 'a' - 10;
      else if ((c >= 'A') && (c <= 'Z'))
         c -= 'A' - 10;

      // prints beginning of oid mapping
      printf("objectIdentifier %-35s AutoOID:%i",  argv[x], c);

      // adjusts size
      len = strlen(argv[x]);
      if (!(strcasecmp(&argv[x][len-4], "-oid")))
         len -= 4;

      // converts each letter to a numeral
      for(y = 1; y < len; y++)
      {
         c = argv[x][y];
         if ((c >= '0') && (c <= '9'))
            c -= '0';
         else if ((c >= 'a') && (c <= 'z'))
            c -= 'a' - 10;
         else if ((c >= 'A') && (c <= 'Z'))
            c -= 'A' - 10;
         printf(".%i", c);
      };
      printf("\n");
   };

   return(0);
}
