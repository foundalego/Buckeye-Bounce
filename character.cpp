#include <character.h>
#include "FEHLCD.h"

character::character()
//get all character sprites for Brutus
    :player_x(200), player_y(500), velocity_x(0), velocity_y(0), count(0), collide(true)
    {
        brutus_static.Open("Brutus_Static_Resize.png");
        brutus1.Open("Brutus_Jump1_Resize.png");
        brutus2.Open("Brutus_Jump2_Resize.png");
        brutus3.Open("Brutus_Jump3_Resize.png");
    }

int character::get_player_x(){
    return player_x;
}

int character::get_player_y(){
    return player_y;
}
void character::velocity_update(int in){
    if (in == 100)
    {
        if (velocity_x < 20)
        {
            velocity_x+=0.7;
        }   
    }
    else if (in == 97)
    {
        if (velocity_x > -20)
        {
            velocity_x-=0.7;
        }
    }
    else if (in == 119){
        velocity_y = -6;
    }
}

void character::spring_jump(){
    count = 150;
    velocity_y = -5;
    collide = false;
}

bool character::get_collide(){
    return collide;
}

void character::position_update(){
    //gravity
    if (velocity_y < 6){
        velocity_y+=0.1;
    }
    //if player is above screen center then gravity increases
    if (player_y <= LCD_HEIGHT/2){
        velocity_y+=0.2;
    }
    //counteracts all gravity if spring has been jumped on
    if (count > 0){
        velocity_y-=0.2;
        count--;
        if (count == 0){
            collide = true;
        }
    }
    player_y+=velocity_y; //update player height for this tick
    //left and right decelleration
    if (velocity_x > 0.5){
        velocity_x-=0.1*velocity_x;
        player_x+=velocity_x;
    }
    else if(velocity_x < -0.5){
        velocity_x-=0.1*velocity_x;
        player_x+=velocity_x;
    }
    else if(velocity_x > -0.5 || velocity_x < 0.5){
        velocity_x = 0;
    }

    //loop to get player to move across sides
    if (player_x >= LCD_WIDTH - WIDTH/2){
        player_x = 0 - WIDTH/2;
    }
    else if(player_x <= -WIDTH/2){
        player_x = LCD_WIDTH - WIDTH/2;
    }
    

}

void character::jump(int num){
    velocity_y = -1*num;
}

void character::end_animation(){
    velocity_y = 20;
    player_y += velocity_y;
}
//establish animations based on velocity
void character::draw_player(){
    if (velocity_y < 0){
        brutus1.Draw(player_x, player_y);
    }
    else if (velocity_y > 0){
        brutus2.Draw(player_x, player_y);
    }
    //brutus_static.Draw(player_x, player_y);
}

float character::get_vel_y(){
    return velocity_y;
}

void character::reset(){
    player_x = 200;
    player_y = 500;
    velocity_x = 0;
    velocity_y = 0;

}
