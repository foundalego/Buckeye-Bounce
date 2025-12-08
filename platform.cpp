////////START OF platform.cpp///////

#include "platform.h"
#include "Game.h"
//#include "game_assets.h"
#include "FEHLCD.h"

//defualt constructor
platform::platform()
    :plat_type(normal), position_x(200), position_y(500), broken_state(false), width(60), height(20), moving_center(0), needs_erased(0), jumped(false), render(true), collide(true), frame(0)
    {
        if (plat_type == normal || plat_type == broken || plat_type == moving_x || plat_type == moving_y || moving_broken){
            width = 98;
            height = 15;
            
            //standard_plat_2.Open("Good_Platform2_Resize.png");
            
        }
        else if (plat_type == dissapearing || plat_type == futuristic_good || plat_type == futuristic_broken || plat_type == futuristic_moving){
            width = 50;
            height = 17;
            
        }
        else if (plat_type == spring)
        {
            width = 99;
            height == 17;
            // 99 wide
            // 24 tall
        }
        else if(plat_type == hole){
            width = 100;
            height = 100;
            //void 147 wide 144 tall
            //enemy dimensions
        }
        
        else{
           width = 77;
           height = 28;
           
        }
        evil_plat.Open("Evil_Platform_Resize.png");
        cloud_plat.Open("Cloud_Platform_Resize.png");
        lantern_l.Open("Spotted_Lanternfly_Face_Left.png");
        lantern_ld.Open("Spotted_Lanternfly_Face_Left_Down.png");
        lantern_r.Open("Spotted_Lanternfly_Face_Right.png");
        lantern_rd.Open("SpotFly_Right_Down.png");
        wings_r.Open("SpotFly_Wings_Right.png");
        wings_l.Open("SpotFly_Wings_Left.png");
        hole_png.Open("a_smaller_void.png");
        spring_png_1.Open("Springy_Platform1.png");
        spring_png_2.Open("Springy_Platform2.png");
        future_g.Open("Future_Platform_Good.png");
        future_b.Open("Future_Platform_Evil.png");
        standard_plat_1.Open("Good_Platform1_Resize.png");
        
        
    
    };
//constructor with x controllable, but not y
platform::platform(identity type, int x)
    :plat_type(type), position_x(x), position_y(500), broken_state(false), needs_erased(0), jumped(false), render(true), collide(true), frame(0)
    {
        if (plat_type == normal || plat_type == broken || plat_type == moving_x || plat_type == moving_y || plat_type == moving_broken){
            width = 98;
            height = 15;
            
            //standard_plat_2.Open("Good_Platform2_Resize.png");
            
        }
        else if (plat_type == dissapearing || plat_type == futuristic_good || plat_type == futuristic_broken || plat_type == futuristic_moving){
            width = 50;
            height = 17;
            cloud_plat.Open("Cloud_Platform_Resize.png");
            
        }
        else if(plat_type == hole){
            width = 100;
            height = 200;
            //void 147 wide 144 tall
            //enemy dimensions
        }
        //enemy dimensions
        else{
           width = 77;
           height = 28;
           
        }
        //intitial velocity for moving x platforms
        if (plat_type == moving_x || floating_bug || futuristic_moving  && position_x > 200){
            x_vel = -1;
        }
        else if(plat_type == moving_x || floating_bug || futuristic_moving  && position_x < 200){
            x_vel = 1;
        }

        if (plat_type == moving_broken || floating_bug || futuristic_moving  && position_x > 200){
            x_vel = -1;
        }
        else if(plat_type == moving_broken || floating_bug || futuristic_moving && position_x < 200){
            x_vel = 1;
        }
        cloud_plat.Open("Cloud_Platform_Resize.png");
        evil_plat.Open("Evil_Platform_Resize.png");
        lantern_l.Open("Spotted_Lanternfly_Face_Left.png");
        lantern_ld.Open("Spotted_Lanternfly_Face_Left_Down.png");
        lantern_r.Open("Spotted_Lanternfly_Face_Right.png");
        lantern_rd.Open("SpotFly_Right_Down.png");
        wings_r.Open("SpotFly_Wings_Right.png");
        wings_l.Open("SpotFly_Wings_Left.png");
        hole_png.Open("a_smaller_void.png");
        spring_png_1.Open("Springy_Platform1.png");
        spring_png_2.Open("Springy_Platform2.png");
        future_g.Open("Future_Platform_Good.png");
        future_b.Open("Future_Platform_Evil.png");
        standard_plat_1.Open("Good_Platform1_Resize.png");
        
    };
//constructor with x and y controllable
platform::platform(identity type, int x, int y)
    :plat_type(type), position_x(x), position_y(y), broken_state(false), needs_erased(0), jumped(false), render(true), collide(true), frame(0)
    {
        if (plat_type == normal || plat_type == broken || plat_type == moving_x || plat_type == moving_y || plat_type == moving_broken || plat_type == spring){
            width = 98;
            height = 15;
            
            //standard_plat_2.Open("Good_Platform2_Resize.png");
            
        }
        else if (plat_type == dissapearing || plat_type == futuristic_good || plat_type == futuristic_broken || plat_type == futuristic_moving){
            width = 50;
            height = 17;
            
            
        }
        else if(plat_type == hole){
            width = 100;
            height = 100;
            //void 147 wide 144 tall
            //enemy dimensions
        }
        //enemy dimensions
        else{
           width = 77;
           height = 28;
           
        }
        //intitial velocity for moving x platforms
        if (plat_type == moving_x || plat_type == floating_bug || plat_type == futuristic_moving  && position_x > 200){
            x_vel = -1;
        }
        else if(plat_type == moving_x || plat_type == floating_bug || plat_type == futuristic_moving  && position_x < 200){
            x_vel = 1;
        }

        if (plat_type == moving_x || plat_type == floating_bug || plat_type == futuristic_moving  && position_x > 200){
            x_vel = -1;
        }
        else if(plat_type == moving_x || plat_type == floating_bug || plat_type == futuristic_moving && position_x < 200){
            x_vel = 1;
        }
        evil_plat.Open("Evil_Platform_Resize.png");
        cloud_plat.Open("Cloud_Platform_Resize.png");
        lantern_l.Open("Spotted_Lanternfly_Face_Left.png");
        lantern_ld.Open("Spotted_Lanternfly_Face_Left_Down.png");
        lantern_r.Open("Spotted_Lanternfly_Face_Right.png");
        lantern_rd.Open("SpotFly_Right_Down.png");
        wings_r.Open("SpotFly_Wings_Right.png");
        wings_l.Open("SpotFly_Wings_Left.png");
        hole_png.Open("a_smaller_void.png");
        spring_png_1.Open("Springy_Platform1.png");
        spring_png_2.Open("Springy_Platform2.png");
        future_g.Open("Future_Platform_Good.png");
        future_b.Open("Future_Platform_Evil.png");
        standard_plat_1.Open("Good_Platform1_Resize.png");

       
    };
 
int platform::get_x(){
    return position_x;
}

int platform::get_y(){
    return position_y;
}

int platform::get_w(){
    return width;
}

int platform::get_h(){
    return height;
}

int platform::get_top(){
    return position_y - height;
}

identity platform::get_identity(){
    return plat_type;
}

bool platform::getCollide(){
    return collide;
}

bool platform::getRender(){
    return render;
}

//draw the correct image at the current posiiton
void platform::draw_platform(){
    if (plat_type == normal){
        standard_plat_1.Draw(position_x, position_y);
        //LCD.DrawRectangle(position_x + 2, position_y + 18, width, height);
    }
    else if(plat_type == broken){
        evil_plat.Draw(position_x, position_y);
        //LCD.DrawRectangle(position_x + 2, position_y + 25, width, height);
    }
    else if(plat_type == dissapearing){
        cloud_plat.Draw(position_x, position_y - (height + 8));
        //LCD.DrawRectangle(position_x + 16, position_y + 15, width, height);
    }
    else if(plat_type == moving_x){
        standard_plat_1.Draw(position_x, position_y);
        //LCD.DrawRectangle(position_x + 2, position_y + 18, width, height);
        
    }
    else if(plat_type == moving_broken){
        evil_plat.Draw(position_x, position_y);
        //LCD.DrawRectangle(position_x + 2, position_y + 18, width, height);
    }
    //bug on plat animation
    else if(plat_type == platform_with_bug){
        if (frame <= 25){
            lantern_r.Draw(position_x, position_y);
            frame++;
            //LCD.DrawRectangle(position_x, position_y, width, height);
        }
        else if(frame > 25 && frame <= 50){
            lantern_rd.Draw(position_x, position_y);
            frame++;
            //LCD.DrawRectangle(position_x, position_y, width, height);
        }
        else if(frame > 50 && frame <= 75){
            lantern_l.Draw(position_x, position_y);
            frame++;
            //LCD.DrawRectangle(position_x, position_y, width, height);
        }
        else if(frame > 75 && frame <= 100){
            lantern_ld.Draw(position_x, position_y);
            frame++;
            //LCD.DrawRectangle(position_x, position_y, width, height);
        }
        else if(frame > 100){
            frame = 0;
            //LCD.DrawRectangle(position_x, position_y, width, height);
        }
    }
    //bug by itself animation
    else if(plat_type == floating_bug){
        if (x_vel > 0){
            wings_r.Draw(position_x, position_y);
            //LCD.DrawRectangle(position_x, position_y + 45, width, height);
        }
        else{
            wings_l.Draw(position_x, position_y);
            //LCD.DrawRectangle(position_x, position_y + 45, width, height);
        }
    }
    else if(plat_type == spring){
        if (jumped){
            if(frame > 25){
                spring_png_1.Draw(position_x, position_y);
                frame++;
                //LCD.DrawRectangle(position_x, position_y, width, height);
            }
            else{
                spring_png_2.Draw(position_x, position_y);
                //LCD.DrawRectangle(position_x, position_y, width, height);
            }
        }
        spring_png_1.Draw(position_x, position_y);
        //LCD.DrawRectangle(position_x, position_y + 45, width, height);
    }
    else if(plat_type == hole){
        hole_png.Draw(position_x, position_y);
        //LCD.DrawRectangle(position_x, position_y, width, height);
    }
    else if(plat_type == futuristic_good){
        future_g.Draw(position_x, position_y);
        ///LCD.DrawRectangle(position_x + 20, position_y + 25, width, height);
    }
    else if(plat_type == futuristic_broken){
        future_b.Draw(position_x, position_y);
        //LCD.DrawRectangle(position_x, position_y, width, height);
    }
    else if(plat_type == futuristic_moving){
        future_g.Draw(position_x, position_y);
        //LCD.DrawRectangle(position_x, position_y, width, height);
    }
}


int platform::platform_update(){
    
    //sets the velocity of the moving platforms
    if (plat_type == moving_x || plat_type == moving_broken || plat_type == futuristic_moving){
        if (position_x + width >= 399){
            x_vel = -1;
        }
        if (position_x <= 0){
            x_vel = 1;
        }
        position_x+=x_vel;
    }
    //sets the initial velocity of a floating bug
    else if (plat_type == floating_bug){
        if (position_x + width >= 399){
            x_vel = -2;
        }
        if (position_x <= 0){
            x_vel = 2;
        }
        position_x+=x_vel;
    }

    //screen movment
    //if score has changed, move platforms by that much
    
    if (jumped){
        return manual_lerp(position_y, 650, 0.07);
    }
    return 0;
}


void platform::move_plat(int amount){
    position_y += amount;
}

//all non standard platfrom logic and erasing logic are housed in this
int platform::specialLogic(int collision, std::vector<platform>& plats, int index){
    if (needs_erased == 1){
        return 1;
    }
    //collision with broken platform
    if (collision == 2){
        //play_break_anim();
        needs_erased = 1;
        return 0;

    }
    else if (collision == 3){ //has collided with a dissapearing platform
        render = false;
        collide = false;
        return 0;
    }
    else if (collision == 4){ //has collided with an enemy (of any type)
        //checks for the next broken platform and turns it into a good platform?
        //then you run the risk of indexing errors, and also how do you get the other platforms in here -> pass them in by reference
        int size = plats.size();
        plats[index + 1].changeToGood();
        needs_erased = 1;
        return 0;
    }
    
    return 0;
}

//changes platform to a stable one, becuase you squashed a latnerfly
void platform::changeToGood(){
    plat_type = normal;
    jumped = !jumped;
}



void platform::check_bounds(){
    if (position_y >= LCD_HEIGHT - 20){
        needs_erased = 1; // if greater than screen height return 0 so it can be destroyed
    }
}

void platform::change_jump(){
    jumped = !jumped;
}

//linear interpolation is a method by which you get the distance along a straight line
//to an object by inputing the start, end, and the ratio of how far along you want to travel
//I made this using wikepedia, they have a 1d formula listed on their website
int platform::manual_lerp(int start, int end, float ratio){
    return (end - start)*ratio;
}

////////END OF platform.cpp///////
