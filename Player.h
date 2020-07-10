#ifndef PLAYER_H
#define PLAYER_H
#include"Card.h"
class Player{
    string name="";
    vector <Card *> cards;
    bool winner=false;
    bool diller=false;
    bool fold =false;
    string combo="";
    pair<int,int> comb_and_last=make_pair(0,0); // карта комбинации , карта(сумма) вне комбинации
    int money;
public:
    Player(string name,int m=1000){
        this->name=name;
        money=m;
    }
    void setCards(Card * card){
        cards.push_back(card);
    }
    vector<Card *> getCards(){
        return cards;
    }
    void show(){
        if(winner)cout<<"Winner ";
        else cout<<"Loser ";
        cout<<name<<" has: ";
        for(auto c :cards)
            cout<<c->rang<<" ";
        cout<<" money "<<money<<endl;
        cout<<"Комбинация/статус: "<<combo<<" карта "
           <<comb_and_last.first<<" допкарта "<<comb_and_last.second<<endl;
    }
    int raise(int st){
        cout<<" Raise ";
        int r;cin>>r;
        while(r<=st){
            cout<<" Raise again! ";
            cin>>r;
        }
        return getBlind(r);
    }
    int decideStep(int stavke,char c){
        // fold , raise, call;

        if(fold)
            return 0;
        else{
            if(diller)cout<<name<<" очередь ";
            cout<<name<<" THINK!!"<<endl;
            if(c=='p' || c=='t')
                cout<<"Raise 1, call 2, fold 3"<<endl;
            if(c=='f')
                cout<<"Raise 1, check 4, fold 3"<<endl;
            int s;cin>>s;
            switch (s) {
            case 1:
                return raise(stavke);
            case 2:
                money -=stavke;
                return stavke;
            case 3:
                fold=1;
                combo="Fold";
                return 0;
            case 4:
                return 0;
            }
            return 0;
        }

    }
    int getBlind(int b){
        if(!fold){
            cout<<name<<" сделал ставку "<<b<<endl;
            if(money==0) {
                fold=1;
                combo="No money";
                return 0;
            }
            //        else if( b <money){
            //            b=money;
            //            money =0;
            //            return b;
            //        }
            else{
                money -=b;
                return b;
            }
        }
        else
            cout<<name<<" я пустой или фолд "<<b<<endl;
    }
    void addCash(int cash){
        money +=cash;
    }
    int getMoney(){
        return money;
    }
    void setDiller(bool d){diller=d;}
    bool getDiller(){return diller;}
    void setFold(bool d){
        combo="Fold";
        fold=d;}
    bool getFold(){return fold;}
    void setWinner(bool d){winner=d;}
    bool getWinner(){return winner;}
    void setCombo(string str){combo=str;}
    string getCombo(){return combo;}
    void setCombLast(pair<int,int> p){
        comb_and_last = p;
    }
    pair<int,int>  getCombLast(){
        return   comb_and_last;
    }
};

#endif // PLAYER_H
