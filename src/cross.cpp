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
#include <vector>


using namespace std;

Word::Word(){
	len = 0;
	x_start = 0;
	x_end = 0;
	y_start = 0;
	y_end = 0;
	vertical = false;
	number = 0;
}


Word::Word(int x_s, int y_s, int x_e, int y_e, bool v, int nb){
	len = x_s - x_e + y_s - y_e - 1;
	if(len<0)
		len *= -1;
	x_start = x_s;
	y_start = y_s;
	x_end = x_e;
	y_end = y_e;
	vertical = v;
	number = nb;
}

Crossing::Crossing(int x_p, int y_p){
	x = x_p;
	y = y_p;
	 nb_v = Optional<int>(0, false);
	 nb_h = Optional<int>(0, false);
	 pos_x = Optional<int>(0, false);
	 pos_y = Optional<int>(0, false);

}


WordPair::WordPair(string c, Word w){
	candidate = c;
	word = w;
}

bool WordPair::operator==(const WordPair& w1, const WordPair& w2){
    return (w1.candidate == w2.candidate && w1.number == w2.number);
}


vector<string> readList(){
	vector<string> result;
	ifstream file("../list.txt");
	string line;
	while (getline(file, line)) {
		result.push_back(line);
	}
	return result;
}

vector<string> readCross(){
	vector<string> result;
	bool empty = false;
	ifstream file("../cross.txt");
	int i = 0;

	while(!empty){
		char c = 0;
		file.get(c);
		if (c == '\n'){
			break;
		}
		result.push_back("");
		while (c != '\n'){
			file.get(c);
			if (c == ' ')
				result[i] += '0';
			if (c == '*')
				result[i] += '1';
		}
//		 cout << result[i] << endl;
		++i;
	}
	return result;
}

vector<Word> createHorizontalWords(vector<string> cross){
	vector<Word> result;
	int start;
	bool buffor;
	int nb = 0;
	int x_size = cross[0].length();
	int y_size = cross.size();
	for(int y = 0; y<y_size; ++y){
		buffor = false;
		for(int x = 0; x<x_size; ++x){
			if(cross[y][x] == '1' && !buffor){
				buffor = true;
				start = x;
			}
			if(cross[y][x] == '0' && buffor){
				Word temp = Word(start, y, x-1, y, false, nb);
				if (temp.len > 1){
					result.push_back(temp);
					++nb;
				}
				buffor = false;
			}
			if(cross[y][x] == '1' && x == x_size-1){
				Word temp = Word(start, y, x, y, false, nb);
				if (temp.len > 1){
					result.push_back(temp);
					++nb;
				}
			}

		}
	}
	return result;
}

vector<Word> createVerticalWords(vector<string> cross){
	vector<Word> result;
	int start;
	bool buffor;
	int nb = 0;
	int x_size = cross[0].length();
	int y_size = cross.size();

	for(int x = 0; x<x_size; ++x){
		buffor = false;
		for(int y = 0; y<y_size; ++y){
			if(cross[y][x] == '1' && !buffor){
				buffor = true;
				start = y;
			}
			if(cross[y][x] == '0' && buffor){
				Word temp = Word(x, start, x, y-1, true, nb);
				if (temp.len > 1){
					result.push_back(temp);
					++nb;
				}
				buffor = false;
			}
			if(cross[y][x] == '1' && y == y_size-1){
				Word temp = Word(x, start, x, y, true, nb);
				if (temp.len > 1){
					result.push_back(temp);
					++nb;
				}
			}

		}
	}
	return result;
}

vector<string> extendSize(vector<string> cross){
	vector<string> result;
	int max_size = 0;
	for(int i=0; i<cross.size(); ++i){
		if(cross[i].length() > max_size)
			max_size = cross[i].length();
	}
	for(int i=0; i<cross.size(); ++i){
		while(cross[i].length() < max_size){
			cross[i] += '0';
		}
		result.push_back(cross[i]);
	}
//	cout << "max size: " << max_size << endl;
	return result;
}

  vector<Crossing> createCrossings(vector<string> cross){
    	vector<Crossing> result;
    	int x_size = cross[0].length();
		int y_size = cross.size();
    	for(int y=0; y<y_size; ++y){
    		for(int x=0; x<x_size; ++x){
    			if(	cross[y][x] == '1' && (
    				(y+1 < y_size && x+1 < x_size && cross[y+1][x] == '1' && cross[y][x+1] == '1') ||
    				(y+1 < y_size && x-1 >= 0 && cross[y+1][x] == '1' && cross[y][x-1] == '1') ||
    				(y-1 >= 0 && x+1 < x_size && cross[y-1][x] == '1' && cross[y][x+1] == '1') ||
    				(y-1 >= 0 && x-1 >= 0 && cross[y-1][x] == '1' && cross[y][x-1] == '1'))
    				){
    				result.push_back(Crossing(x, y));
    			}
    		}
    	}
    	return result;
    }

vector<WordPair> createPairs(vector<Word> words, vector<string> list){
	vector<WordPair> result;
	for (int i=0; i<words.size(); ++i){
		for (int ii=0; ii<list.size(); ++ii){
			if (words[i].len == list[ii].length()){
				result.push_back(WordPair(list[ii], words[i]));
			}
		}
	}
	return result;
}

vector<Word> concatenateWords(vector<Word> w1, vector<Word> w2){
	vector<Word> result = w1;
	for (int i = 0; i<w2.size(); ++i){
		result.push_back(w2[i]);
		result.back().number += w1.size();
	}
	return result;
}

int findAnyOfThatNumber(vector<WordPair> pairs, int number){
    for(int i=0; i<pairs.size(); ++i){
        if(pairs[i].word.number == number){
            return i;
        }
    }
    return -1;
}

bool checkPossibility(vector<WordPair> pair, vector<Crossing> cr){
	for(int i = 0; i<cr.size(); ++i){
		if(!checkPossibilityForCrossing(pair, cr[i]))
			return false;
	}
	return true;
}



bool checkPossibilityForCrossing(vector<WordPair> pair, Crossing cr){
	char c1, c2;
		for(int i = 0; i<pair.size(); ++i){
			if(pair[i].word.vertical == true){
				if(pair[i].word.x_start == cr.x){
					c1 = pair[i].candidate[cr.y - pair[i].word.y_start];
				}
			}
			else{
				if(pair[i].word.vertical == false){
				if(pair[i].word.y_start == cr.y){
					c2 = pair[i].candidate[cr.x - pair[i].word.x_start];
				}
			}
			}
		}
		return c1 == c2;
}

Crossing giveCrossingNumbers(Crossing cr, vector<Word> ver, vector<Word> hor){
    Crossing result;
    for(int i=0; i<ver.size(); ++i){
        if(cr.x == ver[i].x_start && cr.y >= ver[i].y_start && cr.y <= ver[i].y_end){
            result.pos_y.defined = true;
            result.pos_y.value = cr.y - ver[i].y_start;
            result.nb_v.defined = true;
            result.nb_v.value = ver[i].number;
        }
    }
    for(int i=0; i<hor.size(); ++i) {
        if (cr.y == hor[i].y_start && cr.x >= hor[i].x_start && cr.x <= hor[i].x_end) {
            result.pos_x.defined = true;
            result.pos_x.value = cr.x - ver.x_start;
            result.nb_h.defined = true;
            result.nb_h.value = hor[i].number;
        }
    }
}

vector<Crossing> giveAllCrossingNumbers(vector<Crossing>cr, vector<Word>ver, vector<Word>hor){
    vector<Crossing> result;
    for(int i=0; i<cr.size(); ++i){
        result.push_back(giveCrossingNumbers(cr[i], ver, hor));
    }
    return result;
}

vector<WordPair> giveCrossingPossibilities(Crossing cr, vector<WordPair> pairs){
    vector<WordPair> result;
    for (int i = 0; i < pairs.size() ; ++i) {
        for (int j = 0; j < pairs.size() < ; ++j) {
            if (i != j && pairs[i].word.number == cr.nb_v.value || pairs[j].word.number == cr.nb_h.value) {
                if (pairs[i].candidate[cr.pos_y.value] == pairs[j].candidate[cr.pos_x.value]) {
                    result.push_back(pairs[i]);
                    result.push_back(pairs[j]);
                }
            }
        }
    }
}

vector<WordPair> productPossibilities(vector<WordPair> p1, vector<WordPair> p2) {
    vector <WordPair> result;
    int same_word = -1;
    for (int i = 0; i < p1.size(); ++i) {
        for (int j = 0; j < p2.size(); ++j) {
            if (p1[i] == p2[i]) {
                same_word = p1.word.number;
            }
        }
    }


    for (int i = 0; i < p1.size(); ++i) {
        if (p1[i].word.number == same_word) {
            for (int j = 0; j < p2.size(); ++j) {
                if (p1[i] == p2[j]) {
                    result.push_back(p1[i]);
                }
            }
        } else {
            result.push_back(p1[i]);
        }
    }


    for (int k = 0; k < p2.size(); ++k) {
        if (p1[k].word.number != same_word) {
            result.push_back(p1[k]);
        }
    }
    return result;
}


vector<WordPair> productAll(vector<Crossing> cr, vector<WordPair> pairs){
    vector<WordPair> result = giveCrossingPossibilities(cr[0], pairs);;
    for (int i = 1; i < cr.size(); ++i) {
        vector<WordPair> pos = giveCrossingPossibilities(cr[i], pairs);
        result = productPossibilities(result, pos);
    }
    return result;
}

bool answer(vector<WordPair> pair, int nb_of_words){
    int c = 0;
    for (int i = 0; i < nb_of_words; ++i) {
        bool is = false;
        for (int j = 0; j < pair.size(); ++j) {
            if (i == pair[j].word.number){
                is = true;
            }
            if (!is){
                return false;
            }
        }
    }
    return true;
}

vector<string> print(WordPair pair, vector<string> cross){
    if (pair.word.vertical) {
        for (int i = 0; i < pair.candidate.length(); ++i) {
            cross[pair.word.y_start][pair.word.x_start + i] = pair.candidate[i];
        }
    }else{
        for (int i = 0; i < pair.candidate.length(); ++i) {
            cross[pair.word.y_start + i][pair.word.x_start] = pair.candidate[i];
        }
    }
    return cross;
}

void print(vector<WordPair> pairs, vector<string> cross, bool answer){
    if(answer){
        cout << "To możliwe!" << endl;
        for (int i = 0; i <; ++i) {
            cross = print(pairs[i], cross);
        }
        for (int j = 0; j < cross.size(); ++j) {
            cout << cross[i] << endl;
        }
    }else{
        cout << "To niemożliwe!" << endl;
    }
}














