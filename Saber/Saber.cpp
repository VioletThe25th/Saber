// Saber.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
// faire caca sur le trottoir c rigolo mais c pas bo

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <iostream>
#include <stdbool.h>
#include <allegro5/allegro_image.h>
#include "variablesGlobales.h"
#include "structures.h"

bool menu(position*, ALLEGRO_BITMAP*, ALLEGRO_BITMAP*, ALLEGRO_BITMAP*, bool*);


int main()
{
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();

    ALLEGRO_DISPLAY* display = al_create_display(LENGTH_SCREEN, HEIGHT_SCREEN);
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_FONT* font = al_create_builtin_font();

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    // Creates images
    ALLEGRO_BITMAP* backgroundImage = NULL;
    ALLEGRO_BITMAP* playButtonImage = NULL;
    ALLEGRO_BITMAP* quitButtonImage = NULL;

    // Load assets
    backgroundImage = al_load_bitmap("assets/background/menu_background.jpg");
    playButtonImage = al_load_bitmap("assets/buttons/jouerButton.png");
    quitButtonImage = al_load_bitmap("assets/buttons/quitButton.png");

    assert(backgroundImage != NULL);
    assert(playButtonImage != NULL);
    assert(quitButtonImage != NULL);

    ALLEGRO_EVENT event;

    int width = al_get_display_width(display);
    int heigth = al_get_display_height(display);
    bool gameLoop = true;
    bool isInMenu = true;

    position mousePos;
    position characterPos;

    al_start_timer(timer);
    while (gameLoop)
    {
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_TIMER) {
            printf("entering menu\n");
            if (isInMenu) {
          
                isInMenu = menu(&mousePos, backgroundImage, playButtonImage, quitButtonImage,&gameLoop);
            }
            // Refresh the screen
            al_flip_display();
        }
        

        // Close the window if a key is pressed or if the close button is clicked on
        else if ((event.type == ALLEGRO_EVENT_KEY_DOWN) || (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)) {
            gameLoop = false;
        }

    }

    al_destroy_font(font);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_uninstall_keyboard();
    al_uninstall_mouse();
    al_destroy_bitmap(backgroundImage);
    al_destroy_bitmap(playButtonImage);
    al_destroy_bitmap(quitButtonImage);

    return 0;
}

bool menu(position* mousePos, ALLEGRO_BITMAP* backgroundImage, ALLEGRO_BITMAP* playButtonImage, ALLEGRO_BITMAP* quitButtonImage, bool* gameLoop) {
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());

    position playButtonPos = {
        (LENGTH_SCREEN /2) - (al_get_bitmap_width(playButtonImage) / 2), 
        (HEIGHT_SCREEN / 2) - (al_get_bitmap_height(playButtonImage) / 2) 
    };
    position quitButtonPos = {
        (LENGTH_SCREEN / 2) - (al_get_bitmap_width(quitButtonImage) / 2),
        ((HEIGHT_SCREEN / 2) + 300) - (al_get_bitmap_height(quitButtonImage) / 2)
    };

    ALLEGRO_EVENT event;

    al_wait_for_event(queue, &event);

    if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
        mousePos->x = event.mouse.x;
        mousePos->y = event.mouse.y;

        //printf("mouse postion x : %f mouse position y : %f\n", mousePos->x, mousePos->y);

        if ((mousePos->x > playButtonPos.x && mousePos->x < (playButtonPos.x + al_get_bitmap_width(playButtonImage))
            && (mousePos->y > playButtonPos.y && mousePos->y < playButtonPos.y + al_get_bitmap_height(playButtonImage)))) {

            al_wait_for_event(queue, &event);

            if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                *gameLoop = false;
                printf("play\n");
                return false;
            }
        }

        else if ((mousePos->x > quitButtonPos.x && mousePos->x < (quitButtonPos.x + al_get_bitmap_width(quitButtonImage)) 
            && (mousePos->y > quitButtonPos.y && mousePos->y < quitButtonPos.y + al_get_bitmap_height(quitButtonImage))))
        {
            al_wait_for_event(queue, &event);

            if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                *gameLoop = false;
                printf("menu closed\n");
                return false;
            }
        }
    }

    al_draw_bitmap(backgroundImage, 0, 0, 0);
    al_draw_bitmap(playButtonImage, playButtonPos.x, playButtonPos.y, 0);
    al_draw_bitmap(quitButtonImage, quitButtonPos.x, quitButtonPos.y, 0);

    al_destroy_event_queue(queue);
   
    return true;
}


// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
