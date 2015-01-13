#include <windows.h>
#include "Engine.hpp"
#include "view.h"
#include "globals.h"

INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
    sk::Konzole iKonzole;
    sw::Okno iOkno(sw::Pozice(screenX, screenY), sw::Rozmery(width, height), "Tree");    //vytvor okno
//    sw::Okno iOkno(sw::Pozice(512.f, screenY), sw::Rozmery(512, 726), "Tree");    //vytvor okno pro acer
    se::Engine iEngine(iOkno);
    iEngine.dejKonzoli(iKonzole);
    iEngine.priprav();  //vytvori si d3d a z nej g_pd3dDevice
    iOkno.ukaz();               // Show the window, az po inicializaci dx
    while ( iOkno.jeOtevrene() ) {              // main loop
        iOkno.postarejSeOZpravy();
        iEngine.prectiVstup();
        if( iEngine.stav == WM_QUIT )
            break;

        render( iEngine.vemG_pD3DDevice(), iEngine.vemPocetVrcholuStromu(),
                iEngine.vemKeys(), iEngine.vemAxs(), iEngine.vemTreeMatrixy(),
                iEngine.vemTreeVertexBuffers() );
    }
//    system("pause");
    return 0;
}
