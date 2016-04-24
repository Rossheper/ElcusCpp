// Manchester.Efems.h

#pragma once
#define NGPS 32
#define MGPS 81
#define NGLO 32
#define MGLO 61
using namespace System;

namespace ManchesterEfems {

	public ref class Efems 
	{
		// TODO: здесь следует добавить свои методы для этого класса.
	private:
		unsigned char **_gpsEf;
		unsigned char **_gloEf;
	protected:
		virtual bool checkToParity(int frame);
		virtual int GetLineFromEf(int frame);
	public:
		property unsigned char **GPSEf{ 
			virtual unsigned char **get(){
				return _gpsEf;
			}
		}
		property unsigned char GPSEf[int,int]{ 
			virtual unsigned char get(int i, int j){
				return _gpsEf[i][j];
			}
		}
		property unsigned char **GLOEf{ 
			virtual unsigned char **get(){
				return _gloEf;
			}
		}
		property unsigned char GLOEf[int,int]{ 
			virtual unsigned char get(int i, int j){
				return _gloEf[i][j];
			}
		}
		Efems();
		~Efems();

		virtual unsigned short * currEfemsData(int frame, int ncd);
	};

}
