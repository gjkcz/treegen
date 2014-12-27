#include <windows.h>
#include "../msgProc.h"
#include <iostream>
#include <string>
namespace sw
{

struct Rozmery {
public:
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
public:
    int x, y;
    Pozice() : x(0), y(0) {}
    Pozice(int _x, int _y) : x(_x), y(_y) {}
};


class Okno
{
public:
    HWND hWnd;
    Okno()
    {
        std::cout << "";
    }
    Okno(Pozice x, Rozmery y, LPCSTR);
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
