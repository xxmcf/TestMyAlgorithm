/*
 * @brief   16进制字符串转换成16进制数据
 * @author  xiao2macf
 * @version 1.0
 * @date    2020/04/03
 */
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <string>
#include <algorithm>
#include <cctype>
#include <iostream>

using std::string;
using namespace std;

string bin16ToString(unsigned char* bin, int len)
{
    if (nullptr == bin || len <= 0)
        return "";

    char temp[3];
    string s;

    for (int i=0; i<len; i++)
    {
        sprintf(temp, "%02d", bin[i]);
        s += temp;
    }

    return s;
}

string string16ToBin(const char* str)
{
    if (!str)
        return "";
    int len = strlen(str);
    if (len % 2 == 1)
        return "";

    char temp[3];
    char str16[16];

    int i = 0;
    for (; i<10; i++)
        str16[i] = '0' + i;

    for (; i<16; i++)
    {
        str16[i] = 'a' + i - 10;
    }

    string src; //TODO: 要不要先申请空间
    src.resize(len*2);
    std::transform(str, str+len, src.begin(), [](char c){return std::tolower(c);});

    string s;
    for (int i = 0; i<len; i+=2)
    {
        auto pos = std::find(str16, str16+sizeof(str16), str[i]);
        if (pos == str16+sizeof(str16))
        {
            s = "";
            return s;
        }
        pos = std::find(str16, str16+sizeof(str16), str[i+1]);
        if (pos == str16+sizeof(str16))
        {
            s = "";
            return s;
        }
        strncpy(temp, str+i, 2);
        char c = 0;
        sscanf(temp, "%02x", &c);
        s += c;
    }

    return s;
}

TEST_CASE("Bin16ToString Test", "[String16ToBIn]")
{
    SECTION("TestCase1: empty data")
    {
        string s = bin16ToString(nullptr, 0);
        REQUIRE(s.empty());
        s = bin16ToString((unsigned char*)"", 0);
        REQUIRE(s.empty());
    }

    SECTION("TestCase2: normal data")
    {
        unsigned char bin[] = {1, 2, 3, 4, 5};
        string s = bin16ToString(bin, sizeof(bin));
        string dst = "0102030405";
        REQUIRE(s == dst);
    }

}

TEST_CASE("String16ToBIn Test", "[Bin16ToString]")
{
    SECTION("TestCase1: empty data")
    {
        string bin = string16ToBin(nullptr);
        REQUIRE(bin.size() == 0);
        bin = string16ToBin("");
        REQUIRE(bin.size() == 0);
    }

    SECTION("TestCase2: the data length is not multiple of 2")
    {
        string s = "01020304055";
        string bin = string16ToBin(s.c_str());
        REQUIRE(bin.size() == 0);
    }

    SECTION("TestCase3: include character which is not hexadecimal string")
    {
        string s = "01020304mm";
        string bin = string16ToBin(s.c_str());
        REQUIRE(bin.size() == 0);
    }

    SECTION("TestCase4: normal data")
    {
        string s = "0102030405";
        s = string16ToBin(s.c_str());
        string bin;
        bin += 1;
        bin += 2;
        bin += 3;
        bin += 4;
        bin += 5;
        REQUIRE(memcmp(s.data(), bin.data(), bin.size()) == 0);
    }
}

#if 0
TEST_CASE("十六进制字符串转成十进制字符串 ", "")
{
    SECTION("C++流解法 ")
    {
        int a;
        while (scanf("%x", &a) != EOF){
            printf("%d\n", a);
        }

        while(std::cin>>std::hex>>a){
            std::cout<<a<<std::endl;
        }
    }

    SECTION("通用解法")
    {
        string hex_str;
        string oct_str;
        int oct_num = 0;
        while(cin >> hex_str)
        {
            for(int i = 2;i < hex_str.length();i++)
            {
                if(hex_str[i] >= 'A' && hex_str[i] <= 'F')
                oct_num = oct_num*16 + ( hex_str[i] - 'A' + 10 );
                else if(hex_str[i] >= 'a' && hex_str[i] <= 'f')
                oct_num = oct_num*16 + ( hex_str[i] - 'a' + 10 );
                else
                oct_num = oct_num*16 + ( hex_str[i] - '0' );
            }
            cout << oct_num<<endl;
            oct_num = 0;
        }
    }
}
#endif
