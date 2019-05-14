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

        printInstruction();

        vector<string> list = readList();
    	Cross cross;
     	vector<Word> ver = createVerticalWords(cross);
       	vector<Word> hor = createHorizontalWords(cross);
       	vector<Word> words = concatenateWords(ver, hor);
    	vector<Crossing> crs = createCrossings(cross);
    	vector<WordPair> pairs = createPairs(words, list);
    	crs = giveAllCrossingNumbers(crs, words);


        vector<WordPair> result = productAll(crs, pairs);
        result = delDuplicates(result);

//    for (int i = 0; i < result.size() ; ++i) {
//        cout << "{" << result[i].word.number << ", " << result[i].candidate << "}" << endl;
//    }
    CrossDone done = CrossDone(cross, result);
    done.print(answer(result, words.size()));
    return 0;
}

