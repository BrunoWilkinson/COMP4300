#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

class ConfigManager
{
    std::string m_path;
    std::ifstream m_file_in;
    std::vector<std::string> m_config_data;

    void reset_file_stream();

public:
    ConfigManager(const std::string& path);
    const std::vector<std::string> get_config_data(const std::string& config_name);
};

#endif
