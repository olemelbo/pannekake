//
//  singel.cpp
//  Prosjekt
//
//  Created by Emil Kjelsrud on 4/2/13.
//  Copyright (c) 2013 Emil Kjelsrud. All rights reserved.
//

#include "singel.h"

Singel::Singel() {
    
}

Singel::Singel(int romnr): Rom(romnr) {
    
}

Singel::Singel(int romnr, ifstream& infile): Rom(romnr, infile) {
    
}

Singel::~Singel() {

}