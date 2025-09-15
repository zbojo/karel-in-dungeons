#include "global.h"
#include "game_init.h"
#include "game.h"
#include "map_handler.h"
#include "utility.h"
#include "render.h"
#include "items.h"

void printAsciTitleArt(){
    char *kidart[] = {
        " __   ___       __        _______    _______  ___            __    _____  ___       ________   ____  ____  _____  ___    _______    _______    ______    _____  ___    ________  ",
        "|/\"| /  \")     /\"\"\\      /\"      \\  /\"     \"||\"  |          |\" \\  (\\\"   \\|\"  \\     |\"      \"\\ (\"  _||_ \" |(\\\"   \\|\"  \\  /\" _   \"|  /\"     \"|  /    \" \\  (\\\"   \\|\"  \\  /\"       ) ",
        "(: |/   /     /    \\    |:        |(: ______)||  |          ||  | |.\\\\   \\    |    (.  ___  :)|   (  ) : ||.\\\\   \\    |(: ( \\___) (: ______) // ____  \\ |.\\\\   \\    |(:   \\___/  ",
        "|    __/     /' /\\  \\   |_____/   ) \\/    |  |:  |          |:  | |: \\.   \\\\  |    |: \\   ) ||(:  |  | . )|: \\.   \\\\  | \\/ \\       \\/    |  /  /    ) :)|: \\.   \\\\  | \\___  \\    ",
        "(// _  \\    //  __'  \\   //      /  // ___)_  \\  |___       |.  | |.  \\    \\. |    (| (___\\ || \\\\ \\__/ // |.  \\    \\. | //  \\ ___  // ___)_(: (____/ // |.  \\    \\. |  __/  \\\\   ",
        "|: | \\  \\  /   /  \\\\  \\ |:  __   \\ (:      \"|( \\_|:  \\      /\\  |\\|    \\    \\ |    |:       :) /\\\\ __ //\\ |    \\    \\ |(:   _(  _|(:      \"|\\        /  |    \\    \\ | /\" \\   :)  ",
        "(__|  \\__)(___/    \\___)|__|  \\___) \\_______) \\_______)    (__\\_|_)\\___|\\____\\)    (________/ (__________) \\___|\\____\\) \\_______)  \\_______) \\\"_____/    \\___|\\____\\)(_______/   ",
    };

    

    for(int i = 0; i < ASCI_HEIGHT; i++){
        mvprintw(i, 2, "%s", kidart[i]);
    } 

    attron(COLOR_PAIR(BLUE_ON_BLACK));
    mvprintw(ASCI_HEIGHT+1,2, "@2024 Created by Martin Zbojovsky");
    attroff(COLOR_PAIR(BLUE_ON_BLACK));

    refresh();

}

int getKarelY(struct DungeonEntity dungeon[DUNGEON_HEIGHT][DUNGEON_WIDTH]){
    for(int i = 0; i < DUNGEON_HEIGHT; i++){
        for(int j = 0; j < DUNGEON_WIDTH; j++){
            if(dungeon[i][j].id == KAREL_DOWN_ID || dungeon[i][j].id == KAREL_LEFT_ID || dungeon[i][j].id == KAREL_RIGHT_ID || dungeon[i][j].id == KAREL_UP_ID){
                return i;
            }
        }
    }
    return -1;
}

int getKarelX(struct DungeonEntity dungeon[DUNGEON_HEIGHT][DUNGEON_WIDTH]){
    for(int i = 0; i < DUNGEON_HEIGHT; i++){
        for(int j = 0; j < DUNGEON_WIDTH; j++){
            if(dungeon[i][j].id == KAREL_DOWN_ID || dungeon[i][j].id == KAREL_LEFT_ID || dungeon[i][j].id == KAREL_RIGHT_ID || dungeon[i][j].id == KAREL_UP_ID){
                return j;
            }
        }
    }
    return -1;
}

int isInInventory(int inventory[INVENTORY_SIZE], int item_id){
    for(int i = 0; i < INVENTORY_SIZE; i++){
        if(inventory[i] == item_id){
            return 1;
        }
    }
    return 0;
}

int isInChest(int chests[CHEST_COUNT], int chest_id){
    for(int i = 0; i < CHEST_COUNT; i++){
        if(chests[i] == chest_id){
            return 1;
        }
    }
    return 0;
}

int generateRandomNumber(int min, int max){
    return rand() % (max - min + 1) + min;
}

void clearLines(int y, int x, int count){
    for(int i = 0; i < count; i++){
        move(y+i, x);
        wclrtoeol(stdscr);
    }
    
}

void mainScreen(int stats[STATS_SIZE], int inventory[INVENTORY_SIZE], int spells[SPELLS_SIZE], struct Item items[ITEMS_SIZE]){
    clear();
    refresh();
    prepareGame(stats, inventory, spells);
    prepareItems(items);
    switch(menu()){
        case 0:
            game(stats, inventory, spells, items);
            break;
        case 1:
            tutorial();
            mainScreen(stats, inventory, spells, items);
            break;
        case 2:
            break;
    }
}

void tutorial(){
    clear();
    printAsciTitleArt();

    mvprintw(OFFSET_TOP-2, 2, "Press any key to continue...");

    attron(COLOR_PAIR(GREEN_ON_BLACK) | A_BOLD);
    mvprintw(OFFSET_TOP+1, 4, "Controls:");
    attroff(COLOR_PAIR(GREEN_ON_BLACK) | A_BOLD);

    attron(COLOR_PAIR(BLUE_ON_BLACK) | A_BOLD);
    mvprintw(3+OFFSET_TOP, 5, "Movement");
    attroff(COLOR_PAIR(BLUE_ON_BLACK) | A_BOLD);
    attron(A_ITALIC);
    mvprintw(4+OFFSET_TOP, 6, "Use arrow keys to move Karel.");
    attroff(A_ITALIC);
    mvprintw(5+OFFSET_TOP, 6, "W - move up");
    mvprintw(6+OFFSET_TOP, 6, "S - move down");
    mvprintw(7+OFFSET_TOP, 6, "A - move left");
    mvprintw(8+OFFSET_TOP, 6, "D - move right");
    attron(COLOR_PAIR(BLUE_ON_BLACK) | A_BOLD);
    mvprintw(10+OFFSET_TOP, 5, "Utilities");
    attroff(COLOR_PAIR(BLUE_ON_BLACK) | A_BOLD);
    mvprintw(11+OFFSET_TOP, 6, "I - open inventory");
    mvprintw(12+OFFSET_TOP, 6, "S - inspect spells");
    mvprintw(13+OFFSET_TOP, 6, "B - recall to spawn (if you have item Astral Compass)");
    attron(COLOR_PAIR(BLUE_ON_BLACK) | A_BOLD);
    mvprintw(15+OFFSET_TOP, 5, "Spells");
    attroff(COLOR_PAIR(BLUE_ON_BLACK) | A_BOLD);
    mvprintw(16+OFFSET_TOP, 6, "Q - cast spell 1");
    mvprintw(17+OFFSET_TOP, 6, "W - cast spell 2");
    mvprintw(18+OFFSET_TOP, 6, "E - cast spell 3");
    mvprintw(19+OFFSET_TOP, 6, "R - cast spell 4");
    attron(COLOR_PAIR(BLUE_ON_BLACK) | A_BOLD);

    attron(COLOR_PAIR(GREEN_ON_BLACK) | A_BOLD);
    mvprintw(OFFSET_TOP+21, 4, "Entities in dungeons:");
    attroff(COLOR_PAIR(GREEN_ON_BLACK) | A_BOLD);
    mvprintw(OFFSET_TOP+22, 5, "^ > v < - Karel (you)");
    attron(COLOR_PAIR(STONE_COLOR));
    mvprintw(OFFSET_TOP+23, 5, "   ");
    attroff(COLOR_PAIR(STONE_COLOR));
    mvprintw(OFFSET_TOP+23, 9, "- Stone wall (you can't pass through)");
    attron(COLOR_PAIR(MINEABLE_STONE_COLOR));
    mvprintw(OFFSET_TOP+24, 5, "   ");
    attroff(COLOR_PAIR(MINEABLE_STONE_COLOR));
    mvprintw(OFFSET_TOP+24, 9, "- Mineable stone (you can mine it with special item)");
    attron(COLOR_PAIR(CHEST_COLOR));
    mvprintw(OFFSET_TOP+25, 5, "   ");
    attroff(COLOR_PAIR(CHEST_COLOR));
    mvprintw(OFFSET_TOP+25, 9, "- Chest");
    attron(COLOR_PAIR(RED_ON_BLACK));
    mvprintw(OFFSET_TOP+26, 5, " X ");
    attroff(COLOR_PAIR(RED_ON_BLACK));
    mvprintw(OFFSET_TOP+26, 9, "- Enemy");
    attron(COLOR_PAIR(YELLOW_ON_BLACK));
    mvprintw(OFFSET_TOP+27, 5, " $ ");
    attroff(COLOR_PAIR(YELLOW_ON_BLACK));
    mvprintw(OFFSET_TOP+27, 9, "- Coin");
    attron(COLOR_PAIR(MAGENTA_ON_MAGENTA));
    mvprintw(OFFSET_TOP+28, 5, " @ ");
    attroff(COLOR_PAIR(MAGENTA_ON_MAGENTA));
    mvprintw(OFFSET_TOP+28, 9, "- Teleport to next dungeon");
    attron(COLOR_PAIR(MAGENTA_ON_MAGENTA));
    mvprintw(OFFSET_TOP+29, 5, "   ");
    attroff(COLOR_PAIR(MAGENTA_ON_MAGENTA));
    mvprintw(OFFSET_TOP+29, 9, "- Teleport to previous dungeon");
    attron(COLOR_PAIR(BLUE_ON_BLUE));
    mvprintw(OFFSET_TOP+30, 5, " $ ");
    attroff(COLOR_PAIR(BLUE_ON_BLUE));
    mvprintw(OFFSET_TOP+30, 9, "- Shop");
    attron(COLOR_PAIR(DUNGEON_BORDER_COLOR));
    mvprintw(OFFSET_TOP+31, 5, "   ");
    attroff(COLOR_PAIR(DUNGEON_BORDER_COLOR));
    mvprintw(OFFSET_TOP+31, 9, "- Dungeon border");


    



    attron(COLOR_PAIR(GREEN_ON_BLACK) | A_BOLD);
    mvprintw(OFFSET_TOP+1, 4+80, "Gameplay:");
    attroff(COLOR_PAIR(GREEN_ON_BLACK) | A_BOLD);
    attron(COLOR_PAIR(BLUE_ON_BLACK) | A_BOLD);
    mvprintw(3+OFFSET_TOP, 5+80, "Objective");
    attroff(COLOR_PAIR(BLUE_ON_BLACK) | A_BOLD);
    mvprintw(4+OFFSET_TOP, 6+80, "Explore the dungeons and defeat the enemies.");
    mvprintw(5+OFFSET_TOP, 6+80, "Collect coins to buy items.");
    mvprintw(6+OFFSET_TOP, 6+80, "Find chests to get more items.");
    mvprintw(7+OFFSET_TOP, 6+80, "In one of the dungeons, you will find a teleport to get out of the dungeons and win the game.");
    attron(COLOR_PAIR(BLUE_ON_BLACK) | A_BOLD);
    mvprintw(9+OFFSET_TOP, 5+80, "Fighting");
    attroff(COLOR_PAIR(BLUE_ON_BLACK) | A_BOLD);
    mvprintw(10+OFFSET_TOP, 6+80, "You can fight enemies by facing them and challenging them by going in their direction.");
    mvprintw(11+OFFSET_TOP, 6+80, "You can use spells to defeat them or heal yourself.");
    mvprintw(12+OFFSET_TOP, 6+80, "Items boost your health and damage.");
    attron(COLOR_PAIR(BLUE_ON_BLACK) | A_BOLD);
    mvprintw(14+OFFSET_TOP, 5+80, "Chests and items");
    attroff(COLOR_PAIR(BLUE_ON_BLACK) | A_BOLD);
    mvprintw(15+OFFSET_TOP, 6+80, "Chests contain items that can help you in your journey.");
    mvprintw(16+OFFSET_TOP, 6+80, "To open a chest, go in its direction.");
    mvprintw(17+OFFSET_TOP, 6+80, "Items can be found in chests or bought in the shop.");
    attron(COLOR_PAIR(BLUE_ON_BLACK) | A_BOLD);
    mvprintw(19+OFFSET_TOP, 5+80, "Items and Inventory");
    attroff(COLOR_PAIR(BLUE_ON_BLACK) | A_BOLD);
    mvprintw(20+OFFSET_TOP, 6+80, "You can carry up to 3 items in your inventory.");
    mvprintw(21+OFFSET_TOP, 6+80, "Items can be in inventory or consumed to heal or boost your stats.");
    mvprintw(22+OFFSET_TOP, 6+80, "You can empty your inventory by banishing items.");
    mvprintw(23+OFFSET_TOP, 6+80, "Consumable items are marked with a green color.");
    mvprintw(24+OFFSET_TOP, 6+80, "Normal items are marked with a blue color.");
    mvprintw(25+OFFSET_TOP, 6+80, "Special items are marked with a magenta color.");






    refresh();
    getch();

}

void inventoryHandler(int inventory[INVENTORY_SIZE], struct Item items[ITEMS_SIZE], int stats[STATS_SIZE]){
    printInventoryBorder(BLUE_ON_BLUE);

    mvprintw(14, DUNGEON_WIDTH*3 + 17, ">");
    refresh();
    int position = 0;
    clearLines(OFFSET_TOP-1, DUNGEON_WIDTH*3 + 61, 9);
    while(1){
        if(inventory[position] != NO_ITEM){
            clearLines(20, DUNGEON_WIDTH*3 + 17, 3);
            if(items[inventory[position]].isConsumable == 1){
                attron(COLOR_PAIR(BLUE_ON_BLACK));
                mvprintw(20, DUNGEON_WIDTH*3 + 17, "%s", items[inventory[position]].description);
                attroff(COLOR_PAIR(BLUE_ON_BLACK));
                
                if(items[inventory[position]].healthOnConsume > 0 && stats[PLAYER_HEALTH]+items[inventory[position]].healthOnConsume > stats[PLAYER_MAX_HEALTH]){
                    attron(COLOR_PAIR(GREEN_ON_BLACK) | A_ITALIC);
                    mvprintw(21, DUNGEON_WIDTH*3 + 17, "Press 'enter' to consume this item.");
                    attroff(COLOR_PAIR(GREEN_ON_BLACK) | A_ITALIC);
                    attron(COLOR_PAIR(RED_ON_BLACK));
                    mvprintw(21, DUNGEON_WIDTH*3 + 17, "If you consume this item, you won't get the full health bonus, but only %d health. Press 'enter' to consume this item.", stats[PLAYER_MAX_HEALTH] - stats[PLAYER_HEALTH]);
                    attroff(COLOR_PAIR(RED_ON_BLACK));
                }else {
                    attron(COLOR_PAIR(GREEN_ON_BLACK) | A_ITALIC);
                    mvprintw(21, DUNGEON_WIDTH*3 + 17, "Press 'enter' to consume this item.");
                    attroff(COLOR_PAIR(GREEN_ON_BLACK) | A_ITALIC);
                }
                
            }else{
                attron(COLOR_PAIR(BLUE_ON_BLACK));
                mvprintw(20, DUNGEON_WIDTH*3 + 17, "%s", items[inventory[position]].description);
                attroff(COLOR_PAIR(BLUE_ON_BLACK));
                attron(COLOR_PAIR(RED_ON_BLACK) | A_ITALIC);
                mvprintw(21, DUNGEON_WIDTH*3 + 17, "Press 'enter' to banish this item to oblivion forever.");
                attroff(COLOR_PAIR(RED_ON_BLACK) | A_ITALIC);
                
            }
        }else{
            clearLines(20, DUNGEON_WIDTH*3 + 17, 3);
        }
        int ch = getch();
        if(ch == 27){
            return;
        }else if(ch == KEY_UP && position > 0){
            position-=1;
        }else if(ch == KEY_DOWN && position < 2){
            position+=1; 
        }else if(ch == 10 && inventory[position] != 0){
            if(items[inventory[position]].isConsumable == 1){
                if(stats[PLAYER_HEALTH]+items[inventory[position]].healthOnConsume > stats[PLAYER_MAX_HEALTH]){
                    stats[PLAYER_HEALTH] = stats[PLAYER_MAX_HEALTH];
                    printStatsContent(stats);
                }else{
                    stats[PLAYER_HEALTH] += items[inventory[position]].healthOnConsume;
                    stats[PLAYER_MONEY] += items[inventory[position]].coinsOnConsume;
                    stats[PLAYER_EXPERIENCE] += items[inventory[position]].experienceOnConsume;
                    printStatsContent(stats);
                }
                inventory[position] = NO_ITEM;
                clearLines(14, DUNGEON_WIDTH*3 + 17, 3);
                printInventoryBorder(BLUE_ON_BLUE);
                printInventoryContent(inventory, items);
            }
            inventory[position] = NO_ITEM;
            clearLines(14, DUNGEON_WIDTH*3 + 17, 3);
            printInventoryBorder(BLUE_ON_BLUE);
            printInventoryContent(inventory, items);
        }
        if(position == 0){
            mvprintw(14, DUNGEON_WIDTH*3 + 17, ">");
            mvprintw(15, DUNGEON_WIDTH*3 + 17, " ");
            mvprintw(16, DUNGEON_WIDTH*3 + 17, " ");
        }else if(position == 1){
            mvprintw(14, DUNGEON_WIDTH*3 + 17, " ");
            mvprintw(15, DUNGEON_WIDTH*3 + 17, ">");
            mvprintw(16, DUNGEON_WIDTH*3 + 17, " ");
        }else if(position == 2){
            mvprintw(14, DUNGEON_WIDTH*3 + 17, " ");
            mvprintw(15, DUNGEON_WIDTH*3 + 17, " ");
            mvprintw(16, DUNGEON_WIDTH*3 + 17, ">");
        }
        refresh();
    }
}

void spellsInspector(int spells[SPELLS_SIZE], int stats[STATS_SIZE]){
    printSpellsBorder(BLUE_ON_BLUE);
    refresh();
    int position = 0;
    mvprintw(26, DUNGEON_WIDTH*3 + 17, ">");
    attron(COLOR_PAIR(RED_ON_BLACK));
    mvprintw(33, DUNGEON_WIDTH*3 + 17, "Damage to enemy: %d", Q_BASE_DAMAGE+stats[PLAYER_LEVEL]);
    attroff(COLOR_PAIR(RED_ON_BLACK));
    attron(COLOR_PAIR(ORANGE_ON_BLACK));
    mvprintw(34, DUNGEON_WIDTH*3 + 17, "Cost: %d health", (Q_BASE_COST+stats[PLAYER_LEVEL])/2);
    attroff(COLOR_PAIR(ORANGE_ON_BLACK));
    while(1){
        
        if(spells[position] == SPELL_LOCKED){
            clearLines(33, DUNGEON_WIDTH*3 + 17, 2);
            attron(COLOR_PAIR(RED_ON_BLACK) | A_ITALIC);
            mvprintw(33, DUNGEON_WIDTH*3 + 17, "You haven't learned this spell yet. Explore the dungeons to find it!");
            attroff(COLOR_PAIR(RED_ON_BLACK) | A_ITALIC);
        }
        int ch = getch();
        clearLines(33, DUNGEON_WIDTH*3 + 17, 2);
        if(ch == 27){
            return;
        }else if(ch == KEY_UP && position > 0){
            position-=1;
        }else if(ch == KEY_DOWN && position < 3){
            position+=1; 
        }

        if(position == 0){
            mvprintw(26, DUNGEON_WIDTH*3 + 17, ">");
            mvprintw(27, DUNGEON_WIDTH*3 + 17, " ");
            mvprintw(28, DUNGEON_WIDTH*3 + 17, " ");
            mvprintw(29, DUNGEON_WIDTH*3 + 17, " ");
            attron(COLOR_PAIR(RED_ON_BLACK));
            mvprintw(33, DUNGEON_WIDTH*3 + 17, "Damage to enemy: %d", Q_BASE_DAMAGE+stats[PLAYER_LEVEL]);
            attroff(COLOR_PAIR(RED_ON_BLACK));
            attron(COLOR_PAIR(ORANGE_ON_BLACK));
            mvprintw(34, DUNGEON_WIDTH*3 + 17, "Cost: %d health", (Q_BASE_COST+stats[PLAYER_LEVEL])/2);
            attroff(COLOR_PAIR(ORANGE_ON_BLACK));
        }else if(position == 1){
            mvprintw(26, DUNGEON_WIDTH*3 + 17, " ");
            mvprintw(27, DUNGEON_WIDTH*3 + 17, ">");
            mvprintw(28, DUNGEON_WIDTH*3 + 17, " ");
            mvprintw(29, DUNGEON_WIDTH*3 + 17, " ");
            attron(COLOR_PAIR(GREEN_ON_BLACK));
            mvprintw(33, DUNGEON_WIDTH*3 + 17, "Heals you for %d health", W_BASE_HEAL+stats[PLAYER_LEVEL]/2);
            attroff(COLOR_PAIR(GREEN_ON_BLACK));
            attron(COLOR_PAIR(ORANGE_ON_BLACK));
            mvprintw(34, DUNGEON_WIDTH*3 + 17, "Maximum uses in fight: %d", stats[PLAYER_LEVEL] / 5);
            attroff(COLOR_PAIR(ORANGE_ON_BLACK));
        }else if(position == 2){
            mvprintw(26, DUNGEON_WIDTH*3 + 17, " ");
            mvprintw(27, DUNGEON_WIDTH*3 + 17, " ");
            mvprintw(28, DUNGEON_WIDTH*3 + 17, ">");
            mvprintw(29, DUNGEON_WIDTH*3 + 17, " ");
            attron(COLOR_PAIR(RED_ON_BLACK));
            mvprintw(33, DUNGEON_WIDTH*3 + 17, "Damage to enemy: %d", E_BASE_DAMAGE+stats[PLAYER_LEVEL]);
            attroff(COLOR_PAIR(RED_ON_BLACK));
            attron(COLOR_PAIR(ORANGE_ON_BLACK));
            mvprintw(34, DUNGEON_WIDTH*3 + 17, "Cost: %d health", E_BASE_COST+stats[PLAYER_LEVEL]);
            attroff(COLOR_PAIR(ORANGE_ON_BLACK));
        }else if(position == 3){
            mvprintw(26, DUNGEON_WIDTH*3 + 17, " ");
            mvprintw(27, DUNGEON_WIDTH*3 + 17, " ");
            mvprintw(28, DUNGEON_WIDTH*3 + 17, " ");
            mvprintw(29, DUNGEON_WIDTH*3 + 17, ">");
            attron(COLOR_PAIR(RED_ON_BLACK));
            mvprintw(33, DUNGEON_WIDTH*3 + 17, "Damage to enemy: %d", R_BASE_DAMAGE+stats[PLAYER_LEVEL]);
            attroff(COLOR_PAIR(RED_ON_BLACK));
            attron(COLOR_PAIR(ORANGE_ON_BLACK));
            mvprintw(34, DUNGEON_WIDTH*3 + 17, "Cost: %d health", R_BASE_COST+stats[PLAYER_LEVEL]);
            attroff(COLOR_PAIR(ORANGE_ON_BLACK));
        }
        refresh();
    }
}

void experienceHandler(int stats[STATS_SIZE], int spells[SPELLS_SIZE]){
    int buff_exp = stats[PLAYER_EXPERIENCE];
    if(stats[PLAYER_EXPERIENCE] >= 100){
        while(buff_exp >= 100){
            buff_exp -= 100;
            stats[PLAYER_LEVEL] += 1;
            stats[PLAYER_MAX_HEALTH] += 10;
        }
        stats[PLAYER_EXPERIENCE] = buff_exp;
        
    }
    if(stats[PLAYER_LEVEL] >= W_SPELL_LVL_UNLOCK && stats[PLAYER_LEVEL] < E_SPELL_LVL_UNLOCK){
        spells[SPELL_W] = SPELL_UNLOCKED;
    }
    if(stats[PLAYER_LEVEL] >= E_SPELL_LVL_UNLOCK && stats[PLAYER_LEVEL] < R_SPELL_LVL_UNLOCK){
        spells[SPELL_E] = SPELL_UNLOCKED;
    }
    if(stats[PLAYER_LEVEL] >= R_SPELL_LVL_UNLOCK){
        spells[SPELL_R] = SPELL_UNLOCKED;
    }
}

int openChest(int chest_id, int inventory[INVENTORY_SIZE], struct Item items[ITEMS_SIZE]){
    clearLines(OFFSET_TOP-1, DUNGEON_WIDTH*3 + 61, 9);
    printExtraSlotBorder(CHEST_COLOR);
    mvprintw(OFFSET_TOP+1, DUNGEON_WIDTH*3 + 64, "You found a chest!");
    if(chest_id == 0){
        attron(A_ITALIC);
        mvprintw(OFFSET_TOP+3, DUNGEON_WIDTH*3 + 64, "The chest creaks open, revealing ");
        mvprintw(OFFSET_TOP+4, DUNGEON_WIDTH*3 + 64, "nothing but dust and cobwebs.");
        mvprintw(OFFSET_TOP+8, DUNGEON_WIDTH*3 + 63, "Press any key to close the chest.");
        attroff(A_ITALIC);
    }else{
        mvprintw(OFFSET_TOP+3, DUNGEON_WIDTH*3 + 65, "Chest contains: ");
        attron(COLOR_PAIR(items[chest_id].color)| A_BOLD);
        mvprintw(OFFSET_TOP+3, DUNGEON_WIDTH*3 + 65+16, "%s", items[chest_id].name);
        attroff(COLOR_PAIR(items[chest_id].color)| A_BOLD);
        attron(A_ITALIC);
        attron(COLOR_PAIR(items[chest_id].color));
        mvprintw(OFFSET_TOP+8, DUNGEON_WIDTH*3 + 63, "%s", items[chest_id].description);
        attroff(COLOR_PAIR(items[chest_id].color));
        attroff(A_ITALIC);

        if(isInInventory(inventory, NO_ITEM) == 1){
            attron(COLOR_PAIR(GREEN_ON_BLACK) | A_BOLD);
            mvprintw(OFFSET_TOP+9, DUNGEON_WIDTH*3 + 63, "Press 'enter' to take this item or any other key to close the chest.");
            attroff(COLOR_PAIR(GREEN_ON_BLACK) | A_BOLD);
            int ch = getch();
            if(ch == 10){
                for(int i = 0; i < INVENTORY_SIZE; i++){
                    if(inventory[i] == NO_ITEM){
                        inventory[i] = chest_id;
                        break;
                    }
                }
                return 1;
            }
        }else{
            attron(COLOR_PAIR(RED_ON_BLACK) | A_BOLD);
            mvprintw(OFFSET_TOP+9, DUNGEON_WIDTH*3 + 63, "Your load is too heavy. Lighten your inventory and return later.");
            attroff(COLOR_PAIR(RED_ON_BLACK) | A_BOLD);
            attron(A_ITALIC);
            mvprintw(OFFSET_TOP+10, DUNGEON_WIDTH*3 + 63, "Press any key to close the chest.");
            attroff(A_ITALIC);
            getch();
            return 0;
        }
        
    }
    refresh();
    getch();
    return 0;
}

void shopHandler(int inventory[INVENTORY_SIZE], struct Item items[ITEMS_SIZE], int stats[STATS_SIZE]){
    attron(A_ITALIC);
    mvprintw(OFFSET_TOP-2, DUNGEON_WIDTH*3 + 62, "Stats update when you leave the shop 'esc'.");
    attroff(A_ITALIC);
    clearLines(OFFSET_TOP-1, DUNGEON_WIDTH*3 + 61, 9);
    printExtraSlotBorder(BLUE_ON_BLUE);
    attron(COLOR_PAIR(ORANGE_ON_BLACK) | A_BOLD);
    mvprintw(OFFSET_TOP+1, DUNGEON_WIDTH*3 + 64, "Welcome to the shop!");
    attroff(COLOR_PAIR(ORANGE_ON_BLACK) | A_BOLD);
    mvprintw(14, DUNGEON_WIDTH*3 + 64, ">");
    mvprintw(OFFSET_TOP+2, DUNGEON_WIDTH*3 + 66, "[%d$] %s", SHOP_HEAL_POTION_COST, items[ITEM_HEALING_POTION].name);
    mvprintw(OFFSET_TOP+3, DUNGEON_WIDTH*3 + 66, "[%d$] %s", SHOP_EXP_POTION_COST, items[ITEM_EXP_POTION].name);
    mvprintw(OFFSET_TOP+4, DUNGEON_WIDTH*3 + 66, "[%d$] %s", SHOP_STONE_BREAKER_COST, items[ITEM_STONEBREAKER].name);
    int position = 0;
    while(1){
        clearLines(20, DUNGEON_WIDTH*3 + 64, 3);
        if(position == 0){
            if(stats[PLAYER_MONEY] >= SHOP_HEAL_POTION_COST){
                attron(COLOR_PAIR(GREEN_ON_BLACK));
                mvprintw(OFFSET_TOP+2, DUNGEON_WIDTH*3 + 64, ">");
                attroff(COLOR_PAIR(GREEN_ON_BLACK));
                attron(COLOR_PAIR(BLUE_ON_BLACK) | A_BOLD);
                mvprintw(20, DUNGEON_WIDTH*3 + 64, "Item description: %s", items[ITEM_HEALING_POTION].description);
                attroff(COLOR_PAIR(BLUE_ON_BLACK) | A_BOLD);
                if(isInInventory(inventory, NO_ITEM) == 1){
                    attron(COLOR_PAIR(GREEN_ON_BLACK) | A_BOLD);
                    mvprintw(21, DUNGEON_WIDTH*3 + 64, "Press 'enter' to buy this item.");
                    attroff(COLOR_PAIR(GREEN_ON_BLACK) | A_BOLD);
                }else{
                    attron(COLOR_PAIR(ORANGE_ON_BLACK) | A_ITALIC);
                    mvprintw(21, DUNGEON_WIDTH*3 + 64, "Your inventory is full. But you can immediately consume this item.");
                    attroff(COLOR_PAIR(ORANGE_ON_BLACK) | A_ITALIC);
                    attron(COLOR_PAIR(GREEN_ON_BLACK) | A_ITALIC);
                    mvprintw(22, DUNGEON_WIDTH*3 + 64, "Press 'enter' to buy and consume this item.");
                    attroff(COLOR_PAIR(GREEN_ON_BLACK) | A_ITALIC);
                }
            }else{
                attron(COLOR_PAIR(RED_ON_BLACK));
                mvprintw(OFFSET_TOP+2, DUNGEON_WIDTH*3 + 64, ">");
                attroff(COLOR_PAIR(RED_ON_BLACK));
                attron(COLOR_PAIR(BLUE_ON_BLACK) | A_BOLD);
                mvprintw(20, DUNGEON_WIDTH*3 + 64, "Item description: %s", items[ITEM_HEALING_POTION].description);
                attroff(COLOR_PAIR(BLUE_ON_BLACK) | A_BOLD);
                attron(COLOR_PAIR(RED_ON_BLACK) | A_ITALIC);
                mvprintw(21, DUNGEON_WIDTH*3 + 64, "Your purse feels light... too light.");
                attroff(COLOR_PAIR(RED_ON_BLACK) | A_ITALIC);
            }
            mvprintw(15, DUNGEON_WIDTH*3 + 64, " ");
            mvprintw(16, DUNGEON_WIDTH*3 + 64, " ");
        }else if(position == 1){
            if(stats[PLAYER_MONEY] >= SHOP_EXP_POTION_COST){
                attron(COLOR_PAIR(GREEN_ON_BLACK));
                mvprintw(OFFSET_TOP+3, DUNGEON_WIDTH*3 + 64, ">");
                attroff(COLOR_PAIR(GREEN_ON_BLACK));
                attron(COLOR_PAIR(BLUE_ON_BLACK) | A_BOLD);
                mvprintw(20, DUNGEON_WIDTH*3 + 64, "Item description: %s", items[ITEM_EXP_POTION].description);
                attroff(COLOR_PAIR(BLUE_ON_BLACK) | A_BOLD);
                if(isInInventory(inventory, NO_ITEM) == 1){
                    attron(COLOR_PAIR(GREEN_ON_BLACK) | A_BOLD);
                    mvprintw(21, DUNGEON_WIDTH*3 + 64, "Press 'enter' to buy this item.");
                    attroff(COLOR_PAIR(GREEN_ON_BLACK) | A_BOLD);
                }else{
                    attron(COLOR_PAIR(ORANGE_ON_BLACK) | A_ITALIC);
                    mvprintw(21, DUNGEON_WIDTH*3 + 64, "Your inventory is full. But you can immediately consume this item.");
                    attroff(COLOR_PAIR(ORANGE_ON_BLACK) | A_ITALIC);
                    attron(COLOR_PAIR(GREEN_ON_BLACK) | A_ITALIC);
                    mvprintw(22, DUNGEON_WIDTH*3 + 64, "Press 'enter' to buy and consume this item.");
                    attroff(COLOR_PAIR(GREEN_ON_BLACK) | A_ITALIC);
                    
                }
            }else{
                attron(COLOR_PAIR(RED_ON_BLACK));
                mvprintw(OFFSET_TOP+3, DUNGEON_WIDTH*3 + 64, ">");
                attroff(COLOR_PAIR(RED_ON_BLACK));
                attron(COLOR_PAIR(BLUE_ON_BLACK) | A_BOLD);
                mvprintw(20, DUNGEON_WIDTH*3 + 64, "Item description: %s", items[ITEM_EXP_POTION].description);
                attroff(COLOR_PAIR(BLUE_ON_BLACK) | A_BOLD);
                attron(COLOR_PAIR(RED_ON_BLACK) | A_ITALIC);
                mvprintw(21, DUNGEON_WIDTH*3 + 64, "Your purse feels light... too light.");
                attroff(COLOR_PAIR(RED_ON_BLACK) | A_ITALIC);
            }
            mvprintw(14, DUNGEON_WIDTH*3 + 64, " ");
            mvprintw(16, DUNGEON_WIDTH*3 + 64, " ");
        }else if(position == 2){
            if(stats[PLAYER_MONEY] >= SHOP_STONE_BREAKER_COST){
                attron(COLOR_PAIR(GREEN_ON_BLACK));
                mvprintw(OFFSET_TOP+4, DUNGEON_WIDTH*3 + 64, ">");
                attroff(COLOR_PAIR(GREEN_ON_BLACK));
                attron(COLOR_PAIR(BLUE_ON_BLACK) | A_BOLD);
                mvprintw(20, DUNGEON_WIDTH*3 + 64, "Item description: %s", items[ITEM_STONEBREAKER].description);
                attroff(COLOR_PAIR(BLUE_ON_BLACK) | A_BOLD);
                if(isInInventory(inventory, NO_ITEM) == 1){
                    attron(COLOR_PAIR(GREEN_ON_BLACK) | A_BOLD);
                    mvprintw(21, DUNGEON_WIDTH*3 + 64, "Press 'enter' to buy this item.");
                    attroff(COLOR_PAIR(GREEN_ON_BLACK) | A_BOLD);
                }else{
                    attron(COLOR_PAIR(RED_ON_BLACK) | A_ITALIC);
                    mvprintw(21, DUNGEON_WIDTH*3 + 64, "Your inventory is full. Consider consuming some items or banishing");
                    attroff(COLOR_PAIR(RED_ON_BLACK) | A_ITALIC);
                    
                }
            }else{
                attron(COLOR_PAIR(RED_ON_BLACK));
                mvprintw(OFFSET_TOP+4, DUNGEON_WIDTH*3 + 64, ">");
                attroff(COLOR_PAIR(RED_ON_BLACK));
                attron(COLOR_PAIR(MAGENTA_ON_BLACK) | A_BOLD);
                mvprintw(20, DUNGEON_WIDTH*3 + 64, "Item description: %s", items[ITEM_STONEBREAKER].description);
                attroff(COLOR_PAIR(MAGENTA_ON_BLACK) | A_BOLD);
                attron(COLOR_PAIR(RED_ON_BLACK) | A_ITALIC);
                mvprintw(21, DUNGEON_WIDTH*3 + 64, "Your purse feels light... too light.");
                attroff(COLOR_PAIR(RED_ON_BLACK) | A_ITALIC);
            }
            mvprintw(14, DUNGEON_WIDTH*3 + 64, " ");
            mvprintw(15, DUNGEON_WIDTH*3 + 64, " ");
        }
        int ch = getch();  
        if(ch == 27){
            return;
        }else if(ch == KEY_UP && position > 0){
            position-=1;
        }else if(ch == KEY_DOWN && position < 2){
            position+=1;
        }else if(ch == 10){
            switch(position){
                case 0:
                    if(stats[PLAYER_MONEY] >= SHOP_HEAL_POTION_COST){
                        if(isInInventory(inventory, NO_ITEM) == 1){
                            stats[PLAYER_MONEY] -= SHOP_HEAL_POTION_COST;
                            for(int i = 0; i < INVENTORY_SIZE; i++){
                                if(inventory[i] == NO_ITEM){
                                    inventory[i] = ITEM_HEALING_POTION;
                                    return;
                                }
                            }
                        }else{
                            stats[PLAYER_MONEY] -= SHOP_HEAL_POTION_COST;
                            stats[PLAYER_HEALTH] += items[ITEM_HEALING_POTION].healthOnConsume;
                            if(stats[PLAYER_HEALTH] > stats[PLAYER_MAX_HEALTH]){
                                stats[PLAYER_HEALTH] = stats[PLAYER_MAX_HEALTH];
                            }
                        }
                    }
                    return;

                case 1:
                    if(stats[PLAYER_MONEY] >= SHOP_EXP_POTION_COST){
                        if(isInInventory(inventory, NO_ITEM) == 1){
                            stats[PLAYER_MONEY] -= SHOP_EXP_POTION_COST;
                            for(int i = 0; i < INVENTORY_SIZE; i++){
                                if(inventory[i] == NO_ITEM){
                                    inventory[i] = ITEM_EXP_POTION;
                                    return;
                                }
                            }
                        }else{
                            stats[PLAYER_MONEY] -= SHOP_EXP_POTION_COST;
                            stats[PLAYER_EXPERIENCE] += items[ITEM_EXP_POTION].experienceOnConsume;
                            if(stats[PLAYER_HEALTH] > stats[PLAYER_MAX_HEALTH]){
                                stats[PLAYER_HEALTH] = stats[PLAYER_MAX_HEALTH];
                            }
                        }
                    }
                    return;
                
                case 2:
                    if(stats[PLAYER_MONEY] >= SHOP_STONE_BREAKER_COST){
                        if(isInInventory(inventory, NO_ITEM) == 1){
                            stats[PLAYER_MONEY] -= SHOP_STONE_BREAKER_COST;
                            for(int i = 0; i < INVENTORY_SIZE; i++){
                                if(inventory[i] == NO_ITEM){
                                    inventory[i] = ITEM_STONEBREAKER;
                                    return;
                                }
                            }
                        }
                    }
                    return;

            }

        }
    }
    refresh();
    getch();
}

void spawnInfo(){
    attron(COLOR_PAIR(BLUE_ON_BLACK));
    mvprintw(10, 41, "EXPLORE");
    mvprintw(26, 3, "S");
    mvprintw(27, 3, "H");
    mvprintw(28, 3, "O");
    mvprintw(29, 3, "P");
    mvprintw(30, 3, "$");
    attroff(COLOR_PAIR(BLUE_ON_BLACK));
}

int checkRequirements(){
    initscr();
    int height, width;
    getmaxyx(stdscr, height, width);
    if(height < MIN_SCREEN_HEIGHT || width < MIN_SCREEN_WIDTH){
        endwin();
        printf("Please resize the terminal to at least %dx%d and restart the game.\n", MIN_SCREEN_WIDTH, MIN_SCREEN_HEIGHT);
        return 1;
    }
    if(has_colors() == FALSE){
        endwin();
        printf("Your terminal does not support colors. Please enable colors and restart the game.\n");
        return 2;
    }
    return 0;
}

void printClair(int stats[STATS_SIZE]){
    printExtraSlotBorder(MAGENTA_ON_MAGENTA);
    
    attron(COLOR_PAIR(MAGENTA_ON_BLACK) | A_BOLD);
    mvprintw(OFFSET_TOP+1, DUNGEON_WIDTH*3 + 64, "Clairvoyant Orb");
    attroff(COLOR_PAIR(MAGENTA_ON_BLACK) | A_BOLD);
    int enemy_health = generateRandomNumber(MIN_ENEMY_HEALTH+stats[PLAYER_LEVEL] * ENEMY_HEALTH_MULTIPLIER, MAX_ENEMY_HEALTH+stats[PLAYER_LEVEL]*ENEMY_HEALTH_MULTIPLIER),
    enemy_damage = generateRandomNumber(MIN_ENEMY_DAMAGE+stats[PLAYER_LEVEL] * ENEMY_DAMAGE_MULTIPLIER, MAX_ENEMY_DAMAGE+stats[PLAYER_LEVEL]*ENEMY_DAMAGE_MULTIPLIER);
    mvprintw(OFFSET_TOP+3, DUNGEON_WIDTH*3 + 65, "Aproximate enemy health: %d", enemy_health);
    mvprintw(OFFSET_TOP+4, DUNGEON_WIDTH*3 + 65, "Aproximate enemy damage: %d", enemy_damage);


} 