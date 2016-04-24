
#pragma once
#define SIZE_BUFFER 1024
#define NUM_ROWS_GPS 32
#define NUM_ROWS_GLO 32
#define NUM_COL_GPS 81
#define NUM_COL_GLO 61
using namespace System;
using namespace System::Collections::Generic;
using namespace System::IO;

using namespace std;
namespace ManchesterEfems {
	public ref class MarkLogs{
	private:
		String^ _name;
		String^ _dataLog;
		int _offset;
		int _line;
	public:
		MarkLogs();
		MarkLogs(String^ name, String^ dateLog, int offset, int line, List<String^> ^LoadEfems);
		List<String^> ^LoadEfems;
		property String^ Name {
			virtual String^ get(){
				return _name;
			}
		}
		property int Offset {
			virtual int get(){
				return _offset;
			}
		}
		property int Line {
			virtual int get(){
				return _line;
			}
		}
		property String^ DateLog {
			virtual String^ get(){
				return _dataLog;
			}
		}
	};

	public ref class ParseEfemsLogsVPU : Efems{
	private:
		String^ _dateLog;
		


		short _switchLine;
		int _stepLine;
		int _colGpsCount;
		int _colGloCount;
		short _numKadrPass;
		bool _parity;
		int _index;
		char *_seps;
		char *_head;
		char *_tail;
		int _sumLines;
		int _currLine;
	public:
		

		property int CurrLines;
        property long Pos;
        property List<MarkLogs^> ^ _headersParts;
        property String^ Path;
        property String^ str2;
			

		/*String^ _path;
		String^ currLine;
		String^ headerLine;
		List<MarkLogs^> ^ _headersParts;*/
		ParseEfemsLogsVPU();
		List<MarkLogs^> ^ConvertEfems(String^ path);
		List<String^> ^GetEfems(StreamReader ^reader);
		short InitLoadedEfems(List<String^> ^efems);//StackList<char*> efems
		bool Parity(int frame);

	};
}