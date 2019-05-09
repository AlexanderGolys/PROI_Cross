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
    Word(int, int, int, int, bool, int);
    Word();
    int len;
    int x_start;
    int y_start;
    int x_end;
    int y_end;
    bool vertical;
    int number;
};

class Crossing{
public:
	Crossing(int, int);
	int x;
	int y;
	Optional<int> pos_x;
	Optional<int> pos_y;
    Optional<int> nb_v;
    Optional<int> nb_h;
};

class WordPair{
public:
    WordPair(string, Word);
    string candidate;
    Word word;
    bool operator==(const WordPair&);

};


vector<string> readList();
vector<string> readCross();
vector<Word> createVerticalWords(vector<string>);
vector<Word> createHorizontalWords(vector<string>);
vector<string> extendSize(vector<string>);
vector<Crossing> createCrossings(vector<string>);
vector<WordPair> createPairs(vector<Word>, vector<string>);
vector<Word> concatenateWords(vector<Word>, vector<Word>);
bool checkOnce(vector<WordPair>, vector<WordPair>, vector<Crossing>, int);
int findAnyOfThatNumber(vector<WordPair>, int);
bool checkPossibilityForCrossing(vector<WordPair>, Crossing);
bool checkPossibility(vector<WordPair>, vector<Crossing>);
Crossing giveCrossingNumbers(Crossing, vector<Word>);
vector<Crossing> giveAllCrossingNumbers(vector<Crossing>, vector<Word>);
vector<WordPair> giveCrossingPossibilities(Crossing, vector<WordPair>);
vector<WordPair> productPossibilities(vector<WordPair>, vector<WordPair>);
vector<WordPair> productAll(vector<Crossing>, vector<WordPair>);
bool answer(vector<WordPair>, int);

void print(vector<WordPair>, vector<string>, bool);
vector<string> print(WordPair, vector<string>);
vector<WordPair> delDuplicates(vector<WordPair>);
vector<string> delete0(vector<string>);

#endif 
