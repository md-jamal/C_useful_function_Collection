#include<stdio.h>

/* Trim whitespace and newlines from a string
 */
size_t strtrim(char *str)
{
        char *end, *pch = str;

        if(str == NULL || *str == '\0') {
                /* string is empty, so we're done. */
                return 0;
        }

        while(isspace((unsigned char)*pch)) {
                pch++;
        }

        if(pch != str) {
                size_t len = strlen(pch);
                /* check if there wasn't anything but whitespace in the string. */
                if(len == 0) {
                        *str = '\0';
                        return 0;
                }
                memmove(str, pch, len + 1);
                pch = str;
        }

        end = (str + strlen(str) - 1);
        while(isspace((unsigned char)*end)) {
                end--;
        }
        *++end = '\0';

        return end - pch;
}

int main()
{
    char string[64]="  Good Job  ";

    printf("%d\n",strtrim(string));
}
