
#include "eeaapi.h"
#include "SNOW_3G.h"
#include "eea2.h"
#include "ZUC.h"
#include "kdf.h"
/**eea1
	@P key key
	@P COUNT 计数器
	@P BEARER
	@P DIRECTION 方向
	@P length    加密字节数
	@P data    加密输入数据
	@P data    加密输出数据
	@P type    加密方式 0-未加密 1-eea1 2-eea2 3-eea3 
*/

int deeeaapi(unsigned char *key,unsigned int count,unsigned int bearer, unsigned int dir,unsigned char *data, unsigned int length,unsigned int type)
{
	if(type==0)
	{
		return 0;
	}
	if(type==1)
	{
		unsigned int clength=length*8;
		//u8[4];
		f8( key,count, bearer,dir, data,  clength );
		
	}
	else if(type==2)
	{
		printfhexstr("src data",data,strlen(data));
		EEA2(key,count,bearer, dir,data,length);

	}
	else if(type==3)
	{
		ZUC_EEA3(key,count,bearer, dir,data,length);
	}
	else
	{
		return -1;
	}
	return 0;

}
/**Operation_KNAsenc
	@P kasme kasme
	@P type    加密方式 0-未加密 1-eea1 2-eea2 3-eea3 
	@  ret    KNAsenc
*/

unsigned char* Operation_KNAsenc(unsigned char* kasme,unsigned int type)
{
	char SNA[7];
	SNA[0]='\x15';
	SNA[1]='\x01';
	SNA[2]='\x00';
	SNA[3]='\x01';
	if(type==1)
	{
		SNA[4]='\x01';
	}
	else if(type==2)
	{
		SNA[4]='\x02';
	}
	else if(type==3)
	{
		SNA[4]='\x03';
	}
	SNA[5]='\x00';
	SNA[6]='\x01';

	
	
	unsigned char * output;
	unsigned int output_length;
// 		printfhexstr("SNA",SNA,7);
// 	HmacEncode("sha256",kasme, 32,SNA,7,&output,&output_length);
	//HmacEncode("sha256",SNA, 7,kasme,32,&output,&output_length);
// 	printfhexstr("sha256 output",output,32);

// 	unsigned char * output1;
// 	unsigned int output_length1;
	HMAC_Sha5(kasme,32,SNA,7,&output, &output_length);
	printfhexstr("sha256 output1",output,32);
	return output;
	
}
// unsigned char* Operation_KNAsenc(unsigned char* kasme,unsigned int type)
// {
// 	char SNA[7];
// 	SNA[6]='\x15';
// 	SNA[5]='\x01';
// 	SNA[4]='\x00';
// 	SNA[3]='\x01';
// 	if(type==1)
// 	{
// 		SNA[2]='\x01';
// 	}
// 	else if(type==2)
// 	{
// 		SNA[2]='\x02';
// 	}
// 	else if(type==3)
// 	{
// 		SNA[2]='\x03';
// 	}
// 	SNA[1]='\x00';
// 	SNA[0]='\x01';
// 
// 	
// 	
// 	unsigned char * output;
// 	unsigned int output_length;
// 		printfhexstr("SNA",SNA,7);
// 	HmacEncode("sha256",kasme, 32,SNA,7,&output,&output_length);
// 
// 	return output;
// 	
// }
