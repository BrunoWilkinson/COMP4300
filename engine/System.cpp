#include "System.h"

System::System(const std::string& name)
    : m_name(name)
{}

void System::update()
{}

void System::set_enabled(const bool enabled)
{
    m_enabled = enabled;
}
