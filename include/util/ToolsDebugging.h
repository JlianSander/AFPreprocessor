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
#include "ArrayBitSet.h"
#include "Printer.h"
#include "ToolsList.h"

namespace tools {

    /// <summary>
	/// This class is responsible for offering helping methods for Debugging.
	/// </summary>
	class Tools_Debug {

    public:
        static std::list<uint32_t> read_witness(const std::string& file_path_witness);
        static bool compare_witness_to_list(const std::string& file_path_witness, const std::list<uint32_t>& considered_arguments, bool showNotFound, bool show_Remaining,
        std::list<uint32_t>& not_found_OUT, std::list<uint32_t>& remaining_OUT);
        static void test_witness_check();
        static std::list<uint32_t> get_active_attackers(AF &framework, ArrayBitSet &active_args, uint32_t query_argument);
    };    
};

#endif