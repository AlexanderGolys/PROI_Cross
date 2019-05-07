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
	// nb1 = Optional<int>(0, false);
	// nb2 = Optional<int>(0, false);

}

Crossing::Crossing(int x, int y, int w1, int w2){

}

WordPair::WordPair(string c, Word w){
	candidate = c;
	word = w;
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
		// cout << result[i] << result.size() << endl;
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
			if(cross[y][x] == '1' && buffor == false){
				buffor = true;
				start = x;
			}
			if(cross[y][x] == '0' && buffor == true){
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
			if(cross[y][x] == '1' && buffor == false){
				buffor = true;
				start = y;
			}
			if(cross[y][x] == '0' && buffor == true){
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
	cout << "max size: " << max_size << endl;
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






