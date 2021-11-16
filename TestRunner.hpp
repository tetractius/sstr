//
// "THE BEER-WARE LICENSE" (Revision 42):
// filippo.trimoldi@zoho.com wrote this file.
// As long as you retain this notice you can do whatever you want with this stuff.
// If we meet some day, and you think this stuff is worth it, you can buy me a beer in return
// Poul-Henning Kamp
//

#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <functional>

#define EXPECT( chk )  \
    if (!(chk)) { \
        printf("FAILED: Test (%s) failed %s at line %d \n", #chk, __FILE__,__LINE__); \
        } \
    else \
        printf("PASSED: Test (%s) passed %s at line %d \n", #chk, __FILE__,__LINE__);


using TMain = std::function<void()>;

using TNamedTest = std::pair<std::string, TMain>;

class S
{
public:
    static std::vector<std::shared_ptr<TNamedTest>> vector_of_tests;
};

static void runTestsIfNameContains(const std::string& s)
{
    for (auto test: S::vector_of_tests)
    {
        if(test && test->first.contains(s))
        {
            test->second();
        }
    }
}

static void runTests()
{
    runTestsIfNameContains("");
}

#define ADD_RUN(verb)  \
class verb##BeforeMain \
{                      \
    static bool foo;   \
};                     \
void noret##verb();    \
void print##verb##section()                               \
{                                                         \
  std::cout                                               \
  << "============  "                                     \
  << #verb                                                \
  << std::endl;                                           \
}                                                         \
bool ret##verb()                                          \
{                                                         \
  auto p = std::make_shared<TNamedTest>(#verb,                 \
                                        print##verb##section); \
  auto f = std::make_shared<TNamedTest>(#verb,                 \
                                        noret##verb);          \
  S::vector_of_tests.push_back(p);                        \
  S::vector_of_tests.push_back(f);                        \
  return true;                                            \
}                                                         \
bool verb##BeforeMain::foo = ret##verb();                 \
void noret##verb()

#define INIT_RUNS \
std::vector<std::shared_ptr<TNamedTest>> S::vector_of_tests = {};

