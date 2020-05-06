#pragma once

using namespace std;

namespace BP_ECS
{
	struct Component
	{
		unsigned type;

		virtual ~Component() = default;
	};

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

	template<typename T>
	Component* createComponent()
	{
		Component* c = new T();
		c->type = getType<T>();

		return c;
	}
}

/*
struct Component
{
private:
	static unsigned idCounter;

public:
	template<typename T> static unsigned setType();

	virtual unsigned getType() = 0;
};

template<typename T> 
struct BaseComponent : public Component
{
public:
	static unsigned type;

	unsigned getType() override
	{
		return type;
	}
};

template<typename T> 
unsigned BaseComponent<T>::type = Component::setType<T>();


template<typename T>
inline unsigned Component::setType()
{
	static int i = -1;

	if (i == -1)
	{
		i = idCounter++;
	}

	return i;
}
*/