#include<stdio.h>
#include<string.h>

#define TOKENIZE(__token, __sep, __next_token) \
    do \
    { \
        /* Beginning of token  */ \
        __token = __next_token; \
        /* Skip sep */ \
        __token += strspn(__token, __sep); \
        /* Find end of token */ \
        __next_token = __token + strcspn(__token, __sep); \
        if (__token == __next_token) \
        { \
            __token = NULL; \
        } \
        /* Terminate token */ \
        *__next_token = '\0'; \
        /* Next token */ \
        __next_token++; \
    } while (0)




int main()
{
    unsigned char local_buf[40]="\0";
    char *param = NULL;
    char *end_param = NULL;
    char *last_char = NULL;
    static const char *param_sep = " \t,\n";


    strcpy(local_buf, "Some, String \t");

    end_param = local_buf;

    while(1)
    {
        TOKENIZE(param, param_sep, end_param);
        if (param == NULL)
            break;
        else
            printf("param = %s \n",param);
    }
}
