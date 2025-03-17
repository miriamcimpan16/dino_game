#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 400
#define BACKGROUND_SPEED 2  // Viteza de mișcare a fundalului
#define FRAME_RATE 60        // FPS

int main() {
  al_init();
    // Inițializare Allegro
    if (!al_init()) {
        printf("Eroare la inițializarea Allegro!\n");
        return -1;
    }
    al_init_image_addon();
    al_init_primitives_addon();

    // Creare fereastră
    ALLEGRO_DISPLAY* display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!display) {
        printf("Eroare la crearea ferestrei!\n");
        return -1;
    }

    // Creare coadă de evenimente și timer
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / FRAME_RATE);

    // Încărcare imagini
    ALLEGRO_BITMAP* background = al_load_bitmap("back.png");
    ALLEGRO_BITMAP* dino = al_load_bitmap("dinosaur.png");

    if (!background || !dino) {
        printf("Eroare la încărcarea imaginilor! Verifică dacă fișierele există.\n");
        return -1;
    }

    // Înregistrare evenimente
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    // Variabile pentru poziție
    int background_x = 0;
    int dino_width = al_get_bitmap_width(dino);
    int dino_height = al_get_bitmap_height(dino);
    float scale_factor = 0.2;
    int new_dino_width = dino_width * scale_factor;
    int new_dino_height = dino_height * scale_factor;
     int dino_x = 50;  // Mai aproape de marginea din stânga
    int dino_y = SCREEN_HEIGHT - new_dino_height - 50; // La bază
    bool running = true;

    al_start_timer(timer);  // Pornire timer

    // Buclă principală
    while (running) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            running = false;
        } else if (event.type == ALLEGRO_EVENT_TIMER) {
            // Mișcare fundal
            background_x -= BACKGROUND_SPEED;
            if (background_x <= -SCREEN_WIDTH) {
                background_x = 0;
            }

            // Desenare
            al_clear_to_color(al_map_rgb(255, 255, 255));
            al_draw_bitmap(background, background_x, 0, 0);
            al_draw_bitmap(background, background_x + SCREEN_WIDTH, 0, 0);
           al_draw_scaled_bitmap(dino, 
        0, 0, dino_width, dino_height,  // Dimensiuni originale
        dino_x, dino_y, new_dino_width, new_dino_height, // Poziție și dimensiune nouă
        0);

            al_flip_display();
        }
    }

    // Eliberare memorie
    al_destroy_bitmap(background);
    al_destroy_bitmap(dino);
    al_destroy_display(display);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);

    return 0;
}
