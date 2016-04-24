// Главный DLL-файл.

#include "stdafx.h"

#include "Manchester.Task.h"

using namespace ManchesterTask;

PZ::PZ() {
	Init();
}
PZ::PZ(CollectDataPz ^CollPz) {
	Init();
	_CollPz = CollPz;
	_currGrid = (CollPz->GridFieldsData["EditedPZGrid"]);
}
PZ::PZ(CollectDataPz ^CollPz, String^ nameGrid) {
	Init();
	_CollPz = CollPz;
	_currGrid = (CollPz->GridFieldsData[nameGrid]);
}
void PZ::Init() {
	_eps0 = 0;
	_beta0 = 0;
	_B0 = 0;
	_L0 = 0;
	_Qo = 0;
	_psy0 = 0;
	_K = 0;
	_Ukvp = 0;
	_Qtr = 0;
	_Fgsn = 0;
	_Dpry = 0;
	_Pg = 0;
	_FTM = 0;
	_Kren = 0;
	_Dnc = 0;
	_Dbn = 0;
	_Dpr = 0;
	_Kop = 0;
	_Kd = 0;
	_V0x = 0;
	_V0y = 0;
	_X = 0;
	_Y = 0;
	_Z = 0;
	_buffer_pz_write = gcnew array<array<unsigned short>^>(2);
	for (int i = 0; i < 2; i++) {
		_buffer_pz_write[i] = gcnew array<unsigned short>(num_col_pz_write_buffer);
		for (int j = 0; j < num_col_pz_write_buffer; j++)
			_buffer_pz_write[i][j] = 0;
	}
	_CollPz = gcnew CollectDataPz();
	_currGrid = gcnew Dictionary<String^, String^>();
}
double PZ::Interp(double curX, double x1, double x2, double y1, double y2) {
	return ((curX - x1) / (x2 - x1)) * (y2 - y1) + y1;
}
double PZ::Interp2(double *X, double *Y, double **Z, int sizeX, int sizeY, double Xr, double Yr) {
	int currX = 0, currY = 0;
	double bx = 0, by = 0, k00 = 0, k10 = 0, k01 = 0, k11 = 0;
	double *p_Z = (double*)Z;
	for (int i = 0; i < sizeX - 1; i++) {
		if ((X[i] <= Xr) && (X[i + 1] >= Xr)) {
			currX = i;
			for (int j = 0; j < sizeY - 1; j++) {
				if ((Y[j] <= Yr) && (Y[j + 1] >= Yr)) {
					currY = j;
					break;
				}
			}
			break;
		}
	}

	bx = (double)Math::Abs(Xr - X[currX]) / (double)Math::Abs(X[currX + 1] - X[currX]);
	by = (double)Math::Abs(Yr - Y[currY]) / (double)Math::Abs(Y[currY + 1] - Y[currY]);

	k00 = (1 - bx) * (1 - by);
	k10 = bx * (1 - by);
	k01 = (1 - bx) * by;
	k11 = bx * by;
	return k00*p_Z[currY*sizeX + currX] + k10*p_Z[currY*sizeX + (currX + 1)] + k01*p_Z[(currY + 1)*sizeX + currX] + k11*p_Z[(currY + 1) *sizeX + (currX + 1)];
}

double PZ::Interp2(double *X, double *Y, array<double, 2>^ Zz, int sizeX, int sizeY, double Xr, double Yr) {
	int currX = 0, currY = 0;
	double bx = 0, by = 0, k00 = 0, k10 = 0, k01 = 0, k11 = 0;
	//double *p_Z = (double*)Z;
	for (int i = 0; i < sizeX - 1; i++) {
		if ((X[i] <= Xr) && (X[i + 1] >= Xr)) {
			currX = i;
			for (int j = 0; j < sizeY - 1; j++) {
				if ((Y[j] <= Yr) && (Y[j + 1] >= Yr)) {
					currY = j;
					break;
				}
			}
			break;
		}
	}

	bx = (double)Math::Abs(Xr - X[currX]) / (double)Math::Abs(X[currX + 1] - X[currX]);
	by = (double)Math::Abs(Yr - Y[currY]) / (double)Math::Abs(Y[currY + 1] - Y[currY]);

	k00 = (1 - bx) * (1 - by);
	k10 = bx * (1 - by);
	k01 = (1 - bx) * by;
	k11 = bx * by;
	return k00*Zz[currY, currX] + k10*Zz[currY, (currX + 1)] + k01*Zz[(currY + 1), currX] + k11*Zz[(currY + 1), (currX + 1)];
}
int PZ::GetIndex(double *B, int size, double _Dnc) {
	for (int i = 0; i < size - 1; i++)
		if ((_Dnc >= (*(B + i))) && (_Dnc < (*(B + i + 1))))
			return i;
	return size - 1;
}
//1. Угол пуска
double PZ::Koef_thetaTR(short pg, unsigned int dnc, double hb) {
	double Dbn = 0;
	double X[] = { 0.125*_dmax, 0.1875*_dmax, 0.25*_dmax, 0.375*_dmax, 0.5*_dmax, 0.625*_dmax, 0.75*_dmax, 0.875*_dmax, _dmax };
	double Y[] = { 0,3000 };
	if (pg == 1) {
		array<double, 2>^ Z = { { 8,12,17,27,31,40,47,55,55 },{ 7,9,12,18,24,30,35,40,44 } };
		return (Interp2(&X[0], &Y[0], Z, sizeof(X) / sizeof(double), sizeof(Y) / sizeof(double), dnc, hb)* M_PI / 180);
	}
	else {
		array<double, 2>^ Z = { { 10,24,29,35,42,47,55,55,55 },{ 7,18,20,20,28,28,32,36,38 } };
		return (Interp2(&X[0], &Y[0], Z, sizeof(X) / sizeof(double), sizeof(Y) / sizeof(double), dnc, hb)* M_PI / 180);
	}
}
int PZ::Koef_Q0(double thetaTr) {
	return (int)Math::Round(thetaTr*Math::Pow(2, 17), MidpointRounding::AwayFromZero);
}
unsigned short PZ::Koef_Dbn(short pg) {
	if (pg == 1)
		return (unsigned short)Math::Round(0.03125*_dmax, MidpointRounding::AwayFromZero);
	else
		return (unsigned short)Math::Round(0.004375*_dmax, MidpointRounding::AwayFromZero);
}
short PZ::Koef_K(short pg, unsigned int dnc, double hb) {
	if (pg == 1) {
		if (dnc >= 0.1875*_dmax)
			return 1966;
		else
			return 0;
	}
	else {
		if (dnc <= 0.1875*_dmax)
			return 0;
		else {
			double X[] = { 0.1875*_dmax, 0.25*_dmax, 0.375*_dmax, 0.50*_dmax, 0.625*_dmax, 0.75*_dmax, 0.875*_dmax, _dmax };
			double Y[] = { 0,3000 };
			array<double, 2>^ Z = { { 0.015, 0.015, 0.015, 0.015, 0.015, 0.015, 0.015, 0.015 },{ 0.011, 0.011, 0.011, 0.011, 0.015, 0.015, 0.015, 0.015 } };
			return (short)Math::Round((Interp2(&X[0], &Y[0], Z, sizeof(X) / sizeof(double), sizeof(Y) / sizeof(double), dnc, hb))*Math::Pow(2, 17), MidpointRounding::AwayFromZero);
		}
	}
}
//Коп
unsigned short PZ::Koef_Kop(short pg, unsigned int dnc) {
	double Xt[2][4] = { {0.125*_dmax,0.1875*_dmax,0.25*_dmax,_dmax},{0.7,1,1.5,1.5} };
	int index = GetIndex(Xt[0], sizeof(*Xt) / sizeof(**Xt), dnc);
	return (unsigned short)Math::Round(Interp(dnc, Xt[0][index], Xt[0][index + 1], Xt[1][index], Xt[1][index + 1])*Math::Pow(2, 7), MidpointRounding::AwayFromZero);
}
unsigned short PZ::Koef_Kd(short pg, unsigned int dnc) {
	if (dnc <= 0.625*_dmax && dnc >= 0.125*_dmax)
		return 0;
	else
		return (unsigned short)Math::Round(0.2*Math::Pow(2, 10), MidpointRounding::AwayFromZero);
}

void PZ::Koef_Mpn(double ec, double bc) {
	_CollPz->mpn[0][0] = (int)Math::Round(Math::Cos(ec) * Math::Cos(bc) * 131072, MidpointRounding::AwayFromZero);
	_CollPz->mpn[1][0] = (int)Math::Round(Math::Sin(ec) * 131072, MidpointRounding::AwayFromZero);
	_CollPz->mpn[2][0] = (int)Math::Round(-Math::Cos(ec) * Math::Sin(bc) * 131072, MidpointRounding::AwayFromZero);
	_CollPz->mpn[0][1] = (int)Math::Round(-Math::Sin(ec) * Math::Cos(bc) * 131072, MidpointRounding::AwayFromZero);
	_CollPz->mpn[1][1] = (int)Math::Round(Math::Cos(ec) * 131072, MidpointRounding::AwayFromZero);
	_CollPz->mpn[2][1] = (int)Math::Round(Math::Sin(ec) * Math::Sin(bc) * 131072, MidpointRounding::AwayFromZero);
	_CollPz->mpn[0][2] = (int)Math::Round(Math::Sin(bc) * 131072, MidpointRounding::AwayFromZero);
	_CollPz->mpn[1][2] = 0;
	_CollPz->mpn[2][2] = (int)Math::Round(Math::Cos(bc) * 131072, MidpointRounding::AwayFromZero);
	//return 0;
}
short PZ::Koef_Ukvp(short pg) {
	if (pg == 1)
		return 1638;
	else
		return 0;
}
// 5. Программные дальности
unsigned short PZ::Koef_Dpry(short pg, unsigned int dnc, double hb) {
	double X[] = { 0.125*_dmax, 0.1875*_dmax, 0.25*_dmax, 0.375*_dmax, 0.5*_dmax, 0.625*_dmax, 0.75*_dmax, 0.875*_dmax, _dmax };
	double Y[] = { 0,3000 };
	if (pg == 1) {
		array<double, 2>^ Z = { { 0.075*_dmax,0.075*_dmax,0.075*_dmax,0.075*_dmax,0.175*_dmax,0.25*_dmax,0.45*_dmax,0.45*_dmax,0.45*_dmax },
								{ 0.075*_dmax,0.125*_dmax,0.15*_dmax,0.2125*_dmax,0.2875*_dmax,0.5*_dmax,0.55*_dmax,0.65*_dmax,0.65*_dmax } };
		return (unsigned short)Math::Round((Interp2(&X[0], &Y[0], Z, sizeof(X) / sizeof(double), sizeof(Y) / sizeof(double), dnc, hb)) / 2, MidpointRounding::AwayFromZero);
	}
	else {
		array<double, 2>^ Z = { { 0.08125*_dmax,0.0875*_dmax,0.1125*_dmax,0.25*_dmax,0.375*_dmax,0.375*_dmax,0.6875*_dmax,0.875*_dmax,0.975*_dmax },
								{ 0.075*_dmax,0.08125*_dmax,0.125*_dmax,0.25*_dmax,0.4*_dmax,0.4*_dmax,0.625*_dmax,0.775*_dmax,0.925*_dmax } };
		return (unsigned short)Math::Round((Interp2(&X[0], &Y[0], Z, sizeof(X) / sizeof(double), sizeof(Y) / sizeof(double), dnc, hb)) / 2, MidpointRounding::AwayFromZero);
	}
}
// 6. Дальность формирования единичной комманды "вверх"
int PZ::Koef_Dpr(short pg, unsigned int dnc) {
	if (pg == 1 || (0.125*_dmax <= dnc && dnc <= 0.75*_dmax))
		return 0;
	else
		return (int)Math::Round((0.45*_dmax) / 2);
}
short PZ::Koef_Qtr(short pg) {
	if (pg == 1)
		return 30;
	else
		return 90;
}
float PZ::Koef_V0x(double theta0Interp) {
	return (float)Math::Round((Math::Cos(theta0Interp)*v0 * 1024), MidpointRounding::AwayFromZero);
}
float PZ::Koef_V0y(double theta0Interp) {
	return (float)Math::Round((Math::Sin(theta0Interp)*v0 * 1024), MidpointRounding::AwayFromZero);
}
void PZ::CalcPzAndCreateOutBuffer() {

	double _eo = 0;
	double _bo = 0;
	float _Xpy = 0;
	float _Ypy = 0;
	float _Zpy = 0;
	double thetaTrTmp = 0;

	unsigned short *eoPtr = (unsigned short *)&_eo;
	unsigned short *boPtr = (unsigned short *)&_bo;

	unsigned long *tempX = (unsigned long *)&_Xpy;
	unsigned long *tempY = (unsigned long *)&_Ypy;
	unsigned long *tempZ = (unsigned long *)&_Zpy;

	_Dnc = Convert::ToUInt32(_currGrid["П1"]);
	double hb = Convert::ToDouble(_currGrid["П4"]);
	Dictionary<String^, String^>^ _currNotEditedGrid = _CollPz->GridFieldsData["NotEditedPZGrid"];

	_Xpy = (float)Convert::ToDouble(_currGrid["П8"]);
	_Ypy = (float)Convert::ToDouble(_currGrid["П9"]);
	_Zpy = (float)Convert::ToDouble(_currGrid["П10"]);
	_X = (unsigned int)(_Xpy * 32);
	_Y = (unsigned int)(_Ypy * 32);
	_Z = (unsigned int)(_Zpy * 32);
	_bo = Convert::ToDouble(_currGrid["П11"]);
	_eo = Convert::ToDouble(_currGrid["П12"]);

	_beta0 = (unsigned int)(_bo * 67108864);
	_eps0 = (unsigned int)(_eo * 67108864);
	_B0 = (unsigned int)(Convert::ToDouble(_currGrid["П13"]) * 67108864);
	_L0 = (unsigned int)(Convert::ToDouble(_currGrid["П14"]) * 67108864);


	thetaTrTmp = Koef_thetaTR(Convert::ToInt16(_currGrid["П5"]), _Dnc, hb);
	_Qo = Koef_Q0(thetaTrTmp);
	_K = Koef_K(Convert::ToInt16(_currGrid["П5"]), _Dnc, hb);
	_Ukvp = Koef_Ukvp(Convert::ToInt16(_currGrid["П5"]));
	_Qtr = Koef_Qtr(Convert::ToInt16(_currGrid["П5"]));
	_Dbn = Koef_Dbn(Convert::ToInt16(_currGrid["П5"]));
	_Dpr = Koef_Dpr(Convert::ToInt16(_currGrid["П5"]), _Dnc);
	_Dpry = Koef_Dpry(Convert::ToInt16(_currGrid["П5"]), _Dnc, hb);
	_Kop = Koef_Kop(Convert::ToInt16(_currGrid["П5"]), _Dnc);
	_Kd = Koef_Kd(Convert::ToInt16(_currGrid["П5"]), _Dnc);
	_V0x = (unsigned short)(Koef_V0x(thetaTrTmp));
	_V0y = (unsigned short)(Koef_V0y(thetaTrTmp));
	Koef_Mpn(Convert::ToDouble(_currGrid["П3"]), Convert::ToDouble(_currGrid["П2"]));


	_currNotEditedGrid["П15"] = Convert::ToString(_Qo);
	_currNotEditedGrid["П16"] = Convert::ToString(_V0x);
	_currNotEditedGrid["П17"] = Convert::ToString(_V0y);
	_currNotEditedGrid["П18"] = Convert::ToString(_K);
	_currNotEditedGrid["П19"] = Convert::ToString(_Ukvp);
	_currNotEditedGrid["П20"] = Convert::ToString(_Dpry);
	_currNotEditedGrid["П21"] = Convert::ToString(_Dpr);
	_currNotEditedGrid["П22"] = Convert::ToString(_Qtr);
	_currNotEditedGrid["П29"] = Convert::ToString(_Kop);
	_currNotEditedGrid["П30"] = Convert::ToString(_Kd);
	_CollPz->GridFieldsData["NotEditedPZGrid"] = _currNotEditedGrid;

	_buffer_pz_write[0][0] = 1;                                 // формируем слова данных для первого кадра
	_buffer_pz_write[0][1] = _X;
	_buffer_pz_write[0][2] = _X >> 16;
	_buffer_pz_write[0][3] = _Y;
	_buffer_pz_write[0][4] = _Y >> 16;
	_buffer_pz_write[0][5] = _Z;
	_buffer_pz_write[0][6] = _Z >> 16;
	_buffer_pz_write[0][7] = _beta0;
	_buffer_pz_write[0][8] = _beta0 >> 16;
	_buffer_pz_write[0][9] = _eps0;
	_buffer_pz_write[0][10] = _eps0 >> 16;
	_buffer_pz_write[0][11] = _B0;
	_buffer_pz_write[0][12] = _B0 >> 16;
	_buffer_pz_write[0][13] = _L0;
	_buffer_pz_write[0][14] = _L0 >> 16;
	_buffer_pz_write[0][15] = _Qo;
	_buffer_pz_write[0][16] = _Qo >> 16;
	_buffer_pz_write[0][17] = _psy0;
	_buffer_pz_write[0][18] = _psy0 >> 16;
	_buffer_pz_write[0][19] = _K;
	_buffer_pz_write[0][20] = _Ukvp;
	_buffer_pz_write[0][21] = ((Convert::ToUInt16(_currGrid["П6"]) & 0x00FF) << 8) + (_Qtr & 0x00FF);
	_buffer_pz_write[0][22] = _Dpry;
	_buffer_pz_write[0][23] = (Convert::ToInt16(_currGrid["П5"]) & 0x3);
	_buffer_pz_write[0][23] = (_buffer_pz_write[0][23] << 1) + (Convert::ToInt16(_currGrid["П26"]) & 0x1);
	_buffer_pz_write[0][23] = (_buffer_pz_write[0][23] << 1) + (Convert::ToInt16(_currGrid["П23"]) & 0x1);
	_buffer_pz_write[0][24] = _Dnc;
	_buffer_pz_write[0][25] = _Dnc >> 16;
	_buffer_pz_write[0][26] = _Dbn;
	_buffer_pz_write[0][27] = _Dpr;
	_buffer_pz_write[0][28] = _Kop;
	_buffer_pz_write[0][29] = _Kd;
	_buffer_pz_write[0][30] = _V0x;
	_buffer_pz_write[0][31] = _V0y;

	_buffer_pz_write[1][0] = 2;                                 // формируем слова данных для второго кадра
	_buffer_pz_write[1][1] = _CollPz->mpn[0][0];
	_buffer_pz_write[1][2] = _CollPz->mpn[0][0] >> 16;
	_buffer_pz_write[1][3] = _CollPz->mpn[1][0];
	_buffer_pz_write[1][4] = _CollPz->mpn[1][0] >> 16;
	_buffer_pz_write[1][5] = _CollPz->mpn[2][0];
	_buffer_pz_write[1][6] = _CollPz->mpn[2][0] >> 16;
	_buffer_pz_write[1][7] = _CollPz->mpn[0][1];
	_buffer_pz_write[1][8] = _CollPz->mpn[0][1] >> 16;
	_buffer_pz_write[1][9] = _CollPz->mpn[1][1];
	_buffer_pz_write[1][10] = _CollPz->mpn[1][1] >> 16;
	_buffer_pz_write[1][11] = _CollPz->mpn[2][1];
	_buffer_pz_write[1][12] = _CollPz->mpn[2][1] >> 16;
	_buffer_pz_write[1][13] = _CollPz->mpn[0][2];
	_buffer_pz_write[1][14] = _CollPz->mpn[0][2] >> 16;
	_buffer_pz_write[1][15] = _CollPz->mpn[2][2];
	_buffer_pz_write[1][16] = _CollPz->mpn[2][2] >> 16;
	_buffer_pz_write[1][17] = (unsigned short)*tempX;
	_buffer_pz_write[1][18] = *tempX >> 16;
	_buffer_pz_write[1][19] = (unsigned short)*tempY;
	_buffer_pz_write[1][20] = *tempY >> 16;
	_buffer_pz_write[1][21] = (unsigned short)*tempZ;
	_buffer_pz_write[1][22] = *tempZ >> 16;
	_buffer_pz_write[1][23] = *boPtr++;
	_buffer_pz_write[1][24] = *boPtr++;
	_buffer_pz_write[1][25] = *boPtr++;
	_buffer_pz_write[1][26] = *boPtr;
	_buffer_pz_write[1][27] = *eoPtr++;
	_buffer_pz_write[1][28] = *eoPtr++;
	_buffer_pz_write[1][29] = *eoPtr++;
	_buffer_pz_write[1][30] = *eoPtr;
}