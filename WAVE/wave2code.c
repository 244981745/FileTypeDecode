#ifndef	__linux__
#include "wave.c"
#else
#include "wave.h"
#endif
#include <stdio.h>

int main(int argc,char **argv)
{
	FILE *fp;
	struct Riff riff;
	struct Format format;
	struct Fact fact;
	struct Data data;
	unsigned long dataSize=0;
	
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
				getRiff(&riff,fp);	
				getFormat(&format,fp);
				if(format.FormatAttach[0]	!= 0 || format.FormatAttach[1]	!= 0)
				{
					getFact(&fact,fp);		
				}
				dataSize	=	getDataID_Size(&data,fp);
				printf("dataSize:\t%ld\n",dataSize);
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
