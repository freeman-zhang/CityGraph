#include <iostream>
#include <string>
#include <cmath>
#include "quadtree.h"

using namespace std;

Quadtree::Quadtree(){}

Quadtree::~Quadtree(){
	clear();
}

bool Quadtree::insert(string name, float x, float y, int p, int r, int s){
	//if city already exists at (x,y)
	if (_find(x, y)){
		cout << "failure" << endl;
		return false;
	}
	
	//creating a new city object
	City* newCity = new City;
	newCity->name = name;
	newCity->x = x;
	newCity->y = y;
	newCity->p = p;
	newCity->r = r;
	newCity->s = s;
	
	//check if tree has root
	if (_center == NULL){
		_center = newCity;
		cout << "success" << endl;
		_size++;
		return true;
	}
	
	//traverse tree and insert new city node
	float currentx = _center->x;
	float currenty = _center->y;
	City* current = _center;
	
	bool inserted = false;
	while (!inserted){
		//NE 
		if (x >= currentx && y > currenty){
			if (current->NE == NULL){
				current->NE = newCity;
				inserted = true;
			}
			else{
				current = current->NE;
				currentx = current->x;
				currenty = current->y;
			}
		}
		
		//SE 
		else if (x > currentx && y <= currenty){
			if (current->SE == NULL){
				current->SE = newCity;
				inserted = true;
			}
			else{
				current = current->SE;
				currentx = current->x;
				currenty = current->y;
			}
		}
		
		//SW
		else if (x <= currentx && y < currenty){
			if (current->SW == NULL){
				current->SW = newCity;
				inserted = true;
			}
			else{
				current = current->SW;
				currentx = current->x;
				currenty = current->y;
			}
		}
		
		//NW
		else if (x < currentx && y >= currenty){
			if (current->NW == NULL){
				current->NW = newCity;
				inserted = true;
			}
			else{
				current = current->NW;
				currentx = current->x;
				currenty = current->y;
			}
		}
		
	}
	_size++;
	cout << "success" << endl;
	return true;
	
}

bool Quadtree::search(float x, float y){
	City* foundCity = _find(x, y);
	//check if the city was found
	if (foundCity == NULL){
		cout << "not found" << endl;
		return false;
	}
	cout << "found " << foundCity->name << endl;
	return true; 
}

bool Quadtree::q_max(float x, float y, string dir, char attr){

	City* current = _find(x, y);
	//check if city was found
	if (current == NULL){
		cout << "failure" << endl;
		return false;
	}
	//setting current to the node at the direction of the current node.
	//this current will be the starting node and i will check it and all its children
	//to find the q_max
	if (!dir.compare("NE")){
		current = current->NE;
	}
	else if (!dir.compare("SE")){
		current = current->SE;
	}
	else if (!dir.compare("SW")){
		current = current->SW;
	}
	else if (!dir.compare("NW")){
		current = current->NW;
	}
	//checking if direction is empty
	if (current == NULL){
		cout << "failure" << endl;
		return false;
	}
	
	//setting max to the attr value of the starting node;
	if (attr == 'p'){
		_q = current->p;
	}
	if (attr == 'r'){
		_q = current->r;
	}
	if (attr == 's'){
		_q = current->s;
	}
	

	
	//traverse rest of tree to check for min
	_inorder(current, attr, 'M');
	cout << "max " << _q << endl;
	return true;

	
}

bool Quadtree::q_min(float x, float y, string dir, char attr){
	
	City* current = _find(x, y);
	//check if city was found
	if (current == NULL){
		cout << "failure" << endl;
		return false;
	}
	//setting current to the node at the direction of the current node.
	//this current will be the starting node and i will check it and all its children
	//to find the q_max
	if (!dir.compare("NE")){
		current = current->NE;
	}
	else if (!dir.compare("SE")){
		current = current->SE;
	}
	else if (!dir.compare("SW")){
		current = current->SW;
	}
	else if (!dir.compare("NW")){
		current = current->NW;
	}
	//checking if direction is empty
	if (current == NULL){
		cout << "failure" << endl;
		return false;
	}
	
	//setting min to the attr value of the starting node;
	if (attr == 'p'){
		_q = current->p;
	}
	else if (attr == 'r'){
		_q = current->r;
	}
	else if (attr == 's'){
		_q = current->s;
	}
	
	//traverse rest of tree to check for min
	_inorder(current, attr, 'm');
	cout << "min " << _q << endl;
	return true;
	
}

bool Quadtree::q_total(float x, float y, string dir, char attr){
	
	City* current = _find(x, y);
	//check if city was found
	if (current == NULL){
		cout << "failure" << endl;
		return false;
	}
	//setting current to the node at the direction of the current node.
	//this current will be the starting node and i will check it and all its children
	//to find the q_max
	if (!dir.compare("NE")){
		current = current->NE;
	}
	else if (!dir.compare("SE")){
		current = current->SE;
	}
	else if (!dir.compare("SW")){
		current = current->SW;
	}
	else if (!dir.compare("NW")){
		current = current->NW;
	}
	//checking if direction is empty
	if (current == NULL){
		cout << "failure" << endl;
		return false;
	}
	
	//setting total to 0;
	_q = 0;
	
	//traverse rest of tree to get total
	_inorder(current, attr, 't');
	cout << "total " << _q << endl;
	return true;
}

void Quadtree::print(){
	City* current = _center;
	_inorder(current, '0', 'p');
	cout << "\n";
}

void Quadtree::clear(){
	City* current = _center;
	_delete(current);
	_size = 0;
	_center = NULL;
	cout << "success" << endl;
}

void Quadtree::size(){
	cout << "tree size " << _size << endl;
}


//private member functions
City* Quadtree::_find(float x, float y){
	if (_center == NULL){
		return NULL;
	}
	City* current = _center;
	float currentx = current->x;
	float currenty = current->y;
	
	bool found = false;
	
	while(!found){
		if (fabs(x - currentx) < 0.001 && fabs(y - currenty) < 0.001){
			found = true;
		}
		//NE 
		else if (x >= currentx && y > currenty){
			if (current->NE == NULL){
				current = NULL;
				found = true;
			}
			else{
				current = current->NE;
				currentx = current->x;
				currenty = current->y;
			}
		}
		
		//SE 
		else if (x > currentx && y <= currenty){
			if (current->SE == NULL){
				current = NULL;
				found = true;
			}
			else{
				current = current->SE;
				currentx = current->x;
				currenty = current->y;
			}
		}
		
		//SW
		else if (x <= currentx && y < currenty){
			if (current->SW == NULL){
				current = NULL;
				found = true;
			}
			else{
				current = current->SW;
				currentx = current->x;
				currenty = current->y;
			}
		}
		
		//NW
		else if (x < currentx && y >= currenty){
			if (current->NW == NULL){
				current = NULL;
				found = true;
			}
			else{
				current = current->NW;
				currentx = current->x;
				currenty = current->y;
			}
		}
	}
	return current;
	

}

void Quadtree::_inorder(City* current, char attr, char task){
	//task: M = max, m = min, t = total, p = print;
	if (current != NULL){
		_inorder(current->NE, attr, task);
		_inorder(current->NW, attr, task);
		if (task == 'M'){
			if (attr == 'p'){
				if (current->p > _q){
					_q = current->p;
				}
			}
			else if (attr == 'r'){
				if (current->r > _q){
					_q = current->r;
				}
				
			}
			else if (attr == 's'){
				if (current->s > _q){
					_q = current->s;
				}
			}
		}
		else if (task == 'm'){
			if (attr == 'p'){
				if (current->p < _q){
					_q = current->p;
				}
			}
			else if (attr == 'r'){
				if (current->r < _q){
					_q = current->r;
				}
			}
			else if (attr == 's'){
				if (current->s < _q){
					_q = current->s;
				}
			}
		}
		else if (task == 't'){
			if (attr == 'p'){
				_q += current->p;
			}
			else if (attr == 'r'){
				_q += current->r;
			}
			else if (attr == 's'){
				_q += current->s;
			}
		}
		else if (task == 'p'){
			cout << current->name << " ";
		}
		
		_inorder(current->SW, attr, task);
		_inorder(current->SE, attr, task);
		
	}
}

void Quadtree::_delete(City* c){
	//post order
	if (c != NULL){
		_delete(c->NE);
		_delete(c->NW);
		_delete(c->SW);
		_delete(c->SE);
		delete c;
	
	}
}












