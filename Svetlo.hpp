#ifndef __H_SVETLO_INCLUDED__
#define __H_SVETLO_INCLUDED__

namespace se
{

enum TypSvetla {
    smerove=D3DLIGHT_DIRECTIONAL, bodove=D3DLIGHT_POINT
};

class Svetlo
{
public:
    static int pocetInstanciSvetla;
    static void priprav(LPDIRECT3DDEVICE9 pd3dZarizeni){
        pd3dZarizeni->SetRenderState(D3DRS_AMBIENT, t::bila);
//    pd3dZarizeni->SetRenderState( D3DRS_LIGHTING, true );
//    pd3dZarizeni->SetRenderState( D3DRS_SHADEMODE, D3DSHADE_FLAT );
        pd3dZarizeni->SetRenderState( D3DRS_SHADEMODE, D3DSHADE_GOURAUD );
        pd3dZarizeni->SetRenderState( D3DRS_AMBIENT, 0x00202020 );
    }
    static void rozsvit(LPDIRECT3DDEVICE9 pd3dZarizeni, int ktere){
        pd3dZarizeni->LightEnable( ktere, true );
    }
    static void zhasni(LPDIRECT3DDEVICE9 pd3dZarizeni, int ktere){
        pd3dZarizeni->LightEnable( ktere, false );
    }
    Svetlo(LPDIRECT3DDEVICE9 _pzarizeni) : pzarizeni(_pzarizeni){
        rozsviceno = true;
        pzarizeni->LightEnable( pocetInstanciSvetla, rozsviceno );
        D3DXVECTOR3 vecDir;
        svetlo = new D3DLIGHT9();
        svetlo->Type = D3DLIGHT_DIRECTIONAL;
        svetlo->Diffuse.r = 0.1f;
        svetlo->Diffuse.g = 0.1f;
        svetlo->Diffuse.b = 0.1f;
        vecDir = D3DXVECTOR3( -1.f,
                              -1.0f,
                              0.f );
        D3DXVec3Normalize( ( D3DXVECTOR3* )&(svetlo->Direction), &vecDir );
        pzarizeni->SetLight( pocetInstanciSvetla, svetlo );
        citacSvetla = pocetInstanciSvetla;
        pocetInstanciSvetla++;
    }
    Svetlo(LPDIRECT3DDEVICE9 _pzarizeni, D3DCOLORVALUE barva) : pzarizeni(_pzarizeni){
        rozsviceno = true;
        pzarizeni->LightEnable( pocetInstanciSvetla, rozsviceno );
        D3DXVECTOR3 vecDir;
        svetlo = new D3DLIGHT9();
        svetlo->Type = D3DLIGHT_DIRECTIONAL;
        svetlo->Diffuse = barva;
        vecDir = D3DXVECTOR3( -1.f,
                              -1.0f,
                              0.f );
        D3DXVec3Normalize( ( D3DXVECTOR3* )&(svetlo->Direction), &vecDir );
        pzarizeni->SetLight( pocetInstanciSvetla, svetlo );
        citacSvetla = pocetInstanciSvetla;
        pocetInstanciSvetla++;
    }
    Svetlo(LPDIRECT3DDEVICE9 _pzarizeni, D3DCOLORVALUE barva, TypSvetla typ) : pzarizeni(_pzarizeni){
        rozsviceno = true;
        pzarizeni->LightEnable( pocetInstanciSvetla, rozsviceno );
        D3DXVECTOR3 vecDir;
        svetlo = new D3DLIGHT9();
        svetlo->Type = (D3DLIGHTTYPE)typ;
        svetlo->Diffuse = barva;
        vecDir = D3DXVECTOR3( -1.f,
                              -1.0f,
                              0.f );
        D3DXVec3Normalize( ( D3DXVECTOR3* )&(svetlo->Direction), &vecDir );
        pzarizeni->SetLight( pocetInstanciSvetla, svetlo );
        citacSvetla = pocetInstanciSvetla;
        pocetInstanciSvetla++;
    }
    Svetlo(LPDIRECT3DDEVICE9 _pzarizeni, D3DCOLORVALUE barva, TypSvetla typ, D3DXVECTOR3 _smer) : pzarizeni(_pzarizeni){
        rozsviceno = true;
        smer = _smer;
        pzarizeni->LightEnable( pocetInstanciSvetla, rozsviceno );
        svetlo = new D3DLIGHT9();
        svetlo->Type = (D3DLIGHTTYPE)typ;
        svetlo->Diffuse = barva;
        D3DXVec3Normalize( ( D3DXVECTOR3* )&(svetlo->Direction), &smer );
        pzarizeni->SetLight( pocetInstanciSvetla, svetlo );
        citacSvetla = pocetInstanciSvetla;
        pocetInstanciSvetla++;
    }
    ~Svetlo(){
        pzarizeni = nullptr;
    }
    void svit(){
//        light.Range = 1000.0f;
        pzarizeni->SetRenderState( D3DRS_LIGHTING, TRUE );
    }
    void svit(D3DXVECTOR3 novySmer){
        smer = novySmer;
        D3DXVec3Normalize( ( D3DXVECTOR3* )&(svetlo->Direction), &smer );
        pzarizeni->SetLight( citacSvetla, svetlo );
        pzarizeni->SetRenderState( D3DRS_LIGHTING, TRUE );
    }
    void rozsvit(){
        rozsviceno = true;
        pzarizeni->LightEnable( citacSvetla, rozsviceno );
    }
    void zhasni(){
        rozsviceno = false;
        pzarizeni->LightEnable( citacSvetla, rozsviceno );
    }
protected:
private:
    LPDIRECT3DDEVICE9 pzarizeni;
    D3DLIGHT9* svetlo;
    bool rozsviceno;
    D3DXVECTOR3 smer;
    int citacSvetla;
};



}

#endif // __H_SVETLO_INCLUDED__

