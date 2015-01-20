#ifndef __OKNO_H_INCLUDED__
#define __OKNO_H_INCLUDED__


#include <windows.h>
#include "../msgProc.hpp"
#include <iostream>
#include <string>
namespace sw
{

struct Rozmery {
    float x;
    float y;
    Rozmery() : x(320), y(480) {}
    Rozmery(float _x, float _y)
    {
        x=_x;
        y=_y;
    }
};

struct Pozice {
    int x, y;
    Pozice() : x(0), y(0) {}
    Pozice(int _x, int _y) : x(_x), y(_y) {}
};

class Okno
{
public:
    HWND hWnd;
    Okno();
    Okno(const Pozice& x,const Rozmery& y, LPCSTR);
    ~Okno();
    void ukaz();
    bool jeOtevrene() const
    {
        return otevreno;
    }
    void postarejSeOZpravy();
protected:
private:
    bool otevreno;
    WNDCLASSEX wc;
    Pozice pozice;
    Rozmery rozmer;
    LPCSTR nazev;
    HRESULT bQuit;
    MSG msg;
};

}
#endif // __OKNO_H_INCLUDED__
