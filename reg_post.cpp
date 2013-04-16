//
//  reg_post.cpp
//  Prosjekt
//
//  Created by Emil Kjelsrud on 4/2/13.
//  Copyright (c) 2013 Emil Kjelsrud. All rights reserved.
//

#include "reg_post.h"
#include <string>
#include <iostream>

using namespace std;

Reg_post::Reg_post() {
    
}

Reg_post::Reg_post(int antall, string vanlige_reg_poster[MAX_ARRAY]) {
    antall_standard_reg_poster = antall;
	for(int i = 0; i < antall; i++) 
		mest_vanlige_poster[i] = vanlige_reg_poster[i];
}

Reg_post::~Reg_post() {
    
}

void Reg_post::display(){
	int counter = 0;
	for(int i = 0; i < antall_standard_reg_poster; i++){
		counter++;
		cout << counter << ": " << mest_vanlige_poster[i] << "\n" << endl;
	}
}

string Reg_post::get_post(int tall){
	return mest_vanlige_poster[tall];
}