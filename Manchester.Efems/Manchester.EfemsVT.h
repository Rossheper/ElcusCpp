#pragma once
#include "Manchester.Efems.h"
namespace ManchesterEfems {
	public ref class EfemsVT: Efems
	{
		// TODO: здесь следует добавить свои методы для этого класса.
	public:
		EfemsVT():Efems(){}
		virtual unsigned short * currEfemsData(int frame, int ncd) override;
	};
}

