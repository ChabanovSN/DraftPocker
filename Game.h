#ifndef GAME_H
#define GAME_H
#include"Player.h"
#include<queue>
class Game{
public:
    Game(int players = 2):steak(new CardDeck()){

        player.push_back(new Player("I")); // first diller
        player.at(0)->setDiller(1);

        if(players>1 && players <11){
            for(int i  = 1; i<players;i++){
                string name = string("Player");
                player.push_back(new Player(name.append(to_string(i+1))));
            }
        }

    }
    void preflop(){
        // блайнды до раздачи
        if(player.size()==2){
            stavka = player.at(0)->getBlind(5);
            smallBlind();
            player.at(1)->getBlind( bigBlind());
        }else{
            stavka = player.at(1)->getBlind(5);
            smallBlind();
            player.at(2)->getBlind( bigBlind());


        }
        for(int i = 0; i<2;i++){ // раздаем по 2 карты игрокам
            for(auto p :player){
                p->setCards(steak->cards.back());
                steak->cards.pop_back();
            }
        }
        if(player.size()>3) // если играком больше 3 то они делают ставки
                    trade(3,'p');

    }
    void flop(){
         cout<<" flop ";
       for(int i = 0;i<3;i++){
           commonCards.push_back(steak->cards.back());
           steak->cards.pop_back();
          cout<<commonCards[i]->rang<<" ";
       }
       cout<<endl;
       newStep();// дилер ходит последним
       trade(0,'f');
    }
    void torn(){
        cout<<" torn ";
          commonCards.push_back(steak->cards.back());
          steak->cards.pop_back();
          for(auto c : commonCards)
          cout<<c->rang<<" ";
          cout<<endl;

      trade(0,'t');
    }
    void river(){
          cout<<" river";
          commonCards.push_back(steak->cards.back());
          steak->cards.pop_back();
          for(auto c : commonCards)
          cout<<c->rang<<" ";
          cout<<endl;
    }
    int smallBlind(){
        bank +=stavka;
        return  stavka;

    }
    int bigBlind(){
        stavka *=2;
        bank +=stavka;
        fixStavka=stavka;
        return  stavka;
    }
    void show(){
        cout<<"Common cards ";
        for(auto c: commonCards)
            cout<<c->rang<<" ";
        cout<< "\nBank ="<<bank<<endl;
        for(auto p :player)
            p->show();
    }
    ~Game(){
        if(player.size()>0){
            for(auto p :player)
                delete p;
        }
        if(commonCards.size()>0){
            for(auto c :commonCards)
                delete c;
        }
        delete steak;
    }
    //Префлоп, Флоп, Торн, Ривер.
    bool getEndGame(){
        return  endGame;
    }
private:
    void trade(int st , char c){
        if(player.size()>0){
            for(;st<(int)player.size();st++){
              //  newStep(); // переход хода
                if(player[st]->getFold()==false){
                    int newStavke=  player[st]->decideStep(stavka,c);
                    bank +=newStavke;
                    if(newStavke>stavka){
                        stavka=newStavke;
                        if(player[st]->getDiller() && c=='f')
                            trade(0,'f');
                        }
                    if(checkFold()==true){// если все сбросили то выигрывает последний
                        endGame=true;
                        return;
                    }
                }
            }
               stavka=fixStavka;
        }
    }
    int checkFold(){
        int counter = player.size();
        if(player.size()>0){
            for(auto p :player){
                if(p->getFold()==true)counter--;
              //  cout<<" Check folder"<<counter<<endl;
            }
            if(counter==1)
            for(auto p :player)
                if(p->getFold()==false){
                //     cout<<" Check folder 2 "<<counter<<endl;
                    p->setWinner(1);
                    p->setCombo("Остальные сбросили");
                    p->addCash(bank);
                    bank=0;
                    return 1;
                }
        }
    }
    void newStep(){
        if(player.size()>0){
            auto first = player.front(); // переход очереди
          //  first->setDiller(0);
            player.erase(player.begin());
          //  player.at(0)->setDiller(1);
            player.push_back(first);
        }
    }
    int bank=0,stavka = 0, fixStavka=0;
    vector<Player *> player;
    CardDeck * steak;
    vector<Card *> commonCards;
    bool endGame=false;
};

#endif // GAME_H
