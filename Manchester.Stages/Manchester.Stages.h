// Manchester.Stages.h

#pragma once

using namespace System;
using namespace ManchesterTask;
using namespace ManchesterEfems;

namespace ManchesterStages {
	public ref class SizeExchange
	{
	private:
		int _getNumberWords;
		int _sendNumberWords;
		int _getNumberOfFrames;
		int _sendNumberOfFrames;
		unsigned int * _getDataMass;
		static int _steps = 2;

	public:
		SizeExchange(int getNumberWords, int sendNumberWords, int getNumberOfFrames, int sendNumberOfFrames);

		property int Steps{
			virtual int get(){
				return _steps;
			}
		}
		property int GetNumberOfDataWords{
			virtual int get(){
				return _getNumberWords;
			}
			virtual void set(int value){
				_getNumberWords = value;
			}
		}
		property int SendNumberOfDataWords{
			virtual int get(){
				return _sendNumberWords;
			}
			virtual void set(int value){
				_sendNumberWords = value;
			}
		}
		property int GetNumberOfFrames{
			virtual int get(){
				return _getNumberOfFrames;
			}
			virtual void set(int value){
				_getNumberOfFrames = value;
			}
		}
		property int SendNumberOfFrames{
			virtual int get(){
				return _sendNumberOfFrames;
			}
			virtual void set(int value){
				_sendNumberOfFrames = value;
			}
		}
		property unsigned int * GetDataMass{
			virtual unsigned int* get(){
				return _getDataMass;
			}
		}
		
		void SetPrepareMass(unsigned int *newSubAddressGet);
	};
	public ref class Stages
	{
		// TODO: здесь следует добавить свои методы для этого класса.
	private:
		SizeExchange ^_sizes;
		PZ ^pz;
		EfemsVT ^efems;
		unsigned short **_massToSend;
		unsigned short **_massToGet;
		short _flags;
		int _address;
		int _subAddressSend;
		int _subAddressGet;
	public:
		property unsigned short ** MassToSend{
			virtual unsigned short** get(){
				return _massToSend;
			}
		}
		property unsigned short * MassToSend[int]{
			virtual unsigned short* get(int i){
				return _massToSend[i];
			}
		}
		property unsigned short ** MassToGet{
			virtual unsigned short** get(){
				return _massToGet;
			}
		}
		property unsigned short * MassToGet[int]{
			virtual unsigned short* get(int i){
				return _massToGet[i];
			}
		}
		property short ModeFlag{
			virtual short get(){
				return _flags;
			}
			virtual void set(short value){
				_flags = value;
			}
		}
		property int NewAddress{
			virtual int get(){
				return _address;
			}
		}
		property int SubAddressSend{
			virtual int get(){
				return _subAddressSend;
			}
		}
		property int SubAddressGet{
			virtual int get(){
				return _subAddressGet;
			}
		}

		//Stages(SizeExchange^ sizes, short flags, int address, PZ ^ _pz);
		Stages^ GeneratedAddress();
		Stages^ GeneratedPZ();
		Stages^ GeneratedPZEfems();
		Stages^ ReinitEfems(EfemsVT^ newEfems);
		void ReadyCheck(int newSubAddressGet);
		void Config(SizeExchange^ sizes, short flags, int address, int subAddressSend, int subAddressGet);
		unsigned int * PrepareResponseData(unsigned short *responseMass);
	};
}
