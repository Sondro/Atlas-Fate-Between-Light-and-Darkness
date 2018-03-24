#pragma once

#include "components/comp_base.h"
#include "entity/common_msgs.h"

class TCompTempPlayerController;

typedef void (TCompTempPlayerController::*actionfinish)();
typedef void (TCompTempPlayerController::*actionhandler)(float);

struct TMsgStateStart {
	
	actionhandler action_start;
	std::string meshname;
	float speed;
	float size;

	//TMsgSetFSMVariable message_start;

	DECL_MSG_ID();
};

struct TMsgStateFinish {

	actionfinish action_finish;
	std::string meshname;
	float speed;

	//TMsgSetFSMVariable message_finish;

	DECL_MSG_ID();
};

class TCompTempPlayerController : public TCompBase
{
	/* DEPRECATED */
	std::map<std::string, CRenderMesh*> mesh_states;

	physx::PxFilterData * pxPlayerFilterData;
	physx::PxFilterData * pxShadowFilterData;
	physx::PxQueryFilterData PxPlayerDiscardQuery;

	actionhandler state;
	CHandle current_camera;

	float mergeAngle = 0.45f;
	float currentSpeed = 4.f;
	float rotationSpeed = 10.f;
	float fallingTime = 0.f;
	float fallingDistance = 0.f;
	float maxFallingDistance = 12.f;

	/* Stamina private variables */
	float stamina = 100.f;
	const float minStamina = 0.f;
	const float maxStamina = 100.f;
	const float incrStamina = 15.f;
	const float decrStaticStamina = 0.75f;
	const float decrStaminaHorizontal = 12.5f;
	const float decrStaminaVertical = 17.5f;
	const float minStaminaChange = 15.f;

	void onStateStart(const TMsgStateStart& msg);
	void onStateFinish(const TMsgStateFinish& msg);
	void onCreate(const TMsgEntityCreated& msg);

	DECL_SIBLING_ACCESS();

public:

	bool isMerged;
	bool isGrounded;
	bool isInhibited;

	void debugInMenu();
	void renderDebug();
	void load(const json& j, TEntityParseContext& ctx);
	void update(float dt);

	/* State functions */
	void walkState(float dt);
	void idleState(float dt);
	void deadState(float dt);
	void mergeState(float dt);
	void resetState();

	/* Player condition tests */
	const bool concaveTest(void);
	const bool convexTest(void);
	const bool onMergeTest(float dt);
	const bool groundTest(float dt);

	/* Auxiliar functions */
	void updateStamina(float dt);
	void updateShader(float dt);

	static void registerMsgs();
};

