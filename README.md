# sstr: the Super Simple Test Runner

Look... honestly I don't think that anybody should really ever use this stuff. 
But everytime I needed to do some demo and do some test that would require something just a bit more flexible that a single main function, I was annoyed to go through the burden of importing the gtest library (that nowadays it became massively complex - I mean... good (gmocks rocks), but too complex).
Up to a certain point there as catch2... header only. But it started to get super slow, so that now they splitted in several headers and I think that is not header only anymore either.

So here is your single TestRunner.hpp that has only a few calls that I show directly in code.
**BEWARE: Requires at least C++17.**

## Creating Tests

Create how many cpp files you want for your tests

```cpp
#include <TestRunner.hpp>

ADD_RUN(some_very_interesting_test)
{
	EXPECT(<some boolean expression>);
}

ADD_RUN(some_other_very_interesting_test)
{
	EXPECT(<some boolean expression>);
}

```

Then create your main with something like this:

```cpp

#include <TestRunner.hpp>

INIT_RUNS; // To be called before main to initialise the tests

int main()
{
	runTests();
	// or
	runTestsIfNameContains("Interesting");
}
```

## Adding to gotbolt
TODO

## IMPORTANT NOTES

Consider that tests (or so simply called `ADD_RUNS`) are added via static initialisation so you can control the order in which test are run via the order in which the compiled objects of the tests are linked into the executable.

For example with cmake:

```cmake
cmake_minimum_required(VERSION 3.20)
project(ALotOfInterestingTests)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}
        main.cpp
        FirstTestsToRun.cpp
        SecondTestsToRun.cpp
        ...
        LastTestsToRun.cpp)

target_include_directories(${PROJECT_NAME} 
	SYSTEM BEFORE PRIVATE <location of where you have downloaded TestRunner.hpp>)

``` 

And that is even too much I have to said about it... for one file, this README.md is even probably too much :)

