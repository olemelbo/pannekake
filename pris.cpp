//
//  pris.cpp
//  Prosjekt
//
//  Created by Emil Kjelsrud on 4/16/13.
//  Copyright (c) 2013 Emil Kjelsrud. All rights reserved.
//

#include "pris.h"
#include <string.h>
#include "coen.h"
#include "timer.h"
#include "utils.h"
#include "hotell.h"

using namespace std;
extern Hotell* hotellet;
extern Timer timer;

Pris::Pris() {
    
}

Pris::Pris(int ankomst, int avrese) {
    
    
    string kortnavn = hotellet->get_filnavn();
    string filnavn = kortnavn + ".PRS";

    ifstream infile(filnavn);
    
    //Første linje er søppel
    string soppel = read_text(infile);
    
    //Leser inn standard ukepriser
    for(int i = 0; i < ANTALL_ROMTYPER; i++) {
        standard_uke[i] = les_standard_pris(infile);
    }

    //Neste lunje er søppel.
    soppel = read_text(infile);
    
    //Leser inn standard helgpriser
    for(int i = 0; i < ANTALL_ROMTYPER; i++) {
        standard_helg[i] = les_standard_pris(infile);
    }
    
    les_special_price_for_you(infile);
}

int Pris::hent_pris(int romtype, int dato) {
    
    //søndag 0, lørdag 6
    int ukedagnr = timer.ukedagsnr(dato);
    string type = ukedagnr == 0 || ukedagnr == 6 ? "helg" : "uke";
    string rom;
    bool funnet = false;
    int pris = -1;
    
    switch (romtype) {
        case SINGEL:
            rom = "singel";
            break;
        case DOBBEL:
            rom = "dobbel";
            break;
        case SUITE:
            rom = "suite";
            break;
        default:
            return pris;
            break;
    }
    
    for(int i = 0; i < antall_spesialpriser; i++) {
        Spesialpris p = spesialpriser[i];
        if(dato > p.startdato && dato < p.sluttdato) {
            if(rom != p.romtype)
                continue;
            if(type != p.type)
                continue;
            
            pris = p.pris;
            funnet = true;
            break;
        }
    }
    
    //Hvis vi ikke har funnet pris
    if(!funnet) {
        pris = type == "helg" ? standard_helg[romtype] : standard_uke[romtype];
    }
    
    return pris;
}

int Pris::les_standard_pris(ifstream & infile) {
    
    string linje = read_text(infile);
    
    unsigned pos = (int) linje.find(" ");
    string prs = linje.substr(pos + 1);
    int pris = stoi(prs);
    
    return pris;
}

void Pris::les_special_price_for_you(ifstream & infile) {
    
    //Teller spesialpriser
    int teller = 0;
    unsigned pos;
    
    while(infile.good()) {
        string linje = read_text(infile);
        pos = (int) linje.find(" ");
        string startdato_str = linje.substr(0, pos);
        int startdato = stoi(startdato_str);
        
        string midlertidig = linje.substr(pos+1);
    
        pos = (int) midlertidig.find(" ");
        string sluttdato_str = midlertidig.substr(0, pos);
        int sluttdato = stoi(sluttdato_str);
        
        string antall_str = midlertidig.substr(pos+1);
        int antall = stoi(antall_str);
        
        //Looper gjennom alle spesialpriser for angitt dato
        for(int i = 0; i < antall; i++) {
            
            linje = read_text(infile);
            pos = (int) linje.find(" ");
            
            string romtype = linje.substr(0,pos);
            string midlertidig = linje.substr(pos+1);
            
            pos = (int) midlertidig.find(" ");
            string type = midlertidig.substr(0,pos);
            string pris_str = midlertidig.substr(pos+1);
            
            int pris = stoi(pris_str);
            
            Spesialpris p = {
                startdato,
                sluttdato,
                romtype,
                type,
                pris
            };
            
            spesialpriser[teller++] = p;
        }
        
        antall_spesialpriser = teller;
    }
}