#ifndef __TREETYPE_H_INCLUDED__
#define __TREETYPE_H_INCLUDED__
namespace t
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
    zelena = D3DCOLOR_RGBA(0, 255, 0, 255),
    cervena = D3DCOLOR_RGBA(255, 0, 0, 255),
    modra = D3DCOLOR_RGBA(0, 0, 255, 255),
    bila = D3DCOLOR_RGBA(255, 255, 255, 255),
    cerna = D3DCOLOR_RGBA(0, 0, 0, 255),
    zluta = D3DCOLOR_RGBA(255, 255, 0, 255),
    purpurova = D3DCOLOR_RGBA(255, 0, 255, 255),
    azurova = D3DCOLOR_RGBA(0, 255, 255, 255),
    zlutozelena = D3DCOLOR_RGBA(171, 233, 7, 226),
    oranzova = D3DCOLOR_RGBA(255, 128, 0, 240),

    fbila=0xF, fseda=8, fcerna=0x0,
    fmodra=0x9, ftyrkysova=0xB, ftmavemodra=1, ffialova=13,
    fzelena=0xA, ftmavezelena=2, fzelenozluta,
    fzluta=6, fjasnezluta=0x00e, foranzova=FOREGROUND_RED | BACKGROUND_BLUE | FOREGROUND_INTENSITY, fcervena=0xC,

    bbila, bcerna, bmodra=BACKGROUND_BLUE,

    bbilafcerna=0xF0, bcernafbila=0x0F
};

// b+2*g+4*r
enum Barveni
{
    a, b, c, d, e, f, g, y, nebarvit
};

enum Element
{
    bod=0, kruhBodu=1, usecka, kuzel, testUsecka, testValec
};

struct DruhStromu
{
    Element element;
    Barva barva;
    Barveni barveni;
    int rozliseniE;  /*Pocet vrcholu na element/2.*/
    int rozliseniV;  /*Pocet elementu na vetev.*/
    int urovenRozvetveni;
    int pravdepodobnostRozvetveni;
    int _iSType; //0-11
    int _iRType; //0-5
    int _iDType; //6.1.2.3.4.deflt
};


}
#endif // __TREETYPE_H_INCLUDED__

