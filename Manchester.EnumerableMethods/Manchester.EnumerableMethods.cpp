// ֳכאגםûי DLL-פאיכ.

#include "stdafx.h"

#include "Manchester.EnumerableMethods.h"

using namespace ManchesterEnumerableMethods;
XElement^ EnumerableMethods::SelectFunc(KeyValuePair<String^, String^> pairValues) {
	return gcnew XElement(pairValues.Key, pairValues.Value);
}
System::Collections::Generic::IEnumerable<String^>^ EnumerableMethods::SelectFunc(String^ str, int i) {
	System::Collections::Generic::IEnumerable<String^>^ curr = str->Substring(str->IndexOf(':') + 1)->Trim()->Split(gcnew array<Char>{' '}, StringSplitOptions::RemoveEmptyEntries);
	return System::Linq::Enumerable::Skip(curr, 1);
}
DictionaryEntry EnumerableMethods::OrderBy(DictionaryEntry source) {
	return source;
}
XAttribute^ EnumerableMethods::WhereFunc(KeyValuePair<String^, String^> pairValues) {
	for each (DictionaryEntry^ sourceDic in _resourceEnumerator) {
		if (sourceDic->Key->ToString()->Contains(pairValues.Key)) {
			XAttribute ^ atr = gcnew XAttribute(sourceDic->Key->ToString(), sourceDic->Value->ToString());
			return atr;
		}
	}
	return nullptr;
}
