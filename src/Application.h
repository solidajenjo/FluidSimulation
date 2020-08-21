#include <vector>

class Module;
class ModuleRender;
class ModuleEditor;

class Application
{
public:

    bool Init();
    bool Update();
    bool Clean();

    ModuleRender* render { nullptr };
    ModuleEditor* editor { nullptr };

private:

    std::vector<Module*> modules;

};