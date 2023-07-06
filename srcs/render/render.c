#include "../../header.h"

int render(t_general *general)
{

    if (general->scene->mini_map)
    {
        render_mini_map(general);
    }
    else
    {
        render_game(general);
    }

    //mlx_string_put(general->mlib->utils.mlx, general->mlib->utils.win, 300, 200, 0xFFFFFF, "FPS ");
    return (1);
}