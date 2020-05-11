#pragma once

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
			return (true && ... && hasOne(getType<Types>()));
		}

		bool hasOne(unsigned type)
		{
			return find(types.begin(), types.end(), type) != types.end();
		}

		void add(unsigned type)
		{
			types.push_back(type);
		}


		vector<unsigned> types;
	};	
}
