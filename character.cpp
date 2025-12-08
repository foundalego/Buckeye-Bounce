////////START OF character.cpp///////

#include <character.h>
#include "FEHLCD.h"
#include "FEHSound.h"


character::character()
    :player_x(175), player_y(500), velocity_x(0), velocity_y(0), count(0), collide(true)
    {
        //get all character sprites for Brutus
        brutus_static.Open("Brutus_Static_Resize.png");
        brutus1.Open("Brutus_Jump1_Resize.png");
        brutus2.Open("Brutus_Jump2_Resize.png");
        brutus3.Open("Brutus_Jump3_Resize.png");

        //coudln't get sound to be efficient so I scrapped it - first thing to implement if I have more time
        
    }

int character::get_player_x(){
    return player_x;
}

int character::get_player_y(){
    return player_y;
}

//takes in the input from user and updates brutus's velocity
void character::velocity_update(int in){
    //right
    if (in == 100)
    {
        if (velocity_x < 20)
        {
            velocity_x+=0.7;
        }   
    }
    //left
    else if (in == 97)
    {
        if (velocity_x > -20)
        {
            velocity_x-=0.7;
        }
    }
    //up - this is a dev feature for easy testing
    else if (in == 119){
        velocity_y = -6;
    }
}

//this is used when player lands on a spring - collision is turned off and a frame 
//count timer is started that will just move him up
void character::spring_jump(){
    count = 150;
    velocity_y = -5;
    collide = false;
}

bool character::get_collide(){
    return collide;
}

//logic for player position
void character::position_update(){
    //gravity
    if (velocity_y < 6){
        velocity_y+=0.1;
    }
    //if player is above screen center then gravity increases
    if (player_y <= LCD_HEIGHT/2){
        velocity_y+=0.15;
    }
    //counteracts all gravity if spring has been jumped on
    if (count > 0){
        velocity_y-=0.2;
        count--;
        if (count <= 15){
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

//whenever brutus lands on a platform this is called, causing him to jump
void character::jump(int num){
    velocity_y = -1*num;
    //FEHSound jump("jump.wav");
    //jump.play();
}

//this is called when the player dies, and just makes the player move off of the screen
void character::end_animation(){
    velocity_y = 16;
    player_y += velocity_y;
}

//draws brutus at the correct location, and changes depnding on if hes going up or down
void character::draw_player(){
    if (velocity_y < 0){
        brutus1.Draw(player_x, player_y);
    }
    else if (velocity_y > 0){
        brutus2.Draw(player_x, player_y);
    }
    //show hitbox by uncommenting next line
    //LCD.DrawRectangle(player_x + 27, player_y + 8, WIDTH, HEIGHT);
}

float character::get_vel_y(){
    return velocity_y;
}

//after player has died it resets his values that way nothing transfers over from the last run
void character::reset(){
    player_x = 175;
    player_y = 500;
    velocity_x = 0;
    velocity_y = 0;
}

////////END OF character.cpp///////
