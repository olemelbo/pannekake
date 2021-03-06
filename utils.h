//
//  utils.h
//  Prosjekt
//
//	Created by Emil Kjelsrud, Kristin Annabel Folland and Ole Christian Melbostad
//

#ifndef __utils__H
#define __utils__H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string read_text(ifstream &file);
int read_int(ifstream &file);
bool read_bool(ifstream &file);
string getln(string prompt);
string getln(string prompt, int i);
int read_int(string promt);
int convert_to_int(string temp); 
char* convert_string_to_char(string str);
char read_char(string promt);
float read_float(string promt);
float read_float(ifstream &file);

bool did_the_user_press_enter(string beboere);
bool ingen_beboere(string temp, int counter);

bool is_number_less(int num_one, int num_two);
bool gyldig_ankomst(int ankomst, int avreise, int dagens_dato);

#endif /* defined(__Prosjekt__utils__) */
