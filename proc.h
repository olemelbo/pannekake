#if !defined(__PROC_H)
#define __PROC_H
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;

//  PROSEDYREDEKLARASJON:st
char les_kommando();
void skriv_meny();
void reserver_rom();
void avbestill_rom();
void innsjekking();
void utsjekking();
void registrer_regning();
void endre_ankomst_avreisedato();
void opprett_reg_post();
void endre_avreisedato();
void bytt_rom();
string does_hotell_exist_in_file(ifstream& infil, string userinput);
void oversikt_over_hotell();
void beskrivelse_av_suiter();
bool is_rom_category(string rom_kategori);
void vis_alle_reservasjoner_for_person();
void rom_ledig();
void vis_reservasjoner_for_rom();
void vis_navarende_beboer();
void vis_alle_ledige_rom_i_kategori();
void skriv_til_fil();
void bytt_hotell();
void les_fra_fil();
void avslutt();

#endif