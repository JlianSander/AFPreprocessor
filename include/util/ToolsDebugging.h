#ifndef TOOLS_DEBUGGING_H
#define TOOLS_DEBUGGING_H

#include <cstdio>
#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>
#include <list>
#include <functional>

#include "../logic/AF.h"
#include "Printer.h"

namespace tools {

    /// <summary>
	/// This class is responsible for offering helping methods for Debugging.
	/// </summary>
	class Tools_Debug {

    public:
        static bool checkContainsNumbersOfWitness(AF &framework, const std::string& file_path_witness, const std::list<uint32_t>& considered_arguments);
        static void print_Msg_ContainsNumbersOfWitness(AF &framework, const std::string& filePath, const std::list<uint32_t>& arr);
        static void test_witness_check();
    };    
};

#endif