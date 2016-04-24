// Главный DLL-файл.

#include "stdafx.h"
#include "Manchester.DataLoader.h"

using namespace ManchesterDataLoader;

DataLoader::DataLoader(){
	_nameParams = gcnew List<String^>();
	this->_mass = new unsigned int *[MASS_SIZE];
	for(int i = 0; i < MASS_SIZE; i++){
		this->_mass[i] = new unsigned int[MASS_COL_SIZE];
	}
}
DataLoader::~DataLoader(){
	if(this->_mass != nullptr){
		for(int i = 0; i < MASS_SIZE; i++){
			delete[] this->_mass[i];
		}
		delete[] this->_mass;
	}
	delete _nameParams;
}
//Функция, рассчитывающая степень двойки переданного числа
int DataLoader::getPower(double number){
	int power = 0;
	if(number == 0.5 )
		return -1;
	while(number > 1){
		number = (int)(number / 2);
		power++;
	}
	return power;
}

//Функция, рассчитывающая значение фиксированной точки для полученного ПЗ 
double DataLoader::parseWindowPZ(int i){
	if(i < 3) //x0, y0, z0
		return Math::Pow(2,5);
	else if(i > 2 && i < 7) //beta0, e0, B0, L0
		return Math::Pow(2,26);
	else if((i > 6 && i < 9) || (i > 14 && i < 24) || i == 31 )  //theta0, psy0, Mnp, Ktr
		return Math::Pow(2,17);
	else if((i == 9) || (i > 32 && i < 35)) //  y0гк, Kоп, K
		return Math::Pow(2,10);
	else if( i == 25 || i == 29 )  //Uкв, Dnc
		return Math::Pow(2,14);
	else if(i == 10)           //g
		return Math::Pow(2,21);
	else if(i == 26)           //H
		return Math::Pow(2,2);
	else if(i == 24 || i == 28)     //ДпрY, Дпр
		return Math::Pow(2,-1);
	return 1;
}


//Функция, формирующая буфер с обозначениями значений ПЗ
List<String^> ^ DataLoader::setParams(){
	ResXResourceReader ^res = gcnew ResXResourceReader("NameParams.resx");
	IDictionaryEnumerator^ dict = res->GetEnumerator();
	while(dict->MoveNext())
		_nameParams->Add(dict->Value->ToString());
	res->Close();
	return _nameParams;
}

//Функция, разбирающая полученный массив данных с эфемеридами от АЭ
unsigned short *DataLoader::parseEfems(unsigned short *input, int ncd){
	unsigned short *buf = new unsigned short[ncd];
	for(int i = 0; i < ncd; i++)
		buf[i] = 0;
	buf[0] = input[0];
	for(int i = 1; i < ncd; i++){
		short tmp = input[i]&0x00FF;
		buf[i] = (input[i]>>8) + (tmp<<8);
	}
	return buf;
}

//Функция, разбирающая полученный массив данных с "поправками ПД" от АЭ
unsigned int *DataLoader::parsePD(unsigned short *input, int ncd){
	unsigned int *buf = new unsigned int[ncd];
	for(int i = 0; i < ncd; i++)
		buf[i] = 0;
	buf[0] = input[0];
	for(int i = 1, j = 0; j < ncd - 1; i+=2, j++){
		buf[j] = input[i+1];
		buf[j] = buf[j]<<16;
		buf[j] += input[i];
	}
	return buf;
}

//Функция, разбирающая полученный массив данных с "ПЗ" от АЭ
unsigned int *DataLoader::parsePZ(unsigned short *input, int ncd, int frame){
	unsigned int *buf = new unsigned int[ncd];
	int k = 19;
	for(int i = 0; i < ncd; i++)
		buf[i] = 0;
	buf[0] = input[0];
	if(frame == 0){
		for(int i = 0, j = 1; j < ncd - 1; j+=2, i++){
			if(j < 22){
				buf[i] = input[j + 1];
				buf[i] = buf[i]<<16;
				buf[i] += input[j];
			}
			else{
				buf[i] = input[23];
				buf[i + 1] = input[24];
				break;
			}
		}
	}
	else{
		for(int i = 0, j = 1; i < ncd - 1; j+=2, i++){
			if(j < 18){
				buf[i] = input[j + 1];
				buf[i] = buf[i]<<16;     //Матрицы
				buf[i] += input[j];
			}
			else if( k == 23){
				buf[i] = input[24];
				buf[i] = buf[i]<<16;
				buf[i] += input[23];
				k+=2;
			}
			else{
				buf[i] = input[k];
				k++;
				if( k == 30)
					break;
			}
		}
	}
	return buf;
}

//Функция, формирующая массив с обозначениями команд управления
List<String^> ^DataLoader::getCmdKSH(){
	List<String^> ^lst = gcnew List<String^>();
	lst->Add("Установить адрес");
	lst->Add("Ввод задания");
	return lst;
}