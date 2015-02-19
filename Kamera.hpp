#ifndef __H_KAMERA_INCLUDED__
#define __H_KAMERA_INCLUDED__

#include <d3dx9.h>
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
    D3DXMATRIX g_View;
protected:
private:
    D3DXVECTOR3 * Eye, * At, * Up, * vTranslace;
    D3DXMATRIX translate;
    D3DXMATRIX mRotateVX, mRotateVY, mRotateVZ;
    D3DXVECTOR3* vZaxis;
    D3DXVECTOR3 *vKolmice;

    float  CamRotRad;
    float  RotUp;
    float CamRot;
    float CamRotVel;
    float fVel;
//    float fFOV;

};


}
#endif // __H_KAMERA_INCLUDED__

