#pragma once

#include "../../external/plf_colony.h"
#include "Component.h"

#include <algorithm>

namespace BP_ECS
{
	struct ComponentList
	{
		virtual void remove(unsigned entity) = 0;
	};

	template<typename T>
	struct ComponentListTemplate : public ComponentList
	{
		plf::colony<pair<unsigned, T>> components;

		static ComponentListTemplate<T>* Instance()
		{
			static ComponentListTemplate<T>* instace = new  ComponentListTemplate<T>();

			return instace;
		}

		void remove(unsigned entity) final
		{
			auto it = find_if(components.begin(), components.end(), [entity](pair<unsigned, T>& elem) { return elem.first == entity; });

			components.erase(it);
		}

		template<typename... Args>
		void add(unsigned entity, Args... args) 
		{
			components.emplace(make_pair(entity, T(args...)));
		}

		T* get(unsigned entity)
		{
			for (pair<unsigned, T>& item : components)
			{
				if (item.first == entity)
				{
					return &item.second;
				}
			}

			return nullptr;
		}
	};
}