#pragma once
__interface IComponent
{
	virtual void FixedUpdate();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Delete();
};