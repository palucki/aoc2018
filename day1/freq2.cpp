#include <iostream>
#include <fstream>
#include <string>
#include <set>

int main()
{
    std::ifstream fileIn;
    fileIn.open("input");

    std::string line;
    int frequency = 0;

    std::set<int> freqs;
    freqs.insert(frequency);

    while(true)
    {
    fileIn.clear();
    fileIn.seekg(0, std::ios::beg);
    
    while(getline(fileIn, line))
    {
        int theFreq = std::stoi(line);
        frequency += theFreq;

        if(freqs.find(frequency) != freqs.end())
        {
            std::cout << "Frequency found  twice: " << frequency << '\n';
            return 0;
        }
        else
        {
            freqs.insert(frequency);
        }
    }
    }
    return 0;
}
