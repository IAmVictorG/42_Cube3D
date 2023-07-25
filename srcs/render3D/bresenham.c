#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void tracer_droite(int x1, int y1, int x2, int y2)
{
    int dx, dy;
    int err;

    err = x2 - x1;
    dx = err * 2;
    dy = (y2 - y1) * 2;
    while (x1 <= x2)
    {
        printf("Colorier pixel (%d, %d)\n", x1, y1);
        x1++;
        err -= dy;
        if (err <= 0)
        {
            y1++;
            err += dx;
        }
    }
}

void tracer_droite2(int x1, int y1, int x2, int y2)
{
    int dx, dy;
                int e;

    dx = x2 - x1;
    dy = y2 - y1;
    if (dx > 0)
    {
        if (dy > 0)
        {
            if (dx >= dy)
            {
                e = dx;
                dx *= 2;
                dy *= 2;
                while (42)
                {
                    printf("Colorier pixel (%d, %d)\n", x1, y1);
                    x1++;
                    if (x1 == x2)
                        break;
                    e -= dy;
                    if (e < 0)
                    {
                        y1++;
                        e += dx;
                    }
                }
            }
            else
            {
                
            }
        }
    }
}

void tracerSegment(int x1, int y1, int x2, int y2) {
    int dx, dy;  // déclaration des entiers dx et dy
    int e;      // valeur d’erreur
    int step;
    int steep = 0;

    if (abs(y2-y1) > abs(x2-x1)) {
        // Échanger x1 avec y1 et x2 avec y2
        int tmp = x1; x1 = y1; y1 = tmp;
        tmp = x2; x2 = y2; y2 = tmp;
        steep = 1;
    }

    // Assurer que x1 est toujours inférieur à x2
    if (x1 > x2) {
        int tmp = x1; x1 = x2; x2 = tmp;
        tmp = y1; y1 = y2; y2 = tmp;
    }

    e = x2 - x1;
    dx = e * 2;
    dy = abs(y2 - y1) * 2;
    step = (y1 < y2) ? 1 : -1;

    while (x1 <= x2) {
        if (steep) {
            printf("Colorier pixel (%d, %d)\n", y1, x1);
        } else {
            printf("Colorier pixel (%d, %d)\n", x1, y1);
        }
        
        x1++;  
        
        if((e -= dy) <= 0) {
            y1 += step;   
            e += dx;
        }
    }
}

int main(int argc, char const *argv[])
{
    //tracer_droite(0,0,2,40);
    tracerSegment(0,0,2,40);
    return 0;
}
