#include "ini_parser.h"

#include <assert.h>
#include <string>
#include <string.h>
#include <iostream>

void test1()
{
    const char* ini_text= "a=1\nb=2\n"; 
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "\n", "=")) {
        assert(false);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    std::string b = parser.Get("b", NULL);
    assert(b == "2");

    const std::string& c = parser.Get("c", NULL);
    assert(c == "");
}

void test2()
{
    const char* ini_text= "a=1||b=2||c=3"; 
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "||", "=")) {
        assert(false);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    std::string b = parser.Get("b", NULL);
    assert(b == "2");

    const std::string& c = parser.Get("c", NULL);
    assert(c == "3");
}

void test3()
{
    const char* ini_text= "||||a:1||b:2||||c:3||||||"; 
    qh::INIParser parser;
    if (!parser.Parse(ini_text, strlen(ini_text), "||", ":")) {
        assert(false);
    }

    const std::string& a = parser.Get("a", NULL);
    assert(a == "1");

    std::string b = parser.Get("b", NULL);
    assert(b == "2");

    const std::string& c = parser.Get("c", NULL);
    assert(c == "3");
}

void test4()
{
    const char* ini_text_path= "testfile.ini"; 
    qh::INIParser parser;
    if (!parser.Parse(ini_text_path)) assert(false);
  

    const std::string& a = parser.Get("PortController","PortCount", NULL);
    //std::cout<<"a= "<<a<<std::endl;
    assert(a == "3");

    const std::string& b = parser.Get("PortCount", NULL);
    assert(b == "");
	

    std::string c = parser.Get("PortController","Port0", NULL);
    assert(c == "80");
    
    std::string d = parser.Get("CommonCfg","firsttime", NULL);
   // std::cout<<"d= "<<d<<std::endl;
    assert(d == "1");

    const std::string& e = parser.Get("PortController","Port4", NULL);
    assert(e == "");

    const std::string& f = parser.Get("CommonCfg","Port0", NULL);
    assert(f == "88");
}

int main(int argc, char* argv[])
{
    //TODO 在这里添加单元测试，越多越好，代码路径覆盖率越全越好
    test1();
    test2();
    test3();
    test4();
    return 0;
}


