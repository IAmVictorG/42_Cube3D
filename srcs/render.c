#include "../header.h"

int render(t_general *general)
{
    clock_t	t;

    t = clock();

    t = clock() - t;


    if (general->scene->mini_map)
    {
        render_mini_map(general);
    }
    else
    {
        render_game(general);
    }
    (void) t;

    //printf("IMAGE RENDERING %lu ms\n", t);
    //mlx_string_put(general->mlib->utils.mlx, general->mlib->utils.win, 300, 200, 0xFFFFFF, "FPS ");
    return (1);
}