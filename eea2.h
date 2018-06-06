
#ifndef EEA2_H
#define EEA2_H

struct ctr_state { 
    unsigned char ivec[16];   
    unsigned int num; 
    unsigned char ecount[16]; 
}; 
void init_ctr(struct ctr_state *state, const unsigned char iv[16]);
/**eea1
	@P key key
	@P COUNT 计数器
	@P BEARER
	@P DIRECTION 方向
	@P length    加密字节数
	@P data    加密输入数据
	@P data    加密输出数据
*/

void EEA2( unsigned char *key, unsigned int COUNT, unsigned int BEARER, unsigned int DIRECTION,unsigned char *data,  unsigned int length );


#endif
