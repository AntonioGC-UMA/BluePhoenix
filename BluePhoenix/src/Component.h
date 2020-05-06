#pragma once

using namespace std;


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
