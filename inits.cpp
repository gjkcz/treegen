#include "inits.h"

//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------

bool bRust=false;
float fDalka=950000.f; //0




//-----------------------------------------------------------------------------
// Name: InitGeometry()
// Desc: Creates the scene geometry
//-----------------------------------------------------------------------------
int* InitGeometry()
{
    /*while(gRndm==0)
    	gRndm=zaokrouhli(random()*1.0);
    */
    int vPocet, iPocetV=0;
    CUSTOMVERTEX* g_Vertices;

    float xoffset = -2*fDalka;
    float yoffset = -2*fDalka;
    UINT uiTime=0;
    SimpleVertex* Tvertices;
    uiTime = timeGetTime();
    for(int i = 0; i<iObsah; i++)
    {
        xoffset = (i/sqrt((float)iObsah)) * fDalka-(sqrt((float)iObsah)/2)*fDalka+random()*fDalka-fDalka*0.5;
        yoffset = (i-(i/(int)sqrt((float)iObsah)*(int)sqrt((float)iObsah)))* fDalka-(sqrt((float)iObsah)/2)*fDalka+random()*fDalka-fDalka*0.5;
        D3DXMatrixTranslation(&TMatX[i], xoffset, yoffset, 0.f);
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
        type._iRType=5;
        type._iDType=4;
        vPocet = GenerateTree(iPatra, type);
        iPatra+=bRust?1:0;
        iPocetV+=vPocet;
        i_aPocetV[i] = vPocet;
        g_Vertices = new CUSTOMVERTEX[vPocet];

        // Create the vertex buffer.
        if( FAILED( g_pd3dDevice->CreateVertexBuffer( vPocet * sizeof( CUSTOMVERTEX ),
                    0, D3DFVF_CUSTOMVERTEX,
                    D3DPOOL_DEFAULT, &g_pVB[i], NULL ) ) )
        {
            return NULL;
        }

        Tvertices = UnpackTree();
        if( FAILED( g_pVB[i]->Lock( 0, 0, ( void** )&g_Vertices, 0 ) ) )
            return NULL; //pozor do pole nejde e_fail
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
        g_pVB[i]->Unlock();
    }
    uiTime=timeGetTime()-uiTime;
    return i_aPocetV;
}

