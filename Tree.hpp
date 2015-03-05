#ifndef __TREE_H_INCLUDED__
#define __TREE_H_INCLUDED__

#include <iostream>
#include <exception>
#include "globals.hpp"
#include "Helper.hpp"
#include "JednoduchyVertex.hpp"
#include "CustomVertex.hpp"
#include "TreeType.hpp"
#include "Usecka.hpp"
#include "SWU/Konzole.hpp"

namespace t
{
namespace h = helper;


class StromVyjimka: public std::exception
{
public:
    StromVyjimka(const char* say) : zpravicka {say} {}
    virtual const char* what() const throw()
    {
        return zpravicka;
    }
private:
    const char* zpravicka;
} ;


struct objRust {
    float r;
    float sklon;
    float rotace;
};

struct VlastnostiVetve {
    D3DXVECTOR3 x;
    objRust r;
    objRust rT;
    bool k;
    bool suda;
    float d;
    float aR;
    float m;
    float de;
    int posledniVrcholPredchoziVetve;
    VlastnostiVetve* rodicka;
};

struct tuplParamsVetve {
    VlastnostiVetve p_0;
    VlastnostiVetve p_1;
};

class Vetev
{
    friend class Tree;
public:
    Vetev();
    ~Vetev();
protected:
//    SimpleVertex* vrcholy;
//    CUSTOMVERTEX* cstmvtxVrcholy;
private:
};

class Tree
{
public:
    static int pocetInstanciStromu;       // pocet stromu

    Tree();
//    Tree(DruhStromu, D3DXMATRIX& pocatek, LPDIRECT3DDEVICE9& _pzarizeni);
    Tree(DruhStromu&, D3DXMATRIX& pocatek, LPDIRECT3DDEVICE9* _pzarizeni);
    Tree(DruhStromu&, D3DXMATRIX& pocatek, LPDIRECT3DDEVICE9* _pzarizeni, float zRot);
    Tree(Tree&& tmp);                       // move ctor
    Tree& operator= (Tree&&);             // move assignment
    ~Tree();

    void aktualizujMatici();
    void vykresli(bool osvetlovat) const;
    void testVykresli() const;
    void nastavRotaci(float _f) {
        for (auto& iKolmice : kolmice)
            iKolmice.nastavRotaci(_f);
        zmenaRotace = _f;
    }
    void nastavKonzoli(sk::Konzole& k) {iKonzole = k;}
    void nastavVykreslovaciElement(Element _f) {
        druhStromu.element = _f;
    }
    DruhStromu& vemDruhStromu() {
        return druhStromu;
    }

private:
    sk::Konzole iKonzole;
    D3DMATERIAL9 material;
    DruhStromu druhStromu;
    VlastnostiVetve* vlastnostiVetvi;       // Parametry vetvi, pozor dynAlc!
    std::vector<se::Usecka> kolmice;     // pomocne kolmice
    VrcholBK* cstmvtxVrcholy;
    long* indicie;
    LPDIRECT3DVERTEXBUFFER9* bufferVrcholu;
    LPDIRECT3DINDEXBUFFER9* bufferIndicii;
    int pocetVrcholu;
    int pocetIndicii;
    int pocetElementu;
    int pocetClanku;
    int pocetVetvi;
    int pocetRozdvojujicichseVetvi;
    int pocetKoncovychVetvi;
    int citacVrcholu;                            // MOZNA POTREBA VETSIHO MISTA
    int citacIndicii;
    int citacElementu;
    int citacClanku;
    #ifdef DEBUG
//    int kontrolniPocetVrcholu;
    int kontrolniPocetIndicii;
    int kontrolniPocetVetvi;
    int kontrolniPocetElementu;
    #endif // DEBUG
    D3DXMATRIX matice;
    D3DXMATRIX world;
    float rotace, zmenaRotace;
    D3DXMATRIX maticeSkalovani;
    D3DXMATRIX maticeRotaceStromuX;
    D3DXMATRIX maticeRotaceStromuZ;
    LPDIRECT3DDEVICE9 pzarizeni;
    D3DXVECTOR4 barvaStromu;
//    int posledniVrcholPredchoziVetve;
    float per, gonx; //, height;
    int sum;
    int countEm;
    bool bVlnit;
    bool generujKmen();
    bool generujVlastnostiVetvi();
    VlastnostiVetve generujVlastnostiVetve( VlastnostiVetve& parent, int strana, DruhStromu& _tType);
    int spoctiElementy();
    int spoctiVrcholy();           // Potreba pred vytvarenim buffru, potrebuje vygenerovat vlastnosti vetvi
    bool alokujMistoProVrcholyAindicie();
    bool vytvorBufferVrcholu();            // Je treba jiz znat pocet vrcholu
    bool vytvorBufferIndicii();
    void znicBuffery();
    void znicOstatniPointry();
    bool uzamkniPoleDoBuffru();       // musi existovat buffer a cstmvtxVrcholy musi byt nejprve vytvoreny,
    bool generujVykreslovaciDataVetvi();     // Musi znat pocet vrcholu
    bool generujElementyVetve( VlastnostiVetve& );
    void generujVrcholyIndicieVetve(D3DXVECTOR3 pocatek);
    void generujVrcholyIndicieKruhu(D3DXVECTOR3 pocatek);
    void generujVrcholElementu( Element e );
    void generujVrcholElementu( Element e, float, float, float, Barva );
    void generujVrcholElementu(float r, float radiusZ, float sklony, float sklonz, float Dens, float posunX, float posunY, float posunZ);   // melo by brat pole referenci za param
    void generujIndexyElementu( Element e, int );
    void generujIndexyElementu( Element e, int, int );
    void pridejNormaluVrcholu( int pozice, D3DXVECTOR3 kolmice );
    D3DXVECTOR3 spocitejNormaluVrcholu( int a, int b, int c );
    D3DXVECTOR3 spocitejNormaluVrcholu( int a );
    bool generujListy();
    bool generujPlosky();
    bool odemkniVrcholyProCteni();
    bool zkopirujVrcholyDoBuffru(VrcholBK* vrcholy, int pocet);   // Vola vytvorBuffer
};


}
#endif // __TREE_H_INCLUDED__
