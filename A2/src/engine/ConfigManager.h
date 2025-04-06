#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <string>
#include <fstream>
#include <vector>
#include <map>

class ConfigManager
{
    std::string m_path;
    std::map<std::string, std::vector<std::string>> m_config_data;

    void reset_file_stream();
    void add_config_data(const std::string& config_name);

public:
    ConfigManager(const std::string& path, const std::vector<std::string>& list);
    const std::vector<std::string>& get_config_data(const std::string& config_name) const;
};

#endif
