#ifndef CARD_H
#define CARD_H
#include<iostream>
#include<vector>
#include<algorithm>
#include<random>
using namespace std;
class Card{

 public:
    static int static_queue;
    int id;
    string rang,path;
    int cost=0;
    Card(string rang,string path=""){
        id=++static_queue;
        this->rang=rang;
        this->path=path;
        cost = stoi(rang.substr(1,2));
    }
    bool operator==(const Card& rhs) const { return this->rang == rhs.rang;}
};
class CardDeck{
public:
    vector<Card*> cards={
        new Card("D14A"),new Card("D13K"),new Card("D12L"),new Card("D11J"),new Card("D10"),
        new Card("D9"),new Card("D8"),new Card("D7"),new Card("D6"),new Card("D5"),
        new Card("D4"),new Card("D3"),new Card("D2"),
        new Card("C14A"),new Card("C13K"),new Card("C12L"),new Card("C11J"),new Card("C10"),
        new Card("C9"),new Card("C8"),new Card("C7"),new Card("C6"),new Card("C5"),
        new Card("C4"),new Card("C3"),new Card("C2"),
        new Card("S14A"),new Card("S13K"),new Card("S12L"),new Card("S11J"),new Card("S10"),
        new Card("S9"),new Card("S8"),new Card("S7"),new Card("S6"),new Card("S5"),
        new Card("S4"),new Card("S3"),new Card("S2"),
        new Card("H14A"),new Card("H13K"),new Card("H12L"),new Card("H11J"),new Card("H10"),
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
            cout<<c->rang<<" "<<"cost "<<c->cost<<" ";row++;
            if(row==5){row=0;cout<<endl;}
        }
        cout<<endl;
    }
};
int Card::static_queue=0;
#endif // CARD_H
