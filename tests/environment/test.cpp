#include <stdlib.h>
#include <stdio.h>
#include <iostream>

int print_path(void) {
    char *var;
    var = getenv("PATH");
    printf("pathvar=%s", var);
    return 0;
}

extern char **environ;

int main(int argc, char **argv) {
    char** env;

    for (env = environ; *env != 0; env++) {
        //printf("%s\n", *env);
        std::cout<<*env<<std::endl;
    }

    print_path();
}
