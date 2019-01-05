#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <memory>

struct Node {
    Node* parent = nullptr;
    int childrenCount = 0;
    std::vector<std::unique_ptr<Node>> children;
    std::vector<int> metadata;
    bool visited = false;
    
    int sum()
    {        
        int sum = 0;
        
        for(auto e : metadata)
        {
            sum += e;
        }
        
        for(auto& ch : children)
        {
            sum += ch->sum();
            //std::cout << "Now " << sum << '\n';
        }
        
        return sum;
    }
    
    int value()
    {        
        if(children.size() == 0)
        {
            int sum = 0;
            
            for(auto e : metadata)
            {
                sum += e;
            }
            
            std::cout << "No children, sum =  " << sum <<'\n';
            
            return sum;
        }
        else
        {
            std::vector<int> childrenValues;
            for(std::size_t i = 0; i < children.size(); ++i)
            {
                childrenValues.push_back(children[i]->value());
            }
            
            int sum = 0;
            
            for(auto e : metadata)
            {
                if(e-1 >= 0 && e-1 < childrenValues.size()) // from 1 to SIZE
                {
                    sum += childrenValues[e-1];
                }
            }
            std::cout << "Children, sum =  " << sum << '\n';
            
            return sum;
        }
    }
    
    
};

//int sumUp(Node* root)
//{
    //int sum = 0;
    
    //while(root != nullptr)
    //{
        //for(auto e : root->metadata)
        //{
            //sum += e;
        //}
        
        //for(int 
    //}
    
    //return sum;
//}

int main()
{
    std::ifstream inFile("input");
    int value;
    std::vector<int> data;
    while(inFile >> value)
        data.push_back(value);
        
    int left = 0; 
    int right = data.size() - 1;

    auto root = std::make_unique<Node>();
    
    //int childrenCount = data[left++];
    //int metaCount = data[left++];    
        
    Node* current = root.get();
    
    do
    {
        std::cout << "current " << current << '\n';
        if(!current->visited)
        {
            int childrenCount = data[left++];
            int metaCount = data[left++];
            
            std::cout << "CH: " << childrenCount << " M: " << metaCount << '\n';
            
            current->childrenCount = childrenCount;
            current->metadata.resize(metaCount);
            current->visited = true;
            
            //add children if required
            for(int i = 0; i < childrenCount; ++i)
            {
                auto newNode = std::make_unique<Node>();
                newNode->parent = current;
                current->children.push_back(std::move(newNode));
            }
        }
        
        int childrenCount = current->childrenCount;
        int metaCount = current->metadata.size();
    
        bool found = false;
        for(int i = 0; i < childrenCount && !found; ++i)
        {
            if(!current->children[i]->visited)
            {
                current = current->children[i].get();
                found = true;
            }
        }
        
        if(!found)
        {
            std::cout << "Not foud. 0 Child or all visited\n";
            for(int i = 0; i < metaCount; ++i)
            {
                auto meta = data[left++];
                current->metadata.push_back(meta);
                std::cout << "A:Inserting meta: " << meta << '\n';
            }
            
            current = current->parent;
        }
        
        
        //if(current->childrenCount > 0)
        //{
            //current->childrenCount--;
            
            //for(int i = 0; i < metaCount; ++i)
            //{
                //auto meta = data[right--];
                //current->metadata.push_back(meta);
                //std::cout << "A:Inserting meta: " << meta << '\n';
            //}
            
            //std::cout << "Going down\n";
            //current = current->children[current->children.size() - 1].get();
        //}
        //else
        //{
            //for(int i = 0; i < metaCount; ++i)
            //{
                //auto meta = data[left++];
                //current->metadata.push_back(meta);
                //std::cout << "B:Inserting meta: " << meta << '\n';
            //}
            
            
            
            
            ////while(current->parent->children.size() < 2)
            ////{
            //    //current = current->parent; //go to parent which has any childrens left
            ////}
            
            //std::cout << "Going up\n";
        //}
        
        
    }
    while(left < right && current != nullptr);
    
    std::cout << "L: " << left << " R: " << right << '\n'; 
    
    std::cout << "Root has " << root->children.size() << " children\n";
    std::cout << "Root has " << root->metadata.size() << " metas\n";
    
    std::cout << "Sum of metadatas " << root->sum() << '\n';
    std::cout << "Value of root node" << root->value() << '\n';
}
