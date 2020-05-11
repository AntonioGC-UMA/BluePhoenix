#pragma once

#include "Entity.h"
#include "ComponentList.h"

namespace BP_ECS
{
	class Scene;

	struct System
	{
		virtual void Tick() = 0;
		virtual bool filter(Entity* entity) = 0;
		virtual bool hasEntity(unsigned entity) = 0;
		virtual void addEntity(unsigned entity) = 0;
		virtual void removeEntity(unsigned entity) = 0;
	};

	template<class ...Types>
	struct BaseSystem : public System
	{
		std::vector<std::pair<unsigned, std::tuple<Types*...>>> comp;

		bool filter(Entity* entity) override
		{
			return entity->has<Types...>();
		}

		bool hasEntity(unsigned entity) final
		{
			return comp.end() != find_if(comp.begin(), comp.end(), [entity](auto& s) { return s.first == entity; });
		}

		void removeEntity(unsigned entity) final
		{
			auto it = find_if(comp.begin(), comp.end(), [entity](auto& s) { return s.first == entity; });

			comp.erase(it);
		}

		void addEntity(unsigned entity) final
		{		
			std::tuple<Types*...> temp = make_tuple(ComponentListTemplate<Types>::Instance()->get(entity)...);

			comp.push_back({ entity, temp });
		}
	};
}

