//452 players; last marble is worth 70784 points

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

void printVec(const std::vector<int>& marblesLaid, unsigned int current)
{
    for(unsigned int i = 0; i < marblesLaid.size(); ++i)
    {
        if(i == current)
        {
            std::cout << "(" << marblesLaid[i] << ") ";
        }
        else
        {
            std::cout << marblesLaid[i] << " ";
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
    unsigned int current = 0;
    int player = 1; //0 based
    std::vector<int> marblesLaid {0}; //single element
    
    int iter = 0;
    
    while(nextMarble <= MARBLES)
    {
        //if() // marble %23
            //std::cout << "P" << player << '\n';
            if(player == 0)
                std::cout << iter++ << '\n';
            
            if(nextMarble % 23 != 0)
            {
                unsigned int dst = current + 2;
                if(dst > marblesLaid.size())
                {
                    dst = dst - marblesLaid.size();
                }
                
                if(dst == marblesLaid.size())
                {
                    marblesLaid.push_back(nextMarble++);
                    current = marblesLaid.size() - 1;
                }
                else
                {
                    marblesLaid.insert(marblesLaid.begin() + dst, nextMarble++);
                    current = dst;
                }
            }
            else
            {
                SCORES[player] += nextMarble++;
                int toRemove = current - 7;
               
                //std::cout << "Want to remove" << toRemove << '\n';
               
                if(toRemove < 0)
                {
                    toRemove = marblesLaid.size() + toRemove;
                }
                
                //std::cout << "Want to remove" << toRemove << '\n';
                //std::cout << "Size: " << marblesLaid.size() << '\n';
                
                //if(toRemove >= marblesLaid.size())
                //{
                    //toRemove = 
                //}
                SCORES[player] += marblesLaid[toRemove];
                marblesLaid.erase(marblesLaid.begin() + toRemove);
                current = toRemove;
            }
            
            //printVec(marblesLaid, current);
            player = (player + 1) % (PLAYERS);
    }

    std::cout << "Best player's score: " << *std::max_element(SCORES.begin(), SCORES.end());

}
