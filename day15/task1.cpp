#include <iostream>
#include <fstream>
#include <unordered_set>
#include <sstream>
#include <list>
#include <algorithm>
#include <memory>

#include "IPositioned.h"

const int SIZE_X = 9;
const int SIZE_Y = 9;

char map[SIZE_Y][SIZE_X] = {0};

bool debug = false;
bool fullyFinished = true;

using uint = unsigned int;
using Point = std::pair<uint, uint>;

class Unit : public IPositioned {
public:
    enum class Type {
        Elf,
        Goblin
    } type;
    
    Unit(Type _t, uint _x, uint _y) : IPositioned(_x, _y), type(_t) { }
    
    char getMark()
    {
        return type == Type::Elf ? 'E' : 'G';
    }
    
    void move(uint newX, uint newY)
    {
        if(debug)
        {
            std::cout << "Moving from " << x << "," << y << " to " << newX << "," << newY << '\n';
        }
        map[y][x] = '.';

        if(map[newY][newX] == '.')
        {
            map[newY][newX] = getMark();
            x = newX;
            y = newY;
        }
        else
        {
            if(debug)
            {
                std::cout << "Unable to move, blocked cell\n";
            }
        }
    }
    
    void setAdjacentCells(const std::vector<std::pair<uint, uint>>& _adjacentCells)
    {
        adjacentCells = _adjacentCells;
    }
    
    auto getAdjacentFreeCells()
    {
        return adjacentCells;
    }
    
    int getHp() const
    {
        return hp;
    }
    
    bool attack(uint8_t damage)
    {
        //indicate whether remove the unit or not
        if(hp > 0)
        {
            hp -= damage;
            if(hp <= 0)
            {
                hp = 0;
                map[y][x] = '.';
                return true;
            }
        }
        
        return false;
    }
    
    static const uint8_t attackPower = 3;
private:
    int hp = 200;
    
    std::vector<std::pair<uint, uint>> adjacentCells; //initialize with 0
};


bool compareDereferenced(const std::unique_ptr<Unit>& lhs, const std::unique_ptr<Unit>& rhs)
{
    return *lhs < *rhs;
}

bool isElf(const std::unique_ptr<Unit>& lhs)
{
    return lhs->type == Unit::Type::Elf;
}

std::list<std::unique_ptr<Unit>> units;

auto findAdjacentFreeCells(uint x, uint y)
{
    std::vector<Point> freeCells;
    
    if(x > 0 && x < SIZE_X - 1 && y > 0 && y < SIZE_Y - 1)
    {
        if(map[y-1][x] == '.')
        {
            //std::cout << x << "," << y-1 << '\n';
            freeCells.emplace_back(x, y-1);
        }
        
        if(map[y+1][x] == '.')
        {
            //std::cout << x << "," << y+1 << '\n';
            freeCells.emplace_back(x, y+1);
        }
        
        if(map[y][x-1] == '.')
        {
            freeCells.emplace_back(x-1, y);
        }
            
        if(map[y][x+1] == '.')
            freeCells.emplace_back(x+1, y);
    }
    
    //std::cout << "Found " << freeCells.size() << " free cells adjacent to " << x << "," << y << '\n';
    
    return freeCells;
}

//bool enemiesPresent()
//{
    //bool goblinFound = false;
    //bool elfFound = false;
    
    //for(auto& u : units)
    //{
        //if(u->type == Unit::Type::Elf)
        //{
            //elfFound = true;
        //}
        //else if(u->type == Unit::Type::Goblin)
        //{
            //goblinFound = true;
        //}
    //}
    
    //return goblinFound && elfFound;
//}

void displayMapWithUnits()
{
    //char displayedMap[SIZE_Y][SIZE_X] = {0};
    //for(std::size_t i = 0; i < SIZE_Y; ++i)
    //{
        //for(std::size_t j = 0; j < SIZE_X; ++j)
        //{
            //displayedMap[i][j] = map[i][j];
        //}
    //}
      
    //for(auto& c : units)
    //{
        //displayedMap[c->y][c->x] = c->getMark();
    //}
    
    
    for(std::size_t i = 0; i < SIZE_Y; ++i)
    {
        for(std::size_t j = 0; j < SIZE_X; ++j)
        {
            std::cout << map[i][j];
        }
        std::cout << '\n';
    }
    
    for(auto& u : units)
    {
        std::cout << "Unit at " << u->x << "," << u->y << " HP: " << u->getHp() << '\n';
    }
}

void setAllAdjacentCells()
{
    for(auto& u : units)
    {
        u->setAdjacentCells(findAdjacentFreeCells(u->x, u->y));
    }
}

void readMap(const std::string& file)
{
    std::ifstream myFile(file);
    
    std::string line;
    std::size_t i = 0;
    
    while(std::getline(myFile, line) && i < SIZE_Y)
    {
        //std::cout << line << std::endl;
        for(std::size_t j = 0; j < SIZE_X; ++j)
        {
            map[i][j] = line[j];

            if(line[j] == 'E')
            {
                //std::cout << "Elf at " << j << ":" << i << '\n';
                auto elf = std::make_unique<Unit>(Unit::Type::Elf, j, i);
                //elf->setAdjacentCells(getAdjacentFreeCells(j, i));
                
                units.insert(units.end(), std::move(elf));
                
            }
            else if(line[j] == 'G')
            {
                //std::cout << "Goblin at " << j << ":" << i << '\n';
                auto goblin = std::make_unique<Unit>(Unit::Type::Goblin, j, i);
                //goblin->setAdjacentCells(getAdjacentFreeCells(j, i));
                
                units.insert(units.end(), std::move(goblin));
            }
        }
        ++i;
    }
}

bool PairValidAndLessThan(std::pair<bool, uint> lhs, std::pair<bool, uint> rhs) 
{
    //std::cout << "Compare " << lhs.second << " with " << rhs.second << '\n';
    //std::cout << "Valid? L: " << std::boolalpha << lhs.first << " R: " <<rhs.first << '\n';
    if(lhs.first)
    {
        if(rhs.first)
        {
            //std::cout << "1";
            return lhs.second < rhs.second;
        }
        else
        {
            //std::cout << "2";
            return true;
        }
    }
    else
    {
        //std::cout << "3";
        return false;
    }
}

#include <map>
#include <stack>
#include <set>

struct Node {
    Node(uint _x, uint _y, int _cost) : x(_x), y(_y), cost(_cost) {}
    uint x;
    uint y;
    int cost;
    std::set<Point> bestPreviousSteps;
    //std::set<Point> bestNextSteps;
    bool operator<(const Node& rhs) const
    {
        return cost < rhs.cost;
    }
};

//template< class T1, class T2 >
//bool operator<( const std::pair<T1,T2>& lhs, const std::pair<T1,T2>& rhs ) = delete;

bool lessThan(Point lhs, Point rhs)
{
    //std::cout << "comparing\n";
    if(lhs.second < rhs.second)
    {
        return true;
    }
    else if(lhs.second == rhs.second && lhs.first < rhs.first)
    {
        return true;
    }
    else
    {
        return false;
    }
}

struct CustomCompare
{
    bool operator()(const Point& lhs, const Point& rhs)
    {
        //std::cout << "Custom compare\n";
        return lessThan(lhs, rhs);
    }
};

std::vector<Node> calculatedNodes;
std::vector<Node> waitingForVisit;
std::set<Point, CustomCompare> possibleSteps;

void findPaths(auto nodeIt, Point srcNode)
{
    
    
    if(nodeIt->x == srcNode.first && nodeIt->y == srcNode.second)
    {
        std::cout << "Reached target\n";
        return;
    }
    else
    {
        //std::cout << "currently at " << nodeIt->x << "," << nodeIt->y << " searching for " << srcNode.first << "," << srcNode.second << '\n';
    }
    
    //std::string path = "";
    
    if(!nodeIt->bestPreviousSteps.empty())
    {
        //path += "[";
        //uint x = 0;
        //uint y = 0;        
        //std::cout << "Node " << nodeIt->x << "," << nodeIt->y << " has " << nodeIt->bestPreviousSteps.size() << " possible previous\n";
        
        for(auto prev : nodeIt->bestPreviousSteps)
        {
            if(prev.first == srcNode.first && prev.second == srcNode.second)
            {
                //std::cout << "Next step is the final (first) step!\n";
                possibleSteps.insert({nodeIt->x, nodeIt->y});
            }
            else
            {
                //std::cout << "Searching among " << calculatedNodes.size() << " nodes\n";
                //std::cout <<  " " + std::to_string(prev.first) + "," + std::to_string(prev.second);
                auto prevNodeIt = std::find_if (calculatedNodes.begin(), calculatedNodes.end(), [prev](const Node& n){
                    //std::cout << "3";
                    return (n.x == prev.first && n.y == prev.second);});
                
                if(prevNodeIt != calculatedNodes.end())  
                {  
                    //prevNodeIt->bestNextSteps.insert(prev);
                    findPaths(prevNodeIt, srcNode);
                }
                else
                {
                    std::cout << "FATAL ERROR! Previous step not found in calculated nodes\n";
                }
            }
        }
        //std::cout << '\n';
        //path += " ]";
        
        //nodeIt = std::find_if (calculatedNodes.begin(), calculatedNodes.end(), [x,y](const Node& n){
           //return (n.x == x && n.y == y);}); //now prints only one path!
        
        //if(nodeIt == calculatedNodes.end())
        //{
            //return path;
        //}
    }

    //return path;
}

void checkNeighbour(Node src, Node myNode)
{
    auto it = std::find_if (calculatedNodes.begin(), calculatedNodes.end(), [myNode](const Node& n){
           //std::cout << "4";
           return (n.x == myNode.x && n.y == myNode.y);});
    if(it != calculatedNodes.end())
    {
        auto foundCost = it->cost;
        if(foundCost > 1 + src.cost)
        {
            it->cost = 1 + src.cost;

            it->bestPreviousSteps.clear();
            
            it->bestPreviousSteps.insert({src.x, src.y});
        }
        else if(foundCost == 1 + src.cost)
        {
            //std::cout << "Extending for cost = " << foundCost << "!\n";
            
            
            //check for duplicates!
            //it->bestPreviousSteps.find();
            
            it->bestPreviousSteps.insert({src.x, src.y});
            
        }
    }
    else
    {
        auto it = std::find_if (waitingForVisit.begin(), waitingForVisit.end(), [myNode](const Node& n){
            //std::cout << "5";
            return (n.x == myNode.x && n.y == myNode.y);});
        if(it == waitingForVisit.end() && map[myNode.y][myNode.x] == '.')
        {
            waitingForVisit.push_back(myNode);
        }
        
        //check if myNode is valid???
        
        myNode.bestPreviousSteps.insert({src.x, src.y});
        myNode.cost = src.cost + 1;
        //std::cout << "Adding cost " << 1 + src.cost << " for node " << myNode.x << "," << myNode.y << '\n';
        
        if(map[myNode.y][myNode.x] == '.')
            calculatedNodes.push_back(myNode);
        else
        {
            //std::cout << "(" << map[myNode.y][myNode.x] << ") ";
            //std::cout << "invalid point...\n";
        }
        
        //std::cout << "Calculated size: " << calculatedNodes.size() << '\n';
            
    }
}

void calculateDistances(Node src, bool initial = false)
{   
    //std::cout << "AT: " <<  src.x << "," << src.y << '\n';
    
    if(src.x >= SIZE_X || src.y >= SIZE_Y || (map[src.y][src.x] != '.' && !initial))
    {
       //std::cout << "Exceeded limit at " << src.x << "," << src.y << '\n';
       //auto it = std::find_if (waitingForVisit.begin(), waitingForVisit.end(), [src](const Node& n){
           //return (n.x == src.x && n.y == src.y);});
       
       //if(it != waitingForVisit.end())
            //waitingForVisit.erase(it);
        //else
            //std::cout << "ERROR while deleting from waiting\n";
    }
    else
    {
        Node left (src.x - 1, src.y    , 10000);
        Node right(src.x + 1, src.y    , 10000);
        Node up   (src.x    , src.y - 1, 10000);
        Node down (src.x    , src.y + 1, 10000);
        
        checkNeighbour(src, up);
        checkNeighbour(src, right);
        checkNeighbour(src, down);
        checkNeighbour(src, left);

        std::sort(calculatedNodes.begin(), calculatedNodes.end());
        std::sort(waitingForVisit.begin(), waitingForVisit.end());
    }
    
    if(!waitingForVisit.empty())
    {
        //std::cout << "    calculated size : " << calculatedNodes.size() << '\n';
        //std::cout << "    waiting for visit size : " << waitingForVisit.size() << '\n';
        
        auto it = std::find_if (waitingForVisit.begin(), waitingForVisit.end(), [src](const Node& n){
           //std::cout << "6";
           return (n.x == src.x && n.y == src.y);});
       
        if(it != waitingForVisit.end())
            waitingForVisit.erase(it);
        else
        {
               //std::cout << "ERROR while deleting from waiting\n";
        }
         
         
        
        if(waitingForVisit.empty())
        {
            //std::cout << "THE END\n";
            return;
        }
        
        auto nextNode = waitingForVisit.begin();
        auto realNextNode = std::find_if(calculatedNodes.begin(), calculatedNodes.end(), [nextNode](const Node& n){
                        //std::cout << "1";
                        return (n.x == nextNode->x && n.y == nextNode->y);});
        
        if(realNextNode != calculatedNodes.end())
        {
            calculateDistances(*realNextNode); //tu moze byc serioo obug!!!
        }
        else
        {
            std::cout << "Nowhere to go!\n";
        }
    }
}

int getHpFromObjAt(Point xy, Unit::Type type)
{
    auto unit = std::find_if(units.begin(), units.end(), [xy, type](auto& u) {
        //std::cout << "2";
        return u->x == xy.first && u->y == xy.second && u->type != type;        
    });
 
    if(unit != units.end())
    {
        return (*unit)->getHp();
    }
    else
    {
        return -1; //not to consider that object at all
    }
}


std::pair<bool, Point> findTargetWithLeastHp(uint x, uint y, Unit::Type type)
{
    //std::find_if(units.begin(), units.end() []
    //copy if in range !!!
    Point left = {x-1, y};
    Point right = {x+1, y};
    Point up = {x, y-1};
    Point down =  {x, y+1};
    
    Point currentMinHpPoint = {10000, 10000};
    auto minHp = 10000;
    
    //reading order!!! up, left, right, down
    
    auto upHp = getHpFromObjAt(up, type);
    auto leftHp = getHpFromObjAt(left, type);
    auto rightHp = getHpFromObjAt(right, type);
    auto downHp = getHpFromObjAt(down, type);
    bool foundOne = false;
    
    if(upHp > 0 && upHp < minHp)
    {
        currentMinHpPoint = up;
        minHp = upHp;
        foundOne = true;
    }
    
    if(leftHp > 0 && leftHp < minHp)
    {
        currentMinHpPoint = left;
        minHp = leftHp;
        foundOne = true;
    }
    
    if(rightHp > 0 && rightHp < minHp)
    {
        currentMinHpPoint = right;
        minHp = rightHp;
        foundOne = true;
    }
    
    if(downHp > 0 && downHp < minHp)
    {
        currentMinHpPoint = down;
        minHp = downHp;
        foundOne = true;
    }
    
    return {foundOne, currentMinHpPoint};    
}

void moveUnits()
{
    for(auto& u : units)
    {
        bool foundEnemy = false;
        setAllAdjacentCells();
        


                
        int minCost = 10000;
        Point bestStepToMinCost = {1000,1000};
        bool foundPossiblePath = false;
        bool enemyReachable = false;

        //if(u->x == 4 && u->y == 2)
            //debug = true;

        
        auto targetBefore = findTargetWithLeastHp(u->x, u->y, u->type);
        if(targetBefore.first)
        {
            auto targetX = targetBefore.second.first;
            auto targetY = targetBefore.second.second;
            std::cout << "Found valid target! Attacking: " << targetX << "," << targetY << '\n';
            
            auto target = std::find_if(units.begin(), units.end(), [targetX, targetY](auto& u) {
                //std::cout << "7";
                return u->x == targetX && u->y == targetY;});
         
            if(target == units.end())
            {
                std::cout << "Critical error! Not found target!\n";
            }
            else
            {
                if((*target)->attack(u->attackPower))
                {
                    units.erase(target);
                }
            }
            std::cout << "Continuing without calculating the path calculation\n";
            continue;
        }
        
        //bool firstTime = true;
        //Node src(u->x, u->y, 0);
        
        //calculatedNodes.push_back(src);
        //calculateDistances(src, firstTime);

        
        //return;

        auto inRange = u->getAdjacentFreeCells();

        for(auto& other : units)
        {
            
            
            
            
            //auto foundStart = std::find_if (calculatedNodes.begin(), calculatedNodes.end(), [src](const Node& n){
                        //return (n.x == src.x && n.y == src.y);});
            
            if(other->type != u->type)
            {
                foundEnemy = true;
                
                
                
//auto inRange = u->getAdjacentFreeCells();
                


                if((u->x == other->x && u->y + 1 == other->y) || (u->x == other->x && u->y == other->y + 1) ||
                   (u->y == other->y && u->x + 1 == other->x) || (u->y == other->y && u->x == other->x + 1) )
                {
                    enemyReachable = true;
                    std::cout << "Nearest enemy reachable\n";
                    //do not move, attack!
                }
                else
                {
                        //TODO: Added here
                    bool firstTime = true;
                    Node src(other->x, other->y, 0);
                    
                    calculatedNodes.clear();
                    waitingForVisit.clear();
                    
                    calculatedNodes.push_back(src);
                    calculateDistances(src, firstTime);
                    
                    //if(debug)
                    //{
                        //if(debug)
                        {
                            std::cout << "Finding path from " << u->x << "," << u->y << " to ";
                            std::cout << other->x << "," << other->y << '\n';
                            //std::cout << "Calculated nodes size: " << calculatedNodes.size() << "\n";
                        }
                    //}
                    
                    
                    
                    Node dst{u->x, u->y, 0};
                    
                    auto it = std::find_if (calculatedNodes.begin(), calculatedNodes.end(), [dst](const Node& n){
                                    return (n.x == dst.x && n.y == dst.y - 1);});
                    //std::cout << "Up. Cost: " << it->cost << '\n';
                    
                    if(it->cost > 0 && it->cost < minCost)
                    {
                        minCost = it->cost;
                        bestStepToMinCost = {u->x, u->y-1};
                        foundPossiblePath = true;
                    }                
                    
                    it = std::find_if (calculatedNodes.begin(), calculatedNodes.end(), [dst](const Node& n){
                                    return (n.x == dst.x - 1 && n.y == dst.y);});
                    
                    if(it->cost > 0 && it->cost < minCost)
                    {
                        minCost = it->cost;
                        bestStepToMinCost = {u->x - 1, u->y};
                        foundPossiblePath = true;
                    }
                    
                    //std::cout << "Left. Cost: " << it->cost << '\n';
                    
                    it = std::find_if (calculatedNodes.begin(), calculatedNodes.end(), [dst](const Node& n){
                                    return (n.x == dst.x + 1 && n.y == dst.y);});
                    
                    if(it->cost > 0 && it->cost < minCost)
                    {
                        minCost = it->cost;
                        bestStepToMinCost = {u->x + 1, u->y};
                        foundPossiblePath = true;
                    }
                    
                    std::cout << "Need to consider only 'in range' fields to avoid errors\n";
                    
                    //std::cout << "Right. Cost: " << it->cost << '\n';
            
                    it = std::find_if (calculatedNodes.begin(), calculatedNodes.end(), [dst](const Node& n){
                                    return (n.x == dst.x && n.y == dst.y + 1);});
                    //std::cout << "Down. Cost: " << it->cost << '\n';
                    
                    if(it->cost > 0 && it->cost < minCost)
                    {
                        minCost = it->cost;
                        bestStepToMinCost = {u->x, u->y+1};
                        foundPossiblePath = true;
                    }
                    
                    std::cout << "Best step can be taken to: " << bestStepToMinCost.first << "," << bestStepToMinCost.second << '\n';
                }
                /*else
                {
                    //std::cout << "In range size " << inRange.size() << '\n';
                    //std::cout << "Calculated nodes size " << calculatedNodes.size() << '\n';
                    //std::cout << "Units size " << units.size() << '\n';
                    for(auto target : inRange)
                    {
                        auto foundTarget = std::find_if (calculatedNodes.begin(), calculatedNodes.end(), [target](const Node& n){
                            //std::cout << "9";
                            return (n.x == target.first && n.y == target.second);});
                            
                        if(foundTarget != calculatedNodes.end() && foundStart!= calculatedNodes.end())
                        {
                            if(debug)
                            {
                                std::cout << "  " << target.first << "," << target.second << " cost= " << foundTarget->cost << '\n';
                                //std::cout << " path: ";
                            }
                            
                            
                            
                            
                            foundPossiblePath = true;
                            
                            
                            
                            
                            if(minCost > foundTarget->cost)
                            {
                                possibleSteps.clear();
                                findPaths(foundTarget, {u->x, u->y});
                                Point nextBestStep = {possibleSteps.begin()->first, possibleSteps.begin()->second};
                                
                                //std::cout << "The cost is smaller, selecting\n";
                                minCost = foundTarget->cost;
                                bestStepToMinCost = nextBestStep;
                            }
                            else if (minCost == foundTarget->cost)
                            {
                                possibleSteps.clear();
                                findPaths(foundTarget, {u->x, u->y});
                                Point nextBestStep = {possibleSteps.begin()->first, possibleSteps.begin()->second};
                                
                                //std::cout << "The cost is equal\n";
                                if(lessThan(nextBestStep, bestStepToMinCost))
                                {
                                    //std::cout << "Best so far: " << bestStepToMinCost.first << "," << bestStepToMinCost.second;
                                    //std::cout << "new best: " << nextBestStep.first << "," << nextBestStep.second;
                                    //std::cout << "The Point is less, Selecting\n";
                                    bestStepToMinCost = nextBestStep;
                                }
                            }
                            else
                            {
                                //std::cout << "The cost is bigger, ommiting\n";
                            }
                            
                            //if(debug)
                            //{
                                //std::cout << "First step in reading order, from the shortest path is to " << nextBestStep.first << "," << nextBestStep.second;
                                //std::cout << " with cost = " << foundTarget->cost << '\n';
                            //}
                            
                            
                        }
                        else
                        {
                            //std::cout << "  " << target.first << "," << target.second << " cost= " << "NOT FOUND" << '\n';
                        }
                    }
                }*/
            }
        }
        
        
        if(foundPossiblePath && !enemyReachable)
        {
            //if(debug)
            //{
                std::cout << "The unit will move from " << u->x << "," << u->y << " to " 
                          << bestStepToMinCost.first << "," << bestStepToMinCost.second << '\n';
            //}
            
            u->move(bestStepToMinCost.first, bestStepToMinCost.second);            
        }
        
        auto target = findTargetWithLeastHp(u->x, u->y, u->type);
        if(target.first)
        {
            auto targetX = target.second.first;
            auto targetY = target.second.second;
            std::cout << "Found valid target! Attacking: " << targetX << "," << targetY << '\n';
            
            auto target = std::find_if(units.begin(), units.end(), [targetX, targetY](auto& u) {
                //std::cout << "a";
                return u->x == targetX && u->y == targetY;});
         
            if(target == units.end())
            {
                std::cout << "Critical error! Not found target!\n";
            }
            else
            {
                if((*target)->attack(u->attackPower))
                {
                    units.erase(target);
                }
            }
            
            //if(!target.alive())
            //{
                //remove target from units
            //}
        }
        else
        {
        }
        
        if(!foundEnemy)
        {
            std::cout << "Round not fully finished!\n";
            fullyFinished = false;
        }
        
    //debug = false;
    }
    

}

int battleOutcome(uint roundsFinished)
{
    int outcome = 0;
    for(auto& u : units)
    {
        outcome += u->getHp();
    }
    
    std::cout << outcome << "*" << roundsFinished << " = ";
    
    return outcome * roundsFinished;
}

bool battleEnded()
{
     return (std::all_of(units.begin(), units.end(), [](auto& u){return u->type == Unit::Type::Elf;})) ||
            (std::all_of(units.begin(), units.end(), [](auto& u){return u->type == Unit::Type::Goblin;}));
}

int main()
{
    readMap("test");
    std::cout << "Initially\n";
    displayMapWithUnits();

    for(int i = 1; i < 5 && !battleEnded(); ++i)
    {
        //if(i == 3) debug = true;
        //else debug = false;
        
        units.sort(compareDereferenced);     

        moveUnits();


        std::cout << "After round: " << i << '\n';
        displayMapWithUnits();
        
        if(battleEnded())
        {
            if(!fullyFinished)
            {
                --i;
            }
            std::cout << "battle outcome: " << battleOutcome(i) << '\n';
        }
    } 
    
    
    std::map<std::pair<uint, uint>, int> distances;
}
