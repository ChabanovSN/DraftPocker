#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <time.h>
#include"Game.h"
#include"FindWinner.h"
using namespace std;
int main(){
vector<Card *> my={new Card("H8"),new Card("D7"),new Card("H10"),
                   new Card("S10"),new Card("C10"),new Card("S8")};
    CardDeck d;

//std::sort(d.cards.begin(), d.cards.end(),FindWinner::sort_cost);
//FindWinner::show(my);
//int row=0;
//for(auto c : my){
//    cout<<c->rang<<" "<<"cost "<<c->cost<<" ";row++;
//    if(row==5){row=0;cout<<endl;}
//}
//cout<<endl;

    pair<pair<int,int>,string> p = FindWinner::findWinner(my);
   cout<<p.first.first<<" "<<p.first.second<<" " <<p.second<<endl;

    //cout<<" include"<<FindWinner::IsSubset(my,Royal_Flush)<<endl;











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


