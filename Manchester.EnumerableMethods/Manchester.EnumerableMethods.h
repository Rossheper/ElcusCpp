// Manchester.EnumerableMethods.h

#pragma once

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Xml;
using namespace System::Xml::Linq;
using namespace System::Linq;
namespace ManchesterEnumerableMethods {

	public ref class EnumerableMethods
	{
	public:
		// TODO: здесь следует добавить свои методы для этого класса.
		static System::Collections::Generic::IEnumerable<DictionaryEntry>^ _resourceEnumerator;
		static XElement^ SelectFunc(KeyValuePair<String^, String^> pairValues);
		static DictionaryEntry OrderBy(DictionaryEntry source);
		static XAttribute^ WhereFunc(KeyValuePair<String^, String^> pairValues);
		static System::Collections::Generic::IEnumerable<String^>^ SelectFunc(String^ str, int i);
	};
}
