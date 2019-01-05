#include <iostream>
#include <fstream>
#include <array>
#include <sstream>
#include <iomanip>
#include <map>
#include <algorithm>

struct Guard {
    //explicit Guard(int _id) : id(_id) {}

    int id;
    int napTime = 0;
    
    void addNap(int minutes)
    {
        napTime += minutes;
    }
    
};

int getMostSleepyGuardId(const std::map<int, Guard>& g)
{
    auto max = std::max_element(g.begin(), g.end(), [](std::pair<int, Guard> lhs, std::pair<int, Guard> rhs){
        return lhs.second.napTime < rhs.second.napTime;
        });
    
    return max->first;
}

int main()
{
    std::ifstream inFile("input");
    
    std::vector<std::string> data;
    std::map<int, Guard> guards;
    
    if(inFile.is_open())
    {
        std::cout << "Opened \n";
        
        std::string line;
        
        while(std::getline(inFile, line))
        {
            //std::cout << line << '\n';
            data.push_back(line);
            
        }
        
        std::sort(data.begin(), data.end());
        
        int id, hour, minute, oldMinute;
        int tmpInt;
        char tmpChar;
        std::string tmpString;

        int sleepMinutes[60] = {0};

        for(const auto& l : data)
        {
            std::stringstream ss(l);
            
            ss >> tmpChar >> tmpInt >> tmpChar >> tmpInt >> tmpChar >> tmpInt >> tmpChar >> hour >> tmpChar >> minute;
            
            //std::cout << std::setw(2) << hour << ":" << minute << '\n';
            
            ss >> tmpChar >> tmpString;
            
            if(tmpString == "Guard")
            {
                ss >> tmpChar >> id;
                std::cout << "Guard " << id << '\n';
            }
            else if(tmpString == "falls")
            {
                std::cout << "Sleeps from " << hour << ":" << minute << '\n';
            }
            else if(tmpString == "wakes")
            {
                std::cout << "Sleeps to " << hour << ":" << minute << '\n';
                guards[id].addNap(minute - oldMinute);
                
                if(id == 1823)
                {
                    for(int i = oldMinute; i <= minute; ++i)
                    {
                        ++sleepMinutes[i];
                    }
                }
            }
            
            oldMinute = minute;
        }
        
        std::cout << "Found: " << guards.size() << " guards\n";
        
        for(auto g : guards)
        {
            std::cout << "#" << g.first << " sleeped " << g.second.napTime << " mins\n";
        }
        
        std::cout << "the most sleepy: " << getMostSleepyGuardId(guards) << '\n';
        
        for(int i = 0 ; i < 60; ++i)
        {
            std::cout << i << " = " << sleepMinutes[i] << '\n';
        }
        
        inFile.close();
    }
}
