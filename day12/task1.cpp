#include <iostream>
#include <fstream>
#include <unordered_set>
#include <sstream>
#include <vector>
#include <algorithm>

long getSumOfPotsIndexes(const std::string& pots, int indexOffset)
{
    long sumOfPotsIndexes = 0;
    for(int i = 0; i < pots.size(); ++i)
    {
        if(pots[i] == '#')
        {
            sumOfPotsIndexes += i - indexOffset;
        }
    }
    return sumOfPotsIndexes;
}

void printCont(const std::string& cont)
{
    for(auto c : cont)
    {
        std::cout << c;
    }
    std::cout << '\n';
}

int main()
{
    std::ifstream myFile("input");
   
    if(myFile.is_open())
    {
        std::cout << "Opened\n";  
        std::string line;
       
        std::getline(myFile, line);
       
        std::string pots = line.substr(15); //till the end
        //maybe change to list?
        std::unordered_set<std::string> generators;
        std::cout << "initially " << pots << '\n';
        std::getline(myFile, line); //empty line in input
       
        while(std::getline(myFile, line))
        {
            if(line[9] == '#')
            {
                generators.insert(line.substr(0, 5));
                //std::cout << "Good generator: " << line.substr(0, 5) << '\n';
            }           
        }
        std::cout << "Generation: " << 0 << '\n';
        printCont(pots);
       
        const unsigned long GENERATIONS = 10000;
        int indexOffset = 0;
        std::string newGenPots = pots;
        for(unsigned long i = 0; i < GENERATIONS; ++i)
        {
            std::string longerPots = "...." + pots + "....";
            std::string newGenCandidate = ".." + pots + "..";
            for(std::size_t j = 0; j < pots.size() + 4; ++j)
            {
                std::string neighbourhood = longerPots.substr(j, 5);
                //std::cout << "Searching for: " << neighbourhood << '\n';
                auto found = generators.find(neighbourhood);
                if(found != generators.end())
                {
                    newGenCandidate[j] = '#';
                }
                else
                {
                    newGenCandidate[j] = '.';
                }
            }
            
            indexOffset += 2;
           
            pots = newGenCandidate;
            
            
            //printCont(pots);
            //if((i+1) % 2 == 0)
            //{
                std::cout << i+1 << ',';
                std::cout << getSumOfPotsIndexes(pots, indexOffset) << '\n';
            //}
        }
       
        
       
        myFile.close();
    }
    else
    {
        std::cout << "Unable to open input file\n";
    }
}
