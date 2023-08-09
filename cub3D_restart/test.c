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

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}



int main() {

    int t = 0;
    int r = 124;
    int g = 51;
    int b = 225;


    unsigned int result = create_trgb(t,r,g,b);

    printf("ui = %d i = %u x = %x\n", result, result, result);

    printf("t = %d\n", (result >> 24) & 0xFF);
    printf("r = %d\n", (result >> 16) & 0xFF);
    printf("g = %d\n", (result >> 8) & 0xFF);
    printf("b = %d\n", result & 0xFF);


    result = 22;

    printf("r = %d %u\n", result, result);

    // char test1[] = "-12345";
    // char test2[] = "kjha";

    // printf("%s est %snumerique.\n", test1, is_numeric(test1) ? "" : "non ");
    // printf("%s est %snumerique.\n", test2, is_numeric(test2) ? "" : "non ");

    return 0;
}
