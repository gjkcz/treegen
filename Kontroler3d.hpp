#ifndef __H_KONTROLER3D_INCLUDED_
#define __H_KONTROLER3D_INCLUDED_

#include <windows.h>
#include <map>
#include "Input.hpp"
#include "Kamera.hpp"
#include "SWU/Konzole.hpp"

namespace sktrl
{

class Kontroler3d;
using UkazatelNaFunkciKontroleru = void (sktrl::Kontroler3d::*) (void);
using MapaFunkci = std::map<std::string, UkazatelNaFunkciKontroleru>;

class Kontroler3d
{
public:
    Kontroler3d( HWND& );
    ~Kontroler3d();
    std::string& prectiVstupAUpravKameru(float&);
    void posunKameru(skam::Smer kam, float nasobitel){
        iKamera.posunKameru(kam, nasobitel);
    }
    void otocKameru(skam::Smer kam){
        iKamera.otocKameru(kam);
    }
    void nastavRychlost(float rychlost){
                iKamera.nastavRychlost(rychlost);
    }
    void nastavCitlivost(int citlivost){
        iKamera.nastavCitlivostRotace(citlivost);
    }
    void dejKonzoli(const sk::Konzole& x) { iKonzole = x;}
    void dejMoznePrikazy( std::string* _moznePrikazy, int pocet ){
        moznePrikazy = _moznePrikazy;
        pocetMoznychPrikazu = pocet;
    }
    D3DXMATRIX * vemView();
    const D3DXVECTOR3& vemSmerHledi(){
        return iKamera.vemSmerHledi();
    }
    const D3DXVECTOR3& vemUmisteni(){
        return iKamera.vemUmisteni();
    }
protected:
private:
    std::map< std::string, void(sktrl::Kontroler3d::*)(void) > prikazy;
    std::string* moznePrikazy;
    int pocetMoznychPrikazu;
    HWND hWnd;
    si::Input iInput;
    sk::Konzole iKonzole;
    skam::Kamera iKamera;
    D3DXMATRIX * matrixView;
    std::string stav;

    void prazdnaFunkce();
    UkazatelNaFunkciKontroleru najdiFunkci(const std::string&);
    bool zavolejFunkci(UkazatelNaFunkciKontroleru);
    void generujStrom(void);
};


}
#endif // __H_KONTROLER3D_INCLUDED_

