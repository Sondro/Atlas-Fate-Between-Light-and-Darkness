#pragma once

#include "modules/module.h"

class CModuleMapTest : public IModule
{
	CHandle h_e_camera;

public:
	CModuleMapTest(const std::string& aname) : IModule(aname) { }
	bool start() override;
	bool stop() override;
	void update(float delta) override;
	void render() override;
};