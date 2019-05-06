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
#include <cstdio>


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

vector<string> readCross(){
	vector<string> result;
	bool empty = false;
	ifstream file("cross.txt");
	int i = 0;


	while(!empty){
		char c = 0;
		file.get(c);
		// cout << int(c) << "   :c";
		if (c == '\n'){
			break;
		}
		result.push_back("");
		while (c != '\n'){
			file.get(c);
			result[i] += c;
			// if(result[i].length() > 150){
			// 	cout << int(result[i][100]);
			// 	empty = true;
			// 	break;
			// }
		}
		cout << result[i] << result.size() << endl;
		++i;
	}
	return result;
}



