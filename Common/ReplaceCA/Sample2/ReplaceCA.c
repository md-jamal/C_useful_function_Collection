#include <stdio.h>
#include <string.h>

#define Max_CA_String 128

int LoadCA()
{
   FILE *fp, *fpw;
   char str[Max_CA_String];

   /* opening file for reading */
   fp = fopen("./ca.crt" , "r");
   if(fp == NULL) 
   {
       perror("Error opening ca.crt");
       return(-1);
   }

   fpw = fopen("./file.txt" , "w");
   if(fpw == NULL) 
   {
       perror("Error opening file.txt");
       return(-1);
   }

   while((fgets (str, Max_CA_String, fp))!= NULL) 
   {
       if ((strstr(str,"BEGIN CERTIFICATE") != NULL) || (strstr(str,"END CERTIFICATE") != NULL))
           continue;
       fputs(str,fpw);
   }
   fclose(fp);
   fclose(fpw);

   return(0);
}

int EditConfigurationFile()
{
   FILE *fp, *fp2,*fpw;
   int flag = 0;
   int skip = 0;
   char str[Max_CA_String];
   char str2[Max_CA_String];

   /* opening file for reading */
   fp = fopen("./text.txt" , "r+");
   if(fp == NULL) 
   {
       perror("Error opening file");
       return(-1);
   }

   fp2 = fopen("./ca.crt" , "r");
   if(fp2 == NULL) 
   {
       perror("Error opening file");
       return(-1);
   }

   fpw = fopen("./abc.txt" , "w");
 if(fpw == NULL) 
   {
       perror("Error opening file");
       return(-1);
   }

   while((fgets (str, Max_CA_String, fp))!= NULL) 
   {
       if ((strstr(str,"<ca>") != NULL))
       {
           fputs(str,fpw);
           flag = 1;
           continue;
       }

       if ((strstr(str,"</ca>") != NULL))
       {
           fputs(str,fpw);
           skip = 0;
           continue;
       }

       if (flag)
       {
           while((fgets(str2, Max_CA_String, fp2))!= NULL) 
           {
               puts(str2);
               if((str2[0] != '\n'))
                   fputs(str2,fpw);
           }
           flag = 0;
           skip = 1;
       }

       if (!skip)
       {
           fputs(str,fpw);
       }
   }

   fclose(fp);
   fclose(fp2);

}

int main()
{
    LoadCA();
    EditConfigurationFile();
}
