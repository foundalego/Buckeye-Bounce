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
    void LoadAssets();
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
    void pickSection(int score);
    void genericSection();
    void dissapearingSection();
    void movingSection();
    void hardSection();
    void futureSection();

    int orderCount;
    std::vector<back_type> order;
    bool exit;
    bool gameover;

    ///// DECLARING ALL IMAGE FILES /////
    FEHImage play, stats, how_to, credits, close, background, banner, score_card, logo, brutus, bug_1;
};

#endif