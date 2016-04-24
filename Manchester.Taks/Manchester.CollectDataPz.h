#pragma once
using namespace System;
using namespace System::Collections::Generic;

namespace ManchesterTask{
	public ref class CollectDataPz
	{
	private:
		static const char row_mpn = 3;
		static const char col_mpn = 3; 
	public:
		CollectDataPz(void);
		Dictionary<String^,Dictionary<String^,String^>^> ^GridFieldsData;
		array<array<int>^>^ mpn;
	};
}

