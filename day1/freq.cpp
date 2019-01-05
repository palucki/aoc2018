#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::ifstream fileIn;
    fileIn.open("input");

    std::string line;
    int frequency = 0;

    while(getline(fileIn, line))
    {
        frequency += std::stoi(line);
    }

    std::cout << "Frequency: " << frequency << '\n';

    return 0;
}
