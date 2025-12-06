////////START OF platform.h///////

#ifndef PLATFORM_H
#define PLATFORM_H

#include <vector>
#include "FEHImages.h"

//types of platforms
enum identity {
    normal,
    dissapearing, //breaks after 1 jump
    broken, //will break instead of providing thrust
    moving_x, //moves in the x direction
    moving_y, //moves in the y direction
    floating_bug, //a bug floating in midair
    platform_with_bug, //a platform with a bug on top of it
    moving_broken, //moves but breaks instead of providing thrust
    futuristic_good, //normal platform only spawns in space section
    futuristic_broken, //broken platform only spawns in space section
    hole, //immediately ends game
    spring //gets rid of gravity temporarily
};

class platform{
    private:
    //what type of platform is it?
    identity plat_type;
    //position variables for collision
    int position_x, position_y;
    float x_vel, y_vel;
    int height;
    int width;
    int frame;
    int moving_center;
    int needs_erased; // not boolean so that can be incremented for timing purposes
    bool jumped; //if has been jumped on and is in the process of moving this will be true
    bool broken_state;//state of whether or not platform has been broken
    bool render; //if true will render the platform, otherwise nothing will be drawn
    bool collide; //if ture collisions will be detected

    public:
    void change_jump();
    int get_top(), get_x(), get_y(), get_h(), get_w(); //functions to return private variables
    void move_plat(int amount);
    void check_bounds();
    void draw_platform();
    void play_break_anim();
    int platform_update(); //reuturns pixels to move all platforms by if one has been jumped on
    int specialLogic(int collision, std::vector<platform>& plats);
    bool getRender();
    bool getCollide();
    identity get_identity(); //returns identity
    int manual_lerp(int start, int end, float ratio);
    void changeToGood();
    platform();
    platform(identity type, int position);
    platform(identity type, int position, int height);
    FEHImage standard_plat_1, cloud_plat, evil_plat, lantern_r, lantern_rd, lantern_l, lantern_ld, wings_r, 
    wings_l, hole_png, spring_png_1, spring_png_2, future_g, future_b;
};

#endif


////////END OF platform.cpp///////
