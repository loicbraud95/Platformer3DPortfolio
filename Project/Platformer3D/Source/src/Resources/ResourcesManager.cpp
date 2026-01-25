#include "ResourcesManager.h"
#include "Model.h"
#include "Log.h"

ResourceManager* ResourceManager::instance = nullptr;

ResourceManager::~ResourceManager()
{
    std::vector<std::string> lstName;

    for (auto it = resources.begin(); it != resources.end(); ++it)
    {
        lstName.push_back(it->first);
    }

    for (size_t i = 0; i < lstName.size(); i++)
        Delete(lstName[i]);

    lstName.clear();
}

ResourceManager& ResourceManager::Get()
{
    if (instance == nullptr)
        instance = new ResourceManager();
    return *instance;
}

void ResourceManager::Destroy()
{
    if (instance)
    {
        delete instance;
        instance = nullptr;
    }
}

bool ResourceManager::IsKeyInList(std::string name)
{
    auto it = resources.find(name);
    if (it == resources.end())
    {
        DEBUG_LOG("The resource : " + name + " doesn't exist.");
        return false;
    }
    else
    {
        return true;
    }
}

void ResourceManager::Delete(std::string name)
{
    if (IsKeyInList(name))
    {
        auto it = resources.find(name);
        it->second->UnLoad();
        resources.erase(it);
    }

}
std::string ResourceManager::GetExtension(std::string name)
{
    size_t index = name.find('.');
    std::string result = "";

    if (index < 0)
        DEBUG_LOG("No extension detected in name : " + name);
    else
    {
        for (size_t i = index; i < name.size(); i++)
            result += name[i];
    }
    return result;
}

bool ResourceManager::CheckExtension(std::string extension)
{
    if (extension == "")
    {
        return false;
    }
    else
    {
        for (int i = 0; i < nbExtensionKnow; i++)
        {
            if (lstExtension[i] == extension)
                return true;
        }

        return false;
    }
}
