#include <stdio.h>
int main(){
    char var1;
    printf("Enter character: ");
    scanf("%c",&var1);     
    printf("ASCII value(DEC) of %d",var1);  
    if (var1 == 31)
        printf("\n Receive ASCII Control Codes \n Break \n",var1);  
    return 0;
}

// [ASCII Control Codes](http://academic.evergreen.edu/projects/biophysics/technotes/program/ascii_ctrl.htm)
