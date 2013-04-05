//
//  dobbel.cpp
//  Prosjekt
//
//  Created by Emil Kjelsrud on 4/2/13.
//  Copyright (c) 2013 Emil Kjelsrud. All rights reserved.
//

#include "dobbel.h"
#include "utils.h"

Dobbel::Dobbel() {
    
}

Dobbel::Dobbel(int romnr) : Rom(romnr) {
    
}

Dobbel::Dobbel(int romnr, ifstream &file): Rom(romnr, file) {
    ekstra_seng = read_bool(file);
}

Dobbel::~Dobbel() {
    
}

void Dobbel::skriv_til_fil(ostream* ut) {
	Rom::skriv_til_fil(ut);
	*ut << ekstra_seng << "\n";
}