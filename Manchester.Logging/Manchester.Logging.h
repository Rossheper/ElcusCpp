// Manchester.Logging.h

#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Globalization;
using namespace System::Data;
namespace ManchesterLogging {

	public ref class Logging : public IDisposable
	{
		// TODO: здесь следует добавить свои методы для этого класса.
	private:
		StreamWriter ^writer;
		DirectoryInfo ^dirInfo;
		// Track whether Dispose has been called.
		bool disposed;

	public:
		Logging(String^ nameFile);
		~Logging();
		!Logging();
		void ToReadyCheckLog(String^ str, bool writeTimeHeader);
		void ToReadyCheckLog(DataSet^ ds, bool writeTimeHeader, int gloMbpp, int gpsMbpp, int gloBna, int gpsBna);
		void WriteHeaders(DataSet^ ds);

	};
}
