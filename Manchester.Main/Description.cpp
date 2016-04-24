#include "Description.h"

using namespace ManchesterManager;
System::Void Description::Description_Load(System::Object^  sender, System::EventArgs^  e){


	ResourceManager ^man = gcnew ResourceManager("ManchesterManager.Resource", System::Reflection::Assembly::GetExecutingAssembly());
	System::Collections::Generic::IEnumerable<DictionaryEntry>^ tmp = System::Linq::Enumerable::OfType<DictionaryEntry>(man->GetResourceSet(CultureInfo::CurrentUICulture, true, true));
	System::Collections::Generic::IEnumerable<DictionaryEntry>^ EditedDictObj = System::Linq::Enumerable::OrderBy(tmp, gcnew Func< DictionaryEntry, DictionaryEntry >(&EnumerableMethods::OrderBy), gcnew ObjectComparer());
	int index = 0;
	int offset = 15;
	for each (DictionaryEntry^ dict in EditedDictObj) {
		if (index<offset) {
			dataGridViewDescription->Rows->Add();
			dataGridViewDescription->Rows[index]->Cells[0]->Value = dict->Key->ToString();
			dataGridViewDescription->Rows[index]->Cells[1]->Value = dict->Value->ToString();
		}
		else {
			dataGridViewDescription->Rows[index - offset]->Cells[2]->Value = dict->Key->ToString();
			dataGridViewDescription->Rows[index - offset]->Cells[3]->Value = dict->Value->ToString();
		}
		index++;
	}
}
