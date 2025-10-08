#ifndef WITNESS_TESTER_H
#define WITNESS_TESTER_H

#include <iostream>
#include <cstdint>
#include <string_view>
#include <functional>
#include <vector>
#include <queue>

extern "C" {
	#include "../util/MemoryWatchDog.h"
}

#include "../logic/AF.h"
#include "../logic/Decoding.h"
#include "../logic/Encoding.h"
#include "../logic/Enums.h"
#include "../logic/PreProcessor_GR.h"
#include "../logic/Processor_DS_PR.h"
#include "../logic/Reduct.h"
#include "../logic/SatSolver.h"
#include "../logic/ToolsSolver.h"
#include "../logic/Solver_DC_CO.h"

#include "../util/Printer.h"
#include "../util/ToolsList.h"
#include "../util/ToolsDebugging.h"

namespace tools {

    class WitnessTester {
    public:
        static bool test(uint32_t query_argument, AF &framework, const std::string& file_path);

    };
};
#endif