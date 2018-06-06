
#include "public.h"
#include  <stdlib.h>  
char a2x(char ch) 
{     
	switch(ch)     
	{     
		case '1':         
			return 1;     
		case '2':         
			return 2;     
		case '3':         
			return 3;     
		case '4':         
			return 4;
		case '5':
			return 5;
		case '6':
			return 6;
		case '7':
			return 7;
		case '8':
			return 8;
		case '9':
			return 9;
		case 'A':
		case 'a':
			return 10;
		case 'B':
		case 'b':
			return 11;
		case 'C':
		case 'c':
			return 12;
		case 'D':
		case 'd':
			return 13;
		case 'E':
		case 'e':
			return 14;
		case 'F':
		case 'f':
			return 15;
		default:
			break;;
	}
	return 0;
}
//对应int64大小的成员 的转换 范例
unsigned long long swapInt64( unsigned long long value)
{
     return ((value & 0x00000000000000FF) << 56) |
               ((value & 0x000000000000FF00) << 48) |
               ((value & 0x0000000000FF0000) << 40) |
               ((value & 0x00000000FF000000) << 32) |
	       ((value & 0x000000FF00000000) >> 32) |
	       ((value & 0x0000FF0000000000) >> 40) |
	       ((value & 0x00FF000000000000) >> 48) |
	       ((value & 0xFF00000000000000) >> 56);
}
//对应int32大小的成员 的转换 范例 
unsigned int swapInt32(unsigned int value)
{
     return ((value & 0x000000FF) << 24) |
               ((value & 0x0000FF00) << 8) |
               ((value & 0x00FF0000) >> 8) |
               ((value & 0xFF000000) >> 24) ;
}
char* Hex2Str(const char* hexstr,unsigned int *len)
{
	
	*len=strlen(hexstr)/2;
	//len=&mlen;
	char* str2=(char *)malloc(*len+1);
	int  i = 0;
	while(hexstr[i])
	{
		str2[i >> 1] = (a2x(hexstr[i]) << 4) | a2x(hexstr[i + 1]);
		i += 2;
	}
	str2[i >> 1] = '\0'; 
	return str2;
}
int hexCharToValue(const char ch){

  int result = 0;

  //获取16进制的高字节位数据
  if(ch >= '0' && ch <= '9'){

    result = (int)(ch - '0');
  }

  else if(ch >= 'a' && ch <= 'z'){

    result = (int)(ch - 'a') + 10;
  }

  else if(ch >= 'A' && ch <= 'Z'){

    result = (int)(ch - 'A') + 10;
  }

  else{

    result = -1;

  }

 return result;

}

#include <stdio.h>
#include <stdlib.h>

unsigned long long StrToHex1(const char *pstr,int len)
{
    unsigned long long ull = 0ULL;
    if (pstr != NULL) {
	int n;
        for(n=0;n<len;n++) {
            char ch = *pstr++;
            if (ch != ' ') {
                if (ch == '0' && (*pstr == 'x' || *pstr == 'X')) {
                    pstr++;
                    while (*pstr != 0) {
                        unsigned char uc = 0;
                        if (*pstr >= '0' && *pstr <= '9') {
                            uc = (unsigned char)(*pstr - '0');
                        } else if (*pstr >= 'a' && *pstr <= 'f') {
                            uc = (unsigned char)(*pstr - 'a' + 10);
                        } else if (*pstr >= 'A' && *pstr <= 'F') {
                            uc = (unsigned char)(*pstr - 'A' + 10);
                        } else {
                            break;
                        }
                        ull <<= 4;
                        ull |= uc;
                        pstr++;
                    }
                }
                break;
            }

        }
    }
    return ull;
}

int HexToStr(unsigned long long ull, char *pstr, size_t size)
{
    int ret = -1;
    if (pstr != NULL && size > 0) {
        char pref[] = { '0', 'x' };
        size_t cch = sizeof(pref);
        unsigned long long _ull = ull;

        while (_ull > 0) {
            _ull >>= 4;
            cch++;
        }

        if (size >= cch) {
            *pstr++ = pref[0];
            *pstr++ = pref[1];

            while (cch-- > sizeof(pref)) {
                pstr++;
            }

            *pstr-- = 0;

            while (ull > 0ULL) {
                unsigned char uc = ull & 0xF;
                *pstr-- = uc + ((uc < 10) ? '0' : ('A' - 10));
                ull >>= 4;
            }

            ret = 0;
        }
    }
    return ret;
}

char valueToHexCh(const int value)

{

  char result = '\0';

  if(value >= 0 && value <= 9){

    result = (char)(value + 48); //48为ascii编码的‘0’字符编码值

  }

  else if(value >= 10 && value <= 15){

    result = (char)(value - 10 + 65); //减去10则找出其在16进制的偏移量，65为ascii的'A'的字符编码值

  }

  else{

    ;

 }



  return result;

}
int strToHex(char *ch,int clen, char*  hexstr)
{
  int high,low;
  int tmp = 0;
  if(clen == 0 ){
    return -1;
  }


  char *hex=(char *)malloc(clen*2+2);
  int v;
  for(v=0;v<clen;v++){

    tmp = (int)*ch;
    high = tmp >> 4;
    low = tmp & 15;
    hex[2*v] = valueToHexCh(high); //先写高字节
    hex[2*v+1] = valueToHexCh(low); //其次写低字节
    ch++;
  }
  hex[2*clen]=0;
  hexstr=hex;
 // delete [] hex;
  return 0;

}

char* CharToHex( char * buffer , int len)
{


 char * dest=(char *)malloc(2*len+10);
 int i=0;
 int j=0;
 unsigned char temp;
 while(i<len)
 {
  temp=buffer[i];
  if((temp>=0x30)&&(temp<=0x39))
  {
   temp=temp-0x30;
   dest[j]=temp<<4;

  }
  else if((temp>=0x41)&&(temp<=0x46))
  {
   temp=temp-0x41+0x0A;
   dest[j]=temp<<4;
  }
  else if((temp>=0x61)&&(temp<=0x66))
  {
   temp=temp-0x61+0x0A;
   dest[j]=temp<<4;
  }
  else
  {
   dest[j]=0x00;
  }
//  dest[j]=dest[j]<<4;
  temp=buffer[i+1];
  if((temp>=0x30)&&(temp<=0x39))
  {
   temp=temp-0x30;
   dest[j]=dest[j]|temp;

  }
  else if((temp>=0x41)&&(temp<=0x46))
  {
   temp=temp-0x41+0x0A;
   dest[j]=dest[j]|temp;
  }
  else if((temp>=0x61)&&(temp<=0x66))
  {
   temp=temp-0x61+0x0A;
   dest[j]=dest[j]|temp;
  }
  else
  {
   dest[j]=dest[j]|0x00;
  }

  i=i+2;
  j=j+1;
 }
dest[2*len]=0;
return dest;

}
 


 



//打印
void printfhexstr(const char* name,const char* buf,int len)
{
	printf("%s=[\n",name);
	int linenum=len/16+(len%16==0?0:1);
	int n;
	for(n=0;n<linenum;n++)
	{
		int i;
		int start=n*16;
		for(i=0;i<16;i++)
		{
			if((start+i)>=len)
			{
				break;
			}
			char keytmp=buf[start+i];
			char key[2]={0};
			sprintf(key,"%c",keytmp);

			printf("%02X ",keytmp&0xff);
		}
		for(i=0;i<16;i++)
		{
			if((start+i)>=len)
			{
				break;
			}
			char key=buf[start+i];
			if(key=='\x00')
			{
				printf(" ");
			}
			else
			{
				printf("%c",key);
			}
		}
		printf("\n");

	}	

	
	printf("]\n");



}