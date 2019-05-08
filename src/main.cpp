//
//  main.cpp
//  cross
//
//  Created by Alexander Golys on 06/05/2019.
//  Copyright © 2019 Alexander Golys. All rights reserved.
//

#include <iostream>
#include "cross.hpp"

using namespace std;

int main() {

    vector<string> list = readList();
   
    	vector<string> cross = extendSize(readCross());
     	vector<Word> ver = createVerticalWords(cross);
       	vector<Word> hor = createHorizontalWords(cross);

       	vector<Word> words = concatenateWords(ver, hor);

    	vector<Crossing> crs = createCrossings(cross);

    	vector<WordPair> pairs = createPairs(words, list);

    	for(int i=0; i<pairs.size(); ++i){
    		cout << "{" << pairs[i].candidate << ", " << pairs[i].word.number << "}" << endl;
    	}
    	vector<WordPair> empty;
    
    return 0;
}

