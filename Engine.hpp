#ifndef __ENGINE_H_INCLUDED__
#define __ENGINE_H_INCLUDED__

#include <string>
#include <functional>   // aby fungoval bind
#include <random>       // Generatory
#include <thread>       // Multithreading
#include <vector>       // Dynamicke containery
#include <exception>
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
//#include <d3d11.h>
#include "SWU/Okno.hpp"
#include "SWU/Konzole.hpp"
#include "Kontroler3d.hpp"
#include "CustomVertex.hpp"
#include "JednoduchyVertex.hpp"
#include "TreeType.hpp"
#include "Helper.hpp"
#include "Tree.hpp"
#include "Usecka.hpp"
#include "Svetlo.hpp"
#include "globals.hpp"

namespace se
{

class EngineVyjimka: public std::exception
{
public:
    EngineVyjimka(const char* say) : zpravicka {say} {}
    virtual const char* what() const throw()
    {
        return zpravicka;
    }
private:
    const char* zpravicka;
} ;

class Engine;
using UkazatelNaFunkciEnginu = void (se::Engine::*)(float);
using MapaFunkciEnginu = std::map<std::string, UkazatelNaFunkciEnginu>;

class Engine
{
public:
    std::string prikaz;   // pouzivam k precteni zpravy (WM_QUIT, etc.)
    Engine(sw::Okno*);
    ~Engine();
    void releaseD3d();
    void priprav();
    void prectiVstupAUpravKameru() {
        prectiVstupAUpravKameru(arg);
    }
    void prectiVstupAUpravKameru(float&);
    void render3d();
    void dejKonzoli(const sk::Konzole& x){
        iKonzole = x;
        iKontroler3d.dejKonzoli(x);
    }
private:
    sw::Okno* iOkno;
    sktrl::Kontroler3d iKontroler3d;
    sk::Konzole iKonzole;   // abych mohl konzoli pouzivat vsude, to nejde
    LPDIRECT3D9 g_pD3D; // Used to create the D3DDevice
    LPDIRECT3DDEVICE9 pd3dZarizeni; // Our rendering device, lp= neco pointer, je to jenom typedef typedef struct IDirect3DDevice9 *LPDIRECT3DDEVICE9;

    bool bbClearColor = false;
    bool bwireframe = true;
    bool bosvetlovat = true;
    bool bcull = true;
    bool bflatShading = false;
    float fFOV;
    D3DXMATRIX maticeProjekce;

    MapaFunkciEnginu mapaFci;
    std::vector<t::Tree> stromy;
    std::vector<se::Usecka> usecky;
    std::vector<se::Svetlo> svetla;
    float fDalka; //0

    void pripravView();
    void pripravGeometrii();

    float arg;
    UkazatelNaFunkciEnginu najdiFunkci(const std::string&);
    void zavolejFunkci(se::UkazatelNaFunkciEnginu, float arg);

    void selfTest(float arg){
        if(arg <= 0.) arg = 1;      //  chybi argument
        for(int k = 0; k < (int)arg; ++k)
        for(auto i = mapaFci.begin(); i!=mapaFci.end(); ++i)
        {
            if(i->first == "testy")
            continue;
            iKonzole.nastavBarvuPisma(sk::fmodra);
            std::cout << "Volam: "<< i->first << std::endl;
            zavolejFunkci(i->second, arg);
        }
        nastavRychlost(50000.);
        iKonzole.nastavBarvuPisma(sk::ftmavezelena);
        std::cout << "All passed" << std::endl;

        iOkno->nastavDoPopredi();
    }
    void reset(float){
        iKonzole.nastavBarvuPisma(sk::Barva::fzluta);
        pripravView();
        pripravGeometrii();
        nastavRychlost(50000.);
        fFOV = PI/3.6;
        dejCitlivost(3);
    }
    void generujJedenStrom(float);
    void dejFov(float fov){
        fFOV = PI/fov;
    }
    void pridejStrom(float);
    void regenerujStromy(float);
    void odeberStromy(float);
    void odeberStrom(float);
    void nastavRychlost(float rychlost){
        iKontroler3d.nastavRychlost(rychlost);
    }
    void dejCitlivost(float citlivost){
        iKontroler3d.nastavCitlivost(citlivost);
    }
    void setRenderElement(float elem){
        for (auto i = stromy.begin(); i!=stromy.end(); ++i)
        {
            if(elem==0.)
            i->nastavVykreslovaciElement(t::Element::bod);
            if(elem==1. && ( (i->vemDruhStromu()).element == t::Element::bod || (i->vemDruhStromu()).element == t::Element::testValec) )
            i->nastavVykreslovaciElement(t::Element::usecka);
            if(elem==2. && (i->vemDruhStromu()).element == t::Element::usecka)
            i->nastavVykreslovaciElement(t::Element::testValec);
        }
    }
    void switchClearColor(float){
        bbClearColor = !bbClearColor;
    }
    void switchCulling(float){
        bcull = !bcull;
        if(bcull)
        pd3dZarizeni->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
        else
        pd3dZarizeni->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
    }
    void switchWireframe(float){
        bwireframe = !bwireframe;
        if (bwireframe)
            pd3dZarizeni->SetRenderState( D3DRS_FILLMODE , D3DFILL_WIREFRAME );
        else
            pd3dZarizeni->SetRenderState( D3DRS_FILLMODE , D3DFILL_SOLID );
    }
    void switchOsvetlovat(float){
        bosvetlovat = !bosvetlovat;
    }
    void switchShading(float){
        bflatShading = !bflatShading;
        if(bflatShading)
            pd3dZarizeni->SetRenderState( D3DRS_SHADEMODE, D3DSHADE_FLAT );
        else
            pd3dZarizeni->SetRenderState( D3DRS_SHADEMODE, D3DSHADE_GOURAUD );
    }
    void nerotuj(float){
        for (auto& iTree : stromy)
            iTree.nastavRotaci(0.);
    }
    void zhasniSvitilnu(float){
        (--svetla.end())->zhasni();
    }
    void rozzniSvitilnu(float){
        (--svetla.end())->rozsvit();
    }
};


}

#endif // __ENGINE_H_INCLUDED__

