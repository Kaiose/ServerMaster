#pragma once


#define clock Clock::getInstance()

class Clock : public Singleton<Clock> {
	Clock();

	friend Singleton;
public:
	
	std::string		className;
	
	~Clock();


	tm GetTime();
};

