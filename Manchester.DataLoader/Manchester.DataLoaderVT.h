#pragma once
#include "Manchester.DataLoader.h"

namespace ManchesterDataLoader {
	public ref class DataLoaderVT : DataLoader
	{
	private:
		
	public:
		DataLoaderVT() : DataLoader(){}
		virtual unsigned int *parsePZ(unsigned short *input, int ncd, int frame) override;
		virtual double parseWindowPZ(int i) override;
		virtual String^ FormattedPZ(unsigned int* dataInput, int k);
		virtual String^ FormattedEf(unsigned int* dataInput, int count);
		//virtual List<String^>^ FormattedSetAddr(int k, int frmt);
	};
}

