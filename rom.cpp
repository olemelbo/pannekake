//
//  rom.cpp
//  Prosjekt
//
//  Created by Emil Kjelsrud on 4/2/13.
//  Copyright (c) 2013 Emil Kjelsrud. All rights reserved.
//

#include "rom.h"
#include <fstream>
#include "utils.h"
#include "reservasjon.h"

using namespace std;

Rom::Rom() {
    
}

Rom::Rom(int romnr): Num_element(romnr) {
    
}

Rom::Rom(int romnr, ifstream &file): Num_element(romnr) {
    ant_senger = read_int(file);
    frokost_inkludert = read_bool(file);
    reservasjoner = new List(Sorted);
    int antall_reservasjoner = read_int(file);
    for (int i = 0; i < antall_reservasjoner; i++) {
        int ankomst = read_int(file);
        Reservasjon* res = new Reservasjon(ankomst, file);
        reservasjoner->add(res);
    }
}

Rom::~Rom() {
    
}