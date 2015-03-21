#include "Tvar.hpp"
namespace se
{


Tvar::Tvar()
{
    cstmvtxVrcholy = nullptr;
    bufferVrcholu = nullptr;
    bufferIndicii = nullptr;
    paIndicie = nullptr;
}

Tvar::Tvar(D3DXMATRIX& pocatek, t::Barva barva, LPDIRECT3DDEVICE9* _pzarizeni) :  pzarizeni(*_pzarizeni)
{
    cstmvtxVrcholy = nullptr;
    bufferVrcholu = nullptr;
    bufferIndicii = nullptr;
    paIndicie = nullptr;
    D3DXMatrixRotationX(&maticeRotaceStromuX, -3.14159265358979323846/2);     // Otoci strom o -Pi kolem x
    D3DXMatrixScaling(&maticeSkalovani, 0.5f, 0.5f, 0.5f );                 // Zmensi strom na 1/2
    matice = pocatek;
    barvaUsecky = barva;
    zmenaRotace = 0.;
    rotace = 0.;
//    try {
//        if(!uzamkniPoleDoBuffru()) throw 0;
//        generujVrcholy(x, y);
//        generujIndexy( 0, 1 );
//        if(!odemkniVrcholyProCteni()) throw 0;
//    } catch (std::exception& e) {
//    }

}

Tvar::Tvar(D3DXMATRIX& pocatek, t::Barva barva, LPDIRECT3DDEVICE9* _pzarizeni, float zRot) :  pzarizeni(*_pzarizeni), zmenaRotace(zRot)
{
    cstmvtxVrcholy = nullptr;
    bufferVrcholu = nullptr;
    bufferIndicii = nullptr;
    paIndicie = nullptr;
    D3DXMatrixRotationX(&maticeRotaceStromuX, -3.14159265358979323846/2);     // Otoci strom o -Pi kolem x
    D3DXMatrixScaling(&maticeSkalovani, 0.5f, 0.5f, 0.5f );                 // Zmensi strom na 1/2
    matice = pocatek;
    barvaUsecky = barva;
//    zmenaRotace = 0.;
    rotace = 0.;
//    try {
//        if(!uzamkniPoleDoBuffru()) throw 0;
//        generujVrcholy(x, y);
//        generujIndexy( 0, 1 );
//        if(!odemkniVrcholyProCteni()) throw 0;
//    } catch (std::exception& e) {
//    }

}

//void Tvar::generujVrcholy(D3DXVECTOR3& x, D3DXVECTOR3& y)
//{
//        int citacVrcholu = 0;
//        cstmvtxVrcholy[citacVrcholu].x = x.x;
//        cstmvtxVrcholy[citacVrcholu].y = x.y;
//        cstmvtxVrcholy[citacVrcholu].z = x.z;
//        cstmvtxVrcholy[citacVrcholu].color = barvaUsecky;
//        citacVrcholu++;
//
//        cstmvtxVrcholy[citacVrcholu].x = y.x;
//        cstmvtxVrcholy[citacVrcholu].y = y.y;
//        cstmvtxVrcholy[citacVrcholu].z = y.z;
//        cstmvtxVrcholy[citacVrcholu].color = barvaUsecky;
//        citacVrcholu++;
//}
//
//void Tvar::generujIndexy(int a, int b)
//{
//    paIndicie[0] = a;
//    paIndicie[1] = b;
//}

void Tvar::znicBuffery()
{
    if( (bufferIndicii) != nullptr ) {
        (*bufferIndicii)->Release();
        (*bufferIndicii) = NULL;
        delete bufferIndicii;           // release the memory that had been used for holding pointerToBuffer o_|, ta prostredni se alokuje dyn
    }
    if( bufferVrcholu != nullptr ) {
        (*bufferVrcholu)->Release();
        (*bufferVrcholu) = NULL;
        delete bufferVrcholu;
    }
}

void Tvar::znicOstatniPointry()
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
    }
}

Tvar::~Tvar()
{
#ifdef TREEVERBOSE
    std::cout << "Strom being destroyed!" << std::endl;

#endif // defined
    znicOstatniPointry();
    znicBuffery();
}

void Tvar::aktualizujMatici()
{
    if (zmenaRotace > 0.f)
        rotace += zmenaRotace;
    else
        rotace = 0.f;
    D3DXMatrixRotationZ(&maticeRotaceStromuZ, rotace);

    world = maticeRotaceStromuZ * matice * maticeSkalovani * maticeRotaceStromuX;
}

void Tvar::vykresli() const         // const fcion, so it cant change anything in our object
{
    pzarizeni->SetFVF( D3DFVF_VrcholB );
    pzarizeni->SetRenderState( D3DRS_LIGHTING, false );
    pzarizeni->SetTransform( D3DTS_WORLD, &world );
    pzarizeni->SetStreamSource( 0, (*bufferVrcholu), 0, sizeof( VrcholB ) );
//        pzarizeni->SetIndices(*bufferIndicii);
//        pzarizeni->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 40);
        pzarizeni->SetIndices(*bufferIndicii);
        /*pzarizeni->DrawIndexedPrimitive( D3DPT_LINELIST, // PrimitiveType
                                         0,                  // BaseVertexIndex
                                         0,                  // MinIndex
                                         pocetVrcholu,                  // NumVertices
                                         0,                  // StartIndex
                                         pocetElementu );                // PrimitiveCount*/

//    case Tvar: {
        pzarizeni->DrawIndexedPrimitive( D3DPT_LINELIST, // PrimitiveType
                                         0,                  // BaseVertexIndex
                                         0,                  // MinIndex
                                         2,                  // NumVertices
                                         0,                  // StartIndex
                                         1 );                // PrimitiveCount
}

bool Tvar::vytvorBufferVrcholu()
{
    bool vysledek;
#ifdef TREEVERBOSE
//    std::cout << "alokejme nejprve nejake misto pro buffer..." << std::endl;
#endif // defined
    try {
        bufferVrcholu = new LPDIRECT3DVERTEXBUFFER9;
    } catch (std::exception& e) {
    }
    try {
        if( FAILED( pzarizeni->CreateVertexBuffer( 2 * sizeof( VrcholB ),
                    0, D3DFVF_VrcholB,
                    D3DPOOL_DEFAULT, bufferVrcholu, NULL ) ) ) {
            vysledek = false;
        } else {
            vysledek = true;
#ifdef TREEVERBOSE
//        std::cout << "Alokace buffru Ok." << std::endl;
#endif // defined
        }
    } catch (std::exception& e) {
    }

    return vysledek;
}

bool Tvar::vytvorBufferIndicii()
{
    bool vysledek = true;

//    case Tvar:
        try {
            bufferIndicii = new LPDIRECT3DINDEXBUFFER9;     // dyn alc pointer
        } catch (std::exception& e) {
            vysledek = false;
        }
        if( FAILED( pzarizeni->CreateIndexBuffer( 2 * sizeof(long),
                    D3DUSAGE_WRITEONLY , D3DFMT_INDEX32, D3DPOOL_DEFAULT,
                    bufferIndicii, NULL ) ) ) {
            vysledek = false;
        }


    return vysledek;
}

bool Tvar::uzamkniPoleDoBuffru()
{
    bool vysledek;
    // Create the vertex buffer.
    if( vytvorBufferVrcholu() )    // Je treba znat pocet vrcholu
        if( FAILED( (*bufferVrcholu)->Lock( 0, 0, ( void** )&cstmvtxVrcholy, 0 ) ) ) {
            vysledek = false;
        } else
            vysledek = true;
    else {
        vysledek = false;
    }
    // Create index buffer.
        if( vytvorBufferIndicii() )
            if( FAILED( (*bufferIndicii)->Lock(0, 0, ( void** )&paIndicie, 0) ) ) {
                vysledek = false;
            } else
                vysledek = true;
        else {
            vysledek = false;
        }
    return vysledek;
}

bool Tvar::odemkniVrcholyProCteni()
{
    bool vysledek;
    if(FAILED ((*bufferVrcholu)->Unlock())) {
        vysledek = false;
    } else
        vysledek = true;

        if(FAILED ((*bufferIndicii)->Unlock())) {
            vysledek = false;
        } else
            vysledek = true;
    return vysledek;
}



}
