#pragma once

#include <cstdlib>
#include <iostream>
#include "exoModule.h"


class exoMotor
{
public:

	exoMotor(std::string Name, exoModule& module);

	void SetPWM(uint8_t pwm);
	void SetDirection(uint8_t INA, uint8_t INB);

	std::string GetName();

	~exoMotor();

private:

	std::string name_;
	exoModule& module_;

	uint8_t PWM_Handle;
	uint8_t INA_Handle;
	uint8_t INB_Handle;

};
