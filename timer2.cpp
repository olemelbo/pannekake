
#include <ctime>              //  tm-struct, time-funksjoner
#include "timer2.h"           //  (Denne filens deklarasjoner)


// **************************************************************************
//
// **  Funksjoner som behjelper med avlesning av tid og dato(h�ndtering).  **
//
// **************************************************************************


Timer::Timer()  {             //  Initialiserer med antall dager i hver m�ned:


 dager_pr_maaned[0]  = 31;
 dager_pr_maaned[1]  =  0;    //  Februar settes ikke opp, da den er avhengig
 dager_pr_maaned[2]  = 31;    //  av om det aktuelle �ret er skudd�r eller ei.
 dager_pr_maaned[3]  = 30;
 dager_pr_maaned[4]  = 31;
 dager_pr_maaned[5]  = 30;
 dager_pr_maaned[6]  = 31;
 dager_pr_maaned[7]  = 31;
 dager_pr_maaned[8]  = 30;
 dager_pr_maaned[9]  = 31;
 dager_pr_maaned[10] = 30;
 dager_pr_maaned[11] = 31;
}
                              //  Avleser klokka p� datamaskinen og oppdaterer
                              //    tre referanseoverf�rte parametre med timer,
                              //    minutter og sekunder:
void Timer::hent_tid(int& ti, int& mi, int& se)  {
  time(&tid);                  //  Avleser systemklokka
  tidspunkt = localtime(&tid); //     og konverterer:
  ti = tidspunkt->tm_hour;     //  Henter aktuelle felter i struct'en:
  mi = tidspunkt->tm_min;
  se = tidspunkt->tm_sec;
}

                              //  Avleser dagens dato p� datamaskinen.
int Timer::hent_dato()  {     //  Returnerer denne p� formen ����MMDD:
  int d, m, a;
  
  time(&tid);                  //  Avleser systemklokka
  tidspunkt = localtime(&tid); //     og konverterer:
  d = tidspunkt->tm_mday;      //  Henter aktuelle felter i struct'en:
  m = tidspunkt->tm_mon + 1;
  a = tidspunkt->tm_year + 1900;
  return ((a * 10000) + (m * 100) + d);  //  Regner ut/omgj�r og returnerer.
}

                              //  Finner en datos (p� formen ����MMDD)
                              //    dagnummer i �ret og returnerer dette:
int Timer::dagnummer(int t)  {   
  int d, m, a;
  konverter(t, d, m, a);        //  Konverterer 't' over i 'd', 'm' og 'a'.
  return (dagnummer(d, m, a));  //  Bruker den overloadede skjulte funksjonen.
}

                                //  Format (inn):  ����MMDD
int Timer::ukedagsnr(int t)  {  //  Retur: 0=S�ndag, 1=Mandag, 2=Tirsdag, ....
  int d, m, a;                  //         6=L�rdag, 99=mislykkes!

  time(&tid);                   //  Avleser systemklokka og konverterer.
  tidspunkt = localtime(&tid);  //  Gjort KUN for � f� fylt 'tidspunkt'     
                                //     med noe !!!
  konverter(t, d, m, a);        //  Konverterer 't' over i 'd', 'm' og 'a'.

  tidspunkt->tm_mday = d;       //  Fyller 'tidspunkt' med de nye utregnede
  tidspunkt->tm_mon  = m-1;     //    verdiene:
  tidspunkt->tm_year = a-1900;
                                //  'mktime' fyller 'tidspunkt's andre felter.
                                //  Evt. returneres -1 omcasted til 'time_t'.
  if (mktime(tidspunkt) != (time_t)-1)  //  Lykkes/suksess:
     return tidspunkt->tm_wday; //  Henter og returnerer ukedagsnr (0-6).
  else           //  Utenfor intervallet: 1/1-1970  -  18/1-2038 kl.19:14:07 :
     return 99;                 //  Returnerer feilverdien '99'.
}

                                             //  Returnerer antall dager mellom
int Timer::forskjell_datoer(int t1, int t2)  {  //  to datoer ('t1' og 't2'):
  int d1, d2, m1, m2, a1, a2, tot1, tot2, i; // Masse ulike hjelpevariable:

  konverter(t1, d1, m1, a1);                 //  Konverterer 't1/t2' over i 
  konverter(t2, d2, m2, a2);                 //   'd1/d2', 'm1/m2' og 'a1/a2':
  tot1 = dagnummer(d1, m1, a1);              //  Finner deres dagnummer i 
  tot2 = dagnummer(d2, m2, a2);              //   hvert sitt �r ('a1/a2').
  for (i = 1900;  i < a1;  i++)              //  Finner TOTALT antall dager
      tot1 += (skuddaar(i)) ? 366 : 365;     //   siden �r 1900 for hvert av
  for (i = 1900;  i < a2;  i++)              //   de to datoene:
      tot2 += (skuddaar(i)) ? 366 : 365;     
  return ((tot2 > tot1) ? tot2-tot1 : tot1-tot2);  //  Returnerer forskjellen.
}

                                 // Returnerer datoen ETTER 't', p� samme form:
int Timer::nestedato(int t)  {
  int d, m, a;
  
  konverter(t, d, m, a);           //  Konverterer 't' over i 'd', 'm' og 'a'.
  dager_pr_maaned[1] = (skuddaar(a))  ?  29 : 28;   //  Fyller feb. aktuelt �r.
  d++;                                              //  dag++
  if (d > dager_pr_maaned[m-1])  {  m++;  d = 1;  } //  Ny m�ned: mnd++  dag=1
  if (m > 12)                    {  a++;  m = 1;  } //  Nytt �r:  aar++  mnd=1
  return (a*10000) + (m*100) + d;  //  Regner ut/omgj�r og returnerer.
}



// *********************  PRIVATE FUNKSJONER: **********************

                                   //  IDENTISK TIL OPPG_20 (h�sten):
bool Timer::skuddaar(int aa)  {    //  Sjekker om et visst �r er skudd�r:
  if ((aa % 400 == 0)  || ((aa % 4 == 0) && (aa % 100) !=0))
     return true;                  //  Skudd�r dersom: (delelig med 400)
  else                             //    ELLER (delelig med 4 OG ikke med 100)
     return false;
}
                      //  IDENTISK TIL OPPG_20 (h�sten):
                      //  Ut fra datoens input, s� returneres (om mulig)
                      //    denne datoens dagnummer i �ret, ellers returneres 0.
int Timer::dagnummer(int da, int ma, int aa)  {
                                   //  Setter opp antall dager i m�nedene.
                                   //   Verdien for februar settes senere.
  int total_dagnr, i;

  if (aa < 1600  ||  aa > 2100) return 0;    //  Ulovlig �r.
  if (ma < 1     ||  ma > 12)   return 0;    //  Ulovlig m�ned.
                                   //  Ut fra om �ret er skudd�r eller ei,
                                   //    s� settes verdien for februar:
  dager_pr_maaned[1] = (skuddaar(aa))  ?  29 : 28;
  if (da < 1 ||  da > dager_pr_maaned[ma-1])  return 0;  // Ulovlig dag:
                                   //  Garantert at er en lovlig dato !!
  total_dagnr = da;
  for (i = 0;  i < ma-1;  i++)              // Regner ut datoens dagnummer.
     total_dagnr += dager_pr_maaned[i];

  return total_dagnr;                       // Returnerer dagnummeret.
}

                                   //  Konverterer 't' (p� formen '����MMDD'),
                                   //    over i de referanseoverf�rte 
                                   //    parametrene 'da', 'ma' og 'aa':
void Timer::konverter(int t, int& da, int& ma, int& aa)  { 
  aa = t / 10000;
  ma = (t - (aa * 10000)) / 100;
  da = t % 100;
}
