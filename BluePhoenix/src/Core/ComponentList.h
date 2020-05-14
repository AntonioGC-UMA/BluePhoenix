#pragma once

#include "../../external/plf_colony.h"

#include <algorithm>

using namespace std;

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

	void add(unsigned entity, T comp) 
	{
		components.insert({ entity, comp });
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
