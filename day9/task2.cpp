//452 players; last marble is worth 70784 points

#include <iostream>
#include <list>
#include <array>
#include <algorithm>

void printVec(const std::list<int>& marblesLaid, auto current)
{
    for(auto it = marblesLaid.begin(); it != marblesLaid.end(); ++it)
    {
        if(*it == *current)
        {
            std::cout << "(" << *it << ") ";
        }
        else
        {
            std::cout << *it << " ";
        }
    }
    std::cout << '\n';
}

int main()
{
    const int PLAYERS = 452;
    std::array<unsigned long, PLAYERS> SCORES{};
    const int MARBLES = 100 * 70784; // 0 based

    int nextMarble = 1;
    
    int player = 1; //0 based
    std::list<int> marblesLaid {0}; //single element
    auto current = marblesLaid.begin();
    
    int iter = 0;
    
    while(nextMarble <= MARBLES)
    {
        //if() // marble %23
            //std::cout << "P" << player << '\n';
            if(player == 0)
                std::cout << iter++ << '\n';
            
            if(nextMarble % 23 != 0)
            {
                //unsigned int dst = current + 2;
                
                current++;
                if(current == marblesLaid.end())
                    current = marblesLaid.begin();
                
                current++;
                
                
                //if(dst > marblesLaid.size())
                //{
                    //dst = dst - marblesLaid.size();
                //}
                
                //if(dst == marblesLaid.size())
                //{
                    //marblesLaid.push_back(nextMarble++);
                    //current = marblesLaid.size() - 1;
                //}
                //else
                //{
                    
                    current = marblesLaid.insert(current, nextMarble++);
                //}
            }
            else
            {
                SCORES[player] += nextMarble++;
                auto toRemove = current;
                for(int i = 0; i < 7; ++i)
                {
                    --toRemove;
                    if(toRemove == marblesLaid.begin())
                        toRemove = marblesLaid.end();
                }
               
                //std::cout << "Want to remove" << *toRemove << '\n';
               
                //if(toRemove < 0)
                //{
                    //toRemove = marblesLaid.size() + toRemove;
                //}
                
                //std::cout << "Want to remove" << toRemove << '\n';
                //std::cout << "Size: " << marblesLaid.size() << '\n';
                
                SCORES[player] += *toRemove;
                current = marblesLaid.erase(toRemove);
                
            }
            
            //printVec(marblesLaid, current);
            player = (player + 1) % (PLAYERS);
    }

    std::cout << "Best player's score: " << *std::max_element(SCORES.begin(), SCORES.end()) << '\n';

}
