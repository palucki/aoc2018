#include <iostream>

int getPowerLevel(int serial, int x, int y)
{
    long rackId = x + 10;
    long powerLevel = rackId * y;
    powerLevel += serial;
    powerLevel *= rackId;
    
    int hundreds = (powerLevel % 1000) / 100;
    hundreds -= 5;
    
    return hundreds;
}

int getTotalPower(int x, int y, int serialNr)
{
    int totalPower = 0;
    
    for(int i = y; i < y + 3; ++i)
    {
        for(int j = x; j < x+3; ++j)
        {
            totalPower += getPowerLevel(serialNr, j, i);
        }
    }
    
    return totalPower;
}


int main()
{
    const int serialNr = 2568;
    std::pair<int, int> xyOfBestSoFar {};
    int pwrBestSoFar = 0;
    
    for(std::size_t y = 0; y < 297; ++y)
    {
        for(std::size_t x = 0; x < 297; ++x)
        {
            auto totalPwr = getTotalPower(x, y, serialNr);
            if(totalPwr > pwrBestSoFar)
            {
                pwrBestSoFar = totalPwr;
                xyOfBestSoFar.first = x;
                xyOfBestSoFar.second = y;
            }
        }
    }
    
    std::cout << "Best total for serial: " << serialNr << " is " << pwrBestSoFar << '\n';
    std::cout << "At cell: " << xyOfBestSoFar.first << "," << xyOfBestSoFar.second << '\n';
}
