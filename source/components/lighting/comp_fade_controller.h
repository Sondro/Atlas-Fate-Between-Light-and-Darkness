#pragma once

#include "../comp_base.h"
#include "../comp_camera.h"

class TCompFadeController : public TCompBase {

    bool _is_active;
	VEC4 _fade_color;
    std::string _material;

	float _elapsed_time = 0.f;
	float _fade_time;
    float _fall_speed;

	DECL_SIBLING_ACCESS();

public:

	void debugInMenu();
	void load(const json& j, TEntityParseContext& ctx);
	void update(float dt);

	void launch(void);
    void destroy(void);
};