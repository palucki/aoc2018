#include <iostream>
#include <fstream>
#include <unordered_set>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>

std::array<int, 4> prevReg {};
std::array<int, 4> afterReg {};
std::array<std::array<bool, 16>, 16> opcodeCanBeInstruction;

void resetTable()
{
    for(int i = 0; i < 16; ++i)
    {
        for(int j = 0; j < 16; ++j)
        {
            opcodeCanBeInstruction[i][j] = true;
        }
    }
}

bool canBeAddr(int in1, int in2, int out)
{
    if(in2 >= 0 && in2 <= 3)
        return afterReg[out] == prevReg[in1] + prevReg[in2];
    
    return false;
}

bool canBeAddi(int in1, int in2, int out)
{
    return afterReg[out] == prevReg[in1] + in2;
}

bool canBeMulr(int in1, int in2, int out)
{
    if(in2 >= 0 && in2 <= 3)
        return afterReg[out] == prevReg[in1] * prevReg[in2];
    
    return false;
}

bool canBeMuli(int in1, int in2, int out)
{
    return afterReg[out] == prevReg[in1] * in2;
}

bool canBeBanr(int in1, int in2, int out)
{
    if(in2 >= 0 && in2 <= 3)
        return afterReg[out] == (prevReg[in1] & prevReg[in2]);
    
    return false;
}

bool canBeBani(int in1, int in2, int out)
{
    return afterReg[out] == (prevReg[in1] & in2);
}

bool canBeBorr(int in1, int in2, int out)
{
    if(in2 >= 0 && in2 <= 3)
        return afterReg[out] == (prevReg[in1] | prevReg[in2]);
    
    return false;
}

bool canBeBori(int in1, int in2, int out)
{
    return afterReg[out] == (prevReg[in1] | in2);
}

bool canBeSetr(int in1, int in2, int out)
{
    if(in2 >= 0 && in2 <= 3)
        return afterReg[out] == prevReg[in1];
    
    return false;
}

bool canBeSeti(int in1, int in2, int out)
{
    return afterReg[out] == in1;
}

bool canBeGtir(int in1, int in2, int out)
{
    if(afterReg[out] == 1)
    {
        if(in2 >= 0 && in2 <= 3)
        {
            return in1 > prevReg[in2];
        }
    }
    else if(afterReg[out] == 0)
    {
        if(in2 >= 0 && in2 <= 3)
        {
            return in1 <= prevReg[in2];
        }
    }
    
    return false;
}



bool canBeGtri(int in1, int in2, int out)
{
    if(afterReg[out] == 1)
    {
        if(in1 >= 0 && in1 <= 3)
        {
            return prevReg[in1] > in2;
        }
    }
    else if(afterReg[out] == 0)
    {
        if(in1 >= 0 && in1 <= 3)
        {
            return prevReg[in1] <= in2;
        }
    }
    
    return false;
}

bool canBeGtrr(int in1, int in2, int out)
{
    if(afterReg[out] == 1)
    {
        if(in1 >= 0 && in1 <= 3 && in2 >= 0 && in2 <= 3)
        {
            return prevReg[in1] > prevReg[in2];
        }
    }
    else if(afterReg[out] == 0)
    {
        if(in1 >= 0 && in1 <= 3 && in2 >= 0 && in2 <= 3)
        {
            return prevReg[in1] <= prevReg[in2];
        }
    }
    
    return false;
}

bool canBeEqir(int in1, int in2, int out)
{
    if(afterReg[out] == 1)
    {
        if(in2 >= 0 && in2 <= 3)
        {
            return in1 == prevReg[in2];
        }
    }
    else if(afterReg[out] == 0)
    {
        if(in2 >= 0 && in2 <= 3)
        {
            return in1 != prevReg[in2];
        }
    }
    
    return false;
}

bool canBeEqri(int in1, int in2, int out)
{
    if(afterReg[out] == 1)
    {
        if(in1 >= 0 && in1 <= 3)
        {
            return prevReg[in1] == in2;
        }
    }
    else if(afterReg[out] == 0)
    {
        if(in1 >= 0 && in1 <= 3)
        {
            return prevReg[in1] != in2;
        }
    }
    
    return false;
}

bool canBeEqrr(int in1, int in2, int out)
{
    if(afterReg[out] == 1)
    {
        if(in1 >= 0 && in1 <= 3 && in2 >= 0 && in2 <= 3)
        {
            return prevReg[in1] == prevReg[in2];
        }
    }
    else if(afterReg[out] == 0)
    {
        if(in1 >= 0 && in1 <= 3 && in2 >= 0 && in2 <= 3)
        {
            return prevReg[in1] != prevReg[in2];
        }
    }
    
    return false;
}



int main(int argc, char* argv[])
{
    std::ifstream myFile("test1.txt");
    int i = 0;
    if(myFile.is_open())
    {
        std::cout << "Opened\n";   
        std::string line;
        int foundMatchingAtLeastThree = 0;
        resetTable();
        
        while(std::getline(myFile, line))
        {
            std::stringstream ss(line);
            std::string tempS;
            char tempC;
            int opcode, input1, input2, output;
            switch(i)
            {
                case 0:
                    ss >> tempS >> tempC >> prevReg[0]
                                >> tempC >> prevReg[1]
                                >> tempC >> prevReg[2]
                                >> tempC >> prevReg[3];
                    break;
                
                case 1: 
                    ss >> opcode >> input1 >> input2 >> output;
                    break;
                case 2:
                    ss >> tempS >> tempC >> afterReg[0]
                                >> tempC >> afterReg[1]
                                >> tempC >> afterReg[2]
                                >> tempC >> afterReg[3];
                    break;
                default:
                    break;
            }
            
            if(++i > 3)
            {
                i = 0;
                int found = 0;
                // std::cout << "reg:       " << prevReg[0] << prevReg[1] <<prevReg[2] <<prevReg[3] << '\n';
                // std::cout << "after reg: " << afterReg[0] << afterReg[1] <<afterReg[2] <<afterReg[3] << '\n';
                // std::cout << "opcode " << opcode << " " << input1 << " " << input2 << " " << output << '\n';
                
                found += canBeAddr(input1, input2, output) ? 1 : 0;
                found += canBeAddi(input1, input2, output) ? 1 : 0;
                found += canBeMulr(input1, input2, output) ? 1 : 0;
                found += canBeMuli(input1, input2, output) ? 1 : 0;
                found += canBeBanr(input1, input2, output) ? 1 : 0;
                found += canBeBani(input1, input2, output) ? 1 : 0;
                found += canBeBorr(input1, input2, output) ? 1 : 0;
                found += canBeBori(input1, input2, output) ? 1 : 0;
                found += canBeSetr(input1, input2, output) ? 1 : 0;
                found += canBeSeti(input1, input2, output) ? 1 : 0;
                found += canBeGtir(input1, input2, output) ? 1 : 0;
                found += canBeGtri(input1, input2, output) ? 1 : 0;
                found += canBeGtrr(input1, input2, output) ? 1 : 0;
                found += canBeEqir(input1, input2, output) ? 1 : 0;
                found += canBeEqri(input1, input2, output) ? 1 : 0;
                found += canBeEqrr(input1, input2, output) ? 1 : 0;
                
                if(found >= 3)
                {
                    ++foundMatchingAtLeastThree;
                }
                else if(found == 1)
                {
                    std::cout << "Opcode " << opcode << " matches only one\n";
                }
            }
        }

        std::cout << "Found " << foundMatchingAtLeastThree << " samples matching at least three instructions\n";
        
        // for(std::size_t i = 0; i < 16; ++i)
        // {
            // std::cout << "Op " << std::setw(2) << i << " ";
            // for(auto candidate : opcodesCount[i])
            // {
                // std::cout << std::setw(2) << candidate << ",";
            // }
            // std::cout << '\n';
        // }
        
        myFile.close();
    }
    else
    {
        std::cout << "Unable to open input file\n";
    }


}