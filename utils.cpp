//
//  utils.cpp
//  Prosjekt
//
//  Created by Emil Kjelsrud on 4/3/13.
//  Copyright (c) 2013 Emil Kjelsrud. All rights reserved.
//

#include "utils.h"
#include "coen.h"

using namespace std;

char* read_text(ifstream& file) {
    
    char tmp[MAX_TEXT];
    //Henter antallet leger og konverterer
    file.getline(tmp, MAX_TEXT);
    char* p = new char[strlen(tmp)+1];
    strcpy(p, tmp);
    return p;
}

int read_int(ifstream& file) {
    char tmp[MAX_TEXT];
    file.getline(tmp, MAX_TEXT);
    return atoi(tmp);
}