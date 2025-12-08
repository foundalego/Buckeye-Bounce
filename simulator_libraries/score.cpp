////////START OF score.cpp///////

#include "score.h"
//#include <iostream>

score::score()
    :score_height(LCD_HEIGHT){}

void score::update_score(int pixels_moved){
    score_height+=pixels_moved;
}

void score::reset_score(){
    infile.clear();
    infile.open("highscores.txt");
    int a[11];
    std::string names[11];
    int count = -1;
    //loop to store all ten high scores
    for (int i = 0; i < 10; i++){
        infile >> a[i];
        //will store the position of the new high score and make sure it only stores the highest one it is greater than
        if (score_height - LCD_HEIGHT > a[i] && count == -1){
            count = i;
        }
    }
    infile.close();
    if (count != -1){
        outfile.clear();
        outfile.open("highscores.txt");
        //shifts all items up an index
        for (int i = 9; i > count; i--){
            a[i] = a[i-1];
        }
        //puts the new high score in the hole created by shifting everything
        a[count] = score_height - 860;
        for (int i = 0; i < 10; i++){
            outfile << a[i] << std::endl;
        }
        outfile.close();

        //this is the portion where the names get updated
        infile.clear();
        infile.open("highscore_name.txt");
        for (int i = 0; i < 10; i++){
            infile >> names[i];  
        }
        infile.close();
        outfile.clear();
        outfile.open("highscore_name.txt");
        //does the same shifitng but with the names now
        for (int i = 9; i > count; i--){
            names[i] = names[i-1];
        }
        names[count] = score_name;
        for (int i = 0; i < 10; i++){
            outfile << names[i] << std::endl;
        }
    }

    
    score_height = LCD_HEIGHT;
}

void score::drawScores(){
    infile.clear();
    infile.open("highscore_name.txt");
    std::string names[10];
    int a[10];
    for (int i = 0; i < 10; i++){
        infile >> names[i];  
    }
    for (int i = 0; i < 10; i++){
        LCD.WriteAt(names[i], 90, 270+i*54);
    }
    infile.close();
    infile.clear();
    infile.open("highscores.txt");
    for (int i = 0; i < 10; i++){
        infile >> a[i];  
    }
    for (int i = 0; i < 10; i++){
        LCD.WriteAt(a[i], 190, 270+i*54);
    }
    infile.close();
}

void score::set_score_name(std::string name){
    score_name = name;
}

int score::get_score(){
    return score_height;
}

void score::print_score(){
    LCD.SetFontScale(1.0);
    LCD.WriteAt(score_height - LCD_HEIGHT, 337, 5);
}

int score::get_high_score(){
    infile.open("highscores.txt");
    int a;
    infile >> a;
    infile.close();
    return a;
}

////////END OF score.cpp///////
