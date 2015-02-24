#include "Kontroler3d.hpp"
namespace sktrl
{


Kontroler3d::Kontroler3d(HWND& _hWnd) : hWnd(_hWnd), iInput(_hWnd), iKamera()
{
//    void (sktrl::Kontroler3d::*fce1)(void) = &Kontroler3d::generujStrom;
//    prikazy["jeden"] = fce1;
//    matrixView = new D3DXMATRIX();
    stav = "nic";
}

Kontroler3d::~Kontroler3d()
{
#ifdef DESTRUCTORVERBOSE
    std::cout << "Destructor Kontroleru3d." << std::endl;
#endif // DESTRUCTORVERBOSE
    matrixView = nullptr;
//    delete[] moznePrikazy
//    moznePrikazy = nullptr;
//    delete matrixView;
#ifdef DESTRUCTORVERBOSE
    std::cout << "ok." << std::endl;
#endif // DESTRUCTORVERBOSE
}

D3DXMATRIX * Kontroler3d::vemView()
{
//    delete matrixView;
    matrixView = &iKamera.g_View;
    return matrixView;
}

std::string& Kontroler3d::prectiVstupAUpravKameru(float& argOut)
{
    stav = iInput.prectiStavVstupu();
    if (stav != "odejdi") {      // protoze se input nedocte..zpusobil by pad

        if (iInput.Keys[DIK_UP] & 0x80) {
            iKamera.otocKameru(skam::nahoru);
        }
        if (iInput.Keys[DIK_DOWN] & 0x80) {
            iKamera.otocKameru(skam::dolu);
        }
        if (iInput.Keys[DIK_LEFT] & 0x80) {
            iKamera.otocKameru(skam::doleva);
        }
        if (iInput.Keys[DIK_RIGHT] & 0x80) {
            iKamera.otocKameru(skam::doprava);
        }
        if  (iInput.Keys[DIK_ESCAPE] & 0x80){
            stav = "odejdi";
        }

        if (iInput.Keys[DIK_SPACE] & 0x80) {
            std::string tmpStr;
            float tmpCislo = 0.;
            iKonzole.nastavBarvuPisma(sk::ffialova);
            stav = iInput.prectiStavVstupu();
            iKonzole.nastavDoPopredi();
            std::cout << "Nynejsi rychlost je :" << iKamera.vemRychlost()  << std::endl;
            for (int i = 0; i < pocetMoznychPrikazu; ++i){
                    std::cout << "prikaz c." <<i<<" "<<moznePrikazy[i] << std::endl;
            }
            std::cout << "Pro odchod exit/odejdi. Zadej pozadovany petimistny prikaz: " << std::endl;
            std::getline(std::cin, tmpStr);
            std::stringstream(tmpStr) >> tmpCislo;
            if(tmpStr == "exit" || tmpStr == "odejdi"){  // chci pryc?
                stav = "odejdi";
            }
            else if(tmpCislo != 0.) {                   // chci rychlost?
                nastavRychlost(tmpCislo);
                std::cout << "Predpokladam rychlost.." << std::endl;
            } else {                                    // chci prikaz?
                if(tmpStr.length() > 6)
                std::stringstream(tmpStr.substr(6)) >> argOut;
//            argOut = tmpRychlost;

//            if( !zavolejFunkci(najdiFunkci(tmpStr)) ) {
//            std::cout << "tmpRych" << tmpRychlost << std::endl;
                std::cout << "argument: "<< argOut << std::endl;
                stav = tmpStr.substr(0, 5);      // predej prikaz dal az Enginu
            }
            SetForegroundWindow(hWnd);
            iInput.reset();
            iKamera.upravRotaciKamery(iInput.axs);

        } else if ( iInput.Keys[DIK_SUBTRACT] & 0x80 ) {
            std::string tmpStr;
            float tmpRychlost = iKamera.vemRychlost();
            tmpRychlost -= 10.f;
            iKonzole.nastavBarvuPisma(sk::ffialova);
            stav = iInput.prectiStavVstupu();
            iKonzole.nastavDoPopredi();
            std::cout << "Zmensuji rychlost o 10." << std::endl;
            std::cout << "Nova rychlost je :" << tmpRychlost << std::endl;
            iKamera.nastavRychlost(tmpRychlost);
            SetForegroundWindow(hWnd);
            iKamera.upravRotaciKamery(iInput.axs);
            iInput.reset();
        } else if ( iInput.Keys[DIK_ADD] & 0x80 ) {
            std::string tmpStr;
            float tmpRychlost = iKamera.vemRychlost();
            tmpRychlost += 10.f;
            iKonzole.nastavBarvuPisma(sk::ffialova);
            stav = iInput.prectiStavVstupu();
            iKonzole.nastavDoPopredi();
            std::cout << "Zvetsuji rychlost o 10." << std::endl;
            std::cout << "Nova rychlost je :" << tmpRychlost << std::endl;
            iKamera.nastavRychlost(tmpRychlost);
            SetForegroundWindow(hWnd);
            iKamera.upravRotaciKamery(iInput.axs);
            iInput.reset();
        } else {
            iKamera.upravRotaciKamery(iInput.axs);
        }

        if (iInput.Keys[DIK_W] & 0x80) {
            iKamera.posunKameru(skam::dopredu);
        }
        if (iInput.Keys[DIK_S] & 0x80) {
            iKamera.posunKameru(skam::dozadu);
        }
        if (iInput.Keys[DIK_Q] & 0x80) {
            iKamera.posunKameru(skam::nahoru);
        }
        if (iInput.Keys[DIK_E] & 0x80) {
            iKamera.posunKameru(skam::dolu);

        }
        if (iInput.Keys[DIK_A] & 0x80) {
            iKamera.posunKameru(skam::doleva);

        }
        if (iInput.Keys[DIK_D] & 0x80) {
            iKamera.posunKameru(skam::doprava);

        }



    }
    return stav;
}

UkazatelNaFunkciKontroleru Kontroler3d::najdiFunkci(const std::string& nazevFce)
{
    MapaFunkci::const_iterator iIteratoruMapyFunkci;
    iIteratoruMapyFunkci = prikazy.find(nazevFce);
    if ( iIteratoruMapyFunkci == prikazy.end() ) {
//        std::cout << "Tebou pozadovany prikaz zatim neexistuje, muzes ho vsak pridat. Predpokladam nastaveni rychlosti." << std::endl;
        return &Kontroler3d::prazdnaFunkce;
    }   else
        return iIteratoruMapyFunkci->second;

//        ( this->*(iIteratoruMapyFunkci->second) )();
}

bool Kontroler3d::zavolejFunkci(UkazatelNaFunkciKontroleru ukazatelNaFci)
{
    ( this->*ukazatelNaFci )();   // this je pointer na instanci tridy, ktera ma konkretni sadu funkci, napr funkci zavolejFunkci
    if(ukazatelNaFci == &Kontroler3d::prazdnaFunkce)
        return false;
    else
        return true;
}

void Kontroler3d::prazdnaFunkce()
{

}

void Kontroler3d::generujStrom(void)
{
    iKonzole.nastavBarvuPisma(sk::fcervena);
    std::cout << "budu generovat strom z kontroler" << std::endl;
}

}
