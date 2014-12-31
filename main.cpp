#include <windows.h>
#include "Engine.hpp"
#include "view.h"
#include "globals.h"

INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
    RedirectIOToConsole();  // Presmeruj IO do nasi nove konzole
    string str;
//    sw::Okno okno1(sw::Pozice(screenX, screenY), sw::Rozmery(width, height), "Tree");    //vytvor okno
    sw::Okno okno1(sw::Pozice(512.f, screenY), sw::Rozmery(512, 726), "Tree");    //vytvor okno pro acer
    se::Engine iEngine(okno1);
    iEngine.priprav();  //vytvori si d3d a z nej g_pd3dDevice
    okno1.ukaz();               // Show the window, az po inicializaci dx
    while ( okno1.jeOtevrene() ) {              // main loop
        okno1.postarejSeOZpravy();
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
