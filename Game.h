///////START OF game.h FILE/////


#ifndef GAME_H
#define GAME_H

#include "character.h"
#include "platform.h"
#include "score.h"
#include "FEHImages.h"
#include "background.h"
#include <cstdlib>
#include <vector>


class Game{
    public:
    Game();
    void Menu();
    

    protected:
    std::vector<platform> all_plats;
    std::vector<Background> all_backs;
    character dood;
    score s1;
    
    private:
    
    void Run();
    void Stats();
    void Credits();
    void HowTo();
    void Initialize();
    void Input();
    void Logic();
    void Render_all();
    void isGameOver();
    void Shutdown();
    void endScreen();
    void SetGameOverTrue();
    void AddPlatform(identity id, int x, int y);
    int checkPlatCollision(platform& plat);
    int checkEnemyCollision();
    
    void drawPlatforms();
    void drawBackground();
    void addBackground(back_type type, int pos);
    int score;
    float mouse_x, mouse_y;
    int getScore();
    int springed;
    
    // procedural generation methods
    void pickSection(int screenNumber);
    void genericSection(int screenNumber);
    void dissapearingSection(int screenNumber);
    void movingSection(int screenNumber);
    void hardSection(int screenNumber);
    void futureSection(int screenNumber);
    
    void futureMovers(int screenNumber);
    
    void obstacle1(int screenNumber);
    void obstacle2(int screenNumber);
    void bugSection1(int screenNumber);
    void bugSection2(int screenNumber);
    void bugSection3(int screenNumber);
    void bugSection4(int screenNumber);
    void brokenFuture(int screenNumber);
    void brokenSection(int screenNumber);
    
    void bugApocalypse(int screenNumber);
    void mover2(int screenNumber);
    void mover3(int screenNumber);
    void spring1(int screenNumber);
    void spring2(int screenNumber);




    int orderCount;
    std::vector<back_type> order;
    bool exit;
    bool gameover;

    ///// DECLARING ALL IMAGE FILES /////
    FEHImage play, stats, how_to, credits, close, background, banner, score_card, logo, brutus, bug_1;
};

#endif

///// END OF game.h FILE///////
