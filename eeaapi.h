
#ifndef EEAAPI_H
#define EEAAPI_H

/**eea1
	@P key key KNAsenc
	@P COUNT 计数器,32位  低24位为计数器(上下行各自计数)
	@P BEARER		NAS为0
	@P DIRECTION 方向 0上行 1下行
	@P length    加密字节数
	@P data    加密输入数据
	@P data    加密输出数据
	@P type    加密方式 0-未加密 1-eea1 2-eea2 3-eea3 
*/

int deeeaapi(unsigned char *key,unsigned int count,unsigned int bearer, unsigned int dir,unsigned char *data, unsigned int length,unsigned int type);

/**Operation_KNAsenc
	@P kasme kasme
	@P type    加密方式 0-未加密 1-eea1 2-eea2 3-eea3 
	@  ret    KNAsenc
*/

unsigned char* Operation_KNAsenc(unsigned char* kasme,unsigned int type);
#endif