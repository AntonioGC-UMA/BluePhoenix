#pragma once

#include <unordered_map>
#include <vector>
#include <algorithm>

#include "Component.h"

namespace BP_ECS
{
	class Entity
	{
	public:
		template<class... Types>
		bool has()
		{
			return (hasOne<Types>() && ...);
		}

		template<class T>
		bool hasOne()
		{
			auto index = getType<T>();
			return find(types.begin(), types.end(), index) != types.end();
		}

		void add(unsigned type)
		{
			types.push_back(type);
		}


		vector<unsigned> types;
	};	
}
