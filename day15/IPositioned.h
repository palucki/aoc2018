class IPositioned {
public:
    IPositioned(unsigned int _x, unsigned int _y) : x(_x), y(_y) {}
    
    bool operator<(const IPositioned& rhs)
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

    unsigned int x;
    unsigned int y;
};
