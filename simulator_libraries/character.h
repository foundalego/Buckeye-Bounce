////////START OF character.h///////

#ifndef CHARACTER_H
#define CHARACTER_H

#define WIDTH 45 //correct
#define HEIGHT 45 //correct
#include "platform.h"
#include "FEHImages.h"

class character{
    public:
        //functions to access player positions
        int get_player_x();
        int get_player_y();
        //function to take in an input and execute->will probably have other functions nested inside
        void velocity_update(int in);
        //need a function to handle checking input and to make motion smooth
        float get_vel_y();
        void jump(int num);
        void position_update();
        void draw_player();
        void reset();
        void spring_jump();
        void end_animation();
        bool get_collide();
        //constructor
        character();
    private:
    //player position is private to prevent unintended motion
    int player_x;
    int player_y;
    int count;
    //player velocity
    float velocity_y;
    float velocity_x;
    bool collide;
    FEHImage brutus_static, brutus1, brutus2, brutus3;
};


#endif

////////END OF character.h///////
