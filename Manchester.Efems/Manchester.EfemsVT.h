#pragma once
#include "Manchester.Efems.h"
namespace ManchesterEfems {
	public ref class EfemsVT: Efems
	{
		// TODO: ����� ������� �������� ���� ������ ��� ����� ������.
	public:
		EfemsVT():Efems(){}
		virtual unsigned short * currEfemsData(int frame, int ncd) override;
	};
}

