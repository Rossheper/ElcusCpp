#include "stdafx.h"
#include "Manchester.CollectDataPz.h"

using namespace ManchesterTask;
CollectDataPz::CollectDataPz(void)
{
	GridFieldsData = gcnew Dictionary<String^,Dictionary<String^,String^>^>();
	mpn = gcnew array<array<int>^>(row_mpn);
	for(int i = 0; i < row_mpn; i++)
		mpn[i] = gcnew array<int>(col_mpn);
}
