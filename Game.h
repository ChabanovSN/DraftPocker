#ifndef GAME_H
#define GAME_H
#include"Player.h"
#include<queue>
#include<time.h>
#include<FindWinner.h>
class Game{
public:
    Game(int players = 2):stack(new CardDeck()){//  перемешанная калода
        srand(time(NULL));
        player.push_back(new Player(" Human player")); // first diller
        // player.at(0)->setDiller(1);

        if(players>1 && players <11){
            for(int i  = 1; i<players;i++){
                string name = string("Player");
                player.push_back(new Player(name.append(to_string(i))));
            }
        }
        // player[rand()% (int)player.size()]->setDiller(1); // диллер случайно
        player.at(1)->setDiller(1);
        makeDillerFirst();
        lastRichMan=player.size(); // все к гого есть деньги
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
        delete stack;
    }
    void start(){
        while(lastRichMan>1){
            preflop();
            flop();
            turn();
            river();
            checkMoney(); // проверить деньги у играков, если есть только у 1, конец игры
        }
    }
private:
    void preflop(){
        // блайнды до раздачи

        if(player.size()==2){
            stavka =  player.at(0)->getBlind(10);// задает игрок
            smallBlind();
            newStep();
            player.at(0)->getBlind(bigBlind());
        }else{
            newStep();
            stavka = player.at(0)->getBlind(10);
            smallBlind();
            newStep();
            player.at(0)->getBlind( bigBlind());
        }
        player.at(0)->setMaxStavka(stavka); // на префлопе максимальная у Бигблейда
        for(int i = 0; i<2;i++){ // раздаем по 2 карты игрокам
            for(auto p :player){
                p->setCards(stack->cards.back());
                stack->cards.pop_back();
            }
        }
        // show();
        if(player.size()>2) // если играком больше 3 то они делают ставки
            trade();

    }
    void flop(){
        cout<<" flop ";
        for(int i = 0;i<3;i++){
            commonCards.push_back(stack->cards.back());
            stack->cards.pop_back();
            cout<<commonCards[i]->rang<<" ";
        }
        cout<<endl;
        newStep();// дилер ходит последним
        trade();
    }
    void turn(){
        cout<<" turn ";
        commonCards.push_back(stack->cards.back());
        stack->cards.pop_back();
        for(auto c : commonCards)
            cout<<c->rang<<" ";
        cout<<endl;

        trade(); // на один ход меньше так как после диллера ????
    }
    void river(){
        cout<<" river ";
        commonCards.push_back(stack->cards.back());
        stack->cards.pop_back();
        for(auto c : commonCards)
            cout<<c->rang<<" ";
        cout<<endl;
        trade();
        FindWinner::findWinner(commonCards,player);
        giveMoneyWinner();
        for(auto p : player)p->show();
        cout<<endl;
    }
    int smallBlind(){
        bank +=stavka;
        return  stavka;

    }
    int bigBlind(){
        stavka *=2;
        bank +=stavka;

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

    //Префлоп, Флоп, Торн, Ривер.
    bool getEndGame(){
        return  endGame;
    }

    void trade(){
        if(player.size()>0){
            for(int st =0;st<(int)player.size();){
                st+= newStep();
                if(player[0]->getFold())continue;
                else{
                    cout<<"Ходит ~~~~"<<st;
                    player[0]->show();
                    if(player[0]->getDiller())cout<<" Diller is"<<player[0]->getName()<<endl;

                    if(player[0]->getFold()==false){
                        int newStavke=  player[0]->decideStep(stavka);
                        bank +=newStavke;
                        if(newStavke>stavka){
                            player[0]->setMaxStavka(newStavke);
                            stavka=newStavke;
                            //   trade();
                        }
                        if(checkFold()==true){// если все сбросили то выигрывает последний
                            endGame=true;
                            return;
                        }
                    }
                }
            }

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
    int newStep(){
        if(player.size()>0){
            auto first = player.front(); // переход очереди
            player.pop_front();
            player.push_back(first);
            cout<<" New STEP  "<<player[0]->getName()<<" -> "<<first->getName()<<endl;
            if(player[0]->getFold())
                return 1+ newStep();
        }
        return 1;
    }
    void makeDillerFirst(){
        while (player[0]->getDiller() == false) { // устанавливаем диллера на первое место
            Player * p = player.front();
            player.pop_front();
            player.push_back(p);
        }
    }
    void giveMoneyWinner(){
        int countWinner=0;
        for(auto p:player)
            if(p->getWinner())countWinner++;
        if(countWinner>1)cout<<" Надо делиться!! "<<endl;


        for(auto p:player)
            if(p->getWinner())
                p->addCash(bank/countWinner);
        bank %=bank;
    }
    void checkMoney(){
        lastRichMan=player.size();
        for (auto p : player)
            if(p->getMoney()>0)
                lastRichMan--;
    }
    int bank=0,stavka = 0, lastRichMan;
    deque<Player *> player;
    CardDeck * stack;
    vector<Card *> commonCards;
    bool endGame=false;

};

#endif // GAME_H
