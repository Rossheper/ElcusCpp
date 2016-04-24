// ֳכאגםûי DLL-פאיכ.

#include "stdafx.h"

#include "Manchester.FSM.h"
using namespace ManchesterFSM;

FiniteStateMachine::FiniteStateMachine(){
	sendOk = false;
	locked = false;
	manchester = gcnew Manchester();
	dataLoader = gcnew DataLoader();
	stages = gcnew Stages();
	array<Action^,2>^ fsmTmp = {
		{gcnew Action(this,&FiniteStateMachine::CapturePlate), gcnew Action(this,&FiniteStateMachine::SetNewAddress), gcnew Action(this,&FiniteStateMachine::EnterPZ), gcnew Action(this,&FiniteStateMachine::EnterPZ_EF), gcnew Action(this,&FiniteStateMachine::ReadyCheck), gcnew Action(this,&FiniteStateMachine::ErrorSend), gcnew Action(this,&FiniteStateMachine::ErrorSend),  gcnew Action(this,&FiniteStateMachine::CapturePlate), gcnew Action(this,&FiniteStateMachine::ErrorSend), gcnew Action(this,&FiniteStateMachine::ErrorPlate)},
		{nullptr, gcnew Action(this,&FiniteStateMachine::SetNewAddress), gcnew Action(this,&FiniteStateMachine::EnterPZ), gcnew Action(this,&FiniteStateMachine::EnterPZ_EF), nullptr, nullptr, nullptr, nullptr, gcnew Action(this,&FiniteStateMachine::ErrorSend), nullptr},
		{nullptr, nullptr, gcnew Action(this,&FiniteStateMachine::EnterPZ), gcnew Action(this,&FiniteStateMachine::EnterPZ_EF), gcnew Action(this,&FiniteStateMachine::ReadyCheck), nullptr, nullptr, nullptr, gcnew Action(this,&FiniteStateMachine::ErrorSend), nullptr},
		{nullptr, nullptr, nullptr, gcnew Action(this,&FiniteStateMachine::EnterPZ_EF), gcnew Action(this,&FiniteStateMachine::ReadyCheck), gcnew Action(this,&FiniteStateMachine::ReadyCheckFixedSattelite), nullptr, nullptr, gcnew Action(this,&FiniteStateMachine::ErrorSend), nullptr},
		{nullptr, nullptr, nullptr, gcnew Action(this,&FiniteStateMachine::EnterPZ_EF), gcnew Action(this,&FiniteStateMachine::ReadyCheck), gcnew Action(this,&FiniteStateMachine::CapturePlate), gcnew Action(this,&FiniteStateMachine::ReadyCheckFixedSattelite), nullptr, gcnew Action(this,&FiniteStateMachine::ErrorSend), nullptr},
		{nullptr, nullptr, nullptr, nullptr, gcnew Action(this,&FiniteStateMachine::ReadyCheck), gcnew Action(this,&FiniteStateMachine::CapturePlate), nullptr, gcnew Action(this,&FiniteStateMachine::ReadyCheck), gcnew Action(this,&FiniteStateMachine::ErrorSend), nullptr},
		{gcnew Action(this,&FiniteStateMachine::CapturePlate), gcnew Action(this,&FiniteStateMachine::SetNewAddress),  gcnew Action(this,&FiniteStateMachine::EnterPZ), gcnew Action(this,&FiniteStateMachine::EnterPZ_EF), gcnew Action(this,&FiniteStateMachine::ReadyCheck), gcnew Action(this,&FiniteStateMachine::ReadyCheckFixedSattelite), gcnew Action(this,&FiniteStateMachine::CapturePlate), gcnew Action(this,&FiniteStateMachine::ReadyCheck), gcnew Action(this,&FiniteStateMachine::CapturePlate), nullptr},
		{gcnew Action(this,&FiniteStateMachine::CapturePlate), gcnew Action(this,&FiniteStateMachine::ErrorPlate), gcnew Action(this,&FiniteStateMachine::ErrorPlate), gcnew Action(this,&FiniteStateMachine::ErrorPlate), gcnew Action(this,&FiniteStateMachine::ErrorPlate), gcnew Action(this,&FiniteStateMachine::ErrorPlate), gcnew Action(this,&FiniteStateMachine::ErrorPlate), gcnew Action(this,&FiniteStateMachine::ErrorPlate), gcnew Action(this,&FiniteStateMachine::ErrorPlate), gcnew Action(this,&FiniteStateMachine::ErrorPlate)}
	};
	this->fsm = fsmTmp;
}
void FiniteStateMachine::CapturePlate(){
	if(manchester->configuration(NumPlate) == -1){
		this->State = States::ErrorCapture;
	}
	else{
		this->State = States::Start;
	}
}
void FiniteStateMachine::SetNewAddress(){
	//stages = gcnew Stages();
	sizes = gcnew SizeExchange(4,2,1,1);
	stages->Config(sizes,0,Address,1,2);
	stages->GeneratedAddress();
	for(int i = 0; i < sizes->SendNumberOfFrames; i++){
		for(int j = 0; j < sizes->Steps; j++){
			if(j == 0){
				if(sendOk = manchester->sendData(10, stages->NewAddress, j, stages->SubAddressSend, sizes->SendNumberOfDataWords, stages->MassToSend[i]))
					this->State = States::SetNewAddress;
				else{
					break;
					this->State = States::ErrorSend;
				}
			}
			else{
				if(sendOk = manchester->sendData(10, stages->NewAddress, j, stages->SubAddressGet, sizes->GetNumberOfDataWords, stages->MassToGet[i]))
					this->State = States::SetNewAddress;
				else{
					this->State = States::ErrorSend;
					break;
				}
			}
		}
		if(this->State == States::ErrorSend)
			break;
	}
}
void FiniteStateMachine::ErrorSend(){
	this->State = States::ErrorSend;
}
void FiniteStateMachine::ErrorPlate(){
	this->State = States::ErrorCapture;
}

void FiniteStateMachine::EnterPZ(){
	//stages = gcnew Stages();
	sizes = gcnew SizeExchange(32,32,2,2);
	stages->Config(sizes,0,Address,3,4);
	stages->GeneratedPZ();
	for(int i = 0; i < sizes->SendNumberOfFrames; i++){
		for(int j = 0; j < sizes->Steps; j++){
			if(j == 0){
				if(sendOk = manchester->sendData(10, stages->NewAddress, j, stages->SubAddressSend, sizes->SendNumberOfDataWords, stages->MassToSend[i]))
					this->State = States::EnterPZ;
				else{
					this->State = States::ErrorSend;
					break;
				}
			}
			else{
				if(sendOk = manchester->sendData(10, stages->NewAddress, j, stages->SubAddressGet, sizes->GetNumberOfDataWords, stages->MassToGet[i]))
					this->State = States::EnterPZ;
				else{
					this->State = States::ErrorSend;
					break;
				}
			}
		}
		if(this->State == States::ErrorSend)
			break;
	}
}
void FiniteStateMachine::EnterPZ_EF(){
	//stages = gcnew Stages();
	if(FormManager::newEfems!=nullptr)
		stages->ReinitEfems(FormManager::newEfems);
	sizes = gcnew SizeExchange(32,32,98,98);
	stages->Config(sizes,0,Address,3,4);
	stages->GeneratedPZEfems();
	for(int i = 0; i < sizes->SendNumberOfFrames; i++){
		for(int j = 0; j < sizes->Steps; j++){
			if(j == 0){
				if(sendOk = manchester->sendData(10, stages->NewAddress, j, stages->SubAddressSend, sizes->SendNumberOfDataWords, stages->MassToSend[i]))
					this->State = States::EnterPZ_EF;
				else{
					this->State = States::ErrorSend;
					break;
				}
			}
			else{
				if(sendOk = manchester->sendData(10, stages->NewAddress, j, stages->SubAddressGet, sizes->GetNumberOfDataWords, stages->MassToGet[i]))
					this->State = States::EnterPZ_EF;
				else{
					this->State = States::ErrorSend;
					break;
				}
			}
		}
		if(this->State == States::ErrorSend)
			break;
	}
}
void FiniteStateMachine::ReadyCheck(){
	for(int i = 0; i < sizes->GetNumberOfFrames; i++){
		for(int j = 1; j < sizes->Steps; j++){
			if(sendOk = manchester->sendData(10, stages->NewAddress, j, stages->SubAddressGet, sizes->GetNumberOfDataWords, stages->MassToGet[i])){
				sizes->SetPrepareMass(stages->PrepareResponseData(stages->MassToGet[i]));
				//sizes->SetPrepareMass(stages->PrepareResponseData(manchester->Received));
				this->State = States::ReadyCheck;
			}
			else{
				this->State = States::ErrorSend;
				break;
			}
		}
		if(this->State == States::ErrorSend)
			break;
	}
}
void FiniteStateMachine::ReadyCheckFixedSattelite(){
	try{
		Monitor::Enter(stages, locked);
		stages->ReadyCheck(6);
		this->State = States::ReadyCheckFixedSattelite;
	}
	finally{
		if (locked)
		{
			Monitor::Exit(stages);
			locked = false;
		}
	}
}
void FiniteStateMachine::ProcessEvent(Events theEvents){
	this->fsm[(int)this->State,(int)theEvents]->Invoke();
}

void FiniteStateMachine::SetReadyConfig(){
	//stages = gcnew Stages();
	sizes = gcnew SizeExchange(32,32,1,1);
	stages->Config(sizes,0,Address,5,5);
}
void FiniteStateMachine::Fixed(char subAddr, Events state){
	if(state == Events::FixedOn){
		try{
			Monitor::Enter(stages, locked);
			stages->ReadyCheck(subAddr);
			this->State = States::ReadyCheckFixedSattelite;
		}
		finally{
			if (locked)
			{
				Monitor::Exit(stages);
				locked = false;
			}
		}
	}
	else if(state == Events::FixedOff){
		try{
			Monitor::Enter(stages, locked);
			stages->ReadyCheck(subAddr);
			this->State = States::ReadyCheck;
		}
		finally{
			if (locked)
			{
				Monitor::Exit(stages);
				locked = false;
			}
		}
	}
}