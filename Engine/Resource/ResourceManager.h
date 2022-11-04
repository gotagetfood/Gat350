#pragma once
#include "Resource.h"
#include "Core/Utilities.h"
#include <map>
#include <vector>
#include <string>
#include <memory>
#include <cstdarg>

namespace neu
{
	class ResourceManager
	{
	public:
		ResourceManager() = default;
		~ResourceManager() = default;

		void Initialize();
		void Shutdown();

		template <typename T, typename ... TArgs>
		std::shared_ptr<T> Get(const std::string& name, TArgs... args);

		template <typename T>
		std::vector<std::shared_ptr<T>> Get();

	private:
		std::map<std::string, std::shared_ptr<Resource>> m_resources;
	};

	template<typename T, typename ... TArgs>
	inline std::shared_ptr<T> ResourceManager::Get(const std::string& name, TArgs... args)
	{
		std::string lowerName = ToLower(name);
		if (m_resources.find(lowerName) != m_resources.end())
		{
			// found
			return std::dynamic_pointer_cast<T>(m_resources[lowerName]);
		}
		else
		{
			// not found, create resource and enter into resources
			std::shared_ptr<T> resource = std::make_shared<T>();
			resource->Create(lowerName, args...);
			m_resources[lowerName] = resource;

			return resource;
		}
	}

	template <typename T>
	inline std::vector<std::shared_ptr<T>> ResourceManager::Get()
	{
		std::vector<std::shared_ptr<T>> result;

		for (auto& resource : m_resources)
		{
			// get the value of the map (first = key, second = value)
			// the value is a shared_ptr, get() the raw pointer and try to cast to type T*
			if (dynamic_cast<T*>(resource.second.get()))
			{
				// if it is of type T, add the shared pointer to the vector
				result.push_back(std::dynamic_pointer_cast<T>(resource.second));
			}
		}

		return result;
	}
}




// vector [#,#,#,#] -> [#,#,#,#,#,#] 
// [4] [#,#,#,#] :(
// list [#] --> [#] ---> [#] 

// map <key, data>
// [key] -> data
// [key] -> data
// [key] -> data
// [key] -> data