//
//  suite.cpp
//  Prosjekt
//
//  Created by Emil Kjelsrud on 4/2/13.
//  Copyright (c) 2013 Emil Kjelsrud. All rights reserved.
//

#include "suite.h"

Suite::Suite() {
    
}

Suite::Suite(int romnr): Rom(romnr) {
    
}

Suite::Suite(int romnr, ifstream &file): Rom(romnr, file) {
    antall_senger = read_int(file);
    antall_kvadratmeter = read_int(file);
    beskrivelse = read_text(file);
}

Suite::~Suite() {
    
}