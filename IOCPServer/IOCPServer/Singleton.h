/******************************************************************************
파일명   : Singleton.h
목적      : 싱글턴 패턴 생성
사용방식   : public 상속을 받아 사용
******************************************************************************/
#pragma once

template<class T>
class Singleton
{
private:

protected:
	Singleton(const Singleton&) = delete;
	Singleton(const Singleton&&) = delete;
	Singleton& operator = (const Singleton&) = delete;
	Singleton& operator = (const Singleton&&) = delete;

	Singleton()
	{
	}
	virtual ~Singleton()
	{
	}

public:
	
	static T& getInstance()
	{	
		static T instance;
		return instance;
	}

};