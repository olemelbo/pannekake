//
//  utils.h
//  Prosjekt
//
//  Created by Emil Kjelsrud on 4/3/13.
//  Copyright (c) 2013 Emil Kjelsrud. All rights reserved.
//

#ifndef __utils__H
#define __utils__H

#include <iostream>
#include <fstream>

using namespace std;

char* read_text(ifstream &file);
int read_int(ifstream &file);
bool read_bool(ifstream &file);
char* getln(char prompt[]);
char* stripWord(char word[], char str[]);

#endif /* defined(__Prosjekt__utils__) */
