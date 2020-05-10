#pragma once

using namespace std;

namespace BP_ECS
{
	extern unsigned componentCounter;

	template<typename T>
	unsigned getType()
	{
		static unsigned type = -1;

		if (type == -1)
		{
			type = componentCounter++;
		}

		return type;
	}
}
