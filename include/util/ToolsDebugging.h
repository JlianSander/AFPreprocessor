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
#include "ToolsList.h"

namespace tools {

    /// <summary>
	/// This class is responsible for offering helping methods for Debugging.
	/// </summary>
	class Tools_Debug {

    public:
        static bool checkContainsNumbersOfWitness(AF &framework, const std::string& file_path_witness, const std::list<uint32_t>& considered_arguments, bool showNotFound, bool show_Remaining);
        static void test_witness_check();
    };    
};

#endif