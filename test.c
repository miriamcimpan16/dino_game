#include <allegro5/allegro.h>

int main() {
    if (!al_init()) {
        return -1;
    }

    ALLEGRO_DISPLAY* display = al_create_display(800, 400);
    al_rest(2.0);  // Ține fereastra deschisă 2 secunde
    al_destroy_display(display);
    return 0;
}
