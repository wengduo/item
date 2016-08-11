/*************************************************************************
	> File Name: md5.cpp
	> Author:Jone 
	> Mail:mjf2019@126.com 
	> Created Time: 2016年07月05日 星期二 20时30分34秒
 ************************************************************************/
#ifndef MD5_HPP
#define MD5_HPP

#include <openssl/md5.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

void my_md5(const char *filename,char *md5_buff)
{
	MD5_CTX ctx;
	unsigned char outmd[16] = {0};
	char buffer[1024] = {0};
	int len=0;
	FILE *fp=fopen(filename,"rb");
	assert(NULL != fp);

	MD5_Init(&ctx);
	while((len=fread(buffer,1,1024,fp))>0)
	{
		MD5_Update(&ctx,buffer,len);
		memset(buffer,0,sizeof(buffer));
	}
	MD5_Final(outmd,&ctx);


	for(int i=0;i<16;i++)
	{
		sprintf(md5_buff+strlen(md5_buff),"%02X",outmd[i]);
	}
	fclose(fp);
}

#endif
