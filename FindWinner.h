#ifndef FINDWINNER_H
#define FINDWINNER_H
#include"Game.h"
class FindWinner{


    template <typename T>
    bool IsSubset(std::vector<T> A, std::vector<T> B)
    {
        std::sort(A.begin(), A.end());
        std::sort(B.begin(), B.end());
        return std::includes(A.begin(), A.end(), B.begin(), B.end());
    }

 public:
    void takeCards(vector<Card*> &commonCards,deque<Player *> &player){

    }
};

#endif // FINDWINNER_H
