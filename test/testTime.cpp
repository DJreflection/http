//
// Created by zy on 11/18/17.
//

#include <iostream>
#include <map>

using namespace std;

int main()
{
    map<std::string, std::string> res;
    res["aa"] = "nn";


    std::string& tmp = res["aa"];
    tmp.append("hha");

    std::cout << res["aa"] << std::endl;
    return 0;
}