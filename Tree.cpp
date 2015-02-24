#include "Tree.hpp"
namespace t
{
#define PROBLEMATICAL


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

Tree::Tree(Tree&& tmp) {
    // move ctor, constructs itself with the temporary
#ifdef TREEVERBOSE
    std::cout << "Calling trees move ctor" << std::endl;
#endif // defined
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

//    druhStromu.urovenRozvetveni = tmp.druhStromu.urovenRozvetveni;
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
    ++pocetInstanciStromu;
}

Tree& Tree::operator=(Tree&& tmp)       // move assignment
{
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

//    druhStromu.urovenRozvetveni = tmp.druhStromu.urovenRozvetveni;
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

//Tree::Tree(DruhStromu _druhStromu, D3DXMATRIX& pocatek, LPDIRECT3DDEVICE9& _pzarizeni) : druhStromu(_druhStromu), pzarizeni(_pzarizeni)
//{
//    D3DXMatrixRotationX(&maticeRotaceSveta, -3.14159265358979323846/2);     // Otoci strom o -Pi
//    D3DXMatrixScaling(&maticeSkalovani, 0.5f, 0.5f, 0.5f );                 // Zmensi strom na 1/2
//    matice = pocatek * maticeSkalovani * maticeRotaceSveta;
////matice = pocatek;
//
//    Barva = D3DXVECTOR4(0.f,0.f,0.f,0.f);
//    bVlnit = true;
//    vPoradi = 0;
//    per = 0.f;
//    gonx = 0.f;
//    sum = 0;
//    countEm = 0;
//    druhStromu.urovenRozvetveni = iPatra;
//    try {
//        generujKmen();  // nastavi barvu stromu
//        std::cout << "Generuji vlastnosti vetvi..." << std::endl;
//        if(!generujVlastnostiVetvi()) throw 0;   // nastavi take pocet vetvi
//        pocetVrcholu = spoctiVertexy();
////        std::cout << "Pocet vrcholu bude: " << pocetVrcholu << std::endl;
//        std::cout << "Pocet vrcholu bude: " << pocetVrcholu << std::endl;
////        std::cout << "Generuji vrcholy stromu..." << std::endl;
//        std::cout << "Vkladam vrcholy do buffru..." << std::endl;
////        if(!uzamkniVrcholyProUtvareni()) throw StromVyjimka("Nepodarilo se pridat vrcholy do buffru.");
//        std::cout << "///// RefCTOR!!!Generuji vrcholy" << std::endl;
////        if(!generujVrcholyVetvi()) throw StromVyjimka("Nepodarilo se vygenerovat vrcholy vetvi.");      // zavola generujVetev->generujClanek
////        if(!odemkniVrcholyProCteni()) throw StromVyjimka("nepodarilo se odemknout vrcholy pro cteni.");
//    } catch (std::exception& e) {
//        std::cout << "Standard exception: " << e.what() << std::endl;
//    }
//    ++pocetInstanciStromu;
//}

Tree::Tree(DruhStromu& _druhStromu, D3DXMATRIX& pocatek, LPDIRECT3DDEVICE9* _pzarizeni) : druhStromu(_druhStromu), pzarizeni(*_pzarizeni)
{
    std::cout << "Using old CTOR" << std::endl;
    cstmvtxVrcholy = nullptr;
    vlastnostiVetvi = nullptr;
    bufferVrcholu = nullptr;
    D3DXMatrixRotationX(&maticeRotaceStromuX, -3.14159265358979323846/2);     // Otoci strom o -Pi kolem x
    D3DXMatrixScaling(&maticeSkalovani, 0.5f, 0.5f, 0.5f );                 // Zmensi strom na 1/2
//    matice = pocatek * maticeSkalovani * maticeRotaceSveta;
    matice = pocatek;
    barvaStromu = D3DXVECTOR4(0.f,0.f,0.f,0.f);
    bVlnit = true;
    citacVrcholu = 0;
    per = 0.f;
    gonx = 0.f;
    sum = 0;
    countEm = 0;
//    druhStromu.urovenRozvetveni = iPatra;
    try {
        generujKmen();  // nastavi barvu stromu
#ifdef TREEVERBOSE
        std::cout << "\nGeneruji vlastnosti vetvi...";
#endif // defined
        if(!generujVlastnostiVetvi()) throw StromVyjimka("Nepodarilo se vygenerovat vlastnosti vetvi.");   // nastavi take pocet vetvi
        pocetVrcholu = spoctiVrcholy();
#ifdef TREEVERBOSE
        std::cout << "Ok\n";
        std::cout << "Pocet vrcholu bude: " << pocetVrcholu << std::endl;
//        std::cout << "Generuji vrcholy stromu..." << std::endl;
        std::cout << "Vyhrazuji misto pro vrcholy...";
#endif // defined
        if(!alokujMistoProVrcholyAindicie()) throw StromVyjimka("Nelze vyhradit dostatek mista pro vrcholy!");
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
//        std::cout << "Ok\n";
        std::cout << "Strom uspesne vygenerovan a pripraven ke kresleni.\n" << std::endl;
//        std::cout << "Vytvarim vertex buffer stromu..." << std::endl;
//        vytvorBuffer();
//        std::cout << "Nahodny vrchol c. 7 pred prirazeni vrcholu do buffru barva: " << cstmvtxVrcholy[7].color << std::endl;
//        std::cout << "Nahodny vrchol c. 7 pred prirazeni vrcholu do buffrupozice x: " << cstmvtxVrcholy[7].x << std::endl;
//        std::cout << "Vse se zda ok." << std::endl;
//        std::cout << "Nahodny vrchol pred assign c. 7 po prirazeni vrcholu do buffru barva: " << cstmvtxVrcholy[7].color << std::endl;
//        std::cout << "Nahodny vrchol pred assign c. 7 po prirazeni vrcholu do buffrupozice x: " << cstmvtxVrcholy[7].x << std::endl;
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
//    matice = pocatek * maticeSkalovani * maticeRotaceSveta;
    matice = pocatek;
    barvaStromu = D3DXVECTOR4(0.f,0.f,0.f,0.f);
    bVlnit = true;
    citacVrcholu = 0;
    citacIndicii = 0;
    per = 0.f;
    gonx = 0.f;
    sum = 0;
    countEm = 0;
//    druhStromu.urovenRozvetveni = iPatra;
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
//        std::cout << "Generuji vrcholy stromu..." << std::endl;
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
//        std::cout << "Ok\n";
        std::cout << "Strom uspesne vygenerovan a pripraven ke kresleni.\n" << std::endl;
//        std::cout << "Vytvarim vertex buffer stromu..." << std::endl;
//        vytvorBuffer();
//        std::cout << "Nahodny vrchol c. 7 pred prirazeni vrcholu do buffru barva: " << cstmvtxVrcholy[7].color << std::endl;
//        std::cout << "Nahodny vrchol c. 7 pred prirazeni vrcholu do buffrupozice x: " << cstmvtxVrcholy[7].x << std::endl;
//        std::cout << "Vse se zda ok." << std::endl;
//        std::cout << "Nahodny vrchol pred assign c. 7 po prirazeni vrcholu do buffru barva: " << cstmvtxVrcholy[7].color << std::endl;
//        std::cout << "Nahodny vrchol pred assign c. 7 po prirazeni vrcholu do buffrupozice x: " << cstmvtxVrcholy[7].x << std::endl;
#endif // defined
    } catch (std::exception& e) {
        std::cout << "Standard exception: " << e.what() << std::endl;
    }

    ++pocetInstanciStromu;
}

void Tree::znicBuffery()
{
#ifdef TREEVERBOSE
    std::cout << "Releasing (*bufferIndicii)" << std::endl;
#endif // TREEVERBOSE
    if( (bufferIndicii) != nullptr ){
        (*bufferIndicii)->Release();
        (*bufferIndicii) = NULL;
        delete bufferIndicii;           // release the memory that had been used for holding pointerToBuffer o_|, ta prostredni se alokuje dyn
#ifdef TREEVERBOSE
        std::cout << "Ok" << std::endl;
#endif // defined
    }
    else
#ifdef TREEVERBOSE
        std::cout << "NO bufferIndicii=nullptr" << std::endl;
#endif // defined

#ifdef TREEVERBOSE
    std::cout << "Releasing (*bufferVrcholu)" << std::endl;
#endif // defined
    if( bufferVrcholu != nullptr ){
        (*bufferVrcholu)->Release();
        (*bufferVrcholu) = NULL;
        delete bufferVrcholu;
#ifdef TREEVERBOSE
        std::cout << "Ok" << std::endl;
#endif // defined
    }
    else
#ifdef TREEVERBOSE
        std::cout << "NO bufferVrcholu=nullptr" << std::endl;
#endif // defined
}

void Tree::znicOstatniPointry()
{
#ifdef TREEVERBOSE
std::cout << "Mazu porade indicie, vrcholy, vlastnosti" << std::endl;
#endif // TREEVERBOSE
//    float* ptr = new float[50];
//    delete[] ptr;
    if(indicie != nullptr){
//            std::cout << "ind:"<<indicie[50] << std::endl;
//        delete[] indicie;
//        indicie = nullptr;
#ifdef TREEVERBOSE
std::cout << "ok" << std::endl;
#endif // TREEVERBOSE
    }
    else
#ifdef TREEVERBOSE
std::cout << "NO, nullptr" << std::endl;
#endif // TREEVERBOSE
    if(cstmvtxVrcholy != nullptr){
//        delete[] cstmvtxVrcholy;
//        cstmvtxVrcholy = nullptr;
#ifdef TREEVERBOSE
std::cout << "ok" << std::endl;
#endif // TREEVERBOSE
    }
    else
#ifdef TREEVERBOSE
std::cout << "NO, nullptr" << std::endl;
#endif // TREEVERBOSE
    if(vlastnostiVetvi != nullptr){
        delete[] vlastnostiVetvi;
        vlastnostiVetvi = nullptr;
#ifdef TREEVERBOSE
std::cout << "ok" << std::endl;
#endif // TREEVERBOSE
    }
    else
#ifdef TREEVERBOSE
std::cout << "NO, nullptr" << std::endl;
#endif // TREEVERBOSE
}

Tree::~Tree()
{
#ifdef TREEVERBOSE
    std::cout << "Strom being destroyed!" << std::endl;

#endif // defined
    znicOstatniPointry();
    znicBuffery();
//    delete[] vrcholy;
//    if(bufferVrcholu != nullptr) {
//        (*bufferVrcholu)->Release();
//    }
//    if(bufferIndicii != nullptr)
//        (*bufferIndicii)->Release();
//    delete[] indicie;
//    delete[] vetve;
    --pocetInstanciStromu;
}

bool Tree::generujKmen()
{

    int r=0,b=0,g=0;
    sum = 0;
    /*r = GenerateRndm(0,2);
    g = GenerateRndm(0,2);
    b = GenerateRndm(0,2);*/
    /*UINT uiTime=0;
    while(uiTime<1000){
    uiTime = timeGetTime();
    while(r==0||g==0||b==0){*/

    //r = zaokrouhli(helper::random());
    //g = zaokrouhli(helper::random());
    //b = zaokrouhli(helper::random());
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
    /*}
    uiTime=timeGetTime()-uiTime;}*/

    //r=1;g=1;b=0;
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
    //opakuj kolikrat chces rozdvojit
    return true;
}
/*Vytvori predkonfiguraci vetvi(klic), spocte pocet koncovych a ostatnich vetvi(rozdvojenych), vytvori vlastnosti kmene, generuje vlastnostiVetvi*/
bool Tree::generujVlastnostiVetvi()
{
    #ifdef DEBUG
    kontrolniPocetVetvi = 0;
    #endif // DEBUG
    int n = 1;
    //GenerateRndm(4,4);
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
    //gpVs[0].d = GenerateRndm(77*iPater,77*iPater)/1.f; //177max delka *pocet pater=maximalni vyska koruny
    vlastnostiVetvi[0].d = helper::random()*(100000+1111*druhStromu.urovenRozvetveni)+11111*druhStromu.urovenRozvetveni;
    //gpVs[0].r.r = GenerateRndm(0.999*(druhStromu.urovenRozvetveni-1)+20,0.999*(druhStromu.urovenRozvetveni-1)+20);
    //gpVs[0].rT.r =gpVs[0].r.r * (GenerateRndm(111,155)/200.f);
    vlastnostiVetvi[0].r.r = 0.999*(druhStromu.urovenRozvetveni-1)+555;
    vlastnostiVetvi[0].rT.r = vlastnostiVetvi[0].r.r *  (helper::random()*1+0.5)/10.f;
    vlastnostiVetvi[0].de =  50.f* PI/180;
//    gfDensity=gpVs[0].de;
//    gfDensityR= gpVs[0].r.r;

//    if ( druhStromu.element == usecka)
//    vlastnostiVetvi[0].m =  1000.f;//(2*PI*gpVs[0].r.r)/(360/(gpVs[0].de/(PI/180)));
//    else
//    vlastnostiVetvi[0].m =  1100.5f;//(2*PI*gpVs[0].r.r)/(360/(gpVs[0].de/(PI/180)));
//    vlastnostiVetvi[0].m = vlastnostiVetvi[0].d/4.f;

    #ifdef PROBLEMATICAL
    vlastnostiVetvi[0].x.x = 0.0f;
    vlastnostiVetvi[0].x.y = 0.0f;
    vlastnostiVetvi[0].x.z = 0.0f;
    if ( druhStromu.element == usecka ){
//    vlastnostiVetvi[0].d = 100000.f;
    vlastnostiVetvi[0].rT.sklon = PI/2;
    vlastnostiVetvi[0].r.sklon = vlastnostiVetvi[0].rT.sklon;
    vlastnostiVetvi[0].rT.rotace = 0;
    }
    #endif // PROBLEMATICAL

    #ifndef PROBLEMATICAL
    if ( druhStromu.element == usecka )
        vlastnostiVetvi[0].m = vlastnostiVetvi[0].d/2.f;
//    vlastnostiVetvi[0].m =  1000.f;//(2*PI*gpVs[0].r.r)/(360/(gpVs[0].de/(PI/180)));
    else
        vlastnostiVetvi[0].m =  1100.5f;//(2*PI*gpVs[0].r.r)/(360/(gpVs[0].de/(PI/180)));
    #else
    if ( druhStromu.element == usecka){
    vlastnostiVetvi[0].m = vlastnostiVetvi[0].d/2.f;
//        vlastnostiVetvi[0].m =  1000.f;//(2*PI*gpVs[0].r.r)/(360/(gpVs[0].de/(PI/180)));
    }
    else
        vlastnostiVetvi[0].m =  1100.5f;//(2*PI*gpVs[0].r.r)/(360/(gpVs[0].de/(PI/180)));
    #endif // PROBLEMATICAL

//    per = 2*PI/40*gpVs[0].m;
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
    else{
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
//    float PI = 3.14159265358979323846;
    float ample = 1.f;
    float OrigoX, OrigoY, OrigoZ, afterY;
    float posunX, posunY, posunZ;
    float rp, uzk;
    float k=0.f;
    VlastnostiVetve pVs;

    //pVs.r = parent.rT;
    afterY = cos(parent.rT.sklon)*(floor(parent.d/parent.m)*parent.m);//sin(atan((floor(parent.d/parent.m)*parent.m)/OrigoY)+parent.rT.sklon)*(OrigoY/cos(atan((floor(parent.d/parent.m)*parent.m)/OrigoY)));
    posunZ = parent.x.z+sin(parent.rT.sklon)*(floor(parent.d/parent.m)*parent.m);//cos(atan((floor(parent.d/parent.m)*parent.m)/OrigoY)+parent.rT.sklon)*(OrigoY/cos(atan((floor(parent.d/parent.m)*parent.m)/OrigoY)))+parent.x.z;
    posunY = parent.x.y+cos(parent.rT.rotace)*afterY;//cos(atan(afterY/OrigoX)+parent.rT.rotace)*(OrigoX/cos(atan(afterY/OrigoX)))+parent.x.y;
    posunX = parent.x.x+sin(parent.rT.rotace)*afterY;//sin(atan(afterY/OrigoX)+parent.rT.rotace)*(OrigoX/cos(atan(afterY/OrigoX)))+parent.x.x;
    pVs.x.z = posunZ;
    pVs.x.y = posunY;
    pVs.x.x = posunX;
    #ifdef PROBLEMATICAL
    if ( druhStromu.element == usecka ){
//    pVs.d = 1000.;

    float preponaSklonu = parent.d;
    float prilehlaSklonu = cos(parent.rT.sklon)*preponaSklonu;
    float protilehlaSklonu = sin(parent.rT.sklon)*preponaSklonu;
    float prilehlaRotace = cos(parent.rT.rotace)*prilehlaSklonu;
    float protilehlaRotace = sin(parent.rT.rotace)*prilehlaSklonu;
    pVs.x={parent.x.x + protilehlaRotace, parent.x.y + prilehlaRotace, parent.x.z + protilehlaSklonu};
    }
    else
    pVs.x={posunX, posunY, posunZ};
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

//    if(pVs.d<=pVs.m)			//this MUSTNT happen!!!
//        pVs.d=2*pVs.m;
//    pVs.d /= 1.f;
    #ifdef PROBLEMATICAL
/*minimalne pulka a maximalne stejna delka jako rodicka*/
    if ( druhStromu.element == usecka ){
    pVs.d =(helper::random()/2.+1/2.)*parent.d;
    pVs.m = pVs.d;///2.f;
    }
    #endif // PROBLEMATICAL


    /*if(strana%2 == 0)				//když je sudá
    		{
    			//pVs.r.sklon = parent.rT.sklon+k*PI/180;//-(zaokrouhli(helper::random())*0+10)*PI/180;//helper::random()*5*PI/180;//0.2f*pow(gonx*PI/180,2) ;
    			//pVs.r.sklon =  parent.rT.sklon-k*PI/180;
    			//pVs.r.sklon = helper::random()*parent.rT.sklon;
    			//pVs.r.rotace = parent.rT.rotace+((parent.rT.sklon==PI/2)?0:(atan(cos(parent.rT.sklon)*sin(pVs.r.sklon)/cos(pVs.r.sklon))))-((parent.rT.sklon==PI/2)?(PI/2):(PI/2));//+PI/2;//  + helper::random()*90*PI/180;
    			//pVs.rT.sklon = pVs.r.sklon;//helper::random()*5*PI/180;//0.2f*pow(gonx*PI/180,2) ;
    			//pVs.rT.r = parent.rT.r - helper::random()*1;
    			//pVs.d =helper::random()*19000+18277;
    			//pVs.aR = 0;
    			pVs.m = parent.m;
    			//pVs.de = parent.de;
    		}
    		else // jinak je licha
    		{
    			//pVs.r = parent.rT;
    			//pVs.aR = 0;
    			pVs.m = parent.m;
    			//pVs.de = parent.de;
    			//pVs.r.sklon = parent.rT.sklon+k*PI/180;//45*PI/180-(zaokrouhli(helper::random())*0+45)*PI/180;//- helper::random()*5*PI/180;//0.2f*pow(gonx*PI/180,2) ;
    			//pVs.r.sklon =  parent.rT.sklon-k*PI/180;
    			//pVs.r.sklon = helper::random()*PI/2;
    			//pVs.r.rotace = parent.rT.rotace-((parent.rT.sklon==PI/2)?0:(atan(cos(parent.rT.sklon)*sin(pVs.r.sklon)/cos(pVs.r.sklon))))+((parent.rT.sklon==PI/2)?(PI/2):(PI/2));//+PI/2;//  - helper::random()*90*PI/180;

    			//pVs.rT.sklon = pVs.r.sklon;//- helper::random()*5*PI/180;//0.2f*pow(gonx*PI/180,2) ;
    			//pVs.rT.r = parent.rT.r - helper::random()*1;
    			//pVs.d =helper::random()*20000+18277;
    		}*/

    return pVs;
}

void Tree::generujVrcholElementu(float r, float radiusZ, float sklony, float sklonz, float Dens, float posunX, float posunY, float posunZ)
{
    float Zkoord = 0.0f;
//    float PI = 3.14159265358979323846;
    float OrigoX, OrigoY, posX, posY, posZ;
    //
    //NAPLNeni
    //

//    float iVx = 0;
//    int reality=0;
//    iVx=2*PI/Dens;
//    countEm++;
    //reality++;
    /*Barva.x=0.f;//MANUAL OVERRIDE but this never happens
    Barva.y=1.f;
    Barva.z=0.5f;*/
    posX=posunX;
    posY=posunY;
    posZ=posunZ;
//    std::cout << "Generuji clanek cislo: " << vPoradi << std::endl;

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
//        for(int x=0; x<vPocet; x++)         // konverze barev
//        {
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
//                tempColor=(colorK * 255)-(int)(colorK * 255/16)*16;
    }

//        }
//        treeVertexBuffers[i]->Unlock();
//    }

//    cstmvtxVrcholy[vPoradi].color = 0xF;
    //Tvertices[vPoradi].Color = D3DXVECTOR4(0.0f,a/5,1.0f,1.f);
//    cstmvtxVrcholy[vPoradi].Color = Barva;
//    cstmvtxVrcholy[vPoradi].Color = D3DXVECTOR4(1.f, 1.f, 1.f, 1.f);
//    std::cout << "Nahodny vrchol c. x pozice x: " << cstmvtxVrcholy[vPoradi].color << std::endl;
    citacVrcholu++;

//    vPoradi=vPoradi;
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
    case testUsecka:
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
    case kuzel:
        break;
    default:
        break;
    }

}

void Tree::generujIndexyElementu(Element e, int pocatecniIndex)
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
    case usecka:
        indicie[citacIndicii] = pocatecniIndex;
        ++citacIndicii;
        indicie[citacIndicii] = koncovyIndex;
        ++citacIndicii;
        break;
    case kuzel:
        break;
    default:
        break;
    }
}

bool Tree::generujElementyVetve(VlastnostiVetve& pV)
{
    //RustTo = Rust;
//    float PI = 3.14159265358979323846;
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
    //per = 2*PI/40.f;
    sklonz = 0;
    float OrigoY = 0.f;
    float afterY = 0.f;
    float OrigoX = 0.f;
    float OrigoZ = 0.f;
    float Rorigin = pV.r.r;
    objRust TempRust = pV.r;
    float xAmp=1, yAmp=0;
    //pV.m = (2*PI*TempRust.r)/(360/(pV.de/(PI/180))); //360...obvod 1 stupne..
    //pV.r.sklon=-PI/4;
    //pV.rT.sklon=-PI/4;
    if(pV.k)
        pV.rT.r = 0.01f;

    switch (druhStromu.element) {
    case bod:{
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
//            generujIndexyElementu( druhStromu.element, citacVrcholu );
            generujVrcholElementu(usecka, posunX, posunY, posunZ, (pV.suda)?cervena:zelena);
            pV.posledniVrcholPredchoziVetve = citacVrcholu-1;
            #else
        for (float x = 0.f; x+1.f< pV.d/pV.m; x+=1.f) {
            //mezera = (2*PI*TemppV.r.r)/90; //360...obvod 1 stupne..
            TempRust.r += (pV.rT.r -pV.r.r)/floor(pV.d/pV.m);
            TempRust.rotace += (pV.rT.rotace-pV.r.rotace)/floor(pV.d/pV.m);
            TempRust.sklon += (pV.rT.sklon - pV.r.sklon)/floor(pV.d/pV.m);

            //TempRust.sklon = PI/4+sin(3*OrigoZ*PI/180)/10;
            //TempRust.rotace = PI/4;
            sklony = TempRust.sklon-PI/2;
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


            countEm=citacVrcholu;
//        std::cout << "Generuji clanky vetve..." << std::endl;
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
//    std::cout << "Clanky vetve dogenerovany." << std::endl;
            #endif // PROBLEMATICAL

        break;
        }
    case usecka:{
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
//            generujIndexyElementu( druhStromu.element, citacVrcholu );
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
            //mezera = (2*PI*TemppV.r.r)/90; //360...obvod 1 stupne..
            TempRust.r += (pV.rT.r -pV.r.r)/floor(pV.d/pV.m);
            TempRust.rotace += (pV.rT.rotace-pV.r.rotace)/floor(pV.d/pV.m);
            TempRust.sklon += (pV.rT.sklon - pV.r.sklon)/floor(pV.d/pV.m);

            //TempRust.sklon = PI/4+sin(3*OrigoZ*PI/180)/10;
            //TempRust.rotace = PI/4;
            sklony = TempRust.sklon-PI/2;
            sklonz = -TempRust.rotace;

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


            countEm=citacVrcholu;
            if(x+2.f >= pV.d/pV.m)             // konec vetve
            {
//                generujIndexyElementu( druhStromu.element, citacVrcholu );
                generujVrcholElementu( druhStromu.element, posunX, posunY, posunZ, druhStromu.barva );
                pV.posledniVrcholPredchoziVetve = citacVrcholu-1;
            }
            else
            {
                generujIndexyElementu( druhStromu.element, citacVrcholu );
                generujVrcholElementu( druhStromu.element, posunX, posunY, posunZ, druhStromu.barva );
            }
//        std::cout << "Generuji clanky vetve..." << std::endl;
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



    //AxeRotace += PI/2;//- rotace anuluje axerotaci<<<<<
    //rotace += PI/2;
    //r-=0.5;
    gonx = OrigoZ;
    if(/*start.z < height && gnVetvi > 0 && start.z > 0.f &&*/!pV.k) { //neni symetrické, chybí multithreading :D jiz hotovo
        //gnVetvi--;
        /*Barva.x=1.f;
        Barva.y=0.f;
        Barva.z=0.f;
        //for(int x=0;x<180;x++)
        	//RostClanek(TempRust.r, radiusZ, x*PI/180, sklonz, pV.de/30, posunX, posunY, posunZ);
        Barva.x=0.f;
        Barva.y=1.f;
        Barva.z=0.f;*/
        //for(int x=0;x<180;x++)
        //RostClanekRozdvojeni(TempRust.r,0.3/*rp*/, TempRust.r/*r2vneporadku*/, 0/*nic*/, x*PI/180/*inklinace k z*/,0/*nic*/,0/*nic*/, x*PI/180/*rotacekolemz*/, PI/4/*rotace kolem sve osy*/, pV.de/30/*hustota30*vice */, TempRust.r-0.1/*zalomeni*/, posunX, posunY, posunZ, 0.f);

        //for(int x=0; x<110; x++)
        //RostClanekRozdvojeni(TempRust.r,0.3/*rp*/, TempRust.r/*r2vneporadku*/, 0/*nic*/,0/*nic*/,0/*nic*/,0/*nic*/, 0/*nic*/, 0/*nic*/, pV.de/30/*hustota30*vice */, TempRust.r-0.5/*zalomeni*/, posunX, posunY, posunZ + x*0.1f, 0.f);

        //return RostRozdvojeni(pV.x,TempRust,pV.rT, pV.d,pV.aR, pV.m, pV.de);
    } else {
    }
    return true;
}

bool Tree::generujVykreslovaciDataVetvi()
{
#ifdef DEBUG
//    kontrolniPocetVrcholu = 0;
    kontrolniPocetIndicii = 0;
#endif // DEBUG
//            float posunX, posunY, posunZ;
//            posunZ=vlastnostiVetvi[0].x.z;
//            posunY=vlastnostiVetvi[0].x.y;
//            posunX=vlastnostiVetvi[0].x.x;
////            generujIndexyElementu( druhStromu.element, citacVrcholu );
//            generujVrcholElementu(usecka, posunX, posunY, posunZ, (vlastnostiVetvi[0].suda)?cervena:zelena);

    for(int f = 0; f<pocetVetvi; f++) {
//        std::cout << "rost vetev c> " << f << " uspesne." << std::endl;
        generujElementyVetve(vlastnostiVetvi[f]);
        /*r = GenerateRndm(0,2); colors!!!
        g = GenerateRndm(0,2);
        b = GenerateRndm(0,2);
        //r=1;g=1;b=0;
        sum = b+2*g+4*r;*/
    }
#ifdef TREEVERBOSE
#ifdef DEBUG
    if(citacVrcholu == pocetVrcholu)
        std::cout << "..Ok\nPocet vrcholu odpovida odhadu." << std::endl;
    else{
        std::cout << "Pocet vrcholu neodpovida odhadu!" << std::endl;
        std::cout << "Je jich: " << citacVrcholu << std::endl;
    }
    if(citacIndicii == pocetElementu*2)
        std::cout << "..Ok\nPocet indicii odpovida odhadu." << std::endl;
    else{
        std::cout << "Pocet indicii neodpovida odhadu!" << std::endl;
        std::cout << "Je jich: " << citacIndicii << std::endl;
    }
    if(pocetElementu == citacIndicii/2)
        std::cout << "..Ok\nPocet elementu odpovida odhadu." << std::endl;
    else{
        std::cout << "Pocet elementu neodpovida odhadu!" << std::endl;
        std::cout << "Je jich: " << citacIndicii/2 << std::endl;
    }
//    if(kontrolniPocetVetvi == pocetVetvi)
//        std::cout << "..Ok\nPocet vetvi odpovida odhadu." << std::endl;
//    else{
//        std::cout << "Pocet vetvi neodpovida odhadu!" << std::endl;
//        std::cout << "Je jich: " << kontrolniPocetVetvi << std::endl;
//    }
    cstmvtxVrcholy[0].color = D3DCOLOR_XRGB(255,0,0);
    cstmvtxVrcholy[pocetVrcholu-1].color = D3DCOLOR_XRGB(255,0,0);
#endif // DEBUG
//    std::cout << "Vrcholy dogenerovany." << std::endl;
#endif // defined
    return true;
}

bool Tree::generujListy()
{

    return true;
}

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

    //iVx=1000000;
#ifdef PROBLEMATICAL
    if ( druhStromu.element == usecka ){
    return pocetVetvi;//+2;
    }
    else
    return iVx;
#else
    return iVx;
#endif // PROBLEMATICAL
}

int Tree::spoctiElementy()
{
//    if ( druhStromu.element == testUsecka) {
//    } else return 0;

    switch ( druhStromu.element )
    {
    case testUsecka:{
        pocetElementu = 3;
        pocetVrcholu = 4;
        return 3;
        break;
    }
    case usecka:{
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

bool Tree::generujPlosky()
{

    return true;
}

bool Tree::alokujMistoProVrcholyAindicie()
{
    try {
        cstmvtxVrcholy = new CUSTOMVERTEX[pocetVrcholu];
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
//    std::cout << "Pocet vetvi je: " << pocetVetvi << std::endl;
#ifdef TREEVERBOSE
//    std::cout << "Alokace pameti pro CUSTOMVERTEX[] uspesna..." << std::endl;
#endif // defined
    return true;
}

void Tree::aktualizujMatici()
{
    if (zmenaRotace > 0.f)
        rotace += zmenaRotace;
    else
        rotace = 0.f;
    D3DXMatrixRotationZ(&maticeRotaceStromuZ, rotace);

    world = maticeRotaceStromuZ * matice * maticeSkalovani * maticeRotaceStromuX;
}

void Tree::vykresli() const         // const fcion, so it cant change anything in our object
{

    pzarizeni->SetTransform( D3DTS_WORLD, &world );
    pzarizeni->SetStreamSource( 0, (*bufferVrcholu), 0, sizeof( CUSTOMVERTEX ) );
    switch (druhStromu.element) {
    case bod:
        pzarizeni->DrawPrimitive(
            D3DPT_POINTLIST, 0, pocetVrcholu );
        break;
    case testUsecka:
    case usecka:
        pzarizeni->SetIndices(*bufferIndicii);
        pzarizeni->DrawIndexedPrimitive( D3DPT_LINELIST, // PrimitiveType
                                         0,                  // BaseVertexIndex
                                         0,                  // MinIndex
                                         pocetVrcholu,                  // NumVertices
                                         0,                  // StartIndex
                                         pocetElementu );                // PrimitiveCount
        break;
    case kuzel:
        break;

    default:
        break;
    }

}

void Tree::testVykresli() const
{
    // Clear the backbuffer to a black color
//        pd3dZarizeni->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 255, 255, 255 ), 1.0f, 0 );
    pzarizeni->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 0, 0, 0 ), 1.0f, 0 );
    // Begin the scene
    if( SUCCEEDED( pzarizeni->BeginScene() ) ) {
        pzarizeni->SetFVF( D3DFVF_CUSTOMVERTEX );


        D3DXMATRIX mRotateW, mScale;

        D3DXMatrixRotationX(&mRotateW, -3.14159265358979323846/2);     // Otoci strom o -Pi
        D3DXMatrixScaling(&mScale, 0.5f, 0.5f, 0.5f );                 // Zmensi strom na 1/2
        D3DXMATRIX g_World1 = matice * mScale * mRotateW;
        pzarizeni->SetStreamSource( 0, *(bufferVrcholu), 0, sizeof( CUSTOMVERTEX ) );
        pzarizeni->DrawPrimitive(D3DPT_POINTLIST, 0, pocetVrcholu );

//  OLD TREE PART
        // Setup the world, view, and projection Matrices
        D3DXMatrixRotationX(&mRotateW, -3.14159265358979323846/2);     // Otoci strom o -Pi
        D3DXMatrixScaling(&mScale, 1.5f, 1.5f, 1.5f );                 // Zmensi strom na 1/2

//            D3DXMATRIX g_World1 = matice * mScale * mRotateW;
//            D3DXMATRIX g_World1 = treeMatrix[25] * mScale * mRotateW;
        pzarizeni->SetTransform( D3DTS_WORLD, &g_World1 );

        pzarizeni->SetStreamSource( 0, (*bufferVrcholu), 0, sizeof( CUSTOMVERTEX ) );

        pzarizeni->DrawPrimitive(
            D3DPT_POINTLIST, 0, pocetVrcholu );

//             Render the vertex buffer contents
//            pzarizeni->SetStreamSource( 0, treeVertexBuffers[0], 0, sizeof( CUSTOMVERTEX ) );

//            pzarizeni->DrawPrimitive(
//                D3DPT_POINTLIST, 0, aPocetVrcholuStromu[0] );
        // End the scene
        pzarizeni->EndScene();
    } else
        std::cout << "Err rendering" << std::endl;

    // Present the backbuffer contents to the display
    pzarizeni->Present( NULL, NULL, NULL, NULL );

}

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
    if( FAILED( pzarizeni->CreateVertexBuffer( pocetVrcholu * sizeof( CUSTOMVERTEX ),
                0, D3DFVF_CUSTOMVERTEX,
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

    switch ( druhStromu.element ) {
    case testUsecka:
    case usecka:
        try {
            bufferIndicii = new LPDIRECT3DINDEXBUFFER9;     // dyn alc pointer
        } catch (std::exception& e) {
            vysledek = false;
            std::cout << "Heap allocation exception: " << e.what() << std::endl;
        }
        if( FAILED( pzarizeni->CreateIndexBuffer( pocetElementu * 2 * sizeof(long),
                    D3DUSAGE_WRITEONLY , D3DFMT_INDEX32, D3DPOOL_DEFAULT,
                    bufferIndicii, NULL ) ) ) {
            std::cout << "Nepodarilo se vytvorit index buffer." << std::endl;
            vysledek = false;
        }
        break;
    case kuzel:
        vysledek = false;
        break;
    default:
        vysledek = false;
        break;
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
    if( druhStromu.element > 0 )
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

bool Tree::odemkniVrcholyProCteni()
{
    bool vysledek;
    if(FAILED ((*bufferVrcholu)->Unlock())) {
        vysledek = false;
        std::cout << "Nepodarilo se odemknout buffer vrcholu pro cteni." << std::endl;
    } else
        vysledek = true;

    if( druhStromu.element > 0 )
        if(FAILED ((*bufferIndicii)->Unlock())) {
            vysledek = false;
            std::cout << "Nepodarilo se odemknout buffer indicii pro cteni." << std::endl;
        } else
            vysledek = true;
    return vysledek;
}

bool Tree::zkopirujVrcholyDoBuffru(CUSTOMVERTEX* vrcholy, int pocet)
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
//    Tvertices = getTree();

//    int tempColor;
//    float colorK;
//    for(int x=0; x<vPocet; x++)         // konverze barev
//    {
//        g_Vertices[x].x = Tvertices[x].Pos.x;
//        g_Vertices[x].y = Tvertices[x].Pos.y;
//        g_Vertices[x].z = Tvertices[x].Pos.z;
////			g_Vertices[x].color = 0xF000000;
//        for(int b = 0; b<3; b++)
//        {
//            switch(b)
//            {
//            case 0:
//            {
//                colorK = Tvertices[x].Color.z;
//                break;
//            }
//            case 1:
//            {
//                colorK = Tvertices[x].Color.y;
//                break;
//            }
//            case 2:
//            {
//                colorK = Tvertices[x].Color.x;
//                break;
//            }
//            }
//            tempColor=(colorK * 255);
//            g_Vertices[x].color += DWORD(tempColor*(pow(float(16),b*2)));
////                tempColor=(colorK * 255)-(int)(colorK * 255/16)*16;
//        }
//    }
//    (*bufferVrcholu)->Unlock();
    return vysledek;
}

Vetev::Vetev()
{

}

Vetev::~Vetev()
{
//    delete[] vrcholy;
}


}
