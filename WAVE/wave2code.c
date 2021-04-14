/*****************************************************************************
Copyright: 2021, xuanmoo.com
File name: wave2code.c 
Description: 
		转码实现 
Author: dsinjok
Version: 1.0.0.0
Date: 2021-4-14
History: 
*****************************************************************************/

#ifndef	__linux__
#include "wave.c"
#else
#include "wave.h"
#endif
#include <stdio.h>

int wave2code(struct BitStream *bs);

int main(int argc,char **argv)
{
	struct BitStream	bs;
	FILE *fp;
	struct Riff		riff;
	struct Format	format;
	struct Fact		fact;
	struct Data		data;
	
	if(argc < 3)
	{
		printf("usage:\n\twave2code -[momo/stereo] [wavefilename]\n");
		return -1;
	}
	else
	{
		if(!strcmp("-mono",argv[1]) | !strcmp("-stereo",argv[1]))
		{
			fp	=	fopen(argv[2],"rb");
			if(NULL == fp)
			{
				printf("file open error.\n");
				return -1;
			}
			else
			{
				bs.fp	=	fp;
				getRiff(&riff,fp);
				getFormat(&format,fp);
				bs.channel	=	(format.FormatChannells[1]<<8)|(format.FormatChannells[0]);
				bs.sample	=	((format.FormatSamplesPerSec[3]&0xff)<<24)|\
								((format.FormatSamplesPerSec[2]&0xff)<<16)|\
								((format.FormatSamplesPerSec[1]&0xff)<<8)|\
								(format.FormatSamplesPerSec[0]&0xff);
				bs.bitFmt	=	(int)((format.FormatBitsPerSample[1]<<8)|format.FormatBitsPerSample[0]);
				
				if(format.FormatAttach[0]	!= 0 || format.FormatAttach[1]	!= 0)
				{
					getFact(&fact,fp);		
				}
				
				bs.dataSize	=	getDataID_Size(&data,fp);
				if(!strcmp("-mono",argv[1]))	bs.outputchs	=	1;
				if(!strcmp("-stereo",argv[1]))	bs.outputchs	=	2;
				wave2code(&bs);
			}
		}
		else
		{
			printf("\tParameters:%s not supported\n",argv[1]);
			return -1;
		}
	}
	
	
	fclose(fp);
	return 0;
}

/* 
*	wave2code 转码实现 
*/
int wave2code(struct BitStream *bs)
{
	FILE *fout;
	unsigned long	tmp,i;
	signed short	value,ret,j;
	unsigned char	buff[32];
	
	fout	=	fopen("pcm.h","wb");
	if(NULL == fout)
	{
		printf("output file open error.\n");
		return -1;
	}
	fprintf(fout,"const unsigned char pcm[]={\n");
	
	if(bs->channel	==	2)
	{
		if(bs->bitFmt	==	16)
		{
			for(i = 0; i < bs->dataSize; i+=32)
			{
				ret = fread((void*)buff,1,32,bs->fp);
				for(j = 0; j < 32; j+=4)
				{
					if(bs->outputchs	==	1)
					{
						fprintf(fout,"0x%.2x,0x%.2x,",buff[j+1],buff[j]);
					}
					else if(bs->outputchs	==	2)
					{
						fprintf(fout,"0x%.2x,0x%.2x,0x%.2x,0x%.2x",buff[j+1],buff[j],buff[j+3],buff[j+2]);
					}
					else
					{
						printf("output channels error.\n");
						exit(1);
					}
				}
				fprintf(fout,"\n");
			}
		}
	}
	else if(bs->channel	==	1)
	{
		if(bs->bitFmt	==	16)
		{
			for(i = 0; i < bs->dataSize; i+=32)
			{
				ret = fread((void*)buff,1,32,bs->fp);
				for(j = 0; j < 32; j+=4)
				{
					if(bs->outputchs	==	1)
					{
						fprintf(fout,"0x%.2x,0x%.2x,",buff[j+1],buff[j]);
					}
					else if(bs->outputchs	==	2)
					{
						fprintf(fout,"0x%.2x,0x%.2x,0x%.2x,0x%.2x",buff[j+1],buff[j],buff[j+1],buff[j]);
					}
					else
					{
						printf("output channels error.\n");
						exit(1);
					}
				}
				fprintf(fout,"\n");
			}
		}
	}
	else
	{
		printf("bs->channel value error.\n");
		return -1;
	}
	
	fprintf(fout,"\n};\n");
	
	fclose(fout);
	return 0;
}

