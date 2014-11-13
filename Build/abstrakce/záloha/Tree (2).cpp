#include "start.h"


SimpleVertex* Tvertices = NULL;
int vPoradi = 0;

void RostClanek(float r, float radiusZ, float sklony, float sklonz, float Dens, float posunX, float posunY, float posunZ);
void RostClanekRozdvojeni(float r, float rp, float r2, float radiusZ, float sklony, float sklonX1, float sklonY1, float sklonz,float rotace, float Dens, float Uzk, float posunX, float posunY, float posunZ, float tU);
void RostVetev(XMFLOAT3 start,XMFLOAT3 ending,float r,float delka,float sklon, float rotace, float mezera); //nevraci end
void RostRozdvojeni(XMFLOAT3 start,XMFLOAT3 ending,float r,float delka,float sklon, float rotace, float AxeRotace);
void RostOsy();


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
	RostClanek(r, rp, r2, sklonx, sklony,sklonX1,sklonY1, sklonz, Dens, Uzk, posunX, posunY, posunZ, tU);
	tU-=1.f;

	Uzk += 0.01;
	//sklonx -= PI/360;
	//sklonX1 += PI/360;
	//sklony += PI/180;
	//sklonz += 2*PI/180;
	//posunY+=0.01f;
	posunZ+=1.5f;
	rp+=0.1;

	//r+=0.01;
	//r2 +=0.1;
	rp2=rp;


	}*/
	XMFLOAT3 Start;
	XMFLOAT3 End;
	float r = 2.5f;
	float delka = 20.f;
	float rotace = PI/2;
	float sklon = -PI/3;//-89*PI/180;
	float mezera = 0.1f;
	Start.x = 0.0f;
	Start.y = 0.0f;
	Start.z = 0.0f;
	while(r==0)
	{
		r = GenerateRndm(111,555)/100.f;
	}

	//r=0;
	while(r==0)
	{
		r=GenerateRndm(0,9999)/50000.f;
	}
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

	/*for(int x = 0; x < 5000000; x++)	//waiting for rndm
	{
	}*/


	RostOsy();
	RostVetev(Start, End, r, delka, sklon, rotace, mezera);
	Start.z += 20;
	

	/*Start.z = 0.02*10 * 110;
	for (float i = 10.f; i>1.0;i-=1.f)
	{
		//Start.z += 0.02*i *100;
		RostRozdvojeni(Start, End, sqrt(i), delka, sklon, rotace);
		Start.z = 0.02*i *100;
	}*/

	return Tvertices;
}

void RostVetev(XMFLOAT3 start,XMFLOAT3 ending,float r,float delka,float sklon, float rotace, float mezera)//vraci end
{
	float PI = 3.14159265358979323846;						
	float ample, per; //radius krouceni
	float sklony = 0.f; //=uhel v rad, sklonx
	float radiusZ = 0;
	float sklonz = 0;
	float posunX, posunY, posunZ;
	posunX = 0.f;
	posunY = 0.f;
	posunZ = 0.f;
	float Dens = 1.f* PI/180;
	float Zkoord = 0.0f;
	ample= 1.f;
	per = 2*PI/100.f;
	sklonz = 0;
	float OrigoY = 1.f;
	float afterY = 0.f;
	float OrigoX = 0.f;
	float OrigoZ = 0.f;
	float Xorigin = start.x;
	float Yorigin = start.y;
	float Zorigin = 0.01+start.z;
	float Rorigin = r;
	sklony = PI/2 +sklon;
	sklonz = PI/2 -rotace; 
	OrigoZ = Zorigin;
	for (float x = 0.f; x<= 0.f; x+=1.f)
	{
		//sklon += 10*PI/180;
		//sklony = PI/2 +sklon;
		//OrigoZ = 0;
		for (float x = 0.f; x< delka/mezera; x+=1.f)
		{

			//ample+=0.005f;

			//sklony+=PI/(180*4);
			//sklonz-=((2*PI*0.01f)/(4*ample));
			//posunX+=1.f;
			//sklon = PI/4;
			//per+=0.005f;
			OrigoZ+=mezera;
			OrigoX = Xorigin + sin(per*OrigoZ/**100*PI/(180)*/)*ample;
			//OrigoX = 1.1f;
			//OrigoY = 1.0f;
			OrigoY = Yorigin + cos(per*OrigoZ/**100*PI/(180)*/)*ample;
			//sklon += PI/(180*8);
			//sklony = PI/2 +sklon;
			//rotace += 0.2*PI/180;
			afterY = sin(atan(OrigoZ/OrigoY)+sklon)*(OrigoY/cos(atan(OrigoZ/OrigoY)));
			posunZ = cos(atan(OrigoZ/OrigoY)+sklon)*(OrigoY/cos(atan(OrigoZ/OrigoY)));
			posunY = cos(atan(afterY/OrigoX)+rotace)*(OrigoX/cos(atan(afterY/OrigoX)));
			posunX = sin(atan(afterY/OrigoX)+rotace)*(OrigoX/cos(atan(afterY/OrigoX)));
			//cos(atan(OrigoY/OrigoX)+rotace)*(OrigoX/cos(atan(OrigoY/OrigoX)));
			//rotacey=acos(posunY/ample);
			RostClanek(r, radiusZ, sklony, sklonz, Dens, posunX, posunY, posunZ);
			
		}
	} 
	start.x = Xorigin + sin(per*OrigoZ/**100*PI/(180)*/)*ample;
	start.y = Yorigin + cos(per*OrigoZ/**100*PI/(180)*/)*ample;
	start.z += delka;
	//rotace -= PI/2;
	if(start.z < 100.f)
	RostRozdvojeni(start, ending, r, delka, sklon, rotace,0);

}

void RostRozdvojeni(XMFLOAT3 start,XMFLOAT3 ending,float r,float delka,float sklon, float rotace,float AxeRotace)//vraci end
{
	float PI = 3.14159265358979323846;						
	//nTv = 0;
	//nTi = 0;
	//float r = 1.0f; //radius
	float rp = 0.0f; //radius prechodu
	float r2 = 0.1f; //radius															VŠECHNO JSOU RADIÁNY
	float rp2 = rp; //radius prechodu 
	float ample, per; //radius krouceni
	//int vPoradi = 0;
	float sklony = 0.f; //=uhel v rad, sklonx
	float radiusZ = 0;
	float sklonX1 = 0.f; //=uhel v rad, sklonx
	float sklonY1 = 0;
	float sklonz = 0;
	//float Uzk2;	//uzkost2
	float Uzk; //uzkost

	float posunX, posunY, posunZ;
	posunX = 0.f;
	posunY = 0.f;
	posunZ = 0.f;
	float Dens = 1.f* PI/180;
	float	Zkoord = 0.0f;
	Uzk = 0.0f;


	rp=0.f;
	rp2=rp;
	//Uzk = 0.01;

	RostOsy();
	float tU = 1.f;


	ample= 0.0f;
	per = 2*PI/100.f;
	sklonz = 0;

	float OrigoY = 1.f;
	float afterY = 0.f;
	float OrigoX = 0.f;
	float OrigoZ = 0.f;

	float Xorigin = start.x;
	float Yorigin = start.y;
	float Zorigin = 0.01 + start.z;
	float Rorigin = r;
	r2=r;
	while(Rorigin==0)
	{
		Rorigin = GenerateRndm(111,555)/100.f;
	}




	sklony = PI/2 +sklon;
	sklonz = PI/2 -rotace; 
	OrigoZ = Zorigin;
	ample= 0.0f;
	per = 2*PI/10.f;

	float rot = 0.f;


	for (float x = 0.f; x<= 0.f; x+=1.f)
	{
		//sklon += 100*PI/180;
		sklony = PI/2 +sklon;
		//OrigoZ =  Zorigin;
		for (float x = 0.f; x<= 110.f; x+=1.f)
		{
			//r = (sqrt((float)1+4*x)-1)/2;							//sklenice kvadraticka
			//r2=r;
			//sklonx=0;
			//posunX=10.01f;
			//rp=GenerateRndm(0,180);		
			//Uzk+=0.05f;
			//r=0;
			while(r==0)
			{
				r=Rorigin + GenerateRndm(0,9999)/50000.f;
			}

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

			/*for(int x = 0; x < 5000000; x++)	//waiting for rndm
			{
			}*/

			//ample+=0.005f;

			//sklony+=PI/(180*4);
			//sklonz-=((2*PI*0.01f)/(4*ample));
			Uzk += r* 0.0079f;
			//posunX+=1.f;
			//sklon = PI/4;
			OrigoZ+= r * 0.02f;
			//per+=0.005f;
			OrigoX = Xorigin + sin(per*OrigoZ/**100*PI/(180)*//*-ample/2*/)*ample;
			//OrigoX = 1.1f;
			//OrigoY = 1.0f;
			OrigoY = Yorigin;// + sin(per*OrigoZ/**100*PI/(180)*/)*ample;
			//sklon += PI/(180*8);
			//sklony = PI/2 +sklon;
			//rotace += 0.2*PI/180;
			afterY = sin(atan(OrigoZ/OrigoY)+sklon)*(OrigoY/cos(atan(OrigoZ/OrigoY)));
			posunZ = cos(atan(OrigoZ/OrigoY)+sklon)*(OrigoY/cos(atan(OrigoZ/OrigoY)));
			posunY = cos(atan(afterY/OrigoX)+rotace)*(OrigoX/cos(atan(afterY/OrigoX)));
			posunX = sin(atan(afterY/OrigoX)+rotace)*(OrigoX/cos(atan(afterY/OrigoX))); // vzcentrov8n9
			//cos(atan(OrigoY/OrigoX)+rotace)*(OrigoX/cos(atan(OrigoY/OrigoX)));
			//rotacey=acos(posunY/ample);

			
			//sklony = sklon;
			/*
			sklony=PI/2;
			sklonz=x*PI/180;
			posunX = 10.f;
			posunY = 3.f;
			posunZ = 2.f;
			radiusZ = 10.f;*/
			//posunX=cos(x*PI/180)*ample;
			//posunY=sin(x*PI/180)*ample;
			rot += PI/180;
			RostClanekRozdvojeni(r, rp, r2, radiusZ, sklony,sklonX1,sklonY1, sklonz,rot, Dens, Uzk, posunX, posunY, posunZ, tU);
			
			tU-=1.f;
			//sklonx += PI/180;
			//sklonX1 -= PI/2;
			//sklony +=1* PI/180;
			//sklonz += 1* PI/180;
			//posunX=0.0f;
			//posunY+=0.1f;
			//posunZ+=0.1f;
			rp=0.1*r;
			//sklonz=0;
			//r+=0.01;
			//r2 +=0.1;
			rp2=rp;
			//r2=r;
		}
	}
	
	
	
	//Xorigin += (Uzk + cos(acos(Uzk/r))*rp);

	//start.x -=/*(Xorigin + sin(per*OrigoZ)*ample)*/  (Uzk + cos(acos(Uzk/r))*rp);
	//start.y =Yorigin;
	start.z += r * 0.02f * 111;
	//r-=0.1f;
	RostVetev(start, ending, r, delka, sklon, rotace, 0.1);
	//start.x += 2*(Uzk + cos(acos(Uzk/r))*rp);
	RostVetev(start, ending, r, delka, sklon, rotace, 0.1);
}

void RostClanek(float r, float radiusZ, float sklony, float sklonz, float Dens, float posunX, float posunY, float posunZ)
{
	float Zkoord = 0.0f;
	float PI = 3.14159265358979323846;
	float  OrigoX, OrigoY;
	//
	//NAPLNeni
	//
	for (float a = 2*PI; a>= 0.f; a-=Dens)																				//kruh
	{
		OrigoX=cos((float)a-sklonz) * r + radiusZ;
		OrigoY=cos(sklony)* (sin((float)a-sklonz)) * r ;
		Tvertices[vPoradi].Pos = XMFLOAT3(cos(atan(OrigoY/OrigoX)+sklonz)*(OrigoX/cos(atan(OrigoY/OrigoX))) + posunX,sin(atan(OrigoY/OrigoX)+sklonz)*(OrigoX/cos(atan(OrigoY/OrigoX)))+ posunY, Zkoord + sin(sklony)*(sin((float)a-sklonz)) * r + posunZ);
		Tvertices[vPoradi].Color = XMFLOAT4(0.0f,a/5,1.0f,1.f);
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
	rotace =25* PI/180;

	float  OrigoX, OrigoY, MezoX, MezoY;
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
		Tvertices[vPoradi].Color = XMFLOAT4((a-(PI/2))/PI,1.f - (a-(PI/2))/PI,0.f,1.f);
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
		OrigoX=(cos((float)a)) * r2 + cos(acos(Uzk/r))*(r + rp)+ PosunX1;
		OrigoY=(sin((float)a)  * r2) /*+ PosunY + PosunY1*/ ;
		MezoX = cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))+rotace)*((OrigoX-(Uzk + cos(acos(Uzk/r))*rp))/cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))));
		MezoY = sin(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))+rotace)*((OrigoX-(Uzk + cos(acos(Uzk/r))*rp))/cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))));

		if(a<=2*PI)
		{

			Tvertices[vPoradi].Pos = XMFLOAT3(cos(atan((cos(sklony)*MezoY)/MezoX)+sklonz)*sqrt(pow(MezoX,2.f) + pow((cos(sklony)*MezoY),2.f)) + posunX,sin(atan((cos(sklony)*MezoY)/MezoX)+sklonz)*sqrt(pow(MezoX,2.f) + pow((cos(sklony)*MezoY),2.f))+ posunY,/*PosunX1+ posunX +*/ sin(sklony)*MezoY   + Zkoord + posunZ);
			Tvertices[vPoradi].Color = XMFLOAT4((a-PI-acos(Uzk/r))/(2*(PI-acos(Uzk/r))),1.f - (a-PI-acos(Uzk/r))/(2*(PI-acos(Uzk/r))),0.f,1.f);
			//TempR=sqrt(pow(OrigoY, 2.f) + pow(OrigoX, 2.f));
			//Tvertices[vPoradi].Pos = XMFLOAT3(OrigoX,OrigoY,sin(sklonx)*((cos((float)a)) * r2+ cos(acos(Uzk/r))*(r + rp)) + /*PosunX1+ posunX +*/ sin(sklonY1)*(sin((float)a)) * r2   + Zkoord + posunZ);

		}
		else
		{
		OrigoX=(cos((float)a)) * r2 + cos(acos(Uzk/r))*(r + rp)+ PosunX1;
		float OrigoY1=(sin(a-2*PI)  * r2) /*+ PosunY + PosunY1*/ ;
		MezoX = cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))+rotace)*((OrigoX-(Uzk + cos(acos(Uzk/r))*rp))/cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))));
		MezoY = sin(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))+rotace)*((OrigoX-(Uzk + cos(acos(Uzk/r))*rp))/cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))));
			//OrigoY=(sin(a-2*PI)  * r2) /*+ PosunY + PosunY1*/ ;
			Tvertices[vPoradi].Pos = XMFLOAT3(cos(atan((cos(sklony)*MezoY)/MezoX)+sklonz)*sqrt(pow(MezoX,2.f) + pow((cos(sklony)*MezoY),2.f)) + posunX,sin(atan((cos(sklony)*MezoY)/MezoX)+sklonz)*sqrt(pow(MezoX,2.f) + pow((cos(sklony)*MezoY),2.f))+ posunY,/*PosunX1+ posunX +*/ 
				//sin(sklony)*sin(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))+rotace)*((OrigoX-(Uzk + cos(acos(Uzk/r))*rp))/cos(atan(OrigoY/(OrigoX-(Uzk + cos(acos(Uzk/r))*rp)))))
				sin(sklony)*OrigoY1
				+ Zkoord + posunZ);
			Tvertices[vPoradi].Color = XMFLOAT4(0.f,1.f - (a-PI-acos(Uzk/r))/(2*(PI-acos(Uzk/r))),(a-PI-acos(Uzk/r))/(2*(PI-acos(Uzk/r))),1.f);
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
	Tvertices[vPoradi].Color = XMFLOAT4(1.f,1.f - a/2*PI,a/50,1.f);
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
	Tvertices[vPoradi].Color = XMFLOAT4(1.f,1.f - a/2*PI,a/50,1.f);
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
		OrigoX=cos(sklonX1)*(cos((float)a)*rp + PosunX);
		OrigoY=cos(sklony)*(sin((float)a)*rp + PosunY);
		MezoX = cos(atan(OrigoY/OrigoX)+rotace)*(OrigoX/cos(atan(OrigoY/OrigoX)));
		MezoY = sin(atan(OrigoY/OrigoX)+rotace)*(OrigoX/cos(atan(OrigoY/OrigoX)));
		Tvertices[vPoradi].Pos = XMFLOAT3(cos(atan(MezoY/MezoX)+sklonz)*sqrt(pow(MezoX,2.f) + pow(MezoY,2.f)) + posunX-(Uzk + cos(acos(Uzk/r))*rp),sin(atan(MezoY/MezoX)+sklonz)*sqrt(pow(MezoX,2.f) + pow(MezoY,2.f))+ posunY,sin(sklonX1)*(cos((float)a)*rp + PosunX) + sin(sklony)*(sin((float)a)*rp + PosunY)  + Zkoord + posunZ);
		Tvertices[vPoradi].Color = XMFLOAT4((a-PI-acos(Uzk/r))/(0.5*PI-acos(Uzk/r)),1.f - (a-PI-acos(Uzk/r))/(0.5*PI-acos(Uzk/r)),0.f,1.f);
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
		OrigoY=cos(sklony)*(sin((float)a)*rp + PosunY);

		//cos(atan(OrigoY/OrigoX)+sklonz)*sqrt(pow(OrigoX,2.f) + pow(OrigoY,2.f))

		Tvertices[vPoradi].Pos = XMFLOAT3(cos(atan(OrigoY/OrigoX)+sklonz)*sqrt(pow(OrigoX,2.f) + pow(OrigoY,2.f)) + posunX,sin(atan(OrigoY/OrigoX)+sklonz)*sqrt(pow(OrigoX,2.f) + pow(OrigoY,2.f))+ posunY,sin(sklony)*(rp2*sin((float)a) + PosunY)  + Zkoord + posunZ);
		Tvertices[vPoradi].Color = XMFLOAT4(1.f-(a-PI*1.5)/asin(Uzk/r),0.f,(a-PI*1.5)/asin(Uzk/r),1.f);
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
		OrigoY=cos(sklony)*(rp2*sin((float)a) - PosunY) ;

		Tvertices[vPoradi].Pos = XMFLOAT3(cos(atan(OrigoY/OrigoX)+sklonz)*sqrt(pow(OrigoX,2.f) + pow(OrigoY,2.f)) + posunX, sin(atan(OrigoY/OrigoX)+sklonz)*sqrt(pow(OrigoX,2.f) + pow(OrigoY,2.f))+ posunY,sin(sklony)*(rp2*sin((float)a) - PosunY)  + Zkoord + posunZ);
		Tvertices[vPoradi].Color = XMFLOAT4(0.f,1.f-(a-PI*0.5+asin(Uzk/r))/asin(Uzk/r),(a-PI*0.5+asin(Uzk/r))/asin(Uzk/r),1.f);
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
		OrigoY=cos(sklony)*(sin((float)a)*rp - PosunY) ;

		Tvertices[vPoradi].Pos = XMFLOAT3(cos(atan(OrigoY/OrigoX)+sklonz)*sqrt(pow(OrigoX,2.f) + pow(OrigoY,2.f)) + posunX,sin(atan(OrigoY/OrigoX)+sklonz)*sqrt(pow(OrigoX,2.f) + pow(OrigoY,2.f))+ posunY,sin(sklonX1)*(cos((float)a)*rp + PosunX ) + sin(sklony)*(sin((float)a)*rp - PosunY)  + Zkoord + posunZ);
		Tvertices[vPoradi].Color = XMFLOAT4((a-PI*0.5)/asin(Uzk/r),0.f,1.f-(a-PI*0.5)/asin(Uzk/r),1.f);
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
	Tvertices[vPoradi].Color = XMFLOAT4(1.f,1.f - a/2*PI,a/50,1.f);
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