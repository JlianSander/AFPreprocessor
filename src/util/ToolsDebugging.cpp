#include "../../include/util/ToolsDebugging.h"

/*===========================================================================================================================================================*/
/*===========================================================================================================================================================*/


// Helper function to check if a string is a valid integer
static bool isValidInteger(const std::string& token) {
    if (token.empty()) return false;

    size_t start = 0;
    if (token[0] == '-' || token[0] == '+') {
        if (token.size() == 1) return false; // string is just '+' or '-'
        start = 1;
    }

    for (size_t i = start; i < token.size(); ++i) {
        if (!std::isdigit(token[i])) {
            return false;
        }
    }

    return true;
}

/*===========================================================================================================================================================*/
/*===========================================================================================================================================================*/

static std::vector<int> get_numbers(const std::string& file_path){
    // Open the file for reading
     std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << file_path << std::endl;
        return std::vector<int>();
    }

    std::string token;
    std::vector<int> numbersFromFile;

    // Read tokens one by one from the file (space-separated)
    while (file >> token) {
        if (isValidInteger(token)) {
            int number = std::stoi(token);
            numbersFromFile.push_back(number);
        }
        // else: skip the non-numeric token
    }

    file.close();

    return numbersFromFile;
}

/*===========================================================================================================================================================*/
/*===========================================================================================================================================================*/

// Helper function to get a list of all numbers of a file which are not contained in a list of numbers
static std::list<uint32_t> get_list_not_contained_numbers(std::vector<int> numbersFromFile, const std::list<uint32_t>& list_numbers) {
    
    std::list<uint32_t> not_found = std::list<uint32_t>();
    
    // Check if each number from the file is present in the provided list of number
    for (int num : numbersFromFile) {
        bool found = false;
        for (int elem : list_numbers) {
            if (elem == num) {
                found = true;
                //break;
            }
        }
        if (!found) {
            not_found.push_back(num); // If any number is not found in the list of numbers, add it to the list of not found numbers
        }
    }

    return not_found;
}

/*===========================================================================================================================================================*/
/*===========================================================================================================================================================*/


bool tools::Tools_Debug::checkContainsNumbersOfWitness(AF &framework, const std::string& file_path_witness, const std::list<uint32_t>& considered_arguments) {
    
    std::vector<int> numbersFromFile = get_numbers(file_path_witness);
    std::list<uint32_t> not_found = get_list_not_contained_numbers(numbersFromFile, considered_arguments); 

    std::cout << "Did not find " << not_found.size() << " of " << numbersFromFile.size() << " arguments in witness." << std::endl;
    if(!not_found.empty()){
        Printer::print_list(not_found);
        std::cout << std::endl;
    }

    return not_found.empty();
}

/*===========================================================================================================================================================*/
/*===========================================================================================================================================================*/


void tools::Tools_Debug::print_Msg_ContainsNumbersOfWitness(AF &framework, const std::string& filePathWitness, const std::list<uint32_t>& arguments){

    if (checkContainsNumbersOfWitness(framework, filePathWitness, arguments)) {
        std::cout << "All numbers from the witness are present in the list of arguments." << std::endl;
    } else {
        std::cout << "Not all numbers from the witness are present in the list of arguments." << std::endl;
    }
}

/*===========================================================================================================================================================*/
/*===========================================================================================================================================================*/

static void test(const std::string& file_path, const std::list<uint32_t>& list_numbers)
{
    std::vector<int> numbersFromFile = get_numbers(file_path);
    std::list<uint32_t> not_found = get_list_not_contained_numbers(numbersFromFile, list_numbers); 

    if (not_found.empty()) {
        std::cout << "All numbers from the file are present in the list of numbers." << std::endl;
    } else {
        Printer::print_list(not_found);
        std::cout << std::endl;
        std::cout << "Not all numbers from the file are present in the list of numbers." << std::endl;
    }
}


void tools::Tools_Debug::test_witness_check(){
    std::string filePath = "/home/jsander/reducto/debug/test.txt";   // Path to the file
    
    // Test case 1
    std::list<uint32_t> arr_1 = {1, 2, 3, 4, 5};
    test(filePath, arr_1);
    // Test case 2
    std::list<uint32_t> arr_2 = {1, 2, 3, 4, 5, 6};
    test(filePath, arr_2);
    // Test case 3
    std::list<uint32_t> arr_3 = {1, 2, 3, 4, 5, 6, 7};
    test(filePath, arr_3);
    // Test case 4
    std::list<uint32_t> arr_4 = {1, 4, 5, 6, 7};
    test(filePath, arr_4);
}