using namespace System;
using namespace System::Data;
using namespace System::Collections;
using namespace System::Text::RegularExpressions;
namespace ManchesterDataLoader {
#pragma once
	public ref class ObjectComparer : System::Collections::Generic::IComparer<DictionaryEntry>
	{
	public:
		ObjectComparer();
		virtual int Compare(DictionaryEntry x, DictionaryEntry y);
	};
}
