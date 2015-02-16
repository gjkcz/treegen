#include "Engine.hpp"
namespace se
{
namespace h=helper;

Engine::Engine(const sw::Okno& _okno) : okno(_okno), iKontroler3d(okno.hWnd)
{
    h::zapniStopky();
//    std::cout << "Engine uniform initialized.";
    fFOV = D3DX_PI/3;
//    stromy = {};
//    D3DXMatrixRotationX(&mRotateW, -3.14159265358979323846/2);
}

Engine::~Engine()
{
    if( pd3dZarizeni != NULL )
        pd3dZarizeni->Release();
    std::cout << "Engine destruktor dokoncil uvolnovani pameti alokovane jeho instanci iEngine.\n";
    system("pause");
}

void Engine::priprav()
{
    iKonzole.nastavBarvuPisma(sk::Barva::fbila);
    iKonzole.vytiskniSablonu((std::string)"ok");
//    iKonzole.zjistiSoucasnouBarvu();
    iKonzole.nastavBarvuPisma(sk::Barva::fbila);
    std::cout << "Pripravuji D3D" << '\n';
    pripravView();
    std::cout << "Ok" << '\n';
    iKonzole.nastavBarvuPisma(sk::Barva::fzluta);
    std::cout << "Generuji stromy" << '\n';
    pripravGeometrii();
    std::cout << "Ok, pocet stromu je: " << t::Tree::pocetInstanciStromu << '\n';
    iKonzole.nastavBarvuPisma(sk::Barva::fbila);
    std::cout << "Hledi je ve smeru -x" << std::endl;


//    iKonzole.nastavBarvuPisma(sk::Barva::fcervena);
//    helper::Okamzik zacatek = helper::stopky::now();
//    helper::nahodneCislo();
//    helper::Okamzik konec = helper::stopky::now();
//    h::Doba dobaGenerovani = (konec - zacatek);
//    float casGenerovaniVteriny = dobaGenerovani.count() / 1000000000.f;
//    std::cout << "Jedno nahodne cislo zabere: " << casGenerovaniVteriny << " s\n";
//
//    iKonzole.nastavBarvuPisma(sk::Barva::fzelenozluta);
//    zacatek = helper::stopky::now();
//    for(int y = 0; y != 100; ++y)
//        std::cout << "Randomness test: " << helper::random() << std::endl;
//    konec = helper::stopky::now();
//    dobaGenerovani = (konec - zacatek);
//    casGenerovaniVteriny = dobaGenerovani.count() / 1000000000.f;
//    iKonzole.nastavBarvuPisma(sk::Barva::fcervena);
//    std::cout << "Sto nahodnych cisel zabere: " << casGenerovaniVteriny << " s\n";

//    oInput.prepareInputDevices(okno.hWnd);
}

void Engine::pripravView()
{
    // Create the D3D object.
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        std::cout << E_FAIL;

    // Set up the structure used to create the D3DDevice
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof( d3dpp ) );
    d3dpp.Windowed = true;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;

    pd3dZarizeni = NULL;
    // Create the D3DDevice
    if( FAILED(g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, this->okno.hWnd,
                                     D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                     &d3dpp, &pd3dZarizeni ) ) )
    {
//        std::cout << E_FAIL;
        if(FAILED(g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, this->okno.hWnd,
                                        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                        &d3dpp, &pd3dZarizeni )))
        {
            if(FAILED(g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, this->okno.hWnd,
                                            D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                            &d3dpp, &pd3dZarizeni )))
            {
                if( FAILED(g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, this->okno.hWnd,
                                                 D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                                 &d3dpp, &pd3dZarizeni ) ) )
                {
                    if(FAILED(g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, this->okno.hWnd,
                                                    D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                                    &d3dpp, &pd3dZarizeni )))
                    {
                        if(FAILED(g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_FORCE_DWORD, this->okno.hWnd,
                                                        D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                                        &d3dpp, &pd3dZarizeni )))
                        {

                        }
                    }
                }
            }
        }
    }


    // Turn off culling, so we see the front and back of the triangle
    pd3dZarizeni->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

    // Turn off D3D lighting, since we are providing our own vertex colors
    pd3dZarizeni->SetRenderState( D3DRS_LIGHTING, FALSE );

    //TMatX = new D3DXMATRIX[iObsah];

    if( g_pD3D != NULL )
        g_pD3D->Release();
}

void Engine::pripravGeometrii()
{
    t::DruhStromu druhStromu;
    druhStromu.urovenRozvetveni = 6;
    druhStromu.pravdepodobnostRozvetveni = 91;
    druhStromu._iDType = 3;
    druhStromu._iRType = 4;
    druhStromu._iSType = 4;

//    druhStromu.barva = t::zluta;
    druhStromu.element = t::usecka;
    druhStromu.barva = t::zelena;
//    druhStromu.barva = t::azurova;
    druhStromu.barveni = t::g;      // d
//    druhStromu.barva = D3DCOLOR_RGBA(100, 152, 10, 255);

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
    stromy.emplace_back(druhStromu, pocatek, &pd3dZarizeni, 0.009f);     // Vytvori strom a prida ho na konec naseho vektoru stromu
//    stromSpecimen = t::Tree {druhStromu, pocatek, &pd3dZarizeni};   // move assignment

    // DRUHY
    xoffset = -3*fDalka;
    druhStromu.element = t::bod;
    druhStromu.barva = t::azurova;
    D3DXMatrixTranslation(&pocatek, xoffset, yoffset, 0.f);
    stromy.emplace_back(druhStromu, pocatek, &pd3dZarizeni, 0.009f);     // Vytvori strom a prida ho na konec naseho vektoru stromu
//    stromy.emplace_back(druhStromu, pocatek, &pd3dZarizeni);     // Vytvori strom a prida ho na konec naseho vektoru stromu

    #ifdef STACK
    druhStromu._iDType = 3;
    druhStromu._iRType = 4;
    druhStromu._iSType = 0;
    int pocetStacku = 0;  // 1000
    int pocetStromuStacku = 1; //15
    try
    {
        float vyska = 0.f;
        for(int i = 0; i < pocetStacku; ++i)
        {
                xoffset = (i/sqrt((float)pocetStacku)) * fDalka-(sqrt((float)pocetStacku)/2)*fDalka+helper::random()*fDalka-fDalka*0.5;
                yoffset = (i-(i/(int)sqrt((float)pocetStacku)*(int)sqrt((float)pocetStacku)))* fDalka-(sqrt((float)pocetStacku)/2)*fDalka+helper::random()*fDalka-fDalka*0.5;
                D3DXMatrixTranslation(&pocatek, xoffset, yoffset, zoffset);
            for(int o = 0; o < pocetStromuStacku; ++o)
            {
//            xoffset = 0;
//            yoffset = 0;
//                zoffset += fDalka/10.f;

                int iTypu=8;
                int iTyp=0;
                bool bIAm = false;
                int l = 0;
                t::DruhStromu type = druhStromu;
                for(int c=0; c<3; c++)
                {
                    while(!bIAm)
                    {
                        if (o%iTypu==l)
                        {
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
                stromy.emplace_back(type, pocatek, &pd3dZarizeni, 0.009f);     // Vytvori strom a prida ho na konec naseho vektoru stromu
            }
            zoffset = 0.f;
        }
    }

    catch (std::exception& e)
    {
        std::cout << "Standard exception: " << e.what() << std::endl;
    }
    #endif // STACK
    h::Doba dobaGenerovani = (h::stopky::now() - zacatek);
    float casVteriny = dobaGenerovani.count() / 1e6;
    std::cout << "Cas generovani: " << casVteriny << "ms\n";
    std::cout << "Generovani zabere: " << casVteriny/1e3 << " s\n";
}

void Engine::prectiVstupAUpravKameru()
{
    stav = iKontroler3d.prectiVstupAUpravKameru();
}

void Engine::render3d()
{
    // Clear the backbuffer to a black color
    if( bbClearColor==0 )
        pd3dZarizeni->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 255, 255, 255 ), 1.0f, 0 );
    else
        pd3dZarizeni->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 0, 0, 0 ), 1.0f, 0 );
    // Begin the scene
    if( SUCCEEDED( pd3dZarizeni->BeginScene() ) )
    {
        pd3dZarizeni->SetFVF( D3DFVF_CUSTOMVERTEX );
        D3DXMatrixPerspectiveFovLH( &maticeProjekce, fFOV, windowWidth / (FLOAT)windowHeight, 1.0f, 102000000.0f );
        pd3dZarizeni->SetTransform( D3DTS_VIEW, iKontroler3d.vemView() );
        pd3dZarizeni->SetTransform( D3DTS_PROJECTION, &maticeProjekce );

//        stromSpecimen.aktualizujMatici();
//        stromSpecimen.vykresli();

        for (auto &iTree : stromy)        // Vykresli obsah vectoru stromu
        {
            iTree.aktualizujMatici();
            iTree.vykresli();
        }
        // End the scene
        pd3dZarizeni->EndScene();
    }
    else
    {
        std::cout << "Err rendering" << std::endl;
    }
    // Present the backbuffer contents to the display
    pd3dZarizeni->Present( NULL, NULL, NULL, NULL );
}


}
