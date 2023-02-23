#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <iostream>
#include <stdbool.h>
#include <allegro5/allegro_image.h>
#include "variablesGlobales.h"
#include "structures.h"

bool menu(position* mousePos, ALLEGRO_BITMAP* backgroundImage, ALLEGRO_BITMAP* playButtonImage, ALLEGRO_BITMAP* quitButtonImage, bool* gameLoop) {
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());

    position playButtonPos = {
        (LENGTH_SCREEN / 2) - (al_get_bitmap_width(playButtonImage) / 2),
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