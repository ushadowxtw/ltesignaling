/*4G信令的解析*/
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include "public.h"
void testeea1();
void testeea2();
void testeea3();
void decrypttest();
int main(int argc, char *argv[])
{

	//testeea1();	
	//testeea2();
	//testeea3();
 	decrypttest();


	printf("Hello, world!\n");

	return EXIT_SUCCESS;
}
#define EEA1
//
//完整解密测试
void decrypttest()
{
	//type获取说明
	//取自request包：eg:procedureCode: id-downlinkNASTransport (11)->NAS-pDU->NAS security algorithms - Selected NAS security algorithms
	//（0000）2 EEA0 空加密算法
	//（0001）2 128-EEA1 基于SNOW 3G的加密算法
	//（0010）2 128-EEA2 基于AES的加密算法
	//（0011）2 128-EEA3 基于ZUC的加密算法
#ifdef EEA1
	unsigned int type=1;//加密方式（NAS SQN＝０时才可以取得）
#else
	unsigned int type=2;//加密方式（NAS SQN＝０时才可以取得）
#endif
	//计数 COUNT=0X00(高8位)|| NAS　COUNT　 
	//获取NAS　COUNT　＝　0X00(高8位)|| NAS OVERFOLW || NAS SQN
	//NAS SQN的获取　eg:procedureCode: id-downlinkNASTransport (11)->NAS-pDU->－>Sequence number: 0
	//NAS OVERFOLW ＝　当NAS SQN溢出时NAS OVERFOLW+1
	unsigned int NASSQN=0;
	//unsigned int COUNT=0;//此处特殊处理
	unsigned int COUNT=2;//此处特殊处理
	//kasme获取
	//S6
	//3GPP-Authentication-Information Answer-> Authentication-Info: -> AVP: KASME(1450)
	unsigned int kasmelen=0;
	//unsigned char* kasme=Hex2Str("8c608a41cf509714e4908c4ef3b988d1f4a4cec033d98a5302cb881591891d57",&kasmelen);;

#ifdef EEA1
	unsigned char* kasme=Hex2Str("8c608a41cf509714e4908c4ef3b988d1f4a4cec033d98a5302cb881591891d57",&kasmelen);
	printfhexstr("kasme",kasme,kasmelen);
#else
	unsigned char* kasme=Hex2Str("4b95613e7202f8fcd5dd0e5c837aaa12dadaf87a40f24984b2ce57a185c42e27",&kasmelen);
	printfhexstr("kasme",kasme,kasmelen);
#endif
	//计算KNASenc 
	//printfhexstr("kasme",kasme,32);
	unsigned char* KNAsenctmp=Operation_KNAsenc(kasme,type);
	printfhexstr("KNAsenctmp",KNAsenctmp,32);
	free(kasme);
	//KNAsenctmp为256位　取低128位
	unsigned char KNAsenc[16];
	memcpy(KNAsenc,KNAsenctmp+16,16);
	printfhexstr("KNAsenc",KNAsenc,16);
	free(KNAsenctmp);
	/**eea
		@P key key KNAsenc
		@P COUNT 计数器,32位  低24位为计数器(上下行各自计数)
		@P BEARER		NAS为0
		@P DIRECTION 方向 0上行 1下行
		@P length    加密字节数
		@P data    加密输入数据
		@P data    加密输出数据
		@P type    加密方式 0-未加密 1-eea1 2-eea2 3-eea3 
	*/
	unsigned int datalen=0;
#ifdef EEA1
	//u8 *data=Hex2Str("e9904fe29d9cf5406cc51157b2",&datalen);
	u8 *data=Hex2Str("b35d7e30b13c8ae784f8f6a4b8cc1c175c338c10e0f16e53b57b66962786cf7a7f5e9aad81866561e1dfec665f4b8ac0bf2c048265ad6da6f01e76c9c0f39e12a3f14de2ddd80a77f3a9827c5b7161497b6e22da9f2511522f7b9bb4db2017",&datalen);

#else
	//u8 *data=Hex2Str("c5a04a918ad7fd2f1237c64f1f",&datalen);
	u8 *data=Hex2Str("cfba3ae31b4eda2a9622c619fa414423bd86ea466ec9d6cd8f446189d435f4bfc465ab8726becc6905ef2b13b6b2148c765f89c6ebf2931b1fb3a529c40116aef482897fa6c27bcf2f883de42e203cc674a808e7dbbb93f5e6936713c192a5b8c643a4cb4f7208f1a0c58eab3dd82ffccdcfc01c76a48bc3f185fa305b2fa29fd7b349aa02e51e9a83bb1217beffdffb58d8a264df09710cd6fbdc43bf000d25876c8bb3bece",&datalen);

#endif
	unsigned int bearer=0;
	//unsigned int dir=0;
	unsigned int dir=1;
	int ret=deeeaapi(KNAsenc,COUNT,bearer,dir,data,datalen,type);
	//长度 datalen
	
	printfhexstr("data",data,datalen);
	
	free(data);
	
}

#include "SNOW_3G.h"
void testeea1()
{	
/*TS33.401*/
	unsigned int len=0;
	char* key=Hex2Str("2bd6459f82c440e0952c49104805ff48",&len);
	u32 count=0xc675a64b;
	u32 bearer=0x0c;
	u32 dir=1;
	unsigned int datalen=0;
	u8 *data=Hex2Str("3F67850714B8DA69EFB727ED7A6C0C50714AD736C4F5600006E3525BE807C467C677FF864AF45FBA09C27CDE38F87A1F84D59AB255408F2C7B82F9EAD41A1FE65EABEBFBC1F3A4C56C9A26FCF7B3D66D0220EE4775BC58170A2B12F3431D11B344D6E36C",&datalen);

	u32 length=798;
	//u8[4];
	f8( key,count, bearer,dir, data,  length );
	
	printfhexstr("data",data,strlen(data));



	free(key);
	sleep(100);
}

#include "eea2.h"
#include "aes.h"
void testeea2()
{
/*TS33.401*/
 	unsigned int len=0;
	unsigned int cypherlen;
    	char * cypher = Hex2Str("5961605353c64bdca15b195e288553a910632506d6200aa790c4c806c99904cf2445cc50bb1cf168a49673734e081b57e324ce5259c0e78d4cd97b870976503c0943f2cb5ae8f052c7b7d392239587b8956086bcab18836042e2e6ce42432a17105c53d0",&cypherlen);
    	char * key = Hex2Str("2bd6459f82c440e0952c49104805ff48",&len);
	u8 	IV0[8];
	u32 COUNT=0xc675a64b;
	u32 BEARER=0x0c;
	u32 DIRECTION=1;

	IV0[0]	= (COUNT>>24) & 0xFF;
	IV0[1]	= (COUNT>>16) & 0xFF;
	IV0[2]	= (COUNT>>8)  & 0xFF;
	IV0[3]	=  COUNT      & 0xFF;
	
	IV0[4]	= ((BEARER << 3) | ((DIRECTION&1)<<2)) & 0xFC;
	IV0[5]	= 0;
	IV0[6]	= 0;
	IV0[7]	= 0;
	
	char* str2=(char *)malloc(cypherlen+1);

	u64 IV1=0;
	unsigned int pos=0;
	unsigned int lvpos=cypherlen;
	
	while(lvpos>0)
	{
		u8 IV[16];
		memcpy(IV,IV0,8);
		u64 IV1_2=swapInt64(IV1);
		memcpy(IV+8,&IV1_2,8);
		
		unsigned char out[16]; //more than needed
// 		AES_KEY aes_key;
// 		//int msg_len = 16;
// 		struct ctr_state status; 
		
// 		if (AES_set_encrypt_key(key,128, &aes_key)!=0){
// 			printf("key error"); 
// 			break;
// 		}
// 		init_ctr(&status, IV);
// 		printfhexstr("status.ivec",status.ivec,16);

		mbedtls_aes_context ctx;
		mbedtls_aes_init( &ctx );


		unsigned char nonce_counter[16];
		unsigned char stream_block[16];
 		mbedtls_aes_setkey_enc( &ctx, key, 128 );

		memcpy( nonce_counter, IV, 16 );
		
		size_t offset = 0;
printfhexstr("nonce_counter",nonce_counter,16);
		//
		if(lvpos>=16)
		{
		
// 			AES_ctr128_encrypt(cypher+pos, out, 16, &aes_key, status.ivec, status.ecount, &status.num);
			mbedtls_aes_crypt_ctr( &ctx, 16, &offset, nonce_counter, stream_block,
                        cypher+pos, out );
			memcpy(str2+pos,out,16);
			lvpos-=16;
			pos+=16;
		}
		else
		{
// 			AES_ctr128_encrypt(cypher+pos, out, lvpos, &aes_key, status.ivec, status.ecount, &status.num);
			mbedtls_aes_crypt_ctr( &ctx, lvpos, &offset, nonce_counter, stream_block,
                           cypher+pos, out );
			memcpy(str2+pos,out,lvpos);
			pos+=lvpos;
			lvpos=0;
		}

		IV1++;
	}
	str2[pos]=0;
	printfhexstr("out",str2,pos);
	free(str2);
	sleep(100);
}
#include "ZUC.h"

void testeea3()
{
//ZUC

	unsigned int len=0;
	char* key=Hex2Str("173d14ba5003731d7a60049470f00a29",&len);
	//char* key=Hex2Str("3d4c4be96a82fdaeb58f641db17b455b",&len);
	//char* IV=Hex2Str("84319aa8de6915ca1f6bda6bfbd8c766",&len);
	u32 count=0x66035492;
	u32 bearer=0x0f;
	u32 dir=0;
	unsigned int datalen=0;
	u8 *data=Hex2Str("6cf65340735552ab0c9752fa6f9025fe0bd675d9005875b200000000",&datalen);
//(hex) a6c85fc6 6afb8533 aafc2518 dfe78494 0ee1e4b0 30238cc8 00000000
	u32 length=193;
	u32* M=(u32 *)malloc(datalen+1);
	
	int num=datalen/4;
	int cnum=datalen%4;
	int n=0;
	for(n=0;n<num;n++)
	{
		memcpy(&M[n],data+n*4,4);
		
	}
	if(cnum!=0)
	{
		memcpy(&M[n],data+n*4,cnum);
	}

	
	u32* C=(unsigned int *)malloc(datalen+1);
	
	EEA3(key,count,bearer,dir,length, M,C);
	//EEA31(key,IV,count,bearer,dir,length, M,C);
	const char* out=(char *)malloc(datalen+1);
	
	memcpy(out,C,datalen);
	
	printfhexstr("out",out,datalen);
	free(M);
	free(C);
	free(out);
	
	
	

}


