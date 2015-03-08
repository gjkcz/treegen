#ifndef __KONZOLE_H_INCLUDED__
#define __KONZOLE_H_INCLUDED__

#include <windows.h>    // potreba pro konstanty v Barva, jako FOREGROUND_RED
//#include <fcntl.h>
//#include <io.h>
//#include <stdio.h>
#include <iostream>
//#include <fstream>
#include <string>
#include <map>
#include "../Helper.hpp"
//#define _WIN32_WINNT 0x0500 // Abych mohl pouzit GetConsoleWindow redefined

namespace sk
{


//bit 0 - foreground blue
//bit 1 - foreground green
//bit 2 - foreground red
//bit 3 - foreground intensity
//
//bit 4 - background blue
//bit 5 - background green
//bit 6 - background red
//bit 7 - background intensity
enum Barva
{
    fbila=0xF, fseda=8, fcerna=0x0,
    fmodra=0x9, ftyrkysova=0xB, ftmavemodra=1, ffialova=13,
    fzelena=0xA, ftmavezelena=2, fzelenozluta,
    fzluta=6, fjasnezluta=0x00e, foranzova=FOREGROUND_RED | BACKGROUND_BLUE | FOREGROUND_INTENSITY, fcervena=0xC,

    bbila, bcerna, bmodra=BACKGROUND_BLUE,

    bbilafcerna=0xF0, bcernafbila=0x0F
};

class Sablona
{
    public:
    Sablona() : text(std::string("")), barva(fbila) {}
    Sablona(Barva _b, const std::string& _t) : barva(_b), text(_t) {}
    Barva barva;
    std::string text;
};


class Konzole
{
public:
//    std::map<std::string, Sablona> sablony;
    Konzole();
    void nastavDoPopredi();
    void nastavBarvuPisma(Barva);
    void nastavBarvuPisma(WORD);
    void vytiskniSablonu(std::string klic);
    void vytiskniXEnteru(int x);
    void vytiskniXMezer(int x);
    void vytiskniIndicie(const int* paIndicie, int pocet);
    void vytiskniIndicie(const int* paIndicie, int pocet, int indiciiNaClanek, bool btrianglelist);
protected:
private:
    std::string nazevKonzole;
    WORD soucasnaBarva;
    static const WORD MAX_CONSOLE_LINES = 500;
    const std::string& zjistiNazevKonzole();
    void zjistiSoucasnouBarvu();
    int pocetSloupcu;
//    void presmerujIODoKonzole();
};


}

#endif // __KONZOLE_H_INCLUDED__

