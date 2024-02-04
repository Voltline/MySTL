#pragma once
#include <iostream>
#include "../includes/string.h"

namespace StringTest
{
	void StringTest()
	{
		std::cout << "*-----Here are MySTL::String Test-----*" << std::endl;
        MySTL::string s1{ "HEllo!" }, s3{ "World!" }, s0{ "你好，世界！" };
        std::cout << "s0 : " << s0 << std::endl;

        MySTL::string s2{ "HelloABABABBABC123HDJKAS, World!!" };
        std::cout << "s2 : " << s2 << std::endl;
        std::cout << "Find C12 in s2 from pos2 : " << s2.find("C12", 2) << std::endl;
        std::cout << "Find CBA in s2 : " << s2.find("CBA", 0) << std::endl;

        s1 += s3;
        std::cout << "s1 += s3, s1 : " << s1 << std::endl;

        s1.erase(s1.begin() + 6);
        std::cout << "Erase s1.begin() + 6 : " << s1 << std::endl;

        s1.append("ABCDEFGHI");
        std::cout << "Append ABCDEFGHI to s1 : " << s1 << std::endl;

        s1.erase(4, 3);
        std::cout << "Erase from 4 to 6 : " << s1 << std::endl;
        std::cout << "Find ~ in s1 : " << s1.find('~') << std::endl;

        std::cout << "Now please input a line of string with ' ' and '\\t': ";
        getline(std::cin, s1);
        std::cout << "Now, s1 : " << s1 << std::endl;

        s1.swap(s3);
        std::cout << "Finally, swap s1 for s3, s1 : " << s1 << std::endl << "While s3 : " << s3 << std::endl;
        
        std::cout << "*-----End of MySTL::String Test-----*" << std::endl;
	}
}