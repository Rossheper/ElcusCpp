#include "stdafx.h"
#include "Manchester.EfemsVT.h"

using namespace ManchesterEfems;

unsigned short * EfemsVT::currEfemsData(int frame, int ncd){
	unsigned short *buf = new unsigned short[ncd];
	for(int i = 0; i < ncd; i++)
		buf[i] = 0;
	buf[0] = (frame + 2 + 1);
	if(frame < 64){ //GPS
		if(checkToParity(frame)){
			buf[1] = GPSEf[GetLineFromEf(frame)][0];
			buf[1] = buf[1]<<8;
			for(int i = 1, j = 2; i < 60-2; i += 2, j++){
				buf[j] = GPSEf[GetLineFromEf(frame)][i + 1];
				buf[j] = (buf[j]<<8) + GPSEf[GetLineFromEf(frame)][i];
			}
		}
		else
			for(int i = 61-2, j = 1; i < 80; i += 2, j++){
				buf[j] = GPSEf[GetLineFromEf(frame)][i + 1];
				buf[j] = (buf[j]<<8) + GPSEf[GetLineFromEf(frame)][i];
			}
	}
	else{  //GLONASS
		buf[1] = GLOEf[frame - 64][0];
		buf[1] = buf[1]<<8;
		for(int i = 1, j = 2; i < 60; i += 2, j++){
			buf[j] = GLOEf[frame - 64][i + 1];
			buf[j] = (buf[j]<<8) + GLOEf[frame - 64][i];
		}
	}
	return buf;
}
