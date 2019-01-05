#include <iostream>
#include <fstream>
#include <array>
#include <sstream>
#include <iomanip>
#include <map>
#include <algorithm>

struct Guard {
    //explicit Guard(int _id) : id(_id) {}
    int sleepMinutes[60] = {0};
    
    void addNap(int start, int stop)
    {
        for(int i = start; i <= stop; ++i)
        {
            ++sleepMinutes[i];
        }
    }
    
    std::pair<int, int> getMostFrequentlySleepedMin()
    {
        auto elem = std::max_element(std::begin(sleepMinutes), std::end(sleepMinutes));
        auto minute = elem - std::begin(sleepMinutes);
        
        return {minute, *elem};
    }
};

int getMostSleepyGuardId(const std::map<int, Guard>& g)
{
    int maxMinute = 0;
    int maxTimes = 0;
    int maxId = 0;
    
    for(auto elem : g)
    {
        auto minPair = elem.second.getMostFrequentlySleepedMin();
        int minute = minPair.first;
        int times = minPair.second;
        
        std::cout << "Guard " << elem.first << " sleeped mostly at minute " << minute << ". Times: " << times << '\n';
        
    }
    
    return 0;
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
                guards[id].addNap(oldMinute, minute);
            }
            
            oldMinute = minute;
        }
        
        std::cout << "Found: " << guards.size() << " guards\n";
        
        std::cout << "the most sleepy minute: " << getMostSleepyGuardId(guards) << '\n';
        
        inFile.close();
    }
}
