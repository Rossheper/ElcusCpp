// Manchester.manchester.h

#pragma once
#include <Windows.h>
#include "WDMTMKv2.h"
using namespace System;
using namespace ManchesterDataLoader;
using namespace ManchesterEfems;


namespace Manchestermanchester {

	public ref class Manchester
	{
		// TODO: здесь следует добавить свои методы для этого класса.
	private:
		//EfemsVT ^efems;
		HANDLE _currHandle;
		TTmkEventData *events;
		short _word;
		short _addrOY;
		short _currSubAddr;
		short _format;
		short _countOfErrors;
		short _dataInverse;
		short _frame;
		short _errorCode;
		short _mode;
		unsigned short _command;
		//unsigned short *_dataToSend;
		int _setPlate;
		unsigned int _wBase;
		bool _captured;
		unsigned long  wStatus;
		unsigned short wBase, wMaxBase, wSubAddr, wLen, wState;
		unsigned long dwGoodStarts, dwBusyStarts, dwErrStarts, dwStatStarts;
		unsigned long dwStarts;
		unsigned short *_sendingMass;
		unsigned short *_receivedData;
		unsigned short **_pz;
		//Метод, управляющий приемом/передачей
		short sendingControl(short K);

		// Метод, формирующий командное слово
		short formatKC(short addrOy, short K, short subAddr, short ncd);

		//Метод генерации кода ошибок
		void errorParse(short oc);
	public:
		Manchester();
		~Manchester();

		//Получение и установка ссылки на массив ПЗ
		property unsigned short **PZ{
			virtual unsigned short ** get(){
				return this->_pz;
			}
			virtual void set(unsigned short ** newPZ){
				this->_pz = newPZ;
			}
		}

		//Получение массива притяных данных от ОУ
		property unsigned short* Received{
			virtual unsigned short* get(){
				return this->_receivedData;
			}
		}

		//Получение и установка текущего режима
		property short Mode{
			virtual short get(){
				return this->_mode;
			}
			virtual void set(short newMode){
				this->_mode = newMode;
			}
		}

		//Получение текущего командного слова
		property unsigned short CurrentCommandWord{
			virtual unsigned short get(){
				return _command;
			}
		}

		//Получение кода ошибки
		property short OCErr{ 
			virtual short get(){
				return _errorCode;
			}
		}

		//Получение и установка текущего HANDLE
		property HANDLE CurrentHandle{ 
			virtual HANDLE get(){
				return _currHandle;
			}
			virtual void set(HANDLE value){
				_currHandle = value;
			}
		}

		//Получение текущего фрейма
		property short Frame { 
			virtual short get(){
				return _frame;
			}
			virtual void set(short value){
				_frame = value;
			}
		}

		//Получение текущего подадреса
		property short GetSubAddress{
			virtual short get(){
				return this->_currSubAddr;
			}
		}

		// Метод, разворачивающий данные с размером в 1 байт
		virtual short inverseData(short data);

		// Метод, собирающий полученное слово из 2 байт
		virtual short ConcatinateData(short lowData, short highData);

		// Метод, производящий захват выбранной платы манчестера
		virtual int configuration(int currentPlate);

		// Метод, производящий освобождение платы
		virtual bool toFreePlate(int currentPlate);

		// Метод, производящий отправку данных на ОУ
		virtual bool sendData(short oldAddr, short addrOy, short K, short subAddr, short ncd, unsigned short * massToSend);

		//Метод, обрабатывающий получение данных
		virtual int WaitInt(unsigned short wCtrlCode);
	};
}
