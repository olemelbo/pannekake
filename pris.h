//
//  pris.h
//  Prosjekt
//
//  Created by Emil Kjelsrud on 4/16/13.
//  Copyright (c) 2013 Emil Kjelsrud. All rights reserved.
//
//  Denne klassen er til for å hente ut
//  egendefinerte priser for hvert hotell.
//  Det kan lagres både standardpriser og et
//  vilkårlig antall spesialpriser for gitte tidsperioder.
//

#ifndef __pris_H
#define __pris_H

#include <iostream>
#include <fstream>
#include "coen.h"

using namespace std;

struct Spesialpris {
    int startdato;
    int sluttdato;
    string romtype;
    string type;
    int pris;
};

class Pris {
private:
    void last_inn();
    int standard_uke[ANTALL_ROMTYPER];
    int standard_helg[ANTALL_ROMTYPER];
    Spesialpris spesialpriser[MAX_ARRAY];
    int antall_spesialpriser;
    int les_standard_pris(ifstream & infile);
    void les_special_price_for_you(ifstream & infile);
    
public:
    Pris();
    ~Pris();
    //henter pris for angitt romtype ved spesifikk dato.
    int hent_pris(int romtype, int dato);
};

#endif /* defined(__pris_H) */
