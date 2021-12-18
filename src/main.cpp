#include "main.h"


void mainloop(void *v)
{
    App *app = reinterpret_cast<App *>(v);
    app->BrowserGameLoop();
}

int main (int argc, char* argv[])
{
    App *app = App::GetApplication();
    app->initSDL();
    app->Initialize();
    #ifndef __EMSCRIPTEN__
        app->DesktopGameLoop();
        app->QuitGame();
        std::ofstream file;
        file.open("score.txt", std::ios_base::app);
        if (file)
        {
            file << app->GetScore() << std::endl;
        }
        file.close();
        delete app;
        app = NULL;
    #endif

    #ifdef __EMSCRIPTEN__
        emscripten_set_main_loop_arg(mainloop, reinterpret_cast<void*>(app) , 0, 0);
    #endif

    return 0;
}