#include <iostream>
#include <fstream>
#include <array>
#include <sstream>
#include <iomanip>

int main()
{
    std::ifstream inFile("input");
    
    if(inFile.is_open())
    {
        std::cout << "Opened \n";
        
        std::string line;
        std::array<std::array<int, 1000>, 1000> fabric {};
        
        while(std::getline(inFile, line))
        {
            //std::cout << line << '\n';
            int id, leftPos, topPos, rightPos, bottomPos;
            int tmpInt;
            char tmpChar;
            
            std::stringstream ss(line);
            
            ss >> tmpChar >> id >> tmpChar;
            ss >> leftPos >> tmpChar >> topPos;
            ss >> tmpChar >> tmpInt >> tmpChar;
            rightPos = leftPos + tmpInt - 1;
            
            ss >> tmpInt;
            bottomPos = topPos + tmpInt - 1;
            
            for(int row = topPos; row <= bottomPos; ++row)
            {
                for(int col = leftPos; col <= rightPos; ++col)
                {
                    fabric[row][col] += id; 
                    //printf("x:%d, y:%d\n", row, col);
                }
            }
        }
        
        int count = 0;
        
        for(int row = 0; row < 1000; ++row)
        {
            for(int col = 0; col < 1000; ++col)
            {
                if(fabric[row][col] >= 2)
                {
                    //std::cout << "Found " << fabric[row][col] << '\n';
                    ++count;
                }
            }
        }
        
        //std::cout << "At least two count = " << count << '\n';
        std::cout << "Second pass:\n";
        inFile.clear();
        inFile.seekg(0, std::ios::beg);
      
      
        while(std::getline(inFile, line))
        {
            //std::cout << line << '\n';
            int id, leftPos, topPos, rightPos, bottomPos;
            int tmpInt;
            char tmpChar;
            
            std::stringstream ss(line);
            
            ss >> tmpChar >> id >> tmpChar;
            ss >> leftPos >> tmpChar >> topPos;
            ss >> tmpChar >> tmpInt >> tmpChar;
            rightPos = leftPos + tmpInt - 1;
            
            ss >> tmpInt;
            bottomPos = topPos + tmpInt - 1;
            
            bool ok = true;
            for(int row = topPos; row <= bottomPos; ++row)
            {
                for(int col = leftPos; col <= rightPos; ++col)
                {
                    if(fabric[row][col] != id)
                    {
                        ok = false;
                    }
                    //printf("x:%d, y:%d\n", row, col);
                }
            }
            
            if(ok)
            {
                std::cout << "Found " << id << '\n';
            }
        }        
        
        inFile.close();
    }
        
    

}
