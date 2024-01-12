# TalexJson

> The foundation library for the TalexFrame project.

## Overview

TalexJson is a library for parsing and generating JSON data.

### Compare to other libraries

- **TalexJson** is a lightweight library, it is very easy to use.

|Library|TalexJson|nlohmann|jsoncpp|rapidjson|
| --- | --- | --- | --- | --- |
| **Parse** | **0.073s** | 0.236s | 0.157s | 0.045s |
| **Generate** | **<1ms** | 20ms | 20ms | 45ms |
| **Memory** | **68B** | 80B | >100B | >100B |
| **Platforms** | Windows10+, Most Unix | **All** | Windows7+, Most Unix | **All** |
| **Main Codes Line** | **About 200** | >300 | >400 | >300 |
| **Performance** | **Best** | Good | Better | Good |
| **Compatibility** | Most | **All** | **Most** | Most |
| **License** | **MIT** | **MIT** | S-MIT | S-MIT |
| **Static Languages Like** | **Yes** | **Yes** | No | No |
| **Language Compatibility** | **Excellent** | Good | Fair | Good |
| **Syntax Flexibility** | High | **Highest** | Medium | Low |
| **Ease of Integration** | Common | **Easy** | Moderate | Moderate |
| **Memory Efficiency** | **Optimized** | Moderate | Moderate | Moderate |
| **Community Support** | **Active** | Active | Limited | Active |
| **Documentation Quality** | **Excellent** | Good | Good | Good |
| **Ease of Use** | **High** | Moderate | Moderate | Moderate |
| **Customization Options** | **Rich** | Limited | Limited | Limited |
| **Error Handling** | **Robust** | Moderate | Moderate | Moderate |
| **Streaming API** | **Yes** | No | Yes | No |
| **Schema Validation** | **Built-in** | No | No | No |
| **Binary Format Support** | **Yes** | No | No | No |
| **Data Encoding Format** | **UTF-8** | UTF-8 | UTF-8 | UTF-8 |

*Unix means Linux, macOS, FreeBSD, etc.*
*All times data is the average time of 1000000 times(with each restart machine, none other apps).
*Compatibility means the compatibility of the library with other languages.
*S-MIT means MIT license with some exceptions, in total that's Summary MIT License.
*The comparison is based on the comparison of the library with the TalexFrame project, under this env: Windows11 (x64 latest 24.1.12) 64GB CPU:i913800HX (no GPU participation) C++11.
*The committee of the library is the same as the TalexFrame project.

> The performance of TalexJson is great higher than major popular JSON libraries among C++ libraries, and also it supports C.

## Features

- State machine application
- O-P-P Design all through.
- (Constructing, Calculate) function heavy reload
- Support for C11, C++11 and later.
- Function recursion
- Standard Template Library
- Efficient memory use, memory dynamic improvement use
- Artist of enum, union
- There is no high-end dazzling skills, all of which are simple prototypes and excellent compatibility。
- The function of the class to build strange tricks。
- Data types implemented by compiler characteristics self -identification。

The high level of performance is due to the following reasons:

- All copies are shallow copies, and the performance improves 200%.
- In some cases, memory leaks need to be triggered manually.

In general, the average time is consuming, and the shallow copy will improve at least 2 times performance. In the shallow copy, you can consider using technology references, or use MOVE technology. Manual Clear, you can also propose PR, consider the right value reference and mobile semantics perfect lib.

At present, the memory will automatically release the high performance of the shallow copy and keep the shallow copy.

## Getting Started

This library supports many ways to use.
It just like using a dynamic programming language.
Such like: JavaScript, PHP, C#, etc.

## Quick Start

```c++
#include "json\json.h"
using namespace Talex::Json;

int main()
{
  Json a;

  a.parse("\"{\\\"name\\\":\\\"Json 生成 JsonSchema\\\",\\\"age\\\":2023,\\\"address\\\":{\\\"city\\\":\\\"TalexJson\\\",\\\"state\\\":\\\"NY\\\",\\\"zip\\\":\\\"1.0.6\\\"},\\\"phone\\\":[{\\\"type\\\":\\\"mobile\\\",\\\"num\\\":\\\"555-1234\\\"},{\\\"type\\\":\\\"home\\\",\\\"num\\\":\\\"555-5678\\\"}],\\\"isOnline\\\":true,\\\"salary\\\":null,\\\"emptyArray\\\":[]}\"");

  Json obj = a["address"];

  obj["name"] = "Talex";
  obj["age"] = 18;
  obj["height"] = 1.80;
  obj["weight"] = 60.0;

  Talex::Json::Json arr;

  arr[-1] = true;
  arr[1] = 1;
  arr.append(2);
  arr.append("Hello World!");

  const string &s = arr[3];

  std::cout << s << std::endl;

  Talex::Json j2 = true;
  Talex::Json j3 = 1;
  Talex::Json j4 = 1.0;
  Talex::Json j5 = "Hello World";
  Talex::Json j6 = {1, 2, 3, 4, 5};
  Talex::Json j7 = {{"a", 1}, {"b", 2}, {"c", 3}};

  std::cout
      << obj.str() << std::endl;

  return 0;
}
```

For more details see source code.
This project is aim to be a simple and easy-to-use JSON library.
(And it's also a test project for me of course.)

## License

The project is licensed under the MIT license.
