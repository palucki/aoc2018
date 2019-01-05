#include <iostream>
#include <vector>
#include <stack>
#include <iterator>
#include <algorithm>

int main()
{
    //const unsigned int minimumReceipes = 51589;
    std::vector<unsigned long> sequenceToFind  = {8,6,4,8,0,1};

    std::deque<unsigned long> recipes = {3, 7};
    
    unsigned long currentElf1Idx = 0;
    unsigned long currentElf2Idx = 1;
    
    bool end = false;
    
    while(!end)
    {
        unsigned int currentElf1 = recipes[currentElf1Idx];
        unsigned int currentElf2 = recipes[currentElf2Idx];
        
        unsigned int sum = currentElf1 + currentElf2;
        
        std::stack<unsigned int> toInsert;
        
        if(sum == 0)
        {
            toInsert.push(0);
        }
        else
        {
            while(sum > 0)
            {
                toInsert.push(sum % 10);
                sum /= 10;
            }
        }
        
        //std::cout << toInsert.size() << '\n';
        
        while(toInsert.size() > 0)
        {
            recipes.push_back(toInsert.top());
            toInsert.pop();
        }
        
        currentElf1Idx = (currentElf1Idx + currentElf1 + 1) % recipes.size();
        //std::cout << "New 1 index: " << currentElf1Idx << '\n';
        currentElf2Idx = (currentElf2Idx + currentElf2 + 1) % recipes.size();
        //std::cout << "New 2 index: " << currentElf2Idx << '\n';
        
        if(recipes.size() % 100000 == 0)
        {
            auto foundPos = std::search(recipes.begin(), recipes.end(), sequenceToFind.begin(), sequenceToFind.end());
            if(foundPos != recipes.end())
            {
                end = true;
                std::cout << "Result " << std::distance(recipes.begin(), foundPos) << '\n';
            }
        }
        
        
        std::cout << recipes.size() << '\n';
    }
    
    //for(auto& e : recipes)
    //{
        //std::cout << e << " ";
    //}
    //std::cout << '\n';
    


    //std::cout << "Result: ";
    //for(auto it = recipes.begin() + minimumReceipes; it != recipes.begin() + minimumReceipes + 10; ++it)
    //{
        //std::cout << *it;
    //}
    
    //std::cout << '\n';
    
    //std::copy(recipes.begin() + minimumReceipes, recipes.end(), std::ostream_iterator<int>(std::cout, ""));
}
