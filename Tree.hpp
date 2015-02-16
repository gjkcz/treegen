#ifndef __TREE_H_INCLUDED__
#define __TREE_H_INCLUDED__

#include <iostream>
#include <exception>
#include "globals.hpp"
#include "Helper.hpp"
#include "JednoduchyVertex.hpp"
#include "CustomVertex.hpp"
#include "TreeType.hpp"

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
    float d;
    float aR;
    float m;
    float de;
};
//paramsVetve* gpVs;


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
    SimpleVertex* vrcholy;
    CUSTOMVERTEX* cstmvtxVrcholy;
private:
};

class Tree
{
public:
    static int pocetInstanciStromu;       // pocet stromu

    Tree();
//    Tree(DruhStromu, D3DXMATRIX& pocatek, LPDIRECT3DDEVICE9& _pzarizeni);
    Tree(DruhStromu, D3DXMATRIX& pocatek, LPDIRECT3DDEVICE9* _pzarizeni);
    Tree(DruhStromu, D3DXMATRIX& pocatek, LPDIRECT3DDEVICE9* _pzarizeni, float zRot);
    Tree(Tree&& tmp);                       // move ctor
    Tree& operator= (Tree&&);             // move assignment
    ~Tree();

    void aktualizujMatici();
    void vykresli() const;
    void testVykresli() const;
    void nastavRotaci(float _f) {zmenaRotace = _f;}
//    LPDIRECT3DVERTEXBUFFER9* bufferVrcholu;
//    D3DXMATRIX matice;
//    CUSTOMVERTEX* cstmvtxVrcholy;
//    int pocetVrcholu;
//    bool odemkniVrcholyProCteni();
//    bool generujVrcholyVetvi();     // Musi znat pocet vrcholu

private:
    DruhStromu druhStromu;
    VlastnostiVetve* vlastnostiVetvi;       // Parametry vetvi, pozor dynAlc!
//    int iPater;
//    SimpleVertex* vrcholy;
    CUSTOMVERTEX* cstmvtxVrcholy;
    long* indicie;
    LPDIRECT3DVERTEXBUFFER9* bufferVrcholu;
    LPDIRECT3DINDEXBUFFER9* bufferIndicii;
    int pocetVrcholu;
    int pocetElementu;
    int pocetVetvi;
    #ifdef DEBUG
    int kontrolniPocetVrcholu;
    #endif // DEBUG
//    UINT* indicie;
//    Vetev* vetve;
    D3DXMATRIX matice;
    D3DXMATRIX world;
    float rotace, zmenaRotace;
    D3DXMATRIX maticeSkalovani;
    D3DXMATRIX maticeRotaceStromuX;
    D3DXMATRIX maticeRotaceStromuZ;
    LPDIRECT3DDEVICE9 pzarizeni;
    VlastnostiVetve generujVlastnostiVetve(VlastnostiVetve parent, int strana, DruhStromu _tType);
    D3DXVECTOR4 Barva;
    int citacVrcholu;                            // MOZNA POTREBA VETSIHO MISTA
    int citacIndicii;
    float per, gonx; //, height;
    int sum;
    int countEm;
    bool bVlnit;

    bool generujKmen();
    bool generujVlastnostiVetvi();
    int spoctiElementy();
    int spoctiVrcholy();           // Potreba pred vytvarenim buffru, potrebuje vygenerovat vlastnosti vetvi
    bool alokujMistoProVrcholyAindicie();
    bool vytvorBufferVrcholu();            // Je treba jiz znat pocet vrcholu
    bool vytvorBufferIndicii();
    bool uzamkniPoleDoBuffru();       // musi existovat buffer a cstmvtxVrcholy musi byt nejprve vytvoreny,
    bool generujVykreslovaciDataVetvi();     // Musi znat pocet vrcholu
    bool generujElementyVetve(VlastnostiVetve);
    void generujVrcholElementu( Element e );
    void generujVrcholElementu( Element e, float, float, float );
    void generujVrcholElementu(float r, float radiusZ, float sklony, float sklonz, float Dens, float posunX, float posunY, float posunZ);
    void generujIndexyElementu( Element e, int );
    bool generujListy();
    bool generujPlosky();
    bool odemkniVrcholyProCteni();
    bool zkopirujVrcholyDoBuffru(CUSTOMVERTEX* vrcholy, int pocet);   // Vola vytvorBuffer
};


}
#endif // __TREE_H_INCLUDED__
