
#include "start.h"
SimpleVertex* Tvertices; 
int vPoradi = 0;
int gnVetvi = 0;int iReality;int iGuess;float gfDensity;float gfDensityR;
XMFLOAT4 Barva;
float per, gonx, height;
int sum;int countEm; 
bool bVlnit=false;
void RostClanek(float r, float radiusZ, float sklony, float sklonz, float Dens, float posunX, float posunY, float posunZ);
void RostClanekRozdvojeni(float r, float rp, float r2, float radiusZ, float sklony, float sklonX1, float sklonY1, float sklonz,float rotace, float Dens, float Uzk, float posunX, float posunY, float posunZ, float tU);
void RostOsy();

struct objRust
{
	float r;
	float sklon;
	float rotace;
};

struct paramsVetve
{
	XMFLOAT3 x;
	objRust r;objRust rT;
	bool k;
	float d;
	float aR;
	float m;
	float de;
};
paramsVetve* gpVs;


struct tuplParamsVetve
{
	paramsVetve p_0;
	paramsVetve p_1;
};

void RostVetev(paramsVetve);
tuplParamsVetve RostRozdvojeni(XMFLOAT3 start,objRust Rust,objRust RustTo,float delka,float AxeRotace, float mezera, float dens);
paramsVetve generateParams(paramsVetve parent, int strana,tType _tType);


paramsVetve generateParams(paramsVetve parent, int strana,tType _tType)
{

	float PI = 3.14159265358979323846;
	float ample = 1.f;
	float OrigoX, OrigoY, OrigoZ, afterY;
	float posunX, posunY, posunZ;
	float rp, uzk;
	float k=0.f;
	paramsVetve pVs;

	//pVs.r = parent.rT;
	afterY = cos(parent.rT.sklon)*(floor(parent.d/parent.m)*parent.m);//sin(atan((floor(parent.d/parent.m)*parent.m)/OrigoY)+parent.rT.sklon)*(OrigoY/cos(atan((floor(parent.d/parent.m)*parent.m)/OrigoY)));
	posunZ = parent.x.z+sin(parent.rT.sklon)*(floor(parent.d/parent.m)*parent.m);//cos(atan((floor(parent.d/parent.m)*parent.m)/OrigoY)+parent.rT.sklon)*(OrigoY/cos(atan((floor(parent.d/parent.m)*parent.m)/OrigoY)))+parent.x.z;
	posunY = parent.x.y+cos(parent.rT.rotace)*afterY;//cos(atan(afterY/OrigoX)+parent.rT.rotace)*(OrigoX/cos(atan(afterY/OrigoX)))+parent.x.y;
	posunX = parent.x.x+sin(parent.rT.rotace)*afterY;//sin(atan(afterY/OrigoX)+parent.rT.rotace)*(OrigoX/cos(atan(afterY/OrigoX)))+parent.x.x;
	pVs.x.z = posunZ;
	pVs.x.y = posunY;
	pVs.x.x = posunX;
	pVs.k = false;
	pVs.m = parent.m;

	switch(_tType._iSType)
	{
	case 0:  
		{
			pVs.r.sklon = ((strana%2 == 0)?(random()*parent.rT.sklon):(random()*PI/2));
		}
		break;
	case 1:  
		{
			k=6;
			pVs.r.sklon = ((strana%2 == 0)?(parent.rT.sklon-k*PI/180):(parent.rT.sklon-k*PI/180));
		}
		break;
	case 2:  
		{
			pVs.r.sklon = ((strana%2 != 0)?(random()*parent.rT.sklon):(random()*PI/2));
		}
		break;
	case 3:  
		{
			pVs.r.sklon = ((strana%2 == 0)?(random()*PI/4):(random()*PI/2));
		}
		break;
	case 4:  
		{
			pVs.r.sklon = ((strana%2 == 0)?(random()*PI/4+PI/4):(random()*PI/2));
		}
		break;
	case 5:  
		{
			pVs.r.sklon = ((strana%2 == 0)?(random()*PI/4+PI/4):(random()*PI/4+PI/4));
		}
		break;
	case 6:  
		{
			pVs.r.sklon = ((strana%2 == 0)?(PI/8):(PI/3));
		}
		break;
	case 7:  
		{
			k=6;
			pVs.r.sklon = ((strana%2 == 0)?(parent.rT.sklon-k*PI/180):(parent.rT.sklon-k*PI/180));
		}
		break;
	case 8:  
		{
			k=(parent.rT.sklon==PI/2)?35.5:k=1.5;
			pVs.r.sklon = ((strana%2 == 0)?(parent.rT.sklon-k*PI/180):(parent.rT.sklon-k*PI/180));
		}
	case 9:  
		{
			k=((parent.rT.sklon==PI/2)?(35.5):(500000.f/parent.x.z));
			pVs.r.sklon = ((strana%2 == 0)?(parent.rT.sklon-k*PI/180):(parent.rT.sklon-k*PI/180));
		}
	case 10:  
		{
			k=((parent.rT.sklon==PI/2)?(-95.0f):(random()*15.f));
			pVs.r.sklon = ((strana%2 == 0)?(parent.rT.sklon+k*PI/180):(parent.rT.sklon+k*PI/180));
		}

	case 11:  
		{
			k=((parent.rT.sklon==PI/2)?(-45.0f):(random()*2.f));
			pVs.r.sklon = ((strana%2 == 0)?(parent.rT.sklon+k*PI/180):(parent.rT.sklon+k*PI/180));
		}


	default:
		{

		}
		break;
	}
		pVs.rT.sklon = pVs.r.sklon;


		switch(_tType._iRType)
	{
	case 0:  
		{
			pVs.r.rotace = ((strana%2 == 0)?
				(parent.rT.rotace+((parent.rT.sklon==PI/2)?0:(atan(cos(parent.rT.sklon)*sin(pVs.r.sklon)/cos(pVs.r.sklon))))-((parent.rT.sklon==PI/2)?(PI/2):(PI/2))):
				(parent.rT.rotace-((parent.rT.sklon==PI/2)?0:(atan(cos(parent.rT.sklon)*sin(pVs.r.sklon)/cos(pVs.r.sklon))))+((parent.rT.sklon==PI/2)?(PI/2):(PI/2))) );
		}
		break;
	case 1:  
		{
			pVs.r.rotace = ((strana%2 == 0)?
				(parent.rT.rotace+((parent.rT.sklon==PI/2)?0:(atan(cos(parent.rT.sklon)*sin(pVs.r.sklon)/cos(pVs.r.sklon))))-((parent.rT.sklon==PI/2)?(PI/2):(PI/4))):
				(parent.rT.rotace-((parent.rT.sklon==PI/2)?0:(atan(cos(parent.rT.sklon)*sin(pVs.r.sklon)/cos(pVs.r.sklon))))+((parent.rT.sklon==PI/2)?(PI/2):(PI/4))) );
		}
		break;
	case 2:  
		{
			pVs.r.rotace = ((strana%2 == 0)?
				(parent.rT.rotace+((parent.rT.sklon==PI/2)?0:(atan(cos(parent.rT.sklon)*sin(pVs.r.sklon)/cos(pVs.r.sklon))))-((parent.rT.sklon==PI/2)?(PI/2):(random()*PI/2))):
				(parent.rT.rotace-((parent.rT.sklon==PI/2)?0:(atan(cos(parent.rT.sklon)*sin(pVs.r.sklon)/cos(pVs.r.sklon))))+((parent.rT.sklon==PI/2)?(PI/2):(PI/4))) );
		}
		break;
	case 3:  
		{
			pVs.r.rotace = ((strana%2 == 0)?
				(parent.rT.rotace-((parent.rT.sklon==PI/2)?(PI/2):(random()*PI/2))):
				(parent.rT.rotace+((parent.rT.sklon==PI/2)?(PI/2):(PI/4))) );
		}
		break;
	case 4:  
		{
			pVs.r.rotace = ((strana%2 == 0)?
				(parent.rT.rotace-((parent.rT.sklon==PI/2)?(PI/2):(random()*PI+PI/2))):
				(parent.rT.rotace+((parent.rT.sklon==PI/2)?(PI/2):(0))) );
		}
		break;
	case 5:  
		{
			pVs.r.rotace = ((strana%2 == 0)?
				(parent.rT.rotace+((parent.rT.sklon==PI/2)?(PI/2):(random()*PI/2))):
				(parent.rT.rotace-((parent.rT.sklon==PI/2)?(PI/2):(random()*PI/2))) );
		}
		break;

	default:
		{

		}
		break;
	}
			pVs.rT.rotace = pVs.r.rotace;

		switch(_tType._iDType)
	{
	case 6:  
		{
			pVs.d = ((strana%2 == 0)?(random()*19000+18277):(random()*19000+18277));
		}
		break;
	case 1:  
		{
			pVs.d = ((strana%2 == 0)?(0.9*parent.d):(random()*19000+18277));
		}
		break;
	case 2:  
		{
			pVs.d = ((strana%2 == 0)?(0.9*parent.d):(0.98*parent.d));
		}
		break;
	case 3:  
		{
			pVs.d = ((strana%2 == 0)?(0.998*parent.d):(0.998*parent.d));
		}
		break;
	case 4:  
		{
			pVs.d = ((strana%2 == 0)?((random()*0.1+0.9)*parent.d):((random()*0.02+0.98)*parent.d));
		}
		break;


	default:
		{
			pVs.d = ((strana%2 == 0)?(0.998*parent.d):(0.998*parent.d));
		}
		break;
	}
		if(pVs.d<=pVs.m)			//this MUSTNT happen!!!
			pVs.d=2*pVs.m;

	/*if(strana%2 == 0)				//když je sudá
			{	
				//pVs.r.sklon = parent.rT.sklon+k*PI/180;//-(zaokrouhli(random())*0+10)*PI/180;//random()*5*PI/180;//0.2f*pow(gonx*PI/180,2) ;
				//pVs.r.sklon =  parent.rT.sklon-k*PI/180;
				//pVs.r.sklon = random()*parent.rT.sklon;
				//pVs.r.rotace = parent.rT.rotace+((parent.rT.sklon==PI/2)?0:(atan(cos(parent.rT.sklon)*sin(pVs.r.sklon)/cos(pVs.r.sklon))))-((parent.rT.sklon==PI/2)?(PI/2):(PI/2));//+PI/2;//  + random()*90*PI/180;
				//pVs.rT.sklon = pVs.r.sklon;//random()*5*PI/180;//0.2f*pow(gonx*PI/180,2) ;
				//pVs.rT.r = parent.rT.r - random()*1;
				//pVs.d =random()*19000+18277; 
				//pVs.aR = 0;
				pVs.m = parent.m;
				//pVs.de = parent.de;
			}
			else // jinak je licha
			{
				//pVs.r = parent.rT;
				//pVs.aR = 0;
				pVs.m = parent.m;
				//pVs.de = parent.de;
				//pVs.r.sklon = parent.rT.sklon+k*PI/180;//45*PI/180-(zaokrouhli(random())*0+45)*PI/180;//- random()*5*PI/180;//0.2f*pow(gonx*PI/180,2) ;
				//pVs.r.sklon =  parent.rT.sklon-k*PI/180;
				//pVs.r.sklon = random()*PI/2;
				//pVs.r.rotace = parent.rT.rotace-((parent.rT.sklon==PI/2)?0:(atan(cos(parent.rT.sklon)*sin(pVs.r.sklon)/cos(pVs.r.sklon))))+((parent.rT.sklon==PI/2)?(PI/2):(PI/2));//+PI/2;//  - random()*90*PI/180;

				//pVs.rT.sklon = pVs.r.sklon;//- random()*5*PI/180;//0.2f*pow(gonx*PI/180,2) ;
				//pVs.rT.r = parent.rT.r - random()*1;
				//pVs.d =random()*20000+18277;
			}*/

	return pVs;
}

int GenerateTree(int iPater,tType _tType)
{
	float PI = 3.14159265358979323846;
	//
	//
	//NAPLNeni
	//
	//
	vPoradi = 0;
	int r=0,b=0,g=0;
	/*r = GenerateRndm(0,2);
	g = GenerateRndm(0,2);
	b = GenerateRndm(0,2);*/
	/*UINT uiTime=0;
	while(uiTime<1000){
	uiTime = timeGetTime();
	while(r==0||g==0||b==0){*/

	//r = zaokrouhli(random());
	//g = zaokrouhli(random());
	//b = zaokrouhli(random());
	if(zaokrouhli(random())==1)
	{r=1;g=1;b=0;}
	else
	{r=1;g=1;b=0;}
	//r=1;g=0;b=0;//boruvkova
	//r=0;g=1;b=0;//zelenomodry spodek, lososovo zluty vrsek
	//r=0;g=0;b=1;//ugly
	//r=1;g=1;b=0;//fire
	//r=1;g=0;b=1;//fialovo modry
	//r=1;g=1;b=1;//vybledla zelena
	//r=0;g=0;b=0;//sediva
	/*}
	uiTime=timeGetTime()-uiTime;}*/

	//r=1;g=1;b=0;
	sum = b+2*g+4*r;
	switch(sum)
	{
	case 0:
		{
			Barva = XMFLOAT4(0.f,0.f,0.f,1.f);
			break;
		}
	case 1:
		{
			Barva = XMFLOAT4(0.f,0.f,1.f,1.f);
			break;
		}
	case 2:
		{
			Barva = XMFLOAT4(0.f,1.f,0.f,1.f);
			break;
		}
	case 3:
		{
			Barva = XMFLOAT4(0.f,1.f,1.f,1.f);
			break;
		}
	case 4:
		{
			Barva = XMFLOAT4(1.f,0.f,0.f,1.f);
			break;
		}
	case 5:
		{
			Barva = XMFLOAT4(1.f,0.f,1.f,1.f);
			break;
		}
	case 6:
		{
			Barva = XMFLOAT4(1.f,1.f,0.f,1.f);
			break;
		}
	case 7:
		{
			Barva = XMFLOAT4(1.f,1.f,1.f,1.f);
			break;
		}
	}
	//opakuj kolikrat chces rozdvojit
	int n = 1;
	//GenerateRndm(4,4);
	int pocetV = 0;int pocetVKT = 0;byte* klic;int vCount=0;
	paramsVetve parentPv;
	parentPv.k = false;

	int k = integratePower(2,iPater);
	klic = new byte[k];
	for(int x = 0; x<k; x++)
	{
		klic[x] = 0x0000;
	}

	

	// pøeskoèí nultou
	for(int z = 0; z<iPater; z++)	//opakuj pro každou z øad ps>od jedné pøeskoèí nultou
	{
		n=pow(float(2), z);
		for(int x = 0; x<n; x++) // opakuj pro každou z jednotlivých vìtví
		{
			if(klic[integratePower(2,z)+x] == 0x0000) //když bude koncová, nebo z poslední øady, a zároveò její parent není k
			{
				if(iPater-z==2){
					klic[integratePower(2,z+1)+2*x]=0x0001;
					klic[integratePower(2,z+1)+2*x+1]=0x0001;
				}
				else{
					if(z<2 && (integratePower(2,z)+x)%2==0){
						klic[integratePower(2,z+1)+2*x]=0x0000;
						klic[integratePower(2,z+1)+2*x+1]=0x0000;
					}
					else if(zaokrouhli(random()*6)==1){
						klic[integratePower(2,z+1)+2*x]=0x0001;
						klic[integratePower(2,z+1)+2*x+1]=0x0001;
					}
					else if(zaokrouhli(random()*6)==1){
						klic[integratePower(2,z+1)+2*x]=0x0001;
						klic[integratePower(2,z+1)+2*x+1]=0x0000;
					}
					else if(zaokrouhli(random()*6)==1){
						klic[integratePower(2,z+1)+2*x]=0x0000;
						klic[integratePower(2,z+1)+2*x+1]=0x0001;
					}
					else{
						klic[integratePower(2,z+1)+2*x]=0x0000;
						klic[integratePower(2,z+1)+2*x+1]=0x0000;
					}
				}
			}
			else
			{		//když bude parent koncový
				if(iPater-z>1){
				klic[integratePower(2,z+1)+2*x]=0x0002;
				klic[integratePower(2,z+1)+2*x+1]=0x0002;}
			}
		}
	}

	int p = 0;int o = 0;
	for(int h = 0; h<k; h++)
	{
		if(klic[h]==0x0000)
			p++;
		else if(klic[h]==0x0001)
			o++;
	}
	gpVs = new paramsVetve[p+o];
	for(int x = 0; x<p+o; x++)
	{ 
		gpVs[x].k = false;
	}
	gpVs[0].r.rotace= 0;
	gpVs[0].aR = 0;//rotace;
	gpVs[0].r.sklon = PI/2;//-89*PI/180;
	gpVs[0].rT.rotace= 0;
	gpVs[0].rT.sklon = PI/2;//+1*PI/180;//-89*PI/180;
	//gpVs[0].d = GenerateRndm(77*iPater,77*iPater)/1.f; //177max delka *pocet pater=maximalni vyska koruny
	gpVs[0].d = random()*(100000+1111*iPater)+11111*iPater;
	//gpVs[0].r.r = GenerateRndm(0.999*(iPater-1)+20,0.999*(iPater-1)+20);
	//gpVs[0].rT.r =gpVs[0].r.r * (GenerateRndm(111,155)/200.f);
	gpVs[0].r.r = 0.999*(iPater-1)+555;
	gpVs[0].rT.r = gpVs[0].r.r *  (random()*1+0.5)/10.f;
	gpVs[0].de =  50.f* PI/180;
	gfDensity=gpVs[0].de;
	gfDensityR= gpVs[0].r.r;
	gpVs[0].m =  1100.5f;//(2*PI*gpVs[0].r.r)/(360/(gpVs[0].de/(PI/180)));
	per = 2*PI/40*gpVs[0].m;
	gpVs[0].x.x = 0.0f;
	gpVs[0].x.y = 0.0f;
	gpVs[0].x.z = 0.0f;
	

	pocetV++;
	
	for(int z = 0; z<iPater; z++)	//opakuj pro každou z øad ps>od jedné pøeskoèí nultou
	{

		n=pow(float(2), z);
		for(int x = 0; x<n; x++) // opakuj pro každou z jednotlivých vìtví
		{
			if(klic[integratePower(2,z)+x] == 0x0000) //když bude koncová, nebo z poslední øady, a zároveò její parent není k
			{
				gpVs[pocetV] = generateParams(gpVs[integratePower(2,z)+x - pocetVKT], 0, _tType);
				if(klic[integratePower(2,z+1)+2*x]==0x0000)
				{
					gpVs[pocetV].k = false;
				}
				else
				{
					gpVs[pocetV].k = true;					
				}
				pocetV++;

				gpVs[pocetV] = generateParams(gpVs[integratePower(2,z)+x - pocetVKT], 1, _tType);
				if(klic[integratePower(2,z+1)+2*x+1]==0x0000)
				{
					gpVs[pocetV].k = false;
				}
				else
				{
					gpVs[pocetV].k = true;					
				}
				pocetV++;
			}
			else if(klic[integratePower(2,z)+x] == 0x0002)
			{		//když bude parent koncový
				pocetVKT+=1;
			}
		}
	}
	
	//spocteni vX
	int iVx=0;float Uzk=0;float rp=0;
	float iVxT = 0;float l=0;float v=0;
	float fRpDens;
	for(int m = 0; m<p+o; m++)
	{
		if(gpVs[m].k == false)
		{
			iVx += (1) * int(gpVs[m].d/gpVs[m].m);//++++++
		}
		else
		{
			iVx += (1) * int(gpVs[m].d/gpVs[m].m);
		}
	}
	
	//iVx=1000000;
	
	Tvertices = new SimpleVertex[iVx];
	for(int f = 0; f<pocetV; f++) //unpacking
	{
		RostVetev(gpVs[f]);
	/*r = GenerateRndm(0,2); colors!!!
	g = GenerateRndm(0,2);
	b = GenerateRndm(0,2);
	//r=1;g=1;b=0;
	sum = b+2*g+4*r;*/
	}

	//RostOsy();
	//RostVetev(Start, End, Rust,RustTo,false, delka, axerotace, mezera, dens);
	//Start.z += 20;


	/*Start.z = 0.02*10 * 110;
	for (float i = 10.f; i>1.0;i-=1.f)
	{
	//Start.z += 0.02*i *100;
	RostRozdvojeni(Start, End, sqrt(i), delka, sklon, rotace);
	Start.z = 0.02*i *100;
	}*/
	
	return iVx;
}
SimpleVertex* UnpackTree()
{
	return Tvertices;
}

void RostVetev(paramsVetve pV)
{

	//RustTo = Rust;
	float PI = 3.14159265358979323846;
	float ample;//, per; //radius krouceniaa
	float sklony = 0.f; //=uhel v rad, sklonx
	float radiusZ = 0;
	float sklonz = 0;
	float posunX, posunY, posunZ;
	posunX = 0.f;
	posunY = 0.f;
	posunZ = 0.f;
	float Zkoord = 0.0f;
	ample= 1.f;
	//per = 2*PI/40.f;
	sklonz = 0;
	float OrigoY = 0.f;
	float afterY = 0.f;
	float OrigoX = 0.f;
	float OrigoZ = 0.f;
	float Rorigin = pV.r.r;
	objRust TempRust = pV.r;
	float xAmp=1, yAmp=0;
	//pV.m = (2*PI*TempRust.r)/(360/(pV.de/(PI/180))); //360...obvod 1 stupne..
	//pV.r.sklon=-PI/4;
	//pV.rT.sklon=-PI/4;
	if(pV.k)
		pV.rT.r = 0.01f;
	else
	{
	}
	for (float x = 0.f; x+1.f< pV.d/pV.m; x+=1.f)
	{
		//mezera = (2*PI*TemppV.r.r)/90; //360...obvod 1 stupne..
		TempRust.r += (pV.rT.r -pV.r.r)/floor(pV.d/pV.m);
		TempRust.rotace += (pV.rT.rotace-pV.r.rotace)/floor(pV.d/pV.m);
		TempRust.sklon += (pV.rT.sklon - pV.r.sklon)/floor(pV.d/pV.m);

		//TempRust.sklon = PI/4+sin(3*OrigoZ*PI/180)/10;
		//TempRust.rotace = PI/4;
		sklony =TempRust.sklon-PI/2;
		sklonz =  -TempRust.rotace;
		
		//sklony = PI/2 +TempRust.sklon;
		//sklonz = PI/2 -TempRust.rotace;
		OrigoZ+=pV.m;
		
		//OrigoX = (2*xAmp+1)+cos(PI/20*(int)OrigoZ+PI/80)*xAmp;  // to je ten problem>kedysin nabude0tak se nasledujici vyrazy z nejakeho duvodu nevyhodnoti
		//OrigoY = (2*yAmp+1)+sin(PI/20*(int)OrigoZ)*yAmp;
		
		OrigoX = bVlnit?((2*xAmp+1)+cos(PI/20*(int)OrigoZ+PI/80)*xAmp):0;
		OrigoY = bVlnit?((2*yAmp+1)+sin(PI/20*(int)OrigoZ)*yAmp):0;
		//Barva.x=abs((OrigoX-(2*xAmp+1))/xAmp)+1-abs((OrigoX-(2*xAmp+1))/xAmp);//MANUAL OVERRIDE
		//Barva.y=abs((OrigoX-(2*xAmp+1))/xAmp);
		//Barva.z=0.f;
		
			afterY=cos(TempRust.sklon)*OrigoZ;
			posunZ=pV.x.z+sin(TempRust.sklon)*OrigoZ;
			posunY=pV.x.y+cos(TempRust.rotace)*afterY;
			posunX=pV.x.x+sin(TempRust.rotace)*afterY;
			//Barva.x =0.f;//MANUAL OVERRIDE
			//Barva.y=1.f;
			//Barva.z=0.f;
		
		
		countEm=vPoradi;
		
		RostClanek(TempRust.r, radiusZ, sklony, sklonz, pV.de, posunX, posunY, posunZ);
		
		switch(sum)
		{
		case 0:
			{
				Barva.x+=0.01;
				Barva.y+=0.01;
				Barva.z+=0.01;
				break;
			}
		case 1:
			{

				Barva.y+=0.1;
				Barva.z-=0.001;
				break;
			}
		case 2:
			{

				Barva.z+=0.01;
				Barva.y-=0.001;
				break;
			}
		case 3:
			{

				Barva.x+=0.01;
				Barva.y-=0.001;
				Barva.z-=0.001;
				break;
			}
		case 4:
			{

				Barva.x-=0.001;
				Barva.z+=0.01;
				break;
			}
		case 5:
			{

				Barva.x-=0.001;
				Barva.y+=0.01;
				break;
			}
		case 6:
			{								
				Barva.y-=0.0001;			
				break;
			}
		case 7:
			{

				Barva.x-=0.001;
				Barva.z-=0.001;
				break;
			}
		}
	}

	afterY=cos(TempRust.sklon)*OrigoZ;
	posunZ=pV.x.z+sin(TempRust.sklon)*OrigoZ;
	posunY=pV.x.y+cos(TempRust.rotace)*afterY;
	posunX=pV.x.x+sin(TempRust.rotace)*afterY;
	pV.x.x = posunX;
	pV.x.y = posunY;
	pV.x.z = posunZ;
	
	
	
	//AxeRotace += PI/2;//- rotace anuluje axerotaci<<<<<
	//rotace += PI/2;
	//r-=0.5;
	gonx = OrigoZ;
	if(/*start.z < height && gnVetvi > 0 && start.z > 0.f &&*/!pV.k) //neni symetrické, chybí multithreading :D jiz hotovo
	{
		//gnVetvi--;
		/*Barva.x=1.f;
		Barva.y=0.f;
		Barva.z=0.f;
		//for(int x=0;x<180;x++)
			//RostClanek(TempRust.r, radiusZ, x*PI/180, sklonz, pV.de/30, posunX, posunY, posunZ);
		Barva.x=0.f;
		Barva.y=1.f;
		Barva.z=0.f;*/
		//for(int x=0;x<180;x++)
			//RostClanekRozdvojeni(TempRust.r,0.3/*rp*/, TempRust.r/*r2vneporadku*/, 0/*nic*/, x*PI/180/*inklinace k z*/,0/*nic*/,0/*nic*/, x*PI/180/*rotacekolemz*/, PI/4/*rotace kolem sve osy*/, pV.de/30/*hustota30*vice */, TempRust.r-0.1/*zalomeni*/, posunX, posunY, posunZ, 0.f);
		
		//for(int x=0; x<110; x++)
			//RostClanekRozdvojeni(TempRust.r,0.3/*rp*/, TempRust.r/*r2vneporadku*/, 0/*nic*/,0/*nic*/,0/*nic*/,0/*nic*/, 0/*nic*/, 0/*nic*/, pV.de/30/*hustota30*vice */, TempRust.r-0.5/*zalomeni*/, posunX, posunY, posunZ + x*0.1f, 0.f);
		
		//return RostRozdvojeni(pV.x,TempRust,pV.rT, pV.d,pV.aR, pV.m, pV.de);
	}
	else
	{
	}

}

tuplParamsVetve RostRozdvojeni(XMFLOAT3 start,objRust Rust,objRust RustTo,float delka,float AxeRotace, float mezera, float dens)
{
	float PI = 3.14159265358979323846;						
	float rp = 0.0f; //radius prechodu
	float r2 = 0.0f; //radius															VŠECHNO JSOU RADIÁNY
	float rp2 = rp; //radius prechodu 
	float ample;//, per; //radius krouceni
	float sklony = 0.f; //=uhel v rad, sklonx
	float radiusZ = 0;
	float sklonX1 = 0.f; //=uhel v rad, sklonx
	float sklonY1 = 0;
	float sklonz = 0;
	float Uzk; //uzkost
	XMFLOAT3 start1;
	objRust Rust1, Rust2;
	Rust1 = Rust;
	Rust2 = Rust;
	float AxeRotace1 = AxeRotace;
	float posunX, posunY, posunZ;
	posunX = 0.f;
	posunY = 0.f;
	posunZ = 0.f;
	float	Zkoord = 0.0f;
	Uzk = 0.0f;
	rp=0.f;
	rp2=rp;
	float tU = 1.f;
	sklonz = 0;
	float OrigoY = 0.f;
	float afterY = 0.f;
	float OrigoX = 0.f;
	float OrigoZ = 0; //tímto pøetrvává vlnová funkce z vìtve
	float Xorigin = 0;//start.x;
	float Yorigin = 0;//start.y;
	float Rorigin = Rust.r;
	bool konec = false;
	r2=Rorigin;
	sklony =Rust.sklon-PI/2;
	sklonz =-Rust.rotace;
	ample= 1.f;
	objRust TempRust = Rust;
	/*Barva.x=1.f;//MANUAL OVERRIDE
	Barva.y=0.f;
	Barva.z=0.f;*/
	for (float x = 0.f; x<= 110.f; x+=1.f)
	{
		//TempRust.r += (RustTo.r -Rust.r)/(110);
		//TempRust.rotace += (RustTo.rotace-Rust.rotace)/(110);
		//TempRust.sklon += (RustTo.sklon - Rust.sklon)/(110);
		//r = (sqrt((float)1+4*x)-1)/2;							//sklenice kvadratick
		Uzk += Rust.r* 0.0079f;
		OrigoZ+= Rust.r* 0.02f;
		gonx += Rust.r* 0.02f;
		afterY=cos(TempRust.sklon)*OrigoZ;
		posunZ=start.z+sin(TempRust.sklon)*OrigoZ;
		posunY=start.y+cos(TempRust.rotace)*afterY;
		posunX=start.x+sin(TempRust.rotace)*afterY;
		RostClanekRozdvojeni(Rust.r, rp, r2, radiusZ, sklony,sklonX1,sklonY1, sklonz, AxeRotace, dens, Uzk, posunX, posunY, posunZ, tU);
		tU-=1.f;
		rp=0.1*Rust.r;
		rp2=rp;
	}

	tuplParamsVetve tupla;

	return tupla;
	/*
	if(stridat)
	{
	stridat=!stridat;
	if(GenerateRndm(0,9) == 1 | gnVetvi <= 0)
	konec = true;
	delka = GenerateRndm(222,555)/10.f; //TAHLE DZLKA IS MISPLACING THE VETEVSTARTPOS... 333 999/10.F no..ne
	//gnVetvi--;
	gnVetvi--;
	RostVetev(start1, ending, Rust, Rust1,konec, delka,AxeRotace1, mezera, dens);

	if(GenerateRndm(0,9) == 1 | gnVetvi <= 0)
	konec = true;
	delka = GenerateRndm(222,555)/10.f; 
	gnVetvi--;
	RostVetev(start, ending, Rust, Rust2, konec, delka,AxeRotace1, mezera, dens);  //je to tim ye prekalkulaci pocitam se starymi daty je to v startu

	}
	else
	{*/
	//}

	//
	//ZÁVÌREM: BYL TO GONX KDO SE STAÈIL ZMÌNIT PØI ÈEKACÍ SMYÈCE GENERATORU
	//
	//
}

void RostClanek(float r, float radiusZ, float sklony, float sklonz, float Dens, float posunX, float posunY, float posunZ)
{
	float Zkoord = 0.0f;
	float PI = 3.14159265358979323846;
	float  OrigoX, OrigoY, posX, posY, posZ;
	//
	//NAPLNeni
	//

	float iVx = 0;int reality=0;
	iVx=2*PI/Dens;
	countEm++;
	//reality++;
	/*Barva.x=0.f;//MANUAL OVERRIDE but this never happens
	Barva.y=1.f;
	Barva.z=0.5f;*/
	posX=posunX;
	posY=posunY;
	posZ=posunZ;
	Tvertices[vPoradi].Pos = XMFLOAT3(posX,posY,posZ);
	//Tvertices[vPoradi].Color = XMFLOAT4(0.0f,a/5,1.0f,1.f);
	Tvertices[vPoradi].Color = Barva;
	vPoradi++;

	vPoradi=vPoradi;
}

void RostClanekRozdvojeni(float r, float rp, float r2, float radiusZ, float sklony, float sklonX1, float sklonY1, float sklonz, float rotace, float Dens, float Uzk, float posunX, float posunY, float posunZ, float tU)
{

	float Zkoord = 0.0f;
	float rp2=rp;
	float PI = 3.14159265358979323846;
	float tV;

	tV=0.f;
	//
	//
	//NAPLNeni
	//
	//
	float iVx = 0;float l=0;float b=0;int reality=0;int reality1=0;int reality2=0; int reality3=0;
	l=PI/2-(PI/2-acos(Uzk/r));
	b=PI*1.5f+(PI/2-acos(Uzk/r))+Dens;
	iVx=(b-l)/Dens;
	iGuess+=int(iVx)*2;
	

	float  OrigoX, OrigoY, MezoX, MezoY, MezoX1, MezoY1;
	for (float a = PI/2-(PI/2-acos(Uzk/r)); a+Dens< PI*1.5f+(PI/2-acos(Uzk/r))+Dens; a+=Dens)																						//Pulkruh
	{
		iReality++;reality++;
		OrigoX=(cos((float)a) * r);
		OrigoY=(sin((float)a)) * r;
		//OrigoX = sin(atan((OrigoY+(Uzk + cos(acos(Uzk/r))*rp))/OrigoX)+rotace)*(OrigoX/cos(atan((OrigoY+(Uzk + cos(acos(Uzk/r))*rp))/OrigoX)));
		//OrigoY = /*cos(sklony)**/ cos(atan((OrigoY+(Uzk + cos(acos(Uzk/r))*rp))/OrigoX)+rotace)*(OrigoX/cos(atan((OrigoY+(Uzk + cos(acos(Uzk/r))*rp))/OrigoX)));
		//OrigoX = sin(atan((OrigoY+(Uzk + cos(acos(Uzk/r))*rp)*/)/OrigoX))*(OrigoX/cos(atan((OrigoY/*+(Uzk + cos(acos(Uzk/r))*rp)*/)/OrigoX)));
		//OrigoY = cos(atan((OrigoY/*+(Uzk + cos(acos(Uzk/r))*rp)*/)/OrigoX))*(OrigoX/cos(atan((OrigoY/*+(Uzk + cos(acos(Uzk/r))*rp)*/)/OrigoX)));
		MezoX = cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))+rotace)*((OrigoX-(Uzk + cos(acos(Uzk/r))*rp))/cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))));
		MezoY = sin(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))+rotace)*((OrigoX-(Uzk + cos(acos(Uzk/r))*rp))/cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))));
		Tvertices[vPoradi].Pos = XMFLOAT3(cos(atan((cos(sklony)*MezoY)/MezoX)+sklonz)*(MezoX/cos(atan((cos(sklony)*MezoY)/MezoX))) + posunX,sin(atan((cos(sklony)*MezoY)/MezoX)+sklonz)*(MezoX/cos(atan((cos(sklony)*MezoY)/MezoX)))+ posunY, Zkoord+  sin(sklony)*MezoY + posunZ);		
		//Tvertices[vPoradi].Color = XMFLOAT4((a-(PI/2))/PI,1.f - (a-(PI/2))/PI,0.f,1.f);
		Tvertices[vPoradi].Color = Barva;
		vPoradi++;
	}
	

	float PosunX1, PodminkaX1;
	//PosunX1 = cos(acos(Uzk/r))*(r + rp);
	PosunX1 = /*cos(acos(Uzk/r))*(r + rp)*/ + sqrt(pow((r2 + rp), 2.f) - pow(sin(acos(Uzk/r))*(r + rp), 2));
	PodminkaX1 = -(cos(asin((sin(acos(Uzk/r))*(r + rp))/(r2 + rp)))*r2);
	for (float a = PI+acos(Uzk/r); a+Dens< 3*PI-acos(Uzk/r)+Dens; a+=Dens)																						//Vysece2 + pulkruh2
	{
		if(a<=2*PI)
		{
			OrigoX = (cos(a) * r2) + cos(acos(Uzk/r))*(r + rp)+ PosunX1;;//cos(atan((MezoY1)/MezoX1)+sklonz)*sqrt(pow(MezoX1,2.f) + pow((MezoY1),2.f));
			OrigoY = (sin(a)  * r2) /*+ PosunY + PosunY1*/;//sin(atan((MezoY1)/MezoX1)+sklonz)*sqrt(pow(MezoX1,2.f) + pow((MezoY1),2.f));
			//OrigoY=(sin(a-2*PI)  * r2) /*+ PosunY + PosunY1*/ ;
			MezoX =  cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))+rotace)*((OrigoX-(Uzk + cos(acos(Uzk/r))*rp))/cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))));
			MezoY =  sin(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))+rotace)*((OrigoX-(Uzk + cos(acos(Uzk/r))*rp))/cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))));
			iReality++;reality1++;			
			Tvertices[vPoradi].Pos = XMFLOAT3(cos(atan((cos(sklony)*MezoY)/MezoX)+sklonz)*(MezoX/cos(atan((cos(sklony)*MezoY)/MezoX))) + posunX,sin(atan((cos(sklony)*MezoY)/MezoX)+sklonz)*(MezoX/cos(atan((cos(sklony)*MezoY)/MezoX)))+ posunY,/*PosunX1+ posunX +*/
				sin(sklony)*MezoY
				+ Zkoord + posunZ);
			Tvertices[vPoradi].Color = Barva;
			//Tvertices[vPoradi].Color = XMFLOAT4((a-PI-acos(Uzk/r))/(2*(PI-acos(Uzk/r))),1.f - (a-PI-acos(Uzk/r))/(2*(PI-acos(Uzk/r))),0.f,1.f);
			//TempR=sqrt(pow(OrigoY, 2.f) + pow(OrigoX, 2.f));
			//Tvertices[vPoradi].Pos = XMFLOAT3(OrigoX,OrigoY,sin(sklonx)*((cos((float)a)) * r2+ cos(acos(Uzk/r))*(r + rp)) + /*PosunX1+ posunX +*/ sin(sklonY1)*(sin((float)a)) * r2   + Zkoord + posunZ);

		}
		else
		{
			OrigoX = (cos(a-2*PI) * r2) + cos(acos(Uzk/r))*(r + rp)+ PosunX1;
			OrigoY = (sin(a-2*PI)  * r2) /*+ PosunY + PosunY1*/;
			//OrigoY=(sin(a-2*PI)  * r2) /*+ PosunY + PosunY1*/ ;
			MezoX =  cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))+rotace)*((OrigoX-(Uzk + cos(acos(Uzk/r))*rp))/cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))));
			MezoY =  sin(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))+rotace)*((OrigoX-(Uzk + cos(acos(Uzk/r))*rp))/cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))));
					iReality++;reality1++;
			Tvertices[vPoradi].Pos = XMFLOAT3(cos(atan((cos(sklony)*MezoY)/MezoX)+sklonz)*(MezoX/cos(atan((cos(sklony)*MezoY)/MezoX))) + posunX,sin(atan((cos(sklony)*MezoY)/MezoX)+sklonz)*(MezoX/cos(atan((cos(sklony)*MezoY)/MezoX)))+ posunY,/*PosunX1+ posunX +*/
				sin(sklony)*MezoY
				+ Zkoord + posunZ);
			Tvertices[vPoradi].Color = Barva;
			//Tvertices[vPoradi].Color = XMFLOAT4(0.f,1.f - (a-PI-acos(Uzk/r))/(2*(PI-acos(Uzk/r))),(a-PI-acos(Uzk/r))/(2*(PI-acos(Uzk/r))),1.f);
			//TempR=sqrt(pow(OrigoY, 2.f) + pow(OrigoX, 2.f));
			//Tvertices[vPoradi].Pos = XMFLOAT3(OrigoX,OrigoY,sin(sklonx)*((cos((float)a)) * r2+ cos(acos(Uzk/r))*(r + rp)) + /*PosunX1+ posunX +*/ sin(sklonY1)*(sin((float)a)) * r2   + Zkoord + posunZ);

		}
		vPoradi++;
		//}
	}
	reality=0;reality1=0;
	float PosunX, PosunY, PodminkaY, PodminkaX;
	PosunX = cos(acos(Uzk/r))*rp + Uzk;
	PosunY = sin(acos(Uzk/r))*(r + rp);
	float fRpDens = Dens*(r/rp);
	if(rp==0)
		fRpDens=Dens;
 	l=PI+acos(Uzk/r);
	b=1.5*PI+fRpDens;
	iVx=(b-l)/fRpDens;
	iGuess+=iVx;

	for (float a = PI+acos(Uzk/r); a+fRpDens< PI*1.5+fRpDens; a+=fRpDens)																						//Prechod1
	{
		OrigoX= cos(sklonX1)*(cos((float)a)*rp + PosunX);
		OrigoY=(sin((float)a)*rp + PosunY);
		MezoX =  cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))+rotace)*((OrigoX-(Uzk + cos(acos(Uzk/r))*rp))/cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))));
		MezoY =  sin(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))+rotace)*((OrigoX-(Uzk + cos(acos(Uzk/r))*rp))/cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))));
	iReality++;reality++;
		Tvertices[vPoradi].Pos = XMFLOAT3(cos(atan((cos(sklony)*MezoY)/MezoX)+sklonz)*(MezoX/cos(atan((cos(sklony)*MezoY)/MezoX))) + posunX,sin(atan((cos(sklony)*MezoY)/MezoX)+sklonz)*(MezoX/cos(atan((cos(sklony)*MezoY)/MezoX)))+ posunY,/*PosunX1+ posunX +*/
			sin(sklony)*MezoY
			+ Zkoord + posunZ);
		Tvertices[vPoradi].Color = Barva;
		//Tvertices[vPoradi].Color = XMFLOAT4((a-PI-acos(Uzk/r))/(0.5*PI-acos(Uzk/r)),1.f - (a-PI-acos(Uzk/r))/(0.5*PI-acos(Uzk/r)),0.f,1.f);
		vPoradi++;
		//}
	}


	PosunX = Uzk + cos(acos(Uzk/r))*rp;
	//PosunX = r + rp;
	PosunY = sin(acos(Uzk/r))*(r + rp) - rp + rp2;
	PodminkaX = (cos(asin((sin(acos(Uzk/r))*(r + rp))/(r2 + rp)))*rp)/rp2;
	PodminkaY = -rp*(cos(acos(Uzk/r)) - cos(acos(Uzk/r)))/rp2;
	
 	l=PI*1.5;
	b=PI*1.5+asin(Uzk/r)+fRpDens;
	iVx=(b-l)/fRpDens;
	iGuess+=iVx;

	for (float a = PI*1.5; a+fRpDens< PI*1.5+asin(Uzk/r)+fRpDens; a+=fRpDens)																						//Prechod2
	{
		OrigoX=cos(sklonX1)*(cos((float)a)*rp + PosunX);
		OrigoY=(sin((float)a)*rp + PosunY);
		MezoX =  cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))+rotace)*((OrigoX-(Uzk + cos(acos(Uzk/r))*rp))/cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))));
		MezoY =  sin(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))+rotace)*((OrigoX-(Uzk + cos(acos(Uzk/r))*rp))/cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))));
				iReality++;reality2++;
		Tvertices[vPoradi].Pos = XMFLOAT3(cos(atan((cos(sklony)*MezoY)/MezoX)+sklonz)*(MezoX/cos(atan((cos(sklony)*MezoY)/MezoX))) + posunX,sin(atan((cos(sklony)*MezoY)/MezoX)+sklonz)*(MezoX/cos(atan((cos(sklony)*MezoY)/MezoX)))+ posunY,/*PosunX1+ posunX +*/
			sin(sklony)*MezoY
			+ Zkoord + posunZ);
		Tvertices[vPoradi].Color = Barva;
		//Tvertices[vPoradi].Color = XMFLOAT4(1.f-(a-PI*1.5)/asin(Uzk/r),0.f,(a-PI*1.5)/asin(Uzk/r),1.f);
		vPoradi++;
		//}
	}

	PosunX = Uzk + cos(acos(Uzk/r))*rp;
	PosunY = sin(acos(Uzk/r))*(r + rp) - rp + rp2;
	PodminkaX = (cos(asin((sin(acos(Uzk/r))*(r + rp))/(r2 + rp)))*rp)/rp2;
	PodminkaY = -rp*(cos(acos(Uzk/r)) - cos(acos(Uzk/r)))/rp2;
	
 	l=0.5*PI;
	b=0.5*PI-asin(Uzk/r)-fRpDens;
	iVx=(l-b)/fRpDens;
	iGuess+=iVx;

	for (float a = 0.5*PI; a-fRpDens >  0.5*PI-asin(Uzk/r)-fRpDens; a-=fRpDens)																							//Prechod2 dole
	{
		OrigoX=(cos((float)a)*rp2 ) + PosunX;
		OrigoY=(rp2*sin((float)a) - PosunY) ;
				
		MezoX =  cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))+rotace)*((OrigoX-(Uzk + cos(acos(Uzk/r))*rp))/cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))));
		MezoY =  sin(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))+rotace)*((OrigoX-(Uzk + cos(acos(Uzk/r))*rp))/cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))));
		iReality++;reality3++;
		Tvertices[vPoradi].Pos = XMFLOAT3(cos(atan((cos(sklony)*MezoY)/MezoX)+sklonz)*(MezoX/cos(atan((cos(sklony)*MezoY)/MezoX))) + posunX,sin(atan((cos(sklony)*MezoY)/MezoX)+sklonz)*(MezoX/cos(atan((cos(sklony)*MezoY)/MezoX)))+ posunY,/*PosunX1+ posunX +*/
			sin(sklony)*MezoY
			+ Zkoord + posunZ);
		Tvertices[vPoradi].Color = Barva;
		//Tvertices[vPoradi].Color = XMFLOAT4(0.f,1.f-(a-PI*0.5+asin(Uzk/r))/asin(Uzk/r),(a-PI*0.5+asin(Uzk/r))/asin(Uzk/r),1.f);
		vPoradi++;
		//}
	}

	PosunX = cos(acos(Uzk/r))*rp + Uzk;
	PosunY = sin(acos(Uzk/r))*(r + rp);
	PodminkaY =  sin(acos(Uzk/r));
	
 	l=0.5*PI+asin(Uzk/r);
	b=0.5*PI-fRpDens;
	iVx=(l-b)/fRpDens;
	iGuess+=iVx;

	for (float a = 0.5*PI+asin(Uzk/r); a-fRpDens > 0.5*PI-fRpDens; a-=fRpDens)																						//Prechod1 dole
	{
		OrigoX=cos(sklonX1)*(cos((float)a)*rp + PosunX );
		OrigoY=(sin((float)a)*rp - PosunY);
				
		MezoX =  cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))+rotace)*((OrigoX-(Uzk + cos(acos(Uzk/r))*rp))/cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))));
		MezoY =  sin(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))+rotace)*((OrigoX-(Uzk + cos(acos(Uzk/r))*rp))/cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))));
		iReality++;reality1++;
		Tvertices[vPoradi].Pos = XMFLOAT3(cos(atan((cos(sklony)*MezoY)/MezoX)+sklonz)*(MezoX/cos(atan((cos(sklony)*MezoY)/MezoX))) + posunX,sin(atan((cos(sklony)*MezoY)/MezoX)+sklonz)*(MezoX/cos(atan((cos(sklony)*MezoY)/MezoX)))+ posunY,/*PosunX1+ posunX +*/
			sin(sklony)*MezoY
			+ Zkoord + posunZ);
		Tvertices[vPoradi].Color = Barva;
		//Tvertices[vPoradi].Color = XMFLOAT4((a-PI*0.5)/asin(Uzk/r),0.f,1.f-(a-PI*0.5)/asin(Uzk/r),1.f);
		vPoradi++;
		//}
	}
	iVx=iVx;
}

int integratePower(int _zakl, float _doMocniny)
{
	int _v = 0;
	int _mv = 1;
	if (_doMocniny <0)
		return 0;
	for(int i = 0; i < _doMocniny; i++)
	{
		for(int x = 0; x < i; x++)
			_mv*=_zakl;
		_v+=_mv;
		_mv=1;
	}
	return _v;
}

UINT* GenerateTIndices()
{
	int pocit = 0;

	UINT* Tindices = new UINT[10000];

	//po49t8n9 indexu
	//1 troj na každý V
	//3*2*360
	//int nTi = 3*361*2;


	//vPoradi-361= pocet v hore=> to /2 pocet trojuhelniku=>to*3 pocet indicii ale ctverec ma dva facy 2!2!2!2!
	//

	/*UINT Tindices[]=
	{
	{0},
	{9},
	{361}
	};*/
	//, 359,0+360+359

	/*Tindices[pocit]=0;
	Tindices[pocit+1]=6;
	Tindices[pocit+2]=1;
	pocit+=3;
	Tindices[pocit]=1;
	Tindices[pocit+1]=7;
	Tindices[pocit+2]=2;
	pocit+=3;
	Tindices[pocit]=2;
	Tindices[pocit+1]=8;
	Tindices[pocit+2]=3;
	pocit+=3;
	Tindices[pocit]=3;
	Tindices[pocit+1]=9;
	Tindices[pocit+2]=4;
	pocit+=3;
	Tindices[pocit]=4;
	Tindices[pocit+1]=10;
	Tindices[pocit+2]=5;
	pocit+=3;
	Tindices[pocit]=5;
	Tindices[pocit+1]=11;
	Tindices[pocit+2]=0;
	pocit+=3;
	*/
	/*Tindices[pocit]=0;
	Tindices[pocit+1]=6;
	Tindices[pocit+2]=1;
	pocit+=3;
	Tindices[pocit]=1;
	Tindices[pocit+1]=7;
	Tindices[pocit+2]=2;
	pocit+=3;
	Tindices[pocit]=2;
	Tindices[pocit+1]=8;
	Tindices[pocit+2]=3;
	pocit+=3;
	Tindices[pocit]=3;
	Tindices[pocit+1]=9;
	Tindices[pocit+2]=4;
	pocit+=3;
	Tindices[pocit]=4;
	Tindices[pocit+1]=10;
	Tindices[pocit+2]=5;
	pocit+=3;
	Tindices[pocit]=5;
	Tindices[pocit+1]=11;
	Tindices[pocit+2]=0;
	pocit+=3;*/

	//pomer nahore ku dole udava za jak dlouho se prejde k dalsimu dolnimu indexu, to jest vPoradi-361/361
	int nVperline = 361;//180pulkruh 36vzsece 18 jedna
	int Origin=180;

	for(int x = Origin; x < (nVperline-1)/2+Origin; x++)
	{
		Tindices[pocit]=x;
		Tindices[pocit+1]=nVperline+361-x;
		Tindices[pocit+2]=x+1;
		pocit+=3;
	}
	/*for(int x = nVperline+Origin; x < nVperline+Origin+179; x++)
	{
	Tindices[pocit]=x;
	Tindices[pocit+1]=x+1;
	Tindices[pocit+2]=x-nVperline+1;
	pocit+=3;
	}*/


	/*for(int x = 180; x < 270; x++)
	{
	Tindices[pocit]=x;
	Tindices[pocit+1]=(x+90)+361+35;
	Tindices[pocit+2]=x+1;
	pocit+=3;
	}
	for(int x = 361+180+90+35; x < 361+90+35+270; x++)
	{
	Tindices[pocit]=x;
	Tindices[pocit+2]=x+1;
	Tindices[pocit+1]=x-361-90-35;

	pocit+=3;
	}



	for(int x = 270; x < 360; x++)
	{
	Tindices[pocit]=x;
	Tindices[pocit+1]=(x-90)+361;
	Tindices[pocit+2]=x+1;
	pocit+=3;
	}
	for(int x = 270+361-90; x < 361+380-90; x++)
	{
	Tindices[pocit]=x;
	Tindices[pocit+2]=x+1;
	Tindices[pocit+1]=x+90-361;

	pocit+=3;
	}



	for(int x = 541+180; x < 541+180+18; x++)
	{
	Tindices[pocit]=x;
	Tindices[pocit+1]=179;
	Tindices[pocit+2]=x+1;
	pocit+=3;
	}*/

	/*for(int x = nVperline+Origin; x < nVperline+Origin+179; x++)
	{
	Tindices[pocit]=x;
	Tindices[pocit+1]=x+1;
	Tindices[pocit+2]=x-nVperline+1;
	pocit+=3;
	}*/
	/*Tindices[pocit]=nVperline-1+Origin;
	Tindices[pocit+1]=nVperline*2-1+Origin;
	Tindices[pocit+2]=Origin;
	pocit+=3;
	for(int x = nVperline+Origin; x < nVperline*2-1+Origin; x++)
	{
	Tindices[pocit]=x;
	Tindices[pocit+1]=x+1;
	Tindices[pocit+2]=x-nVperline+1;
	pocit+=3;
	}
	Tindices[pocit]=nVperline*2-1+Origin;
	Tindices[pocit+1]=nVperline+Origin;
	Tindices[pocit+2]=Origin;
	pocit+=3;

	for(int x = Origin; x < nVperline-1+Origin; x++)
	{
	Tindices[pocit]=x;
	Tindices[pocit+1]=x+nVperline;
	Tindices[pocit+2]=x+1;
	pocit+=3;
	}
	Tindices[pocit]=nVperline-1+Origin;
	Tindices[pocit+1]=nVperline*2-1+Origin;
	Tindices[pocit+2]=Origin;
	pocit+=3;
	for(int x = nVperline+Origin; x < nVperline*2-1+Origin; x++)
	{
	Tindices[pocit]=x;
	Tindices[pocit+1]=x+1;
	Tindices[pocit+2]=x-nVperline+1;
	pocit+=3;
	}
	Tindices[pocit]=nVperline*2-1+Origin;
	Tindices[pocit+1]=nVperline+Origin;
	Tindices[pocit+2]=Origin;
	pocit+=3;

	/*for(int x = 360; x < 720; x++)
	{
	Tindices[pocit]=x;
	Tindices[pocit+1]=x-360+1;
	Tindices[pocit+2]=x+1;
	pocit+=3;
	}*/
	/*Tindices[pocit]=0;
	Tindices[pocit+1]=359;
	Tindices[pocit+2]=360+359;
	pocit+=3;*/


	//STUPID
	/*int Origin=0;
	int Originh=0;

	int Pvh =  501;
	int Pvd =  361;
	int Pomer;
	Pomer = (Pvh-1)/(Pvd-1); 
	int Zbytek =Pomer * (Pvd-1)-(Pvh-1);

	for(int x = Origin; x < Pvd-Zbytek; x++)
	{
	for(int i = 0; i < Pomer; i++)
	{
	Tindices[pocit]=x;
	Tindices[pocit+1]=((Pvh-1)+(Pvd-1))- x*(Pomer-1)-i;
	Tindices[pocit+2]=(360+716)- x*(Pomer-1)-i-1;
	pocit+=3;
	}		
	Tindices[pocit]=x;
	Tindices[pocit+1]=((Pvh-1)+(Pvd-1))- x*(Pomer-1)-(Pomer-1)-1;
	Tindices[pocit+2]=x+1;
	pocit+=3;
	}

	for(int i = 0; i < Pomer+Zbytek; i++)
	{
	Tindices[pocit]=Pvd;
	Tindices[pocit+1]=361+Pvd*Pomer+i;
	Tindices[pocit+2]=361+Pvd*Pomer+i +1;
	pocit+=3;
	}

	Tindices[pocit]=Pvd;
	Tindices[pocit+1]=361+Pvd*Pomer+Pomer+Zbytek;
	Tindices[pocit+2]=Origin;
	pocit+=3;*/
	/*//BEFORE
	int nVperline = vPoradi - 361;
	int Origin=0;

	for(int x = Origin; x < nVperline-1+Origin; x++)
	{
	Tindices[pocit]=x;
	Tindices[pocit+1]=x+nVperline;
	Tindices[pocit+2]=x+1;
	pocit+=3;
	}
	Tindices[pocit]=nVperline-1+Origin;
	Tindices[pocit+1]=nVperline*2-1+Origin;
	Tindices[pocit+2]=Origin;
	pocit+=3;
	for(int x = nVperline+Origin; x < nVperline*2-1+Origin; x++)
	{
	Tindices[pocit]=x;
	Tindices[pocit+1]=x+1;
	Tindices[pocit+2]=x-nVperline+1;
	pocit+=3;
	}
	Tindices[pocit]=nVperline*2-1+Origin;
	Tindices[pocit+1]=nVperline+Origin;
	Tindices[pocit+2]=Origin;
	pocit+=3;*/

	/*for(int x = 360; x < 720; x++)
	{
	Tindices[pocit]=x;
	Tindices[pocit+1]=x-360+1;
	Tindices[pocit+2]=x+1;
	pocit+=3;
	}*/
	/*Tindices[pocit]=0;
	Tindices[pocit+1]=359;
	Tindices[pocit+2]=360+359;
	pocit+=3;*/
	//Tindices[pocit]=10;
	//Tindices[pocit+1]=11;
	return Tindices;
}


void RostOsy()
{
	float axDens = 10.f;
	float delka = 500.f;
	float origin =0.f;
	//
	//Pomocne obrazce
	//
	//float mer = 1.f;
	/*for (float a = -30.f; a<= 60; a+=0.001f)									//4a
	{
	//r = (sqrt((float)1+4*x)-1)/2;							// kvadraticka fce 4a
	//r2=r;
	Tvertices[vPoradi].Pos = XMFLOAT3((float)a  *mer, fabs(pow((float)a, 2) - 1) *mer, Zkoord);
	vPoradi++;
	}
	for (float a = -30.f; a<= 60; a+=0.001f)
	{
	//r = (sqrt((float)1+4*x)-1)/2;							// linearni fce 4a
	//r2=r;
	Tvertices[vPoradi].Pos = XMFLOAT3((float)a  *mer, (float)a * 2 + 1 *mer, Zkoord);
	vPoradi++;
	}*/

	/*for (float a = -30.f; a<= 60; a+=0.001f)									//4c
	{
	//r = (sqrt((float)1+4*x)-1)/2;							// kvadraticka fce 4c
	//r2=r;
	Tvertices[vPoradi].Pos = XMFLOAT3((float)a  *mer, fabs((float)a + 2) + fabs((float)a - 2) *mer, Zkoord);
	vPoradi++;
	}
	for (float a = -30.f; a<= 60; a+=0.001f)									//4c
	{
	//r = (sqrt((float)1+4*x)-1)/2;							// kvadraticka fce 4c
	//r2=r;
	Tvertices[vPoradi].Pos = XMFLOAT3((float)a  *mer, fabs((float)a + 2) *mer, Zkoord);
	vPoradi++;
	}
	for (float a = -30.f; a<= 60; a+=0.001f)									//4c
	{
	//r = (sqrt((float)1+4*x)-1)/2;							// kvadraticka fce 4c
	//r2=r;
	Tvertices[vPoradi].Pos = XMFLOAT3((float)a  *mer, fabs((float)a - 2) *mer, Zkoord);
	vPoradi++;
	}
	for (float a = -30.f; a<= 60; a+=0.001f)
	{
	//r = (sqrt((float)1+4*x)-1)/2;							// linearni fce 4c
	//r2=r;
	Tvertices[vPoradi].Pos = XMFLOAT3((float)a  *mer, 4.f *mer, Zkoord);
	vPoradi++;
	}


	for (float a = -30.f; a<= 60; a+=0.001f)									//4d
	{
	//r = (sqrt((float)1+4*x)-1)/2;							// kvadraticka fce 4d
	//r2=r;
	Tvertices[vPoradi].Pos = XMFLOAT3((float)a  *mer, (pow((float)a, 2) - (float)a*2 + 3) *mer, Zkoord);
	vPoradi++;
	}
	for (float a = -30.f; a<= 60; a+=0.001f)
	{
	//r = (sqrt((float)1+4*x)-1)/2;							// linearni fce 4d
	//r2=r;
	Tvertices[vPoradi].Pos = XMFLOAT3((float)a  *mer, fabs((float)a - 4) *mer, Zkoord);
	vPoradi++;
	}*/


	/*for (float a = -30.f; a<= 60; a+=0.001f)									//4b
	{
	//r = (sqrt((float)1+4*x)-1)/2;							// kvadraticka fce 4d
	//r2=r;
	Tvertices[vPoradi].Pos = XMFLOAT3((float)a  *mer, ((abs((float)a)-1)/(pow((float)a,2) - 1)) *mer, Zkoord);
	vPoradi++;
	}
	for (float a = -30.f; a<= 60; a+=0.001f)
	{
	//r = (sqrt((float)1+4*x)-1)/2;							// linearni fce 4b
	//r2=r;
	Tvertices[vPoradi].Pos = XMFLOAT3((float)a  *mer, 0.5f *mer, Zkoord);
	vPoradi++;
	}*/


	for (float a = origin; a <= delka; a+=1.f/axDens)												//osa x
	{
		Tvertices[vPoradi].Pos = XMFLOAT3(a, 0.f, 0.0f);
		Tvertices[vPoradi].Color = XMFLOAT4(1.f,0.f,0.f,1.f);
		vPoradi++;

		if((int)a%100 == 0 && ((int)((a-(int)a)*axDens) % (int)(axDens) == 0))
		{
			for (int b = 0; b <= 50; b++)												//osa x
			{
				Tvertices[vPoradi].Pos = XMFLOAT3(a , (float)b/100, 0.0f);
				Tvertices[vPoradi].Color = XMFLOAT4(1.f,0.5f,0.f,1.f);
				vPoradi++;
			}
		}
		else if((int)a % 10 == 0 && ((int)(a*axDens) % (int)(axDens) == 0))
		{
			for (int b = 0; b <= 25; b++)												//osa x
			{
				Tvertices[vPoradi].Pos = XMFLOAT3(a, (float)b/100, 0.0f);
				Tvertices[vPoradi].Color = XMFLOAT4(1.f,1.0f,0.f,1.f);
				vPoradi++;
			}
		}
		else if((int)a % 1 == 0 && ((int)(a*axDens) % (int)(axDens) == 0))
		{
			for (int b = 0; b <= 10; b++)												//osa x
			{
				Tvertices[vPoradi].Pos = XMFLOAT3(a, (float)b/100, 0.0f);
				Tvertices[vPoradi].Color = XMFLOAT4(1.f,0.6f,0.f,1.f);
				vPoradi++;
			}
		}

	}


	for (float a = origin; a <= delka; a+=1/axDens)												//osa y
	{
		Tvertices[vPoradi].Pos = XMFLOAT3(0.f, a, 0.0f);
		Tvertices[vPoradi].Color = XMFLOAT4(0.f,1.f,0.f,1.f);
		vPoradi++;

		if((int)a%100 == 0 && ((int)((a-(int)a)*axDens) % (int)(axDens) == 0))
		{
			for (int b = 0; b <= 50; b++)												//osa y
			{
				Tvertices[vPoradi].Pos = XMFLOAT3((float)b/100, a, 0.0f);
				Tvertices[vPoradi].Color = XMFLOAT4(0.f,1.f,0.f,1.f);
				vPoradi++;
			}
		}
		else if((int)a % 10 == 0 && ((int)(a*axDens) % (int)(axDens) == 0))
		{
			for (int b = 0; b <= 25; b++)												//osa y
			{
				Tvertices[vPoradi].Pos = XMFLOAT3((float)b/100, a, 0.0f);
				Tvertices[vPoradi].Color = XMFLOAT4(1.f,1.0f,0.f,1.f);
				vPoradi++;
			}
		}
		else if((int)a % 1 == 0 && ((int)(a*axDens) % (int)(axDens) == 0))
		{
			for (int b = 0; b <= 10; b++)												//osa y
			{
				Tvertices[vPoradi].Pos = XMFLOAT3((float)b/100,a, 0.0f);
				Tvertices[vPoradi].Color = XMFLOAT4(1.f,0.6f,0.f,1.f);
				vPoradi++;
			}
		}

	}

	for (float a = origin; a <= delka; a+=1/axDens)												//osa x
	{
		Tvertices[vPoradi].Pos = XMFLOAT3(0.f, 0.f, a);
		Tvertices[vPoradi].Color = XMFLOAT4(0.f,0.f,1.f,1.f);
		vPoradi++;

		if((int)a%100 == 0 && ((int)((a-(int)a)*axDens) % (int)(axDens) == 0))
		{
			for (int b = 0; b <= 50; b++)												//osa x
			{
				Tvertices[vPoradi].Pos = XMFLOAT3(0.f , (float)b/100, a);
				Tvertices[vPoradi].Color = XMFLOAT4(0.f,0.f,1.f,1.f);
				vPoradi++;
			}
		}
		else if((int)a % 10 == 0 && ((int)(a*axDens) % (int)(axDens) == 0))
		{
			for (int b = 0; b <= 25; b++)												//osa x
			{
				Tvertices[vPoradi].Pos = XMFLOAT3(0.f, (float)b/100, a);
				Tvertices[vPoradi].Color = XMFLOAT4(1.f,1.0f,0.f,1.f);
				vPoradi++;
			}
		}
		else if((int)a % 1 == 0 && ((int)(a*axDens) % (int)(axDens) == 0))
		{
			for (int b = 0; b <= 10; b++)												//osa x
			{
				Tvertices[vPoradi].Pos = XMFLOAT3(0.f, (float)b/100, a);
				Tvertices[vPoradi].Color = XMFLOAT4(1.f,0.6f,0.f,1.f);
				vPoradi++;
			}
		}
	}

	for (float a = origin; a >= -delka; a-=1.f/axDens)												//osa x
	{
		Tvertices[vPoradi].Pos = XMFLOAT3(a, 0.f, 0.0f);
		Tvertices[vPoradi].Color = XMFLOAT4(1.f,0.f,0.f,1.f);
		vPoradi++;

		if((int)a%100 == 0 && ((int)((a-(int)a)*axDens) % (int)(axDens) == 0))
		{
			for (int b = 0; b <= 50; b++)												//osa x
			{
				Tvertices[vPoradi].Pos = XMFLOAT3(a , (float)b/100, 0.0f);
				Tvertices[vPoradi].Color = XMFLOAT4(1.f,0.f,0.f,1.f);
				vPoradi++;
			}
		}
		else if((int)a % 10 == 0 && ((int)(a*axDens) % (int)(axDens) == 0))
		{
			for (int b = 0; b <= 25; b++)												//osa x
			{
				Tvertices[vPoradi].Pos = XMFLOAT3(a, (float)b/100, 0.0f);
				Tvertices[vPoradi].Color = XMFLOAT4(1.f,1.0f,0.f,1.f);
				vPoradi++;
			}
		}
		else if((int)a % 1 == 0 && ((int)(a*axDens) % (int)(axDens) == 0))
		{
			for (int b = 0; b <= 10; b++)												//osa x
			{
				Tvertices[vPoradi].Pos = XMFLOAT3(a, (float)b/100, 0.0f);
				Tvertices[vPoradi].Color = XMFLOAT4(1.f,0.6f,0.f,1.f);
				vPoradi++;
			}
		}

	}


	for (float a = origin; a >= -delka; a-=1/axDens)												//osa x
	{
		Tvertices[vPoradi].Pos = XMFLOAT3(0.f, a, 0.0f);
		Tvertices[vPoradi].Color = XMFLOAT4(0.f,1.f,0.f,1.f);
		vPoradi++;

		if((int)a%100 == 0 && ((int)((a-(int)a)*axDens) % (int)(axDens) == 0))
		{
			for (int b = 0; b <= 50; b++)												//osa x
			{
				Tvertices[vPoradi].Pos = XMFLOAT3((float)b/100, a, 0.0f);
				Tvertices[vPoradi].Color = XMFLOAT4(0.f,1.f,0.f,1.f);
				vPoradi++;
			}
		}
		else if((int)a % 10 == 0 && ((int)(a*axDens) % (int)(axDens) == 0))
		{
			for (int b = 0; b <= 25; b++)												//osa x
			{
				Tvertices[vPoradi].Pos = XMFLOAT3((float)b/100, a, 0.0f);
				Tvertices[vPoradi].Color = XMFLOAT4(1.f,1.0f,0.f,1.f);
				vPoradi++;
			}
		}
		else if((int)a % 1 == 0 && ((int)(a*axDens) % (int)(axDens) == 0))
		{
			for (int b = 0; b <= 10; b++)												//osa x
			{
				Tvertices[vPoradi].Pos = XMFLOAT3((float)b/100,a, 0.0f);
				Tvertices[vPoradi].Color = XMFLOAT4(1.f,0.6f,0.f,1.f);
				vPoradi++;
			}
		}

	}

	for (float a = origin; a >= -delka; a-=1/axDens)												//osa x
	{
		Tvertices[vPoradi].Pos = XMFLOAT3(0.f, 0.f, a);
		Tvertices[vPoradi].Color = XMFLOAT4(0.f,0.f,1.f,1.f);
		vPoradi++;

		if((int)a%100 == 0 && ((int)((a-(int)a)*axDens) % (int)(axDens) == 0))
		{
			for (int b = 0; b <= 50; b++)												//osa x
			{
				Tvertices[vPoradi].Pos = XMFLOAT3(0.f , (float)b/100, a);
				Tvertices[vPoradi].Color = XMFLOAT4(0.f,0.f,1.f,1.f);
				vPoradi++;
			}
		}
		else if((int)a % 10 == 0 && ((int)(a*axDens) % (int)(axDens) == 0))
		{
			for (int b = 0; b <= 25; b++)												//osa x
			{
				Tvertices[vPoradi].Pos = XMFLOAT3(0.f, (float)b/100, a);
				Tvertices[vPoradi].Color = XMFLOAT4(1.f,1.0f,0.f,1.f);
				vPoradi++;
			}
		}
		else if((int)a % 1 == 0 && ((int)(a*axDens) % (int)(axDens) == 0))
		{
			for (int b = 0; b <= 10; b++)												//osa x
			{
				Tvertices[vPoradi].Pos = XMFLOAT3(0.f, (float)b/100, a);
				Tvertices[vPoradi].Color = XMFLOAT4(1.f,0.6f,0.f,1.f);
				vPoradi++;
			}
		}
	}
	/*
	for (int a = 0; a <= 600; a++)
	{
	Tvertices[vPoradi].Pos = XMFLOAT3(a * axDens + Uzk, (tan(asin(Uzk/r)) *  a * -axDens) + tan(acos(Uzk/r))*Uzk, Zkoord);
	vPoradi++;
	}*/
}