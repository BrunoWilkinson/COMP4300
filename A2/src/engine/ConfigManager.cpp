#include "ConfigManager.h"

void ConfigManager::reset_file_stream()
{
    m_file_in.clear();
    m_file_in.seekg(0);
}

ConfigManager::ConfigManager(const std::string& path)
    : m_path(path)
    , m_file_in(std::ifstream(path))
{}

const std::vector<std::string> ConfigManager::get_config_data(const std::string& config_name)
{
    m_config_data.clear();
    reset_file_stream();

    std::string token;
    bool is_data = false;

    while (m_file_in >> token)
    {
        if (token == config_name)
	{
	    is_data = true;
	    continue;
	}
	else if (token == ";" && is_data)
	{
	    break;
	}
	
	if (is_data)
	{
	    m_config_data.push_back(token);
	}
    }

    return m_config_data;
}

