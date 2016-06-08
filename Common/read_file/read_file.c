#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <utmp.h>

#define SNOOPTAB "/tmp/2/snooptab"

int use_socket = 0, proctype = DEAD_PROCESS;
char snoopdev[32], childproc[128];

void errorf (char *fmt, ...)
{
        va_list args;

        va_start (args, fmt);
        vfprintf (stderr, fmt, args);
        exit (1);
}

char *leafname (char *path)
{
        int i = 0, j;

        for (j = 0; path[j]; j++)
        {
                if (path[j] == '/')
                        i = j + 1;
        }

        return (path + i);
}

/* read a single line from a stream, ignoring all irrelevant stuff */
int  read_line (char *buff, FILE *f)
{
    int b, i;

    *buff = 0;
    do
    {
        while ((b = fgetc(f)) != EOF && isspace(b));
        if (b == EOF) return (0);
        for (i = 0; b != EOF && b != '\n' && b != '\r'; i++)
        {
            buff[i] = (b == '\t') ? ' ': b;
            b = fgetc(f);
        }
        buff[i] = 0;
    }
    while (*buff == '#');

    return (1);
}

/* extract the first word from a string */
char *parse_arg (char *arg, char *buff)
{
        int i = 0, j = 0, quote = 0;

        *arg = 0;
        if (buff == NULL)
                return (NULL);

        while (buff[i] && buff[i] == ' ') i++;
        while (buff[i] && (buff[i] != ' ' || quote))
        {
                switch (buff[i])
                {
                case '\\' :     arg[j++] = buff[++i]; break;
                case '"'  :     quote = !quote; break;
                default   :     arg[j++] = buff[i];
                }
                i++;
        }
        while (buff[i] && buff[i] == ' ') i++;
        arg[j] = 0;

        return (j ? buff + i : NULL);
}


int main (void)
{
        FILE *f;
        char line[1024], arg[128], tty[16], *tail;

        if ((f = fopen(SNOOPTAB, "r")) == NULL)
                errorf ("can't open %s\n", SNOOPTAB);

        strcpy (tty, leafname(ttyname(STDIN_FILENO)));

        while (read_line(line, f))
        {
            /* Read first parameter in the Line */
                tail = parse_arg(arg, line);

                /* If first parameter is *, then true */
                if ((strcmp(arg, tty) == 0) || (*arg == '*'))
                {

                    /* Read second parameter in the Line */
                        tail = parse_arg(snoopdev, tail);
                        /* Read third  parameter in the Line */
                        tail = parse_arg(arg, tail);
                        /* Read fourth parameter in the Line */
                        tail = parse_arg(childproc, tail);
                        
                        if (strcmp(snoopdev, "socket") == 0)
                                use_socket = 1;

                        if (strcmp(arg, "init") == 0)
                                proctype = INIT_PROCESS;
                        else if (strcmp(arg, "login") == 0)
                                proctype = LOGIN_PROCESS;
                        else if (strcmp(arg, "user") == 0)
                                proctype = USER_PROCESS;

                        fclose (f);
                        return (1);
                }
        }

        fclose (f);
        errorf ("no entry for %s in %s\n", tty, SNOOPTAB);
}

