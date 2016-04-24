#pragma once

#include "Manchester.EfemsVT.h"

#define SIZE_BUFFER 1024
#define NUM_ROWS_GPS 32
#define NUM_ROWS_GLO 32
#define NUM_COL_GPS 81
#define NUM_COL_GLO 61

using namespace System;
using namespace System::Collections::Generic;
using namespace System::IO;
using namespace System::Linq;
using namespace std;

namespace ManchesterEfems {
	public ref class MarkLogs{
	private:
		String^ _name;
		String^ _dataLog;
		long long _offset;
		int _line;
		List<IEnumerable<String^>^>^ ilist;
	public:
		MarkLogs();
		MarkLogs(String^ name, String^ dateLog, long long offset, int line, List<String^> ^LoadEfems, List<IEnumerable<String^>^>^ ilist);
		List<String^> ^LoadEfems;

		property String^ Name {
			virtual String^ get(){
				return _name;
			}
		}

		property long long Offset {
			virtual long long get(){
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
		property List<IEnumerable<String^>^>^ ListForMass{
			virtual List<IEnumerable<String^>^>^ get(){
				return ilist;
			}
		}
	};

	public ref class ParseEfemsLogsVPU : EfemsVT{
	private:
		short _switchLine;
		int _stepLine;
		int _colGpsCount;
		int _colGloCount;
		short _numKadrPass;
		bool _parity;
		int _index;
		int _sumLines;
		List<IEnumerable<String^>^> ^ilist;
		List<String^> ^GetEfems(StreamReader ^reader);
	public:
		ParseEfemsLogsVPU();
		property int CurrLines;
		property long Pos;
		property List<MarkLogs^> ^ HeadersParts;
		property String^ Path;		
		List<MarkLogs^> ^ConvertEfems(String^ path);
		bool InitLoadedEfems(String^ path, int index);//StackList<char*> efems
	};
}