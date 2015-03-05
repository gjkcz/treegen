#include "Tree.hpp"
namespace t
{
#define PROBLEMATICAL


/** \brief citron
*
 * \param
 * \param
 * \return
 *
 */

Tree::Tree()
{
    std::cout << "defaultni ctor stromu!" << std::endl;
    cstmvtxVrcholy = nullptr;
    vlastnostiVetvi = nullptr;
    bufferVrcholu = nullptr;
    bufferIndicii = nullptr;
    indicie = nullptr;
    ++pocetInstanciStromu;
}

Tree::Tree(Tree&& tmp)
{
    // move ctor, constructs itself with the temporary
#ifdef TREEVERBOSE
    std::cout << "Calling trees move ctor" << std::endl;
#endif // defined
    pocetIndicii = tmp.pocetIndicii;
    pocetElementu = tmp.pocetElementu;
    pocetClanku = tmp.pocetClanku;
    citacVrcholu = tmp.citacVrcholu;
    citacIndicii = tmp.citacIndicii;
    citacElementu = tmp.citacElementu;
    citacClanku = tmp.citacClanku;
    material = tmp.material;
    kolmice = std::move(tmp.kolmice);
    rotace = tmp.rotace;

    cstmvtxVrcholy =  tmp.cstmvtxVrcholy;
    indicie = tmp.indicie;
    vlastnostiVetvi = tmp.vlastnostiVetvi;
    pocetVrcholu = tmp.pocetVrcholu;
    pocetElementu = tmp.pocetElementu;
    pzarizeni = tmp.pzarizeni;
//    if(!vytvorBuffer())
//        throw StromVyjimka("Nepodarilo se vytvorit buffer pri move assign.");
//    if(!zkopirujVrcholyDoBuffru(tmp.cstmvtxVrcholy, tmp.pocetVrcholu))
//        throw StromVyjimka("Nejde zkopirovat vrcholy do buffru");
    bufferVrcholu = tmp.bufferVrcholu;
    bufferIndicii = tmp.bufferIndicii;

    matice = tmp.matice;
    druhStromu = tmp.druhStromu;
    pocetVetvi = tmp.pocetVetvi;

    maticeSkalovani = tmp.maticeSkalovani;
    maticeRotaceStromuX = tmp.maticeRotaceStromuX;
    maticeRotaceStromuZ = tmp.maticeRotaceStromuZ;
    barvaStromu = tmp.barvaStromu;
    per = tmp.per;
    gonx = tmp.gonx;
    sum = tmp.sum;
    countEm = tmp.countEm;
    bVlnit = tmp.bVlnit;
    zmenaRotace = tmp.zmenaRotace;

    tmp.bufferVrcholu = nullptr;
    tmp.cstmvtxVrcholy = nullptr;
    tmp.vlastnostiVetvi = nullptr;
    tmp.bufferIndicii = nullptr;
    tmp.indicie = nullptr;
    ++pocetInstanciStromu;
}

Tree::Tree(DruhStromu& _druhStromu, D3DXMATRIX& pocatek, LPDIRECT3DDEVICE9* _pzarizeni) : druhStromu(_druhStromu), pzarizeni(*_pzarizeni)
{
    zmenaRotace = 0.f;
    cstmvtxVrcholy = nullptr;
    vlastnostiVetvi = nullptr;
    bufferVrcholu = nullptr;
    bufferIndicii = nullptr;
    indicie = nullptr;
    D3DXMatrixRotationX(&maticeRotaceStromuX, -3.14159265358979323846/2);     // Otoci strom o -Pi kolem x
    D3DXMatrixScaling(&maticeSkalovani, 0.5f, 0.5f, 0.5f );                 // Zmensi strom na 1/2
    matice = pocatek;
    barvaStromu = D3DXVECTOR4(0.f,0.f,0.f,0.f);
    bVlnit = true;
    citacVrcholu = 0;
    citacIndicii = 0;
    per = 0.f;
    gonx = 0.f;
    sum = 0;
    countEm = 0;
    try {
        generujKmen();  // nastavi barvu stromu
#ifdef TREEVERBOSE
        std::cout << "\nGeneruji vlastnosti vetvi...";
#endif // defined
        if(!generujVlastnostiVetvi()) throw StromVyjimka("Nepodarilo se vygenerovat vlastnosti vetvi.");   // nastavi take pocet vetvi
        pocetVrcholu = spoctiVrcholy();
        pocetElementu = spoctiElementy();
#ifdef TREEVERBOSE
        std::cout << "Ok\n";
        std::cout << "Pravdepodobnost rozvetveni: " << druhStromu.pravdepodobnostRozvetveni<<"%" << std::endl;
        std::cout << "Pocet urovni koruny: " << druhStromu.urovenRozvetveni << std::endl;
        std::cout << "Pocet vetvi bude: " << pocetVetvi<< std::endl;
        std::cout << "Pocet elementu bude: " << pocetElementu << std::endl;
        std::cout << "Pocet vrcholu bude: " << pocetVrcholu << std::endl;
        std::cout << "Vyhrazuji misto pro vrcholy...";
#endif // defined
//        if(!alokujMistoProVrcholyAindicie()) throw StromVyjimka("Nelze vyhradit dostatek mista pro vrcholy!");
#ifdef TREEVERBOSE
        std::cout << "Ok\n";
#endif
        if(!uzamkniPoleDoBuffru()) throw StromVyjimka("Nepodarilo se pridat vrcholy do buffru.");
#ifdef TREEVERBOSE
        std::cout << "Generuji vrcholy...";
#endif // defined
        if(!generujVykreslovaciDataVetvi()) throw StromVyjimka("Nepodarilo se vygenerovat vrcholy vetvi.");      // zavola generujVetev->generujClanek
        if(!odemkniVrcholyProCteni()) throw StromVyjimka("nepodarilo se odemknout vrcholy pro cteni.");
#ifdef TREEVERBOSE
        std::cout << "Strom uspesne vygenerovan a pripraven ke kresleni.\n" << std::endl;
#endif // defined
    } catch (std::exception& e) {
        std::cout << "Standard exception: " << e.what() << std::endl;
    }

    ++pocetInstanciStromu;
}

Tree::Tree(DruhStromu& _druhStromu, D3DXMATRIX& pocatek, LPDIRECT3DDEVICE9* _pzarizeni, float zRot) : druhStromu(_druhStromu), pzarizeni(*_pzarizeni), zmenaRotace(zRot)
{
    cstmvtxVrcholy = nullptr;
    vlastnostiVetvi = nullptr;
    bufferVrcholu = nullptr;
    bufferIndicii = nullptr;
    indicie = nullptr;
    D3DXMatrixRotationX(&maticeRotaceStromuX, -3.14159265358979323846/2);     // Otoci strom o -Pi kolem x
    D3DXMatrixScaling(&maticeSkalovani, 0.5f, 0.5f, 0.5f );                 // Zmensi strom na 1/2
    matice = pocatek;
    barvaStromu = D3DXVECTOR4(0.f,0.f,0.f,0.f);
    material = *(new D3DMATERIAL9());
//ZeroMemory(&mtrl, sizeof(mtrl));
//    material.Ambient.r = 0.75f;
//    material.Ambient.g = 1.0f;
//    material.Ambient.b = 0.0f;
//    material.Ambient.a = 1.0f;
    D3DXCOLOR b = (D3DXCOLOR) druhStromu.barva;
    material.Diffuse = material.Ambient = (D3DCOLORVALUE)b;

    bVlnit = true;
    citacVrcholu = 0;
    citacIndicii = 0;
    per = 0.f;
    gonx = 0.f;
    sum = 0;
    countEm = 0;
    try {
        generujKmen();  // nastavi barvu stromu
#ifdef TREEVERBOSE
        std::cout << "\nGeneruji vlastnosti vetvi...";
#endif // defined
        if(!generujVlastnostiVetvi()) throw StromVyjimka("Nepodarilo se vygenerovat vlastnosti vetvi.");   // nastavi take pocet vetvi
        pocetVrcholu = spoctiVrcholy();
        pocetElementu = spoctiElementy();
#ifdef TREEVERBOSE
        std::cout << "Ok\n";
        std::cout << "Pravdepodobnost rozvetveni: " << druhStromu.pravdepodobnostRozvetveni<<"%" << std::endl;
        std::cout << "Pocet urovni koruny: " << druhStromu.urovenRozvetveni << std::endl;
        std::cout << "Pocet vetvi bude: " << pocetVetvi<< std::endl;
        std::cout << "Pocet clanku bude: " << pocetClanku << std::endl;
        std::cout << "Pocet elementu bude: " << pocetElementu << std::endl;
        std::cout << "Pocet indicii bude: " << pocetIndicii << std::endl;
        std::cout << "Pocet vrcholu bude: " << pocetVrcholu << std::endl;
        std::cout << "Vyhrazuji misto pro vrcholy...";
#endif // defined
//        if(!alokujMistoProVrcholyAindicie()) throw StromVyjimka("Nelze vyhradit dostatek mista pro vrcholy!");
#ifdef TREEVERBOSE
        std::cout << "Ok\n";
#endif
        if(!uzamkniPoleDoBuffru()) throw StromVyjimka("Nepodarilo se pridat vrcholy do buffru.");
#ifdef TREEVERBOSE
        std::cout << "Generuji vrcholy...";
#endif // defined
        if(!generujVykreslovaciDataVetvi()) throw StromVyjimka("Nepodarilo se vygenerovat vrcholy vetvi.");      // zavola generujVetev->generujClanek
        if(!odemkniVrcholyProCteni()) throw StromVyjimka("nepodarilo se odemknout vrcholy pro cteni.");
#ifdef TREEVERBOSE
        std::cout << "Strom uspesne vygenerovan a pripraven ke kresleni.\n" << std::endl;
#endif // defined
    } catch (std::exception& e) {
        std::cout << "Standard exception: " << e.what() << std::endl;
    }

    ++pocetInstanciStromu;
}


/** \brief Move assignment
 *
 * \param rvalueref
 * \return itself
 *
 */

Tree& Tree::operator=(Tree&& tmp)       // move assignment
{
    material = tmp.material;
    rotace = tmp.rotace;
    kolmice = std::move(tmp.kolmice);
    for (int i = 0; i < pocetVrcholu; ++i)
        pridejNormaluVrcholu(i, spocitejNormaluVrcholu(i));
    std::cout << "Pozor move assign chce ssmazat buffr" << std::endl;
    znicBuffery();
//    znicOstatniPointry();
//    if(cstmvtxVrcholy != nullptr)
//        delete[] cstmvtxVrcholy;
//    if(vlastnostiVetvi != nullptr)
//        delete[] vlastnostiVetvi;
//        std::cout << "stalo se" << std::endl;
    cstmvtxVrcholy =  tmp.cstmvtxVrcholy;
    indicie = tmp.indicie;
    vlastnostiVetvi = tmp.vlastnostiVetvi;
    pocetVrcholu = tmp.pocetVrcholu;
    pocetElementu = tmp.pocetElementu;
    pzarizeni = tmp.pzarizeni;
//    if(!vytvorBuffer())
//        throw StromVyjimka("Nepodarilo se vytvorit buffer pri move assign.");
//    if(!zkopirujVrcholyDoBuffru(tmp.cstmvtxVrcholy, tmp.pocetVrcholu))
//        throw StromVyjimka("Nejde zkopirovat vrcholy do buffru");
    bufferVrcholu = tmp.bufferVrcholu;
    bufferIndicii = tmp.bufferIndicii;

    matice = tmp.matice;
    druhStromu = tmp.druhStromu;
    pocetVetvi = tmp.pocetVetvi;
    maticeSkalovani = tmp.maticeSkalovani;
    maticeRotaceStromuX = tmp.maticeRotaceStromuX;
    maticeRotaceStromuZ = tmp.maticeRotaceStromuZ;
    barvaStromu = tmp.barvaStromu;
    citacVrcholu = tmp.citacVrcholu;
    citacIndicii = tmp.citacIndicii;
    per = tmp.per;
    gonx = tmp.gonx;
    sum = tmp.sum;
    countEm = tmp.countEm;
    bVlnit = tmp.bVlnit;
    zmenaRotace = tmp.zmenaRotace;

    tmp.bufferVrcholu = nullptr;
    tmp.cstmvtxVrcholy = nullptr;
    tmp.vlastnostiVetvi = nullptr;
    tmp.bufferIndicii = nullptr;
    tmp.indicie = nullptr;

#ifdef TREEVERBOSE
    std::cout << "Presouvani pomoci move assignment fce uspesne dokonceno." << std::endl;
#endif // defined
    return *this;
}


void Tree::znicBuffery()
{
#ifdef TREEVERBOSE
    std::cout << "Releasing (*bufferIndicii)" << std::endl;
#endif // TREEVERBOSE
    if( (bufferIndicii) != nullptr ) {
        (*bufferIndicii)->Release();
        (*bufferIndicii) = NULL;
        delete bufferIndicii;           // release the memory that had been used for holding pointerToBuffer o_|, ta prostredni se alokuje dyn
#ifdef TREEVERBOSE
        std::cout << "Ok" << std::endl;
#endif // defined
    } else
#ifdef TREEVERBOSE
        std::cout << "NO bufferIndicii=nullptr" << std::endl;
#endif // defined

#ifdef TREEVERBOSE
    std::cout << "Releasing (*bufferVrcholu)" << std::endl;
#endif // defined
    if( bufferVrcholu != nullptr ) {
        (*bufferVrcholu)->Release();
        (*bufferVrcholu) = NULL;
        delete bufferVrcholu;
#ifdef TREEVERBOSE
        std::cout << "Ok" << std::endl;
#endif // defined
    } else{
#ifdef TREEVERBOSE
        std::cout << "NO bufferVrcholu=nullptr" << std::endl;
#endif // defined
    }
}

void Tree::znicOstatniPointry()
{
#ifdef TREEVERBOSE
    std::cout << "Mazu porade indicie, vrcholy, vlastnosti" << std::endl;
#endif // TREEVERBOSE
    if(indicie != nullptr) {
//            std::cout << "ind:"<<indicie[50] << std::endl;
//        delete[] indicie;
//        indicie = nullptr;
#ifdef TREEVERBOSE
        std::cout << "ok" << std::endl;
#endif // TREEVERBOSE
    } else
#ifdef TREEVERBOSE
        std::cout << "NO, nullptr" << std::endl;
#endif // TREEVERBOSE
    if(cstmvtxVrcholy != nullptr) {
//        delete[] cstmvtxVrcholy;
//        cstmvtxVrcholy = nullptr;
#ifdef TREEVERBOSE
        std::cout << "ok" << std::endl;
#endif // TREEVERBOSE
    } else
#ifdef TREEVERBOSE
        std::cout << "NO, nullptr" << std::endl;
#endif // TREEVERBOSE
    if(vlastnostiVetvi != nullptr) {
        delete[] vlastnostiVetvi;
        vlastnostiVetvi = nullptr;
#ifdef TREEVERBOSE
        std::cout << "ok" << std::endl;
#endif // TREEVERBOSE
    } else{}
#ifdef TREEVERBOSE
        std::cout << "NO, nullptr" << std::endl;
#endif // TREEVERBOSE
}

/** \brief Detonator
 *
 * \param
 * \param
 * \return
 *
 */

Tree::~Tree()
{
#ifdef TREEVERBOSE
    std::cout << "Strom being destroyed!" << std::endl;

#endif // defined
    znicOstatniPointry();
    znicBuffery();
    --pocetInstanciStromu;
}


/** \brief Nastavi barvu pro primky.
 *
 * \param
 * \param
 * \return
 *
 */

bool Tree::generujKmen()
{
    int r=0,b=0,g=0;
    sum = 0;
    if(helper::zaokrouhli(helper::random())==1) {
        r=1;
        g=1;
        b=0;
    } else {
        r=1;
        g=1;
        b=0;
    }
    //r=1;g=0;b=0;//boruvkova
    //r=0;g=1;b=0;//zelenomodry spodek, lososovo zluty vrsek
    //r=0;g=0;b=1;//ugly
    //r=1;g=1;b=0;//fire
    //r=1;g=0;b=1;//fialovo modry
    //r=1;g=1;b=1;//vybledla zelena
    //r=0;g=0;b=0;//sediva
    sum = b+2*g+4*r;
    sum = druhStromu.barveni;
    switch(sum) {
    case 0: {
        barvaStromu = D3DXVECTOR4(0.f,0.f,0.f,1.f);
        break;
    }
    case 1: {
        barvaStromu = D3DXVECTOR4(0.f,0.f,1.f,1.f);
        break;
    }
    case 2: {
        barvaStromu = D3DXVECTOR4(0.f,1.f,0.f,1.f);
        break;
    }
    case 3: {
        barvaStromu = D3DXVECTOR4(0.f,1.f,1.f,1.f);
        break;
    }
    case 4: {
        barvaStromu = D3DXVECTOR4(1.f,0.f,0.f,1.f);
        break;
    }
    case 5: {
        barvaStromu = D3DXVECTOR4(1.f,0.f,1.f,1.f);
        break;
    }
    case 6: {
        barvaStromu = D3DXVECTOR4(1.f,1.f,0.f,1.f);
        break;
    }
    case 7: {
        barvaStromu = D3DXVECTOR4(1.f,1.f,1.f,1.f);
        break;
    }
    default: {
        barvaStromu = D3DXVECTOR4(0.f,0.f,0.f,0.f);
        break;
    }
    }
    return true;
}


/** \brief Vytvori predkonfiguraci vetvi(klic),
 *   spocte pocet koncovych a ostatnich vetvi(rozdvojenych),
 *   vytvori vlastnosti kmene,
 *   generuje vlastnostiVetvi
 * \param
 * \param
 * \return
 *
 */

bool Tree::generujVlastnostiVetvi()
{
#ifdef DEBUG
    kontrolniPocetVetvi = 0;
#endif // DEBUG
    int n = 1;
    int pocetV = 0;         // iterator parametru vetvi
    int pocetVKT = 0;       // pocet vetvi ktere nejsou
    byte* klic;
    int vCount=0;
    VlastnostiVetve parentPv;
    parentPv.k = false;
    int k = h::integratePower(2,druhStromu.urovenRozvetveni);       // Pocet vsech moznosti
    klic = new byte[k];
    for(int x = 0; x<k; x++) {              // Init klice
        klic[x] = 0x0000;
    }

#ifdef OLDPROBABILITY
    //
    // Generuje predkonfiguraci vetvi neboli rozvetveni do klice
    // preskocí nultou
    //
    for(int z = 0; z < druhStromu.urovenRozvetveni; z++) {	// opakuj pro každou z rad ps>od jedné preskocí nultou(kmen)
        n = pow(float(2), z);
        for(int x = 0; x < n; x++) { // opakuj pro každou z jednotlivých vetví
            if(klic[h::integratePower(2,z) + x] == 0x0000) { // když bude koncová, nebo z poslední rady, a zároven její parent není k
                if(druhStromu.urovenRozvetveni - z == 2) {   // kdyz jsme v posledni rade
                    klic[h::integratePower(2,z + 1) + 2 * x]=0x0001;
                    klic[h::integratePower(2,z + 1) + 2 * x + 1]=0x0001;
                } else {
                    if(z < 2 && (h::integratePower(2,z) + x) % 2==0) {
                        klic[h::integratePower(2,z + 1) + 2 * x]=0x0000;
                        klic[h::integratePower(2,z + 1) + 2 * x + 1]=0x0000;
                    } else if(helper::zaokrouhli(helper::random()*3)==1) {  // 1 ku 3, ze se obe ukonci
                        klic[h::integratePower(2,z+1)+2*x]=0x0001;
                        klic[h::integratePower(2,z+1)+2*x+1]=0x0001;
                    } else if(helper::zaokrouhli(helper::random()*3)==1) {  // 1 ku 3, ze se ukonci prvni
                        klic[h::integratePower(2,z+1)+2*x]=0x0001;
                        klic[h::integratePower(2,z+1)+2*x+1]=0x0000;
                    } else if(helper::zaokrouhli(helper::random()*3)==1) {  // 1 ku 3, ze se ukonci druha
                        klic[h::integratePower(2,z+1)+2*x]=0x0000;
                        klic[h::integratePower(2,z+1)+2*x+1]=0x0001;
                    } else {                                                // 3 ku 6, ze se obe rozvetvi
                        klic[h::integratePower(2,z+1)+2*x]=0x0000;
                        klic[h::integratePower(2,z+1)+2*x+1]=0x0000;
                    }
                }
            } else {
                //když bude parent koncový
                if(druhStromu.urovenRozvetveni-z>1) {
                    klic[h::integratePower(2,z+1)+2*x]=0x0002;
                    klic[h::integratePower(2,z+1)+2*x+1]=0x0002;
                }
            }
        }
    }
#else
//
    // Generuje predkonfiguraci vetvi neboli rozvetveni do klice
    // preskocí nultou
    //
    for(int z = 0; z < druhStromu.urovenRozvetveni; z++) {	// opakuj pro každou z rad ps>od jedné preskocí nultou(kmen)
        n = pow(float(2), z);
        for(int x = 0; x < n; x++) { // opakuj pro každou z jednotlivých vetví
            if(klic[h::integratePower(2,z) + x] == 0x0000) { // když bude koncová, nebo z poslední rady, a zároven její parent není k
                if(druhStromu.urovenRozvetveni - z == 2) {   // kdyz jsme v posledni rade
                    klic[h::integratePower(2,z + 1) + 2 * x]=0x0001;
                    klic[h::integratePower(2,z + 1) + 2 * x + 1]=0x0001;
                } else {
                    if(z < 2 && (h::integratePower(2,z) + x) % 2==0) {
                        klic[h::integratePower(2,z + 1) + 2 * x]=0x0000;
                        klic[h::integratePower(2,z + 1) + 2 * x + 1]=0x0000;
                    } else if(helper::zaokrouhli(helper::random()*pow(1.f - (druhStromu.pravdepodobnostRozvetveni/100.00f), -1.f))==1) {  // 1 ku pow((druhStromu.pravdepodobnostRozvetveni/100.00f), -1.f), ze se obe ukonci
                        klic[h::integratePower(2,z+1)+2*x]=0x0001;
                        klic[h::integratePower(2,z+1)+2*x+1]=0x0001;
                    } else if(helper::zaokrouhli(helper::random()*pow(1.f - (druhStromu.pravdepodobnostRozvetveni/100.00f), -1.f))==1) {  // 1 ku pow((druhStromu.pravdepodobnostRozvetveni/100.00f), -1.f), ze se ukonci prvni
                        klic[h::integratePower(2,z+1)+2*x]=0x0001;
                        klic[h::integratePower(2,z+1)+2*x+1]=0x0000;
                    } else if(helper::zaokrouhli(helper::random()*pow(1.f - (druhStromu.pravdepodobnostRozvetveni/100.00f), -1.f))==1) {  // 1 ku pow(druhStromu.pravdepodobnostRozvetveni/100.0f, -1.f), ze se ukonci druha
                        klic[h::integratePower(2,z+1)+2*x]=0x0000;
                        klic[h::integratePower(2,z+1)+2*x+1]=0x0001;
                    } else {                                                // 3 ku 6, ze se obe rozvetvi
                        klic[h::integratePower(2,z+1)+2*x]=0x0000;
                        klic[h::integratePower(2,z+1)+2*x+1]=0x0000;
                    }
                }
            } else {
                //když bude parent koncový
                if(druhStromu.urovenRozvetveni-z>1) {
                    klic[h::integratePower(2,z+1)+2*x]=0x0002;
                    klic[h::integratePower(2,z+1)+2*x+1]=0x0002;
                }
            }
        }
    }
#endif
    //
    //  Spocita vysledek predkonfigurace, tedy kolik vetvi se rozdvoji, kolik jich je dohromady.
    //
    int p = 0;      // rozdvojujici se vetve
    int o = 0;      // konecne vetve
    for(int h = 0; h<k; h++) {
        if(klic[h]==0x0000)
            p++;
        else if(klic[h]==0x0001)
            o++;
    }
    pocetVetvi = p+o;
    pocetKoncovychVetvi = o;
    pocetRozdvojujicichseVetvi = p;
    vlastnostiVetvi = new VlastnostiVetve[pocetVetvi];
    for(int x = 0; x < pocetVetvi; x++) {    // inicializace parametru vetve
        vlastnostiVetvi[x].k = false;
    }

    //
    //  inicializace kmenu
    //
    vlastnostiVetvi[0].suda = false;
    vlastnostiVetvi[0].r.rotace= 0;
    vlastnostiVetvi[0].aR = 0;//rotace;
    vlastnostiVetvi[0].r.sklon = PI/2;//-89*PI/180;
    vlastnostiVetvi[0].rT.rotace = 0;
    vlastnostiVetvi[0].rT.sklon = PI/2;//+1*PI/180;//-89*PI/180;
    vlastnostiVetvi[0].d = helper::random()*(100000+1111*druhStromu.urovenRozvetveni)+11111*druhStromu.urovenRozvetveni;
    vlastnostiVetvi[0].r.r = 0.999*(druhStromu.urovenRozvetveni-1)+555;
    vlastnostiVetvi[0].rT.r = vlastnostiVetvi[0].r.r *  (helper::random()*1+0.5)/10.f;
    vlastnostiVetvi[0].de =  50.f* PI/180;
#ifdef PROBLEMATICAL
    vlastnostiVetvi[0].x.x = 0.0f;
    vlastnostiVetvi[0].x.y = 0.0f;
    vlastnostiVetvi[0].x.z = 0.0f;
    if ( druhStromu.element == usecka ) {
        vlastnostiVetvi[0].rT.sklon = PI/2;
        vlastnostiVetvi[0].r.sklon = vlastnostiVetvi[0].rT.sklon;
        vlastnostiVetvi[0].rT.rotace = 0;
    }
#endif // PROBLEMATICAL

#ifndef PROBLEMATICAL
    if ( druhStromu.element == usecka )
        vlastnostiVetvi[0].m = vlastnostiVetvi[0].d/2.f;
    else
        vlastnostiVetvi[0].m =  1100.5f;//(2*PI*gpVs[0].r.r)/(360/(gpVs[0].de/(PI/180)));
#else
    if ( druhStromu.element == usecka) {
        vlastnostiVetvi[0].m = vlastnostiVetvi[0].d/2.f;
//        vlastnostiVetvi[0].m =  1000.f;//(2*PI*gpVs[0].r.r)/(360/(gpVs[0].de/(PI/180)));
    } else
        vlastnostiVetvi[0].m =  1100.5f;//(2*PI*gpVs[0].r.r)/(360/(gpVs[0].de/(PI/180)));
#endif // PROBLEMATICAL
    vlastnostiVetvi[0].posledniVrcholPredchoziVetve = 0;
    vlastnostiVetvi[0].rodicka = &vlastnostiVetvi[0];
#ifdef DEBUG
    kontrolniPocetVetvi++;
#endif // DEBUG
    pocetV++;
    //
    //      Nastaveni parametru vetvi podle klice + generuje zbyle parametry
    //
    for(int z = 0; z<druhStromu.urovenRozvetveni; z++) {	//opakuj pro každou z øad ps>od jedné pøeskoèí nultou(kmen)
        n=pow(float(2), z);
        for(int x = 0; x<n; x++) { // opakuj pro každou z jednotlivých vìtví
            if(klic[h::integratePower(2,z)+x] == 0x0000) { //když bude koncová, nebo z poslední øady, a zároveò její parent není k
                vlastnostiVetvi[pocetV] = generujVlastnostiVetve(vlastnostiVetvi[h::integratePower(2,z)+x - pocetVKT], 0, druhStromu);
                if(klic[h::integratePower(2,z+1)+2*x]==0x0000) {
                    vlastnostiVetvi[pocetV].k = false;
                } else {
                    vlastnostiVetvi[pocetV].k = true;
                }
                pocetV++;

                vlastnostiVetvi[pocetV] = generujVlastnostiVetve(vlastnostiVetvi[h::integratePower(2,z)+x - pocetVKT], 1, druhStromu);
                if(klic[h::integratePower(2,z+1)+2*x+1]==0x0000) {
                    vlastnostiVetvi[pocetV].k = false;
                } else {
                    vlastnostiVetvi[pocetV].k = true;
                }
                pocetV++;
            } else if(klic[h::integratePower(2,z)+x] == 0x0002) {
                //když bude parent koncový
                pocetVKT+=1;
            }
        }
    }

#ifdef TREEVERBOSE
#ifdef DEBUG
    if(kontrolniPocetVetvi == pocetVetvi)
        std::cout << "..Ok\nPocet vetvi odpovida odhadu.";
    else {
        std::cout << "Pocet vetvi neodpovida odhadu!" << std::endl;
        std::cout << "Je jich: " << kontrolniPocetVetvi << std::endl;
    }
#endif // DEBUG
#endif // defined
    return true;
}

VlastnostiVetve Tree::generujVlastnostiVetve( VlastnostiVetve& parent, int strana, DruhStromu& _tType)
{
#ifdef DEBUG
    ++kontrolniPocetVetvi;
#endif // DEBUG
    float ample = 1.f;
    float OrigoX, OrigoY, OrigoZ, afterY;
    float posunX, posunY, posunZ;
    float rp, uzk;
    float k=0.f;
    VlastnostiVetve pVs;

    afterY = cos(parent.rT.sklon)*(floor(parent.d/parent.m)*parent.m);//sin(atan((floor(parent.d/parent.m)*parent.m)/OrigoY)+parent.rT.sklon)*(OrigoY/cos(atan((floor(parent.d/parent.m)*parent.m)/OrigoY)));
    posunZ = parent.x.z+sin(parent.rT.sklon)*(floor(parent.d/parent.m)*parent.m);//cos(atan((floor(parent.d/parent.m)*parent.m)/OrigoY)+parent.rT.sklon)*(OrigoY/cos(atan((floor(parent.d/parent.m)*parent.m)/OrigoY)))+parent.x.z;
    posunY = parent.x.y+cos(parent.rT.rotace)*afterY;//cos(atan(afterY/OrigoX)+parent.rT.rotace)*(OrigoX/cos(atan(afterY/OrigoX)))+parent.x.y;
    posunX = parent.x.x+sin(parent.rT.rotace)*afterY;//sin(atan(afterY/OrigoX)+parent.rT.rotace)*(OrigoX/cos(atan(afterY/OrigoX)))+parent.x.x;
    pVs.x.z = posunZ;
    pVs.x.y = posunY;
    pVs.x.x = posunX;
#ifdef PROBLEMATICAL
    if ( druhStromu.element == usecka ) {
        float preponaSklonu = parent.d;
        float prilehlaSklonu = cos(parent.rT.sklon)*preponaSklonu;
        float protilehlaSklonu = sin(parent.rT.sklon)*preponaSklonu;
        float prilehlaRotace = cos(parent.rT.rotace)*prilehlaSklonu;
        float protilehlaRotace = sin(parent.rT.rotace)*prilehlaSklonu;
        pVs.x= {parent.x.x + protilehlaRotace, parent.x.y + prilehlaRotace, parent.x.z + protilehlaSklonu};
    } else
        pVs.x= {posunX, posunY, posunZ};
#endif // PROBLEMATICAL
    pVs.k = false;
    pVs.m = parent.m;
    pVs.suda = (strana%2==0)? true : false;
    pVs.posledniVrcholPredchoziVetve = 0;
    if(parent.posledniVrcholPredchoziVetve == 0)
        pVs.rodicka = &parent;


    switch(_tType._iSType) {
    case 0: {
        pVs.r.sklon = ((strana%2 == 0)?(helper::random()*parent.rT.sklon):(helper::random()*PI/2));
    }
    break;
    case 1: {
        k=6;
        pVs.r.sklon = ((strana%2 == 0)?(parent.rT.sklon-k*PI/180):(parent.rT.sklon-k*PI/180));
    }
    break;
    case 2: {
        pVs.r.sklon = ((strana%2 != 0)?(helper::random()*parent.rT.sklon):(helper::random()*PI/2));
    }
    break;
    case 3: {
        pVs.r.sklon = ((strana%2 == 0)?(helper::random()*PI/4):(helper::random()*PI/2));
    }
    break;
    case 4: {
        pVs.r.sklon = ((strana%2 == 0)?(helper::random()*PI/4+PI/4):(helper::random()*PI/2));
    }
    break;
    case 5: {
        pVs.r.sklon = ((strana%2 == 0)?(helper::random()*PI/4+PI/4):(helper::random()*PI/4+PI/4));
    }
    break;
    case 6: {
        pVs.r.sklon = ((strana%2 == 0)?(PI/8):(PI/3));
    }
    break;
    case 7: {
        k=6;
        pVs.r.sklon = ((strana%2 == 0)?(parent.rT.sklon-k*PI/180):(parent.rT.sklon-k*PI/180));
    }
    break;
    case 8: {
        k=(parent.rT.sklon==PI/2)?35.5:k=1.5;
        pVs.r.sklon = ((strana%2 == 0)?(parent.rT.sklon-k*PI/180):(parent.rT.sklon-k*PI/180));
    }
    case 9: {
        k=((parent.rT.sklon==PI/2)?(35.5):(500000.f/parent.x.z));
        pVs.r.sklon = ((strana%2 == 0)?(parent.rT.sklon-k*PI/180):(parent.rT.sklon-k*PI/180));
    }
    case 10: {
        k=((parent.rT.sklon==PI/2)?(-95.0f):(helper::random()*15.f));
        pVs.r.sklon = ((strana%2 == 0)?(parent.rT.sklon+k*PI/180):(parent.rT.sklon+k*PI/180));
    }

    case 11: {
        k=((parent.rT.sklon==PI/2)?(-45.0f):(helper::random()*2.f));
        pVs.r.sklon = ((strana%2 == 0)?(parent.rT.sklon+k*PI/180):(parent.rT.sklon+k*PI/180));
    }


    default: {

    }
    break;
    }
//    pVs.r.sklon = PI/4;
    pVs.rT.sklon = pVs.r.sklon;


    switch(_tType._iRType) {
    case 0: {
        pVs.r.rotace = ((strana%2 == 0)?
                        (parent.rT.rotace+((parent.rT.sklon==PI/2)?0:(atan(cos(parent.rT.sklon)*sin(pVs.r.sklon)/cos(pVs.r.sklon))))-((parent.rT.sklon==PI/2)?(PI/2):(PI/2))):
                        (parent.rT.rotace-((parent.rT.sklon==PI/2)?0:(atan(cos(parent.rT.sklon)*sin(pVs.r.sklon)/cos(pVs.r.sklon))))+((parent.rT.sklon==PI/2)?(PI/2):(PI/2))) );
    }
    break;
    case 1: {
        pVs.r.rotace = ((strana%2 == 0)?
                        (parent.rT.rotace+((parent.rT.sklon==PI/2)?0:(atan(cos(parent.rT.sklon)*sin(pVs.r.sklon)/cos(pVs.r.sklon))))-((parent.rT.sklon==PI/2)?(PI/2):(PI/4))):
                        (parent.rT.rotace-((parent.rT.sklon==PI/2)?0:(atan(cos(parent.rT.sklon)*sin(pVs.r.sklon)/cos(pVs.r.sklon))))+((parent.rT.sklon==PI/2)?(PI/2):(PI/4))) );
    }
    break;
    case 2: {
        pVs.r.rotace = ((strana%2 == 0)?
                        (parent.rT.rotace+((parent.rT.sklon==PI/2)?0:(atan(cos(parent.rT.sklon)*sin(pVs.r.sklon)/cos(pVs.r.sklon))))-((parent.rT.sklon==PI/2)?(PI/2):(helper::random()*PI/2))):
                        (parent.rT.rotace-((parent.rT.sklon==PI/2)?0:(atan(cos(parent.rT.sklon)*sin(pVs.r.sklon)/cos(pVs.r.sklon))))+((parent.rT.sklon==PI/2)?(PI/2):(PI/4))) );
    }
    break;
    case 3: {
        pVs.r.rotace = ((strana%2 == 0)?
                        (parent.rT.rotace-((parent.rT.sklon==PI/2)?(PI/2):(helper::random()*PI/2))):
                        (parent.rT.rotace+((parent.rT.sklon==PI/2)?(PI/2):(PI/4))) );
    }
    break;
    case 4: {
        pVs.r.rotace = ((strana%2 == 0)?
                        (parent.rT.rotace-((parent.rT.sklon==PI/2)?(PI/2):(helper::random()*PI+PI/2))):
                        (parent.rT.rotace+((parent.rT.sklon==PI/2)?(PI/2):(0))) );
    }
    break;
    case 5: {
        pVs.r.rotace = ((strana%2 == 0)?
                        (parent.rT.rotace+((parent.rT.sklon==PI/2)?(PI/2):(helper::random()*PI/2))):
                        (parent.rT.rotace-((parent.rT.sklon==PI/2)?(PI/2):(helper::random()*PI/2))) );
    }
    break;

    default: {

    }
    break;
    }
//    pVs.r.rotace = helper::random()*(PI);
    pVs.rT.rotace = pVs.r.rotace;

    switch(_tType._iDType) {
    case 6: {
        pVs.d = ((strana%2 == 0)?(helper::random()*19000+18277):(helper::random()*19000+18277));
    }
    break;
    case 1: {
        pVs.d = ((strana%2 == 0)?(0.9*parent.d):(helper::random()*19000+18277));
    }
    break;
    case 2: {
        pVs.d = ((strana%2 == 0)?(0.9*parent.d):(0.98*parent.d));
    }
    break;
    case 3: {
        pVs.d = ((strana%2 == 0)?(0.998*parent.d):(0.998*parent.d));
    }
    break;
    case 4: {
        pVs.d = ((strana%2 == 0)?((helper::random()*0.1+0.9)*parent.d):((helper::random()*0.02+0.98)*parent.d));
    }
    break;


    default: {
        pVs.d = ((strana%2 == 0)?(0.998*parent.d):(0.998*parent.d));
    }
    break;
    }
#ifdef PROBLEMATICAL
    /*minimalne pulka a maximalne stejna delka jako rodicka*/
    if ( druhStromu.element == usecka ) {
        pVs.d =(helper::random()/2.+1/2.)*parent.d;
        pVs.m = pVs.d;///2.f;
    }
#endif // PROBLEMATICAL
    return pVs;
}

/** \brief Spocita dopredu clanky, elementy, vrcholy, indicie.
 *         Vetve jsou spocteny uz v generujVlastnostiVetvi
 * \param
 * \param
 * \return
 *
 */

int Tree::spoctiVrcholy()
{
    //
    //spocteni vrcholu
    //
    int iVx=0;
    float Uzk=0;
    float rp=0;
    float iVxT = 0;
    float l=0;
    float v=0;
    float fRpDens;
    for(int m = 0; m < pocetVetvi; m++) {
        if(vlastnostiVetvi[m].k == false) {
            iVx += (1) * int(vlastnostiVetvi[m].d/vlastnostiVetvi[m].m);//++++++
        } else {
            iVx += (1) * int(vlastnostiVetvi[m].d/vlastnostiVetvi[m].m);
        }
    }
#ifdef PROBLEMATICAL
    if ( druhStromu.element == usecka ) {
        return pocetVetvi;//+2;
    } else
        return iVx;
#else
    return iVx;
#endif // PROBLEMATICAL
}

int Tree::spoctiElementy()
{
    switch (druhStromu.element) {
    case kruhBodu: {
        pocetElementu = druhStromu.rozliseniE;
        pocetVrcholu = 2*pocetElementu;
        pocetVetvi = 1;
        return pocetElementu;
        break;
    }
    case testValec: {
        pocetClanku = druhStromu.rozliseniV;
        pocetElementu = pocetClanku*druhStromu.rozliseniE*2+0;
//        pocetElementu = 2;
        pocetVrcholu = (pocetClanku+1)*druhStromu.rozliseniE;
        pocetIndicii = (pocetElementu + 2*pocetClanku);
        pocetVetvi = 1;
        return pocetElementu;
        break;
    }
    case testUsecka: {
        pocetElementu = 3;
        pocetVrcholu = 4;
        return 3;
        break;
    }
    case usecka: {
//    int iVx = 0;
//    for(int m = 0; m < pocetVetvi; m++) {
//        if(vlastnostiVetvi[m].k == false) {
//            iVx += (1) * int(vlastnostiVetvi[m].d/vlastnostiVetvi[m].m);//++++++
//        } else {
//            iVx += (1) * int(vlastnostiVetvi[m].d/vlastnostiVetvi[m].m);
//        }
//    }
#ifdef PROBLEMATICAL
        return pocetVetvi-1;        /*Az na kmen je ke kazdemu vrcholu jedna primka.*/
#else
        return (pocetVrcholu-1);
#endif // PROBLEMATICAL
        break;
    }
    default:
        return pocetVrcholu;
        break;
    }
}


/** \brief Generuje vrcholy,
 *
 * \param
 * \param
 * \return
 *
 */

void Tree::generujVrcholElementu(float r, float radiusZ, float sklony, float sklonz, float Dens, float posunX, float posunY, float posunZ)
{
    float Zkoord = 0.0f;
    float OrigoX, OrigoY, posX, posY, posZ;
    posX=posunX;
    posY=posunY;
    posZ=posunZ;
    cstmvtxVrcholy[citacVrcholu].x = posX;
    cstmvtxVrcholy[citacVrcholu].y = posY;
    cstmvtxVrcholy[citacVrcholu].z = posZ;
    cstmvtxVrcholy[citacVrcholu].color = druhStromu.barva;
#ifdef TREEVERBOSE
#ifdef DEBUG
    ++citacVrcholu;
#endif // DEBUG
#endif // TREEVERBOSE
    int tempColor;
    float colorK;
// konverze barev
//
//
    for(int b = 0; b<3; b++) {
        switch(b) {
        case 0: {
            colorK = barvaStromu.z;
            break;
        }
        case 1: {
            colorK = barvaStromu.y;
            break;
        }
        case 2: {
            colorK = barvaStromu.x;
            break;
        }
        }
        tempColor=(colorK * 255);
        cstmvtxVrcholy[citacVrcholu].color += DWORD(tempColor*(pow(float(16),b*2)));
    }
    citacVrcholu++;
}

void Tree::generujVrcholElementu(Element e, float x, float y, float z, Barva barva)
{
    switch ( e ) {
    case usecka:
        cstmvtxVrcholy[citacVrcholu].x = x;
        cstmvtxVrcholy[citacVrcholu].y = y;
        cstmvtxVrcholy[citacVrcholu].z = z;
        cstmvtxVrcholy[citacVrcholu].color = barva;
        int tempColor;
        float colorK;
        for(int b = 0; b<3; b++) {
            switch(b) {
            case 0: {
                colorK = barvaStromu.z;
                break;
            }
            case 1: {
                colorK = barvaStromu.y;
                break;
            }
            case 2: {
                colorK = barvaStromu.x;
                break;
            }
            }
            tempColor=(colorK * 255);
            cstmvtxVrcholy[citacVrcholu].color += DWORD(tempColor*(pow(float(16),b*2)));
        }

        citacVrcholu++;
        break;
    case kuzel:
        break;
    default:
        break;
    }

}

void Tree::generujVrcholElementu(Element e)
{
    switch ( e ) {
    case testValec: {
        float Dens = 2.* PI/druhStromu.rozliseniE;
        float OrigoX=0., OrigoY=0., posX=0., posY=0., posZ=0., posunX=0., posunY=0.;
        float Zkoord = 0.;
        float sklonz = PI/2;
        float sklony = 0.;
        float posunZ = 0.;
        float rMod = sin(citacClanku*PI/180)*5000. +100000.;
        float r = rMod;
            posunZ = citacClanku*(1000000./druhStromu.rozliseniV);
        if(citacVrcholu>=druhStromu.rozliseniE) {
//            r -= citacClanku*10000.;
        }
        float radiusZ = 50000.;
        for (float a = 2*PI; a >= Dens; a-=Dens) {																			//kruh
            r = rMod+sin(a*20)*5000.;
            OrigoX=cos((float)a-sklonz) * r + radiusZ;
            OrigoY=cos(sklony)* (sin((float)a-sklonz)) * r;
            if(OrigoX==0) {
                posX=0.;
                posY=0.;
            } else {
                posX=cos(atan(OrigoY/OrigoX)+sklonz)*(OrigoX/cos(atan(OrigoY/OrigoX))) + posunX;
                posY=sin(atan(OrigoY/OrigoX)+sklonz)*(OrigoX/cos(atan(OrigoY/OrigoX)))+ posunY;
            }
            posZ=Zkoord + sin(sklony)*(sin((float)a-sklonz)) * r + posunZ;
            cstmvtxVrcholy[citacVrcholu].x = posX;
            cstmvtxVrcholy[citacVrcholu].y = posY;
            cstmvtxVrcholy[citacVrcholu].z = posZ;
            cstmvtxVrcholy[citacVrcholu].color = druhStromu.barva;

            if(citacVrcholu+druhStromu.rozliseniE == pocetVrcholu) {}
            else if(citacVrcholu+druhStromu.rozliseniE < pocetVrcholu)
                generujIndexyElementu(testValec, citacVrcholu, citacVrcholu + druhStromu.rozliseniE);


            citacVrcholu++;
        }
        citacClanku++;
//        cstmvtxVrcholy[0].color = zelena;
//        cstmvtxVrcholy[citacVrcholu].color = azurova;

        break;
    }
    case kruhBodu: {
        float Dens = 2.* PI/druhStromu.rozliseniE;
        float OrigoX=0., OrigoY=0., posX=0., posY=0., posZ=0., posunX=0., posunY=0.;
        float Zkoord = 0.;
        float sklonz = PI/2;
        float sklony = 0.;
        float posunZ = 1000.*citacVrcholu;
        float radiusZ = 50000.;
        float r = 200000.;
        for (float a = 2*PI; a >= Dens; a-=Dens) {																			//kruh
            OrigoX=cos((float)a-sklonz) * r + radiusZ;
            OrigoY=cos(sklony)* (sin((float)a-sklonz)) * r;
            if(OrigoX==0) {
                posX=0.;
                posY=0.;
            } else {
                posX=cos(atan(OrigoY/OrigoX)+sklonz)*(OrigoX/cos(atan(OrigoY/OrigoX))) + posunX;
                posY=sin(atan(OrigoY/OrigoX)+sklonz)*(OrigoX/cos(atan(OrigoY/OrigoX)))+ posunY;
            }
            posZ=Zkoord + sin(sklony)*(sin((float)a-sklonz)) * r + posunZ;
            cstmvtxVrcholy[citacVrcholu].x = posX;
            cstmvtxVrcholy[citacVrcholu].y = posY;
            cstmvtxVrcholy[citacVrcholu].z = posZ;
            cstmvtxVrcholy[citacVrcholu].color = cervena;
            citacVrcholu++;
        }
        std::cout << "\nhoVrtochy: " << citacVrcholu << std::endl;
        break;
    }
    case testUsecka: {
        cstmvtxVrcholy[citacVrcholu].x = 0.f;
        cstmvtxVrcholy[citacVrcholu].y = 0.f;
        cstmvtxVrcholy[citacVrcholu].z = 0.f;
        cstmvtxVrcholy[citacVrcholu].color = druhStromu.barva;
        citacVrcholu++;

        cstmvtxVrcholy[citacVrcholu].x = 0.f;
        cstmvtxVrcholy[citacVrcholu].y = 0.f;
        cstmvtxVrcholy[citacVrcholu].z = 100000.f;
        cstmvtxVrcholy[citacVrcholu].color = druhStromu.barva;
        citacVrcholu++;

        cstmvtxVrcholy[citacVrcholu].x = 0.f;
        cstmvtxVrcholy[citacVrcholu].y = 10000.f;
        cstmvtxVrcholy[citacVrcholu].z = 200000.f;
        cstmvtxVrcholy[citacVrcholu].color = druhStromu.barva;
        citacVrcholu++;

        cstmvtxVrcholy[citacVrcholu].x = 0.f;
        cstmvtxVrcholy[citacVrcholu].y = -100000.f;
        cstmvtxVrcholy[citacVrcholu].z = 200000.f;
        cstmvtxVrcholy[citacVrcholu].color = druhStromu.barva;
        citacVrcholu++;
        break;
    }
    case kuzel:
        break;
    default:
        break;
    }

}

/** \brief Generuje indexy
 *
 * \param
 * \param
 * \return
 *
 */

void Tree::generujIndexyElementu(Element e, int pocatecniIndex)
{
    switch ( e ) {
    case testValec: {
        indicie[citacIndicii] = pocatecniIndex;
        ++citacIndicii;
        break;
    }
    case testUsecka: {
        indicie[0] = 0;
        indicie[1] = 1;

        indicie[2] = 1;
        indicie[3] = 2;

        indicie[4] = 1;
        indicie[5] = 3;
        break;
    }
    case usecka:
        indicie[citacIndicii] = pocatecniIndex;
        ++citacIndicii;
        indicie[citacIndicii] = pocatecniIndex+1;
        ++citacIndicii;
        break;
    case kuzel:
        break;
    default:
        break;
    }

}

void Tree::generujIndexyElementu(Element e, int pocatecniIndex, int koncovyIndex)
{
    switch ( e ) {
    case testUsecka:
        indicie[0] = 0;
        indicie[1] = 1;

        indicie[2] = 1;
        indicie[3] = 2;

        indicie[4] = 1;
        indicie[5] = 3;
        break;
    case testValec:
    case usecka:
        indicie[citacIndicii] = pocatecniIndex;
        ++citacIndicii;
        indicie[citacIndicii] = koncovyIndex;
        ++citacIndicii;
        citacElementu+=2;
        break;
    case kuzel:
        break;
    default:
        break;
    }
}

/*Spocitat normalu lze az po vygenerovani pozice.*/
/** \brief Pocitani kolmic
 *
 * \param
 * \param
 * \return
 *
 */

D3DXVECTOR3 Tree::spocitejNormaluVrcholu(int a, int b, int c)
{
    D3DXVECTOR3 normala;
    D3DXVECTOR3 b0 = {cstmvtxVrcholy[a].x, cstmvtxVrcholy[a].y, cstmvtxVrcholy[a].z};
    D3DXVECTOR3 b1 = {cstmvtxVrcholy[b].x, cstmvtxVrcholy[b].y, cstmvtxVrcholy[b].z};
    D3DXVECTOR3 b2 = {cstmvtxVrcholy[c].x, cstmvtxVrcholy[c].y, cstmvtxVrcholy[c].z};
    D3DXVECTOR3 u = b1-b0;
    D3DXVECTOR3 v = b2-b0;
    D3DXVec3Cross(&normala, &u, &v);
    D3DXVec3Normalize(&normala, &normala);
//    D3DXVECTOR3 konec = 100000.*normala + b0;
//    konec = {0.,0.,0.};
//    kolmice.emplace_back( matice, b0, konec, azurova, &pzarizeni );

    return normala;
}

D3DXVECTOR3 Tree::spocitejNormaluVrcholu(int a)
{
    int b = a+druhStromu.rozliseniE, c = a+1;
    D3DXVECTOR3 b0 = {cstmvtxVrcholy[a].x, cstmvtxVrcholy[a].y, cstmvtxVrcholy[a].z};
    D3DXVECTOR3 konec, n0, n1, vyslednice;
    if(b < pocetVrcholu && c < pocetVrcholu ) {     // spodni rada
        n0 = spocitejNormaluVrcholu(a, b, c);
        konec = 100000.*n0 + b0;
        #ifdef ZOBRAZ_NORMALY

        kolmice.emplace_back( matice, b0, konec, azurova, &pzarizeni, zmenaRotace );
        #endif // ZOBRAZ_NORMALY
        b = a+druhStromu.rozliseniE-1, c = a-1;
        if(c < 0) {
            c = a+druhStromu.rozliseniE;
            n1 = spocitejNormaluVrcholu(a, b, c);
        } else
            n1 = spocitejNormaluVrcholu(b, a, c);
        konec = 100000.*n1 + b0;
//        konec = {0.,0.,0.};
        #ifdef ZOBRAZ_NORMALY

        kolmice.emplace_back( matice, b0, konec, zelena, &pzarizeni, zmenaRotace );
        #endif // ZOBRAZ_NORMALY
        vyslednice = n0 + n1;
//        vyslednice = {vyslednice.x, vyslednice.y, 0.};        // jen xy slozka neni spravne
        D3DXVec3Normalize(&vyslednice, &vyslednice);
        konec = 100000.*vyslednice + b0;
        #ifdef ZOBRAZ_NORMALY

        kolmice.emplace_back( matice, b0, konec, modra, &pzarizeni, zmenaRotace );
        #endif // ZOBRAZ_NORMALY
    } else if(a<=pocetVrcholu-1) {                  // horni rada
        b = a-druhStromu.rozliseniE;
        if(c == pocetVrcholu) {
            c = b + 1;
            n0 = spocitejNormaluVrcholu(a, c, b);
            konec = 100000.*n0 + b0;
        #ifdef ZOBRAZ_NORMALY

            kolmice.emplace_back( matice, b0, konec, cervena, &pzarizeni, zmenaRotace );
        #endif // ZOBRAZ_NORMALY
        } else {
            n0 = spocitejNormaluVrcholu(a, c, b);
            konec = 100000.*n0 + b0;
        #ifdef ZOBRAZ_NORMALY

            kolmice.emplace_back( matice, b0, konec, azurova, &pzarizeni, zmenaRotace );
        #endif // ZOBRAZ_NORMALY
        }
        b = a-druhStromu.rozliseniE, c = a-1;
        n1 = spocitejNormaluVrcholu(a, b, c);
        konec = 100000.*n1 + b0;
//        konec = {0.,0.,0.};
        #ifdef ZOBRAZ_NORMALY

        kolmice.emplace_back( matice, b0, konec, zelena, &pzarizeni, zmenaRotace );
        #endif // ZOBRAZ_NORMALY
        vyslednice = n0 + n1;
        D3DXVec3Normalize(&vyslednice, &vyslednice);
        konec = 100000.*vyslednice + b0;
        #ifdef ZOBRAZ_NORMALY

        kolmice.emplace_back( matice, b0, konec, purpurova, &pzarizeni, zmenaRotace );
        #endif // ZOBRAZ_NORMALY

    }
    return vyslednice;
}

void Tree::pridejNormaluVrcholu(int pozice, D3DXVECTOR3 kolmice)
{
    if(cstmvtxVrcholy[pozice].kolmice == D3DXVECTOR3(0.,0.,0.))
        cstmvtxVrcholy[pozice].kolmice = kolmice;
    else
        std::cout << "Normala uz existuje!" << std::endl;
}


/** \brief Vytvori vrcholy, indicie a kolmice podle parametru vetve
 *
 * \param
 * \param
 * \return
 *
 */

bool Tree::generujElementyVetve(VlastnostiVetve& pV)
{
    float ample;//, per; //radius krouceniaa
    float sklony = 0.f; //=uhel v rad, sklonx
    float radiusZ = 0;
    float sklonz = 0;
    float posunX, posunY, posunZ;
    posunX = 0.f;
    posunY = 0.f;
    posunZ = 0.f;
    float Zkoord = 0.0f;
    ample= 1.f;
    sklonz = 0;
    float OrigoY = 0.f;
    float afterY = 0.f;
    float OrigoX = 0.f;
    float OrigoZ = 0.f;
    float Rorigin = pV.r.r;
    objRust TempRust = pV.r;
    float xAmp=1, yAmp=0;
    if(pV.k)
        pV.rT.r = 0.01f;

    switch (druhStromu.element) {
    case testValec: {
        generujVrcholElementu(druhStromu.element);
        for(int i = 0; i < pocetClanku; ++i) {
            ///*degenerovany trojuhelnik*/
//        generujIndexyElementu(testValec, druhStromu.rozliseni-1);
//        generujIndexyElementu(testValec, 2*druhStromu.rozliseni-1);
//        generujIndexyElementu(testValec, 2*druhStromu.rozliseni-1);
//        generujIndexyElementu(testValec, 3*druhStromu.rozliseni-1);
            ///*koncove spojovaci indexy*/
            generujIndexyElementu(testValec, 0+i*druhStromu.rozliseniE);
            generujIndexyElementu(testValec, 0+(i+1)*druhStromu.rozliseniE);
//        generujIndexyElementu(testValec, 0);
//        generujIndexyElementu(testValec, 0+druhStromu.rozliseni);
            generujVrcholElementu(druhStromu.element);
//        generujIndexyElementu(testValec, 0);
//        generujIndexyElementu(testValec, 1);
//            generujIndexyElementu(testValec, 0+druhStromu.rozliseni);
//            generujIndexyElementu(testValec, 0+2*druhStromu.rozliseni);
//////        generujIndexyElementu(testValec, 0+2*druhStromu.rozliseni);
//            generujVrcholElementu(druhStromu.element);
//        citacElementu /= 3;
//        generujIndexyElementu(testValec, 0);
//        generujIndexyElementu(testValec, 0+druhStromu.rozliseni);
//        generujIndexyElementu(testValec, 1);
//        generujIndexyElementu(testValec, 1+druhStromu.rozliseni);
//        generujIndexyElementu(testValec, 2);
//        generujIndexyElementu(testValec, 2+druhStromu.rozliseni);
//        indicie[citacIndicii] = 0;
//        ++citacIndicii;

        }
        for (int i = 0; i < pocetVrcholu; ++i)
            pridejNormaluVrcholu(i, spocitejNormaluVrcholu(i));

        break;
    }
    case kruhBodu: {
        generujVrcholElementu(druhStromu.element);
        generujVrcholElementu(druhStromu.element);
        /*
        for (float a = 2*PI; a> Dens; a-=Dens)																				//kruh
        	{
        		reality++;
        		OrigoX=cos((float)a-sklonz) * r + radiusZ;
        		OrigoY=cos(sklony)* (sin((float)a-sklonz)) * r;
        			posunX=cos(atan(OrigoY/OrigoX)+sklonz)*(OrigoX/cos(atan(OrigoY/OrigoX))) + posunX;
        			posunY=sin(atan(OrigoY/OrigoX)+sklonz)*(OrigoX/cos(atan(OrigoY/OrigoX)))+ posunY;
        		posZ=Zkoord + sin(sklony)*(sin((float)a-sklonz)) * r + posunZ;
        		Tvertices[vPoradi].Pos = XMFLOAT3(posunX,posunY,posZ);
        		//Tvertices[vPoradi].Color = XMFLOAT4(0.0f,a/5,1.0f,1.f);
        	       generujVrcholElementu(usecka, posunX, posunY, posunZ, druhStromu.barva);
        		Tvertices[vPoradi].Color = Barva;
        		vPoradi++;
        	}*/
//	generujVrcholElementu( druhStromu.element );
        break;
    }
    case bod: {
#ifdef PROBLEMATICAL
        // na zacatku spojim kazdy pocatecni vrchol s vrcholem rodicky
//            if ( pV.rodicka->posledniVrcholPredchoziVetve != 0)
//            generujIndexyElementu(druhStromu.element, pV.rodicka->posledniVrcholPredchoziVetve, citacVrcholu);
        TempRust.r += (pV.rT.r -pV.r.r)/floor(pV.d/pV.m);
        TempRust.rotace += (pV.rT.rotace-pV.r.rotace)/floor(pV.d/pV.m);
        TempRust.sklon += (pV.rT.sklon - pV.r.sklon)/floor(pV.d/pV.m);
        sklony = TempRust.sklon-PI/2;
        sklonz = -TempRust.rotace;
        OrigoZ+=pV.m;
        OrigoX = bVlnit?((2*xAmp+1)+cos(PI/20*(int)OrigoZ+PI/80)*xAmp):0;
        OrigoY = bVlnit?((2*yAmp+1)+sin(PI/20*(int)OrigoZ)*yAmp):0;
        afterY=cos(TempRust.sklon)*OrigoZ;
        posunZ=pV.x.z;
        posunY=pV.x.y;
        posunX=pV.x.x;
        generujVrcholElementu(usecka, posunX, posunY, posunZ, (pV.suda)?cervena:zelena);
        pV.posledniVrcholPredchoziVetve = citacVrcholu-1;
#else
        for (float x = 0.f; x+1.f< pV.d/pV.m; x+=1.f) {
            TempRust.r += (pV.rT.r -pV.r.r)/floor(pV.d/pV.m);
            TempRust.rotace += (pV.rT.rotace-pV.r.rotace)/floor(pV.d/pV.m);
            TempRust.sklon += (pV.rT.sklon - pV.r.sklon)/floor(pV.d/pV.m);
            sklony = TempRust.sklon-PI/2;
            sklonz =  -TempRust.rotace;
            OrigoZ+=pV.m;
            OrigoX = bVlnit?((2*xAmp+1)+cos(PI/20*(int)OrigoZ+PI/80)*xAmp):0;
            OrigoY = bVlnit?((2*yAmp+1)+sin(PI/20*(int)OrigoZ)*yAmp):0;
            afterY=cos(TempRust.sklon)*OrigoZ;
            posunZ=pV.x.z+sin(TempRust.sklon)*OrigoZ;
            posunY=pV.x.y+cos(TempRust.rotace)*afterY;
            posunX=pV.x.x+sin(TempRust.rotace)*afterY;
            countEm=citacVrcholu;
            generujVrcholElementu(TempRust.r, radiusZ, sklony, sklonz, pV.de, posunX, posunY, posunZ);
            switch(sum) {
            case 0: {
                barvaStromu.x+=0.01;
                barvaStromu.y+=0.01;
                barvaStromu.z+=0.01;
                break;
            }
            case 1: {

                barvaStromu.y+=0.1;
                barvaStromu.z-=0.001;
                break;
            }
            case 2: {

                barvaStromu.z+=0.01;
                barvaStromu.y-=0.001;
                break;
            }
            case 3: {

                barvaStromu.x+=0.01;
                barvaStromu.y-=0.001;
                barvaStromu.z-=0.001;
                break;
            }
            case 4: {

                barvaStromu.x-=0.001;
                barvaStromu.z+=0.01;
                break;
            }
            case 5: {

                barvaStromu.x-=0.001;
                barvaStromu.y+=0.01;
                break;
            }
            case 6: {
                barvaStromu.y-=0.0001;
                break;
            }
            case 7: {

                barvaStromu.x-=0.001;
                barvaStromu.z-=0.001;
                break;
            }
            }
        }
#endif // PROBLEMATICAL

        break;
    }
    case usecka: {
#ifdef PROBLEMATICAL
        float koeficientBarvy = 9.0f;
        // na zacatku spojim kazdy pocatecni vrchol s vrcholem rodicky
        if ( citacVrcholu != 0/* pV.rodicka->posledniVrcholPredchoziVetve != 0*/)
            generujIndexyElementu(druhStromu.element, pV.rodicka->posledniVrcholPredchoziVetve, citacVrcholu);
//            else
//            std::cout << "Rodicka je kmen" << std::endl;
        TempRust.r += (pV.rT.r -pV.r.r)/floor(pV.d/pV.m);
        TempRust.rotace += (pV.rT.rotace-pV.r.rotace)/floor(pV.d/pV.m);
        TempRust.sklon += (pV.rT.sklon - pV.r.sklon)/floor(pV.d/pV.m);
        sklony = TempRust.sklon-PI/2;
        sklonz = -TempRust.rotace;
        OrigoZ+=pV.m;
        OrigoX = bVlnit?((2*xAmp+1)+cos(PI/20*(int)OrigoZ+PI/80)*xAmp):0;
        OrigoY = bVlnit?((2*yAmp+1)+sin(PI/20*(int)OrigoZ)*yAmp):0;
        afterY=cos(TempRust.sklon)*OrigoZ;
        posunZ=pV.x.z;
        posunY=pV.x.y;
        posunX=pV.x.x;
#ifdef DEBUG
        generujVrcholElementu(usecka, posunX, posunY, posunZ, (pV.suda)?cervena:zelena);
#else
        generujVrcholElementu(usecka, posunX, posunY, posunZ, druhStromu.barva);
#endif // DEBUG
        pV.posledniVrcholPredchoziVetve = citacVrcholu-1;

#else
        float koeficientBarvy = 9.0f;
        // na zacatku spojim kazdy pocatecni vrchol s vrcholem rodicky
        if ( pV.rodicka->posledniVrcholPredchoziVetve != 0)
            generujIndexyElementu(druhStromu.element, pV.rodicka->posledniVrcholPredchoziVetve, citacVrcholu);
        for (float x = 0.f; x+1.f< pV.d/pV.m; x+=1.f) {
            TempRust.r += (pV.rT.r -pV.r.r)/floor(pV.d/pV.m);
            TempRust.rotace += (pV.rT.rotace-pV.r.rotace)/floor(pV.d/pV.m);
            TempRust.sklon += (pV.rT.sklon - pV.r.sklon)/floor(pV.d/pV.m);
            sklony = TempRust.sklon-PI/2;
            sklonz = -TempRust.rotace;
            OrigoZ+=pV.m;
            OrigoX = bVlnit?((2*xAmp+1)+cos(PI/20*(int)OrigoZ+PI/80)*xAmp):0;
            OrigoY = bVlnit?((2*yAmp+1)+sin(PI/20*(int)OrigoZ)*yAmp):0;
            afterY=cos(TempRust.sklon)*OrigoZ;
            posunZ=pV.x.z+sin(TempRust.sklon)*OrigoZ;
            posunY=pV.x.y+cos(TempRust.rotace)*afterY;
            posunX=pV.x.x+sin(TempRust.rotace)*afterY;
            countEm=citacVrcholu;
            if(x+2.f >= pV.d/pV.m) {           // konec vetve
                generujVrcholElementu( druhStromu.element, posunX, posunY, posunZ, druhStromu.barva );
                pV.posledniVrcholPredchoziVetve = citacVrcholu-1;
            } else {
                generujIndexyElementu( druhStromu.element, citacVrcholu );
                generujVrcholElementu( druhStromu.element, posunX, posunY, posunZ, druhStromu.barva );
            }
//            if( (x+2.f >= pV.d/pV.m) && (pV.k) )  // konec vetve a je v koncove rade
//            {
////                generujIndexyElementu( druhStromu.element, citacVrcholu );
//                generujVrcholElementu( druhStromu.element, posunX, posunY, posunZ, zluta );
////                pV.posledniVrcholPredchoziVetve = citacVrcholu-1;
////            else if(x+2.f >= pV.d/pV.m && pV.suda)     // konec sude vetve, oznacen cervene
//            }
//            else if((x+2.f >= pV.d/pV.m)&&(pV.suda))     // konec sude vetve, oznacen cervene
//            {
////                generujIndexyElementu( druhStromu.element, citacVrcholu );
//                generujVrcholElementu( druhStromu.element, posunX, posunY, posunZ, azurova );
////                pV.posledniVrcholPredchoziVetve = citacVrcholu-1;
//            }
//            else if(x+2.f >= pV.d/pV.m)             // konec vetve
//            {
////                generujIndexyElementu( druhStromu.element, citacVrcholu );
//                generujVrcholElementu( druhStromu.element, posunX, posunY, posunZ, azurova );
////                pV.posledniVrcholPredchoziVetve = citacVrcholu-1;
//            }
//            else if(pV.suda)    // oznacim si sude vetve purpurovou
//            {
//                generujIndexyElementu( druhStromu.element, citacVrcholu );
//                generujVrcholElementu( druhStromu.element, posunX, posunY, posunZ, purpurova );
//            }
//            else    // ani konec vrcstvy, ani vetve ani suda neni
//            {
//                generujIndexyElementu( druhStromu.element, citacVrcholu );
//                generujVrcholElementu( druhStromu.element, posunX, posunY, posunZ, zelena );
//            }

        }
#endif // PROBLEMATICAL
        switch(sum) {
        case 0: {
            barvaStromu.x+=0.01*koeficientBarvy;
            barvaStromu.y+=0.01*koeficientBarvy;
            barvaStromu.z+=0.01*koeficientBarvy;
            break;
        }
        case 1: {

            barvaStromu.y+=0.1*koeficientBarvy;
            barvaStromu.z-=0.001*koeficientBarvy;
            break;
        }
        case 2: {

            barvaStromu.z+=0.01*koeficientBarvy;
            barvaStromu.y-=0.001*koeficientBarvy;
            break;
        }
        case 3: {

            barvaStromu.x+=0.01*koeficientBarvy;
            barvaStromu.y-=0.001*koeficientBarvy;
            barvaStromu.z-=0.001*koeficientBarvy;
            break;
        }
        case 4: {

            barvaStromu.x-=0.001*koeficientBarvy;
            barvaStromu.z+=0.01*koeficientBarvy;
            break;
        }
        case 5: {

            barvaStromu.x-=0.001*koeficientBarvy;
            barvaStromu.y+=0.01*koeficientBarvy;
            break;
        }
        case 6: {
            barvaStromu.y-=0.0001*koeficientBarvy;
            break;
        }
        case 7: {

            barvaStromu.x-=0.001*koeficientBarvy;
            barvaStromu.z-=0.001*koeficientBarvy;
            break;
        }
        }
        break;
    }
    case testUsecka: {
        generujVrcholElementu( druhStromu.element );
        generujIndexyElementu( druhStromu.element, 0 );
        break;
    }
    default:
        break;
    }
    afterY=cos(TempRust.sklon)*OrigoZ;
    posunZ=pV.x.z+sin(TempRust.sklon)*OrigoZ;
    posunY=pV.x.y+cos(TempRust.rotace)*afterY;
    posunX=pV.x.x+sin(TempRust.rotace)*afterY;
    pV.x.x = posunX;
    pV.x.y = posunY;
    pV.x.z = posunZ;
    gonx = OrigoZ;
    return true;
}

bool Tree::generujVykreslovaciDataVetvi()
{
#ifdef DEBUG
    kontrolniPocetIndicii = 0;
#endif // DEBUG
    for(int f = 0; f<pocetVetvi; f++) {
//        std::cout << "rost vetev c> " << f << " uspesne." << std::endl;
        generujElementyVetve(vlastnostiVetvi[f]);
    }

//    switch ( druhStromu.element )
//    {
//    case usecka:{
//        for( int i=0; i<pocetVrcholu-1; ++i )
//        {
//            D3DXVECTOR3 temp = {0., 0., 1.};
//            D3DXVec3Normalize(&temp, &temp);
//            pridejNormaluVrcholu(i, temp);
//        }
//        break;
//    }
//
//    default:
//        break;
//    }
    int pocetIndiciiNaClanek;
    switch (druhStromu.element) {
    case testValec: {
        pocetIndiciiNaClanek = /*pocetClanku**/(druhStromu.rozliseniE*2 + 2);
//        iKonzole.vytiskniIndicie((const int*)indicie, citacIndicii, pocetIndiciiNaClanek);
        break;
    }
    case usecka: {
        pocetIndiciiNaClanek = citacIndicii/8;
        break;
    }
    default: {
        break;
    }
    }

#ifdef TREEVERBOSE
#ifdef DEBUG
    if(citacVrcholu == pocetVrcholu)
        std::cout << "..Ok\nPocet vrcholu odpovida odhadu." << std::endl;
    else {
        std::cout << "Pocet vrcholu neodpovida odhadu!" << std::endl;
        std::cout << "Je jich: " << citacVrcholu << std::endl;
    }
    if(citacIndicii == pocetIndicii)
        std::cout << "..Ok\nPocet indicii odpovida odhadu." << std::endl;
    else {
        std::cout << "Pocet indicii neodpovida odhadu!" << std::endl;
        std::cout << "Je jich: " << citacIndicii << std::endl;
    }
    if(pocetElementu == citacElementu)
        std::cout << "..Ok\nPocet elementu odpovida odhadu." << std::endl;
    else {
        std::cout << "Pocet elementu neodpovida odhadu!" << std::endl;
        std::cout << "Je jich: " << citacElementu << std::endl;
    }
    cstmvtxVrcholy[0].color = D3DCOLOR_XRGB(255,0,0);
    cstmvtxVrcholy[pocetVrcholu-1].color = D3DCOLOR_XRGB(255,0,0);
#endif // DEBUG
#endif // defined
    return true;
}


/** \brief Provede translace a rotace matice
 *
 * \param
 * \param
 * \return
 *
 */

void Tree::aktualizujMatici()
{

    if (zmenaRotace > 0.f)
        rotace += zmenaRotace;
    else
        rotace = 0.f;
    D3DXMatrixRotationZ(&maticeRotaceStromuZ, rotace);

    world = maticeRotaceStromuZ * matice * maticeSkalovani * maticeRotaceStromuX;

    for (auto &iUsecka : kolmice) {
        iUsecka.aktualizujMatici();
    }
}

/** \brief Vykresli vysledek
 *
 * \param
 * \param
 * \return
 *
 */

void Tree::vykresli(bool osvetlovat) const         // const fcion, so it cant change anything in our object
{
    for (auto &iUsecka : kolmice) {
        iUsecka.vykresli();
    }

    pzarizeni->SetTransform( D3DTS_WORLD, &world );
    switch (druhStromu.element) {
    case testValec: {
        if(osvetlovat) {
            pzarizeni->SetRenderState( D3DRS_LIGHTING, true );
            pzarizeni->SetStreamSource( 0, (*bufferVrcholu), 0, sizeof( VrcholBK ) );
            pzarizeni->SetFVF( D3DFVF_VrcholBK );
        } else {
            pzarizeni->SetRenderState( D3DRS_LIGHTING, false );
            pzarizeni->SetFVF( D3DFVF_VrcholPKB );
            pzarizeni->SetStreamSource( 0, (*bufferVrcholu), 0, sizeof( VrcholPKB ) );

        }
        pzarizeni->SetMaterial(&material);
        pzarizeni->SetIndices(*bufferIndicii);
        pzarizeni->DrawIndexedPrimitive( D3DPT_TRIANGLESTRIP, // PrimitiveType
                                         0,                  // BaseVertexIndex
                                         0,                  // MinIndex
                                         pocetVrcholu,                  // NumVertices
                                         0,                  // StartIndex
                                         pocetElementu+2*(pocetClanku-1)/*(nulovy obsah mezi clanky, napr03a36=033,363)*//*+4*(pocetClanku-1)*/ );                // PrimitiveCount
        break;
    }
    case kruhBodu:
    case bod: {
        pzarizeni->SetFVF( D3DFVF_VrcholBK );
        pzarizeni->SetStreamSource( 0, (*bufferVrcholu), 0, sizeof( VrcholBK ) );
        pzarizeni->SetRenderState( D3DRS_LIGHTING, false );
        pzarizeni->DrawPrimitive(
            D3DPT_POINTLIST, 0, pocetVrcholu );
        break;
    }
    case testUsecka:
    case usecka: {
        pzarizeni->SetRenderState( D3DRS_LIGHTING, false );
        pzarizeni->SetFVF( D3DFVF_VrcholPKB );
        pzarizeni->SetStreamSource( 0, (*bufferVrcholu), 0, sizeof( VrcholPKB ) );
        pzarizeni->SetIndices(*bufferIndicii);
        pzarizeni->DrawIndexedPrimitive( D3DPT_LINELIST, // PrimitiveType
                                         0,                  // BaseVertexIndex
                                         0,                  // MinIndex
                                         pocetVrcholu,                  // NumVertices
                                         0,                  // StartIndex
                                         pocetElementu );                // PrimitiveCount
        break;
    }
    case kuzel:
        break;

    default:
        break;
    }
}


/** \brief Vytvori buffer vrcholu a indicii a uzamkne(vyhradi pristup pro meneni) do nich nase pole,
 *          o alokaci se stara Zarizeni
 * \param
 * \param
 * \return
 *
 */

bool Tree::vytvorBufferVrcholu()
{
    bool vysledek;
#ifdef TREEVERBOSE
//    std::cout << "alokejme nejprve nejake misto pro buffer..." << std::endl;
#endif // defined
    try {
        bufferVrcholu = new LPDIRECT3DVERTEXBUFFER9;
    } catch (std::exception& e) {
        std::cout << "Standard exception: " << e.what() << std::endl;
    }
    try {
        int structSize = (druhStromu.element==usecka)?sizeof( VrcholPKB ):sizeof( VrcholBK );
        if( FAILED( pzarizeni->CreateVertexBuffer( pocetVrcholu * structSize,
                    0, D3DFVF_VrcholBK,
                    D3DPOOL_DEFAULT, bufferVrcholu, NULL ) ) ) {
            vysledek = false;
            std::cout << "Chyba vytvareni buffru.\n";
            std::cout << "Pocet dosud vytvorenych stromu je: " << Tree::pocetInstanciStromu << std::endl;
        } else {
            vysledek = true;
#ifdef TREEVERBOSE
//        std::cout << "Alokace buffru Ok." << std::endl;
#endif // defined
        }
    } catch (std::exception& e) {
        std::cout << "Std exception: " << e.what() << std::endl;
    }

    return vysledek;
}

bool Tree::vytvorBufferIndicii()
{
    bool vysledek = true;

    switch (druhStromu.element) {
    case testValec: {
        try {
            bufferIndicii = new LPDIRECT3DINDEXBUFFER9;     // dyn alc pointer
        } catch (std::exception& e) {
            vysledek = false;
            std::cout << "Heap allocation exception: " << e.what() << std::endl;
        }
        if( FAILED( pzarizeni->CreateIndexBuffer( pocetIndicii * sizeof(long),
                    D3DUSAGE_WRITEONLY , D3DFMT_INDEX32, D3DPOOL_DEFAULT,
                    bufferIndicii, NULL ) ) ) {
            std::cout << "Nepodarilo se vytvorit index buffer." << std::endl;
            vysledek = false;
        }
        break;
    }
    case testUsecka:
    case usecka: {
        try {
            bufferIndicii = new LPDIRECT3DINDEXBUFFER9;     // dyn alc pointer
        } catch (std::exception& e) {
            vysledek = false;
            std::cout << "Heap allocation exception: " << e.what() << std::endl;
        }
        if( FAILED( pzarizeni->CreateIndexBuffer( (pocetElementu * 2+2) * sizeof(long),
                    D3DUSAGE_WRITEONLY , D3DFMT_INDEX32, D3DPOOL_DEFAULT,
                    bufferIndicii, NULL ) ) ) {
            std::cout << "Nepodarilo se vytvorit index buffer." << std::endl;
            vysledek = false;
        }
        break;
    }
    case kuzel: {
        vysledek = false;
        break;
    }
    default: {
        vysledek = false;
        break;
    }
    }

    return vysledek;
}

bool Tree::uzamkniPoleDoBuffru()
{
    bool vysledek;
    // Create the vertex buffer.
    if( vytvorBufferVrcholu() )    // Je treba znat pocet vrcholu
        if( FAILED( (*bufferVrcholu)->Lock( 0, 0, ( void** )&cstmvtxVrcholy, 0 ) ) ) {
            std::cout << "Chyba uzamykani vrcholu do buffru.";
            vysledek = false;
        } else
            vysledek = true;
    else {
        std::cout << "Chyba vytvareni vertex buffru." << std::endl;
        vysledek = false;
    }
    // Create index buffer.
    if( druhStromu.element > 1 )
        if( vytvorBufferIndicii() )
            if( FAILED( (*bufferIndicii)->Lock(0, 0, ( void** )&indicie, 0) ) ) {
                std::cout << "Chyba uzamykani indicii do buffru." << std::endl;
                vysledek = false;
            } else
                vysledek = true;
        else {
            std::cout << "Chyba vytvareni index buffru." << std::endl;
            vysledek = false;
        }
    return vysledek;
}

/** \brief vyhradi pristup do buffru GP
 *
 * \param
 * \param
 * \return
 *
 */

bool Tree::odemkniVrcholyProCteni()
{
    bool vysledek;
    if(FAILED ((*bufferVrcholu)->Unlock())) {
        vysledek = false;
        std::cout << "Nepodarilo se odemknout buffer vrcholu pro cteni." << std::endl;
    } else
        vysledek = true;

    if( druhStromu.element > 1 && bufferIndicii != NULL)
        if(FAILED ((*bufferIndicii)->Unlock())) {
            vysledek = false;
            std::cout << "Nepodarilo se odemknout buffer indicii pro cteni." << std::endl;
        } else
            vysledek = true;
    return vysledek;
}


bool Tree::zkopirujVrcholyDoBuffru(VrcholBK* vrcholy, int pocet)
{
    bool vysledek;

    if( FAILED( (*bufferVrcholu)->Lock( 0, 0, ( void** )&cstmvtxVrcholy, 0 ) ) ) {
        std::cout << "Chyba uzamykani vrcholu do buffru.";
        vysledek = false;
    } else
        vysledek = true;
    for (int i = 0; i < pocet; ++i) {
        cstmvtxVrcholy[i] = vrcholy[i];
    }
    (*bufferVrcholu)->Unlock();
    return vysledek;
}

Vetev::Vetev()
{

}

Vetev::~Vetev()
{
//    delete[] vrcholy;
}

bool Tree::generujPlosky()
{

    return true;
}

bool Tree::generujListy()
{

    return true;
}

bool Tree::alokujMistoProVrcholyAindicie()
{
    try {
        cstmvtxVrcholy = new VrcholBK[pocetVrcholu];
        switch (druhStromu.element) {
        case usecka:
            indicie = new long[pocetElementu*2];
            break;
        case kuzel:
            indicie = new long[pocetElementu*3];
            break;
        default:
            break;
        }

    } catch (std::exception& e) {
        std::cout << "Heap allocation vyjimka v alokujMistoVrcholu(): " << e.what() << std::endl;
    }
#ifdef TREEVERBOSE
#endif // defined
    return true;
}

}
