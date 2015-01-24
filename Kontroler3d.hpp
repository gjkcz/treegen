#ifndef __H_KONTROLER3D_INCLUDED_
#define __H_KONTROLER3D_INCLUDED_

#include <windows.h>
#include "Input.hpp"
#include "Kamera.hpp"

namespace sktrl
{


class Kontroler3d
{
public:
    Kontroler3d(HWND);
    ~Kontroler3d();
    HRESULT prectiVstupAUpravKameru();
    void posunKameru(skam::Smer, float nasobitel);
    D3DXMATRIX * vemView();
protected:
private:
    si::Input iInput;
    skam::Kamera iKamera;
    D3DXMATRIX * matrixView;
    HRESULT stav;
};


}
#endif // __H_KONTROLER3D_INCLUDED_

