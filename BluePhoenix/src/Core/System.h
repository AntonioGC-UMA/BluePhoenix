#pragma once

#include "Entity.h"


namespace BP_ECS
{
	class Scene;

	struct System
	{
		static Scene scene;

		virtual void Tick() = 0;
		virtual bool filter(Entity* entity) = 0;
		virtual void addEntity(Entity* entity) = 0;
	};

	template<class ...Types>
	struct BaseSystem : public System
	{
		//std::vector<std::pair<unsigned, std::tuple<Types...>>> comp;
		std::vector<std::tuple<Types*...>> comp;


		/*Check components match*/
		bool filter(Entity* entity) override
		{
			return entity->has<Types...>();
		}

		/*Add entity to proces*/
		void addEntity(Entity* entity) final
		{
			comp.push_back(make_tuple(entity->get<Types>()...)); // TODO: Revisar como funciona esto, porque parece magia
		}
	};
}

