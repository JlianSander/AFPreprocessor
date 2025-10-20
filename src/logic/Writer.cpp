#include "../../include/logic/Writer.h"
using namespace std;

/*===========================================================================================================================================================*/
/*===========================================================================================================================================================*/

bool Writer::write_af_to_i23(const std::string &filename, AF &framework, bool is_quiet_mode){
    std::ofstream file(filename);

    if (!file) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return false;
    }

    // Write the header
    file << "p af "<< framework.num_args  << "\n";

    // Write the attacks
    for (const auto &pair : framework.attacks) {
        file << pair.first << " " << pair.second << "\n";
    }

    file.close();
    if(!is_quiet_mode)
    {
        std::cout << "File written successfully to " << filename << std::endl;
    }
    
    return true;
}

/*===========================================================================================================================================================*/
/*===========================================================================================================================================================*/

bool Writer::write_map_to_file(const std::string &filename, std::map<uint32_t, uint32_t> &map, bool is_quiet_mode){
    std::ofstream file(filename);
    
    if (!file) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return false;
    }

    // Write the pairs
    for (const auto &pair : map) {
        file << pair.first << " " << pair.second << "\n";
    }

    file.close();
    if(!is_quiet_mode)
    {
        std::cout << "File written successfully to " << filename << std::endl;
    }
    
    return true;
}