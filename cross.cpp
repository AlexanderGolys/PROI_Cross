//
//  cross.cpp
//  cross
//
//  Created by Alexander Golys on 06/05/2019.
//  Copyright © 2019 Alexander Golys. All rights reserved.
//

#include "cross.hpp"
#include <iostream>
#include <fstream>

using namespace std;

vector<string> readList(){
	vector<string> result;
	ifstream file("list.txt");
	string line;
	while (getline(file, line)) {
		result.push_back(line);
	}
	return result;
}
