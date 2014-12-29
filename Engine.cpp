#include "Engine.hpp"
namespace se {


Engine::Engine(const sw::Okno& _okno) : okno(_okno), oInput(okno.hWnd)
{
}

Engine::~Engine()
{
    for(int i = 0; i < iObsah; i++) {
        if( treeVertexBuffers[i] != NULL )
            treeVertexBuffers[i]->Release();
    }
    if( g_pd3dDevice != NULL )
        g_pd3dDevice->Release();
    delete treeMatrix;
    delete treeVertexBuffers;
    delete aPocetVrcholuStromu;
}

void Engine::priprav()
{
    pripravView();
    pripravGeometrii();
//    oInput.prepareInputDevices(okno.hWnd);
}

void Engine::pripravView()
{
    // Create the D3D object.
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        std::cout << E_FAIL;

    // Set up the structure used to create the D3DDevice
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof( d3dpp ) );
    d3dpp.Windowed = true;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;

    g_pd3dDevice = NULL;
    // Create the D3DDevice
    if( FAILED(g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, this->okno.hWnd,
                                     D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                     &d3dpp, &g_pd3dDevice ) ) )
    {
        std::cout << E_FAIL;
        if(FAILED(g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, this->okno.hWnd,
                                        D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                        &d3dpp, &g_pd3dDevice )))
        {
            if(FAILED(g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, this->okno.hWnd,
                                            D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                            &d3dpp, &g_pd3dDevice )))
            {
                if( FAILED(g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, this->okno.hWnd,
                                                 D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                                 &d3dpp, &g_pd3dDevice ) ) )
                {
                    if(FAILED(g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, this->okno.hWnd,
                                                    D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                                    &d3dpp, &g_pd3dDevice )))
                    {
                        if(FAILED(g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_FORCE_DWORD, this->okno.hWnd,
                                                        D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                                        &d3dpp, &g_pd3dDevice )))
                        {

                        }
                    }
                }
            }
        }
    }


    // Turn off culling, so we see the front and back of the triangle
    g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );

    // Turn off D3D lighting, since we are providing our own vertex colors
    g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

    //TMatX = new D3DXMATRIXA16[iObsah];

    if( g_pD3D != NULL )
        g_pD3D->Release();
}

void Engine::pripravGeometrii()
{
    treeMatrix = new D3DXMATRIXA16[iObsah];   // array of matrices to hold the rotation and position of each tree
    treeVertexBuffers = new LPDIRECT3DVERTEXBUFFER9[iObsah]; // array of Buffers to hold vertices
    aPocetVrcholuStromu = new int[iObsah];
    fDalka=950000.f;

    int vPocet, iPocetV=0;
    CUSTOMVERTEX* g_Vertices;
    float xoffset = -2*fDalka;
    float yoffset = -2*fDalka;
    UINT uiTime=0;
    SimpleVertex* Tvertices;
    uiTime = timeGetTime();
    for(int i = 0; i<iObsah; i++)
    {
        xoffset = (i/sqrt((float)iObsah)) * fDalka-(sqrt((float)iObsah)/2)*fDalka+helper::random()*fDalka-fDalka*0.5;
        yoffset = (i-(i/(int)sqrt((float)iObsah)*(int)sqrt((float)iObsah)))* fDalka-(sqrt((float)iObsah)/2)*fDalka+helper::random()*fDalka-fDalka*0.5;
        D3DXMatrixTranslation(&treeMatrix[i], xoffset, yoffset, 0.f);
        int iTypu=8;
        int iTyp=0;
        bool bIAm = false;
        int l = 0;
        tType type;
        for(int c=0; c<3; c++)
        {
            while(!bIAm)
            {
                if (i%iTypu==l)
                {
                    bIAm=true;
                    iTyp=l;
                }
                l++;
            }
            (c==0)?(type._iSType=iTyp):((c==1)?(type._iRType=iTyp):(type._iDType=iTyp));
            iTypu=(c==0)?5:3;
            l = 0;
            bIAm = false;
        }
//        type._iRType=5;
//        type._iDType=4;

        vPocet = GenerateTree(iPatra, type);
        //iPatra+=bRust?1:0;    nejde s makro konstantou
        iPocetV+=vPocet;
        aPocetVrcholuStromu[i] = vPocet;
        g_Vertices = new CUSTOMVERTEX[vPocet];

        // Create the vertex buffer.
        if( FAILED( g_pd3dDevice->CreateVertexBuffer( vPocet * sizeof( CUSTOMVERTEX ),
                    0, D3DFVF_CUSTOMVERTEX,
                    D3DPOOL_DEFAULT, &treeVertexBuffers[i], NULL ) ) )
        {
            std::cout << NULL;
        }

        Tvertices = UnpackTree();
        if( FAILED( treeVertexBuffers[i]->Lock( 0, 0, ( void** )&g_Vertices, 0 ) ) )
            std::cout << NULL; //pozor do pole nejde e_fail
        int tempColor;
        float colorK;
        for(int x=0; x<vPocet; x++)
        {
            g_Vertices[x].x = Tvertices[x].Pos.x;
            g_Vertices[x].y = Tvertices[x].Pos.y;
            g_Vertices[x].z = Tvertices[x].Pos.z;
//			g_Vertices[x].color = 0xF000000;
            for(int b = 0; b<3; b++)
            {
                switch(b)
                {
                case 0:
                {
                    colorK = Tvertices[x].Color.z;
                    break;
                }
                case 1:
                {
                    colorK = Tvertices[x].Color.y;
                    break;
                }
                case 2:
                {
                    colorK = Tvertices[x].Color.x;
                    break;
                }
                }
                tempColor=(colorK * 255);
                g_Vertices[x].color += DWORD(tempColor*(pow(float(16),b*2)));
                //tempColor=(colorK * 255)-(int)(colorK * 255/16)*16;
            }
        }
        treeVertexBuffers[i]->Unlock();
    }
    uiTime=timeGetTime()-uiTime;

    std::cout << "Cas generovani: " << uiTime << "ms\n";
}

void Engine::prectiVstup()
{
    stav = oInput.prectiStavVstupu();
}


}
