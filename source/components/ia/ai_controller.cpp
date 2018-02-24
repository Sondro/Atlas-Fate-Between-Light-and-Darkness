#include "mcv_platform.h"
#include "components/comp_transform.h"
#include "ai_controller.h"

TCompTransform* IAIController::getMyTransform() {
  TCompTransform* c = h_transform;
  if (!c) {
    CEntity* e = h_entity;
    assert(e);
    h_transform = e->get< TCompTransform >();
    assert(h_transform.isValid());
    c = h_transform;
  }
  return c;
}

// Show common information for the AIControllers
void IAIController::debugInMenu() {
  ImGui::Text("State: %s", stateName.c_str());
  if (ImGui::TreeNode("States")) {
    for (auto it = statemap.begin(); it != statemap.end(); ++it)
      ImGui::Text("%s", it->first.c_str());
    ImGui::TreePop();
  }
}

void IAIController::update(float dt)
{
	if (!paused) {
		assert(!stateName.empty());
		assert(statemap.find(stateName) != statemap.end());
		// this is a trusted jump as we've tested for coherence in ChangeState
		(this->*state)(dt);
	}

	if (btDebugPause.getsPressed()) {
		paused = !paused;
	}
}

void IAIController::ChangeState(const std::string& newstate)
{
  // try to find a state with the suitable name
  if (statemap.find(newstate) == statemap.end())
  {
    // the state we wish to jump to does not exist. we abort
    fatal("Invalid ChangeState(%s)\n", newstate.c_str());
  }
  stateName = newstate;
  state = statemap[stateName];
}


void IAIController::AddState(const std::string& name, statehandler sh)
{
  // try to find a state with the suitable name
  if (statemap.find(name) != statemap.end())
  {
    //TODO: 
    //fatal("Invalid AddState(%s). Already defined.\n", name.c_str());
  }
  else {
	statemap[name] = sh;
  }
}

void IAIController::setEntity(CHandle new_entity) {
  h_entity = new_entity;
  assert(h_entity.isValid());
}

const std::string IAIController::getStateName() {
	return stateName;
}
