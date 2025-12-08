#include "background.h"
#include <thread>

Background::Background(back_type type, int pos)
    :setting(type), position(pos), needsErased(false)
{
    if (type == base){
        base_png_1.Open("Background.100_Base.png");
        base_png_2.Open("Background.66_Base.png");
        base_png_3.Open("Background.33_Base.png");
    }
    else if(type == light){
        light_png_1.Open("Background.100_Light.png");
        light_png_2.Open("Background.66_Light.png");
        light_png_3.Open("Background.33_Light.png");
    }
    else if(type == light_t){
        light_t_png_1.Open("Background.100_L_to_M.png");
        light_t_png_2.Open("Background.66_L_to_M.png");
        light_t_png_3.Open("Background.33_L_to_M.png");
    }
    else if(type == mid){
        mid_png_1.Open("Bg.100_Mid.png");
        mid_png_2.Open("Bg.66_Mid.png");
        mid_png_3.Open("Bg.33_Mid.png");
    }
    else if(type == mid_t){
        mid_t_png_1.Open("Bg.100_M_to_D.png");
        mid_t_png_2.Open("Bg.66_M_to_D.png");
        mid_t_png_3.Open("Bg.33_M_to_D.png");
    }
    else if(type == moon){
        moon_png_1.Open("Bg.100_Dark_w_Moon.png");
        moon_png_2.Open("Bg.66_Dark_w_Moon.png");
        moon_png_3.Open("Bg.33_Dark_w_Moon.png");
    }
    else if(type == stars){
        stars_png_1.Open("Bg.100_Dark_w_Stars.png");
        stars_png_2.Open("Bg.66_Dark_w_Stars.png");
        stars_png_3.Open("Bg.33_Dark_w_Stars.png");
    }
    else if(type == stars_t){
        stars_t_png_1.Open("Bg.100_Dark_to_Space.png");
        stars_t_png_2.Open("Bg.66_Dark_to_Space.png");
        stars_t_png_3.Open("Bg.33_Dark_to_Space.png");
    }
    else if(type == space){
        space_png_1.Open("Bg.100_Space.png");
        space_png_2.Open("Bg.66_Space.png");
        space_png_3.Open("Bg.33_Space.png");
    }
}

void Background::changePosition(int move_y){
    position+=move_y;
}

void draw_task(FEHImage& png, int x, int y) {
    png.Draw(x, y);
}

void Background::drawBack(){
    if (setting == base) {
        std::thread t1(draw_task, std::ref(base_png_1), 0, position);
        std::thread t2(draw_task, std::ref(base_png_2), 0, position + 286);
        std::thread t3(draw_task, std::ref(base_png_3), 0, position + 572);

        t1.join();
        t2.join();
        t3.join();
    }

    else if(setting == light){
        std::thread t1(draw_task, std::ref(light_png_1), 0, position);
        std::thread t2(draw_task, std::ref(light_png_2), 0, position + 286);
        std::thread t3(draw_task, std::ref(light_png_3), 0, position + 572);

        t1.join();
        t2.join();
        t3.join();
    }

    else if(setting == light_t){
        std::thread t1(draw_task, std::ref(light_t_png_1), 0, position);
        std::thread t2(draw_task, std::ref(light_t_png_2), 0, position + 286);
        std::thread t3(draw_task, std::ref(light_t_png_3), 0, position + 572);

        t1.join();
        t2.join();
        t3.join();
    }
    else if(setting == mid){
        std::thread t1(draw_task, std::ref(mid_png_1), 0, position);
        std::thread t2(draw_task, std::ref(mid_png_2), 0, position + 286);
        std::thread t3(draw_task, std::ref(mid_png_3), 0, position + 572);

        t1.join();
        t2.join();
        t3.join();
        
    }
    else if(setting == mid_t){
        std::thread t1(draw_task, std::ref(mid_t_png_1), 0, position);
        std::thread t2(draw_task, std::ref(mid_t_png_2), 0, position + 286);
        std::thread t3(draw_task, std::ref(mid_t_png_3), 0, position + 572);

        t1.join();
        t2.join();
        t3.join();
    }
    else if(setting == moon){
        std::thread t1(draw_task, std::ref(moon_png_1), 0, position);
        std::thread t2(draw_task, std::ref(moon_png_2), 0, position + 286);
        std::thread t3(draw_task, std::ref(moon_png_3), 0, position + 572);

        t1.join();
        t2.join();
        t3.join();
    }
    else if(setting == stars){
        std::thread t1(draw_task, std::ref(stars_png_1), 0, position);
        std::thread t2(draw_task, std::ref(stars_png_2), 0, position + 286);
        std::thread t3(draw_task, std::ref(stars_png_3), 0, position + 572);

        t1.join();
        t2.join();
        t3.join();
    }
    else if(setting == stars_t){
        std::thread t1(draw_task, std::ref(stars_t_png_1), 0, position);
        std::thread t2(draw_task, std::ref(stars_t_png_2), 0, position + 286);
        std::thread t3(draw_task, std::ref(stars_t_png_3), 0, position + 572);

        t1.join();
        t2.join();
        t3.join();
    }
    else if(setting == space){
        std::thread t1(draw_task, std::ref(space_png_1), 0, position);
        std::thread t2(draw_task, std::ref(space_png_2), 0, position + 286);
        std::thread t3(draw_task, std::ref(space_png_3), 0, position + 572);

        t1.join();
        t2.join();
        t3.join();
    }

}

bool Background::get_erase(){
    return needsErased;
}

int Background::get_pos(){
    return position;
}
