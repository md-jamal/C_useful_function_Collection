#include <stdio.h>
#include <string.h>

#define Max_CA_String 128

int GetKeyFromOpenvpnClientConfigurationFile()
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
       printf("Error opening file");
       return(-1);
   }

   fpw = fopen("./OpenvpnClientKey.txt" , "w");
   if(fpw == NULL) 
   {
       printf("Error opening file");
       return(-1);
   }

   while((fgets (str, Max_CA_String, fp))!= NULL) 
   {
       if ((strstr(str,"<key>") != NULL))
       {
           flag = 1;
           continue;
       }

       if ((strstr(str,"</key>") != NULL))
       {
           flag = 0;
           continue;
       }

       if (flag)
       {
           fputs(str,fpw);
       }

   }

   fclose(fp);
   fclose(fpw);
}

int GetCAFromOpenvpnClientConfigurationFile()
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
       printf("Error opening file");
       return(-1);
   }

   fpw = fopen("./OpenvpnClientCA.txt" , "w");
   if(fpw == NULL) 
   {
       printf("Error opening file");
       return(-1);
   }

   while((fgets (str, Max_CA_String, fp))!= NULL) 
   {
       if ((strstr(str,"<ca>") != NULL))
       {
           flag = 1;
           continue;
       }

       if ((strstr(str,"</ca>") != NULL))
       {
           flag = 0;
           continue;
       }

       if (flag)
       {
           fputs(str,fpw);
       }

   }

   fclose(fp);
   fclose(fpw);
}


int GetCertFromOpenvpnClientConfigurationFile()
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
       printf("Error opening file");
       return(-1);
   }

   fpw = fopen("./OpenvpnClientCert.txt" , "w");
   if(fpw == NULL) 
   {
       printf("Error opening file");
       return(-1);
   }

   while((fgets (str, Max_CA_String, fp))!= NULL) 
   {
       if ((strstr(str,"<cert>") != NULL))
       {
           flag = 1;
           continue;
       }

       if ((strstr(str,"</cert>") != NULL))
       {
           flag = 0;
           continue;
       }

       if (flag)
       {
           fputs(str,fpw);
       }

   }

   fclose(fp);
   fclose(fpw);
}

int ModifyCAtoConfigurationFile()
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
       printf("Error opening file");
       return(-1);
   }

   fp2 = fopen("./ca.crt" , "r");
   if(fp2 == NULL) 
   {
       printf("Error opening file");
       return(-1);
   }

   fpw = fopen("./NewConfigurationFile.txt" , "w");
   if(fpw == NULL) 
   {
       printf("Error opening file");
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
   fclose(fpw);

}

int main()
{
    ModifyCAtoConfigurationFile();
    GetCertFromOpenvpnClientConfigurationFile();
    GetKeyFromOpenvpnClientConfigurationFile();
    GetCAFromOpenvpnClientConfigurationFile();
}
