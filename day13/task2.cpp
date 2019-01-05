#include <iostream>
#include <fstream>
#include <unordered_set>
#include <set>
#include <vector>
#include <algorithm>

const int XLIMIT = 150;
const int YLIMIT = 150;

std::string area[YLIMIT];

struct Car {
    unsigned int x = 0;
    unsigned int y = 0;
    unsigned int id = 0;
    
    enum class Direction {
        left,
        right,
        up,
        down
    } currentDir = Direction::left;
    Direction beforeDir;
    
    enum class NextCrossingGo {
        left,
        straight,
        right
    } nextDir = NextCrossingGo::left;
    
    Car(unsigned int _x, unsigned int _y, unsigned int _id, Direction _d = Direction::left)
    : x(_x)
    , y(_y)
    , id(_id)
    , currentDir(_d) 
    , beforeDir(_d)
    {
        //std::cout << "Creating car at " << x << " " << y << '\n';
    }
    
    
    
    bool operator<(const Car& rhs)
    {
        if(y < rhs.y)
        {
            return true;
        }
        else if(y == rhs.y && x < rhs.x)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    void update()
    {
        char nextCell = ' ';
        beforeDir = currentDir;
        switch(currentDir)
        {
            case Car::Direction::right:
                nextCell = area[y][x+1];
                std::cout << "Car is going right. Its next place: " << nextCell << "\n";
                if(nextCell == '\\')
                {
                    currentDir = Car::Direction::down;
                }
                else if(nextCell == '/')
                {
                    currentDir = Car::Direction::up;
                }
                else if(nextCell == '+')
                {
                    switch(nextDir)
                    {
                        case Car::NextCrossingGo::straight:
                            currentDir = Car::Direction::right;
                            nextDir = Car::NextCrossingGo::right;
                        break;
                        
                        case Car::NextCrossingGo::right:
                            currentDir = Car::Direction::down;
                            nextDir = Car::NextCrossingGo::left;
                        break;
                        
                        case Car::NextCrossingGo::left:
                            currentDir = Car::Direction::up;
                            nextDir = Car::NextCrossingGo::straight;
                        break;
                    }
                }
                
                x += 1;
                if(x >= XLIMIT)
                {
                    std::cout << "E exceeded for >\n";
                }
                
            break;
        
            case Car::Direction::left:
                nextCell = area[y][x-1];
                std::cout << "Car is going left. Its next place: " << nextCell << "\n";
                if(nextCell == '\\')
                {
                    currentDir = Car::Direction::up;
                }
                else if(nextCell == '/')
                {
                    currentDir = Car::Direction::down;
                }
                else if(nextCell == '+')
                {
                    switch(nextDir)
                    {
                        case Car::NextCrossingGo::straight:
                            currentDir = Car::Direction::left;
                            nextDir = Car::NextCrossingGo::right;
                        break;
                        
                        case Car::NextCrossingGo::right:
                            currentDir = Car::Direction::up;
                            nextDir = Car::NextCrossingGo::left;
                        break;
                        
                        case Car::NextCrossingGo::left:
                            currentDir = Car::Direction::down;
                            nextDir = Car::NextCrossingGo::straight;
                        break;
                    }
                }
                
                
                if(x == 0)
                {
                    std::cout << "E exceeded for <\n";
                }
                else
                {
                    x -= 1;
                }
            break;        
        
            case Car::Direction::up:
                nextCell = area[y-1][x];
                std::cout << "Car is going up. Its next place: " << nextCell << "\n";
                if(nextCell == '\\')
                {
                    currentDir = Car::Direction::left;
                }
                else if(nextCell == '/')
                {
                    currentDir = Car::Direction::right;
                }
                else if(nextCell == '+')
                {
                    switch(nextDir)
                    {
                        case Car::NextCrossingGo::straight:
                            currentDir = Car::Direction::up;
                            nextDir = Car::NextCrossingGo::right;
                        break;
                        
                        case Car::NextCrossingGo::right:
                            currentDir = Car::Direction::right;
                            nextDir = Car::NextCrossingGo::left;
                        break;
                        
                        case Car::NextCrossingGo::left:
                            currentDir = Car::Direction::left;
                            nextDir = Car::NextCrossingGo::straight;
                        break;
                    }
                }
                
                if(y == 0)
                {
                    std::cout << "E exceeded for ^\n";
                }
                else
                {
                    y -= 1;
                }
                
            break;
        
            case Car::Direction::down:
                nextCell = area[y+1][x];
                std::cout << "Car is going down. Its next place: " << nextCell << "\n";
                if(nextCell == '\\')
                {
                    currentDir = Car::Direction::right;
                }
                else if(nextCell == '/')
                {
                    currentDir = Car::Direction::left;
                }
                else if(nextCell == '+')
                {
                    switch(nextDir)
                    {
                        case Car::NextCrossingGo::straight:
                            currentDir = Car::Direction::down;
                            nextDir = Car::NextCrossingGo::right;
                        break;
                        
                        case Car::NextCrossingGo::right:
                            currentDir = Car::Direction::left;
                            nextDir = Car::NextCrossingGo::left;
                        break;
                        
                        case Car::NextCrossingGo::left:
                            currentDir = Car::Direction::right;
                            nextDir = Car::NextCrossingGo::straight;
                        break;
                    }
                }
                
                y += 1;
                if(y >= YLIMIT)
                {
                    std::cout << "E exceeded for v\n";
                }
                
            break;
        }
        
    }
    
};


int main()
{    
    std::ifstream myFile("input");
   
    if(myFile.is_open())
    {
        std::cout << "Opened\n";  
        std::string line;
       
        int i = 0;
        int carId = 0;
        std::vector<Car> cars;
       
        while(std::getline(myFile, line))
        {
            //std::cout << i++ << ": ";
            //std::cout << "Before " << line << std::endl;
           
            for(std::size_t c = 0; c < line.size(); ++c)
            {
                switch(line[c])
                {
                    case '<':
                        std::cout << "Found < car at " << c << ":" << i << std::endl;
                        cars.emplace_back(c, i, carId++, Car::Direction::left);
                        line[c] = '.';
                    break;

                    case '>':
                        std::cout << "Found > car at " << c << ":" << i << std::endl;
                        cars.emplace_back(c, i, carId++, Car::Direction::right);
                        line[c] = '.';
                        //if(line[c-1] == '-' && line[c+1] == '-')
                        //{
                            //std::cout << "replacing with -\n";
                            //line[c] = '-';
                        //}
                        //else if(line[c-1] == '-' && line[c+1] == '-')
                        //{
                            //std::cout << "replacing with -\n";
                            //line[c] = '-';
                        //}
                        //else
                        //{
                           
                        //}
                        //else
                        //{
                            //std::cout << "Unhandled character\n";
                        //}
                    break;
                   
                    case '^':
                        std::cout << "Found ^ car at " << c << ":" << i << std::endl;
                        cars.emplace_back(c, i, carId++, Car::Direction::up);
                        line[c] = '.';
                    break;
                   
                    case 'v':
                        std::cout << "Found v car at " << c << ":" << i << std::endl;
                        cars.emplace_back(c, i, carId++, Car::Direction::down);
                        line[c] = '.';
                    break;
                }
            }
           
            //std::cout << "       " << line << std::endl;
            area[i++] = line;
        }
        //std::cout << '\n';
       
        bool carsCollide = false;
        while(!carsCollide)
        {        
            std::sort(cars.begin(), cars.end());
            std::cout << "After sort:\n";
            for(auto& c : cars)
            {
                std::cout << "(" << c.x << "," << c.y << ")\n";
            }
              
             
                
            //check if any collissions occur
            std::set<int> carsToBeRemoved;
              
                
            for(auto& c : cars)
            {
                c.update();
                    
               
                
                for(std::size_t i = 0; i < cars.size() ; ++i)
                {
                    for(std::size_t j = 0; j < cars.size(); ++j)
                    {
                        if(j == i)
                            continue;
                        
                        if(cars[i].x == cars[j].x && cars[i].y == cars[j].y)
                        {
                            std::cout << "collision at cell (" << cars[i].x << "," << cars[i].y << ")\n";
                            std::cout << "ids to be removed are " << cars[i].id << "," << cars[j].id << "\n";
                            
                            carsToBeRemoved.insert(cars[i].id);
                            carsToBeRemoved.insert(cars[j].id);
                        }
                        //else
                        //{
                            //if(cars[i].beforeDir == Car::Direction::left && cars[j].beforeDir == Car::Direction::right &&
                              //(cars[i].x + 1) == cars[j].x && cars[i].y == cars[j].y)
                            //{
                                //std::cout << "1 DIFFERENT COLISION\n";
                                //carsToBeRemoved.insert(cars[i].id);
                                //carsToBeRemoved.insert(cars[j].id);
                            //}
                            //else if(cars[i].beforeDir == Car::Direction::right && cars[j].beforeDir == Car::Direction::left &&
                                    //cars[i].x == (cars[j].x + 1) && cars[i].y == cars[j].y)
                            //{
                                //std::cout << "2 DIFFERENT COLISION\n";
                                //carsToBeRemoved.insert(cars[i].id);
                                //carsToBeRemoved.insert(cars[j].id);
                            //}
                            //else if(cars[i].beforeDir == Car::Direction::up && cars[i].beforeDir == Car::Direction::down &&
                                    //(cars[i].y + 1) == (cars[j].y ) && cars[i].x == cars[j].x)
                            //{
                                //std::cout << "3 DIFFERENT COLISION\n";
                                //carsToBeRemoved.insert(cars[i].id);
                                //carsToBeRemoved.insert(cars[j].id);
                            //}
                            //else if(cars[i].beforeDir == Car::Direction::down && cars[i].beforeDir == Car::Direction::up &&
                                   //(cars[i].y) == (cars[j].y+1) && cars[i].x == cars[j].x)
                            //{
                                //std::cout << "4 DIFFERENT COLISION\n";
                                //carsToBeRemoved.insert(cars[i].id);
                                //carsToBeRemoved.insert(cars[j].id);
                            //}
                        //}
                        
                        if(cars.size() - carsToBeRemoved.size() <= 1)
                        {
                            carsCollide = true;
                        }
                    }
                }
            }
            
            //use remove if
            cars.erase(std::remove_if(cars.begin(), 
                                      cars.end(),
                                     [&carsToBeRemoved](const Car& c){
                                         return carsToBeRemoved.find(c.id) != carsToBeRemoved.end();
                                      }),
                       cars.end());
            
            if(cars.size() == 1)
            {
                std::cout << "Car at pos " << cars[0].x << "," << cars[0].y << '\n';
                std::cout << "Direction: " << static_cast<unsigned int>(cars[0].currentDir) << "\n";
                std::cout << "Next : " << static_cast<unsigned int>(cars[0].nextDir) << "\n";
            
            }
        }
       
        myFile.close();
    }
    else
    {
        std::cout << "Unable to open input file\n";
    }


}
