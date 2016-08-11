/*************************************************************************
    > File Name: new.cpp
    > Author: wengduo
    > Mail: 2292466904@qq.com
    > Created Time: 2016年07月16日 星期六 13时23分51秒
 *
 * ***********************************************************************/

#include <iostream>
#include <cstdio>
#include <cassert>


bool insert_file_first(char* result_buff, char* table_name, char* path, char* name, char* md5)
{
	char sql[128] = {0};
	sprintf(sql,"select * from %s where virtual_path = '%s%s'",table_name, path, name);
	if(QueryData(sql))//查找用户表是否有重名文件
	{
		result = mysql_store_result(mysql);
		row = mysql_fetch_row(result);
		if( row == NULL)//没有重名文件
		{
			mysqlFreeResult();
			memset(sql,0,128);
			sprintf(sql,"select * from files where md5 = '%s'",md5);
			if(QueryData(sql))//在md5表中找是否有重名md5码
			{
				result = mysql_store_result(mysql);
				row = mysql_fetch_row(result);
				if(row == NULL)//md5表没有 result=0 return 1;
				{
					sprintf(result_buff,"0%s%d%s",file_path,file_name,name);
					++file_name;
					mysqlFreeResult();
					return true;
				}
				else          //md5表中有  秒传;
				{
					result_buff[0] = '1';
					memset(sql,0,128);
					sprintf(sql,"insert into %s values('%s%s','%s')",table_name,path,name,row[1]);
					mysqlFreeResult();
					if(QueryData(sql))
					{
						return true;
					}
					else
					{
						perror("insert file error \n");
						return false;
					}
				}
			}
			else
			{
				perror("ming ling error\n");
				return false;
			}
 	  }
		else//用户表中有重名文件
		{
			perror("%s have same name files ,error\n",table_name);
			return false;
		}
	}
	else
	{
		perror("insert file error \n");
		return false;
	}
}

bool insert_file(char* result_buff, char* table_name, char* path,char* name, char* md5)
{
	char sql[128] = {0};
	sprintf(sql,"select * from %s where virtual_path = '%s'",table_name,path);
	if(QueryData(sql))//找用户表中这个路径为不为空
	{
		result = mysql_store_result(mysql);
		row = mysql_fetch_row(result);
		if( row == NULL )// 不空
		{
			mysqlFreeResult();
			memset(sql,0,128);
			sprintf(sql,"insert into files values('%s','%s')",md5,result_buff);
			if(QueryData(sql))//向md5表中插入数据
			{
				memset(sql,0,128);
				sprintf(sql,"insert into %s values('%s%s','%s')",table_name,path,name,result_buff);
				if(QueryData(sql))
				{
					return true;
				}
				else
				{
					perror("insert table real_path error\n");
					return false;
				}
			}
			else // md5表中有这个数据，那么查询真实路径
			{
				memset(sql,0,128);
				sprintf(sql,"select real_path from files where md5 = '%s'",md5);
				if(QueryData(sql))
				{
					result = mysql_store_result(mysql);
					row = mysql_fetch_row(result);
					if(row != NULL )
					{
						memset(sql,0,128);
						sprintf(sql,"insert into %s values('%s%s','%s')",table_name,path,name,row[0]);
						mysqlFreeResult();
						if(QueryData(sql))
						{
							return true;
						}
						else
						{
							perror("insert file error\n");
							return false;
						}
					}// 不存在else
					else
					{
						mysqlFreeResult();
						printf("row == NULL\n");
						return false;
					}
				}
				else
				{
					perror("select real_path error\n");
				}
			}
		}
		else // 空
		{
			mysqlFreeResult();
			char new_path[128] = {0};
			sprintf(new_path,"%s%s",path,name);
			ReName(table_name,path,new_path);// 修改用户表
			memset(sql,0,128);
			sprintf(sql,"insert into files values('%s','%s')",md5,result_buff);
			if(QueryData(sql))//向md5表中插入数据
			{
				memset(sql,0,128);
				sprintf(sql,"insert real_path into %s values('%s')",table_name,result_buff);
				if(QueryData(sql))
				{
					return true;
				}
				else
				{
					perror("insert table real_path error\n");
					return false;
				}
			}
			else
			{
				memset(sql,0,128);
				sprintf(sql,"select real_path from files where md5 = '%s'",md5);
				if(QueryData(sql))
				{
					result = mysql_store_result(mysql);
					row = mysql_fetch_row(result);
					if(row != NULL)
					{
						memset(sql,0,128);
						sprintf(sql,"insert real_path into %s values('%s')",table_name,row[0]);
					}
					mysqlFreeResult();
				}
				else
				{
					perror("insert file error\n");
					return false;
				}
			}
		}
	}
	else
	{
		perror("insert files error\n");
		return false;
	}

}

bool insert_file(char* result_buff, char* table_name, char* path, char* name, char* md5, bool tag)
{
	if(!tag)
	{//查找
	  return insert_file_first(result_buff,table_name,path,name,md5);
	}
	else
	{//插入
		return insert_file_second(result_buff,table_name,path,name,md5);
	}
}
