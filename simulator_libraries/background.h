/////////START OF background.h//////////////

#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "FEHImages.h"

enum back_type{
    base,
    light,
    light_t,
    mid,
    mid_t,
    moon,
    stars,
    stars_t,
    space
};

class Background{
    
    public:
    Background(back_type type, int pos);
    void changePosition(int move_y);
    void drawBack();
    int get_pos();
    bool get_erase();
    private:
    back_type setting;
    int position;
    bool needsErased;
    //all images classes
    FEHImage base_png_1, base_png_2, base_png_3, light_png_1, light_png_2, light_png_3, light_t_png_1, light_t_png_2, light_t_png_3,
     mid_png_1,mid_png_2, mid_png_3, mid_t_png_1, mid_t_png_2, mid_t_png_3, moon_png_1, moon_png_2, moon_png_3, stars_png_1, stars_png_2, stars_png_3, stars_t_png_1,
     stars_t_png_2, stars_t_png_3, space_png_1, space_png_2, space_png_3;
};

#endif

/////////END OF background.h//////////////
