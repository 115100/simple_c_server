#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    char *userInput;

    printf("Type something: ");
    n = scanf("%ms", &userInput);

    printf("%d\n", n);
    printf("You typed: %s\n", userInput);

    free(userInput);

    return 0;
}
