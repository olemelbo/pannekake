//
//  regning.cpp
//  Prosjekt
//
//  Created by Emil Kjelsrud on 4/2/13.
//  Copyright (c) 2013 Emil Kjelsrud. All rights reserved.
//

#include "regning.h"
#include "listtool.h"
#include "utils.h"

Regning::Regning() {
	// Denne skal ikke kjøres    
}

Regning::Regning(char* nvn, int total) : Text_element(nvn) {
    
}

Regning::Regning(char* nvn, ifstream &file): Text_element(nvn) {
    totalsum = read_int(file);
}

Regning::~Regning() {
    
}

void Regning::skriv_til_fil(ostream* ut) {
	*ut << text << "\n"
		<< totalsum << "\n";
}
