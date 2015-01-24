#include "Kontroler3d.hpp"
namespace sktrl
{


Kontroler3d::Kontroler3d(HWND hWnd) : iInput(hWnd), iKamera(), matrixView(new D3DXMATRIX())
{

}

Kontroler3d::~Kontroler3d()
{
    delete matrixView;
}

D3DXMATRIX * Kontroler3d::vemView()
{
    matrixView = &iKamera.g_View;
    return matrixView;
}

void Kontroler3d::posunKameru(skam::Smer kam, float nasobitel = 1.f)
{
    iKamera.posunKameru(kam, nasobitel);
}

HRESULT Kontroler3d::prectiVstupAUpravKameru()
{
    stav = iInput.prectiStavVstupu();
    if (stav != WM_QUIT)        // protoze se input nedocte..zpusobil by pad
    {

        iKamera.upravRotaciKamery(iInput.axs);

        if (iInput.Keys[DIK_W] & 0x80)
        {
            iKamera.posunKameru(skam::dopredu);
        }
        if (iInput.Keys[DIK_S] & 0x80)
        {
            iKamera.posunKameru(skam::dozadu);
        }
        if (iInput.Keys[DIK_Q] & 0x80)
        {
            iKamera.posunKameru(skam::nahoru);
        }
        if (iInput.Keys[DIK_E] & 0x80)
        {
            iKamera.posunKameru(skam::dolu);

        }
        if (iInput.Keys[DIK_A] & 0x80)
        {
            iKamera.posunKameru(skam::doleva);

        }
        if (iInput.Keys[DIK_D] & 0x80)
        {
            iKamera.posunKameru(skam::doprava);

        }
    }
    return stav;
}


}
