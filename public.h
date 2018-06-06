#ifndef PUBLIC_H
#define PUBLIC_H

typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned long long u64;
char* Hex2Str(const char* hexstr,unsigned int* len);
int strToHex(char *ch,int clen, char* hexstr);
void printfhexstr(const char* name,const char* buf,int len);
unsigned long long swapInt64( unsigned long long value);
unsigned int swapInt32(unsigned int value);
#endif
