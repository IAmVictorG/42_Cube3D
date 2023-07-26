#ifndef RENDER_H
# define RENDER_H

#include "../../header.h"

void    ne_near(t_general *general, t_tab tab, int imageincre, int dist);
void    nw_near(t_general *general, t_tab tab, int imageincre, int dist);
void    se_near(t_general *general, t_tab tab, int imageincre, int dist);
void    sw_near(t_general *general, t_tab tab, int imageincre, int dist);

void    ne(t_general *general, t_tab tab, int imageincre, int dist);
void    nw(t_general *general, t_tab tab, int imageincre, int dist);
void    se(t_general *general, t_tab tab, int imageincre, int dist);
void    sw(t_general *general, t_tab tab, int imageincre, int dist);

#endif