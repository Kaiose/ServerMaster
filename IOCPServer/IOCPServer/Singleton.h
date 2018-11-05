/******************************************************************************
���ϸ�   : Singleton.h
����      : �̱��� ���� ����
�����   : public ����� �޾� ���
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