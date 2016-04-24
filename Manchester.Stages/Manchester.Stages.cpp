// Ãëàâíûé DLL-ôàéë.

#include "stdafx.h"

#include "Manchester.Stages.h"

using namespace ManchesterStages;
using namespace ManchesterDataLoader;

SizeExchange::SizeExchange(int getNumberWords, int sendNumberWords, int getNumberOfFrames, int sendNumberOfFrames)
{
	_getNumberWords = getNumberWords;
	_sendNumberWords = sendNumberWords;
	_getNumberOfFrames = getNumberOfFrames;
	_sendNumberOfFrames = sendNumberOfFrames;
	_getDataMass = nullptr;
}
void SizeExchange::SetPrepareMass(unsigned int *prepareMass){
	_getDataMass = prepareMass;
}
Stages^ Stages::GeneratedAddress(){
	_massToSend[0][0] = (_sizes->SendNumberOfFrames);
	_massToSend[0][1] = _address;
	return this;
}

Stages^ Stages::GeneratedPZ(){
	for(int i = 0; i < _sizes->SendNumberOfFrames; i++)
		for(int j = 0; j < _sizes->SendNumberOfDataWords; j++)
			_massToSend[i][j] = pz->Write_Buffer[i,j];
	return this;
}
Stages^ Stages::GeneratedPZEfems(){
	unsigned short *tmpData = new unsigned short[_sizes->SendNumberOfDataWords];
	for(int i = 0; i < _sizes->SendNumberOfFrames; i++){
		for(int j = 0; j < _sizes->SendNumberOfDataWords; j++){
			if(i < 2)
				_massToSend[i][j] = pz->Write_Buffer[i,j];
			else{
				tmpData = efems->currEfemsData(i-2,_sizes->SendNumberOfDataWords);
				_massToSend[i][j] = tmpData[j];
			}
		}
	}
	return this;
}
Stages^ Stages::ReinitEfems(EfemsVT ^newEfems){
	this->efems = newEfems;
	return this;
}
void Stages::ReadyCheck(int newSubAddressGet){
	_subAddressGet = newSubAddressGet;
}
void Stages::Config(SizeExchange^ sizes, short flags, int address, int subAddressSend, int subAddressGet){
	_sizes = sizes;
	_flags = flags;
	_address = address;
	_subAddressSend = subAddressSend;
	_subAddressGet = subAddressGet;
	_massToGet = new unsigned short*[_sizes->GetNumberOfFrames];
	for(int i = 0; i < _sizes->GetNumberOfFrames; i++)
		_massToGet[i] = new unsigned short[_sizes->GetNumberOfDataWords];
	_massToSend = new unsigned short*[_sizes->SendNumberOfFrames];
	for(int i = 0; i < _sizes->SendNumberOfFrames; i++)
		_massToSend[i] = new unsigned short[_sizes->SendNumberOfDataWords];
	pz = FormManager::switchPz;
	efems = gcnew EfemsVT();
}
unsigned int * Stages::PrepareResponseData(unsigned short *responseMass){
	unsigned int *_prepareMass = new unsigned int[_sizes->GetNumberOfDataWords/2];
	for(int i = 0, j = 0; j < _sizes->GetNumberOfDataWords/2;j++, i+=2){
		if(j < 6){
			_prepareMass[j] = responseMass[i + 1];
			_prepareMass[j] = _prepareMass[j]<<16;                  //Êîîðäèíàòû è ñêîðîñòè ÌÁÏÏ
			_prepareMass[j] += responseMass[i];
		}
		else if( j == 6){
			_prepareMass[j] = responseMass[i];           //Trust(ÁÍÀ) FIX PZ GSN VR
		}
		else if(j == 7){
			_prepareMass[j] = responseMass[i - 1];      //Ñ÷åò÷èê ÁÍÀ è ÌÁÏÏ
			//mbppold = _prepareMass[7]&0x003F;
		}
		else if(j == 8){
			_prepareMass[j] = responseMass[i - 2];   //Ñòàòóñû GDOP(ÌÁÏÏ) GPSCount(ÌÁÏÏ) GLOCount(ÌÁÏÏ)
		}
		else if(j > 8 && j <15){
			_prepareMass[j] = responseMass[i - 2];
			_prepareMass[j] = _prepareMass[j]<<16;                  //Êîîðäèíàòû è ñêîðîñòè ÁÍÀ
			_prepareMass[j] += responseMass[i - 3];
		}
		else{
			_prepareMass[j] = responseMass[27];  //Ñòàòóñû GDOP(ÁÍÀ) GPSCount(ÁÍÀ) GLOCount(ÁÍÀ)
			break;
		}
	}
	return _prepareMass;
}