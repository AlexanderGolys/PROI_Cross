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

template <class T>
class Optional{
public:
    T value;
    bool defined;
    
    Optional(T v, bool def){
    value = v;
    defined = def;
    }
    Optional(){
    value = 0;
    defined = false;
    }
};

class Word{
public:
    Word(int, int, int, int, bool);
    int len;
    int x_start;
    int y_start;
    int x_end;
    int y_end;
    bool vertical;
};

class Crossing{
public:
	Crossing(int, int);
    Crossing(int, int, int, int);
	int x;
	int y;
	// Optional<int> nb1;
	// Optional<int> nb2;
};




vector<string> readList();
vector<string> readCross();
vector<Word> createVerticalWords(vector<string>);
vector<Word> createHorizontalWords(vector<string>);
vector<string> extendSize(vector<string>);
vector<Crossing> createCrossings(vector<string>);


#endif 
