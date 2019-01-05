#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <set>
#include <algorithm>

std::set<char> preStepsForStep['Z'-'A'+1];              //UPDATE
bool used['Z'-'A'+1] = {false};
int timeHasCome['Z'-'A'+1] = {0};

void showUsed()
{
    std::cout << "ABCDEFEGHIJKLMNPQRSTUVWXYZ - used?\n";
    
    for(char i = 'A'; i <= 'Z'; ++i)
    {
        std::cout << ((used[i - 'A']) ? "X" : " ");
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
        std::string sequence = "";


        // std::set<char> nextStepsForStep['Z'-'A'+1];
        
        while(std::getline(myFile, line))
        {
            char prev = line[5];
            char next = line[36];
            
            preStepsForStep[next - 'A'].insert(prev);
            // nextStepsForStep[prev - 'A'].insert(next);
        }
        
        showUsed();
                
        //perform first step (insert all without prerequisities)
        for(char i = 'A'; i <= 'Z'; ++i)
        {
            timeHasCome[i - 'A'] = 60 + i - 'A';
        }

        showUsed();

        int second = 1;

        while(sequence.size() < 'Z' - 'A')
        {
            for(char i = 'A'; i <= 'Z'; ++i)
            {
                bool allFound = true;
                for(auto step : preStepsForStep[i - 'A'])
                {
                    if(!used[step - 'A'])
                    {
                        allFound = false;
                    }
                }
                
                if(allFound && !used[i - 'A'] && timeHasCome[i - 'A'] == 0)
                {
                    std::cout << "will insert " << i << '\n';
                    used[i - 'A'] = true;
                    sequence += i;
                    break;
                }
                else
                {
                    --timeHasCome[i - 'A'];
                }
            }
            showUsed();
            std::cout << "Sequence in second " << second++ << " = " << sequence << '\n';
        } 
        
        myFile.close();
    }
    else
    {
        std::cout << "Unable to open input file\n";
    }


}
