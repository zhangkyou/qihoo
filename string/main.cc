#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <assert.h>
#include <string.h>
#include <stdexcept>
#include "qh_string.h"

void test1(){
	qh::string s;
	s = "abc";//= operator
	//std::cout<<"Test 1:"<<std::endl;
	//std::cout<<s.size()<<std::endl;
	assert(s.size()==3);
    	assert(strncmp(s.c_str(), "abc",3) == 0);//c_str()
    	assert(s[0] == 'a');//[] operator
	//std::cout<<s[0]<<std::endl;
}

void test2() {
    	char a[] = "abc";
    	qh::string s(a); // construction
	//std::cout<<"Test 2:"<<std::endl;
	//printf("%s\n",s.data());
    	assert(s.size()==3);
	//std::cout<<s.size()<<std::endl;
    	assert(strncmp(s.c_str(), a,3) == 0);
}

void test3() {
    	char a[] = "abc";
    	qh::string s1(a);
	//std::cout<<"Test 3:"<<std::endl;
    	qh::string s2 = s1; // equal operator
	//printf("%s\n",s2.data());
	//std::cout<<s2.size()<<std::endl;
    	assert(s2.size()==3);
    	assert(strncmp(s2.c_str(), "abc",3) == 0);
}

// out of range case
void test4() {
    	char a[] = "abc";
    	qh::string s(a); // equal
	//std::cout<<"Test 4:"<<std::endl;
    	char c;

   	try {
        	c = s[5];
    	} catch (std::out_of_range) {
        	//std::cout<<"out of range!"<<std::endl;
		return;
    	}
    	assert(0>1); //shoudn't go here
}


int main(int argc, char* argv[])
{
    //TODO 在这里添加单元测试，越多越好，代码路径覆盖率越全越好
    //TODO 单元测试写法请参考INIParser那个项目，不要写一堆printf，要用assert进行断言判断。
    test1();
    test2();
    test3();
    test4();

#ifdef WIN32
    system("pause");
#endif

	return 0;
}

