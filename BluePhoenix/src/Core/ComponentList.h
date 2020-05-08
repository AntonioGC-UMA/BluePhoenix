#pragma once

#include "../../external/plf_colony.h"
#include "Component.h"

namespace BP_ECS
{

	struct ComponentList
	{
		virtual void remove(Component*) = 0;

		virtual Component* add() = 0;
	};

	template<typename T>
	struct ComponentListTemplate : public ComponentList
	{
		plf::colony<T> components;

		void remove(Component* c) final
		{
			T* toRemove = dynamic_cast<T*>(c);
			auto it = components.get_iterator_from_pointer(toRemove);

			components.erase(it, ++it);
		}

		Component* add() final
		{
			auto a = components.insert(T());
			
			return &(*a);
		}
	};
}