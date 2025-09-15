#include "global.h"
#include "game_init.h"
#include "game.h"
#include "map_handler.h"
#include "utility.h"
#include "render.h"

void printDungeon(struct DungeonEntity dungeon[DUNGEON_HEIGHT][DUNGEON_WIDTH]){
    clear();
    //spawnInfo();
    printAsciTitleArt();
    for(int i = 0; i < DUNGEON_HEIGHT; i++){
        for(int j = 0; j < DUNGEON_WIDTH; j++){
            attron(COLOR_PAIR(dungeon[i][j].color_id));
            if(dungeon[i+1][j].id == MINEABLE_STONE_ID || dungeon[i+1][j].id == STONE_ID){
                mvprintw(OFFSET_TOP+i * 2 + 1, j * 3 + PADDING_LEFT, "   ");
            }
            if(dungeon[i][j].id == SHOP_ID){
                mvprintw(OFFSET_TOP+i*2-1, j * 3 + PADDING_LEFT, " $ ");
                mvprintw(OFFSET_TOP+i*2+1 * 2, j * 3 + PADDING_LEFT, " $ ");
                mvprintw(OFFSET_TOP+i*2+2, j * 3 + PADDING_LEFT, " $ ");
                mvprintw(31, j * 3 + PADDING_LEFT, " $ ");
            }
            mvprintw(OFFSET_TOP+i * 2, j * 3 + PADDING_LEFT, "%c%c%c", dungeon[i][j].render[0], dungeon[i][j].render[1], dungeon[i][j].render[2]);
            attroff(COLOR_PAIR(dungeon[i][j].color_id));
        }
    }
    refresh();
}

void printLayout(int color_dungeon_border, int color_inventory_border, int color_stats_border, int color_spells_border){
    printDungeonBorder(color_dungeon_border);
    printInventoryBorder(color_inventory_border);
    printStatsBorder(color_stats_border);
    printSpellsBorder(color_spells_border);
}

void printData(int stats[STATS_SIZE], int inventory[INVENTORY_SIZE], int spells[SPELLS_SIZE], struct Item items[ITEMS_SIZE]){
    printInventoryContent(inventory, items);
    printStatsContent(stats);
    printSpellsContent(spells);
}

void printDungeonBorder(int color_dungeon_border){
    attron(COLOR_PAIR(color_dungeon_border));
    for(int i = 0; i < DUNGEON_WIDTH * 3+4; i++){
        mvprintw(OFFSET_TOP-1, i+PADDING_LEFT-2, " ");
        mvprintw(OFFSET_TOP-1+DUNGEON_HEIGHT * 2, i+PADDING_LEFT-2, " ");
    }
    for(int i = 0; i < DUNGEON_HEIGHT*2; i++){
        mvprintw(i+OFFSET_TOP, PADDING_LEFT-2, "  ");
        mvprintw(i+OFFSET_TOP, DUNGEON_WIDTH*3+PADDING_LEFT, "  ");
    }
    attroff(COLOR_PAIR(color_dungeon_border));
}

void printInventoryBorder(int color_inventory_border){
    attron(COLOR_PAIR(color_inventory_border));
    for(int i = 0; i < 41; i++){
        mvprintw(OFFSET_TOP-1, i + DUNGEON_WIDTH*3 + 15, " ");
        mvprintw(OFFSET_TOP+6, i + DUNGEON_WIDTH*3 + 15, " ");
    }
    for(int i = 0; i < 7; i++){
        mvprintw(i+OFFSET_TOP, DUNGEON_WIDTH*3 + 15, " ");
        mvprintw(i+OFFSET_TOP, DUNGEON_WIDTH*3 + 55, " ");
    }
    attroff(COLOR_PAIR(color_inventory_border));
}

void printStatsBorder(int color_stats_border){
    attron(COLOR_PAIR(color_stats_border));
    for(int i = 0; i < 41; i++){
        mvprintw(OFFSET_TOP+24, i + DUNGEON_WIDTH*3 + 15, " ");
        mvprintw(OFFSET_TOP+8+24, i + DUNGEON_WIDTH*3 + 15, " ");
    }
    for(int i = 0; i < 8; i++){
        mvprintw(i+OFFSET_TOP+25, DUNGEON_WIDTH*3 + 15, " ");
        mvprintw(i+OFFSET_TOP+25, DUNGEON_WIDTH*3 + 55, " ");
    }
    attroff(COLOR_PAIR(color_stats_border));
}

void printSpellsBorder(int color_spells_border){
    attron(COLOR_PAIR(color_spells_border));
    for(int i = 0; i < 41; i++){
        mvprintw(OFFSET_TOP-1+12, i + DUNGEON_WIDTH*3 + 15, " ");
        mvprintw(OFFSET_TOP+7+12, i + DUNGEON_WIDTH*3 + 15, " ");
    }
    for(int i = 0; i < 8; i++){
        mvprintw(i+OFFSET_TOP+12, DUNGEON_WIDTH*3 + 15, " ");
        mvprintw(i+OFFSET_TOP+12, DUNGEON_WIDTH*3 + 55, " ");
    }
    attroff(COLOR_PAIR(color_spells_border));
}

void printInventoryContent(int inventory[INVENTORY_SIZE], struct Item items[ITEMS_SIZE]){
    mvprintw(OFFSET_TOP+1, DUNGEON_WIDTH*3 + 17, "Inventory");
    for(int i = 0; i < INVENTORY_SIZE; i++){
        mvprintw(OFFSET_TOP+i+2, DUNGEON_WIDTH*3 + 19, "Slot %d:", i+1);
        if(items[inventory[i]].id == 0){
            mvprintw(OFFSET_TOP+i+2, DUNGEON_WIDTH*3 + 27, "Empty");
        }else{
            attron(COLOR_PAIR(items[inventory[i]].color));
            mvprintw(OFFSET_TOP+i+2, DUNGEON_WIDTH*3 + 27, "%s", items[inventory[i]].id == 0 ? "Empty" : items[inventory[i]].name);
            attroff(COLOR_PAIR(items[inventory[i]].color));
        }
    }
}

void printSpellsContent(int spells[SPELLS_SIZE]){
    mvprintw(OFFSET_TOP+13, DUNGEON_WIDTH*3 + 17, "Spells");
    mvprintw(OFFSET_TOP+14, DUNGEON_WIDTH*3 + 19, "Q: ");
    mvprintw(OFFSET_TOP+15, DUNGEON_WIDTH*3 + 19, "W: ");
    mvprintw(OFFSET_TOP+16, DUNGEON_WIDTH*3 + 19, "E: ");
    mvprintw(OFFSET_TOP+17, DUNGEON_WIDTH*3 + 19, "R: ");
    for(int i = 0; i < SPELLS_SIZE; i++){
        if(spells[i] == SPELL_LOCKED){
            mvprintw(OFFSET_TOP+14+i, DUNGEON_WIDTH*3 + 22, "Locked");
        }else{
            mvprintw(OFFSET_TOP+14+i, DUNGEON_WIDTH*3 + 22, "%s", SPELL_LIST[i]);
        }
    }
}

void printStatsContent(int stats[STATS_SIZE]){
    mvprintw(OFFSET_TOP+26, DUNGEON_WIDTH*3 + 17, "Stats");
    mvprintw(OFFSET_TOP+27, DUNGEON_WIDTH*3 + 19, "Health: %d/%d", stats[PLAYER_HEALTH], stats[PLAYER_MAX_HEALTH]);
    mvprintw(OFFSET_TOP+28, DUNGEON_WIDTH*3 + 19, "Level: %d", stats[PLAYER_LEVEL]);
    mvprintw(OFFSET_TOP+29, DUNGEON_WIDTH*3 + 19, "Money: %d", stats[PLAYER_MONEY]);
    mvprintw(OFFSET_TOP+30, DUNGEON_WIDTH*3 + 19, "Experience: [");
    for(int i = -1; i < 10; i++){ 
        
        if(i < stats[PLAYER_EXPERIENCE]/10){
            attron(COLOR_PAIR(GREEN_ON_GREEN));
            mvprintw(OFFSET_TOP+30, DUNGEON_WIDTH*3 + 32+i+1, " ");
            attroff(COLOR_PAIR(GREEN_ON_GREEN));
        }else{
            mvprintw(OFFSET_TOP+30, DUNGEON_WIDTH*3 + 31+i+1, ":");
        }
    }
    mvprintw(OFFSET_TOP+30, DUNGEON_WIDTH*3 + 42, "]");
}

void printExtraSlotBorder(int color_extra_slot_border){
    attron(COLOR_PAIR(color_extra_slot_border));
    for(int i = 0; i < 41; i++){
        mvprintw(OFFSET_TOP-1, i + DUNGEON_WIDTH*3 + 15+47, " ");
        mvprintw(OFFSET_TOP+6, i + DUNGEON_WIDTH*3 + 15+47, " ");
    }
    for(int i = 0; i < 7; i++){
        mvprintw(i+OFFSET_TOP, DUNGEON_WIDTH*3 + 15+47, " ");
        mvprintw(i+OFFSET_TOP, DUNGEON_WIDTH*3 + 55+47, " ");
    }
    attroff(COLOR_PAIR(color_extra_slot_border));   
}