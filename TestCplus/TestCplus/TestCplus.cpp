// TestCplus.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <iostream>

#include <fstream> 
#include <vector> 
#include "base64.h"  

using namespace std;

union B_F{
	unsigned char b[4];
	float f;
};

union B_S{
	unsigned char b[2];
	short s;
};
vector <string> v; 
char ch; 

int _tmain(int argc, _TCHAR* argv[])
{
	string qpeFileout = "qpeout.txt";
	fstream io1;
	io1.open(qpeFileout.c_str(),ios::out);

	string qpeFile = "qpe.txt";
	ifstream io;
	io.open(qpeFile.data());

	string s;
	getline(io,s);
	io.close();             //关闭文件输入流 

	//const std::string s = "10.3" ;  

	//std::string encoded = base64_encode(reinterpret_cast<const unsigned char*>(s.c_str()), s.length());  
	std::string decoded = base64_decode(s); 
	//std::string decoded = b64decodestring(s);

	//std::cout << "encoded: " << encoded << std::endl;  
	//std::cout << "decoded: " << decoded << std::endl;  
	const char* p = decoded.c_str();

	B_F b_f;
	int k = 0;
	for(int i=0;i<880;i++){
		for(int j=0;j<1050;j++){
			b_f.b[0] = p[k];
			b_f.b[1] = p[k+1];
			b_f.b[2] = p[k+2];
			b_f.b[3] = p[k+3];
			io1<<b_f.f<<" ";
			k = k+4;
		}
		io1<<endl;
	}

	io1.close();
	/*for(int i=0; i<100000; i++) 
	v.push_back("abcdefghijklmn"); 
	// 此时检查内存情况 占用54M 
	cout << "Vector的容量为" << v.capacity() << " Vector 的大小为:"<<v.size()<< endl; 
	//vector<string>::iterator it;
	for ( int i = 0 ; i<2 ; i++ )  {
	v.erase(v.begin());
	}
	cout << "Vector erase后的容量为" << v.capacity() << " Vector 的大小为:"<<v.size()<< endl; 
	v.clear(); 
	// 此时再次检查， 仍然占用54M 

	cout << "Vector 的容量为" << v.capacity() <<" Vector 的大小为:"<<v.size()<< endl; 
	// 此时容量为 1048576 

	vector<string>(v).swap(v); 

	cout << "Vector 的容量为" << v.capacity() <<" Vector 的大小为:"<<v.size()<< endl; 

	for(int i=0; i<100000; i++) 
	v.push_back("1111"); 
	cout << "Vector 的容量为" << v.capacity()<<" Vector 的大小为:"<<v.size()<< endl; 
	// 此时容量为0 
	// 检查内存，释放了 10M+ 即为数据内存 */
	cout<<"test"<<endl;
	getchar();
	return 0;
}