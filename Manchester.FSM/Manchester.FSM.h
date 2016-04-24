// Manchester.FSM.h

#pragma once

using namespace System;
using namespace ManchesterDataLoader;
using namespace ManchesterEfems;
using namespace Manchestermanchester;
using namespace ManchesterStages;
using namespace ManchesterTask;
using namespace System::Threading;
using namespace System::Threading::Tasks;
namespace ManchesterFSM {

	public ref class FiniteStateMachine
	{
	private:
		PZ ^ _pz;
		Action ^ fsm2;
		array<Action^,2> ^ fsm;
		Stages ^ stages;
		SizeExchange ^ sizes;
		Manchester ^manchester;
		DataLoader ^dataLoader;

		bool locked;
		bool sendOk;
		void CapturePlate();
		void SetNewAddress();
		void EnterPZ();
		void EnterPZ_EF();
		void ReadyCheck();
		void ReadyCheckFixedSattelite();
		void ErrorSend();
		void ErrorPlate();
	public:
		delegate Action^ MyDel();

		enum class States
		{
			Start,
			SetNewAddress,
			EnterPZ,
			EnterPZ_EF,
			ReadyCheck,
			ReadyCheckFixedSattelite,
			ErrorSend,
			ErrorCapture
		};
		enum class Events 
		{ 
			CapturePlate, 
			SetAddr, 
			CalcPZ, 
			CalcPZ_Ef, 
			ReadyOn, 
			ReadyOff, 
			FixedOn, 
			FixedOff,
			Abort,
			AbortPlate
		};
		property unsigned int* ResponseMass{
			virtual unsigned int* get(){
				return sizes->GetDataMass;
			}
		}
		property int LengthDataMass{
			virtual int get(){
				return sizes->GetNumberOfDataWords/2;
			}
		}
		property States State;
		property int NumPlate;
		property int Address;
		FiniteStateMachine();
		void ProcessEvent(Events theEvents);
		void SetReadyConfig();
		void Fixed(char subAddr, Events state);
	};
}
