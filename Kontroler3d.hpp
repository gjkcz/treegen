#ifndef __H_KONTROLER3D_INCLUDED_
#define __H_KONTROLER3D_INCLUDED_

#include <windows.h>
#include "Input.hpp"
#include "Kamera.hpp"
#include "SWU/Konzole.hpp"

namespace sktrl
{

class Kontroler3d
{
public:
    Kontroler3d(HWND);
    ~Kontroler3d();
    HRESULT prectiVstupAUpravKameru();
    void posunKameru(skam::Smer, float nasobitel);
    void dejKonzoli(const sk::Konzole& x) { iKonzole = x;}
    D3DXMATRIX * vemView();
protected:
private:
    si::Input iInput;
    sk::Konzole iKonzole;
    skam::Kamera iKamera;
    D3DXMATRIX * matrixView;
    HRESULT stav;
};


}
#endif // __H_KONTROLER3D_INCLUDED_

