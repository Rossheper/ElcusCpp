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
		// TODO: ����� ������� �������� ���� ������ ��� ����� ������.
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
		//�����, ����������� �������/���������
		short sendingControl(short K);

		// �����, ����������� ��������� �����
		short formatKC(short addrOy, short K, short subAddr, short ncd);

		//����� ��������� ���� ������
		void errorParse(short oc);
	public:
		Manchester();
		~Manchester();

		//��������� � ��������� ������ �� ������ ��
		property unsigned short **PZ{
			virtual unsigned short ** get(){
				return this->_pz;
			}
			virtual void set(unsigned short ** newPZ){
				this->_pz = newPZ;
			}
		}

		//��������� ������� �������� ������ �� ��
		property unsigned short* Received{
			virtual unsigned short* get(){
				return this->_receivedData;
			}
		}

		//��������� � ��������� �������� ������
		property short Mode{
			virtual short get(){
				return this->_mode;
			}
			virtual void set(short newMode){
				this->_mode = newMode;
			}
		}

		//��������� �������� ���������� �����
		property unsigned short CurrentCommandWord{
			virtual unsigned short get(){
				return _command;
			}
		}

		//��������� ���� ������
		property short OCErr{ 
			virtual short get(){
				return _errorCode;
			}
		}

		//��������� � ��������� �������� HANDLE
		property HANDLE CurrentHandle{ 
			virtual HANDLE get(){
				return _currHandle;
			}
			virtual void set(HANDLE value){
				_currHandle = value;
			}
		}

		//��������� �������� ������
		property short Frame { 
			virtual short get(){
				return _frame;
			}
			virtual void set(short value){
				_frame = value;
			}
		}

		//��������� �������� ���������
		property short GetSubAddress{
			virtual short get(){
				return this->_currSubAddr;
			}
		}

		// �����, ��������������� ������ � �������� � 1 ����
		virtual short inverseData(short data);

		// �����, ���������� ���������� ����� �� 2 ����
		virtual short ConcatinateData(short lowData, short highData);

		// �����, ������������ ������ ��������� ����� ����������
		virtual int configuration(int currentPlate);

		// �����, ������������ ������������ �����
		virtual bool toFreePlate(int currentPlate);

		// �����, ������������ �������� ������ �� ��
		virtual bool sendData(short oldAddr, short addrOy, short K, short subAddr, short ncd, unsigned short * massToSend);

		//�����, �������������� ��������� ������
		virtual int WaitInt(unsigned short wCtrlCode);
	};
}
