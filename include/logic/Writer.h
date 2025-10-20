#ifndef WRITER_H
#define WRITER_H

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <unordered_map>

#include "AF.h"

class Writer {

public:

    /// @brief Method to write a given abstract argumenation framework as a file in format .i23
    /// @param filename The path to the file to create
    /// @param framework The framework to save in the file.
    /// @param is_quiet_mode If set to 'true' there is no printouts to console
    /// @return 'true' iff the file was sucessfully saved.
    bool static write_af_to_i23(const std::string &filename, AF &framework, bool is_quiet_mode);

    /// @brief Method to write a given map as a file
    /// @param filename The path to the file to create
    /// @param map The map to save in the file.
    /// @param is_quiet_mode If set to 'true' there is no printouts to console
    /// @return 'true' iff the file was sucessfully saved.
    bool static write_map_to_file(const std::string &filename, std::map<uint32_t, uint32_t> &map, bool is_quiet_mode);

};
#endif