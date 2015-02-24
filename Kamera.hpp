#ifndef __H_KAMERA_INCLUDED__
#define __H_KAMERA_INCLUDED__

#include <d3dx9.h>
#include <iostream>
#include "globals.hpp"
namespace skam
{


enum Smer
{
    dopredu,
    dozadu,
    doleva,
    doprava,
    nahoru,
    dolu
};

class Kamera
{
public:
    Kamera();
    ~Kamera();
    void upravRotaciKamery(float * aOsy);
    void posunKameru(Smer kam);
    void posunKameru(Smer kam, float jakMoc);   // nasobitel
    void nastavRychlost(float rychlost) { fVel = rychlost; }
    void nastavCitlivostRotace(int _citl){
        nasobitelKoeficientu = _citl;
        koeficienRotaceOs[0] = nasobitelKoeficientu*0.0005f;
        koeficienRotaceOs[1] = nasobitelKoeficientu*D3DX_PI/11520;
    }
    void otocKameru(Smer kam);
    void otocKameru(Smer kam, float jakMoc);
    float& vemRychlost() { return fVel; }
    const D3DXVECTOR3& vemSmerHledi(){
        obnovSmerHledi();
        return (*vZaxis);
    }
    const D3DXVECTOR3& vemUmisteni(){
        return (*vTranslace);
    }
    D3DXMATRIX g_View;
protected:
private:
    D3DXVECTOR3 * Eye, * At, * Up, * vTranslace;
    D3DXMATRIX translate;
    D3DXMATRIX mRotateVX, mRotateVY, mRotateVZ;
    D3DXVECTOR3* vZaxis;
    D3DXVECTOR3* vKolmice;

    float rotaceKolemOs[3];
    float koeficienRotaceOs[3];
    int nasobitelKoeficientu;
    float CamRotRad;
    float RotUp;
    float CamRot;
    float CamRotVel;
    float fVel;

    void obnovSmerHledi(){
        vZaxis->x = g_View._13;
        vZaxis->y = g_View._23;
        vZaxis->z = g_View._33; // toto je presne smer, kterym hledim
    }
//    float fFOV;

};


}
#endif // __H_KAMERA_INCLUDED__

