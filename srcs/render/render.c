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
    return (1);
}