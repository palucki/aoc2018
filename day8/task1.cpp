#include <iostream>
#include <fstream>
#include <stack>

int main()
{
	int data = 0;
	int sumOfMeta = 0;
	
	std::ifstream inFile("test");
	
	inFile >> data;
	std::stack<int> children; //1 element
	children.push(data);
	
	inFile >> data;
	std::stack<int> meta;
	meta.push(data);
	
	std::cout << "children: " << children.top() << " meta: " << meta.top() <<'\n';
	
	while(!children.empty() && !meta.empty())
	{
		if(children.top() == 0)
		{
			children.pop();
			while(meta.top()-- != 0)
			{
				inFile >> data;
				sumOfMeta += data;
			}
			meta.pop();
		}
		else
		{
			children.top()--;
			inFile >> data;
			children.push(data);
			
			inFile >> data;
			meta.push(data);
		}
	}

	std::cout << "Sum of metadata: " << sumOfMeta << '\n';
}
