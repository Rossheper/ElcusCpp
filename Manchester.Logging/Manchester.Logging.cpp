// ֳכאגםûי DLL-פאיכ.

#include "stdafx.h"

#include "Manchester.Logging.h"
using namespace ManchesterLogging;
Logging::Logging(String^ nameFile){
	dirInfo = gcnew DirectoryInfo(".\\logs");
	if(!dirInfo->Exists)
		dirInfo->Create();
	writer = gcnew StreamWriter(dirInfo->FullName +"\\"+ nameFile,true, System::Text::Encoding::Default);
	disposed = false;
}
Logging::~Logging(){

	// Call C++ finalizer to clean up unmanaged resources.
	this->!Logging();

	// Mark the class as disposed. This flag allows you to throw an
	// exception if a disposed object is accessed.
	disposed = true;
}
Logging::!Logging(){
	writer->~StreamWriter();
	dirInfo->~DirectoryInfo();
}
void Logging::ToReadyCheckLog(String^ strLine, bool writeTimeHeader){
	if(writeTimeHeader)
		writer->WriteLine(DateTime::Now.ToString("mm:ss:ms",DateTimeFormatInfo::InvariantInfo) + strLine);
	else
		writer->WriteLine(strLine);
}
void Logging::ToReadyCheckLog(DataSet^ ds, bool writeTimeHeader, int gloMbpp, int gpsMbpp, int gloBna, int gpsBna){
	writer->Write("\n");
	if(writeTimeHeader)
		writer->Write(DateTime::Now.ToString("mm:ss:ms",DateTimeFormatInfo::InvariantInfo));
	writer->Write("|\t");
	for each (DataTable^ table in ds->Tables)
	{
		if(table->Rows->Count > 0){
			DataRow ^ row = table->Rows[table->Rows->Count - 1];
			for each (Object^ value in row->ItemArray)
			{
				if(!Convert::IsDBNull(value)){
					writer->Write(value->ToString());
					writer->Write(" ");
				}
			}
			writer->Write("|\t|");
		}
	}
	writer->Write(Convert::ToString(gpsMbpp));
	writer->Write(" ");
	writer->Write(gloMbpp);
	writer->Write("\t");
	writer->Write(gpsBna);
	writer->Write(" ");
	writer->Write(gloBna);
}
void Logging::WriteHeaders(DataSet^ ds){
	writer->Write("\n\n");
	writer->WriteLine("*** Run new ready check ***");
	writer->WriteLine(DateTime::Now.ToLongDateString() +" "+ DateTime::Now.ToLongDateString());
	writer->Write(DateTime::Now.ToString("mm:ss:ms",DateTimeFormatInfo::InvariantInfo));
	writer->Write("|\t");
	for each (DataTable^ table in ds->Tables)
	{
		for each (DataColumn ^ Column in table->Columns)
		{
			writer->Write(Column->Caption->ToString());
			writer->Write(" ");
		}
		writer->Write("|\t|");
	}
	

	writer->Write("GPSm");
	writer->Write(" ");
	writer->Write("GLOm");
	writer->Write("\t");
	writer->Write("GPSb");
	writer->Write(" ");
	writer->Write("GLOb");
	writer->Write("\n");
}

