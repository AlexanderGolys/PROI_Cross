//
//  cross.hpp
//  cross
//
//  Created by Alexander Golys on 06/05/2019.
//  Copyright © 2019 Alexander Golys. All rights reserved.
//

#ifndef cross_hpp
#define cross_hpp

#include <iostream>
#include <vector>
using namespace std;

class Word{
    Word(int, int, int, int);
    int len;
    int x_start;
    int y_start;
    int x_end;
    int y_end;
};

class Crossing{
	Crossing(int, int);
	int x;
	int y;
	int nb1;
	int nb2;
};

vector<string> readList();
vector<string> readCross();
vector<Word> createWords(vector<string>);


#endif 
