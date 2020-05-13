#include <string>
struct City{
	City *NE = NULL, *SE = NULL, *SW = NULL, *NW = NULL;
	std::string name;		//name of city
	float x = 0, y = 0;		//co-ordinates
	int p = 0, r = 0, s = 0;	//city values (pop., cost, salary)
};

class Quadtree{
public:
	
	bool insert(std::string name, float x, float y, int p, int r, int s);	//insert a node
	bool search(float x, float y);		//search for a node at x,y
	bool q_max(float x, float y, std::string dir, char attr);	//find max 
	bool q_min(float x, float y, std::string dir, char attr);	//find min
	bool q_total(float x, float y, std::string dir, char attr);	//find total
	void print();		//print tree with in-order traversal
	void clear();		//clear all nodes
	void size();		//print size
	
	Quadtree();			//ctor
	~Quadtree();		//dtor
	
private:
	City* _center = NULL;		//root
	City* _find(float x, float y);	//find node at x,y
	void _inorder(City*, char attr, char task);		//traverse inorder
	void _delete(City*); 	//post-order traversal to clear nodes
	int _size = 0;
	int _q;
	

};