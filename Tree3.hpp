#ifndef __TREE3_H_INCLUDED__
#define __TREE3_H_INCLUDED__

#include <iostream>
#include <exception>
#include "globals.hpp"
#include "Helper.hpp"
#include "JednoduchyVertex.hpp"
#include "CustomVertex.hpp"
#include "TreeType.hpp"
#include "Usecka.hpp"
#include "SWU/Konzole.hpp"

namespace t3
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
    int rozliseniE;  /*Pocet vrcholu na element/2.*/
    int rozliseniV;  /*Pocet elementu na vetev.*/
    float de;
    int posledniVrcholPredchoziVetve;
    int citacClankuVetve;
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

class Tree3
{
public:
    static int pocetInstanciStromu;       // pocet stromu

    Tree3();
//    Tree3(DruhStromu, D3DXMATRIX& pocatek, LPDIRECT3DDEVICE9& _pzarizeni);
    Tree3(t::DruhStromu&, D3DXMATRIX& pocatek, LPDIRECT3DDEVICE9* _pzarizeni);
    Tree3(t::DruhStromu&, D3DXMATRIX& pocatek, LPDIRECT3DDEVICE9* _pzarizeni, float zRot);
    Tree3(Tree3&& tmp);                       // move ctor
    Tree3& operator= (Tree3&&);             // move assignment
    ~Tree3();

    void aktualizujMatici();
    void vykresli(bool osvetlovat) const;
    void testVykresli() const;
    void nastavRotaci(float _f) {
        for (se::Tvar& iKolmice : kolmice)
            iKolmice.nastavRotaci(_f);
        zmenaRotace = _f;
    }
    void nastavKonzoli(sk::Konzole& k) {iKonzole = k;}
    void nastavVykreslovaciElement(t::Element _f) {
        druhStromu.element = _f;
    }
    t::DruhStromu& vemDruhStromu() {
        return druhStromu;
    }

private:
    sk::Konzole iKonzole;
    D3DMATERIAL9 material;
    t::DruhStromu druhStromu;
    VlastnostiVetve* vlastnostiVetvi;       // Parametry vetvi, pozor dynAlc!
    std::vector<se::Usecka> kolmice;     // pomocne kolmice
    VrcholBK* cstmvtxVrcholy;
    long* paIndicie;
    std::vector<VrcholBK> vrcholy;
    std::vector<long> indicie;
    LPDIRECT3DVERTEXBUFFER9* bufferVrcholu;
    LPDIRECT3DINDEXBUFFER9* bufferIndicii;
    bool btriangleList;
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
    long citacClanku;
    int citacVetvi;
    D3DXMATRIX matice;
    D3DXMATRIX world;
    float rotace, zmenaRotace;
    D3DXMATRIX maticeSkalovani;
    D3DXMATRIX maticeRotaceStromuX;
    D3DXMATRIX maticeRotaceStromuZ;
    LPDIRECT3DDEVICE9 pzarizeni;
    D3DXVECTOR4 barvaStromu;
    float per, gonx; //, height;
    int sum;
    int countEm;
    bool bVlnit;
    bool generujKmen();
    bool generujVlastnostiVetvi();
    VlastnostiVetve generujVlastnostiVetve( const VlastnostiVetve& parent, int strana, t::DruhStromu& _tType );
    int spoctiClanky();
    int spoctiElementy();
    int spoctiVrcholy();           // Potreba pred vytvarenim buffru, potrebuje vygenerovat vlastnosti vetvi
    bool vytvorBufferVrcholu();            // Je treba jiz znat pocet vrcholu
    bool vytvorBufferIndicii();
    void znicBuffery();
    void znicOstatniPointry();
    bool uzamkniPoleDoBuffru();       // musi existovat buffer a cstmvtxVrcholy musi byt nejprve vytvoreny,
    bool generujVykreslovaciDataVetvi();     // Musi znat pocet vrcholu
    bool generujElementyVetve( VlastnostiVetve& );
    void generujVrcholyKruhu( const D3DXVECTOR3& pocatek, VlastnostiVetve& pV, float r, float radiusZ, float sklony, float sklonz, float Dens );
    void generujVrcholyVetve( const D3DXVECTOR3& pocatek, int kolikClanku, VlastnostiVetve& pV );
    int generujIndicieVetve( int cislo, int kolikClanku );
    void generujIndicieKruhuXY( int x, int y );
    void generujVrcholElementu( float r, float radiusZ, float sklony, float sklonz, float Dens, float posunX, float posunY, float posunZ );   // melo by brat pole referenci za param
    void generujIndicieElementu( t::Element e, int );
    void generujIndicieElementu( t::Element e, int, int );
    void pridejNormaluVrcholu( int pozice, D3DXVECTOR3 kolmice );
    D3DXVECTOR3 spocitejNormaluVrcholu( int a, int b, int c );
    D3DXVECTOR3 spocitejNormaluVrcholu( int a );
    bool odemkniVrcholyProCteni();
    bool zkopirujVrcholyDoBuffru( const std::vector<VrcholBK>& _vrcholy );   // Vola vytvorBuffer
    bool zkopirujIndicieDoBuffru( const std::vector<long>& _indicie );   // Vola vytvorBuffer
};


}
#endif // __TREE3_H_INCLUDED__
