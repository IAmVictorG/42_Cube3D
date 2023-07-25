#include "../header.h"

int render(t_general *general)
{
    clock_t	t;

    t = clock();

    general->time = t;
    if (general->scene->mini_map)
    {
        render_mini_map(general);
    }
    else
    {
        render_game(general);
    }
    (void) t;
    t = clock() - t;
    t /= 1000;
    //printf("IMAGE RENDERING %lu ms\n", t);
    //mlx_string_put(general->mlib->utils.mlx, general->mlib->utils.win, 300, 200, 0xFFFFFF, "FPS ");
    return (1);
}