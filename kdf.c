#include "kdf.h"

#include "hmac_sha2.h"

int HMAC_Sha5(const char * key, unsigned int key_length,const char * input, unsigned int input_length,unsigned char ** output, unsigned int *output_length)
{

	unsigned char *mac=(unsigned char*)malloc(SHA256_DIGEST_SIZE);

	output_length = SHA256_DIGEST_SIZE;
	hmac_sha256(key, key_length, input,
                    input_length, mac, output_length);
	* output=mac;


	return 0;

}
