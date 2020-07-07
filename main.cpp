#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <time.h>
#include"Game.h"
using namespace std;
int main(){
    Game g(2);
    g.preflop();
    if(g.getEndGame()){
        g.show();
        return 0;
    }

    g.flop();
    if(g.getEndGame()){
        g.show();
        return 0;
    }
    g.torn();
    if(g.getEndGame()){
        g.show();
        return 0;
    }
    g.river();
    g.show();

    // g.step();
    //  g.step();
    return 0;
}


