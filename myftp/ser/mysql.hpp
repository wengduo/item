#ifndef _mysql_hpp_
#define _mysql_hpp_




#include <mysql/mysql.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <vector>
#include <string.h>
using namespace std;

int mysql_file_name = 1;
char mysql_file_path[128] = "/home/wengduo/lianxi/myftp/ser/";

class Mysql
{
	public:

		Mysql(string host="localhost",int port=3306,string name="root",string passwd="wd123456",string db="cloud_file")
		{
			mysql =new MYSQL;
			result = NULL;
			mysql_init(mysql);
			if(!mysql_real_connect(mysql,host.c_str(),name.c_str(),passwd.c_str(),db.c_str(),port,NULL,0))
			{
				cout<<"ral_connect fail"<<mysql_error(mysql)<<endl;
			}
			else
			{
				cout<<"connect with server succeed"<<endl;
			}

		}

		bool QueryData(string str)
		{
			bool tag=true;
			//cout<<str<<endl;
			if(mysql_real_query(mysql,str.c_str(),str.size()))
			{
				tag=false;
				printf("cai zuo error\n");
				//cout<<"query fail:"<<mysql_error(mysql)<<endl;
			}
			return tag;
		}

		bool LoginQuery(char *name, char* passwd)
		{
			char sql[128] = {0};
			sprintf(sql, "select * from user_passwd where name = '%s'", name);
			if(!mysql_real_query(mysql, sql, strlen(sql)))
			{
				cout << "aaaaaaa" << endl;

				result = mysql_store_result(mysql);
				if(result == NULL)
				{
					cout << "get result error" << endl;
					return false;
				}
				else
				{
					row=mysql_fetch_row(result);
					printf("%d-%d\n",strlen(passwd),strlen(row[1]));
					printf("passwd:%s-%s\n",row[1],passwd);

					if(strcmp(passwd, row[1]) == 0)
					{
						printf("passwd:%s-%s\n",row[1],passwd);
						mysql_free_result(result);
						return true;
					}

					mysql_free_result(result);
					while(!mysql_next_result(mysql))
					{
						result = mysql_store_result(mysql);
						mysql_free_result(result);
					}


					return false;
				}
			}
		}

		bool mkdir_file(char* table_name,char* path,char* dir_name)
		{
			char sql[128] = {0};
			sprintf(sql,"select * from %s where virtual_path = '%s'",table_name, path);
			if(QueryData(sql))
			{
				result = mysql_store_result(mysql);
				row = mysql_fetch_row(result);
				if( row == NULL )//不是空文件夹
				{
					mysqlFreeResult(); 
					memset(sql,0,128);
					sprintf(sql,"insert into %s values('%s%s/',NULL)",table_name,path,dir_name);
					if(QueryData(sql))
					{
						return true;
					}
					else
					{
						perror("insert dir error\n");
						return false;
					}
				}
				else // 是个空文件夹
				{

					mysqlFreeResult(); 
					memset(sql,0,128);
					sprintf(sql,"%s%s/",path,dir_name);
					return ReName(table_name,path,sql);
				}
			}
			else
			{
				perror("cao zuo  error\n");
				return false;
			}
		}



		void DealResult(char *result_buff,char *table_name,char *path)
		{
			int num=0;
			bool tag=true;
			char sql[128] = {0};
			string vec1;
			string vec;
			sprintf(sql, "select * from %s", table_name);
			if(QueryData(sql))
			{
				result=mysql_store_result(mysql);
				if(NULL==result)
				{
					int n=mysql_affected_rows(mysql);
					if(n>0)
					{
						cout<<" there are "<<n<<" row influenced"<<endl;
					}
					else
					{      
						cout<<"get result fail"<<mysql_error(mysql)<<endl;
						tag = false;
					}
				}
				else
				{
					num = mysql_num_fields(result);
					int m = mysql_num_rows(result);
					if( m > 0 )
					{
						// cout<<"QQQ"<<endl;
						char buff[128] = {0};

						int i,j,k = 0;
						char flag = '0';
						while((row=mysql_fetch_row(result)))
						{
							flag = '0';
							i = 0;
							printf("row[0] : %s\n",row[0]);
							if(strncmp(row[0],path,strlen(path)) == 0)
							{
								printf("row[0] : %s\n",row[0]);
								int buff_size = strlen(row[0]);
								j = strlen(path);
								printf("i : %d     j : %d     buff_Size : %d\n",i,j,buff_size);
								while(j < buff_size)
								{
									printf("row[0][j] : %c \n", row[0][j]);
									if(row[0][j] == '/')
									{
										flag = '1';
										break;
									}


									vec1 += row[0][j++];
								}
								k++;
								std::cout << "vec1 : " << vec1 << std::endl;;
								vec += ' ' + vec1 + ' ' + flag;
								std::cout << "vec : " << vec << std::endl;;
								vec1.clear();
							}
						}
						sprintf(result_buff+1," %d",k);
						strcpy(result_buff+strlen(result_buff),vec.c_str());

					}
					// cout<<"WWWW"<<endl;								int i = 0;
					mysql_free_result(result);
					//printf("%p-%d",result,i++);
					while(!mysql_next_result(mysql))
					{
						result = mysql_store_result(mysql);
						//printf("%p-%d",result,i++);
						mysql_free_result(result);
					}

					//cout<<"RRRR"<<endl;
				}
			}

		}

		bool ReName(char* table_name, char* old_path, char* new_path)
		{
			char sql[128] = {0};
			sprintf(sql,"update %s set virtual_path = '%s' where virtual_path = '%s'",table_name,new_path,old_path);
			if(QueryData(sql))
			{
				printf("update true\n");
				return true;
			}
			else
			{
				printf("update false\n");
				return false;
			}
		}
		void mysqlFreeResult() 
		{
			mysql_free_result(result);
			while(!mysql_next_result(mysql))
			{
				result = mysql_store_result(mysql);
				//printf("%p-%d",result,i++);
				mysql_free_result(result);
			}
		}

		bool remove_file(char* table_name, char* path,char *name)
		{
			char sql[128] = {0};
			char real_path[128] = {0};
			sprintf(sql,"select real_path from %s where virtual_path = '%s%s'",table_name,path,name); 
			if(QueryData(sql)) // 查找表中的真实路径
			{
				result=mysql_store_result(mysql); 
				row = mysql_fetch_row(result); 
				if(row[0] != NULL) //找到啦
				{
					strcpy(real_path,row[0]);
					printf("real_path : %s\n",real_path);
				}
				mysqlFreeResult();
				memset(sql,0,128);
				sprintf(sql,"delete from %s where virtual_path = '%s%s'",table_name,path,name);
				if(QueryData(sql))//从用户表中删除
				{
					return true;
				}
				else
				{
					perror("delete error\n");
					return false;
				}

			}
			else
			{
				perror("no this files\n");
				return false;
			}
	 }


		bool insert_file_first(char* result_buff, char* table_name, char* path, char* name, char* md5)
		{
			printf("mysql:%s-%s-%s-%s\n",table_name,path,name,md5);
			char sql[128] = {0};
			sprintf(sql,"select * from %s where virtual_path = '%s%s'",table_name, path, name);
			if(QueryData(sql))//查找用户表是否有重名文件
			{
				printf("1llll\n");
				result = mysql_store_result(mysql);
				row = mysql_fetch_row(result);
				if( row == NULL)//没有重名文件
				{
					printf("2llll\n");
					mysqlFreeResult();
					memset(sql,0,128);
					sprintf(sql,"select real_path from files where md5 = '%s'",md5);
					if(QueryData(sql))//在md5表中找是否有重名md5码
					{
						result = mysql_store_result(mysql);
						row = mysql_fetch_row(result);
						char real_path[128] = {0};
						if(row == NULL)//md5表没有 result=0 return 1;
						{
							printf("3llll\n");
							sprintf(result_buff,"0%s%d%s",mysql_file_path,mysql_file_name,name);
							++mysql_file_name;
							mysqlFreeResult();
							return true;
						}
						else          //md5表中有  秒传;
						{
							printf("4llll\n");
							strcpy(real_path,row[0]);
							mysqlFreeResult();
							result_buff[0] = '1';
							memset(sql,0,128);
							sprintf(sql,"select virtual_path from %s where virtual_path = '%s'",table_name, path);
							if(QueryData(sql))
							{
								result = mysql_store_result(mysql);
								row = mysql_fetch_row(result);
								if(row == NULL)
								{ 
									printf("5llll\n");
									memset(sql,0,128);
									sprintf(sql,"insert into %s values('%s%s','%s')",table_name,path,name,real_path);
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
								else
								{
									char new_path[128] = {0};
									sprintf(new_path,"%s%s",path,name);
									ReName(table_name,path,new_path);// 修改用户表
									memset(sql,0,128);
									sprintf(sql,"update %s set real_path = '%s' where virtual_path = '%s'",table_name,real_path,new_path);
									printf("sql:%s\n",sql);
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
					perror("table have same name files ,error\n");
					return false;
				}
			}
			else
			{
				perror("insert file error \n");
				return false;
			}
		}

		bool insert_file_second(char* result_buff, char* table_name, char* path,char* name, char* md5)
		{
			char sql[128] = {0};
			printf("path : %s\n",path);
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
						sprintf(sql,"update %s set real_path = '%s' where virtual_path = '%s'",table_name,result_buff,new_path);
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
							printf(" row : %s\n", row[0]);
							if(row != NULL)
							{
								memset(sql,0,128);
								sprintf(sql,"update %s set real_path = '%s' where virtual_path = '%s'",table_name,row[0],new_path);
								if(QueryData(sql))
								{
									return true;
								}
								else
								{
									perror("insert data error\n");
									return false;
								}
								//		sprintf(sql,"insert real_path into %s values('%s')",table_name,row[0]);
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

		bool GetFile(char *result_buff,char* table_name, char* path,bool flag = false)
		{
			char sql[128] = {0};
			if(flag)
			{
				path[0] = '/';
			}

			//	mysql_free_result(result);
			//printf("%p-%d",result,i++);
			while(!mysql_next_result(mysql))
			{
				result = mysql_store_result(mysql);
				//printf("%p-%d",result,i++);
				mysql_free_result(result);
			}
			sprintf(sql, "select * from %s where virtual_path = '%s'", table_name, path);
			if(QueryData(sql))
			{
				result = mysql_store_result(mysql);

				row=mysql_fetch_row(result);
				if(row != NULL)
				{
					mysql_free_result(result);
					result_buff[0] = '0';
				}
				else
				{
					mysql_free_result(result);
					result_buff[0] = '1';
					DealResult(result_buff,table_name,path);
				}

			}
		} //0   1[0000] erty 9 werty 4567 sprintf


		bool getreal_path(char *result_buff,char *username,char *path,char *file_name)
		{
			char sql[128] = {0};
			sprintf(sql,"select real_path from %s where virtual_path = '%s%s';",username,path,file_name);
			if(QueryData(sql))
			{
				result = mysql_store_result(mysql);
				row = mysql_fetch_row(result);
				if(row != NULL)
				{
					strcpy(result_buff,row[0]);
					mysql_free_result(result);
					return true;
				}
				else
				{
					printf("mysql error\n");
					return false;
				}
			}
			else
			{
				printf("mysql error\n");
				return false;
			}
		}
		~Mysql()
		{
			//if(result!=NULL)
			//{
			//   mysql_free_result(result);
			//}
			mysql_close(mysql);
		}
	private:
		string  vec;
		MYSQL *mysql;
		MYSQL_RES *result;
		MYSQL_FIELD *fd;
		MYSQL_ROW  row;
		bool friend insert_file(char* result_buff, char* table_name, char* path, char* md5, bool tag);
};


//string username;
//string filepath;
Mysql mysqlserver;
bool Register(char *name, char *passwd)
{
	printf("mysql:%s-%s\n",name,passwd); 
	char str[100];
	bool tag = true;
	sprintf(str, "insert into user_passwd (name, passwd) values('%s','%s')", name, passwd);
	char tablename[100];
	sprintf(tablename,"create table %s(virtual_path varchar(32) not null primary key, real_path varchar(64))",name);
	if (mysqlserver.QueryData(str))
	{
		cout<<tablename<<endl;
		if(mysqlserver.QueryData(tablename))
		{
			memset(str, 0, 100);
			//	memset(tablename, 0, 100);
			//	sprintf(tablename, "%s", "\");
			sprintf(str, "insert into %s (virtual_path) values('/')", name);
			mysqlserver.QueryData(str);
		}
	}
	else
	{
		cout << "Register fail"  << endl;
		tag = false;
	}

	return tag;
}

bool remove_file(char* table_name, char* path,char *name)
{
	return mysqlserver.remove_file(table_name,path,name);
}

bool ReName(char* table_name, char* old_path, char* new_path)
{
	return mysqlserver.ReName(table_name,old_path,new_path);
}

bool insert_file(char* result_buff, char* table_name, char* path,char *name, char* md5, bool tag)
{
	return mysqlserver.insert_file(result_buff,table_name,path,name,md5,tag);
}

bool Get_File(char *result_buff,char* table_name, char* path,bool flag );

bool Login(char * name,char * passwd, char *result_buff)
{
	if(mysqlserver.LoginQuery(name, passwd))
	{
		char buff[128] = {0};
		cout << "Login success" << endl;
		//char result_buff[128] = {0};
		Get_File(result_buff,name,buff,true);
		//mysqlserver.DealResult(result_buff, name, "/");
		cout << result_buff << endl;
		return true;
	}
	return false;
}

bool Get_File(char *result_buff,char* table_name, char* path,bool flag = false)
{
	return mysqlserver.GetFile(result_buff,table_name,path,flag);
} //0   1[0000] erty 9 werty 4567 sprintf


bool get_real_path(char *result_buff,char *username,char *path,char *file_name)
{
	return mysqlserver.getreal_path(result_buff,username,path,file_name);
}

bool mysql_mkdir_file(char* table_name,char* path,char* dir_name)
{
	return mysqlserver.mkdir_file(table_name,path,dir_name);
}

//int main()
//{
//	char buff[128] = {0};
//	bool flag = get_real_path(buff,"essity","/","1.rmvb");
//	printf("%d-%s\n",flag,buff);
//	return 0;
//}

#endif
