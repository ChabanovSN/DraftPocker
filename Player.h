#ifndef PLAYER_H
#define PLAYER_H
#include"Card.h"
class Player{
    string name="";
    vector <Card *> cards;
    int statusWinner = 0; // поиск среди победителей с max статусом
    bool winner=false;
    bool diller=false;
    bool fold =false;
    int MaxStavka = 0;
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
    string getName(){
        return name;
    }
    void setMaxStavka(int s){
        MaxStavka =s;
    }
    void show(){
        if(winner)cout<<"Winner ";
        else cout<<"Loser ";
        cout<<statusWinner<<" ";
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
         cout<<" Raise "<<r<<endl;
        money -=r;
        return getBlind(r); // здесь для экономии просто переназначает ставку
    }
    int decideStep(int stavke){
        // fold , raise, call;
    //  show();
        if(fold)
            return 0;
        else{
            if(diller)cout<<name<<" очередь ";
            cout<<name<<" THINK!!"<<endl;

               if(MaxStavka==stavke)                       // p префлоп t терн
                cout<<"Raise 1, fold 3, check 4"<<endl;
               else
                   cout<<"Raise 1, call 2, fold 3"<<endl;
            int s;cin>>s;
            switch (s) {
            case 1:
                return raise(stavke);
            case 2:
                cout<<" call "<<stavke<<endl;
                money -=stavke;
                MaxStavka=stavke;
                return stavke;
            case 3:
                fold=1;
                combo="Fold";
                 cout<<" fold "<<endl;
                return 0;
            case 4:
                  cout<<" check "<<endl;
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
    void setStatusWinner(int s){statusWinner=s;}
    int getStatusWinner(){return statusWinner;}
};

#endif // PLAYER_H
