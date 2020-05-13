#include <iostream>
#include <string>
#include <cmath>
#include <cctype>
#include <algorithm>
#include "quadtree.cpp"

using namespace std;

int main(const int argc, const char* const argv[]){
	string inputLine;
	Quadtree tree;
	while (!cin.eof()){
		//gets next line and assign to inputLine
		getline(cin, inputLine);
		int i = 0;
		string command = "";
		while (inputLine[i] != ' ' && i < inputLine.length() && command.compare("print") && command.compare("clear") && command.compare("size")){
			command += inputLine[i];
			i++;
		}

		
		if (!command.compare("i")){
			string input;
			i++;
			//getting name
			while (inputLine[i] != ';'){
				input += inputLine[i];
				i++;
			}
			string name = input;
			i++;
			input = "";
			//getting x
			while (inputLine[i] != ';'){
				input += inputLine[i];
				i++;
			}
			float x = stof(input);
			i++;
			input = "";
			//getting y
			while (inputLine[i] != ';'){
				input += inputLine[i];
				i++;
			}
			float y = stof(input);
			i++;
			input = "";
			//getting p
			while (inputLine[i] != ';'){
				input += inputLine[i];
				i++;
			}
			int p = stoi(input);
			i++;
			input = "";
			//getting r
			while (inputLine[i] != ';'){
				input += inputLine[i];
				i++;
			}
			int r = stoi(input);
			i++;
			input = "";
			//getting s
			while (i < inputLine.length()-1){
				input += inputLine[i];
				i++;
			}
			int s = stoi(input);
			tree.insert(name, x, y, p, r, s);
			
		}
		else if (!command.compare("s")){
			string input;
			i++;
			
			//getting x
			while (inputLine[i] != ';'){
				input += inputLine[i];
				i++;
			}
			float x = stof(input);
			i++;
			input = "";
			//getting y
			while (i < inputLine.length()){
				input += inputLine[i];
				i++;
			}
			float y = stof(input);
			
			tree.search(x,y);
		}
		else if (!command.compare("q_max")){
			string input;
			i++;
			
			//getting x
			while (inputLine[i] != ';'){
				input += inputLine[i];
				i++;
			}
			float x = stof(input);
			i++;
			input = "";
			//getting y
			while (inputLine[i] != ';'){
				input += inputLine[i];
				i++;
			}
			float y = stof(input);
			i++;
			input = "";
			//getting direction
			while (inputLine[i] != ';'){
				input += inputLine[i];
				i++;
			}
			string dir = input;
			i++;
			input = "";
			//getting attr;
			char attr = inputLine[i];
			
			tree.q_max(x, y, dir, attr);
			
			
		}
		else if (!command.compare("q_min")){
			string input;
			i++;
			
			//getting x
			while (inputLine[i] != ';'){
				input += inputLine[i];
				i++;
			}
			float x = stof(input);
			i++;
			input = "";
			//getting y
			while (inputLine[i] != ';'){
				input += inputLine[i];
				i++;
			}
			float y = stof(input);
			i++;
			input = "";
			//getting direction
			while (inputLine[i] != ';'){
				input += inputLine[i];
				i++;
			}
			string dir = input;
			i++;
			input = "";
			//getting attr;
			char attr = inputLine[i];
			
			tree.q_min(x, y, dir, attr);
		}
		else if (!command.compare("q_total")){
			string input;
			i++;
			
			//getting x
			while (inputLine[i] != ';'){
				input += inputLine[i];
				i++;
			}
			float x = stof(input);
			i++;
			input = "";
			//getting y
			while (inputLine[i] != ';'){
				input += inputLine[i];
				i++;
			}
			float y = stof(input);
			i++;
			input = "";
			//getting direction
			while (inputLine[i] != ';'){
				input += inputLine[i];
				i++;
			}
			string dir = input;
			i++;
			input = "";
			//getting attr;
			char attr = inputLine[i];
			
			tree.q_total(x, y, dir, attr);
		}
		else if (!command.compare("print")){
			tree.print();
		}
		else if (!command.compare("clear")){
			tree.clear();
		}
		else if (!command.compare("size")){
			tree.size();
		}	
	}

	return 0;
}



