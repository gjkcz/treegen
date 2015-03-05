#include "Engine.hpp"
namespace se
{
namespace h=helper;

Engine::Engine(sw::Okno* _okno) : iOkno(_okno), iKontroler3d(iOkno->hWnd)
{
    h::zapniStopky();
    void (se::Engine::*jedenStrom)(float) = &Engine::generujJedenStrom;
    void (se::Engine::*nastavRychlost)(float) = &Engine::nastavRychlost;
    void (se::Engine::*odeber)(float) = &Engine::odeberStrom;
    mapaFci["testy"] = &Engine::selfTest;
    mapaFci["jeden"] = jedenStrom;        // prob
    mapaFci["rychl"] = nastavRychlost;
    mapaFci["odebe"] = odeber;
    mapaFci["gener"] = &Engine::pridejStrom;
    mapaFci["eleme"] = &Engine::setRenderElement;
    mapaFci["backc"] = &Engine::switchClearColor;
    mapaFci["vymaz"] = &Engine::odeberStromy;
    mapaFci["regen"] = &Engine::regenerujStromy;
    mapaFci["reset"] = &Engine::reset;
    mapaFci["fovde"] = &Engine::dejFov;
    mapaFci["citli"] = &Engine::dejCitlivost;
    mapaFci["wiref"] = &Engine::switchWireframe;
    mapaFci["osvet"] = &Engine::switchOsvetlovat;
    mapaFci["nerot"] = &Engine::nerotuj;
    mapaFci["zhasn"] = &Engine::zhasniSvitilnu;
    mapaFci["rozzn"] = &Engine::rozzniSvitilnu;
    mapaFci["culli"] = &Engine::switchCulling;
    mapaFci["pride"] = &Engine::pridejStrom;
    std::string* prikazy = new std::string[mapaFci.size()];
    int c = 0;
    for (auto i = mapaFci.begin(); i != mapaFci.end(); ++i, ++c) {
        prikazy[c] = i->first;
    }
    iKontroler3d.dejMoznePrikazy(prikazy, mapaFci.size());
    #ifdef NAPOVEDA
    std::cout << "Pro zadani prikazu stiskni mezernik+prikaz[+mezera+argument]+enter. Pro odchod ESC. \nPohyb wsad+sipky+mys. Leve tlacitko mysi prida strom, prave ukonci program. "<< std::endl;
    #endif // NAPOVEDA
    fFOV = PI/3.6;
    dejCitlivost(3);
    pd3dZarizeni = NULL;
    g_pD3D = NULL;
}

void Engine::releaseD3d()
{
    stromy.clear();
#ifdef DESTRUCTORVERBOSE
    std::cout << "Engine release.\nPocet stromu: " << t::Tree::pocetInstanciStromu << std::endl;
    std::cout << "Releasing zarizeni" << std::endl;
#endif // DESTRUCTORVERBOSE
    if( pd3dZarizeni != NULL ) {
        pd3dZarizeni->Release();
        pd3dZarizeni = NULL;
    }
#ifdef DESTRUCTORVERBOSE
    std::cout << "Ok" << std::endl;
    std::cout << "Releasing d3d" << std::endl;
#endif // DESTRUCTORVERBOSE
    if( g_pD3D != NULL ) {
        g_pD3D->Release();
        g_pD3D = NULL;
    }
#ifdef DESTRUCTORVERBOSE
    std::cout << "ok" << std::endl;
#endif // DESTRUCTORVERBOSE
}

Engine::~Engine()
{
    releaseD3d();
    std::cout << "Engine destruktor dokoncil uvolnovani pameti alokovane jeho instanci iEngine.\n";
}

void Engine::priprav()              // vola porade: pripravView, pripravGeometrii,
{
    iKonzole.nastavBarvuPisma(sk::Barva::fbila);
//    iKonzole.vytiskniSablonu((std::string)"ok");
//    iKonzole.zjistiSoucasnouBarvu();
    iKonzole.nastavBarvuPisma(sk::Barva::fbila);
    std::cout << "Pripravuji D3D" << '\n';
    pripravView();
    std::cout << "Ok" << '\n';
    iKonzole.nastavBarvuPisma(sk::Barva::fzluta);
    std::cout << "Generuji stromy" << '\n';
    pripravGeometrii();
    iKontroler3d.nastavRychlost(5000.);
    std::cout << "Ok, pocet stromu je: " << t::Tree::pocetInstanciStromu << '\n';
    iKonzole.nastavBarvuPisma(sk::Barva::fbila);
    std::cout << "Hledi je ve smeru -x" << std::endl;
}

void Engine::pripravView()
{
    if(g_pD3D == NULL)
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        std::cout << "FAILED to create d3d object";

    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof( d3dpp ) );
    d3dpp.Windowed = true;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
//    d3dpp.EnableAutoDepthStencil = TRUE;
//    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
    d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

    if (pd3dZarizeni == NULL)
    if( FAILED(g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, this->iOkno->hWnd,
                                     D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                     &d3dpp, &pd3dZarizeni ) ) ) {
//        std::cout << E_FAIL;
        if(FAILED(g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, this->iOkno->hWnd,
                                        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                        &d3dpp, &pd3dZarizeni ))) {
            if(FAILED(g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, this->iOkno->hWnd,
                                            D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                            &d3dpp, &pd3dZarizeni ))) {
                if( FAILED(g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, this->iOkno->hWnd,
                                                 D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                                 &d3dpp, &pd3dZarizeni ) ) ) {
                    if(FAILED(g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, this->iOkno->hWnd,
                                                    D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                                    &d3dpp, &pd3dZarizeni ))) {
                        if(FAILED(g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_FORCE_DWORD, this->iOkno->hWnd,
                                                        D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                                        &d3dpp, &pd3dZarizeni ))) {

                        }
                    }
                }
            }
        }
    }


    pd3dZarizeni->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
    bcull = false;
    pd3dZarizeni->SetRenderState( D3DRS_FILLMODE , D3DFILL_WIREFRAME );
    bwireframe = true;
    // Turn on the zbuffer
//    pd3dZarizeni->SetRenderState( D3DRS_ZENABLE, TRUE );

    Svetlo::priprav(pd3dZarizeni);
    D3DXVECTOR3 smer = {0.f, 0.f, -1.};
    D3DCOLORVALUE barva = {0.1f, 0.1f, 0.1f};
    Svetlo denniSvetlo = {pd3dZarizeni, barva, se::smerove, smer};
    svetla.push_back(denniSvetlo);

    barva = {0.1, 0.1, 0.0};
    smer = {0.f, 0.05f, -1.};
    svetla.emplace_back(pd3dZarizeni, barva, se::smerove, smer);
    /*baterka musi byt posledni*/
    barva = {0.4, 0.4, 0.5};
    svetla.emplace_back(pd3dZarizeni, barva);
}

void Engine::pripravGeometrii()
{
    t::DruhStromu druhStromu;
    druhStromu.urovenRozvetveni = 12;
    druhStromu.pravdepodobnostRozvetveni = 91;
    druhStromu._iDType = 3;
    druhStromu._iRType = 4;
    druhStromu._iSType = 4;
    druhStromu.element = t::testValec;
    druhStromu.rozliseniE = 3;
    druhStromu.rozliseniV = 2;
    druhStromu.barva = t::bila;
    druhStromu.barveni = t::g;      // dasdASdASd
    D3DXMATRIX pocatek;
    fDalka = 950000.f; // ' nova fitura kazi formatovani
    float xoffset = -2*fDalka;
    float yoffset = -2*fDalka;
    float zoffset = 0.f;
    h::Okamzik zacatek = h::stopky::now();
    // PRVNI
    yoffset = 0.f;
    xoffset = -1*fDalka;
    D3DXMatrixTranslation(&pocatek, xoffset, yoffset, 0.f);
    stromy.emplace_back(druhStromu, pocatek, &pd3dZarizeni, 0.005f);     // Vytvori strom a prida ho na konec naseho vektoru stromu
    stromy[0].nastavKonzoli(iKonzole);

    D3DXVECTOR3 pocatecniBod = {10000000., 0., 0.};
    D3DXVECTOR3 koncovyBod = {5000., 40000., 100000.};
    yoffset = 10000.f;
    xoffset = -1*fDalka;
    D3DXMatrixTranslation(&pocatek, xoffset, yoffset, 0.f);
    // DRUHY
    xoffset = -3*fDalka;
    druhStromu.element = t::bod;
    druhStromu.barva = t::zlutozelena;
    D3DXMatrixTranslation(&pocatek, xoffset, yoffset, 0.f);
//    stromy.emplace_back(druhStromu, pocatek, &pd3dZarizeni, 0.009f);     // Vytvori strom a prida ho na konec naseho vektoru stromu

#ifdef STACK
    druhStromu.element = t::usecka;
    druhStromu._iDType = 3;
    druhStromu._iRType = 4;
    druhStromu._iSType = 0;
    int pocetStacku = 0;  // 1000
    int pocetStromuStacku = 1; //15
    try {
        float vyska = 0.f;
        for(int i = 0; i < pocetStacku; ++i) {
            xoffset = (i/sqrt((float)pocetStacku)) * fDalka-(sqrt((float)pocetStacku)/2)*fDalka+helper::random()*fDalka-fDalka*0.5;
            yoffset = (i-(i/(int)sqrt((float)pocetStacku)*(int)sqrt((float)pocetStacku)))* fDalka-(sqrt((float)pocetStacku)/2)*fDalka+helper::random()*fDalka-fDalka*0.5;
            D3DXMatrixTranslation(&pocatek, xoffset, yoffset, zoffset);
            for(int o = 0; o < pocetStromuStacku; ++o) {
//            xoffset = 0;
//            yoffset = 0;
//                zoffset += fDalka/10.f;

                int iTypu=8;
                int iTyp=0;
                bool bIAm = false;
                int l = 0;
                t::DruhStromu type = druhStromu;
                for(int c=0; c<3; c++) {
                    while(!bIAm) {
                        if (o%iTypu==l) {
                            bIAm=true;
                            iTyp=l;
                        }
                        l++;
                    }
                    (c==0)?(type._iSType=iTyp):((c==1)?(type._iRType=iTyp):(type._iDType=iTyp));
                    iTypu=(c==0)?5:3;
                    l = 0;
                    bIAm = false;
                }
//        type._iRType=5;
//        type._iDType=4;
                stromy.emplace_back(druhStromu, pocatek, &pd3dZarizeni, 0.00f);     // Vytvori strom a prida ho na konec naseho vektoru stromu
            }
            zoffset = 0.f;
        }
    }

    catch (std::exception& e) {
        std::cout << "Standard exception: " << e.what() << std::endl;
    }
#endif // STACK
    h::Doba dobaGenerovani = (h::stopky::now() - zacatek);
    float casVteriny = dobaGenerovani.count() / 1e6;
    std::cout << "Cas generovani: " << casVteriny << "ms\n";
    std::cout << "Generovani zabere: " << casVteriny/1e3 << " s\n";
    iOkno->nastavDoPopredi();
}

/* Postarej se o prikazi z cli a okna, obnov stav vstupu a uprav kameru. */
void Engine::prectiVstupAUpravKameru(float& arg)
{
    prikaz = iKontroler3d.prectiVstupAUpravKameru(arg);

    if(prikaz != "odejdi" & prikaz != "nic" & iOkno->jeOtevrene() == true) {
        try {
            std::cout << "Argument: "<< arg << std::endl;
            zavolejFunkci(najdiFunkci(prikaz), arg);
            prikaz = "nic";
        } catch (std::exception& e) {
            std::cout << "nejde zavolat fci: " << e.what() << std::endl;
        }
    } else if (prikaz == "odejdi") {
        iOkno->zavri();
        releaseD3d();
    }
}

void Engine::render3d()
{
    if( bbClearColor )
        pd3dZarizeni->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 255, 255, 255 ), 1.0f, 0 );
    else
        pd3dZarizeni->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 0, 0, 0 ), 1.0f, 0 );
    // Begin the scene
    if( SUCCEEDED( pd3dZarizeni->BeginScene() ) ) {
        D3DXMatrixPerspectiveFovLH( &maticeProjekce, fFOV, iOkno->vemRozmerX() / (FLOAT)(iOkno->vemRozmerY()), 1.0f, 102000000.0f );
        pd3dZarizeni->SetTransform( D3DTS_VIEW, iKontroler3d.vemView() );
        pd3dZarizeni->SetTransform( D3DTS_PROJECTION, &maticeProjekce );
        svetla[se::Svetlo::pocetInstanciSvetla - 1].svit(iKontroler3d.vemSmerHledi());  /*baterka*/
        for (auto &iSvetlo : svetla){
            iSvetlo.svit();
        }

        for (auto &iTree : stromy) {      // Vykresli obsah vectoru stromu
            iTree.aktualizujMatici();
            iTree.vykresli(bosvetlovat);
        }


        pd3dZarizeni->SetFVF( D3DFVF_VrcholB );
        pd3dZarizeni->SetRenderState( D3DRS_LIGHTING, false );
        for (auto &iUsecka : usecky) {
            iUsecka.aktualizujMatici();
            iUsecka.vykresli();
        }
        // End the scene
        pd3dZarizeni->EndScene();
    } else {
        std::cout << "Err rendering" << std::endl;
    }
    pd3dZarizeni->Present( NULL, NULL, NULL, NULL );
}


UkazatelNaFunkciEnginu Engine::najdiFunkci(const std::string& nazevFce)
{
    MapaFunkciEnginu::const_iterator iIteratoruMapyFunkci;
    iIteratoruMapyFunkci = mapaFci.find(nazevFce);
    if(iIteratoruMapyFunkci == mapaFci.end())
        throw EngineVyjimka("nenalezena pozadovana funkce enginu");
    else
        return iIteratoruMapyFunkci->second;
}

void Engine::zavolejFunkci(UkazatelNaFunkciEnginu ukazatelFce, float arg)
{
    (this->*ukazatelFce)(arg);
}

void Engine::odeberStrom(float)
{
    std::cout << "Pocet stromu je: " << t::Tree::pocetInstanciStromu << std::endl;
    if(stromy.size() != 0)
        stromy.erase(stromy.end());
    std::cout << "Ok, pocet stromu je: " << t::Tree::pocetInstanciStromu << '\n';
}

void Engine::odeberStromy(float)
{
    stromy.clear();
    std::cout << "Ok, pocet stromu je: " << t::Tree::pocetInstanciStromu << '\n';
//    stromy.erase(stromy.begin(), stromy.end());
}

void Engine::regenerujStromy(float kolikrat)
{
    t::DruhStromu druhStromu;
    druhStromu.urovenRozvetveni = 12;
    druhStromu.pravdepodobnostRozvetveni = 85;
    druhStromu._iDType = 3;
    druhStromu._iRType = 4;
    druhStromu._iSType = 4;
    druhStromu.element = t::usecka;
    druhStromu.barva = t::zelena;
    druhStromu.barveni = t::g;      // d
//    druhStromu.barva = D3DCOLOR_RGBA(100, 152, 10, 255);
    D3DXMATRIX pocatek;
    fDalka = 950000.f; // ' nova fitura kazi formatovani
    float xoffset = -2*fDalka;
    float yoffset = -2*fDalka;
    float zoffset = 0.f;
    // PRVNI
    yoffset = 0.f;
    xoffset = -1*fDalka;
    D3DXMatrixTranslation(&pocatek, xoffset, yoffset, 0.f);
    druhStromu.element = t::usecka;
    druhStromu._iDType = 3;
    druhStromu._iRType = 4;
    druhStromu._iSType = 0;
    int pocetStacku = 10*((int)kolikrat+1);  // 1000
    int pocetStromuStacku = 1; //15
    try {
        float vyska = 0.f;
        for(int i = 0; i < pocetStacku; ++i) {
            xoffset = (i/sqrt((float)pocetStacku)) * fDalka-(sqrt((float)pocetStacku)/2)*fDalka+helper::random()*fDalka-fDalka*0.5;
            yoffset = (i-(i/(int)sqrt((float)pocetStacku)*(int)sqrt((float)pocetStacku)))* fDalka-(sqrt((float)pocetStacku)/2)*fDalka+helper::random()*fDalka-fDalka*0.5;
            D3DXMatrixTranslation(&pocatek, xoffset, yoffset, zoffset);
            for(int o = 0; o < pocetStromuStacku; ++o) {
//            xoffset = 0;
//            yoffset = 0;
//                zoffset += fDalka/10.f;

                int iTypu=8;
                int iTyp=0;
                bool bIAm = false;
                int l = 0;
                t::DruhStromu type = druhStromu;
                for(int c=0; c<3; c++) {
                    while(!bIAm) {
                        if (o%iTypu==l) {
                            bIAm=true;
                            iTyp=l;
                        }
                        l++;
                    }
                    (c==0)?(type._iSType=iTyp):((c==1)?(type._iRType=iTyp):(type._iDType=iTyp));
                    iTypu=(c==0)?5:3;
                    l = 0;
                    bIAm = false;
                }
//        type._iRType=5;
//        type._iDType=4;
                stromy.emplace_back(type, pocatek, &pd3dZarizeni, 0.00f);     // Vytvori strom a prida ho na konec naseho vektoru stromu
            }
            zoffset = 0.f;
        }
    }

    catch (std::exception& e) {
        std::cout << "Standard exception: " << e.what() << std::endl;
    }

    std::cout << "Ok, pocet stromu je: " << t::Tree::pocetInstanciStromu << '\n';
    iOkno->nastavDoPopredi();

}

void Engine::pridejStrom(float)
{
    iKonzole.nastavBarvuPisma(sk::fcervena);
    t::DruhStromu druhStromu;
    druhStromu.urovenRozvetveni = 12;
    druhStromu.pravdepodobnostRozvetveni = 85;
    druhStromu._iDType = 3;
    druhStromu._iRType = 4;
    druhStromu._iSType = 4;
    druhStromu.element = t::testValec;
    druhStromu.rozliseniV = 1000;
    druhStromu.rozliseniE = 60;
//    druhStromu.rozliseniV = 10;
//    druhStromu.rozliseniE = 3;
    druhStromu.barva = t::zelena;
    druhStromu.barveni = t::g;      // d
//    druhStromu.barva = D3DCOLOR_RGBA(100, 152, 10, 255);
    D3DXMATRIX pocatek;
    float vzdalenostOdKamery = 1000000.;
    float xoffset = -2.*iKontroler3d.vemUmisteni().x + iKontroler3d.vemSmerHledi().x*vzdalenostOdKamery;
    float yoffset = 2.*iKontroler3d.vemUmisteni().z + iKontroler3d.vemSmerHledi().z*-vzdalenostOdKamery;
    float zoffset = -2.*iKontroler3d.vemUmisteni().y + iKontroler3d.vemSmerHledi().y*vzdalenostOdKamery;
    // PRVNI
    D3DXMatrixTranslation(&pocatek, xoffset, yoffset, zoffset);
    try {
        stromy.emplace_back(druhStromu, pocatek, &pd3dZarizeni, 0.0009f);     // Vytvori strom a prida ho na konec naseho vektoru stromu
    } catch (std::exception& e) {
        std::cout << "exception occured in pridejStrom: " << e.what() << std::endl;
    }
    std::cout << "Ok, pocet stromu je: " << t::Tree::pocetInstanciStromu << '\n';
}

void Engine::generujJedenStrom(float arg)
{
    odeberStromy(arg);
    pridejStrom(arg);
    std::cout << "Ok, pocet stromu je: " << t::Tree::pocetInstanciStromu << '\n';
}


}
