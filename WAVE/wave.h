#ifndef	_WAVE_H
#define	_WAVE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Riff{
	unsigned char RiffID[4];
	unsigned char RiffSize[4];
	unsigned char RiffType[4];
};

struct Format{
	unsigned char FormatID[4];
	unsigned char FormatSize[4];
	unsigned char FormatTag[2];
	unsigned char FormatChannells[2];	//1- mono 2-stereo
	unsigned char FormatSamplesPerSec[4];
	unsigned char FormatAvgBytesPerSec[4];
	unsigned char FormatBolckAlign[2];
	unsigned char FormatBitsPerSample[2];
	unsigned char FormatAttach[2];
};

struct Fact{
	unsigned char FactID[4];
	unsigned char FactSize[4];
	unsigned char FactData[4];
};

struct Data{
	unsigned char DataID[4];
	unsigned char DataSize[4];
	unsigned char *data;
};

int getRiff(struct Riff *riff,FILE *fp);
int getFormat(struct Format *format,FILE *fp);
int getFact(struct Fact *fact,FILE *fp);
int getDataID_Size(struct Data *data,FILE *fp);

#endif
