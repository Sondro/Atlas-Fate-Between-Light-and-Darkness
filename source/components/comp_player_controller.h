#pragma once

#include "comp_base.h"
#include "geometry/transform.h"
#include "ia/ai_controller.h"
#include "entity/common_msgs.h"

class TCompPlayerController : public IAIController {

	/* Attributes */

	float stamina = 100.f;
	float maxStamina = 100.f;
	float minStamina = 0.f;
	float dcrStaminaOnPlaceMultiplier = 0.5f;
	float dcrStaminaGround = 0.02f;
	float dcrStaminaWall = 0.08f;
	float incrStamina = 0.5f;

	float walkSpeedFactor = 1.0f;
	float runSpeedFactor = 2.0f;
	float walkSlowSpeedFactor = 0.5f;
	float rotationSpeed = 1.0f;
	VEC3  speed;

  /* Timers */

  /* Keys */
  const Input::TButton& btUp = EngineInput["btUp"];
  const Input::TButton& btDown = EngineInput["btDown"];
  const Input::TButton& btRight = EngineInput["btRight"];
  const Input::TButton& btLeft = EngineInput["btLeft"];
  const Input::TButton& btShadowMerging = EngineInput["btShadowMerging"];
  const Input::TButton& btAttack = EngineInput["btAttack"];
  const Input::TButton& btRun = EngineInput["btRun"];
  const Input::TButton& btSlow = EngineInput["btSlow"];
  const Input::TButton& btAction = EngineInput["btAction"];
  /* TODO: not for milestone 1 */
  //const Input::TButton& btCrouch = EngineInput["w"];	
  //const Input::TButton& btSecAction = EngineInput["w"];




  DECL_SIBLING_ACCESS();

  void onMsgDamage(const TMsgDamage& msg);

  /* Private aux functions */
  bool motionButtonsPressed();
  void movePlayer(float);

public:
  void debugInMenu();
  void load(const json& j, TEntityParseContext& ctx);
  //void update(float dt);
  void Init();
  
  static void registerMsgs();

  /* States */
  void IdleState(float);
  void MotionState(float);	//Movement
  void PushState(float);
  void AttackState(float);
  void ProbeState(float);
  void RemovingInhibitorState(float);
  void ShadowMergingEnterState(float);
  void ShadowMergingHorizontalState(float);
  void ShadowMergingVerticalState(float);
  void ShadowMergingEnemyState(float);
  void ShadowMergingLandingState(float);
  void ShadowMergingExitState(float);
  void FallingState(float);
  void LandingState(float);
  void HitState(float);
  void DeadState(float);

  bool checkShadows();
};