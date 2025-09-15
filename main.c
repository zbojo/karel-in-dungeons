#include "global.h"
#include "game_init.h"
#include "game.h"
#include "map_handler.h"
#include "utility.h"
#include "render.h"
#include "items.h"

int main(){

    if(checkRequirements() == 1 || checkRequirements() == 2){
        endwin();
        return 0;
    }

    int stats[STATS_SIZE], inventory[INVENTORY_SIZE], spells[SPELLS_SIZE];
    struct Item items[ITEMS_SIZE];
    prepareGame(stats, inventory, spells);
    prepareItems(items);
    mainScreen(stats, inventory, spells, items);

    endwin();
    return 0;
}