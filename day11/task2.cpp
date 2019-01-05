#include <iostream>

int totalPowers[300][300];

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

int getTotalPower(int x, int y, int dim)
{
    int totalPower = 0;
    
    for(int i = y; i < y + dim; ++i)
    {
        for(int j = x; j < x+dim; ++j)
        {
            totalPower += totalPowers[j-1][i-1];
        }
    }
    
    return totalPower;
}

int main()
{
    const int serialNr = 2568;
    
    for(std::size_t y = 0; y < 300; ++y)
    {
        for(std::size_t x = 0; x < 300; ++x)
        {
            totalPowers[y][x] = getPowerLevel(serialNr, x, y);
        }
    }
    
    std::pair<int, int> xyOfBestSoFar {};
    int pwrBestSoFar = 0;
    int dimBest = 0;
    
    for(int dim = 1; dim <= 300; ++dim) // consider <=
    {
        std::cout << "Dim: " << dim << '\n';
        for(int y = 1; y <= 301 - dim; ++y)
        {
            for(int x = 1; x <= 301 - dim; ++x)
            {
                auto totalPwr = getTotalPower(x, y, dim);
                if(totalPwr > pwrBestSoFar)
                {
                    pwrBestSoFar = totalPwr;
                    xyOfBestSoFar.first = x;
                    xyOfBestSoFar.second = y;
                    dimBest = dim;
                }
            }
        }
    }
    
    std::cout << "Best total for serial: " << serialNr << " is " << pwrBestSoFar << '\n';
    std::cout << "At cell: " << xyOfBestSoFar.second - 1<< "," << xyOfBestSoFar.first - 1 << '\n';
    std::cout << "Dim: " << dimBest << '\n';
}
