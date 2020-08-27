#include <vector>

class Module;
class ModuleRender;
class ModuleEditor;
class ModuleInput;
class ModulePhysics;

class Application
{
public:

    bool Init();
    bool Update();
    bool Clean();

    ModuleRender* m_Render { nullptr };
    ModuleEditor* m_Editor { nullptr };
    ModuleInput* m_Input { nullptr };
    ModulePhysics* m_Physics { nullptr };

    std::vector<Module*> m_Modules;

    float m_TotalTime = 0.f;
    float m_DeltaTime = 0.f;
};