#pragma once
class Focusable
{
public:
	Focusable();
	~Focusable();

	virtual bool IsFocus() = 0;

	virtual void Focus() = 0;
	virtual void Blur() = 0;

	virtual bool TakeFocus(Focusable *requester) = 0;
};

