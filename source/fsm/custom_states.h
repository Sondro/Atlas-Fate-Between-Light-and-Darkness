#pragma once

#include "state.h"

namespace FSM
{
	class AnimationState : public IState
	{
		virtual void onStart(CContext& ctx) const override;
		virtual void onFinish(CContext& ctx) const override;
		virtual bool load(const json& jData);

	private:
		float _size = 1.f;
		float _speed = 1.f;
		std::string _animationName;
	};

	class FallState : public IState
	{
		virtual void onStart(CContext& ctx) const override;
		virtual void onFinish(CContext& ctx) const override;
		virtual bool load(const json& jData);

	private:
		float _force = 1.f;
		float _speed = 1.f;
		float _size = 1.f;
		std::string _animationName;
	};

	class WalkState : public IState
	{
		virtual void onStart(CContext& ctx) const override;
		virtual void onFinish(CContext& ctx) const override;
		virtual bool load(const json& jData);

	private:
		float _size = 1.f;
		float _speed = 1.f;
		float _rotation_speed = 1.f;
		std::string _animationName;
	};

	class RunState : public IState
	{
		virtual void onStart(CContext& ctx) const override;
		virtual void onFinish(CContext& ctx) const override;
		virtual bool load(const json& jData);

	private:
		float _size = 1.f;
		float _speed = 1.f;
		float _rotation_speed = 1.f;
		std::string _animationName;
	};

	class CrouchState : public IState
	{
		virtual void onStart(CContext& ctx) const override;
		virtual void onFinish(CContext& ctx) const override;
		virtual bool load(const json& jData);

	private:
		float _size = 1.f;
		float _speed = 1.f;
		float _rotation_speed = 1.f;
		std::string _animationName;
	};

	class EnterMergeState : public IState
	{
		virtual void onStart(CContext& ctx) const override;
		virtual void onFinish(CContext& ctx) const override;
		virtual bool load(const json& jData);

	private:
		float _size = 1.f;
		float _speed = 1.f;
		std::string _animationName;
	};

	class MergeState : public IState
	{
		virtual void onStart(CContext& ctx) const override;
		virtual void onFinish(CContext& ctx) const override;
		virtual bool load(const json& jData);

	private:
		float _size = 1.f;
		float _speed = 1.f;
		std::string _animationName;
	};

	class ExitMergeState : public IState
	{
		virtual void onStart(CContext& ctx) const override;
		virtual void onFinish(CContext& ctx) const override;
		virtual bool load(const json& jData);

	private:
		float _size = 1.f;
		float _speed = 1.f;
		std::string _animationName;
	};

	class LandMergeState : public IState
	{
		virtual void onStart(CContext& ctx) const override;
		virtual void onFinish(CContext& ctx) const override;
		virtual bool load(const json& jData);

	private:
		float _size = 1.f;
		float _speed = 1.f;
		std::string _animationName;
	};

	class AttackState : public IState
	{
		virtual void onStart(CContext& ctx) const override;
		virtual void onFinish(CContext& ctx) const override;
		virtual bool load(const json& jData);
	private:
		float _size = 1.f;
		float _speed = 2.f;
		std::string _animationName;
	};
}
