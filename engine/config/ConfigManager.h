#ifndef CONFIGMANAGER_H
#define CONFIGMANGER_H

#include <string>

/**
* TODO: make this class handle the config file in an arbitarty way
* meaning it should be able to read a json a return the data to given token
* /

class ConfigManager
{
    std::string m_path;
    std::ifstream m_fileIn;

	ConfigManager(const std::string& path);

    void ResetFileStream()
    {
        m_fileIn.clear();
        m_fileIn.seekg(0);
    }

	CreateData(const ConfigData& configData)
	{
        std::string token;
		while (m_fileIn >> token)
		{
			if (token == ConfigData.token)
			{
                m_fileIn >> 
			}
		}

		ResetFileStream();
	}
};
