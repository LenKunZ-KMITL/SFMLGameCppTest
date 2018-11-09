#pragma once
#include <memory>

#include "EventListener.h"

typedef struct ControlDrawEventArgs {
} ControlDrawEventArgs;

class ControlDrawEvent :
	public EventListener<ControlDrawEventArgs>
{
public:
	ControlDrawEvent();
	~ControlDrawEvent();
};

