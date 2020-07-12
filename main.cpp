#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <time.h>
#include"Game.h"
#include"FindWinner.h"
using namespace std;
int main(){
vector<Card *> combo={
        new Card("S12L"),new Card("H9"),new Card("C14A"),
                             new Card("H11J"), new Card("D3")
};
  deque<Player *> pl;
  Player * m= new Player("My");
  m->setCards(new Card("D4")); m->setCards(new Card("H6"));
 //  m->setFold(1);
  pl.push_back(m);
  Player * c= new Player("Comp1");
  c->setCards(new Card("D11J")); c->setCards(new Card("S7"));
  //c->setFold(1);
  pl.push_back(c);
  Player * c2= new Player("Comp2");
  c2->setCards(new Card("D11J")); c2->setCards(new Card("S7"));
  c2->setFold(1);
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


