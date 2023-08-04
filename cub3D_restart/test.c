#include <stdio.h>
#include <stdbool.h>

int is_numeric(char *str) {
    if (!str || *str == '\0') 
    {
        return 0; // Retourne 0 si la chaîne est vide ou NULL
    }

    while (*str) 
    {
        if (*str < '0' || *str > '9') {
            return 0; // Retourne 0 dès qu'on trouve un caractère qui n'est pas un chiffre
        }
        str++;
    }

    return 1; // Si on arrive ici, tous les caractères sont des chiffres
}

int main() {
    char test1[] = "-12345";
    char test2[] = "kjha";

    printf("%s est %snumerique.\n", test1, is_numeric(test1) ? "" : "non ");
    printf("%s est %snumerique.\n", test2, is_numeric(test2) ? "" : "non ");

    return 0;
}
