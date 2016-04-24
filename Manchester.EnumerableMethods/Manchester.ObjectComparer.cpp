#include "stdafx.h"
#include "Manchester.ObjectComparer.h"
using namespace ManchesterDataLoader;
ObjectComparer::ObjectComparer() {
}
int ObjectComparer::Compare(DictionaryEntry x, DictionaryEntry y) {
	

	int numX = Int32::Parse(x.Key->ToString()->Substring(x.Key->ToString()->IndexOf(L'Ï') + 1));
	
	int numY = Int32::Parse(y.Key->ToString()->Substring(y.Key->ToString()->IndexOf(L'Ï') + 1));
		
	if (numX < numY)
		return -1;
	else if (numX > numY)
		return 1;
	else
		return 0;
}
