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

    // vector<string> list = readList();
   
    	vector<string> cross = extendSize(readCross());

    for(int i = 0; i < cross.size(); ++i){
    	cout << cross[i] << endl;
    }



     vector<Word> ver = createVerticalWords(cross);

     cout << "ver size: " << ver.size() << endl;
    for (int i = 0; i<ver.size(); ++i){
    	cout << "len: " << ver[i].len << " x: " << ver[i].x_start << endl;
    }

       	vector<Word> hor = createHorizontalWords(cross);

     cout << "hor size: " << hor.size() << endl;
    for (int i = 0; i<hor.size(); ++i){
    	cout << "len: " << hor[i].len << " y: " << hor[i].y_start << endl;
    }


    	vector<Crossing> crs = createCrossings(cross);
    // for (int i = 0; i<cr.size(); ++i){
    // 	cout << "x: " << cr[i].x << " y: " << cr[i].y << endl;
    // }
    return 0;
}
