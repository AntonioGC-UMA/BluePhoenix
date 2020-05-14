#pragma once

#ifndef TAM
	#define TAM 64
#endif

#include <unordered_map>
#include <bitset>
#include <vector>
#include <iostream>


#include "ComponentList.h"


namespace ecs
{
	using namespace std;

	typedef  uint32_t Entity;
	typedef  bitset<TAM> Key;

	struct System
	{
		virtual void Tick() = 0;
		virtual bool filtrar(Key k) = 0;
		virtual bool hasEntity(Entity entity) = 0;
		virtual void addEntity(Entity entity) = 0;
		virtual void removeEntity(Entity entity) = 0;
	};

	static Key contC = 2;


	template <typename T>
	Key getCode()
	{
		static Key k = 0;

		if (k == 0)
		{
			k = contC;
			contC <<= 1;
		}

		return k;
	}

	template <typename... T>
	Key getKey()
	{
		return (Key(0) | ... | getCode<T>());
	}


	struct Scene
	{
	private:

		Entity contE = 0;		
		unsigned contS = 0;
		unordered_map<Entity, Key> entities;
		unordered_map<Key, ComponentList*> compList;
		vector<System*> systems;
		vector<System*> activeSystems;

	public:

		void Tick();

		unsigned addSystem(System* s);		

		void activateSystem(unsigned pos);

		void deactivateSystem(unsigned pos);

		Entity createEntity();

		void destroyEntity(Entity ent);

		template<typename T>
		void addComponent(Entity ent, T comp)
		{
			Key k = getCode<T>();

			ComponentListTemplate<T>* list = ComponentListTemplate<T>::Instance();

			auto item = compList.find(k);

			if (item == compList.end())
			{
				compList.insert({ k , list });
			}

			list->add(ent, comp);

			Key entK = (entities.at(ent) |= k);

			for (auto item : systems)
			{
				if (item->filtrar(entK)  && !item->hasEntity(ent))
					item->addEntity(ent);
			}
		}

		template <typename T>
		T* getComponent(Entity ent)
		{
			Key k = getCode<T>();
			auto item = entities.find(ent);
			if (item != entities.end())
			{
				if ((item->second & k) != 0)
				{
					return ComponentListTemplate<T>::Instance()->get(ent);
				}				
			}

			cerr << "ERROR: No se ha encontrado el compnente" << endl;

			return nullptr;
		}

		template <typename T>
		void removeComponent(Entity ent)
		{
			Key k = getCode<T>();
			Key entK = (entities.at(ent) ^= k);

			ComponentListTemplate<T>::Instance()->remove(ent);

			for (auto item : systems)
			{
				if (!item->filtrar(entK) && item->hasEntity(ent))
					item->removeEntity(ent);
			}
		}
				

	};


	template<class ...Types>
	struct BaseSystem : public System
	{
		std::vector<std::pair<Entity, std::tuple<Types*...>>> comp;

		bool hasEntity(Entity entity) final
		{
			return comp.end() != find_if(comp.begin(), comp.end(), [entity](auto& s) { return s.first == entity; });
		}

		bool filtrar(Key k) override
		{
			Key myKey = getKey<Types...>();
			return (myKey & k) == myKey;
		}

		void removeEntity(Entity entity) final
		{
			auto it = find_if(comp.begin(), comp.end(), [entity](auto& s) { return s.first == entity; });

			comp.erase(it);
		}

		void addEntity(Entity entity) final
		{
			std::tuple<Types*...> temp = make_tuple(ComponentListTemplate<Types>::Instance()->get(entity)...);

			comp.push_back({ entity, temp });
		}
	};
}