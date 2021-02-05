#pragma once

class App
{
public:
	virtual void init() = 0;
	virtual void update(const float& deltaTime) = 0;

	/* temporary */
	virtual void __render__() {}
};