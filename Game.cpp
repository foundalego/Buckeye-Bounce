#include "Game.h"
#include <thread>
#include "FEHLCD.h"
#include "FEHKeyboard.h"
#include "FEHImages.h"
#include <chrono>
#include "FEHRandom.h"

// game constructor
Game::Game()
    :gameover(false), exit(false), orderCount(0), springed(0){
        order = {light, light, light, light, light, light, light, light,  // 8 runs of the "light" bg
                light_t, mid, mid, mid, mid, mid, mid, mid, mid, mid, mid, mid, mid, //13 runs of the "mid" bg
                mid_t, moon, stars, stars, stars, stars, stars, stars, //8 runs of the "dark" bg
                stars, stars, stars, stars, stars, stars, stars_t, space}; //7 runs of the "space" bg variations
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
        //score_card.Open("Score_Plaque.png");
    }

//main menu function that controls overarching gameplay    
void Game::Menu(){
    while (!exit){
        LCD.Clear(BLACK);
        background.Draw(0,0);
        logo.Draw(50, 40);
        how_to.Draw(140,450);
        play.Draw(140,350);
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
    LoadAssets();
    Initialize();
    addBackground(base, 0);
    addBackground(light, -858);
    //AddPlatform(floating_bug, 100, 300);
    //AddPlatform(platform_with_bug, 200, 600);
    //genericSection();
    //AddPlatform(hole, 200, 300);
    AddPlatform(spring, 200, 300);
    //AddPlatform(broken, 200, 400);
    //AddPlatform(futuristic_broken, 100, 400);
    //AddPlatform(futuristic_good, 100, -400);
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
        //if mouse clicks in the exit area
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
        LCD.SetFontScale(1.0);
        LCD.WriteLine("Software development: Ben Coughlin");
        LCD.WriteLine("Creative Director: Sophie Subit");
        close.Draw(300,800);
        LCD.Update();
        while (!LCD.Touch(&mouse_x, &mouse_y));
        //if user clicks the exit button
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
        LCD.SetFontScale(1.0);
        //Write instructions
        LCD.WriteLine("Goal: Climb as high as possible");
        LCD.WriteLine("Controls: A for left, D for right");
        LCD.WriteLine("Landing on a platform will make you jump");
        LCD.WriteLine("Landing on a bug will squash it and make you jump");
        LCD.WriteLine("Landing on a spring or jetpack will give you a huge boost");
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
    for (int i = 0; i < 8; i++)
    {
        AddPlatform(normal, (Random.RandInt()%320 + 10), i*100);
    }
    genericSection();
    //movingSection();
}
// loads all images and sounds needed
void Game::LoadAssets(){
    
}
// take user input, might need to change type to determine how its comminicating with run function
void Game::Input(){
    int ch;
    if (Keyboard.isPressed(KEY_A) || Keyboard.isPressed(KEY_LEFT)){
        ch = 97;
    }
    else if(Keyboard.isPressed(KEY_D) || Keyboard.isPressed(KEY_RIGHT)){
        ch = 100;
    }
    else if(Keyboard.isPressed(KEY_W) || Keyboard.isPressed(KEY_UP)){
        ch = 119;
    }
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
        if (all_plats[i].specialLogic(checkPlatCollision(all_plats[i]), all_plats) == 1){ //if 1 is returned by special logic then the current platform must be destroyed
            all_plats.erase(all_plats.begin() + i);
            //i--;
            //AddPlatform(normal, 200, 0);
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
                orderCount++;
            }
            //if it has gone above the preset order just generate a space background
            else{
                addBackground(space, (all_backs[i].get_pos() - (2*LCD_HEIGHT) + 5));
            }
            //delete background that has left the screen
            pickSection(s1.get_score());
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

// correctly close files
void Game::Shutdown(){
    gameover = !gameover;
    s1.reset_score();
    dood.reset();
    all_plats.clear();
    all_backs.clear();
    LCD.SetFontScale(1.0);
    orderCount = 0;
}

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
        if (dood.get_player_x() > plat.get_x() && 
            dood.get_player_x() < plat.get_x() + plat.get_w() && 
            dood.get_player_y() >= plat.get_y() &&
            dood.get_player_y() <= plat.get_y() + plat.get_h())
        {
            SetGameOverTrue();
        }
        //top right corner is in void
        else if 
            (dood.get_player_x() + 45 > plat.get_x() && 
            dood.get_player_x() + 45 < plat.get_x() + plat.get_w() && 
            dood.get_player_y() >= plat.get_y() &&
            dood.get_player_y() <= plat.get_y() + plat.get_h())
        {
            SetGameOverTrue();
        }

        //bottom left corner collision
        else if 
            (dood.get_player_x() + 45 > plat.get_x() && 
            dood.get_player_x() + 45 < plat.get_x() + plat.get_w() && 
            dood.get_player_y() + 45 >= plat.get_y() &&
            dood.get_player_y() + 45 <= plat.get_y() + plat.get_h())
        {
            SetGameOverTrue();
        }
        else if 
            (dood.get_player_x() > plat.get_x() && 
            dood.get_player_x() < plat.get_x() + plat.get_w() && 
            dood.get_player_y() + 45 >= plat.get_y() &&
            dood.get_player_y() + 45 <= plat.get_y() + plat.get_h())
        {
            SetGameOverTrue();
        }
        
    }
    

    //spring collision logic
    else if(plat.get_identity() == spring){
        if (dood.get_player_x() + 45 > plat.get_x() - 25 && 
            dood.get_player_x() + 45 < plat.get_x() + plat.get_w() - 25 && 
            dood.get_player_y() + 45 >= plat.get_y() &&
            dood.get_player_y() + 45 <= plat.get_y() + 7 &&
            dood.get_vel_y() > 0)
            {
                springed = 170;
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
                springed = 170;
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
        if (dood.get_player_x() + 45 > plat.get_x() && 
            dood.get_player_x() + 45 < plat.get_x() + plat.get_w() && 
            dood.get_player_y() + 45 >= plat.get_y() &&
            dood.get_player_y() + 45 <= plat.get_y() + 7 &&
            dood.get_vel_y() > 0)
            {
            //here is where the death of enemy logic would be
            //if player is heading downwards and collides the bug is squashed
            
            plat.change_jump();
            dood.jump(6);
            return 4;
            
            //otherwise the player is heading upwards and the bug kills them
        }
        //////LEFT EDGE + GOING DOWN//////
        else if (
            dood.get_player_x() > plat.get_x() && 
            dood.get_player_x() < plat.get_x() + plat.get_w() && 
            dood.get_player_y() + 45 >= plat.get_y() &&
            dood.get_player_y() + 45 <= plat.get_y() + 7 &&
            dood.get_vel_y() > 0)
            {
            //here is where the death of enemy logic would be
            //if player is heading downwards and collides the bug is squashed
            
            plat.change_jump();
            dood.jump(6);
            return 4;
        }


        ///////RIGHT EDGE + GOING UP//////
        if (dood.get_player_x() + 45 > plat.get_x() && 
            dood.get_player_x() + 45 < plat.get_x() + plat.get_w() && 
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
            dood.get_player_x() > plat.get_x() && 
            dood.get_player_x() < plat.get_x() + plat.get_w() && 
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
        if (dood.get_player_x() + 45 > plat.get_x() && 
            dood.get_player_x() + 45 < plat.get_x() + plat.get_w() && 
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
            dood.get_player_x() > plat.get_x() && 
            dood.get_player_x() < plat.get_x() + plat.get_w() - 50 && 
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

void Game::drawPlatforms(){
    int size = all_plats.size();
    for (int i = 0; i < size; i++){
        if (all_plats[i].get_y() > 0 && all_plats[i].get_y() < LCD_HEIGHT - 20 && all_plats[i].getRender() == true)
        {
            all_plats[i].draw_platform();
        }
    }
}

void Game::drawBackground(){
    for (int i = 0; i < all_backs.size(); i++){
        all_backs[i].drawBack();
    }
}

//need platforms to move at the equal and opposite velocity to give illusion of screen moving
//only calling it after the jump mathod has been called so you just need to call this function for a certain amount of time after jump has been called
//have a screen center variable and if dood ever crosses that line then everything gets dragged down that far
void Game::addBackground(back_type type, int pos){
    all_backs.emplace_back(type, pos);
}


void Game::AddPlatform(identity type, int x, int y){
    all_plats.emplace_back(type, x, y); 
}

void Game::pickSection(int score){
    float a = Random.RandInt()%100 + score/1000;
    if (a > 0 && a <= 50){
        genericSection();
    }
    else if(a > 50 && a <= 75){
        movingSection();
    }
    else if(a > 75 && a <= 80){
        hardSection();
    }
    else if(a > 80 && a <= 95){
        dissapearingSection();
    }
    else if(a > 95){
        futureSection();
    }
}
//establish set up of the usual platform
void Game::genericSection(){
    for (int i = 0; i < 8; i++)
    {
        AddPlatform(normal, (Random.RandInt()%320 + 10), -860 + i*110);
    }
}

void Game::movingSection(){
    for (int i = 0; i < 7; i++)
    {
        int a = Random.RandInt()%5;
        if (a > 0 && a <= 2){
            AddPlatform(normal, (Random.RandInt()%320 + 10), -860 + i*120);
        }
        else if (a > 2 && a <= 4){
            AddPlatform(moving_x, (Random.RandInt()%320 + 10), -860 + i*120);
        }
        else{
            AddPlatform(moving_broken, (Random.RandInt()%320 + 10), -860 + i*120);
        }
    }
}

//creates a preset sections of dissapearing platforms
void Game::dissapearingSection(){
    AddPlatform(dissapearing, Random.RandInt()%300 + 10, -850);
    AddPlatform(dissapearing, Random.RandInt()%300 + 10, -730);
    AddPlatform(broken, 120, -690);
    AddPlatform(dissapearing, Random.RandInt()%300 + 10, -610);
    AddPlatform(dissapearing, Random.RandInt()%300 + 10, -490);
    AddPlatform(broken, 120, -4200);
    AddPlatform(dissapearing, Random.RandInt()%300 + 10, -370);
    AddPlatform(dissapearing, Random.RandInt()%300 + 10, -250);
    AddPlatform(dissapearing, Random.RandInt()%300 + 10, -130);
}

void Game::hardSection(){
    AddPlatform(normal, 100, -850);
    AddPlatform(normal, 100, -730);
    AddPlatform(normal, 100, -610);
    AddPlatform(normal, 100, -490);
    AddPlatform(normal, 100, -370);
    AddPlatform(normal, 100, -250);
    AddPlatform(normal, 100, -130);
}

void Game::futureSection(){
    for (int i = 0; i < 8; i++)
    {
        AddPlatform(futuristic_good, (Random.RandInt()%320 + 10), -860 + i*110);
    }

}
