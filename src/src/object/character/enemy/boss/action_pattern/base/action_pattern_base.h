#pragma once
#include <memory>
#include "../../boss.h"
#include "../../../../../../camera/camera.h"

class ActionPattern
{
public:
	virtual void Init() = 0;
	virtual std::shared_ptr<ActionPattern> Action(std::shared_ptr<ActionPattern>&, Boss&,const float) = 0;
	virtual void Render() = 0;
	virtual void Destroy() = 0;
	virtual ~ActionPattern() {}
};