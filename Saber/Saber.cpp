// Saber.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//
// faire caca sur le trottoir c rigolo mais c pas bo

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <iostream>
#include <stdbool.h>
#include "variablesGlobales.h"
#include "structures.h"

void menu(position*);


int main()
{
    al_init();
    al_install_keyboard();
    al_install_mouse();

    ALLEGRO_DISPLAY* display = al_create_display(LENGTH_SCREEN, HEIGHT_SCREEN);
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_FONT* font = al_create_builtin_font();

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    ALLEGRO_EVENT event;

    int width = al_get_display_width(display);
    int heigth = al_get_display_height(display);
    bool gameLoop = true;

    position mousePos;
    position characterPos;

    al_start_timer(timer);
    while (gameLoop)
    {
        al_wait_for_event(queue, &event);


        
        if (event.type == ALLEGRO_EVENT_TIMER) {
            menu(&mousePos);
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

    return 0;
}

void menu(position* mousePos) {
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());

    ALLEGRO_EVENT event;

    al_wait_for_event(queue, &event);

    if (event.type == ALLEGRO_EVENT_MOUSE_AXES) {
        mousePos->x = event.mouse.x;
        mousePos->y = event.mouse.y;


    }
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
