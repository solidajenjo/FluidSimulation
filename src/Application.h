#include <vector>

class Module;
class ModuleRender;

class Application
{
public:

    bool Init();
    bool Update();
    bool Clean();

    ModuleRender* render { nullptr };

private:

    std::vector<Module*> modules;

};