#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

void
happy(unsigned char *buffer, unsigned int buflen)
{
   unsigned char *tmp = buffer;

   while (buflen > 1)
   {
        printf("%c",*tmp++);
        buflen--;
   }
}

void 
decode_file (char *file)
{
  int ifd; 
  unsigned char *buffer;
  unsigned int buflen = 0;
  int rv = 0;
  struct stat st;
  if ((ifd = open (file, O_RDONLY)) == -1)
  {
      fprintf(stderr, "Error opening binary file %s: %s\n", file, strerror (errno));
      exit (-1);
  }
  if ((rv = fstat (ifd, &st)))
  {
      fprintf(stderr, "Can't stat file %s: %s\n", file, strerror (errno));
      exit (-1);
  }
  buffer = (unsigned char *) malloc (st.st_size * sizeof (unsigned char) + 1); /* allocate the memory */
  /* +1 mean need to add one more null terminal (\0) */
  buflen = read (ifd, buffer, st.st_size); 
  /*decode_main_aggregate (buffer, buflen);*/
  happy(buffer, buflen);
  free(buffer);
}  

int 
main ()
{
    decode_file("./a.txt");

    return 0;
}
