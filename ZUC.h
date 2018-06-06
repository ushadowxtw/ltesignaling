

#ifndef ZUC_H
#define ZUC_H
#include "public.h"

/**
	@P CK key
	@P COUNT 计数器
	@P BEARER
	@P DIRECTION 方向
	@P LENGTH    加密位数
	@P M    加密输入数据
	@P C    加密输出数据
*/

void EEA3(u8* CK,u32 COUNT,u32 BEARER,u32 DIRECTION,u32 LENGTH,u32* M,u32* C);

void ZUC_EEA3( unsigned char *key, unsigned int COUNT, unsigned int BEARER, unsigned int DIRECTION,unsigned char *data,  unsigned int length );
//void EEA31(u8* CK,u8* IV,u32 COUNT,u32 BEARER,u32 DIRECTION,u32 LENGTH,u32* M,u32* C);

#endif
