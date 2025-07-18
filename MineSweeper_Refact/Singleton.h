#pragma once

template<typename T>
class SSingleton
{
protected:
	SSingleton() {}
	~SSingleton() {}

private:
	SSingleton(const SSingleton&) = delete;
	SSingleton& operator=(const SSingleton&) = delete;

public:
	static T& Instance()
	{
		static T instance;
		return instance;
	}
};