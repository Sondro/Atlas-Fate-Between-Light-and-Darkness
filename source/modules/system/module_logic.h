#pragma once

#include "modules/module.h"
#include "entity/entity.h"
#include <SLB/SLB.hpp>
#include "modules/system/module_game_console.h"
#include "modules/system/module_particles.h"
#include "modules/game/module_game_manager.h"
#include "input/button.h"
#include "components/player_controller/comp_player_tempcontroller.h"
#include "components/ia/comp_bt_patrol.h"
#include "components/comp_transform.h"
#include "components/comp_audio.h"
//#include "components/camera_controller/comp_camera_thirdperson.h"

class TCompCameraThirdPerson;
class TCompRender;
class TCompNoiseEmitter;
class TCompParticles;

class CModuleLogic : public IModule
{

public:

    struct ConsoleResult {
        bool success;
        std::string resultMsg;
    };

    struct DelayedScript {
        std::string script;
        float remainingTime;
    };

    struct CommandVariable {
        void* variable;
    };

    /* Enum with event id. Add as many as necessary */
    enum Events {
        GAME_START,
        GAME_END,
        SCENE_START,
        SCENE_END,
        TRIGGER_ENTER,
        TRIGGER_EXIT,
        PATROL_STUNNED,
        PATROL_KILLED,
        PLAYER_ON_SHADOW_ENTER,
        NUM_EVENTS
    };

    std::vector<std::string> log;
    std::map<int, std::string> _bindings;

    CModuleLogic(const std::string& aname) : IModule(aname) { }

    bool start() override;
    bool stop() override;
    void update(float delta) override;
    CModuleLogic* getPointer() { return this; }

    void execCvar(std::string& script);
    ConsoleResult execScript(const std::string& script);
    bool execScriptDelayed(const std::string& script, float delay);
    bool execSystemScriptDelayed(const std::string& script, float delay);
    bool execEvent(Events event, const std::string& params = "", float delay = 0.f);
    void printLog();
    void setPause(bool paused) { this->paused = paused; }
    void clearDelayedScripts();

private:

    SLB::Manager* m = new SLB::Manager;
    SLB::Script* s = new SLB::Script(m);

    std::vector<DelayedScript> delayedScripts;
    std::vector<DelayedScript> delayedSystemScripts;

    void BootLuaSLB();
    void publishClasses();
    void loadScriptsInFolder(char * path);

    bool started = false;
    bool paused = false;
};

/* Auxiliar functions */
CModuleGameConsole* getConsole();
CModuleLogic* getLogic();
CModuleGameManager * getGameManager();
CModuleParticles* getParticles();
TCompTempPlayerController* getPlayerController();
TCompNoiseEmitter* getPlayerNoiseEmitter();
void execDelayedScript(const std::string& script, float delay);
void execDelayedSystemScript(const std::string& script, float delay);
void pauseEnemies(bool pause);
void pauseEnemyEntities(bool pause);
void deleteEnemies();
bool isDebug();
void changeGamestate(const std::string& gamestate);
void pauseGame(bool pause);
void pausePlayerToggle();
void infiniteStamineToggle();
void immortal(bool state);
void inShadows();
void speedBoost(const float speed);
void playerInvisible();
void noClipToggle();
void lanternsDisable(bool disable);
void blendInCamera(const std::string& cameraName, float blendInTime, const std::string& mode = "cinematic", const std::string& interpolator = "");
void blendOutCamera(const std::string& cameraName, float blendOutTime);
void blendOutActiveCamera(float blendOutTime);
void resetMainCameras();
CHandle spawn(const std::string & name, const VEC3 & pos, const VEC3& lookat);
void move(const std::string & name, const VEC3 & pos, const VEC3& lookat);
void bind(const std::string& key, const std::string& script);
void loadscene(const std::string &level);
void unloadscene();
void loadCheckpoint();
void shadowsToggle();
void debugToggle();
void postFXToggle();
void renderNavmeshToggle();
void sleep(float time);
void cinematicModeToggle();
bool isCheckpointSaved();
void destroyHandle(unsigned int h);
void resetPatrolLights();
void animateSoundGraph(int value);

/* Sounds */
SoundEvent playEvent(const std::string& name);
void stopAllAudioComponents();

/* Tutorial */
void setTutorialPlayerState(bool active, const std::string& stateName);

/* Cinematic */
void setCinematicPlayerState(bool active, const std::string & stateName);
void setAIState(const std::string& name, bool active, const std::string & stateName);

/* GUI */
void unPauseGame();
void backFromControls();
void unlockDeadButton();
void execDeadButton();
void takeOutBlackScreen();
void goToMainMenu();
void takeOutCredits();
void takeOutControlsOnMainMenu();

/* DEBUG - TODO: Delete */
void sendOrderToDrone(const std::string& droneName, VEC3 position);
void toggle_spotlight(const std::string& lightName);
void toggleButtonCanBePressed(const std::string& buttonName, bool canBePressed);

// Extra cvar commands
void cg_drawfps(bool value);
void cg_drawlights(int type);

CEntity* toEntity(CHandle h);
TCompTransform* toTransform(CHandle h);
TCompAIPatrol* toAIPatrol(CHandle h);
TCompAudio* toAudio(CHandle h);
TCompCameraThirdPerson* toTPCamera(CHandle h);
TCompRender* toRender(CHandle h);
TCompParticles* toParticles(CHandle h);
