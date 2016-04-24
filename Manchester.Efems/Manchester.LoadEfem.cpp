#include "stdafx.h"
#include "Manchester.LoadEfem.h"
using namespace System;
using namespace System::IO;
using namespace ManchesterEfems;

MarkLogs::MarkLogs(){
	_name = nullptr;
	_offset = 0;
	_line = 0;
	LoadEfems = gcnew List<String^>();
	ilist = gcnew List<IEnumerable<String^>^>();
}

MarkLogs::MarkLogs(String^ name, String^ dateLog, long long offset, int line, List<String^> ^LoadEfems, List<IEnumerable<String^>^>^ ilist){
	this->_name = name;
	this->_offset = offset;
	this->_line = line;
	this->_dataLog = dateLog;
	this->LoadEfems = LoadEfems;
	this->ilist = ilist;
}
ParseEfemsLogsVPU::ParseEfemsLogsVPU(){
	_switchLine = 0;
	_stepLine = 0;
	_colGpsCount = 0;
	_colGloCount = 0;
	_numKadrPass = 0;
	_parity = 0;
	_index = 0;
	_sumLines = 0;
	ilist = nullptr;
}
List<MarkLogs^> ^ParseEfemsLogsVPU::ConvertEfems(String^ path)
{
	Path = path;
	HeadersParts = gcnew List<MarkLogs^>();
	String^ _dateLog;
	StreamReader ^ reader = gcnew StreamReader(path);
	CurrLines = 0;
	while (!reader->EndOfStream)
	{
		String^ str = reader->ReadLine();
		if(str->Contains("Начало работы"))
			_dateLog = str;
		CurrLines++;
		if (str->Contains("EPHEMERIDS"))
		{
			HeadersParts->Add(gcnew MarkLogs(str->TrimEnd('-'), _dateLog, reader->BaseStream->Position, CurrLines, GetEfems(reader), ilist));
			CurrLines += 96;
		}
	}
	reader->Close();
	return HeadersParts;
}

List<String^> ^ ParseEfemsLogsVPU::GetEfems(StreamReader ^reader){
	int lines = 0;
	String^ str;
	List<String^> ^ lst = gcnew List<String^>();
	ilist = gcnew List<IEnumerable<String^>^>();
	IEnumerable<String^>^ curr;
	IEnumerable<String^>^ prev;
	while (!reader->EndOfStream)
	{
		str = reader->ReadLine();
		curr = str->Substring(str->IndexOf(':') + 1)->Trim()->Split(gcnew array<Char>{' '}, StringSplitOptions::RemoveEmptyEntries);
		if (lines < 64)
		{
			IEnumerable<String^>^ tmp;
			lst->Add(str);
			str = reader->ReadLine();
			tmp = str->Substring(str->IndexOf(':') + 1)->Trim()->Split(gcnew array<Char>{' '}, StringSplitOptions::RemoveEmptyEntries);
			ilist->Add(Linq::Enumerable::Concat(Linq::Enumerable::Skip(curr,1),Linq::Enumerable::Take(Linq::Enumerable::Skip(tmp,2),10)));
			lines++;
		}
		else
			ilist->Add(Linq::Enumerable::Skip(curr,1));
		prev = curr;
		lines++;
		lst->Add(str);
		if(str->Contains("Kadr 96:"))
			break;

	}
	return lst;
}
bool ParseEfemsLogsVPU::InitLoadedEfems(String^ path, int index){
	List<MarkLogs^> ^ marks = ConvertEfems(path);
	unsigned int hex2dec = 0;
	_stepLine = 0;
	for each (IEnumerable<String^>^ efems in marks[index]->ListForMass)
	{
		_index = 0;
		for each (String^ str in efems)
		{
			hex2dec = UInt32::Parse(str, System::Globalization::NumberStyles::HexNumber);
			if(_stepLine > 31){
				if(_index < 1 )
					GLOEf[_stepLine - 32][_index++] = (hex2dec & 0xFF00)>>8;
				else{
					GLOEf[_stepLine - 32][_index++] = hex2dec & 0x00FF;
					GLOEf[_stepLine - 32][_index++] = (hex2dec & 0xFF00)>>8;
				}
			}
			else{
				if(_index < 1 )
					GPSEf[_stepLine][_index++] = (hex2dec & 0xFF00)>>8;
				else{
					GPSEf[_stepLine][_index++] = hex2dec & 0x00FF;
					GPSEf[_stepLine][_index++] = (hex2dec & 0xFF00)>>8;
				}
			}
			_index++;
		}
		_stepLine++;
	}
	if(_stepLine == 64)
		return 1;
	else
		return 0;
}