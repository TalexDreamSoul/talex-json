#include <iostream>

using namespace std;

#include "json\json.h"
using namespace Talex::Json;

int main()
{

  Json a;

  a.parse("\"{\\\"name\\\":\\\"Json 生成 JsonSchema\\\",\\\"age\\\":2023,\\\"address\\\":{\\\"city\\\":\\\"utoolsk\\\",\\\"state\\\":\\\"NY\\\",\\\"zip\\\":\\\"1.0.6\\\"},\\\"phone\\\":[{\\\"type\\\":\\\"mobile\\\",\\\"num\\\":\\\"555-1234\\\"},{\\\"type\\\":\\\"home\\\",\\\"num\\\":\\\"555-5678\\\"}],\\\"isOnline\\\":true,\\\"salary\\\":null,\\\"emptyArray\\\":[]}\"");

  Json obj = a["address"];

  // obj["name"] = "Talex";
  // obj["age"] = 18;
  // obj["height"] = 1.80;
  // obj["weight"] = 60.0;

  // Talex::Json::Json arr;

  // arr[-1] = true;
  // arr[1] = 1;
  // arr.append(2);
  // arr.append("Hello World!");

  // const string &s = arr[3];

  // std::cout << s << std::endl;

  // Talex::Json j2 = true;
  // Talex::Json j3 = 1;
  // Talex::Json j4 = 1.0;
  // Talex::Json j5 = "Hello World";
  // Talex::Json j6 = {1, 2, 3, 4, 5};
  // Talex::Json j7 = {{"a", 1}, {"b", 2}, {"c", 3}};

  std::cout
      << obj.str() << std::endl;

  return 0;
}