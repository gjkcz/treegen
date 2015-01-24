#include <windows.h>
//#include <dinput.h>
#include "Engine.hpp"
//#include "view.hpp"
#include "globals.hpp"

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
    sk::Konzole iKonzole;
    sw::Pozice iPozice {screenX, screenY};
    sw::Rozmery iRozmery {width, height};
    sw::Okno iOkno(iPozice, iRozmery, "Tree");    //vytvor okno
//    sw::Okno iOkno(sw::Pozice(512.f, screenY), sw::Rozmery(512, 726), "Tree");    //vytvor okno pro acer
    se::Engine iEngine(iOkno);
//    std::cout << "Ello!\n";
    iEngine.dejKonzoli(iKonzole);
    iEngine.priprav();  //vytvori si d3d a z nej g_pd3dDevice
    iOkno.ukaz();               // Show the window, az po inicializaci dx
    while ( iOkno.jeOtevrene() ) {              // main loop
        iOkno.postarejSeOZpravy();
        iEngine.prectiVstupAUpravKameru();
        if( iEngine.stav == WM_QUIT )
            break;

        iEngine.render3d();
//        render( iEngine.vemG_pD3DDevice(), iEngine.vemPocetVrcholuStromu(),
//                iEngine.vemKeys(), iEngine.vemAxs(), iEngine.vemTreeMatrixy(),
//                iEngine.vemTreeVertexBuffers() );
    }
//    system("pause");
    return 0;
}
