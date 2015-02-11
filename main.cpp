#include <windows.h>
#include "Engine.hpp"
#include "globals.hpp"

int t::Tree::pocetInstanciStromu = 0;

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
    sk::Konzole iKonzole;
    sw::Pozice iPozice {screenX, screenY};
    sw::Rozmery iRozmery {windowWidth, windowHeight};
    sw::Okno iOkno(iPozice, iRozmery, "Tree");    //vytvor okno
    //    sw::Okno iOkno(sw::Pozice(512.f, screenY), sw::Rozmery(512, 726), "Tree");    //vytvor okno pro acer
    se::Engine iEngine(iOkno);
    iEngine.dejKonzoli(iKonzole);
    iEngine.priprav();  //vytvori si d3d a z nej g_pd3dDevice a pak geometrii
    iOkno.ukaz();               // Show the window, az po inicializaci dx
    while ( iOkno.jeOtevrene() ) {              // main loop
//    iKonzole.nastavBarvuPisma(sk::Barva::foranzova);
        iOkno.postarejSeOZpravy();
        iEngine.prectiVstupAUpravKameru();
        if( iEngine.stav == WM_QUIT ){
            std::cout << "want to quit" << std::endl;break;}
        iEngine.render3d();
    }
    std::cout << "no prob" << std::endl;
    //    system("pause");
    return 0;
}
