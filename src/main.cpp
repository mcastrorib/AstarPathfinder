// include CMake Configuration file
#include "pathfinder_config.h"

// include built-in PathFinder library
#include "PathFinder.h"

// Main Program
int main(int argc, char *argv[])
{        
    PathFinderApp *app;
    app = new PathFinderApp(IMAGEPATH);
    app->run();
    
    delete app;
    app = NULL;
    return 0;
}
