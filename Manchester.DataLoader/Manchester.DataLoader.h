// Manchester.DataLoader.h

#pragma once
//#define NUM_COMMANDS 2
//#define PARAMS 40
//#define MASS_SIZE 96
//#define MASS_COL_SIZE 61

using namespace System;
using namespace System::Data;
using namespace System::Collections::Generic;
using namespace System::Resources;
using namespace System::Collections;
using namespace ManchesterTask;
using namespace ManchesterEfems;
namespace ManchesterDataLoader {

	public ref class NaviStatus
	{
	public:
		static short gloBna = 0;
		static short gpsBna = 0;
		static short gloMbpp = 0;
		static short gpsMbpp = 0;
		static int sumNaviBna = 0;
		static int sumNaviMbpp = 0;
		static bool GLC = false;
	};
	public ref class FormManager
	{
	public:
		static EfemsVT ^ newEfems = nullptr;
		static PZ ^ switchPz = nullptr;
		static String ^ pathApp = nullptr;
	};
	public ref class DataLoader
	{
		// TODO: здесь следует добавить свои методы для этого класса.
	private:
		unsigned int **_mass;
		List<String^> ^_nameParams;
	protected:
		static const short NUM_COMMANDS = 2;
		static const short PARAMS = 40;
		static const short MASS_SIZE = 96;
		static const short MASS_COL_SIZE = 61;
	public:
		DataLoader();
		~DataLoader();
		property List<String^> ^NameParams {
			virtual List<String^> ^get(){
				return _nameParams;
			}
		}
		
		virtual List<String^> ^ setParams();
		virtual int getPower(double number);
		virtual unsigned short *parseEfems(unsigned short *input, int ncd);
		virtual unsigned int *parsePD(unsigned short *input, int ncd);
		virtual unsigned int *parsePZ(unsigned short *input, int ncd, int frame);
		//virtual unsigned int *parsePZVT(unsigned short *input, int ncd, int frame);
		virtual double parseWindowPZ(int i);
		virtual List<String^> ^getCmdKSH();

	};
}
