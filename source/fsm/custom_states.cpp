#include "mcv_platform.h"
#include "custom_states.h"
#include "context.h"
#include "components/player_controller/comp_player_animator.h"
#include "components/player_controller/comp_player_tempcontroller.h"

//class TCompTempPlayerController;
//class TCompPlayerAnimator;
//
//typedef void (TCompTempPlayerController::*actionhandler)(float);
//typedef void (TCompPlayerAnimator::*animatonhandler)(float);

namespace FSM
{

	bool AnimationState::load(const json& jData){

		_animationName = jData["animation"];
		_speed = jData.value("speed", 4.f);
		_size = jData.value("size", 1.f);
		return true;
	}

	void AnimationState::onStart(CContext& ctx) const {

		//CEntity* e = ctx.getOwner();
		//e->sendMsg(TMsgAnimation{ _animationName });
		CEntity* e = ctx.getOwner();
		e->sendMsg(TMsgStateStart{ (actionhandler)&TCompTempPlayerController::idleState, "pj_idle", _speed, _size });
	}

	void AnimationState::onFinish(CContext& ctx) const {

	}

	bool WalkState::load(const json& jData) {

		_animationName = jData["animation"];
		_speed = jData.value("speed", 4.f);
		_size = jData.value("size", 1.f);
		_rotation_speed = jData.value("rotationSpeed", 10.f);

		return true;
	}

	void WalkState::onStart(CContext& ctx) const {

		// Send a message to the player controller
		//CEntity* e = ctx.getOwner();
		//e->sendMsg(TMsgAnimation{ "walk" });

		CEntity* e = ctx.getOwner();
		e->sendMsg(TMsgStateStart{ (actionhandler)&TCompTempPlayerController::walkState, "pj_walk", _speed, _size });
	}

	void WalkState::onFinish(CContext& ctx) const {

	}

	bool RunState::load(const json& jData) {

		_animationName = jData["animation"];
		_speed = jData.value("speed", 5.5f);
		_size = jData.value("size", 1.f);
		_rotation_speed = jData.value("rotationSpeed", 10.f);

		return true;
	}

	void RunState::onStart(CContext& ctx) const {

		// Send a message to the player controller
		//CEntity* e = ctx.getOwner();
		//e->sendMsg(TMsgAnimation{ "run" });

		CEntity* e = ctx.getOwner();
		e->sendMsg(TMsgStateStart{ (actionhandler)&TCompTempPlayerController::walkState, "pj_run", _speed, _size });
	}

	void RunState::onFinish(CContext& ctx) const {

	}

	bool FallState::load(const json& jData) {

		_force = jData.value("force", 1.f);
		_speed = jData.value("speed", 3.f);
		_size = jData.value("size", 1.f);
		_animationName = jData["animation"];
		return true;
	}

	void FallState::onStart(CContext& ctx) const {

		// Send a message to the player controller
		CEntity* e = ctx.getOwner();
		e->sendMsg(TMsgStateStart{ (actionhandler)&TCompTempPlayerController::walkState, "pj_fall", _speed, _size });
	}

	void FallState::onFinish(CContext& ctx) const {

	}


	bool CrouchState::load(const json& jData) {

		_animationName = jData["animation"];
		_speed = jData.value("speed", 3.f);
		_size = jData.value("size", 1.f);
		_rotation_speed = jData.value("rotationSpeed", 10.f);

		return true;
	}

	void CrouchState::onStart(CContext& ctx) const {

		// Send a message to the player controller
		//CEntity* e = ctx.getOwner();
		//e->sendMsg(TMsgAnimation{ "crouch" });

		CEntity* e = ctx.getOwner();
		e->sendMsg(TMsgStateStart{ (actionhandler)&TCompTempPlayerController::walkState, "pj_crouch", _speed, _size });
	}

	void CrouchState::onFinish(CContext& ctx) const {

	}

	bool EnterMergeState::load(const json& jData) {

		_animationName = jData["animation"];
		_speed = jData.value("speed", 3.f);
		_size = jData.value("size", 1.f);

		return true;
	}

	void EnterMergeState::onStart(CContext& ctx) const {

		// Send a message to the player controller
		//CEntity* e = ctx.getOwner();
		//e->sendMsg(TMsgAnimation{ "crouch" });

		CEntity* e = ctx.getOwner();
		e->sendMsg(TMsgStateStart{ (actionhandler)&TCompTempPlayerController::idleState, "pj_fall", _speed, _size });
	}

	void EnterMergeState::onFinish(CContext& ctx) const {

		CEntity* e = ctx.getOwner();
		e->sendMsg(TMsgStateFinish{ (actionfinish)&TCompTempPlayerController::mergeEnemy });
	}

	bool MergeState::load(const json& jData) {

		_animationName = jData["animation"];
		_speed = jData.value("speed", 3.f);
		_size = jData.value("size", 1.f);

		return true;
	}

	void MergeState::onStart(CContext& ctx) const {

		// Send a message to the player controller
		//CEntity* e = ctx.getOwner();
		//e->sendMsg(TMsgAnimation{ "crouch" });

		CEntity* e = ctx.getOwner();
		e->sendMsg(TMsgStateStart{ (actionhandler)&TCompTempPlayerController::mergeState, "pj_shadowmerge", _speed, _size });
	}

	void MergeState::onFinish(CContext& ctx) const {

		CEntity* e = ctx.getOwner();
		e->sendMsg(TMsgStateFinish{ (actionfinish)&TCompTempPlayerController::resetState });
		dbg("reset stated\n");
	}

	bool ExitMergeState::load(const json& jData) {

		_animationName = jData["animation"];
		_speed = jData.value("speed", 3.f);
		_size = jData.value("size", 1.f);

		return true;
	}

	void ExitMergeState::onStart(CContext& ctx) const {

		// Send a message to the player controller
		//CEntity* e = ctx.getOwner();
		//e->sendMsg(TMsgAnimation{ "crouch" });

		CEntity* e = ctx.getOwner();
		e->sendMsg(TMsgStateStart{ (actionhandler)&TCompTempPlayerController::idleState, "pj_fall", _speed, _size });

		// Disable the rigidbody so that we can handle our transition in air manually
	}

	void ExitMergeState::onFinish(CContext& ctx) const {

		//CEntity* e = ctx.getOwner();
		//e->sendMsg(TMsgStateFinish{ (actionfinish)&TCompTempPlayerController::resetState });
		// Re enable rigidbody.
	}


	bool LandMergeState::load(const json& jData) {

		_animationName = jData["animation"];
		_speed = jData.value("speed", 2.f);
		_size = jData.value("size", 1.f);

		return true;
	}

	void LandMergeState::onStart(CContext& ctx) const {

		CEntity* e = ctx.getOwner();
		e->sendMsg(TMsgStateStart{ (actionhandler)&TCompTempPlayerController::idleState, "pj_fall", _speed, _size });
	}
	void LandMergeState::onFinish(CContext& ctx) const {

	}


	bool AttackState::load(const json& jData) {

		_animationName = jData["animation"];
		_speed = jData.value("speed", 2.f);
		_size = jData.value("size", 1.f);
		return true;
	}

	void AttackState::onStart(CContext& ctx) const {

		CEntity* e = ctx.getOwner();
		e->sendMsg(TMsgStateStart{ (actionhandler)&TCompTempPlayerController::walkState, "pj_attack", _speed, _size });
	}
	void AttackState::onFinish(CContext& ctx) const {

	}

	bool RemoveInhibitor::load(const json& jData) {

		_animationName = jData["animation"];
		_speed = jData.value("speed", 2.f);
		_size = jData.value("size", 1.f);
		return true;
	}

	void RemoveInhibitor::onStart(CContext& ctx) const {

		CEntity* e = ctx.getOwner();
		e->sendMsg(TMsgStateStart{ (actionhandler)&TCompTempPlayerController::idleState, "pj_idle", _speed, _size });
	}

	void RemoveInhibitor::onFinish(CContext& ctx) const {

	}

	bool DeadState::load(const json& jData) {

		_animationName = jData["animation"];
		_speed = jData.value("speed", 2.f);
		_size = jData.value("size", 1.f);
		return true;
	}

	void DeadState::onStart(CContext& ctx) const {

		CEntity* e = ctx.getOwner();
		e->sendMsg(TMsgStateStart{ (actionhandler)&TCompTempPlayerController::deadState, "pj_fall", _speed, _size });
	}
	void DeadState::onFinish(CContext& ctx) const {

	}

}