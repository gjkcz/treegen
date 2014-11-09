#include "start.h"


SimpleVertex* Tvertices = NULL;
int vPoradi = 0;

void RostClanek(float r, float rp, float r2, float sklonx, float sklony, float sklonX1, float sklonY1, float sklonz, float Dens, float Uzk, float posunX, float posunY, float posunZ, float tU);
void RostOsy();


SimpleVertex*  GenerateTree(int nVetvi, int vPoradi, int nTv)
{
	float PI = 3.14159265358979323846;
	//nTv = 0;
	//nTi = 0;
	float r = 0.0f; //radius
	float rp = 0.0f; //radius prechodu
	float r2 = 0.0f; //radius															VŠECHNO JSOU RADIÁNY
	float rp2 = rp; //radius prechodu
	//int vPoradi = 0;
	float sklonx = 0.f; //=uhel v rad, sklonx
	float sklony = 0;
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

	rp=0.f;
	rp2=rp;
	Uzk = 0.0;

	RostOsy();
	float tU = 1.f;
	r2=0;
	sklonx=0;
	//sklonz = -90* PI/180;
	for (float x = 0.f; x<= 360.f; x+=1.f)
	{
		//r = (sqrt((float)1+4*x)-1)/2;							//sklenice kvadraticka
		//r2=r;
		//sklonx=0;
		//posunX=10.01f;
		//rp=GenerateRndm(0,180);		
		r=0;
		while(r==0)
		{
			r= 1.5f + GenerateRndm(0,9999)/100000.f;
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

		for(int x = 0; x < 5000000; x++)
		{
		}
		RostClanek(r, rp, r2, sklonx, sklony,sklonX1,sklonY1, sklonz, Dens, Uzk, posunX, posunY, posunZ, tU);
		tU-=1.f;

		//Uzk = 0.3;
		sklonx += PI/180;
		//sklonX1 -= PI/2;
		//sklony +=45* PI/180;
		sklonz += PI/180;
		//posunX+=0.1f;
		//posunY+=0.1f;
		posunZ+=0.1f;
		//rp=1.0;8
		//sklonz=0;
		//r+=0.01;
		//r2 +=0.1;
		rp2=rp;
		//r2=r;
	}
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
	return Tvertices;
}

void RostClanek(float r, float rp, float r2, float sklonx, float sklony, float sklonX1, float sklonY1, float sklonz, float Dens, float Uzk, float posunX, float posunY, float posunZ, float tU)
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

	if (r2==0.f)
	{

		for (float a = 2*PI; a>= 0.f; a-=Dens)																				//kruh
		{
			//Tvertices[vPoradi].Pos = XMFLOAT3(( cos((float)((a * 3.14)/180))) * r, (sin((float)a)) * r, Zkoord);			//NICE FILTER
			Tvertices[vPoradi].Pos = XMFLOAT3((cos(sklonx)* (cos((float)a+sklonz) * r + posunX)),cos(sklony)* (sin((float)a+sklonz)) * r + posunY, Zkoord + sin(sklonx)*(cos((float)a) * r + posunX) + sin(sklony)*(sin((float)a)) * r + posunZ);			

			//Tvertices[vPoradi].Tex = XMFLOAT2(tU,tV/(2*PI/Dens));
			Tvertices[vPoradi].Color = XMFLOAT4(1.f,a/6,a/50,1.f);
			tV++;

			Tvertices[vPoradi].Normal = XMFLOAT3((cos(sklonx)* (cos((float)a) * r + posunX)),cos(sklony)* (sin((float)a)) * r + posunY,0.0f);


			vPoradi++;
		}
		tV=0;



	}
	else
	{
		float  OrigoX, OrigoY;

		for (float a = PI/2-(PI/2-acos(Uzk/r)); a<= PI*1.5f+(PI/2-acos(Uzk/r)); a+=Dens)																						//Pulkruh
		{
			

				OrigoX=cos(sklonX1)* (cos((float)a+sklonz) * r + posunX);
				OrigoY=cos(sklony)* (sin((float)a+sklonz)) * r - posunY;

				//Tvertices[vPoradi].Pos = XMFLOAT3(( cos((float)((a * 3.14)/180))) * r, (sin((float)a)) * r, Zkoord);			//NICE FILTER
				Tvertices[vPoradi].Pos = XMFLOAT3(OrigoX,OrigoY, Zkoord + sin(sklonX1)*(cos((float)a) * r + posunX) + sin(sklony)*(sin((float)a)) * r + posunZ);		
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
				OrigoX=cos(sklonx)*((cos((float)a)) * r2 + cos(acos(Uzk/r))*(r + rp))+ PosunX1+ posunX;
				OrigoY=cos(sklonY1)* (sin((float)a)  * r2) /*+ PosunY + PosunY1*/ + posunY;
			if(a<=2*PI)
			{
				

				Tvertices[vPoradi].Pos = XMFLOAT3(cos(atan(OrigoY/OrigoX)+sklonz)*sqrt(pow(OrigoX,2.f) + pow(OrigoY,2.f)),sin(atan(OrigoY/OrigoX)+sklonz)*sqrt(pow(OrigoX,2.f) + pow(OrigoY,2.f)),sin(sklonx)*((cos((float)a)) * r2+ cos(acos(Uzk/r))*(r + rp)) + /*PosunX1+ posunX +*/ sin(sklonY1)*(sin((float)a)) * r2   + Zkoord + posunZ);
				Tvertices[vPoradi].Color = XMFLOAT4((a-PI-acos(Uzk/r))/(2*(PI-acos(Uzk/r))),1.f - (a-PI-acos(Uzk/r))/(2*(PI-acos(Uzk/r))),0.f,1.f);
				//TempR=sqrt(pow(OrigoY, 2.f) + pow(OrigoX, 2.f));
				//Tvertices[vPoradi].Pos = XMFLOAT3(OrigoX,OrigoY,sin(sklonx)*((cos((float)a)) * r2+ cos(acos(Uzk/r))*(r + rp)) + /*PosunX1+ posunX +*/ sin(sklonY1)*(sin((float)a)) * r2   + Zkoord + posunZ);
				
			}
			else
			{

				Tvertices[vPoradi].Pos = XMFLOAT3(cos(atan(OrigoY/OrigoX)+sklonz)*sqrt(pow(OrigoX,2.f) + pow(OrigoY,2.f)),sin(atan(OrigoY/OrigoX)+sklonz)*sqrt(pow(OrigoX,2.f) + pow(OrigoY,2.f)),sin(sklonx)*((cos(a-2*PI)) * r2+ cos(acos(Uzk/r))*(r + rp)) + /*PosunX1+ posunX +*/ sin(sklonY1)*(sin(a-2*PI)) * r2   + Zkoord + posunZ);
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
				OrigoX=cos(sklonX1)*(cos((float)a)*rp + PosunX+ posunX);
				OrigoY=cos(sklony)*(sin((float)a)*rp + PosunY) + posunY;

				Tvertices[vPoradi].Pos = XMFLOAT3(cos(atan(OrigoY/OrigoX)+sklonz)*sqrt(pow(OrigoX,2.f) + pow(OrigoY,2.f)),sin(atan(OrigoY/OrigoX)+sklonz)*sqrt(pow(OrigoX,2.f) + pow(OrigoY,2.f)),sin(sklonX1)*(cos((float)a)*rp + PosunX+ posunX) + sin(sklony)*(sin((float)a)*rp + PosunY)  + Zkoord + posunZ);
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
			//{
				OrigoX=cos(sklonx)*(cos((float)a  )*rp2 + posunX)  + PosunX;
				OrigoY=cos(sklonY1)*(rp2*sin((float)a ) + posunX + PosunY)  + posunY;

				//cos(atan(OrigoY/OrigoX)+sklonz)*sqrt(pow(OrigoX,2.f) + pow(OrigoY,2.f))

				Tvertices[vPoradi].Pos = XMFLOAT3(cos(atan(OrigoY/OrigoX)+sklonz)*sqrt(pow(OrigoX,2.f) + pow(OrigoY,2.f)),sin(atan(OrigoY/OrigoX)+sklonz)*sqrt(pow(OrigoX,2.f) + pow(OrigoY,2.f)),sin(sklonx)*(cos((float)a)*rp2 + posunX) + sin(sklonY1)*(rp2*sin((float)a) + PosunY)  + Zkoord + posunZ);
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
				OrigoX=cos(sklonx)*(cos((float)a)*rp2 + posunX) + PosunX;
				OrigoY=cos(sklonY1)*(rp2*sin((float)a) - PosunY) + posunY;

				Tvertices[vPoradi].Pos = XMFLOAT3(cos(atan(OrigoY/OrigoX)+sklonz)*sqrt(pow(OrigoX,2.f) + pow(OrigoY,2.f)), sin(atan(OrigoY/OrigoX)+sklonz)*sqrt(pow(OrigoX,2.f) + pow(OrigoY,2.f)),sin(sklonx)*(cos((float)a)*rp2 + posunX) + sin(sklonY1)*(rp2*sin((float)a) - PosunY)  + Zkoord + posunZ);
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
				OrigoX=cos(sklonX1)*(cos((float)a)*rp + PosunX + posunX);
				OrigoY=cos(sklony)*(sin((float)a)*rp - PosunY) + posunY;

				Tvertices[vPoradi].Pos = XMFLOAT3(cos(atan(OrigoY/OrigoX)+sklonz)*sqrt(pow(OrigoX,2.f) + pow(OrigoY,2.f)),sin(atan(OrigoY/OrigoX)+sklonz)*sqrt(pow(OrigoX,2.f) + pow(OrigoY,2.f)),sin(sklonX1)*(cos((float)a)*rp + PosunX + posunX) + sin(sklony)*(sin((float)a)*rp - PosunY)  + Zkoord + posunZ);
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
//	vPoradi=361;
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
		vPoradi++;

		if((int)a%100 == 0 && ((int)((a-(int)a)*axDens) % (int)(axDens) == 0))
		{
			for (int b = 0; b <= 50; b++)												//osa x
			{
				Tvertices[vPoradi].Pos = XMFLOAT3(a , (float)b/100, 0.0f);
				vPoradi++;
			}
		}
		else if((int)a % 10 == 0 && ((int)(a*axDens) % (int)(axDens) == 0))
		{
			for (int b = 0; b <= 25; b++)												//osa x
			{
				Tvertices[vPoradi].Pos = XMFLOAT3(a, (float)b/100, 0.0f);
				vPoradi++;
			}
		}
		else if((int)a % 1 == 0 && ((int)(a*axDens) % (int)(axDens) == 0))
		{
			for (int b = 0; b <= 10; b++)												//osa x
			{
				Tvertices[vPoradi].Pos = XMFLOAT3(a, (float)b/100, 0.0f);
				vPoradi++;
			}
		}

	}


	for (float a = origin; a <= delka; a+=1/axDens)												//osa x
	{
		Tvertices[vPoradi].Pos = XMFLOAT3(0.f, a, 0.0f);
		vPoradi++;

		if((int)a%100 == 0 && ((int)((a-(int)a)*axDens) % (int)(axDens) == 0))
		{
			for (int b = 0; b <= 50; b++)												//osa x
			{
				Tvertices[vPoradi].Pos = XMFLOAT3((float)b/100, a, 0.0f);
				vPoradi++;
			}
		}
		else if((int)a % 10 == 0 && ((int)(a*axDens) % (int)(axDens) == 0))
		{
			for (int b = 0; b <= 25; b++)												//osa x
			{
				Tvertices[vPoradi].Pos = XMFLOAT3((float)b/100, a, 0.0f);
				vPoradi++;
			}
		}
		else if((int)a % 1 == 0 && ((int)(a*axDens) % (int)(axDens) == 0))
		{
			for (int b = 0; b <= 10; b++)												//osa x
			{
				Tvertices[vPoradi].Pos = XMFLOAT3((float)b/100,a, 0.0f);
				vPoradi++;
			}
		}

	}

	for (float a = origin; a <= delka; a+=1/axDens)												//osa x
	{
		Tvertices[vPoradi].Pos = XMFLOAT3(0.f, 0.f, a);
		vPoradi++;

		if((int)a%100 == 0 && ((int)((a-(int)a)*axDens) % (int)(axDens) == 0))
		{
			for (int b = 0; b <= 50; b++)												//osa x
			{
				Tvertices[vPoradi].Pos = XMFLOAT3(0.f , (float)b/100, a);
				vPoradi++;
			}
		}
		else if((int)a % 10 == 0 && ((int)(a*axDens) % (int)(axDens) == 0))
		{
			for (int b = 0; b <= 25; b++)												//osa x
			{
				Tvertices[vPoradi].Pos = XMFLOAT3(0.f, (float)b/100, a);
				vPoradi++;
			}
		}
		else if((int)a % 1 == 0 && ((int)(a*axDens) % (int)(axDens) == 0))
		{
			for (int b = 0; b <= 10; b++)												//osa x
			{
				Tvertices[vPoradi].Pos = XMFLOAT3(0.f, (float)b/100, a);
				vPoradi++;
			}
		}
	}

	for (float a = origin; a >= -delka; a-=1.f/axDens)												//osa x
	{
		Tvertices[vPoradi].Pos = XMFLOAT3(a, 0.f, 0.0f);
		vPoradi++;

		if((int)a%100 == 0 && ((int)((a-(int)a)*axDens) % (int)(axDens) == 0))
		{
			for (int b = 0; b <= 50; b++)												//osa x
			{
				Tvertices[vPoradi].Pos = XMFLOAT3(a , (float)b/100, 0.0f);
				vPoradi++;
			}
		}
		else if((int)a % 10 == 0 && ((int)(a*axDens) % (int)(axDens) == 0))
		{
			for (int b = 0; b <= 25; b++)												//osa x
			{
				Tvertices[vPoradi].Pos = XMFLOAT3(a, (float)b/100, 0.0f);
				vPoradi++;
			}
		}
		else if((int)a % 1 == 0 && ((int)(a*axDens) % (int)(axDens) == 0))
		{
			for (int b = 0; b <= 10; b++)												//osa x
			{
				Tvertices[vPoradi].Pos = XMFLOAT3(a, (float)b/100, 0.0f);
				vPoradi++;
			}
		}

	}


	for (float a = origin; a >= -delka; a-=1/axDens)												//osa x
	{
		Tvertices[vPoradi].Pos = XMFLOAT3(0.f, a, 0.0f);
		vPoradi++;

		if((int)a%100 == 0 && ((int)((a-(int)a)*axDens) % (int)(axDens) == 0))
		{
			for (int b = 0; b <= 50; b++)												//osa x
			{
				Tvertices[vPoradi].Pos = XMFLOAT3((float)b/100, a, 0.0f);
				vPoradi++;
			}
		}
		else if((int)a % 10 == 0 && ((int)(a*axDens) % (int)(axDens) == 0))
		{
			for (int b = 0; b <= 25; b++)												//osa x
			{
				Tvertices[vPoradi].Pos = XMFLOAT3((float)b/100, a, 0.0f);
				vPoradi++;
			}
		}
		else if((int)a % 1 == 0 && ((int)(a*axDens) % (int)(axDens) == 0))
		{
			for (int b = 0; b <= 10; b++)												//osa x
			{
				Tvertices[vPoradi].Pos = XMFLOAT3((float)b/100,a, 0.0f);
				vPoradi++;
			}
		}

	}

	for (float a = origin; a >= -delka; a-=1/axDens)												//osa x
	{
		Tvertices[vPoradi].Pos = XMFLOAT3(0.f, 0.f, a);
		vPoradi++;

		if((int)a%100 == 0 && ((int)((a-(int)a)*axDens) % (int)(axDens) == 0))
		{
			for (int b = 0; b <= 50; b++)												//osa x
			{
				Tvertices[vPoradi].Pos = XMFLOAT3(0.f , (float)b/100, a);
				vPoradi++;
			}
		}
		else if((int)a % 10 == 0 && ((int)(a*axDens) % (int)(axDens) == 0))
		{
			for (int b = 0; b <= 25; b++)												//osa x
			{
				Tvertices[vPoradi].Pos = XMFLOAT3(0.f, (float)b/100, a);
				vPoradi++;
			}
		}
		else if((int)a % 1 == 0 && ((int)(a*axDens) % (int)(axDens) == 0))
		{
			for (int b = 0; b <= 10; b++)												//osa x
			{
				Tvertices[vPoradi].Pos = XMFLOAT3(0.f, (float)b/100, a);
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