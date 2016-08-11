/*************************************************************************
	> File Name: sql.cpp
	> Author:Jone 
	> Mail:mjf2019@126.com 
	> Created Time: 2016年07月07日 星期四 15时48分47秒
 ************************************************************************/

#include <iostream>
#include "Mysql.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
using namespace std;

string username;
string filepath;
string indexsize;
string allname;
string path  = "/home/";

Mysql mysqlserver;
bool Register(char *id, char *name, char *passwd)
{
    
	char str[100];
	bool tag = true;
	sprintf(str, "insert into user(userid, name, passwd) values('%s', '%s',' %s')", id, name, passwd);
    char tablename[100];
    sprintf(tablename,"create table %s(name varchar(20),address varchar(25),hash varchar(20),filesize varchar(10))",name);
	if (mysqlserver.QueryData(str))
	{
        cout<<tablename<<endl;
        mysqlserver.QueryData(tablename);
    }
    else
    {
    cout << "Register fail"  << endl;
    tag = false;
    }
	return tag;
}
bool Login(char *id,char * name,char * passwd)
{
    username = name;
    string userid = id;
    string userpasswd = passwd;
    string sql = "select * from user where userid = "+userid +" and passwd = " + userpasswd;
    if(mysqlserver.QueryData(sql))
    {
        return true;
    }
    return false;
}

string GetFile()
{
    string sql = "select name form "+username;
    mysqlserver.QueryData(sql);
    allname = mysqlserver.DealResult();
    return allname;
}

bool  FineFile(const char* md5 )
{
    bool tag = true;
    string str = md5;
    string sql ="select * from file where md5 =  '" + str +" '";
    if(!mysqlserver.QueryData(sql))
    {
        cout<<"false"<<endl;
        tag = false;
    }
    
    cout<<"Findfile  OK"<<endl;
    return tag;
}

string GetFileIndex(const char * md5)
{
    string str = md5;  
    string sql = "select fileindex from file where md5 = '" + str +"'";
   cout<<sql<<endl;
    mysqlserver.DealResult();
    if(mysqlserver.QueryData(sql) )
    {
        cout<<"fileindex OK"<<endl;
       return  mysqlserver.DealResult();
    }
    mysqlserver.DealResult();
    return NULL;
}

string CheckUserMd5(const char * usermd5)
{
    string useroldmd5 = usermd5;

      string sql = "select fileindex from file  where md5 = '" + useroldmd5 +"'"; 
    if(mysqlserver.QueryData(sql))
    {
        filepath = mysqlserver.DealResult();
        return filepath;
    }
    cout<<"no have file"<<endl;
    return path;
}

string FileUpload(char * filename ,char * usermd5,char * filesize)
{
    
    string userfilename = filename;
    string size = filesize;
    mysqlserver.DealResult();
    if(CheckUserMd5(usermd5) == (path+filename))// 文件存在
    {
        cout<<"ooooooo"<<endl;
        string str = "insert into " + username + " values( '"+ userfilename+ "','" + filepath +"','"+ usermd5+ "'," +  filesize+  ")";
       // cout<<str<<endl;
        //mysqlserver.DealResult();
        cout<<"file check ---------"<<endl;
        mysqlserver.QueryData(str);
        cout<<"file check finish------------"<<endl;
        return userfilename;
    }
    else
    {

        path += filename;
        cout<<path<<endl;
        string str = "insert into " +username + "(name ,address,hash,filesize) values( '"+ userfilename+ "','" + path +"','"+ usermd5+ "','" +size +"')";
       
        string sql = "insert into file (fileindex,md5,filesize) values('"+ path +"','"+ usermd5+ "','" +size +"')";

        cout<<str<<endl;
        cout<<sql<<endl;
        cout<<"FileUpload---------- "<<endl;
        mysqlserver.DealResult();
        mysqlserver.QueryData(str);
        mysqlserver.DealResult();
        mysqlserver.QueryData(sql);

        return path;
    }
}

string  FileUpdown(char *name )
{
    string filename  = name;
    string  sql = "select address from "  + username+ " where name  = '" + filename +"'" ;
  

    string  sql3 = "select hash  from "  + username+ " where name  = '" + filename + "'";

    
    
    mysqlserver.DealResult();
    string ar1;
    string ar2;
    string ar3;
    string ar4;
    string ar5;
    if(mysqlserver.QueryData(sql))
    {
         ar1= mysqlserver.DealResult();  //address
        mysqlserver.QueryData(sql3);
        ar3 = mysqlserver.DealResult(); //hash
        //cout<<ar3<<endl;
    string  sql2 = "select filesize from file where  md5  = '" + ar3 + "'";
        mysqlserver.QueryData(sql2) ;
         ar2 = mysqlserver.DealResult(); //size
        //cout<<ar2<<endl;
        indexsize = ar1 + " " + ar2;
        cout<<"file download  in my file-----"<<endl;
        cout<<ar1 <<" "<<ar2 <<endl;
        return indexsize;
    }
    else
    {
        
    string  sql4 = "select address from file where name  = '" + filename +"'" ;
   
        mysqlserver.QueryData(sql4);  //address
        ar4 = mysqlserver.DealResult();

        string  sql5 = "select filesize from file where name  = '" + ar4 + "'";
        mysqlserver.QueryData(sql5) ;
        ar5 = mysqlserver.DealResult();  //size
        indexsize = ar4 + " " + ar5;
        cout<<"file down in file -----"<<endl;
        return indexsize;
    }

}

int main()
{
    //Register("1111","qqqq","3333");
    Login("1111","qqqq","3333");
    //FineFile("d41d8cd98f00b204");
    //cout<<"sssss"<<endl;
    //string  ss1 = GetFileIndex("d41d8cd98f00b204");
    //cout<<"OK"<<endl;
    //string ss =FileUpload("222e.cpp","3333","1118");
    string ss = FileUpdown("222e.cpp");
    return 0;
}
