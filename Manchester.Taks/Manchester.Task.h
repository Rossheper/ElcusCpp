// Manchester.Taks.h
#include "Manchester.CollectDataPz.h"
#pragma once

using namespace System;

namespace ManchesterTask {

	public ref class PZ
	{
	private:
		static const int Zn = 2;
		static const int Zm = 9;
		static const double M_PI = 3.14159265358979323846;
		static const int _dmax = 80000;
		static const int v0 = 46;
		static const short num_col_mpn = 3;
		static const short num_row_mpn = 3;
		static const short num_row_pz_write_buffer = 2;
		static const short num_col_pz_write_buffer = 32;

		CollectDataPz ^_CollPz;
		Dictionary<String^,String^>^ _currGrid;
		unsigned int _X;
		unsigned int _Y;
		unsigned int _Z;
		unsigned int _eps0;		
		unsigned int _beta0;		
		unsigned int _B0;
		unsigned int _L0;
		int _Qo;
		unsigned int _psy0;
		short _K;
		short _Ukvp;
		short _Qtr;
		short _Fgsn;
		unsigned short _Dpry;
		short _Pg;
		short _FTM;
		unsigned short _Kren;
		unsigned int _Dnc;
		unsigned short _Dbn;
		int _Dpr;
		unsigned short _Kop;
		unsigned short _Kd;
		unsigned short _V0x;
		unsigned short _V0y;
		array<array<unsigned short>^>^ _buffer_pz_write;
		//unsigned short ** _buffer_pz_write;

		// TODO: здесь следует добавить свои методы для этого класса.
		double Interp(double curX, double x1, double x2, double y1, double y2);
		double Interp2(double *X,double *Y, double **Z,int sizeX, int sizeY, double Xr, double Yr);
		double Interp2(double *X, double *Y, array<double, 2>^ Zz, int sizeX, int sizeY, double Xr, double Yr);
		int GetIndex(double *B, int size, double _Dnc);
		double Koef_thetaTR(short pg, unsigned int dnc, double hb);	//OK
		int Koef_Q0(double thetaTr);	//OK
		short Koef_K(short pg, unsigned int dnc, double hb);	//OK
		unsigned short Koef_Dbn(short pg); //OK
		unsigned short Koef_Kop(short pg, unsigned int dnc); //OK
		unsigned short Koef_Kd(short pg, unsigned int dnc); //OK
		void Koef_Mpn(double ec, double bc);//OK
		short Koef_Ukvp(short pg);//OK
		unsigned short Koef_Dpry(short pg, unsigned int dnc, double hb);//OK
		int Koef_Dpr(short pg, unsigned int dnc);//OK
		short Koef_Qtr(short pg);//OK
		float Koef_V0x(double theta0Interp);//OK
		float Koef_V0y(double theta0Interp);//OK
		void Init();
	public:
		PZ();
		PZ(CollectDataPz ^CollPz);
		PZ(CollectDataPz ^CollPz, String^ nameGrid);
		void CalcPzAndCreateOutBuffer();
		property unsigned short Write_Buffer[int, int]{
			virtual unsigned short get(int i, int j){
				return _buffer_pz_write[i][j];
			}
		}
		//property array<array<unsigned short>^>^ Write_Buffer{
		//	virtual array<array<unsigned short>^>^ get(){
		//		return _buffer_pz_write;
		//	}
		//}
		property CollectDataPz ^ CollectionPZ{
			virtual CollectDataPz ^ get(){
				return _CollPz;
			}
		}
	};
}
