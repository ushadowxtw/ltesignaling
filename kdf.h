#ifndef KDF_H
#define KDF_H

int HmacEncode(const char * algo,
const char * key, unsigned int key_length,
const char * input, unsigned int input_length,
unsigned char ** output, unsigned int *output_length);

int HMAC_Sha5(const char * key, unsigned int key_length,const char * input, unsigned int input_length,unsigned char ** output, unsigned int *output_length);

#endif