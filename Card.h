#ifndef CARD_H
#define CARD_H
#include<iostream>
#include<vector>
#include<algorithm>
#include<random>
using namespace std;
class Card{

 public:
    string rang,path;
    Card(string rang,string path=""){
        this->rang=rang;
        this->path=path;
    }
};
class CardDeck{
public:
    vector<Card*> cards={
        new Card("DA"),new Card("DK"),new Card("DL"),new Card("DJ"),new Card("D10"),
        new Card("D9"),new Card("D8"),new Card("D7"),new Card("D6"),new Card("D5"),
        new Card("D4"),new Card("D3"),new Card("D2"),
        new Card("CA"),new Card("CK"),new Card("CL"),new Card("CJ"),new Card("C10"),
        new Card("C9"),new Card("C8"),new Card("C7"),new Card("C6"),new Card("C5"),
        new Card("C4"),new Card("C3"),new Card("C2"),
        new Card("SA"),new Card("SK"),new Card("SL"),new Card("SJ"),new Card("S10"),
        new Card("S9"),new Card("S8"),new Card("S7"),new Card("S6"),new Card("S5"),
        new Card("S4"),new Card("S3"),new Card("S2"),
        new Card("HA"),new Card("HK"),new Card("HL"),new Card("HJ"),new Card("H10"),
        new Card("H9"),new Card("H8"),new Card("H7"),new Card("H6"),new Card("H5"),
        new Card("H4"),new Card("H3"),new Card("H2")
    };
    CardDeck(){
        random_device rd;
        auto rng = default_random_engine {rd()};
        shuffle(begin(cards), end(cards),rng);
    }
    ~CardDeck(){
        if(cards.size()>0)
            for(auto c :cards)
                delete c;
    }
    void show(){
        int row=0;
        for(auto c : cards){
            cout<<c->rang<<" ";row++;
            if(row==10){row=0;cout<<endl;}
        }
        cout<<endl;
    }
};

#endif // CARD_H
