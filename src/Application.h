#include <vector>

class Module;
class ModuleRender;
class ModuleEditor;
class ModuleInput;

class Application
{
public:

    bool Init();
    bool Update();
    bool Clean();

    ModuleRender* m_render { nullptr };
    ModuleEditor* m_editor { nullptr };
    ModuleInput* m_input { nullptr };

private:

    std::vector<Module*> m_modules;

};