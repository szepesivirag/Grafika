#include "app.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    printf("Vezerles:\n");
    printf("W / S  - elore / hatra\n");
    printf("A / D  - balra / jobbra\n");
    printf("U / J  - fenyer novelese / csokkentese\n");
    printf("ESC    - kilepes\n\n");

    App app;

    init_app(&app, 800, 600);

    while (app.is_running) {
        handle_app_events(&app);
        update_app(&app);
        render_app(&app);
    }

    destroy_app(&app);

    return 0;
}