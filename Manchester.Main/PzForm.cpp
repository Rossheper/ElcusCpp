#include "PzForm.h"
using namespace ManchesterManager;
using namespace System::IO;
DataGridViewComboBoxCell^ PzForm::CreateComboBoxCell(FlagsComboBoxes boxes){
	DataGridViewComboBoxCell ^colCell =  gcnew DataGridViewComboBoxCell();
	if(boxes == FlagsComboBoxes::FTM){ 
		colCell->Items->AddRange(gcnew array<String^> { "0","1" }); 
		colCell->MaxDropDownItems = 2; 
	}
	else if(boxes == FlagsComboBoxes::Pg){
		colCell->Items->AddRange(gcnew array<String^> { "0","1","2" }); 
		colCell->MaxDropDownItems = 3; 
	}
	colCell->FlatStyle = FlatStyle::Standard;
	colCell->Style->NullValue="0";
	return colCell;
}
List<String^>^ PzForm::CreatingHeadersCellNames(FlagsComboBoxes boxes){
	Generic::List<String^> ^headersCell = gcnew List<String^>();
	if(boxes == FlagsComboBoxes::Edited){
		for(int i = 0; i < 14; i++)
			headersCell->Add("П" + Convert::ToString(i+1));
		headersCell->Add("П" + Convert::ToString(23));
		headersCell->Add("П" + Convert::ToString(26));
		headersCell->Add("П" + Convert::ToString(27));
	}
	else if(boxes == FlagsComboBoxes::NotEdited){
		for(int i = 0; i < 8; i++)
			headersCell->Add("П" + Convert::ToString(i+15));
		headersCell->Add("П" + Convert::ToString(29));
		headersCell->Add("П" + Convert::ToString(30));
	}
	return headersCell;
}
System::Void PzForm::InitNotEditedGrid(String^ name, List<String^> ^headersNotEditingCell){
	ResourceManager ^man = gcnew ResourceManager(name, System::Reflection::Assembly::GetExecutingAssembly());
	System::Collections::Generic::IEnumerable<DictionaryEntry>^ tmp = System::Linq::Enumerable::OfType<DictionaryEntry>(man->GetResourceSet(CultureInfo::CurrentUICulture, true, true));
	System::Collections::Generic::IEnumerable<DictionaryEntry>^ EditedDictObj = System::Linq::Enumerable::OrderBy(tmp, gcnew Func< DictionaryEntry, DictionaryEntry >(&EnumerableMethods::OrderBy), gcnew ObjectComparer());
	int index = 0;
	for each (DictionaryEntry^ NotEditedDict in EditedDictObj) {
		NotEditedPZGrid->Rows->Add();
		NotEditedPZGrid->Rows[index]->HeaderCell->Value = NotEditedDict->Key;
		NotEditedPZGrid->Rows[index]->Cells[0]->Value = NotEditedDict->Value;
		index++;
	}
}
System::Void PzForm::InitEditedGrid(String^ name, List<String^> ^headersEditingCell){
	ResourceManager ^man = gcnew ResourceManager(name, System::Reflection::Assembly::GetExecutingAssembly());
	System::Collections::Generic::IEnumerable<DictionaryEntry>^ tmp = System::Linq::Enumerable::OfType<DictionaryEntry>(man->GetResourceSet(CultureInfo::CurrentUICulture, true, true));
	System::Collections::Generic::IEnumerable<DictionaryEntry>^ EditedDictObj = System::Linq::Enumerable::OrderBy(tmp, gcnew Func< DictionaryEntry, DictionaryEntry >(&EnumerableMethods::OrderBy), gcnew ObjectComparer());
	int index = 0;
	for each (DictionaryEntry^ EditedDict in EditedDictObj){
		String^ s = EditedDict->Key->ToString();
		EditedPZGrid->Rows->Add();
		if(Convert::ToString(EditedDict->Key)->Contains("П5"))
			EditedPZGrid->Rows[index]->Cells[0] = CreateComboBoxCell(FlagsComboBoxes::Pg);
		if(Convert::ToString(EditedDict->Key)->Contains("П26"))
			EditedPZGrid->Rows[index]->Cells[0] = CreateComboBoxCell(FlagsComboBoxes::FTM);
		EditedPZGrid->Rows[index]->HeaderCell->Value = EditedDict->Key;
		EditedPZGrid->Rows[index]->Cells[0]->Value = EditedDict->Value;
		index++;
	}
}
System::Void PzForm::InitPMs(){
	for(int i = 0; i < 3; i++){
		PM24->Rows->Add();
		PM25->Rows->Add();
		for(int j = 0; j < PM25->Columns->Count; j++){
			PM24->Rows[i]->Cells[j]->Value = "0";
			PM25->Rows[i]->Cells[j]->Value = "0";
		}
	}
}
array<array<int>^>^ PzForm::GetMpnFromGrids(DataGridView ^currGridView){
	array<array<int>^>^ mpn = mpn = gcnew array<array<int>^>(currGridView->Rows->Count);
	for(int i = 0; i < currGridView->Rows->Count; i++){
		mpn[i] = gcnew array<int>(currGridView->ColumnCount);
		for(int j = 0; j < currGridView->ColumnCount; j++)
			mpn[i][j] = Convert::ToInt32(currGridView->Rows[i]->Cells[j]->Value);
	}
	return mpn;
}
Dictionary<String^,String^>^ PzForm::GetDataFromGrids(DataGridView ^currGridView){

	Dictionary<String^, String^>^ dic = gcnew  Dictionary<String^, String^>();
	for(int i = 0; i < currGridView->Rows->Count; i++)
		for(int j = 0; j < currGridView->ColumnCount; j++)
			if(currGridView->Rows[i]->HeaderCell->Value->ToString()->Contains("П5") || currGridView->Rows[i]->HeaderCell->Value->ToString()->Contains("П26"))
				dic->Add(currGridView->Rows[i]->HeaderCell->Value->ToString(), ((DataGridViewComboBoxCell^)currGridView->Rows[i]->Cells[j])->EditedFormattedValue->ToString());
			else
				dic->Add(currGridView->Rows[i]->HeaderCell->Value->ToString(), currGridView->Rows[i]->Cells[j]->Value->ToString());
	return dic;
}
CollectDataPz ^ PzForm::GetCollectionGridsData(){
	collectData = gcnew CollectDataPz();
	for each (Object ^ grid in this->Controls)
		if(grid->GetType() == NotEditedPZGrid->GetType())
			if(((DataGridView^)grid)->Name->Contains("PZGrid") || ((DataGridView^)grid)->Name->Contains("EditedPZGrid"))
				collectData->GridFieldsData->Add(((DataGridView^)grid)->Name,GetDataFromGrids((DataGridView^)grid));
	return collectData;
}
System::Void PzForm::PzForm_Load(System::Object^  sender, System::EventArgs^  e) {

	InitEditedGrid("ManchesterManager.DefaultValuesEdited", CreatingHeadersCellNames(FlagsComboBoxes::Edited));
	InitNotEditedGrid("ManchesterManager.DefaultValuesNotEdited", CreatingHeadersCellNames(FlagsComboBoxes::NotEdited));
	InitPMs();

	ResourceManager ^man = gcnew ResourceManager("ManchesterManager.Resource", System::Reflection::Assembly::GetExecutingAssembly());
	System::Collections::Generic::IEnumerable<DictionaryEntry>^ tmp = System::Linq::Enumerable::OfType<DictionaryEntry>(man->GetResourceSet(CultureInfo::CurrentUICulture, true, true));
	EnumerableMethods::_resourceEnumerator = System::Linq::Enumerable::OrderBy(tmp, gcnew Func< DictionaryEntry, DictionaryEntry >(&EnumerableMethods::OrderBy), gcnew ObjectComparer());
	
}
System::Void PzForm::Load_Mpn(CollectDataPz^ calcPz){
	for(int i = 0; i < PM25->Rows->Count;i++)
		for(int j = 0; j < PM25->Columns->Count;j++)
			PM25->Rows[i]->Cells[j]->Value = calcPz->mpn[i][j];
}
System::Void PzForm::Load_CalcPz(CollectDataPz^ calcPz){
	Dictionary<String^, String^>^ _currGrid = calcPz->GridFieldsData["NotEditedPZGrid"];
	int index = 0;
	for each (KeyValuePair<String^, String^> ^ cellValue in _currGrid)
	{
		NotEditedPZGrid->Rows[index]->Cells[0]->Value = cellValue->Value;
		index++;
	}				 
}
System::Void PzForm::descriptionToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	Description ^descriptionWindiow = gcnew Description();
	descriptionWindiow->Show();
}

System::Void PzForm::Calc_Click(System::Object^  sender, System::EventArgs^  e) {
	pz = gcnew PZ(GetCollectionGridsData());
	pz->CalcPzAndCreateOutBuffer();
	OK_button->Enabled = true;
	Load_CalcPz(pz->CollectionPZ);
	Load_Mpn(pz->CollectionPZ);
	ManchesterDataLoader::FormManager::switchPz = pz;
	PzToXml(pz->CollectionPZ);
}

System::Void PzForm::EditedPZGrid_CellValueChanged(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
	if(e->RowIndex > -1 && e->ColumnIndex > -1 && e->RowIndex != 15 && e->RowIndex != 4){
		bool zap = ((DataGridView^)sender)->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value->ToString()->Contains(".");
		if (CultureInfo::CurrentCulture->NumberFormat->CurrencyDecimalSeparator == "," && zap)
			((DataGridView^)sender)->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value = ((DataGridView^)sender)->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value->ToString()->Replace('.', ',');
		else if (CultureInfo::CurrentCulture->NumberFormat->CurrencyDecimalSeparator == "." && !zap)
			((DataGridView^)sender)->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value = ((DataGridView^)sender)->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value->ToString()->Replace(',', '.');
	}
}

System::Void PzForm::EditedPZGrid_CellValidating(System::Object^  sender, System::Windows::Forms::DataGridViewCellValidatingEventArgs^  e) {
	Double tmp;
	if (String::IsNullOrEmpty(e->FormattedValue->ToString()) || String::IsNullOrWhiteSpace(e->FormattedValue->ToString()) || !Double::TryParse(e->FormattedValue->ToString(),tmp)){
		((DataGridView^)sender)->Rows[e->RowIndex]->ErrorText = "Ошибка формата строки!";
		e->Cancel = true;
	}
}
System::Void PzForm::EditedPZGrid_CellEndEdit(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
	((DataGridView^)sender)->Rows[e->RowIndex]->ErrorText = String::Empty;
}
System::Void PzForm::PzForm_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
	if ((e->KeyChar >= '0' && e->KeyChar <= '9') || e->KeyChar == '\b' || e->KeyChar == '-' || e->KeyChar == ',' || e->KeyChar == '.'){
		e->Handled = false;
		if (CultureInfo::CurrentCulture->NumberFormat->CurrencyDecimalSeparator == "," && e->KeyChar == '.')
			e->KeyChar = ',';
		else if (CultureInfo::CurrentCulture->NumberFormat->CurrencyDecimalSeparator == "." && e->KeyChar == ',')
			e->KeyChar = '.';
	}
	else
		e->Handled = true;
}
System::Void PzForm::OK_button_Click(System::Object^  sender, System::EventArgs^  e) {
	Close();
}
System::Void PzForm::PzToXml(CollectDataPz ^dataList){
	DirectoryInfo ^ dirInfo;
	xmlDoc = gcnew XDocument();
	XComment ^comment = gcnew XComment(DateTime::Now.ToLongDateString() +" "+ DateTime::Now.ToLongTimeString());
	XElement ^NewElement = gcnew XElement("Root");
	xmlDoc->Add(gcnew XComment("Calculated Fly Task Params"));
	xmlDoc->Add(comment);
	for each (KeyValuePair<String^,Dictionary<String^, String^>^>^ currGrid in dataList->GridFieldsData)
	{
		System::Collections::Generic::IEnumerable<XAttribute^> ^xAttr = System::Linq::Enumerable::Select(currGrid->Value, gcnew Func<KeyValuePair<String^, String^>,XAttribute^>(&EnumerableMethods::WhereFunc));
		System::Collections::Generic::IEnumerable<XElement^> ^ xElem = System::Linq::Enumerable::Select(currGrid->Value, gcnew Func<KeyValuePair<String^, String^>,XElement^>(&EnumerableMethods::SelectFunc));
		NewElement->Add(gcnew XElement(currGrid->Key,xAttr,xElem));
	}
	xmlDoc->Add(NewElement);
	dirInfo = gcnew DirectoryInfo(".\\logs");
	if(!dirInfo->Exists)
		dirInfo->Create();
	
	xmlDoc->Save(dirInfo->FullName + "\\Pz.xml");
}

