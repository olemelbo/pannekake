//
//  utils.cpp
//  Prosjekt
//
//  Created by Emil Kjelsrud on 4/3/13.
//  Copyright (c) 2013 Emil Kjelsrud. All rights reserved.
//

#include "utils.h"
#include "coen.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

string read_text(ifstream& file) {
    string tmp;
    getline(file, tmp);
    return tmp;
}


int read_int(ifstream& file) {
    string tmp;
    getline(file, tmp);
    return stoi(tmp);
}

float read_float(ifstream& file) {
	string tmp;
	getline(file, tmp);
	return atof(tmp.c_str());
}

int read_int(string promt) {
	cout << endl << promt << ": ";
	string result;
    getline(cin,result);
    int r = stoi(result);
    return r;
}

char read_char(string promt) {
	cout << endl << promt << ": ";

    char cmd;
    char* tmp;
    tmp = new char(1);
	
    //Leser input
    string str;
    getline(cin, str);
    
    const char* c = str.c_str();
    strcpy(tmp, c);
    cmd = *tmp;
    
    //delete(tmp);
    
    return toupper(cmd);
}

bool read_bool(ifstream &file) {
    int test = read_int(file);
    return test > 0 ? true : false;
}

int convert_to_int(string temp ) {
	return stoi(temp);
}

 string getln(string promt) {
    cout << endl << promt << ": ";
	string result;
    getline(cin,result);
    return result;
}

 char * convert_string_to_char(string str) {
	char * writable = new char[str.size() + 1];
	std::copy(str.begin(), str.end(), writable);
	writable[str.size()] = '\0'; // don't forget the terminating 0

	// don't forget to free the string after finished using it
	delete[] writable;
	return writable;
 }

string getln(string promt, int i) {
    cout << promt << " " << i << ": " << endl;
	string result;
    getline(cin,result);
    return result;
}
