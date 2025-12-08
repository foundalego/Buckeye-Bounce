////////START OF score.h///////

#ifndef SCORE_H
#define SCORE_H
#include "FEHLCD.h"
#include <fstream>

class score {
    private:
    int score_height; //horiziontal position of score -> used to calculate max score
    std::ifstream infile;
    std::ofstream outfile;
    std::string score_name;

    public:
    score();
    void drawScores();
    int get_high_score();
    void reset_score();
    void set_score_name(std::string name);
    void update_score(int pixels_moved);
    int get_score(); //for purposes of storing it in a txt file
    void print_score(); //to print to top right corner at all times
    
};

#endif

////////END OF score.h///////
