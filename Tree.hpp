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
    Tree(DruhStromu, D3DXMATRIX& pocatek, LPDIRECT3DDEVICE9& _pzarizeni);
    Tree(DruhStromu, D3DXMATRIX& pocatek, LPDIRECT3DDEVICE9* _pzarizeni);
    Tree(Tree&& tmp);                       // move ctor
    Tree& operator= (Tree&&);             // move assignment
    ~Tree();

    void vykresli() const;
    void testVykresli() const;
    void aktualizujMatici();
//    LPDIRECT3DVERTEXBUFFER9* bufferVrcholu;
//    D3DXMATRIX matice;
//    CUSTOMVERTEX* cstmvtxVrcholy;
//    int pocetVrcholu;
//    bool odemkniVrcholyProCteni();
//    bool generujVrcholyVetvi();     // Musi znat pocet vrcholu

private:
    DruhStromu druhStromu;
    VlastnostiVetve* vlastnostiVetvi;       // Parametry vetvi, pozor dynAlc!
    int iPater;
//    SimpleVertex* vrcholy;
    CUSTOMVERTEX* cstmvtxVrcholy;
    LPDIRECT3DVERTEXBUFFER9* bufferVrcholu;
    int pocetVrcholu;
    int pocetVetvi;
//    UINT* indicie;
//    Vetev* vetve;
    D3DXMATRIX matice;
    D3DXMATRIX world;
    D3DXMATRIX maticeSkalovani, maticeRotaceSveta;
    LPDIRECT3DDEVICE9 pzarizeni;
    VlastnostiVetve generujVlastnostiVetve(VlastnostiVetve parent, int strana, DruhStromu _tType);

    D3DXVECTOR4 Barva;
    int vPoradi;
    float per, gonx; //, height;
    int sum;
    int countEm;
    bool bVlnit;
    void RostClanek(float r, float radiusZ, float sklony, float sklonz, float Dens, float posunX, float posunY, float posunZ);
    bool RostVetev(VlastnostiVetve);

    bool generujVlastnostiVetvi();
    bool generujVrcholyVetvi();     // Musi znat pocet vrcholu
    bool generujKmen();
    bool generujListy();
    int spoctiVertexy();           // Potreba pred vytvarenim buffru, potrebuje vygenerovat vlastnosti vetvi
    bool generujPlosky();
    bool prevedVrcholyNaCstmvtx();
    bool vytvorBuffer();            // Je treba jiz znat pocet vrcholu
    bool zkopirujVrcholyDoBuffru(CUSTOMVERTEX* vrcholy, int pocet);   // Vola vytvorBuffer

    bool uzamkniVrcholyProUtvareni();
    bool odemkniVrcholyProCteni();
};


}
#endif // __TREE_H_INCLUDED__
