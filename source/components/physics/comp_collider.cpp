#include "mcv_platform.h"
#include "comp_collider.h"
#include "components/comp_transform.h"
#include "components/player_controller/comp_player_controller.h"

DECL_OBJ_MANAGER("collider", TCompCollider);

void TCompCollider::debugInMenu() {

}

void TCompCollider::load(const json& j, TEntityParseContext& ctx) {

  std::string shape = j["shape"].get<std::string>();
  if (strcmp("box", shape.c_str()) == 0)
  {
    config.shapeType = physx::PxGeometryType::eBOX;
  }
  else if (strcmp("sphere", shape.c_str()) == 0)
  {
    config.shapeType = physx::PxGeometryType::eSPHERE;
  }
  else if (strcmp("plane", shape.c_str()) == 0)
  {
    config.shapeType = physx::PxGeometryType::ePLANE;
  }
  else if (strcmp("capsule", shape.c_str()) == 0)
  {
    config.shapeType = physx::PxGeometryType::eCAPSULE;
  }
  else if (strcmp("convex", shape.c_str()) == 0)
  {
	  config.shapeType = physx::PxGeometryType::eCONVEXMESH;
  }
  else if (strcmp("mesh", shape.c_str()) == 0)
  {
	  config.shapeType = physx::PxGeometryType::eTRIANGLEMESH;
  }

  config.is_controller = j.value("is_controller", false);
  config.is_dynamic = j.value("is_dynamic", false);
  config.is_trigger = j.value("is_trigger", false);
  config.height = j.value("height", 0.f);
  config.currentHeight = config.height;
  config.radius = j.value("radius", 0.f);
  config.gravity = j.value("gravity", false);
  config.filename = j.value("name", "");

  config.group = CEngine::get().getPhysics().getFilterByName(j.value("group", "all"));
  config.mask = CEngine::get().getPhysics().getFilterByName(j.value("mask", "all"));

  if (j.count("halfExtent"))
    config.halfExtent = loadVEC3(j["halfExtent"]);

  // Setting some default values.
  isInside = false;
  isGrounded = false;
}


void TCompCollider::registerMsgs() {

  DECL_MSG(TCompCollider, TMsgEntityCreated, onCreate);
  DECL_MSG(TCompCollider, TMsgTriggerEnter, onTriggerEnter);
  DECL_MSG(TCompCollider, TMsgTriggerExit, onTriggerExit);
  DECL_MSG(TCompCollider, TMsgEntityDestroyed, onDestroy);
}

void TCompCollider::onCreate(const TMsgEntityCreated& msg) {

  CEngine::get().getPhysics().createActor(*this);
  TCompTransform *transform = get<TCompTransform>();
  lastFramePosition = transform->getPosition();
}

void TCompCollider::onDestroy(const TMsgEntityDestroyed & msg)
{
	if(actor && actor->getScene())
		actor->getScene()->removeActor(*actor);
		actor = nullptr;
	if (controller != NULL && controller) {
		controller->release();
		controller = nullptr;
	}
}

void TCompCollider::onTriggerEnter(const TMsgTriggerEnter& msg) {

	dbg("Entered the trigger!!!!\n");
}

void TCompCollider::onTriggerExit(const TMsgTriggerExit& msg) {

	dbg("Exited the trigger!!!!\n");
}

void TCompCollider::update(float dt) {

	if (config.is_controller) {
		if (CHandle(this).getOwner().isValid()) {
			TCompTransform *transform = get<TCompTransform>();
			VEC3 new_pos = transform->getPosition();
			VEC3 delta_movement = new_pos - lastFramePosition;
			controller->move(physx::PxVec3(delta_movement.x, delta_movement.y, delta_movement.z), 0.f, dt, physx::PxControllerFilters());
			lastFramePosition = new_pos;
		}
	}

	if (config.gravity) {

		//velocity += normal_gravity;
		physx::PxControllerCollisionFlags col = controller->move(physx::PxVec3(normal_gravity.x * dt, normal_gravity.y * dt, normal_gravity.z * dt), 0.f, dt, physx::PxControllerFilters());
		isGrounded = col.isSet(physx::PxControllerCollisionFlag::eCOLLISION_DOWN) ? true : false;
	}
}

void TCompCollider::Resize(float new_size)
{
	config.currentHeight = new_size;
	controller->resize((physx::PxReal)new_size);
}

void TCompCollider::SetUpVector(VEC3 new_up)
{
	controller->setUpDirection(physx::PxVec3(new_up.x, new_up.y, new_up.z));
}

VEC3 TCompCollider::GetUpVector()
{
	physx::PxVec3 upDirection = controller->getUpDirection();
	return VEC3(upDirection.x,upDirection.y,upDirection.z);
}
