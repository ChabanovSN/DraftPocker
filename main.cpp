#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <time.h>
#include"Game.h"
#include"FindWinner.h"
using namespace std;
int main(){
vector<Card *> combo={
        new Card("S12L"),new Card("H3"),new Card("H4"),
                             new Card("C8"), new Card("C10")
};
  deque<Player *> pl;
  Player * m= new Player("My");
  m->setCards(new Card("S7")); m->setCards(new Card("S8"));
  pl.push_back(m);
  Player * c= new Player("Comp1");
  c->setCards(new Card("C7")); c->setCards(new Card("C14A"));
 // c->setFold(1);
  pl.push_back(c);
  Player * c2= new Player("Comp2");
  c2->setCards(new Card("C5")); c2->setCards(new Card("C3"));
 // c2->setFold(1);
  pl.push_back(c2);
  FindWinner::findWinner(combo,pl);
  for(auto p : pl)p->show();



//    Game g(2);
//    g.preflop();
//    if(g.getEndGame()){
//        g.show();
//        return 0;
//    }

//    g.flop();
//    if(g.getEndGame()){
//        g.show();
//        return 0;
//    }
//    g.torn();
//    if(g.getEndGame()){
//        g.show();
//        return 0;
//    }
//    g.river();
//    g.show();

//    // g.step();
//    //  g.step();
    return 0;
}


