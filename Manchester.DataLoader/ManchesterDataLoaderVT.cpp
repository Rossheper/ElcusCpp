#include "stdafx.h"
#include "Math.h"
#include "Manchester.DataLoaderVT.h"
using namespace System;
using namespace System::Text;
using namespace ManchesterDataLoader;

//Функция, рассчитывающая значение фиксированной точки для ПЗ
double DataLoaderVT::parseWindowPZ(int i){
	if(i < 4) //x0, y0, z0
		return Math::Pow(2,5);
	else if(i > 3 && i < 8) //beta0, e0, B0, L0
		return Math::Pow(2,26);
	else if((i > 7 && i < 11) || (i > 20 && i < 29))  //theta0, K , Mnp
		return Math::Pow(2,17);
	else if(i > 18 && i < 22)            // Кд , Vx0, Vy0
		return Math::Pow(2,10);
	else if(i == 18)
		return Math::Pow(2,7);
	else if(i == 17 || i == 13)  // Дпр , ДпрУ
		return Math::Pow(2, -1);
	else if(i == 11)  // Ukb
		return Math::Pow(2, 15);
	return 1;
}
//Функция, разбирающая полученный массив данных с "ПЗ" от АЭ (VT)
unsigned int *DataLoaderVT::parsePZ(unsigned short *input, int ncd, int frame){
	unsigned int *buf = new unsigned int[ncd];
	int k = 19;
	for(int i = 0; i < ncd; i++)
		buf[i] = 0;
	buf[0] = input[0];
	if(frame == 0){
		for(int i = 1, j = 1; j < ncd - 1; j+=2, i++){
			if(j < 19){
				buf[i] = input[j + 1];
				buf[i] = buf[i]<<16;
				buf[i] += input[j];
			}
			else{
				buf[10] = input[19];     //K
				buf[11] = input[20];     //UkvP
				buf[12] = input[21];     //Fgsn + Qtr
				buf[13] = input[22];     //DprY
				buf[14] = input[23];     //Pg FTM Kren

				buf[15] = input[25];
				buf[15] = buf[15]<<16;    //Dnc
				buf[15] += input[24];

				buf[16] = input[26];      //Дбн
				buf[17] = input[27];      //Дпр
				buf[18] = input[28];      //Коп
				buf[19] = input[29];      //Кд
				buf[20] = input[30];      //V0x
				buf[21] = input[31];      //V0y
				break;
			}
		}
	}
	else{
		for(int i = 1, j = 1; i < ncd - 1; j+=2, i++){
			if(j < 22){
				buf[i] = input[j + 1];
				buf[i] = buf[i]<<16;     //Матрицы   + Xny Yny Zny
				buf[i] += input[j];
			}
			else{
				buf[12] = input[24];
				buf[12] = buf[12]<<16;         //Бета01 младшая часть
				buf[12] += input[23];
				//Бета01
				buf[13] = input[26];
				buf[13] = buf[13]<<16;         //Бета01 старшая часть
				buf[13] += input[25];

				buf[14] = input[28];
				buf[14] = buf[14]<<16;         //Эпс01 младшая часть
				buf[14] += input[27];
				//Эпс01
				buf[15] = input[30];
				buf[15] = buf[15]<<16;         //Эпс01 старшая часть
				buf[15] += input[29];
				break;
			}
		}
	}
	return buf;
}
////Установка адреса
//List<String^>^ DataLoaderVT::FormattedSetAddr(unsigned int* dataInput, int k, int frmt){
//	List<String^>^ list = gcnew List<String^>();
//    //retStr = gcnew StringBuilder();
//    /*for(int i = 0; i < wordCount[ComboBox1->ItemIndex][frmt]; i++)
//        str += toHex(man.mass[i]).operator+=(" ");*/
//    for(int i = 0; i < wordCount[ComboBox1->ItemIndex][frmt]; i++){
//        if(i == 1){
//			list->Add((dataInput[i]&0x1F).ToString());
//            //P->Caption = (man.mass[i]&0x600)>>9;       //П
//            //currAddress->Caption = (man.mass[i]&0x1F); //Адрес
//            currAddress->Font->Color = clGreen;
//            if((man.mass[i]& 0x00C0)>>6 == 1){
//                VM->Font->Color = clGreen;
//            }
//            else if((man.mass[i]& 0x00C0)>>6 == 2){
//                GSN->Font->Color = clGreen;
//            }
//            else{
//                GSN->Font->Color = clRed;
//                VM->Font->Color = clRed;
//            }
//        }
//        else if(i == 2){}
//            //FirmwareMBPP->Caption = (IntToStr((man.mass[i + 1])).operator+=(".").operator+=(man.mass[i]));
//        str += toHex(man.mass[i]).operator+=("  ");
//    }
//    return str;
//}
//Эфемериды
String^ DataLoaderVT::FormattedEf(unsigned int* dataInput, int count){
	StringBuilder^ retStr = gcnew StringBuilder();
	for(int i = 0; i < count; i++)
		retStr->Append(String::Format("{0:X}",dataInput[i]))->Insert(3," ")->Append("  ");
	return retStr->ToString();
}
//ПЗ
String^ DataLoaderVT::FormattedPZ(unsigned int* dataInput, int k){
	StringBuilder^ retStr = gcnew StringBuilder();
	if(k == 0){
		for(int i = 1; i < 22; i++){
			if(i < 10){
				retStr->Append(NameParams[i-1]);
				retStr->Append(dataInput[i] / parseWindowPZ(i));
				retStr->Append(" |");
			}
			else if(i == 14){
				retStr->Append(NameParams[14]);//Пг
				retStr->Append((dataInput[14] & 0xC)>>2)->Append(" |");
				retStr->Append(NameParams[15]);//FTM
				retStr->Append((dataInput[14] & 0x2)>>1)->Append(" |");
				retStr->Append(NameParams[16]);//Kren
				retStr->Append(dataInput[14] & 0x1)->Append(" |");
			}
			else if(i == 12){
				retStr->Append(NameParams[11])->Append((dataInput[12] & 0xFF00)>>8)->Append(" |");//Fgsn
				retStr->Append(NameParams[12])->Append((dataInput[12] & 0x00FF))->Append(" |");//thetaTR
			}
			else if(i > 9 && (i != 14 || i != 12)){
				if(i < 12){
					retStr->Append(NameParams[i-1]);
				}
				else if(i == 13){
					retStr->Append(NameParams[i]);
				}
				else{
					retStr->Append(NameParams[i+2]);
				}
				retStr->Append(dataInput[i] /parseWindowPZ(i))->Append(" |");;
			}
		}
	}
	else if(k == 1){
		for(int i = 1; i < 16; i++){
			if(i < 9){ //Mpn
				retStr->Append(NameParams[i + 23])->Append(Convert::ToInt32(dataInput[i])/parseWindowPZ(i + 20))->Append(" |");
			}
			else if(i > 8 && i < 12){ //Xny Yny Zny
				retStr->Append(NameParams[i + 23])->Append(dataInput[i] / parseWindowPZ(i + 20))->Append(" |");
			}
			else{
				retStr->Append(NameParams[35])->Append(dataInput[13])->Append(" |")->Append(dataInput[12])->Append(" |");
				retStr->Append(NameParams[36])->Append(dataInput[15])->Append(" |")->Append(dataInput[14])->Append(" |");
				break;
			}
		}
	}
	return retStr->ToString();
}