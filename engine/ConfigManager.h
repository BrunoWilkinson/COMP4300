#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

typedef std::vector<std::string> config_data;

class ConfigManager
{
    std::string m_path;
    std::ifstream m_file_in;
    config_data m_config_data;

    void reset_file_stream();

public:
    ConfigManager(const std::string& path);
    config_data get_config_data(const std::string& config_name);
};

#endif
