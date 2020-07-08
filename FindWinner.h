#ifndef FINDWINNER_H
#define FINDWINNER_H
#include"Game.h"
#include <utility>
#include<map>
static vector<Card *> Royal_Flush[4]={{new Card("D14A"),new Card("D13K"),new Card("D12L"),
                                       new Card("D11J"),new Card("D10")},
                                      {new Card("H14A"),new Card("H13K"),new Card("H12L"),
                                       new Card("H11J"),new Card("H10")},
                                      {new Card("C14A"),new Card("C13K"),new Card("C12L"),
                                       new Card("C11J"),new Card("C10")},
                                      {new Card("S14A"),new Card("S13K"),new Card("S12L"),
                                       new Card("S11J"),new Card("S10")}};





class FindWinner{
    static pair<int,int> full_House( vector<Card*> &user){
        sort(user.begin(), user.end(),sort_q);
         map<int,int> countUniq;
          countUniq[user[0]->cost]=1;
          map<int,int>::iterator it;
      int comb3=0, comb2=0;
        for(size_t i=1;i<user.size();i++){
             it = countUniq.find(user[i]->cost);
             if(it == countUniq.end())
                  countUniq[user[i]->cost]=1;
             else
                 it->second++;
        }

        for(auto e :countUniq){
            if(e.second==3)comb3=e.first;
            if(e.second==2)comb2=e.first;
        }
         if(comb3 && comb2)
             return make_pair(comb3,comb2);
        return make_pair(0,0);
    }
    static int straight_Flush( vector<Card*> &user){
        sort(user.begin(), user.end(),sort_q);
        int score, checkQueue;
        score=checkQueue=user[0]->cost;
        for(size_t i=0;i<user.size();i++){
            if(user[0]->rang.at(0) !=user[i]->rang.at(0)) // все одной масти
                return 0;
            if(checkQueue ==user[i]->cost){// проверка последовательности
                score +=user[i]->cost;
                checkQueue--;
            }
            else
                return 0;
        }
        return score;
    }

    static bool eqCards(const vector <Card*> &combo, const vector<Card*> &user){
        size_t counter = combo.size();
        for(size_t i=0;i<user.size();i++)
            for(size_t j=0;j<combo.size();j++)
                if(user[i]->rang==combo[j]->rang)counter--;
        return !counter;
    }
    static pair<int,int> four_of_card( vector<Card*> &user){
        sort(user.begin(), user.end(),sort_cost);

        int score, checkQueue,counter =1;;
          score=checkQueue=user[0]->cost;
        for(size_t i=1;i<user.size();i++){
            if(checkQueue ==user[i]->cost){// проверка последовательности
                score +=user[i]->cost;
                counter++;
                if(counter==4){
                  vector<int> cards;
                    for(size_t j=0;j<user.size();j++)
                        if(user[j]->cost!=user[i]->cost){
                               cards.push_back(user[j]->cost);

                        }
                     sort(cards.begin(),cards.end());//поиск старшей из оставших
                    return make_pair(score,cards[cards.size()-1]);
                }

            }
            else{
                checkQueue =user[i]->cost;
                counter=1;
                score =user[i]->cost;
            }
        }
        return make_pair(0,0);

    }


public:
    static inline bool sort_rang(const Card *c1, const Card *c2){
        return (c1->rang > c2->rang );
    }
    static inline bool sort_cost(const Card *c1, const Card *c2){
        return ( c1->cost < c2->cost);
    }
    static inline bool sort_q(const Card *c1, const Card *c2){
        return (c1->id < c2->id);
    }
    template <typename T>
    static  bool IsSubset(std::vector<T> A, std::vector<T> B)
    {
        //        std::sort(A.begin(), A.end(),more_rang);
        //        std::sort(B.begin(), B.end(),more_rang);
        return std::includes(A.begin(), A.end(), B.begin(), B.end());
    }
    void takeCards(vector<Card*> &commonCards,deque<Player *> &player){

    }


    static pair<pair<int,int>,string> findWinner(vector<Card*> &user){
        //Royal_Flush
        for(int i = 0; i<4;i++)
            if(eqCards(Royal_Flush[i],user))
                return make_pair(make_pair(1,0), string("Royal Flush"));

        //Straight Flush
        int score = straight_Flush(user);
        if(score)
            return make_pair(make_pair(score,0), string("Straight Flush"));
        // CORE
        pair<int,int>  scoreFour = four_of_card(user);
         if(scoreFour.first)
              return make_pair(scoreFour, string("CORE"));
      //Full House
       pair<int,int> score3_2 = full_House(user);
            if(score3_2.first)
                return make_pair(score3_2, string("Full House"));
        return  make_pair(make_pair(0,0)," EMPTY");
    }

    static void show(vector<Card *> cards){
        int row=0;
        for(auto c : cards){
            cout<<c->rang<<" "<<"cost "<<c->cost<<" ";row++;
            if(row==5){row=0;cout<<endl;}
        }
        cout<<endl;
    }
};

#endif // FINDWINNER_H
