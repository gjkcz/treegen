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
//    sw::Pozice iPozice {0, 0};
//    sw::Rozmery iRozmery {1024, 600};
    sw::Okno iOkno(iPozice, iRozmery, "Tree", hThisInstance);    //vytvor okno
//        sw::Okno iOkno(sw::Pozice(0.f, screenY), sw::Rozmery(1024, 726), "Tree");    //vytvor okno pro acer
    se::Engine iEngine(&iOkno);
    iEngine.dejKonzoli(iKonzole);
    iEngine.priprav();  //vytvori si d3d a z nej g_pd3dDevice a pak geometrii
    iOkno.ukaz();
    while ( iOkno.jeOtevrene() ) {              // main loop
//    iKonzole.nastavBarvuPisma(sk::Barva::foranzova);
        iEngine.prectiVstupAUpravKameru();
        if(!iOkno.postarejSeOZpravy()){                     // krizek
            std::cout << "want to quit by X" << std::endl;
            iEngine.releaseD3d();
            break;
        }
        else if(iEngine.prikaz == "odejdi" ){               // prikaz/mys
            std::cout << "want to quit by command or mouse" << std::endl;
            break;
        }
        iEngine.render3d();
    }
//    system("pause");
    return 0;
}
