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

std::array<int, 4> reg {10, 10, 110 ,10};

void execute(int opcode, int in1, int in2, int out)
{
    switch(opcode)
    {
        case 9: reg[out] = reg[in1] + reg[in2];          break;   //addr             
        case 11: reg[out] = reg[in1] + in2;               break;   //addi                  
        case 15: reg[out] = reg[in1] * reg[in2];          break;   //mulr             
        case 7: reg[out] = reg[in1] * in2;               break;   //muli                  
        case 5: reg[out] = (reg[in1] & reg[in2]);        break;   //banr           
        case 1: reg[out] = (reg[in1] & in2);             break;   //bani                
        case 6: reg[out] = (reg[in1] | reg[in2]);        break;   //borr           
        case 3: reg[out] = (reg[in1] | in2);             break;   //bori                
        case 8: reg[out] = reg[in1];                     break;   //setr                        
        case 2: reg[out] = in1;                          break;   //seti                             
        case 12: reg[out] = in1 > reg[in2] ? 1 : 0;       break;   //gtir          
        case 14: reg[out] = reg[in1] > in2 ? 1 : 0;       break;   //gtri          
        case 13: reg[out] = reg[in1] > reg[in2] ? 1 : 0;  break;   //gtrr      
        case 4: reg[out] = in1 == reg[in2] ? 1 : 0;      break;   //eqir         
        case 0: reg[out] = reg[in1] == in2 ? 1 : 0;      break;   //eqri         
        case 10: reg[out] = reg[in1] == reg[in2] ? 1 : 0; break;   //eqrr    
        default: std::cout << "ERROR\n"; break;
    }
}

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
                
                if(!canBeAddr(input1, input2, output)) opcodeCanBeInstruction[opcode][0] = false;
                if(!canBeAddi(input1, input2, output)) opcodeCanBeInstruction[opcode][1] = false;
                if(!canBeMulr(input1, input2, output)) opcodeCanBeInstruction[opcode][2] = false;
                if(!canBeMuli(input1, input2, output)) opcodeCanBeInstruction[opcode][3] = false;
                if(!canBeBanr(input1, input2, output)) opcodeCanBeInstruction[opcode][4] = false;
                if(!canBeBani(input1, input2, output)) opcodeCanBeInstruction[opcode][5] = false;
                if(!canBeBorr(input1, input2, output)) opcodeCanBeInstruction[opcode][6] = false;
                if(!canBeBori(input1, input2, output)) opcodeCanBeInstruction[opcode][7] = false;
                if(!canBeSetr(input1, input2, output)) opcodeCanBeInstruction[opcode][8] = false;
                if(!canBeSeti(input1, input2, output)) opcodeCanBeInstruction[opcode][9] = false;
                if(!canBeGtir(input1, input2, output)) opcodeCanBeInstruction[opcode][10] = false;
                if(!canBeGtri(input1, input2, output)) opcodeCanBeInstruction[opcode][11] = false;
                if(!canBeGtrr(input1, input2, output)) opcodeCanBeInstruction[opcode][12] = false;
                if(!canBeEqir(input1, input2, output)) opcodeCanBeInstruction[opcode][13] = false;
                if(!canBeEqri(input1, input2, output)) opcodeCanBeInstruction[opcode][14] = false;
                if(!canBeEqrr(input1, input2, output)) opcodeCanBeInstruction[opcode][15] = false;
            }
        }

        std::cout << "Found " << foundMatchingAtLeastThree << " samples matching at least three instructions\n";
        
        for(std::size_t i = 0; i < 16; ++i)
        {
            std::cout << "op " << std::setw(2) << i << " ";
            for(std::size_t j = 0; j < 16; ++j)
            {
                std::cout << std::setw(2) << opcodeCanBeInstruction[i][j] << ",";
            }
            std::cout << '\n';
        }
        
        myFile.close();
        
        
        std::ifstream myFile2("test2.txt");
        

        
        if(myFile2.is_open())
        {
            std::cout << "Opened 2\n";   
            std::string line;
            
            while(std::getline(myFile2, line))
            {
                std::stringstream ss(line);
                int opcode, input1, input2, output;
                ss >> opcode >> input1 >> input2 >> output;
                execute(opcode, input1, input2, output);
                std::cout << "Register values: " << reg[0] << "," << reg[1] << "," << reg[2] << "," << reg[3] << '\n';
            }
        }
    }
    else
    {
        std::cout << "Unable to open input file\n";
    }


}