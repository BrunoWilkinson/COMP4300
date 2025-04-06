#include <cassert>
#include "ConfigManager.h"

ConfigManager::ConfigManager(const std::string& path, const std::vector<std::string>& list) : m_path(path)
{
    for (const std::string& config_name : list)
    {
	add_config_data(config_name);
    }
}

void ConfigManager::add_config_data(const std::string& config_name)
{
    std::fstream file;
    file.open(m_path);
    assert(file.is_open());

    std::vector<std::string> data;

    std::string token;
    bool is_data = false;
    while (file >> token)
    {
        if (token == config_name)
	{
	    is_data = true;
	    continue;
	}

	if (token == ";" && is_data)
	{
	    break;
	}
	
	if (is_data)
	{
	    data.push_back(token);
	}
    }

    m_config_data.insert({ config_name, data });
    file.close();
}

const std::vector<std::string>& ConfigManager::get_config_data(const std::string& config_name) const
{
    return m_config_data.find(config_name)->second;
}
