#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <sstream>
#include <utility>

struct Point {
    enum Direction {
        Forward,
        Back
    };
    long x = 0;
    long y = 0;
    int vx = 0;
    int vy = 0;

    void update(Direction dir)
    {
        if(dir == Forward)
        {
            x += vx;
            y += vy;
        }
        else
        {
            x -= vx;
            y -= vy;
        }
    }
    
    bool insideWindow(int winX, int winY)
    {
        //if(x >= centreXY.first - winX && x <= centreXY.first + winX &&
           //y >= centreXY.second - winY && y <= centreXY.second + winY)
            //return true;
        
        //std::cout << "original   " << x << ":" << y << "\n";
        
        if(x > 0 && x < 2*winX &&
           y > 0 && y < 2*winY)
            return true;
            
        return false;
    }
};

std::vector<Point> points;

void normalize(int minX, int minY)
{
    std::cout << "Normalize. MinX: " << minX << " minY: " << minY <<'\n';
    for(auto& p : points)
    {
        std::cout << "Before: " << p.x << ":" << p.y << '\n';
        p.x -= minX;
        p.y -= minY;
        std::cout << "After: " << p.x << ":" << p.y << '\n';
    }
}

std::pair<int, int> update(Point::Direction dir)
{ 
    long minX = 100000;
    long minY = 100000;
    //int maxY = 0;
    
    for(auto& p : points)
    {
        if(minX > p.x) minX = p.x;
        if(minY > p.y) minY = p.y;
        p.update(dir);
    }
    
    std::pair<int, int> xy = {minX, minY};
    
    return xy;
}


void display(int minX, int minY)
{
    constexpr int DIMX = 80;
    constexpr int DIMY = 15;
    std::array<std::array<bool, 2*DIMX>, 2*DIMY> area;

    for(int i = 0; i < 2*DIMY; ++i)
    {
        for(int j = 0; j < 2*DIMX; ++j)
        {
            area[i][j] = false;
        }
    }

    for(auto& p : points)
    {
        if(p.insideWindow(DIMX, DIMY))
        {
            //std::cout << "original   " << p.x << ":" << p.y << "\n";
            //std::cout << "mapped to: " << p.x + DIMX << ":" << p.y + DIMY<< "\n";
            ////area[p.y + centreXY.second - DIMY/2][p.x + centreXY.first - DIMX/2] = true;
            area[p.y][p.x] = true;
        }
        
    }

    for(int i = 0; i < 2*DIMY; ++i)
    {
        for(int j = 0; j < 2*DIMX; ++j)
        {
            if(area[i][j])
            {
                std::cout << "X";
            }
            else
            {
                std::cout << " ";
            }
        }
        std::cout << '\n';
    }
}

int main()
{
    std::ifstream inFile("input");
    std::string line;

    if(inFile.is_open())
    {
        while(std::getline(inFile, line))
        {
            const int XPOS = 10; //len 6
            const int YPOS = 18; //len 6
            const int VXPOS = 36; //len 2
            const int VYPOS = 40; //len 2
            
            int x, y, vx, vy;

            x = std::stoi(line.substr(XPOS, 6));
            y = std::stoi(line.substr(YPOS, 6));
            vx = std::stoi(line.substr(VXPOS, 2));
            vy = std::stoi(line.substr(VYPOS, 2));
            
            std::cout << "x " << x << " y " << y
                      << " vx " << vx << " vy " << vy << '\n';

            points.push_back({x, y, vx, vy});
        }
        
        //auto oldPointXX = update(Point::Forward);
        auto minXY = update(Point::Forward);
        //int minLenX = abs(minXY.first - minXY.second);
        
        
        
        //while(true)
        //{
            //minXY = update(Point::Forward);
            //if(abs(minXY.first - minXY.second) < minLenX)
            //{
                //minLenX = abs(minXY.first - minXY.second);
                //std::cout << "New min len: " << minLenX <<'\n';
                //std::cout << "For point: " << minXY.first << ":" << minXY.second << '\n';
                
                //if(minLenX == 89)
                //{
                    //while(true)
                    //{
                        //normalize(minXY.first, minXY.second);
                        //display();
                        //char dec;
                        //std::cin >> dec;
                        //minXY = update(dec == 'b' ? Point::Back : Point::Forward);
                        
                        //std::cout << "Mins: " << minXY.first << ":" << minXY.second << '\n';
                    //}
                //}
            //}
        //}
        
        int iteration = 0;
        
        for(int i = 0; i < 10885; ++i)
        {
            iteration++;
            minXY = update(Point::Forward);
        }
        
        while(true)
        {
            iteration++;
            normalize(minXY.first, minXY.second);
            display(minXY.first, minXY.second);
            char dec;
            std::cin >> dec;

            std::cout << "it: " << iteration << '\n';
            minXY = update(dec == 'b' ? Point::Back : Point::Forward);

            
            std::cout << "New mins " << minXY.first << ":" << minXY.second << '\n';
        }

        inFile.close();
    }
}
