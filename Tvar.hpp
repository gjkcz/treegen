#ifndef __H_TVAR_INCLUDED__
#define __H_TVAR_INCLUDED__

#include "JednoduchyVertex.hpp"
#include "CustomVertex.hpp"
#include "TreeType.hpp"     // barva
#include <exception>
namespace se
{

class Tvar
{
public:
    Tvar();
    Tvar(Tvar&& tmp){                   // move citron
        cstmvtxVrcholy =  tmp.cstmvtxVrcholy;
        paIndicie = tmp.paIndicie;
        pzarizeni = tmp.pzarizeni;
        maticeSkalovani = tmp.maticeSkalovani;
        maticeRotaceStromuX = tmp.maticeRotaceStromuX;
        maticeRotaceStromuZ = tmp.maticeRotaceStromuZ;
        barvaUsecky = tmp.barvaUsecky;
        bufferVrcholu = tmp.bufferVrcholu;
        bufferIndicii = tmp.bufferIndicii;

        matice = tmp.matice;
        zmenaRotace = tmp.zmenaRotace;
        rotace = tmp.rotace;

        tmp.bufferVrcholu = nullptr;
        tmp.cstmvtxVrcholy = nullptr;
        tmp.bufferIndicii = nullptr;
        tmp.paIndicie = nullptr;
    }
    Tvar(D3DXMATRIX& pocatek, t::Barva, LPDIRECT3DDEVICE9* _pzarizeni);
    Tvar(D3DXMATRIX& pocatek, t::Barva, LPDIRECT3DDEVICE9* _pzarizeni, float zRot);
    ~Tvar();
    Tvar& operator=(Tvar&& tmp){        // move assasin
//        znicBuffery();
//        znicOstatniPointry();
        cstmvtxVrcholy =  tmp.cstmvtxVrcholy;
        paIndicie = tmp.paIndicie;
        pzarizeni = tmp.pzarizeni;
        maticeSkalovani = tmp.maticeSkalovani;
        maticeRotaceStromuX = tmp.maticeRotaceStromuX;
        maticeRotaceStromuZ = tmp.maticeRotaceStromuZ;
        barvaUsecky = tmp.barvaUsecky;
        bufferVrcholu = tmp.bufferVrcholu;
        bufferIndicii = tmp.bufferIndicii;

        matice = tmp.matice;
        zmenaRotace = tmp.zmenaRotace;

        tmp.bufferVrcholu = nullptr;
        tmp.cstmvtxVrcholy = nullptr;
        tmp.bufferIndicii = nullptr;
        tmp.paIndicie = nullptr;
        return *this;
    }
    virtual void aktualizujMatici();
    virtual void nastavRotaci(float rot) {zmenaRotace = rot;}
    virtual void vykresli() const;
protected:
    float rotace, zmenaRotace;
    D3DXMATRIX matice;
    D3DXMATRIX world;
    D3DXMATRIX maticeSkalovani;
    D3DXMATRIX maticeRotaceStromuX;
    D3DXMATRIX maticeRotaceStromuZ;
    VrcholB* cstmvtxVrcholy;
    long* paIndicie;
    LPDIRECT3DVERTEXBUFFER9* bufferVrcholu;
    LPDIRECT3DINDEXBUFFER9* bufferIndicii;
    LPDIRECT3DDEVICE9 pzarizeni;
    t::Barva barvaUsecky;
    bool vytvorBufferVrcholu();            // Je treba jiz znat pocet vrcholu
    bool vytvorBufferIndicii();
    void znicBuffery();
    void znicOstatniPointry();
    bool uzamkniPoleDoBuffru();       // musi existovat buffer a cstmvtxVrcholy musi byt nejprve vytvoreny,
    bool odemkniVrcholyProCteni();
    virtual void generujVrcholy(D3DXVECTOR3&, D3DXVECTOR3&) =0;
    virtual void generujIndexy(int, int) =0;
//    virtual void pure() =0;
};


}

#endif // __H_TVAR_INCLUDED__

