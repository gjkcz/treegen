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
    paIndicie = nullptr;
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
    vrcholy = std::move(tmp.vrcholy);
    indicie = std::move(tmp.indicie);
    rotace = tmp.rotace;

    cstmvtxVrcholy =  tmp.cstmvtxVrcholy;
    paIndicie = tmp.paIndicie;
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
    tmp.paIndicie = nullptr;
    ++pocetInstanciStromu;
}

Tree::Tree(DruhStromu& _druhStromu, D3DXMATRIX& pocatek, LPDIRECT3DDEVICE9* _pzarizeni) : druhStromu(_druhStromu), pzarizeni(*_pzarizeni)
{
    zmenaRotace = 0.f;
    cstmvtxVrcholy = nullptr;
    vlastnostiVetvi = nullptr;
    bufferVrcholu = nullptr;
    bufferIndicii = nullptr;
    paIndicie = nullptr;
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
    paIndicie = nullptr;
    btriangleList = true;
    D3DXMatrixRotationX(&maticeRotaceStromuX, -3.14159265358979323846/2);     // Otoci strom o -Pi kolem x
    D3DXMatrixScaling(&maticeSkalovani, 0.5f, 0.5f, 0.5f );                 // Zmensi strom na 1/2
    matice = pocatek;
    barvaStromu = D3DXVECTOR4(0.f,0.f,0.f,0.f);
    material = *(new D3DMATERIAL9());
    D3DXCOLOR b = (D3DXCOLOR) druhStromu.barva;
    material.Diffuse = material.Ambient = (D3DCOLORVALUE)b;

    bVlnit = true;
    citacVrcholu = 0;
    citacIndicii = 0;
    citacClanku = 0;
    citacElementu = 0;
    citacVetvi = 0;
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
//        if(!alokujMistoProVrcholyAindicie()) throw StromVyjimka("Nelze vyhradit dostatek mista pro vrcholy!");
#ifdef TREEVERBOSE
        std::cout << "Ok\n";
#endif
#ifdef TREEVERBOSE
        std::cout << "Generuji vrcholy...";
#endif // defined
        pocetClanku = spoctiClanky();
//        pocetVetvi = 4;
        if(!generujVykreslovaciDataVetvi()) throw StromVyjimka("Nepodarilo se vygenerovat vrcholy vetvi.");      // zavola generujVetev->generujClanek
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
        if(!uzamkniPoleDoBuffru()) throw StromVyjimka("Nepodarilo se uzamknout vrcholy do buffru.");
        if(!zkopirujVrcholyDoBuffru(vrcholy)) throw StromVyjimka("Nepodarilo se zkopirovat vrcholy do statickeho pole a buffru.");
        if(!zkopirujIndicieDoBuffru(indicie)) throw StromVyjimka("Nepodarilo se zkopirovat indicie do statickeho pole a buffru.");
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
    paIndicie = tmp.paIndicie;
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
    tmp.paIndicie = nullptr;

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
    } else {
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
    if(paIndicie != nullptr) {
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
    } else {}
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
        vlastnostiVetvi[x].rozliseniE = druhStromu.rozliseniE;
        vlastnostiVetvi[x].rozliseniV = druhStromu.rozliseniV;
        vlastnostiVetvi[x].citacClankuVetve = 0;
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

VlastnostiVetve Tree::generujVlastnostiVetve( const VlastnostiVetve& parent, int strana, DruhStromu& _tType)
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
        pVs.rodicka = (VlastnostiVetve*)&parent;


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

/** \brief Spocita clanky, elementy, vrcholy, indicie.
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
    return vrcholy.size();
//    if ( druhStromu.element == usecka ) {
//        return pocetVetvi;//+2;
//    } else
//        return iVx;
#else
    return iVx;
#endif // PROBLEMATICAL
}

int Tree::spoctiClanky()
{
    /** \brief kazda vetev jinak
     *
     * \param
     * \param
     * \return
     *
     */

    return (1*druhStromu.rozliseniV);
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
        int pocet = 1;
//        pocetClanku = pocet*druhStromu.rozliseniV;
        pocetElementu = pocetClanku*druhStromu.rozliseniE*2+0;
//        pocetElementu = 2;
//        pocetVrcholu = (pocetClanku+1*pocet)*druhStromu.rozliseniE;
//        pocetIndicii = (pocetElementu + 2*pocetClanku);
        pocetIndicii = indicie.size();
//        pocetVrcholu = vrcholy.size();
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
//        paIndicie[citacIndicii] = pocatecniIndex;
        indicie.push_back(pocatecniIndex);
        ++citacIndicii;
        break;
    }
    case testUsecka: {
        paIndicie[0] = 0;
        paIndicie[1] = 1;

        paIndicie[2] = 1;
        paIndicie[3] = 2;

        paIndicie[4] = 1;
        paIndicie[5] = 3;
        break;
    }
    case usecka: {
        paIndicie[citacIndicii] = pocatecniIndex;
        ++citacIndicii;
        paIndicie[citacIndicii] = pocatecniIndex+1;
        ++citacIndicii;
        break;
    }
    case kuzel: {
        break;
    }
    default: {
        break;
    }
    }
}

void Tree::generujIndexyElementu(Element e, int pocatecniIndex, int koncovyIndex)
{
    switch ( e ) {
    case testUsecka: {
        paIndicie[0] = 0;
        paIndicie[1] = 1;

        paIndicie[2] = 1;
        paIndicie[3] = 2;

        paIndicie[4] = 1;
        paIndicie[5] = 3;
        break;
    }
    case testValec:
    case usecka: {
//        paIndicie[citacIndicii] = pocatecniIndex;
        indicie.push_back(pocatecniIndex);
        ++citacIndicii;
//        paIndicie[citacIndicii] = koncovyIndex;
        indicie.push_back(koncovyIndex);
        ++citacIndicii;
        citacElementu+=2;
        break;
    }
    case kuzel: {
        break;
    }
    default: {
        break;
    }
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
    D3DXVECTOR3 b0 = {vrcholy[a].x, vrcholy[a].y, vrcholy[a].z};
    D3DXVECTOR3 b1 = {vrcholy[b].x, vrcholy[b].y, vrcholy[b].z};
    D3DXVECTOR3 b2 = {vrcholy[c].x, vrcholy[c].y, vrcholy[c].z};
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
    int pocetVrcholuNaVetev = (druhStromu.rozliseniV+1)*druhStromu.rozliseniE;
    int pocetVetviPredemnou = a/pocetVrcholuNaVetev;
    int odectu = pocetVetviPredemnou*pocetVrcholuNaVetev;
    int testuju = a-odectu;
//    std::cout << "a "<<a << std::endl;
//    std::cout << "testuju "<<testuju << std::endl;
//    std::cout << "Posledni vrcholy vetve vetsirovno: "<<(druhStromu.rozliseniV)*druhStromu.rozliseniE << std::endl;
//    std::cout << "Posledni vrcholy vetve mensirovno: "<<(druhStromu.rozliseniV)*druhStromu.rozliseniE+(druhStromu.rozliseniE-1) << std::endl;
    bool bposledniVrcholyVetve = false;
    if(testuju >= (druhStromu.rozliseniV)*druhStromu.rozliseniE &&
        testuju <= (druhStromu.rozliseniV)*druhStromu.rozliseniE+(druhStromu.rozliseniE-1))
            bposledniVrcholyVetve = true;
//    std::cout << "bool "<<bposledniVrcholyVetve << std::endl;

    int b = a+druhStromu.rozliseniE, c = a+1;
    D3DXVECTOR3 b0 = {vrcholy[a].x, vrcholy[a].y, vrcholy[a].z};
    D3DXVECTOR3 konec, n0, n1, vyslednice;
    pocetVrcholu = vrcholy.size();
    if( (b < pocetVrcholu && c < pocetVrcholu) && (!bposledniVrcholyVetve) ) {     // spodni rada
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

        kolmice.emplace_back( matice, b0, konec, zluta, &pzarizeni, zmenaRotace );
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
    if(vrcholy[pozice].kolmice == D3DXVECTOR3(0.,0.,0.))
        vrcholy[pozice].kolmice = kolmice;
    else
        std::cout << "Normala uz existuje!" << std::endl;
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
    case kuzel: {
        break;
    }
    default: {
        break;
    }
    }
}


void Tree::generujVrcholyIndicieKruhu(const D3DXVECTOR3& pocatek)
{
    float Dens = 2.* PI/druhStromu.rozliseniE;
    float OrigoX=0., OrigoY=0.,
          posX=0., posY=0., posZ=0.,
          posunX=pocatek.x, posunY=pocatek.y, posunZ=0.;
    float Zkoord = 0.;
    float sklonz = PI/2;
    float sklony = 0.;
    float rMod = sin(citacClanku*PI/180)*5000. +100000.;
    float r = rMod;
    posunZ = citacClanku*(1000000./druhStromu.rozliseniV) + pocatek.z;
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
//        cstmvtxVrcholy[citacVrcholu].x = posX;
//        cstmvtxVrcholy[citacVrcholu].y = posY;
//        cstmvtxVrcholy[citacVrcholu].z = posZ;
//        cstmvtxVrcholy[citacVrcholu].color = druhStromu.barva;
        VrcholBK tmp = {posX, posY, posZ, D3DXVECTOR3(0., 0., 0.), druhStromu.barva};
        vrcholy.push_back(tmp);
//        vrcholy.emplace_back(posX, posY, posZ, D3DXVECTOR3(0., 0., 0.), druhStromu.barva);
//        if(citacVrcholu+druhStromu.rozliseniE == (pocetClanku+1)*druhStromu.rozliseniE) {}
//        else if(citacVrcholu+druhStromu.rozliseniE < (pocetClanku+1)*druhStromu.rozliseniE)
        generujIndexyElementu(testValec, citacVrcholu, citacVrcholu + druhStromu.rozliseniE);
        citacVrcholu++;
    }
    citacClanku++;
}

void Tree::generujVrcholyKruhu(const D3DXVECTOR3& pocatek)
{
    float Dens = 2.* PI/druhStromu.rozliseniE;
    float OrigoX=0., OrigoY=0.,
          posX=0., posY=0., posZ=0.,
          posunX=pocatek.x, posunY=pocatek.y, posunZ=0.;
    float Zkoord = 0.;
    float sklonz = PI/2;
    float sklony = 0.;
    float rMod = sin(citacClanku*5*PI/180)*5000. +10000.;
    float r = rMod;
    posunZ = /*citacClanku*(1000000./druhStromu.rozliseniV)*/ + pocatek.z;
    if(citacVrcholu>=druhStromu.rozliseniE) {
//            r -= citacClanku*10000.;
    }
    float radiusZ = 50000.;
    for (float a = 2*PI; a >= Dens; a-=Dens) {																			//kruh
        r = rMod+sin(a*7)*500.;
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
//        cstmvtxVrcholy[citacVrcholu].x = posX;
//        cstmvtxVrcholy[citacVrcholu].y = posY;
//        cstmvtxVrcholy[citacVrcholu].z = posZ;
//        cstmvtxVrcholy[citacVrcholu].color = druhStromu.barva;
        VrcholBK tmp = {posX, posY, posZ, D3DXVECTOR3(0., 0., 0.), druhStromu.barva};
        vrcholy.push_back(tmp);
        citacVrcholu++;
    }
    citacClanku++;
}

void Tree::generujVrcholyKruhu(const D3DXVECTOR3& pocatek, VlastnostiVetve& pV)
{
    float Dens = 2.* PI/druhStromu.rozliseniE;
    float OrigoX=0., OrigoY=0.,
          posX=0., posY=0., posZ=0.,
          posunX=pocatek.x, posunY=pocatek.y, posunZ=0.;
    float Zkoord = 0.;
    float sklonz = PI/2;
    float sklony = 0.;
    float rMod = sin(pV.citacClankuVetve*5*PI/180)*1. +10000.;//65000
    float r = rMod;
    posunZ = /*citacClanku*(1000000./druhStromu.rozliseniV)*/ + pocatek.z;
    if(citacVrcholu>=druhStromu.rozliseniE) {
//            r -= citacClanku*10000.;
    }
    float radiusZ = 50000.;
    for (float a = 2*PI; a >= Dens; a-=Dens) {																			//kruh
        r = rMod+sin(a*4)*500.;
        OrigoX=cos((float)a-sklonz) * r + radiusZ + sin(pV.citacClankuVetve*5*PI/180)*4700.;
        OrigoY=cos(sklony)* (sin((float)a-sklonz)) * r + sin(pV.citacClankuVetve*5*PI/180)*2700.;
        if(OrigoX==0) {
            posX=0.;
            posY=0.;
        } else {
            posX=cos(atan(OrigoY/OrigoX)+sklonz)*(OrigoX/cos(atan(OrigoY/OrigoX))) + posunX;
            posY=sin(atan(OrigoY/OrigoX)+sklonz)*(OrigoX/cos(atan(OrigoY/OrigoX)))+ posunY;
        }
        posZ=Zkoord + sin(sklony)*(sin((float)a-sklonz)) * r + posunZ;
//        cstmvtxVrcholy[citacVrcholu].x = posX;
//        cstmvtxVrcholy[citacVrcholu].y = posY;
//        cstmvtxVrcholy[citacVrcholu].z = posZ;
//        cstmvtxVrcholy[citacVrcholu].color = druhStromu.barva;
        VrcholBK tmp = {posX, posY, posZ, D3DXVECTOR3(0., 0., 0.), druhStromu.barva};
        vrcholy.push_back(tmp);
        citacVrcholu++;
    }
    citacClanku++;
    pV.citacClankuVetve++;
}

void Tree::generujVrcholyKruhu(const D3DXVECTOR3& pocatek, VlastnostiVetve& pV, float r, float radiusZ, float sklony, float sklonz, float Dens)
{
//    float Zkoord = 0.0f;
    float OrigoX=0., OrigoY=0.,
          posX=0., posY=0., posZ=0.,
          posunX=pocatek.x, posunY=pocatek.y, posunZ=0.;
	float iVx = 0;int reality=0;
	iVx=2*PI/Dens;

//	for (float a = 2*PI; a> Dens; a-=Dens)																				//kruh
//	{
//		reality++;
//		OrigoX=cos((float)a-sklonz) * r + radiusZ;
//		OrigoY=cos(sklony)* (sin((float)a-sklonz)) * r;
//		if(OrigoX==0)
//		{
////			Barva.x=0.f;//MANUAL OVERRIDE but this never happens
////			Barva.y=1.f;
////			Barva.z=0.f;
//			posX=posunX;
//			posY=posunY;
//		}
//		else{
//			posX=cos(atan(OrigoY/OrigoX)+sklonz)*(OrigoX/cos(atan(OrigoY/OrigoX))) + pocatek.x;
//			posY=sin(atan(OrigoY/OrigoX)+sklonz)*(OrigoX/cos(atan(OrigoY/OrigoX)))+ pocatek.y;
//		}
//		posZ=Zkoord + sin(sklony)*(sin((float)a-sklonz)) * r + pocatek.z;
//		vPoradi++;
//	}
    /*float*/ Dens = 2.* PI/druhStromu.rozliseniE;
    float Zkoord = 0.;
//    float sklonz = PI/2;
//    float sklony = 0.;
    float rMod = sin(pV.citacClankuVetve*5*PI/180)*1. +10000.;//65000
    /*float*/ r = rMod+r;
    posunZ = /*citacClanku*(1000000./druhStromu.rozliseniV)*/ + pocatek.z;
    if(citacVrcholu>=druhStromu.rozliseniE) {
//            r -= citacClanku*10000.;
    }
//    float radiusZ = 50000.;
    for (float a = 2*PI; a >= Dens; a-=Dens) {																			//kruh
        r = rMod+sin(a*4)*500.;
        OrigoX=cos((float)a-sklonz) * r + radiusZ + sin(pV.citacClankuVetve*5*PI/180)*4700.;
        OrigoY=cos(sklony)* (sin((float)a-sklonz)) * r + sin(pV.citacClankuVetve*5*PI/180)*2700.;
        if(OrigoX==0.f) {
                std::cout << "nula origoX" << std::endl;
            posX=posunX;
            posY=posunY;
        } else {
            posX=cos(atan(OrigoY/OrigoX)+sklonz)*(OrigoX/cos(atan(OrigoY/OrigoX))) + posunX;
            posY=sin(atan(OrigoY/OrigoX)+sklonz)*(OrigoX/cos(atan(OrigoY/OrigoX)))+ posunY;
        }
        posZ=Zkoord + sin(sklony)*(sin((float)a-sklonz)) * r + posunZ;
//        cstmvtxVrcholy[citacVrcholu].x = posX;
//        cstmvtxVrcholy[citacVrcholu].y = posY;
//        cstmvtxVrcholy[citacVrcholu].z = posZ;
//        cstmvtxVrcholy[citacVrcholu].color = druhStromu.barva;
        VrcholBK tmp = {posX, posY, posZ, D3DXVECTOR3(0., 0., 0.), druhStromu.barva};
        vrcholy.push_back(tmp);
        citacVrcholu++;
    }
    citacClanku++;
    pV.citacClankuVetve++;
}

void Tree::generujIndicieClanku(int cislo)
{
    int zacatek = cislo*druhStromu.rozliseniE;
    for(int i = 0; i < druhStromu.rozliseniE; ++i) {
        generujIndexyElementu(testValec, i+zacatek); //2.1
        generujIndexyElementu(testValec, i+zacatek+(1)*druhStromu.rozliseniE); //2.1
    }
    generujIndexyElementu(testValec, 0+zacatek);//2
    generujIndexyElementu(testValec, 0+zacatek+1*druhStromu.rozliseniE);
}

/** \brief spoji element x s elementem y
 *          cislovani od 0
 * \param
 * \param
 * \return
 *
 */
void Tree::generujIndicieClankuXY(int x, int y)
{
    if(!btriangleList) {
        int zacatek = x*druhStromu.rozliseniE;
        int konec = y*druhStromu.rozliseniE;
        for(int i = 0; i < druhStromu.rozliseniE; ++i) {
            generujIndexyElementu(testValec, i+zacatek); //2.1
            generujIndexyElementu(testValec, i+konec); //2.1
        }
        generujIndexyElementu(testValec, 0+zacatek);//2
        generujIndexyElementu(testValec, 0+konec);
    } else {
        int pocetClankuKIndexovani = 1;
        int zacitOdclanku = x;
        for(int l = zacitOdclanku; l < pocetClankuKIndexovani+zacitOdclanku; ++l) {
            int pocatecniClanek = l;
            int koncovyClanek = y;
            int pocatecniIndexX = (pocatecniClanek)*druhStromu.rozliseniE;
            int pocatecniIndexY = (koncovyClanek-1)*druhStromu.rozliseniE;
            for(int i = pocatecniIndexX, n = pocatecniIndexY; i < pocatecniIndexX+druhStromu.rozliseniE-1; ++i, ++n) {
                generujIndexyElementu(testValec, 0+i, n);
                generujIndexyElementu(testValec, 1+i);

                generujIndexyElementu(testValec, n);
                generujIndexyElementu(testValec, n+1,  1+i);
            }
            int n = pocatecniIndexY+druhStromu.rozliseniE-1;
//        std::cout << "n je : "<<n << std::endl;
            int i = pocatecniIndexX+druhStromu.rozliseniE-1;
            generujIndexyElementu(testValec, 0+i, n);
            generujIndexyElementu(testValec, pocatecniIndexX);

            generujIndexyElementu(testValec, n);
            generujIndexyElementu(testValec, pocatecniIndexY, pocatecniIndexX);
        }
        int konecnyClanek = y;
    }
}

/** \brief spoji kruh x s kruhem y
 *          cislovani od 0
 * \param
 * \param
 * \return
 *
 */
void Tree::generujIndicieKruhuXY(int x, int y)
{
    if(!btriangleList) {
        int zacatek = (x-1)*druhStromu.rozliseniE;
        int konec = (y)*druhStromu.rozliseniE;
        for(int i = 0; i < druhStromu.rozliseniE; ++i) {
            generujIndexyElementu(testValec, i+zacatek); //2.1
            generujIndexyElementu(testValec, i+konec); //2.1
        }
        generujIndexyElementu(testValec, 0+zacatek);//2
        generujIndexyElementu(testValec, 0+konec);
    } else {
        int pocetClankuKIndexovani = 1;
        int zacitOdclanku = x;
        for(int l = zacitOdclanku; l < pocetClankuKIndexovani+zacitOdclanku; ++l) {
            int pocatecniClanek = l-1;
            int koncovyClanek = y;
            int pocatecniIndexX = (pocatecniClanek)*druhStromu.rozliseniE;
            int pocatecniIndexY = (koncovyClanek-1)*druhStromu.rozliseniE;
            for(int i = pocatecniIndexX, n = pocatecniIndexY; i < pocatecniIndexX+druhStromu.rozliseniE-1; ++i, ++n) {
                generujIndexyElementu(testValec, 0+i, n);
                generujIndexyElementu(testValec, 1+i);

                generujIndexyElementu(testValec, n);
                generujIndexyElementu(testValec, n+1,  1+i);
            }
            int n = pocatecniIndexY+druhStromu.rozliseniE-1;
//        std::cout << "n je : "<<n << std::endl;
            int i = pocatecniIndexX+druhStromu.rozliseniE-1;
            generujIndexyElementu(testValec, 0+i, n);
            generujIndexyElementu(testValec, pocatecniIndexX);

            generujIndexyElementu(testValec, n);
            generujIndexyElementu(testValec, pocatecniIndexY, pocatecniIndexX);
        }
        int konecnyClanek = y;
    }
}


/** \brief generuje indicie clanku cislo x, spoji ho s elementem x+preskocit
 *
 * \param
 * \param
 * \return
 *
 */

void Tree::generujIndicieClanku(int cislo, int preskocit)
{
    int zacatek = cislo*druhStromu.rozliseniE;
    for(int i = 0; i < druhStromu.rozliseniE; ++i) {
        generujIndexyElementu(testValec, i+zacatek); //2.1
        generujIndexyElementu(testValec, i+zacatek+(1+preskocit)*druhStromu.rozliseniE); //2.1
    }
    generujIndexyElementu(testValec, 0+zacatek);//2
    generujIndexyElementu(testValec, 0+zacatek+(1+preskocit)*druhStromu.rozliseniE);
}

void Tree::generujVrcholyVetve(const D3DXVECTOR3& pocatek, int kolikClanku)
{
    if(kolikClanku != 0) {
        D3DXVECTOR3 _poc = pocatek;
        generujVrcholyKruhu( _poc );
        _poc.z += 7000.;
        for (int w = 0; w < kolikClanku; ++w) {
            generujVrcholyKruhu( _poc );
            _poc.z += 7000.;
        }
        ++citacVetvi;
    }
}

void Tree::generujVrcholyVetve(const D3DXVECTOR3& pocatek, int kolikClanku, VlastnostiVetve& pV)
{

	/*float ample;//, per; //radius krouceniaa
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
	else
	{
	}
	for (float x = 0.f; x+1.f< pV.d/pV.m; x+=1.f)
	{
		//mezera = (2*PI*TemppV.r.r)/90; //360...obvod 1 stupne..
		TempRust.r += (pV.rT.r -pV.r.r)/floor(pV.d/pV.m);
		TempRust.rotace += (pV.rT.rotace-pV.r.rotace)/floor(pV.d/pV.m);
		TempRust.sklon += (pV.rT.sklon - pV.r.sklon)/floor(pV.d/pV.m);

		//TempRust.sklon = PI/4+sin(3*OrigoZ*PI/180)/10;
		//TempRust.rotace = PI/4;
		sklony =TempRust.sklon-PI/2;
		sklonz =  -TempRust.rotace;

		//sklony = PI/2 +TempRust.sklon;
		//sklonz = PI/2 -TempRust.rotace;
		OrigoZ+=pV.m;

		//OrigoX = (2*xAmp+1)+cos(PI/20*(int)OrigoZ+PI/80)*xAmp;  // to je ten problem>kedysin nabude0tak se nasledujici vyrazy z nejakeho duvodu nevyhodnoti
		//OrigoY = (2*yAmp+1)+sin(PI/20*(int)OrigoZ)*yAmp;

		OrigoX = bVlnit?((2*xAmp+1)+cos(PI/20*(int)OrigoZ+PI/80)*xAmp):0;
		OrigoY = bVlnit?((2*yAmp+1)+sin(PI/20*(int)OrigoZ)*yAmp):0;
		//Barva.x=abs((OrigoX-(2*xAmp+1))/xAmp)+1-abs((OrigoX-(2*xAmp+1))/xAmp);//MANUAL OVERRIDE
		//Barva.y=abs((OrigoX-(2*xAmp+1))/xAmp);
		//Barva.z=0.f;

			afterY=cos(TempRust.sklon)*OrigoZ;
			posunZ=pV.x.z+sin(TempRust.sklon)*OrigoZ;
			posunY=pV.x.y+cos(TempRust.rotace)*afterY;
			posunX=pV.x.x+sin(TempRust.rotace)*afterY;
			//Barva.x =0.f;//MANUAL OVERRIDE
			//Barva.y=1.f;
			//Barva.z=0.f;


		countEm=vPoradi;

		RostClanek(TempRust.r, radiusZ, sklony, sklonz, pV.de, posunX, posunY, posunZ);

	afterY=cos(TempRust.sklon)*OrigoZ;
	posunZ=pV.x.z+sin(TempRust.sklon)*OrigoZ;
	posunY=pV.x.y+cos(TempRust.rotace)*afterY;
	posunX=pV.x.x+sin(TempRust.rotace)*afterY;
	pV.x.x = posunX;
	pV.x.y = posunY;
	pV.x.z = posunZ;
	}*/


//    if(pV.k)
//        pV.rT.r = 0.01f;
    D3DXVECTOR3 _poc = pocatek;
    pV.citacClankuVetve = pV.rodicka->citacClankuVetve;
    float ample;//, per; //radius krouceniaa
    objRust TempRust = pV.r;
    float xAmp=1, yAmp=0;
    float Dens = 2.* PI/druhStromu.rozliseniE;
    float OrigoX=0., OrigoY=0., OrigoZ=0., posX=0., posY=0., posZ=0., posunX=0., posunY=0., afterY = 0.;
    float sklonz = PI/2;
    float sklony = 0.;
    float posunZ = 0.;
    float rMod = sin(citacClanku*PI/180)*5000. + pV.rodicka->r.r;
    float r = rMod;
    posunZ = citacClanku*(1000000./druhStromu.rozliseniV);
    float radiusZ = 0.f;
    if ( citacClanku != 0){
        pV.r = pV.rodicka->rT;
//        r = TempRust.r;
//        sklony = TempRust.sklon;
//        sklonz = TempRust.rotace;
    }
        _poc = pV./*rodicka->*/x;
        TempRust = pV.r;
//    generujVrcholyKruhu( _poc, pV, r, radiusZ, sklony, sklonz, Dens );
    for (float x = 0.f; x <= kolikClanku; x += 1.f) {
        TempRust.r += (pV.rT.r - pV.r.r)/kolikClanku;
        TempRust.rotace += (pV.rT.rotace - pV.r.rotace)/kolikClanku;
        TempRust.sklon += (pV.rT.sklon - pV.r.sklon)/kolikClanku;
        sklony = TempRust.sklon-PI/2;
//        sklonz = -TempRust.rotace;
        sklonz = -TempRust.rotace;
        OrigoZ+=pV.m;
        OrigoX = bVlnit?((2*xAmp+1)+cos(PI/20*(int)OrigoZ+PI/80)*xAmp):0;
        OrigoY = bVlnit?((2*yAmp+1)+sin(PI/20*(int)OrigoZ)*yAmp):0;
        afterY=cos(TempRust.sklon)*OrigoZ;
        posunZ=pV.x.z+sin(TempRust.sklon)*OrigoZ;
        posunY=pV.x.y+cos(TempRust.rotace)*afterY;
        posunX=pV.x.x+sin(TempRust.rotace)*afterY;
        countEm=citacVrcholu;
        _poc = {posunX, posunY, posunZ};
        generujVrcholyKruhu( _poc, pV, r, radiusZ, sklony, sklonz, Dens );
    }
    ++citacVetvi;
}

int Tree::generujIndicieVetve(int cislo, int kolikClanku)
{
//    std::cout << "cislo: "<< cislo << std::endl;
    int pocetClankuKIndexovani = kolikClanku;
    int pocetClankuVetve = druhStromu.rozliseniV;
    int pocatecniKruh = (cislo-1)*(pocetClankuVetve+1)+1;
//    std::cout << "kruh: "<< pocatecniKruh << std::endl;
    for (int i = pocatecniKruh; i < kolikClanku+pocatecniKruh; ++i) {
        generujIndicieKruhuXY(i,i+1);
    }
    int konecnyClanek = 0;
    return konecnyClanek;
}


/** \brief odpoji celou vetev az k rozdvojeni, (vytvori postupne degenerovane trojuhelniky. 99, 66, atd)
 *
 * \param
 * \param
 * \return vraci cislo rozdvojovaciho clanku
 *
 */

int Tree::generujIndicieOdpojeniClanku(int x, int pocetClankuVetve, bool suda)
{
    int pocetClankuLicheVetve = pocetClankuVetve;           // Risk of potencial errors
    int zacatek = x*druhStromu.rozliseniE;
    int indicie;
    for (int i = 0; i < pocetClankuVetve-suda?1:0; ++i) {
        indicie = zacatek-i*(druhStromu.rozliseniE);
        generujIndexyElementu(testValec, indicie, indicie);
    }
    if ( suda ) {
        indicie = (x-pocetClankuVetve-pocetClankuLicheVetve+1)*druhStromu.rozliseniE;
        generujIndexyElementu(testValec, indicie, indicie);
    }
    return (x-pocetClankuVetve);
}

/** \brief Indicie rozdeleni je treba vytvorit po indiciich prvni vetve, dalsi vetvi je treba rict, kde navazat
 *
 * \param
 * \param
 * \return
 *
 */

void Tree::generujIndicieRozdeleni()
{
    // ↓
    int citac = 0;
    generujIndexyElementu(testValec, 0+(pocetClanku)*druhStromu.rozliseniE);//1 konec-zacate
    generujIndexyElementu(testValec, 0+(pocetClanku+1)*druhStromu.rozliseniE);//1konec-zacate

    for (int u = 0; u < pocetClanku - 1; ++u)
        generujIndicieClanku(pocetClanku+(1+u)); //1.vse

//    generujIndicieClanku(pocetClanku+(1)); //1.1
//    generujIndicieClanku(pocetClanku+(2)); //1.2
    // to pujde pryc ↑, vsimni si, ze jeden clanek je jiz vygenerovany, neni to spatne pro prehlednost?

    generujIndicieOdpojeniClanku(pocetClanku+(pocetClanku-1), pocetClanku, false); // rozdel

    // ↓
    int zacatek = 0;
    int cisloElementuRozdvojeni = pocetClanku+zacatek;

    generujIndicieClanku(cisloElementuRozdvojeni, pocetClanku); // 2 prvni clanek musi spojit element rozdvojeni a prvni element druhe vetve,

    int cisloNavazujicihoClanku = cisloElementuRozdvojeni + pocetClanku + 1;
    for (int u = 0; u < pocetClanku - 1; ++u)
        generujIndicieClanku(cisloNavazujicihoClanku+(u)); //2.vse
//    generujIndicieClanku(cisloNavazujicihoClanku);  //2.1
//    generujIndicieClanku(cisloNavazujicihoClanku + 1);  //2.2
    // ↑ pujde pryc taky
}

/** \brief Generuje vrcholy a indicie vetve, Musi znat pocet clanku dopredu.
 *
 * \param pocatek
 * \param
 * \return
 *
 */

void Tree::generujVrcholyIndicieVetve(const D3DXVECTOR3& _pocatek, bool zakoncit, bool navazat, int pocatecniElement=0, bool suda=0, int kolikPreskocit=0)
{
    ///* Vzdy u liche vetve zavolam generuj indicie odpojeni a u sude generuj indicie navazani */
    int citac=0;
    if( !navazat ) {
//        generujVrcholyIndicieKruhu( _pocatek );
        generujVrcholyKruhu( _pocatek );
        generujIndicieClanku(citacClanku-1);
    } else if( navazat && !suda )
        generujIndicieClanku(citacClanku-1); // prida zavereecne
    else if ( navazat && suda ) {
        int zacatek = pocatecniElement;
        int cisloElementuRozdvojeni = pocatecniElement+1;
        generujVrcholyKruhu(_pocatek);
        generujIndicieClanku(cisloElementuRozdvojeni, pocetClanku*kolikPreskocit); // 2 prvni clanek musi spojit element rozdvojeni a prvni element druhe vetve,

        int cisloNavazujicihoClanku = cisloElementuRozdvojeni + pocetClanku*kolikPreskocit + 1;
        for (int u = 0; u < pocetClanku - 1; ++u) {
            generujIndicieClanku(cisloNavazujicihoClanku+(u)); //2.vse
            generujVrcholyKruhu(_pocatek);
        }
    }

    if(!suda) {
        citac+=2*druhStromu.rozliseniE;//0
        for(int i = (!suda)?0:1; i < pocetClanku; ++i) {
            citac+=2;//0konec-zacate
            if(zakoncit && i == pocetClanku-1)
                generujVrcholyKruhu( _pocatek );
            else {
                generujVrcholyKruhu( _pocatek );
                generujIndicieClanku(citacClanku-1);

//            generujVrcholyIndicieKruhu( _pocatek );
                ///*koncove spojovaci indexy*/
//        generujIndexyElementu(testValec, pocatecniElement*druhStromu.rozliseniE+i*druhStromu.rozliseniE); //0konec-zacate
//        generujIndexyElementu(testValec, pocatecniElement*druhStromu.rozliseniE+(i+1)*druhStromu.rozliseniE); //0konec-zacate
            }
            citac+=2*druhStromu.rozliseniE;//1
        }
        if( !zakoncit ) {
            D3DXVECTOR3 pocatek = {0., 00000., 0000.};
            generujIndicieRozdeleni();

            for (int o = 1; o < pocetClanku+1; ++o)
                generujVrcholyKruhu( -o*_pocatek);
//        pocatek = {10000., 100000., 10000.};
//        generujVrcholyKruhu( -_pocatek ); //....1
//        pocatek = {10000., 100000., 40000.};
//        generujVrcholyKruhu( -_pocatek ); //1.1
//        generujVrcholyKruhu( -2*_pocatek ); //1.2

            pocatek = {10000., 100000., 100000.};
            for (int o = 1; o < pocetClanku+1; ++o)
                generujVrcholyKruhu( o*pocatek);
//        generujVrcholyKruhu( 3*pocatek ); //2
//        pocatek = {10000., 100000., 100000.};
//        generujVrcholyKruhu( 3*pocatek ); //2.1
//        generujVrcholyKruhu( 4*pocatek ); //2.2
        }
//    if( navazat && !suda )
//        generujIndicieOdpojeniClanku(citacClanku-2, pocetClanku); // rozdel
    }
}


/** \brief Vytvori vrcholy, indicie a kolmice podle parametru vetve
 *
 * \param
 * \param
 * \return
 *
 */

bool Tree::generujElementyVetve( VlastnostiVetve& pV)
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
///* Triangle strip */
        if(!btriangleList) {
            D3DXVECTOR3 pocatek = {10000., 100000., 0.};
            generujVrcholyIndicieVetve( pocatek, true, false, 0 , false );
            std::cout << "\ncitac clanku> " << citacClanku << std::endl;
            generujVrcholyIndicieVetve( pocatek, true, true/*, citacClanku-1*/, false );
            pocatek = {10000., 900000., 80000.};
            generujVrcholyIndicieVetve( pocatek, true, true/*, citacClanku-1*/, false );
            int cisloClankuRozdvojeni = generujIndicieOdpojeniClanku(citacClanku-2, 1*pocetClanku, false); // rozdel
            generujVrcholyIndicieVetve( -1*pocatek, true, true, cisloClankuRozdvojeni, true, 1);
//
            cisloClankuRozdvojeni = generujIndicieOdpojeniClanku(citacClanku-2, pocetClanku, true); // rozdel
            pocatek = {100000., 600000., 00.};
            generujVrcholyKruhu( pocatek );
            std::cout << "\ncislo clanku rozdvojnei: "<< cisloClankuRozdvojeni << std::endl;
            generujIndicieClankuXY(cisloClankuRozdvojeni-pocetClanku, citacClanku-1);

            pocatek = {300000., 900000., 80000.};
            generujVrcholyIndicieVetve( pocatek, true, true/*, citacClanku-1*/, false );
            cisloClankuRozdvojeni = generujIndicieOdpojeniClanku(citacClanku-2, 1*pocetClanku, false); // rozdel
            pocatek.x = -pocatek.x;
            generujVrcholyIndicieVetve( pocatek, true, true, cisloClankuRozdvojeni, true, 1);

//        generujVrcholyIndicieVetve( pocatek, true, true, cisloClankuRozdvojeni-1, true, 3);
//        generujVrcholyIndicieVetve( -2*pocatek, true, true, cisloClankuRozdvojeni, true, 3);
//        generujVrcholyIndicieVetve( pocatek, true, true, citacClanku-1, false );
//        cisloClankuRozdvojeni = generujIndicieOdpojeniClanku(citacClanku-2, 1*pocetClanku, false);
//        generujVrcholyIndicieVetve( -2*pocatek, true, true, cisloClankuRozdvojeni, true, 1);
        } else
        {
///* Triangle list */
            D3DXVECTOR3 pocatek = {10000., 100000., 0.};
//            float koeficientBarvy = 9.0f;
            int soucasnyKruh;
            int soucasnyClanek = citacClanku-1-1*(citacVetvi-1);
//            int budouciClanek = soucasnyClanek+1;
//            TempRust.r += (pV.rT.r -pV.r.r)/floor(pV.d/pV.m);
//            TempRust.rotace  += (pV.rT.rotace-pV.r.rotace)/floor(pV.d/pV.m);
//            TempRust.sklon += (pV.rT.sklon - pV.r.sklon)/floor(pV.d/pV.m);
//            sklony = TempRust.sklon-PI/2;
//            sklonz = -TempRust.rotace;
//            OrigoZ += pV.m;
//            OrigoX = bVlnit?((2*xAmp+1)+cos(PI/20*(int)OrigoZ+PI/80)*xAmp):0;
//            OrigoY = bVlnit?((2*yAmp+1)+sin(PI/20*(int)OrigoZ)*yAmp):0;
//            afterY = cos(TempRust.sklon)*OrigoZ;
//            posunZ = pV.x.z;
//            posunY = pV.x.y;
//            posunX = pV.x.x;
//            pocatek = {posunX, posunY, posunZ};
            if ( citacClanku != 0/* pV.rodicka->posledniVrcholPredchoziVetve != 0*/) {
                generujIndicieKruhuXY(pV.rodicka->posledniVrcholPredchoziVetve, citacClanku+1); // beru jako posledni clanek rodicky
            }
            soucasnyClanek = citacClanku+1-1*(citacVetvi-1);
            generujVrcholyVetve( pocatek, druhStromu.rozliseniV, pV );      // pridava dva clanky 3 kruhy
            generujIndicieVetve( citacVetvi, druhStromu.rozliseniV );
            soucasnyKruh = citacClanku;//-prazdny clanek  na pomezi
            pV.posledniVrcholPredchoziVetve = soucasnyKruh;
        }
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
    default: {
        break;
    }
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
    for (int i = 0; i < vrcholy.size(); ++i)
        pridejNormaluVrcholu(i, spocitejNormaluVrcholu(i));
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
//    cstmvtxVrcholy[0].color = D3DCOLOR_XRGB(255,0,0);
//    cstmvtxVrcholy[pocetVrcholu-1].color = D3DCOLOR_XRGB(255,0,0);
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
//        std::cout << "ZACINAM KRSLIT" << std::endl;
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
        pzarizeni->DrawIndexedPrimitive( btriangleList?D3DPT_TRIANGLELIST:D3DPT_TRIANGLESTRIP, // PrimitiveType
                                         0,                  // BaseVertexIndex
                                         0,                  // MinIndex
                                         pocetVrcholu,                  // NumVertices
                                         0,                  // StartIndex
                                         btriangleList?(indicie.size()/3):(indicie.size()/2-1)*2/*pocetElementu+2*(pocetClanku-1)+6+4*//*(nulovy obsah mezi clanky, napr03a36=033,363)*//*+4*(pocetClanku-1)*/ );                // PrimitiveCount
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
            if( FAILED( (*bufferIndicii)->Lock(0, 0, ( void** )&paIndicie, 0) ) ) {
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


bool Tree::zkopirujVrcholyDoBuffru(const std::vector<VrcholBK>& _vrcholy)
{
    bool vysledek = true;

//    cstmvtxVrcholy = new VrcholBK[_vrcholy.size()];
    for (int i = 0; i < _vrcholy.size(); ++i) {
        cstmvtxVrcholy[i] = _vrcholy[i];
    }

    return vysledek;
}

bool Tree::zkopirujIndicieDoBuffru(const std::vector<long>& _indicie)
{
    bool vysledek = true;

//    paIndicie = new long[_indicie.size()];
    for (int i = 0; i < _indicie.size(); ++i) {
        paIndicie[i] = _indicie[i];
    }

#ifdef VYTISKNI_INDICIE
    /** \brief vytiskne indicie
     *
     * \param
     * \param
     * \return
     *
     */
    int pocetIndiciiNaClanek;
    switch (druhStromu.element) {
    case testValec: {
        pocetIndiciiNaClanek = /*pocetClanku**/(druhStromu.rozliseniE*2 + 2);
        iKonzole.vytiskniIndicie((const int*)paIndicie, citacIndicii, pocetIndiciiNaClanek, btriangleList);
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
#endif // VYTISKNI_INDICIE
    return vysledek;
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
            paIndicie = new long[pocetElementu*2];
            break;
        case kuzel:
            paIndicie = new long[pocetElementu*3];
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

Vetev::Vetev()
{

}

Vetev::~Vetev()
{

}

void Tree::testVykresli() const
{

}


}
