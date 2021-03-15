
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int args_len(int argc, char *argv[])
{
    int len = 0;
    for (int i = 1; i < argc; i++)
    {
        len += strlen(argv[i]) + 1;
    }
    return len + 1;
}

char *execute(char *cmd)
{

    FILE *fp;
    char path[1035];
    fp = popen(cmd, "r");
    if (fp == NULL)
    {
        printf("Failed to run command\n");
        exit(1);
    }

    /* Read the output a line at a time - output it. */
    fgets(path, sizeof(path), fp) != NULL;

    /* close */
    pclose(fp);

    char *buf = (char *)malloc(strlen(path));
    strcpy(buf, path);
    return buf;
}

int main(int argc, char *argv[])
{
    int argslen = args_len(argc, argv);
    char *buf = (char *)malloc(argslen);
    if (!buf)
        goto error;

    for (int i = 1; i < argc; i++)
    {
        buf[0] = '\0';
        strcat(buf, "pidof ");
        strcat(buf, argv[i]);

        char *pids = execute(buf);
        buf[0] = '\0';
        strcat(buf, "kill -9 ");
        strcat(buf, pids);
        system(buf);
    }
    free(buf);
    return 0;
error:
    //thi probably won't happen, but in case you're covered
    printf("Not enough memory!");
    return 0;
}
