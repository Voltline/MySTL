#pragma once
#include <iostream>
#include "../includes/String.h"

namespace StringTest
{
	void StringTest()
	{
		std::cout << "*-----Here are MySTL::String Test-----*" << std::endl;
        MySTL::String s1{ "HEllo!" }, s3{ "World!" };
        s1 += s3;
        std::cout << "s1 += s3, s1 : " << s1 << std::endl;
        s1.erase(s1.begin() + 6);
        std::cout << "Erase s1.begin() + 6 : " << s1 << std::endl;
        s1.append("ABCDEFGHI");
        std::cout << "Append ABCDEFGHI to s1 : " << s1 << std::endl;
        s1.erase(4, 3);
        std::cout << "Erase from 4 to 6 : " << s1 << std::endl;
        std::cout << "Find ~ in s1 : " << s1.find('~') << std::endl;
        std::cout << "*-----End of MySTL::String Test-----*" << std::endl;
	}
}