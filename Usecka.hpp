#ifndef __H_USECKA_INCLUDED__
#define __H_USECKA_INCLUDED__

#include "Tvar.hpp"
namespace se
{


class Usecka : public Tvar
{
public:
    Usecka();
    Usecka(Usecka&& tmp){                   // move citron
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
    Usecka(D3DXMATRIX& pocatek, D3DXVECTOR3& x, D3DXVECTOR3& y, t::Barva, LPDIRECT3DDEVICE9* _pzarizeni);
    Usecka(D3DXMATRIX& pocatek, D3DXVECTOR3& x, D3DXVECTOR3& y, t::Barva, LPDIRECT3DDEVICE9* _pzarizeni, float zRot);
    ~Usecka();
    Usecka& operator=(Usecka&& tmp){        // move assasin
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
//    void aktualizujMatici();
//    void nastavRotaci(float rot) {zmenaRotace = rot;}
//    void vykresli() const;
protected:
private:
//    float rotace, zmenaRotace;
//    D3DXMATRIX matice;
//    D3DXMATRIX world;
//    D3DXMATRIX maticeSkalovani;
//    D3DXMATRIX maticeRotaceStromuX;
//    D3DXMATRIX maticeRotaceStromuZ;
//    VrcholB* cstmvtxVrcholy;
//    long* paIndicie;
//    LPDIRECT3DVERTEXBUFFER9* bufferVrcholu;
//    LPDIRECT3DINDEXBUFFER9* bufferIndicii;
//    LPDIRECT3DDEVICE9 pzarizeni;
//    t::Barva barvaUsecky;
//    bool vytvorBufferVrcholu();            // Je treba jiz znat pocet vrcholu
//    bool vytvorBufferIndicii();
//    void znicBuffery();
//    void znicOstatniPointry();
//    bool uzamkniPoleDoBuffru();       // musi existovat buffer a cstmvtxVrcholy musi byt nejprve vytvoreny,
//    bool odemkniVrcholyProCteni();
    void generujVrcholy(D3DXVECTOR3&, D3DXVECTOR3&);
    void generujIndexy(int, int);
};


}
#endif // __H_USECKA_INCLUDED__

