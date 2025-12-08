////////START OF Game.cpp///////

#include "Game.h"
#include <thread>
#include "FEHLCD.h"
#include "FEHKeyboard.h"
#include "FEHImages.h"
#include <chrono>
#include "FEHRandom.h" 
#include <iostream>

// game constructor
Game::Game()
    :gameover(false), exit(false), orderCount(0), springed(0){
        order = {light, light, light, light, light, light, light, light,  // 8
                light_t, mid, mid, mid, mid, mid, mid, mid, mid, mid, mid, mid, mid, //13
                mid_t, moon, stars, stars, stars, stars, stars, stars, //8
                stars, stars, stars, stars, stars, stars, stars_t, space}; //7
         //Open the appropriate images in correspondence with their pages
        how_to.Open("How_To_Button_Resize.png");
        play.Open("Play_Button_Resize.png");
        stats.Open("Stats_Button_Resize.png");
        credits.Open("Credits_Button_Resize.png");
        background.Open("Background_Base_with_Shoe.png");
        close.Open("Close_Button_Resize.png");
        banner.Open("Game_Header_Banner.png");
        logo.Open("Logo.png");
        brutus.Open("Brutus_Static_Resize.png");
        bug_1.Open("Spotted_Lanternfly_Face_Right.png");
    }

//main menu function that controls overarching gameplay    
void Game::Menu(){
    while (!exit){
        LCD.Clear(BLACK);
        background.Draw(0,0);
        logo.Draw(50, 40);
        how_to.Draw(140,450);
        brutus.Draw(250, 45);
        play.Draw(140,350);
        bug_1.Draw(20, 435);
        stats.Draw(20,450);
        credits.Draw(260,450);
        close.Draw(0,0);
        LCD.Update();
        while(!LCD.Touch(&mouse_x, &mouse_y));
        //if mouse was clicked on play
        if (mouse_x > 140 &&
            mouse_x < 240 &&
            mouse_y > 350 &&
            mouse_y < 400)  
        {
            Run();
        }
        //if mouse was clicked on stats
        else if (mouse_x > 20 &&
                mouse_x < 120 &&
                mouse_y > 450 &&
                mouse_y < 500)
        {
            Stats();
        }
        //if mouse was clicked on credits
        else if (mouse_x > 140 &&
                mouse_x < 240 &&
                mouse_y > 450 &&
                mouse_y < 500)
        {
            HowTo();    
        }
        //if mouse was clicked on how to
        else if (mouse_x > 260 &&
                mouse_x < 360 &&
                mouse_y > 450 &&
                mouse_y < 500)
        {
            Credits();
        }
        //if exit was clicked
        else if (mouse_x > 20 &&
                mouse_x < 80 &&
                mouse_y > 20 &&
                mouse_y < 80)
        {
            exit = !exit;
        }
        Sleep(100);
    }
}



// function to start eveyrthing
void Game::Run(){
    //first couple platform loop
    for (int i = 0; i < 8; i++)
    {
        AddPlatform(normal, (Random.RandInt()%320 + 10), i*100);
    }
    AddPlatform(normal, 175, 800);
    //run first frame
    Input();
    Logic();
    addBackground(base, 0);
    addBackground(light, -858);
    //altered render function
        LCD.Clear();
        drawBackground();
        drawPlatforms();
        dood.draw_player();
        banner.Draw(0,0);
        s1.print_score();
        LCD.WriteAt("LOADING...", 120, 370);
        LCD.Update();
    //then load all the platforms
    Initialize();
    //another altered render function
        LCD.Clear();
        drawBackground();
        drawPlatforms();
        dood.draw_player();
        banner.Draw(0,0);
        s1.print_score();
        LCD.WriteAt("CLICK TO START", 120, 370);
        LCD.Update();
    while(!LCD.Touch(&mouse_x, &mouse_y));
    while(!gameover){
        Input();
        Logic();
        Render_all();
        //Sleep(10); //slow mode
    }
    endScreen();
    Shutdown();
    
}

//Stats page
void Game::Stats(){
    while(!exit){
        Sleep(100);
        LCD.Clear(); 
        background.Draw(0,0);
        logo.Draw(50, 40);
        LCD.SetFontScale(2.0);
        LCD.WriteAt("HIGH SCORES:", 50, 225);
        LCD.SetFontScale(2.0);
        s1.drawScores();
        close.Draw(300,800);
        LCD.Update();
        while (!LCD.Touch(&mouse_x, &mouse_y));
        if (mouse_x > 320 &&
            mouse_x < 380 &&
            mouse_y > 820 &&
            mouse_y < 860){
            exit = !exit;
        }
    }
    exit = !exit;
}
//establish credits page
void Game::Credits(){
    while(!exit){
        Sleep(100);
        LCD.Clear();  
        background.Draw(0,0);
        logo.Draw(50, 40);
        LCD.SetFontScale(1.5);
        LCD.WriteAt("Software development:", 10, 300);
        LCD.SetFontScale(2.0);
        LCD.WriteAt("Ben Coughlin", 50, 350);
        LCD.SetFontScale(1.5);
        LCD.WriteAt("Creative Director:", 30, 450);
        LCD.SetFontScale(2.0);
        LCD.WriteAt("Sophie Subit", 50, 500);
        close.Draw(300,800);
        LCD.Update();
        while (!LCD.Touch(&mouse_x, &mouse_y));
        if (mouse_x > 320 &&
            mouse_x < 380 &&
            mouse_y > 820 &&
            mouse_y < 860){
            exit = !exit;
        }
    }
    exit = !exit;
}
//establish instructions page
void Game::HowTo(){
    while(!exit){
        Sleep(100);
        LCD.Clear();
        background.Draw(0,0);
        logo.Draw(50, 40);
        LCD.SetFontScale(1.5);
        LCD.WriteAt("Goal: Climb as high ", 10, 300);
        LCD.WriteAt("as you can!", 140, 325);
        LCD.WriteAt("Controls:", 10, 360);
        LCD.WriteAt("A or Left Arrow", 60, 395);
        LCD.WriteAt("for left", 110, 425);
        LCD.WriteAt("D or Right Arrow", 60, 470);
        LCD.WriteAt("for left", 110, 495);
        LCD.WriteAt("Watch out for any", 30, 540);
        LCD.WriteAt("invasive lantern bugs!", 5, 565);
        LCD.WriteAt("(or faulty platforms)", 18, 592);

        close.Draw(300,800);
        LCD.Update();
        while (!LCD.Touch(&mouse_x, &mouse_y));
        if (mouse_x > 320 &&
            mouse_x < 380 &&
            mouse_y > 820 &&
            mouse_y < 860){
            exit = !exit;
        }
    }
    exit = !exit;
}

// loads screen
void Game::Initialize(){
    //seed RNG
    Random.Seed();
    //generation loop
    for (int i = 0; i < 30; i++){
        pickSection(i);
        LCD.FillRectangle(120, 390, i*5, 7);
        LCD.Update();
    }
}
// take user input
void Game::Input(){
    int ch;
    if (Keyboard.isPressed(KEY_A) || Keyboard.isPressed(KEY_LEFT)){
        ch = 97;
    }
    else if(Keyboard.isPressed(KEY_D) || Keyboard.isPressed(KEY_RIGHT)){
        ch = 100;
    }
    //uncomment if you want to enable dev feature or flying
    /*else if(Keyboard.isPressed(KEY_W) || Keyboard.isPressed(KEY_UP)){
        ch = 119;
    }*/
    else if(Keyboard.isPressed(KEY_ESCAPE)){
        ch = 27;
    }
    //ch = Keyboard.lastChar();
    dood.velocity_update(ch);
    if (ch == 27){
        SetGameOverTrue();
    }
}
// all logic (colisions, positions,  velcoity, input interface)
void Game::Logic(){
    int size = all_plats.size();
    int move_pixels = 0;
    //loop to get pixels to move screen by
    //if a spring has been jumped on then we just base the movement off of that
    //otherwise need platforms to move at the equal and opposite velocity to give illusion of screen moving
    if (springed == 0){
        for (int i = 0; i < size; i++)
        {
            int a = all_plats[i].platform_update();
            if ( a > 0 && a > move_pixels){
                move_pixels = a;
            }
        }
    }
    else{
        move_pixels = springed/10;
        springed--;
    }
    for (int i = 0; i < size; i++){
        all_plats[i].move_plat(move_pixels);
        if (all_plats[i].specialLogic(checkPlatCollision(all_plats[i]), all_plats, i) == 1){ //if 1 is returned by special logic then the current platform must be destroyed
            all_plats.erase(all_plats.begin() + i);
        }
        else{
            all_plats[i].check_bounds();
        }
    }
    //loop to move background
    for (int i = 0; i < all_backs.size(); i++){
        //if needs erased erase otherwise change position
        if (all_backs[i].get_pos() > 860){
            //if in the preset order of backgrounds create the next background when the previous one leaves the screen
            if (orderCount < 37){
                addBackground(order[orderCount], (all_backs[i].get_pos() - (2*LCD_HEIGHT) + 5));
                //if pre-loaded generation runs out start generating as you go
                if (orderCount >= 29){
                    pickSection(orderCount);
                }
                orderCount++;
                
            }
            //if it has gone above the preset order just generate a space background
            else{
                addBackground(space, (all_backs[i].get_pos() - (2*LCD_HEIGHT) + 5));
                //if pre-loaded generation runs out start generating as you go
                if (orderCount >= 29){
                    pickSection(orderCount);
                    orderCount++;
                }
            }

            
            //delete background that has left the screen
            all_backs.erase(all_backs.begin() + i);
        }
        all_backs[i].changePosition(move_pixels);
    }
    s1.update_score(move_pixels);
    dood.position_update();
    isGameOver();
}

//In the event that the character falls:
void Game::isGameOver(){
    if (dood.get_player_y() > 850){
        SetGameOverTrue();
    }
}
// draw to screen
void Game::Render_all(){
    LCD.Clear();
    drawBackground();
    drawPlatforms();
    dood.draw_player();
    banner.Draw(0,0);
    s1.print_score();
    LCD.Update();
}


void Game::endScreen(){
    //two sections 1. to clear the platoforms off the screen smoothly and 2. to get players intials and ask them to play again or not
    //section 1
    float time = 0;
    while(time < 5){
        int size = all_plats.size();
        for (int i = 0; i < size; i++){
            all_plats[i].move_plat(-20);
        }
        dood.end_animation();
        Render_all();
        Sleep(10);
        time += 0.1;
    }
    //bring in game over text and text prompting user for their name
    time = 0;
    
    while(time < 3){
        LCD.Clear();
        drawBackground();
        LCD.SetFontScale(2.0);
        
        if (time > 0.5){
            LCD.WriteAt("GAME", 5 + time * 50, 300);
        }
        LCD.WriteAt("OVER", 150, LCD_HEIGHT - time*170);
        LCD.SetFontScale(1.0);
        banner.Draw(0,0);
        s1.print_score();
        LCD.Update();
        time+=0.1;
        Sleep(10);
    }
    //bring in more text
    time = 0;
    while(time < 2){
        LCD.Clear();
        drawBackground();
        LCD.SetFontScale(2.0);
        LCD.WriteAt("GAME", 150, 300);
        LCD.WriteAt("OVER", 150, 350);
        LCD.SetFontScale(1.5);
        LCD.WriteAt("ENTER INITIALS:", 30, LCD_HEIGHT - time*200);
        LCD.SetFontScale(1.0);
        if(time > 0.5){
            LCD.WriteAt("(HIT 0 WHEN FINISHED)", 50, LCD_HEIGHT + 50 - time*200);
        }
        LCD.SetFontScale(1.0);
        banner.Draw(0,0);
        s1.print_score();
        LCD.Update();
        time+=0.1;
        Sleep(10);
    }
    std::string name = {""};
    char ch = Keyboard.lastChar();
    ch = 0;
    //get user input on their name
    while (ch != 48)
    {
        ch = Keyboard.lastChar();
        if(ch == 48 && name.length() == 3){
            ch = 48;
        }
        else{
            ch -= 32;
        }

        if(ch > 65){
            name += ch;
        }

        if(name.length() > 3){
            name = "";
        }
        LCD.Clear();
        drawBackground();
        LCD.SetFontScale(2.0);
        LCD.WriteAt("GAME", 150, 300);
        LCD.WriteAt("OVER", 150, 350);
        LCD.SetFontScale(1.5);
        LCD.WriteAt("ENTER INITIALS:", 30, 460);
        LCD.WriteAt(name, 300, 460);
        LCD.SetFontScale(1.0);
        LCD.WriteAt("(HIT 0 WHEN FINISHED)", 50, 510);
        banner.Draw(0,0);
        s1.print_score();
        LCD.Update();
        time+=0.1;
        Sleep(10);
        
    }
    s1.set_score_name(name);
    
}

// correctly close files and resets the game
void Game::Shutdown(){
    gameover = !gameover;
    s1.reset_score();
    dood.reset();
    all_plats.clear();
    all_backs.clear();
    LCD.SetFontScale(1.0);
    orderCount = 0;
}

//ends game
void Game::SetGameOverTrue(){
    gameover = true;
}

//first it checks what platform type it checking collisions with, then checks collision
int Game::checkPlatCollision(platform& plat){
    //check if collision has been turned off for the current platform
    if (!plat.getCollide()){
        return 0;
    }

    if (!dood.get_collide()){
        return 0;
    }
    

    //void collision logic
    else if (plat.get_identity() == hole){
        //top left corner of player is in void
        if (dood.get_player_x() + 27 > plat.get_x() && 
            dood.get_player_x() + 27< plat.get_x() + plat.get_w() && 
            dood.get_player_y() + 8>= plat.get_y() &&
            dood.get_player_y() + 8 <= plat.get_y() + plat.get_h())
        {
            SetGameOverTrue();
        }
        //top right corner is in void
        else if 
            (dood.get_player_x() + 27 + 45 > plat.get_x() && 
            dood.get_player_x() + 27 + 45 < plat.get_x() + plat.get_w() && 
            dood.get_player_y() + 8>= plat.get_y() &&
            dood.get_player_y() + 8 <= plat.get_y() + plat.get_h())
        {
            SetGameOverTrue();
        }

        //bottom left corner collision
        else if 
            (dood.get_player_x() + 27 + 45> plat.get_x() && 
            dood.get_player_x() + 27 + 45< plat.get_x() + plat.get_w() && 
            dood.get_player_y() + 8 + 45>= plat.get_y() &&
            dood.get_player_y() + 8 + 45<= plat.get_y() + plat.get_h())
        {
            SetGameOverTrue();
        }
        else if 
            (dood.get_player_x() + 27 > plat.get_x() && 
            dood.get_player_x() + 27< plat.get_x() + plat.get_w() && 
            dood.get_player_y() + 8 + 45>= plat.get_y() &&
            dood.get_player_y() + 8 + 45<= plat.get_y() + plat.get_h())
        {
            SetGameOverTrue();
        }
        
    }
    

    //spirng collision logic
    else if(plat.get_identity() == spring){
        if (dood.get_player_x() + 45 > plat.get_x() - 25 && 
            dood.get_player_x() + 45 < plat.get_x() + plat.get_w() - 25 && 
            dood.get_player_y() + 45 >= plat.get_y() &&
            dood.get_player_y() + 45 <= plat.get_y() + 7 &&
            dood.get_vel_y() > 0)
            {
                springed = 160;
                dood.spring_jump();
            return 5;
        }
        else if (
            dood.get_player_x() > plat.get_x() - 27 && 
            dood.get_player_x() < plat.get_x() + plat.get_w() - 27 && 
            dood.get_player_y() + 45 >= plat.get_y() &&
            dood.get_player_y() + 45 <= plat.get_y() + 7 &&
            dood.get_vel_y() > 0)
            {
                springed = 160;
                dood.spring_jump();
            return 5;
        }
    }

    //dissapearing platform collision logic
    
    else if (plat.get_identity() == dissapearing){
        if (dood.get_player_x() + 45 > plat.get_x() && 
            dood.get_player_x() + 45 < plat.get_x() + plat.get_w() && 
            dood.get_player_y() + 45 >= plat.get_y() &&
            dood.get_player_y() + 45 <= plat.get_y() + 7 &&
            dood.get_vel_y() > 0)
        {
            plat.change_jump();
            dood.jump(6);
            return 3;
        }
        else if (
            dood.get_player_x() > plat.get_x() && 
            dood.get_player_x() < plat.get_x() + plat.get_w() && 
            dood.get_player_y() + 45 >= plat.get_y() &&
            dood.get_player_y() + 45 <= plat.get_y() + 7 &&
            dood.get_vel_y() > 0)
        {
            plat.change_jump();
            dood.jump(6);
            return 3;
        }
    }

    //enemy and enemy platform collision logic
    else if(plat.get_identity() == floating_bug || plat.get_identity() == platform_with_bug){
        //logic if player is travelling down

        ///////RIGHT EDGE + GOING DOWN//////
        if (dood.get_player_x() + 45 + 27> plat.get_x() && 
            dood.get_player_x() + 45 + 27 < plat.get_x() + plat.get_w() && 
            dood.get_player_y() + 45 >= plat.get_y() &&
            dood.get_player_y() + 45 <= plat.get_y() + 7 &&
            dood.get_vel_y() > 0)
            {
            //here is where the death of enemy logic would be
            //if player is heading downwards and collides the bug is squashed
            springed = 40;
            //plat.change_jump();
            dood.jump(6);
            return 4;
            
            //otherwise the player is heading upwards and the bug kills them
        }
        //////LEFT EDGE + GOING DOWN//////
        else if (
            dood.get_player_x() + 27> plat.get_x() && 
            dood.get_player_x() + 27< plat.get_x() + plat.get_w() && 
            dood.get_player_y() + 45 >= plat.get_y() &&
            dood.get_player_y() + 45 <= plat.get_y() + 7 &&
            dood.get_vel_y() > 0)
            {
            //here is where the death of enemy logic would be
            //if player is heading downwards and collides the bug is squashed
            springed = 40;
            //plat.change_jump();
            dood.jump(6);
            return 4;
        }


        ///////RIGHT EDGE + GOING UP//////
        if (dood.get_player_x() + 45 + 27 > plat.get_x() && 
            dood.get_player_x() + 45 + 27< plat.get_x() + plat.get_w() && 
            dood.get_player_y() >= plat.get_y() +  plat.get_h()&&
            dood.get_player_y() <= plat.get_y() + 7 +  plat.get_h() &&
            dood.get_vel_y() < 0)
            {
            //here is where the death of enemy logic would be
            //if player is heading downwards and collides the bug is squashed
            
            SetGameOverTrue();
            
            //otherwise the player is heading upwards and the bug kills them
        }

        ///////LEFT EDGE + GOING UP//////
        else if (
            dood.get_player_x() + 27> plat.get_x() && 
            dood.get_player_x() + 27< plat.get_x() + plat.get_w() && 
            dood.get_player_y() >= plat.get_y() +  plat.get_h()&&
            dood.get_player_y() <= plat.get_y() + 7 +  plat.get_h()&&
            dood.get_vel_y() < 0)
            {
            //here is where the death of enemy logic would be
            //if player is heading downwards and collides the bug is squashed
            
            SetGameOverTrue();
        }
    }
    //future platform collision logic (because of the smaller hitboxes)
    else if(plat.get_identity() == futuristic_broken || plat.get_identity() == futuristic_good){
        if (dood.get_player_x() + 45 > plat.get_x() - 10 && 
            dood.get_player_x() + 45 < plat.get_x() + plat.get_w() - 10 && 
            dood.get_player_y() + 35 >= plat.get_y() &&
            dood.get_player_y() + 35 <= plat.get_y() + 7 &&
            dood.get_vel_y() > 0)
            {
                if(plat.get_identity() == futuristic_broken){
                    return 2;
                }
            plat.change_jump();
            dood.jump(6);
            return 1;
        }
        else if (
            dood.get_player_x() > plat.get_x() - 10 && 
            dood.get_player_x() < plat.get_x() + plat.get_w() - 10 && 
            dood.get_player_y() + 35 >= plat.get_y() &&
            dood.get_player_y() + 35 <= plat.get_y() + 7 &&
            dood.get_vel_y() > 0)
            {
                if(plat.get_identity() == futuristic_broken){
                    return 2;
                }
            dood.jump(5);
            plat.change_jump();
            return 1;
        }
    }
    //normal AABB collision for all other platforms
    else{
        if (dood.get_player_x() + 45 > plat.get_x() - 25 && 
            dood.get_player_x() + 45 < plat.get_x() + plat.get_w() - 25 && 
            dood.get_player_y() + 45 >= plat.get_y() &&
            dood.get_player_y() + 45 <= plat.get_y() + 7 &&
            dood.get_vel_y() > 0)
            {
                if(plat.get_identity() == broken || plat.get_identity() == moving_broken || plat.get_identity() == futuristic_broken){
                    return 2;
                }
            plat.change_jump();
            dood.jump(6);
            return 1;
        }
        else if (
            dood.get_player_x() > plat.get_x() - 27 && 
            dood.get_player_x() < plat.get_x() + plat.get_w() - 27 && 
            dood.get_player_y() + 45 >= plat.get_y() &&
            dood.get_player_y() + 45 <= plat.get_y() + 7 &&
            dood.get_vel_y() > 0)
            {
                if(plat.get_identity() == broken || plat.get_identity() == moving_broken || plat.get_identity() == futuristic_broken){
                    return 2;
                }
            dood.jump(5);
            plat.change_jump();
            return 1;
        }
    }
    //if it has reached this point no collision has occured and return 0
    return 0;
}

//calls draw function for all platforms within LCD screen boundary
void Game::drawPlatforms(){
    int size = all_plats.size();
    for (int i = 0; i < size; i++){
        if (all_plats[i].get_y() > 0 && all_plats[i].get_y() < LCD_HEIGHT - 20 && all_plats[i].getRender() == true)
        {
            all_plats[i].draw_platform();
        }
    }
}

//calls draw function for all backgrounds within LCD screen boundary
void Game::drawBackground(){
    for (int i = 0; i < all_backs.size(); i++){
        all_backs[i].drawBack();
    }
}

//adds a background to the all_backs vector
void Game::addBackground(back_type type, int pos){
    all_backs.emplace_back(type, pos);
}

//adds a platform to the all_plats vector
void Game::AddPlatform(identity type, int x, int y){
    all_plats.emplace_back(type, x, y); 
}

//randomly picks a section to generate
// 12/6/25 note - extremely inefficent but idk how to get the assets to be extern variables and 
//im giving up so im just gonna load all of them at the start of the game, so this is def an area to imporve upon
void Game::pickSection(int screenNumber){
    int a = Random.RandInt()%1000 + screenNumber*7;
    if (a >= 0 && a <= 500){
        genericSection(screenNumber);
        std::cout << "1\n";
    }
    else if(a > 470 && a <= 485){
        spring1(screenNumber);
        std::cout << "2\n";
    }
    else if(a > 485 && a <= 500){
        spring2(screenNumber);
        std::cout << "3\n";
    }
    else if(a > 500 && a <= 550){
        movingSection(screenNumber);
        std::cout << "4\n";
    }
    else if(a > 550 && a <= 575){
        mover2(screenNumber);
        std::cout << "5\n";
    }
    else if(a > 575 && a <= 600){
        mover3(screenNumber);
        std::cout << "6\n";
    }
    else if(a > 600 && a <= 625){
        hardSection(screenNumber);
        std::cout << "7\n";
    }
    else if(a > 625 && a <= 675){
        dissapearingSection(screenNumber);
        std::cout << "8\n";
    }
    else if(a > 675 && a <= 700){
        obstacle1(screenNumber);
        std::cout << "9\n";
    }
    else if(a > 700 && a <= 710){
        obstacle2(screenNumber);
        std::cout << "10\n";
    }
    else if(a > 710 && a <= 730){
        bugSection1(screenNumber);
        std::cout << "11\n";
    }
    else if(a > 730 && a <= 750){
        bugSection2(screenNumber);
        std::cout << "12\n";
    }
    else if(a > 750 && a <= 770){
        bugSection3(screenNumber);
        std::cout << "13\n";
    }
    else if(a > 770 && a <= 790){
        bugSection4(screenNumber);
        std::cout << "14\n";
    }
    else if(a > 790 && a <= 850){
        brokenSection(screenNumber);
        std::cout << "15\n";
    }
    else if(a > 850 && a <= 860){
        bugApocalypse(screenNumber);
        std::cout << "16\n";
    }
    else if(a > 860 && a <= 900){
        brokenFuture(screenNumber);
        std::cout << "17\n";
    }
    else if(a > 900 && a <= 1000){
        futureSection(screenNumber);
        std::cout << "18\n";
    }
    else if(a > 1000){
        futureMovers(screenNumber);
        std::cout << "19\n";
    }
}

////////NOTES FOR AFTER THIS PART OF CODE///////
/*
After these lines we get into the sectino generation. Basically each function draws about 10 platforms
at a certain number of backgrounds above the screen. So if you want to generate 1 backgorund above spawn
pass in 0. Each one is bassically the same, but added for variety and gameplay sake. This is an area that
could easily be imporved upon but im not very good at level design so I just tried my hardest :)
Anyway if you are a judge reading this, just ask and ill explain each function indivdually.
*/
void Game::genericSection(int screenNumber){
    for (int i = 0; i < 9; i++)
    {
        AddPlatform(normal, (Random.RandInt()%320 + 10), -850 + i*96 +(-860 * screenNumber));
    }
}

void Game::movingSection(int screenNumber){
    for (int i = 0; i < 9; i++)
    {
        int a = Random.RandInt()%4;
        if (a > 0 && a <= 2){
            AddPlatform(normal, (Random.RandInt()%320 + 10), (-850 + i*96) +(-860 * screenNumber));
        }
        else if (a > 2 && a <= 4){
            AddPlatform(moving_x, (Random.RandInt()%320 + 10), (-850 + i*96) +(-860 * screenNumber));
        }
    }
    AddPlatform(broken, (Random.RandInt()%320 + 10), -680+(-860 * screenNumber));
    AddPlatform(broken, (Random.RandInt()%320 + 10), -550+(-860 * screenNumber));
    AddPlatform(broken, (Random.RandInt()%320 + 10), -330+(-860 * screenNumber));
}


void Game::futureMovers(int screenNumber){
    for (int i = 0; i < 9; i++)
    {
        int a = Random.RandInt()%4;
        if (a > 0 && a <= 2){
            AddPlatform(futuristic_good, (Random.RandInt()%320 + 10), (-850 + i*96) +(-860 * screenNumber));
        }
        else if (a > 2 && a <= 4){
            AddPlatform(futuristic_moving, (Random.RandInt()%320 + 10), (-850 + i*96) +(-860 * screenNumber));
        }
    }
    AddPlatform(futuristic_broken, (Random.RandInt()%320 + 10), -680+(-860 * screenNumber));
    AddPlatform(futuristic_broken, (Random.RandInt()%320 + 10), -550+(-860 * screenNumber));
    AddPlatform(futuristic_broken, (Random.RandInt()%320 + 10), -330+(-860 * screenNumber));
}
//creates a preset sections of dissapearing platforms
void Game::dissapearingSection(int screenNumber){
    AddPlatform(dissapearing, Random.RandInt()%300 + 10, -850 +(-860 * screenNumber));
    AddPlatform(dissapearing, Random.RandInt()%300 + 10, -800+(-860 * screenNumber));
    AddPlatform(dissapearing, Random.RandInt()%300 + 10, -730+(-860 * screenNumber));
    //AddPlatform(broken, 120, -690);
    AddPlatform(dissapearing, Random.RandInt()%300 + 10, -610+(-860 * screenNumber));
    AddPlatform(dissapearing, Random.RandInt()%300 + 10, -490+(-860 * screenNumber));
    //AddPlatform(broken, 120, -420);
    AddPlatform(dissapearing, Random.RandInt()%300 + 10, -370+(-860 * screenNumber));
    AddPlatform(dissapearing, Random.RandInt()%300 + 10, -250+(-860 * screenNumber));
    AddPlatform(dissapearing, Random.RandInt()%300 + 10, -130+(-860 * screenNumber));
    AddPlatform(dissapearing, Random.RandInt()%300 + 10, -130+(-860 * screenNumber));
}

void Game::hardSection(int screenNumber){
    AddPlatform(normal, Random.RandInt()%300 + 10, -850+(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -730+(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -610+(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -480+(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -350+(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -220+(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -100+(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -10+(-860 * screenNumber));
}

void Game::futureSection(int screenNumber){
    for (int i = 0; i < 8; i++)
    {
        AddPlatform(futuristic_good, (Random.RandInt()%320 + 10), (-850 + i*110)+(-860 * screenNumber));
    }
}

void Game::obstacle1(int screenNumber){
    AddPlatform(normal, 100, -850+(-860 * screenNumber));
    AddPlatform(normal, 220, -720+(-860 * screenNumber));
    AddPlatform(normal, 300, -600+(-860 * screenNumber));
    AddPlatform(normal, 100, -490+(-860 * screenNumber));
    AddPlatform(hole, 150, -420+(-860 * screenNumber));
    AddPlatform(normal, 220, -290+(-860 * screenNumber));
    AddPlatform(broken, 300, -280+(-860 * screenNumber));
    AddPlatform(normal, 100, -200+(-860 * screenNumber));
    AddPlatform(normal, 290, -120+(-860 * screenNumber));
    AddPlatform(normal, 70, -50+(-860 * screenNumber));
}

void Game::obstacle2(int screenNumber){
    AddPlatform(normal, 100, -840+(-860 * screenNumber));
    AddPlatform(normal, 220, -720+(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -690+(-860 * screenNumber));
    AddPlatform(normal, 300, -600+(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -550+(-860 * screenNumber));
    AddPlatform(normal, 154, -460+(-860 * screenNumber));
    AddPlatform(hole, 40, -420+(-860 * screenNumber));
    AddPlatform(hole, 260, -420+(-860 * screenNumber));
    AddPlatform(normal, 110, -290+(-860 * screenNumber));
    AddPlatform(normal, 200, -290+(-860 * screenNumber));
    AddPlatform(normal, 100, -190+(-860 * screenNumber));
    AddPlatform(normal, 290, -130+(-860 * screenNumber));
    AddPlatform(normal, 70, -50+(-860 * screenNumber));
}

void Game::bugSection1(int screenNumber){
    AddPlatform(normal, Random.RandInt()%300 + 10, -850 +(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -730+(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -680 +(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -570+(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -470+(-860 * screenNumber));
    AddPlatform(platform_with_bug, 150, -373 +(-860 * screenNumber));
    AddPlatform(broken, 150, -360 +(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -280+(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -170+(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -70+(-860 * screenNumber));
}

void Game::bugSection2(int screenNumber){
    AddPlatform(normal, Random.RandInt()%300 + 10, -850 +(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -730+(-860 * screenNumber));
    AddPlatform(platform_with_bug, 125, -693 +(860 * screenNumber));
    AddPlatform(broken, 125, -680 +(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -570+(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -470+(-860 * screenNumber));
    AddPlatform(platform_with_bug, 250, -373 +(-860 * screenNumber));
    AddPlatform(broken, 250, -360 +(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -280+(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -170+(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -70+(-860 * screenNumber));
}

void Game::bugSection3(int screenNumber){
    AddPlatform(normal, Random.RandInt()%300 + 10, -850 +(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -730+(-860 * screenNumber));
    AddPlatform(floating_bug, 125, -683 +(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -570+(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -470+(-860 * screenNumber));
    AddPlatform(floating_bug, Random.RandInt()%300 + 10, -373 +(-860 * screenNumber));
    AddPlatform(broken, 250, -310 +(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -280+(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -170+(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -70+(-860 * screenNumber));
}

void Game::bugSection4(int screenNumber){
    AddPlatform(normal, Random.RandInt()%300 + 10, -850 +(-860 * screenNumber));
    AddPlatform(moving_x, Random.RandInt()%300 + 10, -730+(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -680 +(-860 * screenNumber));
    AddPlatform(moving_x, Random.RandInt()%300 + 10, -570+(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -470+(-860 * screenNumber));
    AddPlatform(floating_bug, 250, -373 +(-860 * screenNumber));
    AddPlatform(broken, 250, -360 +(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -280+(-860 * screenNumber));
    AddPlatform(moving_x, Random.RandInt()%300 + 10, -170+(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -70+(-860 * screenNumber));
}

void Game::brokenFuture(int screenNumber){
    for (int i = 0; i < 16; i++){
        if (i%2 == 0){
            AddPlatform(futuristic_good, Random.RandInt()%300 + 10, -830+i*50 + (-860 * screenNumber));
        }
        else{
            AddPlatform(futuristic_broken, Random.RandInt()%300 + 10, -830+i*50 + (-860 * screenNumber));
        }
    }
}

void Game::brokenSection(int screenNumber){
    for (int i = 0; i < 16; i++){
        if (i%2 == 0){
            AddPlatform(normal, Random.RandInt()%300 + 10, -830+i*50 + (-860 * screenNumber));
        }
        else{
            AddPlatform(broken, Random.RandInt()%300 + 10, -830+i*50 + (-860 * screenNumber));
        }
    }
}

void Game::bugApocalypse(int screenNumber){
    for (int i = 0; i < 8; i++)
    {
        int a = Random.RandInt()%320 + 10; 
        AddPlatform(platform_with_bug, a, -860 - 13 + i*110 +(-860 * screenNumber)); 
        AddPlatform(broken, a, -860 + i*110 +(-860 * screenNumber));
    }
}

void Game::mover2(int screenNumber){
    AddPlatform(normal, Random.RandInt()%300 + 10, -850 +(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -730+(-860 * screenNumber));
    AddPlatform(moving_x, 125, -683 +(860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -570+(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -470+(-860 * screenNumber));
    AddPlatform(moving_x, Random.RandInt()%300 + 10, -373 +(860 * screenNumber));
    AddPlatform(broken, 250, -310 +(860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -280+(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -170+(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -70+(-860 * screenNumber));
}

void Game::mover3(int screenNumber){
    AddPlatform(normal, Random.RandInt()%300 + 10, -850 +(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -730+(-860 * screenNumber));
    AddPlatform(moving_x, 125, -683 +(860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -570+(-860 * screenNumber));
    AddPlatform(broken, Random.RandInt()%300 + 10, -520+(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -470+(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -373 +(860 * screenNumber));
    AddPlatform(normal, 250, -310 +(860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -280+(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -170+(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -70+(-860 * screenNumber));
}

void Game::spring1(int screenNumber){
    AddPlatform(normal, Random.RandInt()%300 + 10, -850 +(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -730+(-860 * screenNumber));
    AddPlatform(spring, 145, -683 +(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -570+(-860 * screenNumber));
    AddPlatform(broken, Random.RandInt()%300 + 10, -520+(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -470+(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -373 +(860 * screenNumber));
    AddPlatform(normal, 250, -310 +(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -280+(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -170+(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -70+(-860 * screenNumber));
}

void Game::spring2(int screenNumber){
    AddPlatform(normal, Random.RandInt()%300 + 10, -850 +(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -730+(-860 * screenNumber));
    AddPlatform(normal, 125, -683 +(860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -570+(-860 * screenNumber));
    AddPlatform(broken, Random.RandInt()%300 + 10, -520+(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -470+(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -373 +(860 * screenNumber));
    AddPlatform(spring, 250, -310 +(860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -280+(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -170+(-860 * screenNumber));
    AddPlatform(normal, Random.RandInt()%300 + 10, -70+(-860 * screenNumber));
}





////////END OF Game.cpp///////

