#include "start.h"
SimpleVertex* Tvertices = NULL;
int vPoradi = 0;
int gnVetvi = 0;
XMFLOAT4 Barva;
float per, gonx, height;
bool stridat = true;
void RostClanek(float r, float radiusZ, float sklony, float sklonz, float Dens, float posunX, float posunY, float posunZ);
void RostClanekRozdvojeni(float r, float rp, float r2, float radiusZ, float sklony, float sklonX1, float sklonY1, float sklonz,float rotace, float Dens, float Uzk, float posunX, float posunY, float posunZ, float tU);
void RostOsy();

struct objRust
{
	float r;
	float sklon;
	float rotace;
};

struct tuplFloat3
{
	XMFLOAT3 x_0;
	XMFLOAT3 x_1;
};

tuplFloat3 RostVetev(XMFLOAT3 start,XMFLOAT3 ending,objRust Rust, objRust RustTo,bool konec,float delka,float AxeRotace, float mezera, float dens); //nevraci end
tuplFloat3 RostRozdvojeni(XMFLOAT3 start,XMFLOAT3 ending,objRust Rust,float delka,float AxeRotace, float mezera, float dens);


SimpleVertex*  GenerateTree(int nVetvi, int vPoradi, int nTv)
{
	float PI = 3.14159265358979323846;
	nTv = vPoradi;

	//
	//
	//NAPLNeni
	//
	//

	//nTv = vPoradi;
	vPoradi = 0;
	//WORD* Tindices = new WORD[nTi];

	Tvertices = new SimpleVertex[nTv];
	XMFLOAT3* Tpositions = new XMFLOAT3[nTv];
	XMFLOAT2* Ttextcoords = new XMFLOAT2[nTv];
	XMFLOAT3* Tnormals = new XMFLOAT3[nTv];
	/*for (float x = 0.f; x<= 2.f; x+=1.f)
	{
	//r = (sqrt((float)1+4*x)-1)/2;							//sklenice kvadraticka
	//r2=r;

	//posunX=10.01f;
	//rp=GenerateRndm(0,180);		
	r=0;
	while(r==0)
	{
	r= 1.f + GenerateRndm(0,9999)/100000.f;
	}
	r2=0;
	/*sklonx=0;
	while(sklonx==0)
	{
	sklonx=-GenerateRndm(0,45)*PI/180;
	}

	sklonz=0;
	while(sklonz==0)
	{
	sklonz=-GenerateRndm(90,360)*PI/180;
	}*/
	/*
	for(int x = 0; x < 5000000; x++)
	{
	}
	

	}*/
	Barva = XMFLOAT4(/*GenerateRndm(0,2)/*/0.f, /*GenerateRndm(0,2)/*/1.0f,/*GenerateRndm(0,2)/*/0.1f,1.f);
	//Barva= XMFLOAT4(1.f,1.0f,0.0f,1.f);
	XMFLOAT3 Start;
	XMFLOAT3 End;
	float delka = 0.f;
	objRust Rust;
	Rust.rotace= -PI/2;
	float axerotace = 0;//rotace;
	Rust.sklon = -PI/2;//-89*PI/180;
	Rust.r = GenerateRndm(111,999)/100.f;

	objRust RustTo;
	RustTo.rotace= -PI/3;
	RustTo.sklon = -PI/2;//-89*PI/180;
	RustTo.r = Rust.r;
	//float mezera = Rust.r*0.2;//d
	//360...obvod 1 stupne..
	float dens =  30.f* PI/180;
	float mezera = (2*PI*Rust.r)/(360/(dens/(PI/180)));
	per = 2*PI/30.f;
	gnVetvi = nVetvi;
	//gnVetvi=10;
	//gnVetvi = GenerateRndm(1,100);
	height = GenerateRndm(100,200);
	Start.x = 0.0f;
	Start.y = 0.0f;
	Start.z = 0.0f;


	//r=0;

	//dulezite
	/*sklonx=0;
	while(sklonx==0)
	{
	sklonx=-GenerateRndm(0,45)*PI/180;
	}

	sklonz=0;
	while(sklonz==0)
	{
	sklonz=-GenerateRndm(90,360)*PI/180;
	}*/




	//mezera = (2*PI*r)/90;

	delka = GenerateRndm(111,999)/10.f;


	//opakuj kolikrat chces rozdvojit
	int n = 1;XMFLOAT3* POS = new XMFLOAT3[256];tuplFloat3 tuplPosice;XMFLOAT3* tempPOS = new XMFLOAT3[256];
	for(int x = 0; x < n; x++)
	{
		tuplPosice = RostVetev(POS[x]);
		POS[x] = tuplPosice.x_0;
		tempPOS[x] = tuplPosice.x_1;
	}
	for(int x = 0; x < n; x++)	
		POS[n+x] = tempPOS[x];
	n *= 2;


	//RostOsy();
	RostVetev(Start, End, Rust,RustTo,false, delka, axerotace, mezera, dens);
	//Start.z += 20;


	/*Start.z = 0.02*10 * 110;
	for (float i = 10.f; i>1.0;i-=1.f)
	{
	//Start.z += 0.02*i *100;
	RostRozdvojeni(Start, End, sqrt(i), delka, sklon, rotace);
	Start.z = 0.02*i *100;
	}*/

	return Tvertices;
}

tuplFloat3 RostVetev(XMFLOAT3 start,XMFLOAT3 ending,objRust Rust, objRust RustTo,bool konec,float delka,float AxeRotace, float mezera, float dens)
{

	//RustTo = Rust;
	float PI = 3.14159265358979323846;
	float ample;//, per; //radius krouceni
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
	float Rorigin = Rust.r;
	objRust TempRust = Rust;
	mezera = (2*PI*TempRust.r)/(360/(dens/(PI/180))); //360...obvod 1 stupne..
	if(konec)
		RustTo.r = 0.01f;

	for (float x = 0.f; x< delka/mezera; x+=1.f)
	{
		//mezera = (2*PI*TempRust.r)/90; //360...obvod 1 stupne..
		TempRust.r += (RustTo.r-Rust.r)/(delka/mezera);
		TempRust.rotace += (RustTo.rotace-Rust.rotace)/(delka/mezera);
		TempRust.sklon += (RustTo.sklon - Rust.sklon)/(delka/mezera);
		sklony = PI/2 +TempRust.sklon;
		sklonz = PI/2 -TempRust.rotace;
		OrigoZ+=mezera;
		OrigoX = sin(per*(OrigoZ+PI/180))*ample;
		OrigoY = sin(per*(OrigoZ+PI/180))*ample;
		afterY = sin(atan(OrigoZ/OrigoY)+TempRust.sklon)*(OrigoY/cos(atan(OrigoZ/OrigoY)));
		posunZ = cos(atan(OrigoZ/OrigoY)+TempRust.sklon)*(OrigoY/cos(atan(OrigoZ/OrigoY)))+start.z;
		posunY = cos(atan(afterY/OrigoX)+TempRust.rotace)*(OrigoX/cos(atan(afterY/OrigoX)))+start.y;
		posunX = sin(atan(afterY/OrigoX)+TempRust.rotace)*(OrigoX/cos(atan(afterY/OrigoX)))+start.x;
		RostClanek(TempRust.r, radiusZ, sklony, sklonz, dens, posunX, posunY, posunZ);
		Barva.x+=0.01;
	}

	OrigoX = sin(per*(+PI/180))*ample;
	OrigoY = sin(per*(+PI/180))*ample;
	afterY = sin(atan(OrigoZ/OrigoY)+TempRust.sklon)*(OrigoY/cos(atan(OrigoZ/OrigoY)));
	posunZ = cos(atan(OrigoZ/OrigoY)+TempRust.sklon)*(OrigoY/cos(atan(OrigoZ/OrigoY)))+start.z;
	posunY = cos(atan(afterY/OrigoX)+TempRust.rotace)*(OrigoX/cos(atan(afterY/OrigoX)))+start.y;
	posunX = sin(atan(afterY/OrigoX)+TempRust.rotace)*(OrigoX/cos(atan(afterY/OrigoX)))+start.x;
	start.x = posunX;
	start.y = posunY;
	start.z = posunZ;

	//AxeRotace += PI/2;//- rotace anuluje axerotaci<<<<<
	//rotace += PI/2;
	//r-=0.5;
	gonx = OrigoZ;
	if(/*start.z < height && gnVetvi > 0 && start.z > 0.f &&*/!konec) //neni symetrické, chybí multithreading :D
	{
		//gnVetvi--;
		return RostRozdvojeni(start, ending, TempRust, delka,AxeRotace, mezera, dens);
	}

}

tuplFloat3 RostRozdvojeni(XMFLOAT3 start,XMFLOAT3 ending,objRust Rust,float delka,float AxeRotace, float mezera, float dens)
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
	sklony = PI/2 +Rust.sklon;
	sklonz = PI/2 -Rust.rotace; 
	ample= 1.0f;
	for (float x = 0.f; x<= 110.f; x+=1.f)
	{
		//r = (sqrt((float)1+4*x)-1)/2;							//sklenice kvadratick
		Uzk += Rust.r* 0.0079f;
		OrigoZ+= Rust.r* 0.02f;
		gonx += Rust.r* 0.02f;
		OrigoX = Xorigin + sin(per*(gonx+PI/180))*ample;
		OrigoY = Yorigin + sin(per*(gonx+PI/180))*ample;
		afterY = sin(atan(OrigoZ/OrigoY)+Rust.sklon)*(OrigoY/cos(atan(OrigoZ/OrigoY)));
		posunZ = cos(atan(OrigoZ/OrigoY)+Rust.sklon)*(OrigoY/cos(atan(OrigoZ/OrigoY)))+start.z; 
		posunY = cos(atan(afterY/OrigoX)+Rust.rotace)*(OrigoX/cos(atan(afterY/OrigoX)))+start.y;
		posunX = sin(atan(afterY/OrigoX)+Rust.rotace)*(OrigoX/cos(atan(afterY/OrigoX)))+start.x; // vzcentrov8n9
		RostClanekRozdvojeni(Rust.r, rp, r2, radiusZ, sklony,sklonX1,sklonY1, sklonz, AxeRotace, dens, Uzk, posunX, posunY, posunZ, tU);
		tU-=1.f;
		rp=0.1*Rust.r;
		rp2=rp;
	}
	OrigoX = Xorigin + sin(per*(gonx+PI/180))*ample+cos(AxeRotace)*((Uzk + cos(acos(Uzk/Rust.r))*rp));  //changed:""""SDAFSDFASDFASDF aco
	OrigoY = Yorigin + sin(per*(gonx+PI/180))*ample+sin(AxeRotace)*((Uzk + cos(acos(Uzk/Rust.r))*rp));
	afterY = sin(atan(OrigoZ/OrigoY)+Rust.sklon)*(OrigoY/cos(atan(OrigoZ/OrigoY)));
	posunZ = cos(atan(OrigoZ/OrigoY)+Rust.sklon)*(OrigoY/cos(atan(OrigoZ/OrigoY)))+start.z; 
	Rust1.rotace=Rust.rotace- /*PI/2 +*/ GenerateRndm(20,120)*PI/180;
	posunY = cos(atan(afterY/OrigoX)+Rust.rotace)*(OrigoX/cos(atan(afterY/OrigoX)))+start.y; //zadna zmena Rust.rotace!!!
	posunX = sin(atan(afterY/OrigoX)+Rust.rotace)*(OrigoX/cos(atan(afterY/OrigoX)))+start.x; // vzcentrov8n9
	start1 =  XMFLOAT3(posunX,posunY,posunZ);
	if(GenerateRndm(0,2)==1)
		Rust1.sklon = -GenerateRndm(65,80)*PI/180;//0.2f*pow(gonx*PI/180,2) ;
	else
		Rust1.sklon = -GenerateRndm(10,80)*PI/180;//0.2f*pow(gonx*PI/180,2) ;
	Rust1.r =Rust.r - GenerateRndm(0,999)/1000.f;
	delka = 0;
	delka = GenerateRndm(222,999)/10.f; //TAHLE DZLKA IS MISPLACING THE VETEVSTARTPOS... 333 999/10.F
	OrigoX = Xorigin + sin(per*(gonx+PI/180))*ample+cos(AxeRotace)*(-(Uzk + cos(acos(Uzk/Rust.r))*rp));  //changed:""""SDAFSDFASDFASDF aco
	OrigoY = Yorigin + sin(per*(gonx+PI/180))*ample+sin(AxeRotace)*(-(Uzk + cos(acos(Uzk/Rust.r))*rp));
	afterY = sin(atan(OrigoZ/OrigoY)+Rust.sklon)*(OrigoY/cos(atan(OrigoZ/OrigoY)));
	posunZ = cos(atan(OrigoZ/OrigoY)+Rust.sklon)*(OrigoY/cos(atan(OrigoZ/OrigoY)))+start.z;
	posunY = cos(atan(afterY/OrigoX)+Rust.rotace)*(OrigoX/cos(atan(afterY/OrigoX)))+start.y;
	posunX = sin(atan(afterY/OrigoX)+Rust.rotace)*(OrigoX/cos(atan(afterY/OrigoX)))+start.x; // vzcentrov8n9
	start =  XMFLOAT3(posunX,posunY,posunZ);
	Rust2.sklon = Rust1.sklon;
	Rust2.rotace=/*Rust.rotace*/ /*+ PI/2 +*/+ GenerateRndm(10,180)*PI/180;
	Rust2.r =Rust.r - GenerateRndm(111,999)/1000.f;
	tuplFloat3 tupla;
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
		//stridat=!stridat;
		if(GenerateRndm(0,9) == 1 | gnVetvi <= 0 || start.z >= height)
			konec = true;
		delka = GenerateRndm(222,555)/10.f; 
		//gnVetvi--;
		RostVetev(start, ending, Rust, Rust2, konec, delka,AxeRotace1, mezera, dens);  //je to tim ye prekalkulaci pocitam se starymi daty je to v startu

		/*if(GenerateRndm(0,9) == 1 | gnVetvi <= 0)
			konec = true;
		delka = GenerateRndm(222,555)/10.f; //TAHLE DZLKA IS MISPLACING THE VETEVSTARTPOS... 333 999/10.F no..ne*/
		gnVetvi--;
		//gnVetvi--;
		RostVetev(start1, ending, Rust, Rust1,konec, delka,AxeRotace1, mezera, dens); 
		
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
	float  OrigoX, OrigoY;
	//
	//NAPLNeni
	//
	for (float a = 2*PI; a> Dens; a-=Dens)																				//kruh
	{
		OrigoX=cos((float)a-sklonz) * r + radiusZ;
		OrigoY=cos(sklony)* (sin((float)a-sklonz)) * r ;
		Tvertices[vPoradi].Pos = XMFLOAT3(cos(atan(OrigoY/OrigoX)+sklonz)*(OrigoX/cos(atan(OrigoY/OrigoX))) + posunX,sin(atan(OrigoY/OrigoX)+sklonz)*(OrigoX/cos(atan(OrigoY/OrigoX)))+ posunY, Zkoord + sin(sklony)*(sin((float)a-sklonz)) * r + posunZ);
		//Tvertices[vPoradi].Color = XMFLOAT4(0.0f,a/5,1.0f,1.f);
		Tvertices[vPoradi].Color = Barva;
		vPoradi++;
	}
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

	//nTv = vPoradi;

	//WORD* Tindices = new WORD[nTi];
	//rotace =/*0;*/PI/4;
	//sklony=0;
	//posunX= 0;
	//posunY=0;
	float  OrigoX, OrigoY, MezoX, MezoY, MezoX1, MezoY1;
	for (float a = PI/2-(PI/2-acos(Uzk/r)); a<= PI*1.5f+(PI/2-acos(Uzk/r)); a+=Dens)																						//Pulkruh
	{

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
	//PosunX1 = cos(acos(Uzk2/r2))*(rp2 + r2);
	PosunX1 = /*cos(acos(Uzk/r))*(r + rp)*/ + sqrt(pow((r2 + rp), 2.f) - pow(sin(acos(Uzk/r))*(r + rp), 2));
	PodminkaX1 = -(cos(asin((sin(acos(Uzk/r))*(r + rp))/(r2 + rp)))*r2);
	for (float a = PI+acos(Uzk/r); a<= 3*PI-acos(Uzk/r); a+=Dens)																						//Vysece2 + pulkruh2
	{
		//if((cos((float)a)) * r2 >= PodminkaX1)
		//{
		//OrigoX=cos(sklonx)*((cos((float)a + sklonz)) * r2 + cos(sklonz)*cos(acos(Uzk/r))*(r + rp))+ cos(sklonz)*PosunX1+ posunX;
		//OrigoY=cos(sklonY1)* (sin((float)a + sklonz)  * r2 + sin(sklonz)*cos(acos(Uzk/r))*(r + rp)) /*+ PosunY + PosunY1*/ + sin(sklonz)*PosunX1 + posunY;

		if(a<=2*PI)
		{

			//	MezoX1 = (cos(a) * r2) + cos(acos(Uzk/r))*(r + rp)+ PosunX1;
			//	MezoY1 = (sin(a)  * r2) /*+ PosunY + PosunY1*/;

			OrigoX = (cos(a) * r2) + cos(acos(Uzk/r))*(r + rp)+ PosunX1;;//cos(atan((MezoY1)/MezoX1)+sklonz)*sqrt(pow(MezoX1,2.f) + pow((MezoY1),2.f));
			OrigoY = (sin(a)  * r2) /*+ PosunY + PosunY1*/;//sin(atan((MezoY1)/MezoX1)+sklonz)*sqrt(pow(MezoX1,2.f) + pow((MezoY1),2.f));
			//OrigoY=(sin(a-2*PI)  * r2) /*+ PosunY + PosunY1*/ ;
			MezoX =  cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))+rotace)*((OrigoX-(Uzk + cos(acos(Uzk/r))*rp))/cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))));
			MezoY =  sin(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))+rotace)*((OrigoX-(Uzk + cos(acos(Uzk/r))*rp))/cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))));

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
	//+ sqrt(pow((r2 + rp), 2.f) - pow(sin(acos(Uzk/r))*(r + rp), 2)) + cos(acos(Uzk/r))*(r + rp)
	/*for (float a = 0.f; a<= 2*PI; a+=Dens)																						//Vysece2 + pulkruh2
	{
	//if((cos((float)a)) * r2 >= PodminkaX1)
	//{
	//OrigoX=cos(sklonx)*((cos((float)a + sklonz)) * r2 + cos(sklonz)*cos(acos(Uzk/r))*(r + rp))+ cos(sklonz)*PosunX1+ posunX;
	//OrigoY=cos(sklonY1)* (sin((float)a + sklonz)  * r2 + sin(sklonz)*cos(acos(Uzk/r))*(r + rp)) /*+ PosunY + PosunY1*//* + sin(sklonz)*PosunX1 + posunY;

	OrigoX=cos(sklonx)*((cos((float)a)) * r2 + cos(acos(Uzk/r))*(r + rp))+ PosunX1+ posunX;
	OrigoY=cos(sklonY1)* (sin((float)a)  * r2) /*+ PosunY + PosunY1*/ /*+ posunY;

	Tvertices[vPoradi].Pos = XMFLOAT3(cos(atan(OrigoY/OrigoX)+sklonz)*sqrt(pow(OrigoX,2.f) + pow(OrigoY,2.f)),sin(atan(OrigoY/OrigoX)+sklonz)*sqrt(pow(OrigoX,2.f) + pow(OrigoY,2.f)),sin(sklonx)*((cos((float)a)) * r2+ cos(acos(Uzk/r))*(r + rp)) + /*PosunX1+ posunX +*//* sin(sklonY1)*(sin((float)a)) * r2   + Zkoord + posunZ);
	//Tvertices[vPoradi].Color = XMFLOAT4(1.f,1.f - a/2*PI,a/50,1.f);
	//TempR=sqrt(pow(OrigoY, 2.f) + pow(OrigoX, 2.f));
	//Tvertices[vPoradi].Pos = XMFLOAT3(OrigoX,OrigoY,sin(sklonx)*((cos((float)a)) * r2+ cos(acos(Uzk/r))*(r + rp)) + /*PosunX1+ posunX +*/ /*sin(sklonY1)*(sin((float)a)) * r2   + Zkoord + posunZ);
	vPoradi++;
	//}
	}*/

	/*for (float a = 0.f; a<= 2*PI; a+=Dens)																						//Vysece zruš podmínky jsou zbyteèné, vše staèí omezit alfou v deklaraci for cyklu....
	{
	if(cos((float)a) >= 0.f && cos((float)a) <= Uzk && sin((float)a) >= 0.f)
	{
	OrigoX=cos(sklonX1)* (cos((float)a) * r + posunX);
	OrigoY=cos(sklony)* (sin((float)a)) * r + posunY;


	Tvertices[vPoradi].Pos = XMFLOAT3(cos(atan(OrigoY/OrigoX)+sklonz)*sqrt(pow(OrigoX,2.f) + pow(OrigoY,2.f)),sin(atan(OrigoY/OrigoX)+sklonz)*sqrt(pow(OrigoX,2.f) + pow(OrigoY,2.f)),sin(sklonX1)*(cos((float)a) * r + posunX) + sin(sklony)*(sin((float)a)) * r + Zkoord + posunZ);
	//Tvertices[vPoradi].Color = XMFLOAT4(1.f,1.f - a/2*PI,a/50,1.f);
	vPoradi++;
	}
	}*/

	//float mezisklon = sklonX1;
	float PosunX, PosunY, PodminkaY, PodminkaX;
	PosunX = cos(acos(Uzk/r))*rp + Uzk;
	PosunY = sin(acos(Uzk/r))*(r + rp);
	//PodminkaY =  -sin(acos(Uzk/r));

	for (float a = PI+acos(Uzk/r); a<= PI*1.5; a+=Dens)																						//Prechod1
	{
		//sklonX11 -= ((sklonX11-sklonX11)/2)/(2*PI/Dens);
		//if(sin((float)a) <= PodminkaY && cos((float)a)*rp <= 0)
		//{
		OrigoX= cos(sklonX1)*(cos((float)a)*rp + PosunX);
		OrigoY=(sin((float)a)*rp + PosunY);
		MezoX =  cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))+rotace)*((OrigoX-(Uzk + cos(acos(Uzk/r))*rp))/cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))));
		MezoY =  sin(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))+rotace)*((OrigoX-(Uzk + cos(acos(Uzk/r))*rp))/cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))));

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


	for (float a = PI*1.5; a<= PI*1.5+asin(Uzk/r); a+=Dens)																						//Prechod2
	{
		//sklonX1 -= ((sklonX1-sklonX1)/2)/(2*PI/Dens);
		//if(cos((float)a)*rp2 + rp*(cos(acos(Uzk/r)) - sin(acos(Uzk/r))) >= 0)
		//if(cos((float)a) >= PodminkaY && cos((float)a) <= PodminkaX && rp2*sin((float)a) <= 0.f)
		//
		OrigoX=cos(sklonX1)*(cos((float)a)*rp + PosunX);
		OrigoY=(sin((float)a)*rp + PosunY);
		MezoX =  cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))+rotace)*((OrigoX-(Uzk + cos(acos(Uzk/r))*rp))/cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))));
		MezoY =  sin(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))+rotace)*((OrigoX-(Uzk + cos(acos(Uzk/r))*rp))/cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))));

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
	//sklonX1 = sklonX1;

	for (float a =0.5*PI; a>=  0.5*PI-asin(Uzk/r); a-=Dens)																							//Prechod2 dole
	{

		//sklonX1 -= ((sklonX1-sklonX1)/2)/(2*PI/Dens);
		//if(cos((float)a)*rp2 + rp*(cos(acos(Uzk/r)) - sin(acos(Uzk/r))) >= 0)
		//if(cos((float)a) >= PodminkaY && cos((float)a) <= PodminkaX && rp2*sin((float)a) >= 0.f)
		//{
		OrigoX=(cos((float)a)*rp2 ) + PosunX;
		OrigoY=(rp2*sin((float)a) - PosunY) ;

		MezoX =  cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))+rotace)*((OrigoX-(Uzk + cos(acos(Uzk/r))*rp))/cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))));
		MezoY =  sin(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))+rotace)*((OrigoX-(Uzk + cos(acos(Uzk/r))*rp))/cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))));

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

	for (float a = 0.5*PI+asin(Uzk/r); a>= 0.5*PI; a-=Dens)																						//Prechod1 dole
	{
		//sklonX11 -= ((sklonX11-sklonX11)/2)/(2*PI/Dens);
		//if(sin((float)a) >= PodminkaY && cos((float)a)*rp <= 0)
		//{
		OrigoX=cos(sklonX1)*(cos((float)a)*rp + PosunX );
		OrigoY=(sin((float)a)*rp - PosunY) ;

		MezoX =  cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))+rotace)*((OrigoX-(Uzk + cos(acos(Uzk/r))*rp))/cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))));
		MezoY =  sin(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))+rotace)*((OrigoX-(Uzk + cos(acos(Uzk/r))*rp))/cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))));

		Tvertices[vPoradi].Pos = XMFLOAT3(cos(atan((cos(sklony)*MezoY)/MezoX)+sklonz)*(MezoX/cos(atan((cos(sklony)*MezoY)/MezoX))) + posunX,sin(atan((cos(sklony)*MezoY)/MezoX)+sklonz)*(MezoX/cos(atan((cos(sklony)*MezoY)/MezoX)))+ posunY,/*PosunX1+ posunX +*/
			sin(sklony)*MezoY
			+ Zkoord + posunZ);
		Tvertices[vPoradi].Color = Barva;
		//Tvertices[vPoradi].Color = XMFLOAT4((a-PI*0.5)/asin(Uzk/r),0.f,1.f-(a-PI*0.5)/asin(Uzk/r),1.f);
		vPoradi++;
		//}
	}

	/*for (float a = 0.f; a<= 2*PI; a+=Dens)																						//Vysec dole
	{
	if(cos((float)a) >= 0.f && cos((float)a) <= Uzk && sin((float)a) <= 0.f)
	{
	OrigoX=cos(sklonX1)*(cos((float)a)* r + posunX) ;
	OrigoY=cos(sklony)* (sin((float)a)) * r + posunY;

	Tvertices[vPoradi].Pos = XMFLOAT3(cos(atan(OrigoY/OrigoX)+sklonz)*sqrt(pow(OrigoX,2.f) + pow(OrigoY,2.f)),sin(atan(OrigoY/OrigoX)+sklonz)*sqrt(pow(OrigoX,2.f) + pow(OrigoY,2.f)), sin(sklonX1)*(cos((float)a)* r +posunX) + sin(sklony)*(sin((float)a)) * r  + Zkoord + posunZ);
	//Tvertices[vPoradi].Color = XMFLOAT4(1.f,1.f - a/2*PI,a/50,1.f);
	vPoradi++;
	}
	}*/
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
	float delka = 100.f;
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