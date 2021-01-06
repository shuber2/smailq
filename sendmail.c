#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


static void usage(char* arg0) {
    puts("A wrapper script for smailq that mimics sendmail.\n"
         "USAGE:\n");
    printf("  %s [OPTIONS] [recipient ...]\n", arg0);
    printf("  %s -bp\n", arg0);
    puts("\n"
         "OPTIONS:\n"
         "  -bp\n"
         "     Calls `smailq --list`\n"
         "\n"
         "  -h\n"
         "     Prints this help text\n"
         "\n"
         "  [OPTIONS] [recipient ...]\n"
         "     Calls `smailq --send -- [OPTIONS] [recipient ...]`.\n"
         "     It passes all options as MSA options to smailq.\n");
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        fputs("No arguments given.\n", stderr);
        usage(argv[0]);
        return EINVAL;
    }

    if (strcmp(argv[1], "-h") == 0) {
        usage(argv[0]);
        return EXIT_SUCCESS;
    }

    if (strcmp(argv[1], "-bp") == 0) {
        execlp("smailq", "smailq", "list", NULL);
        perror("Error calling smailq --list");
        return EXIT_FAILURE;
    }

    /* We have to add two more arguments: -- --send */
    char** newargv = malloc((argc+2)*sizeof(char*));
    if (newargv == NULL) {
        perror(NULL);
        return EXIT_FAILURE;
    }

    /* Fill in the arguments for smailq. Note that argv[argc] is NULL and
     * newargv must be termined by a NULL pointer for execvp(). */
    newargv[0] = "smailq";
    newargv[1] = "--send";
    newargv[2] = "--";
    for (int i=1; i <= argc; ++i)
        newargv[2+i] = argv[i];

    execvp("smailq", newargv);
    perror("Error calling smailq --list");
    free(newargv);
    return EXIT_FAILURE;
}
