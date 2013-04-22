//
//  pris.cpp
//  Prosjekt
//
//	Created by Emil Kjelsrud, Kristin Annabel Folland and Ole Christian Melbostad
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
    
    //henter of konstruerer filnavn
    string kortnavn = hotellet->get_filnavn();
    string filnavn = kortnavn + ".PRS";

    //Åpner filstrøm
    ifstream infile(filnavn);
    
    if(!infile.is_open()) {
        cout << "Kunne ikke lese filen " << filnavn;
        return;
    }
    
    //Første linje er søppel
    string soppel = read_text(infile);
    
    //Leser inn standard ukepriser
    for(int i = 0; i < ANTALL_ROMTYPER; i++) {
        standard_uke[i] = les_standard_pris(infile);
    }

    //Neste linje er søppel.
    soppel = read_text(infile);
    
    //Leser inn standard helgpriser
    for(int i = 0; i < ANTALL_ROMTYPER; i++) {
        standard_helg[i] = les_standard_pris(infile);
    }
    
    les_special_price_for_you(infile);
}

//Tar i mot romtype og dato, og returnerer aktuell pris
int Pris::hent_pris(int romtype, int dato) {
    
    //søndag 0, lørdag 6
    int ukedagnr = timer.ukedagsnr(dato);
    
    //Konverterer dagtypen
    string type = ukedagnr == 0 || ukedagnr == 6 ? "helg" : "uke";
    string rom;
    bool funnet = false;
    
    //Pris er -1 helt til prisen er lest
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
            
            //Forkaster pris som ikke er relevant
            if(rom != p.romtype)
                continue;
            if(type != p.type)
                continue;
            
            //Her er pris funnet og vi brekket ut av løkken
            pris = p.pris;
            funnet = true;
            break;
        }
    }
    
    //Hvis vi ikke har funnet spesialpris,
    //henter vi standardpriser
    if(!funnet) {
        pris = type == "helg" ? standard_helg[romtype] : standard_uke[romtype];
    }
    
    return pris;
}

//Tar filstrøm som parameter og returnerer
//prisen for gjeldende linje etter definert standard-pris format
int Pris::les_standard_pris(ifstream & infile) {
    
    string linje = read_text(infile);
    
    unsigned pos = (int) linje.find(" ");
    string prs = linje.substr(pos + 1);
    int pris = stoi(prs);
    
    return pris;
}

//Tar filstrøm som paramenter og returnerer
//prisen for gjeldende linje etter definert spesial-pris format
void Pris::les_special_price_for_you(ifstream & infile) {
    
    //Teller spesialpriser
    int teller = 0;
    unsigned pos;
    
    //Løper på filen til vi har nådd slutten
    while(infile.good()) {
        
        //Henter første linje
        string linje = read_text(infile);
        pos = (int) linje.find(" ");
        
        //Første segment er startdato
        string startdato_str = linje.substr(0, pos);
        int startdato = stoi(startdato_str);
        
        //klargjør for splitting av andre segment
        string midlertidig = linje.substr(pos+1);
    
        //andre segment er sluttdato
        pos = (int) midlertidig.find(" ");
        string sluttdato_str = midlertidig.substr(0, pos);
        int sluttdato = stoi(sluttdato_str);
        
        //tredje og siste segment er
        //antallet priser som etterfølger
        string antall_str = midlertidig.substr(pos+1);
        int antall = stoi(antall_str);
        
        //Looper gjennom alle spesialpriser for angitt dato
        for(int i = 0; i < antall; i++) {
            
            //Henter linje og definerer segmentene
            //på samme måte som tidligere
            linje = read_text(infile);
            pos = (int) linje.find(" ");
            
            //Første segment er romtype
            string romtype = linje.substr(0,pos);
            string midlertidig = linje.substr(pos+1);
            
            pos = (int) midlertidig.find(" ");
            
            //andre segment er dagtypen
            string type = midlertidig.substr(0,pos);
            
            //siste segment er gjeldende pris
            string pris_str = midlertidig.substr(pos+1);
            int pris = stoi(pris_str);
            
            //Konstruerer en struct som holder alle
            //assosiative data, slik at vi enkelt kan
            //hente ut aktuelle priser.
            
            Spesialpris p = {
                startdato,
                sluttdato,
                romtype,
                type,
                pris
            };
            
            //Legger til struct i array og teller opp antallet
            spesialpriser[teller++] = p;
        }
        
        //Lagrer antallet spesialpriser slik at vi senere kan
        //løpe på denne når vi skal bla i structene.
        antall_spesialpriser = teller;
    }
}