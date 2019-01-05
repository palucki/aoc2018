#include <iostream>
#include <fstream>
#include <array>
#include <sstream>
#include <iomanip>
#include <map>
#include <algorithm>

int main()
{
    std::ifstream inFile("input");
        

    if(inFile.is_open())
    {
        std::cout << "Opened \n";
        
        std::string line;
        
        std::getline(inFile, line);
        
        inFile.close();
        
        bool sizeChanged = true;
        
        while(sizeChanged)
        {
            
            
        }
        
        std::cout << "Resulting polimer size: " << line.size() << '\n';
    }
}
