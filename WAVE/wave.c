#include "wave.h"
#define	INFO

int getRiff(struct Riff *riff,FILE *fp)
{
	memset((void *)riff,'\0',sizeof(struct Riff));
	fread((void*)riff,1,12,fp);
	
#ifdef	INFO
	printf("------------------------ RIFF ------------------------\n");
	printf("Riff ID:\t\t%.4s\n",	riff->RiffID);
	printf("Riff Size:\t\t%d\n",((riff->RiffSize[3]&0xff)<<24)|\
							((riff->RiffSize[2]&0xff)<<16)|\
							((riff->RiffSize[1]&0xff)<<8)|\
							(riff->RiffSize[0]&0xff));
	printf("Riff Type:\t\t%.4s\n",riff->RiffType);
	printf("------------------------------------------------------\n\n");
#endif
	
	return 0;
}

int getFormat(struct Format *format,FILE *fp)
{
	int formatsize=0;
	memset((void *)format,'\0',sizeof(struct Format));
	fread((void*)format,1,24,fp);
	formatsize	=	((format->FormatSize[3]&0xff)<<24)|\
					((format->FormatSize[2]&0xff)<<16)|\
					((format->FormatSize[1]&0xff)<<8)|\
					(format->FormatSize[0]&0xff);
	if(18 == formatsize)
		fread((void*)format->FormatAttach,1,2,fp);

#ifdef	INFO
	printf("----------------------- Format -----------------------\n");
	printf("Format ID:\t\t%.4s\n",format->FormatID);
	printf("Format Size:\t\t%d\n",((format->FormatSize[3]&0xff)<<24)|\
							((format->FormatSize[2]&0xff)<<16)|\
							((format->FormatSize[1]&0xff)<<8)|\
							(format->FormatSize[0]&0xff));
	printf("Format Tag:\t\t0x%.2x\n",format->FormatTag[1]<<8|format->FormatTag[0]);
	printf("Format Channels:\t%d\n",format->FormatChannells[1]<<8|\
									format->FormatChannells[0]);
	printf("Format Samples:\t\t%d\n",((format->FormatSamplesPerSec[3]&0xff)<<24)|\
							((format->FormatSamplesPerSec[2]&0xff)<<16)|\
							((format->FormatSamplesPerSec[1]&0xff)<<8)|\
							(format->FormatSamplesPerSec[0]&0xff));
	printf("Format AvgByte:\t\t%d\n",((format->FormatAvgBytesPerSec[3]&0xff)<<24)|\
							((format->FormatAvgBytesPerSec[2]&0xff)<<16)|\
							((format->FormatAvgBytesPerSec[1]&0xff)<<8)|\
							(format->FormatAvgBytesPerSec[0]&0xff));
	printf("Format BlockAlign:\t%d\n",format->FormatBolckAlign[1]<<8|\
									format->FormatBolckAlign[0]);
	printf("Format BitsPSample:\t%d\n",format->FormatBitsPerSample[1]<<8|\
									format->FormatBitsPerSample[0]);
	if(18 == formatsize)
		printf("Format Attach:\t\t%.2s\n",format->FormatAttach);
	printf("------------------------------------------------------\n\n");
#endif

	return 0;
}

int getFact(struct Fact *fact,FILE *fp)
{
	memset((void*)fact,'\0',sizeof(struct Fact));
	fread((void *)fact,1,12,fp);
	
#ifdef	INFO
	printf("------------------------ Fact ------------------------\n");
	printf("Fact ID:\t\t%.4s\n",fact->FactID);
	printf("Fact Size:\t\t%d\n",((fact->FactSize[3]&0xff)<<24)|\
							((fact->FactSize[2]&0xff)<<16)|\
							((fact->FactSize[1]&0xff)<<8)|\
							(fact->FactSize[0]&0xff));
	printf("Fact Data:\t\t%.4s\n",fact->FactData);
	printf("Fact Data:\t\t%.2x %.2x %.2x %.2x\n",fact->FactData[0],\
					fact->FactData[1],fact->FactData[2],fact->FactData[3]);
	printf("------------------------------------------------------\n\n");
#endif
	
	return 0;
}

int getDataID_Size(struct Data *data,FILE *fp)
{
	memset((void*)data,'\0',sizeof(struct Data));
	fread((void *)data,1,8,fp);
	
#ifdef	INFO
	printf("------------------------ Data ------------------------\n");
	printf("Data ID:\t\t%.4s\n",data->DataID);
	printf("Data Size:\t\t%d\n",((data->DataSize[3]&0xff)<<24)|\
							((data->DataSize[2]&0xff)<<16)|\
							((data->DataSize[1]&0xff)<<8)|\
							(data->DataSize[0]&0xff));
	printf("------------------------------------------------------\n\n");
#endif
	
	return (((data->DataSize[3]&0xff)<<24)|\
							((data->DataSize[2]&0xff)<<16)|\
							((data->DataSize[1]&0xff)<<8)|\
							(data->DataSize[0]&0xff));
}


