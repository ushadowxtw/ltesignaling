
#include "eea2.h"
// #include <openssl/aes.h>
#include "public.h"
#include <stdlib.h>
#include "aes.h"
void init_ctr(struct ctr_state *state, const unsigned char iv[16]){
    state->num = 0; 
    memset(state->ecount, 0, 16); 
    memcpy(state->ivec, iv, 16);
} 
// void EEA2_1( unsigned char *key, unsigned int COUNT, unsigned int BEARER, unsigned int DIRECTION,unsigned char *data,  unsigned int length )
// {
// 	printfhexstr("src data1",data,strlen(data));
// 	unsigned int len=0;
// 
// 	unsigned char 	IV0[8];
// 
// 	IV0[0]	= (COUNT>>24) & 0xFF;
// 	IV0[1]	= (COUNT>>16) & 0xFF;
// 	IV0[2]	= (COUNT>>8)  & 0xFF;
// 	IV0[3]	=  COUNT      & 0xFF;
// 	
// 	IV0[4]	= ((BEARER << 3) | ((DIRECTION&1)<<2)) & 0xFC;
// 	IV0[5]	= 0;
// 	IV0[6]	= 0;
// 	IV0[7]	= 0;
// 	
// 	char* str2=(char *)malloc(length+1);
// 
// 	unsigned long long IV1=0;
// 	unsigned int pos=0;
// 	unsigned int lvpos=length;
// 	
// 	while(lvpos>0)
// 	{
// 		unsigned char IV[16];
// 		memcpy(IV,IV0,8);
// 		IV1=swapInt64(IV1);
// 		memcpy(IV+8,&IV1,8);
// 		
// 		unsigned char out[16]; //more than needed
// 		AES_KEY aes_key;
// 
// 		struct ctr_state status; 
// 		
// 		if (AES_set_encrypt_key(key,128, &aes_key)!=0){
// 			printf("key error"); 
// 			break;
// 		}
// 		init_ctr(&status, IV);
// 		printfhexstr("status.ivec",status.ivec,16);
// 		//
// 		if(lvpos>=16)
// 		{
// 		
// 			AES_ctr128_encrypt(data+pos, out, 16, &aes_key, status.ivec, status.ecount, &status.num);
// 
// 			memcpy(str2+pos,out,16);
// 			lvpos-=16;
// 			pos+=16;
// 		}
// 		else
// 		{
// 			AES_ctr128_encrypt(data+pos, out, lvpos, &aes_key, status.ivec, status.ecount, &status.num);
// 
// 			memcpy(str2+pos,out,lvpos);
// 			pos+=lvpos;
// 			lvpos=0;
// 			
// 		}
// 
// 		IV1++;
// 	}
// 	str2[pos]=0;
// 	printfhexstr("out",str2,pos);
// 	memcpy(data,str2,pos);
// 
// 	free(str2);
// }
void EEA2( unsigned char *key, unsigned int COUNT, unsigned int BEARER, unsigned int DIRECTION,unsigned char *data,  unsigned int length )
{
	printfhexstr("src data1",data,strlen(data));
	unsigned int len=0;

	unsigned char 	IV0[8];

	IV0[0]	= (COUNT>>24) & 0xFF;
	IV0[1]	= (COUNT>>16) & 0xFF;
	IV0[2]	= (COUNT>>8)  & 0xFF;
	IV0[3]	=  COUNT      & 0xFF;
	
	IV0[4]	= ((BEARER << 3) | ((DIRECTION&1)<<2)) & 0xFC;
	IV0[5]	= 0;
	IV0[6]	= 0;
	IV0[7]	= 0;
	
	char* str2=(char *)malloc(length+1);

	unsigned long long IV1=0;
	unsigned int pos=0;
	unsigned int lvpos=length;
	
	while(lvpos>0)
	{
		unsigned char IV[16];
		memcpy(IV,IV0,8);
		u64 IV1_2=swapInt64(IV1);
		memcpy(IV+8,&IV1_2,8);
		
		unsigned char out[16]; //more than needed

		mbedtls_aes_context ctx;
		mbedtls_aes_init( &ctx );


		unsigned char nonce_counter[16];
		unsigned char stream_block[16];
 		mbedtls_aes_setkey_enc( &ctx, key, 128 );

		memcpy( nonce_counter, IV, 16 );

		size_t offset = 0;
		if(lvpos>=16)
		{
			mbedtls_aes_crypt_ctr( &ctx, 16, &offset, nonce_counter, stream_block,
                        data+pos, out );

			memcpy(str2+pos,out,16);
			lvpos-=16;
			pos+=16;
		}
		else
		{
			mbedtls_aes_crypt_ctr( &ctx, lvpos, &offset, nonce_counter, stream_block,
                           data+pos, out );
			memcpy(str2+pos,out,lvpos);
			pos+=lvpos;
			lvpos=0;
			
		}

		IV1++;
	}
	str2[pos]=0;
	printfhexstr("out",str2,pos);
	memcpy(data,str2,pos);

	free(str2);
}
