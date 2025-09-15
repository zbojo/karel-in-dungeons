#include "global.h"
#include "game_init.h"
#include "game.h"
#include "map_handler.h"
#include "utility.h"
#include "render.h"
#include "items.h"

void game(int stats[STATS_SIZE], int inventory[INVENTORY_SIZE], int spells[SPELLS_SIZE], struct Item items[ITEMS_SIZE]){
    struct DungeonEntity dungeon[DUNGEON_HEIGHT][DUNGEON_WIDTH];
    int current_dungeon = 0;
    loadDungeon("dungeons/spawn.txt", dungeon);  
    while(stats[PLAYER_HEALTH] > 0){
        experienceHandler(stats, spells);
        printDungeon(dungeon);
        if(current_dungeon == 0){
            spawnInfo();
        }
        if(isInInventory(inventory, ITEM_CLAIRVOYANT_ORB) == 1){
            printClair(stats);
        }
        printLayout(DUNGEON_BORDER_COLOR, WHITE_ON_WHITE, WHITE_ON_WHITE, WHITE_ON_WHITE);
        printData(stats, inventory, spells, items);
        int nextMove = getNextMove();
        int move = handleMove(dungeon, nextMove, stats, inventory, spells, items);
        if(move == 1){
            saveDungeon(DUNGEON_LIST[current_dungeon], dungeon);
            current_dungeon++;
            if(current_dungeon == 7){
                clear();
                attron(COLOR_PAIR(RED_ON_BLACK) | A_BOLD);
                mvprintw(5, 5, "You have reached the end of the beta version. Thank you for playing!");
                attroff(COLOR_PAIR(RED_ON_BLACK) | A_BOLD);
                attron(A_ITALIC);
                mvprintw(6, 5 , "Press 'ENTER' key to exit the game.");
                mvprintw(8, 5, "@2024 Martin Zbojovsky FEI TUKE KPI");
                refresh();
                int end_ch = 0;
                while(end_ch != 10){
                    end_ch = getch();
                }
                endwin();
                return;
            }
            loadDungeon(DUNGEON_LIST[current_dungeon], dungeon);
        }else if(move == 2){
            saveDungeon(DUNGEON_LIST[current_dungeon], dungeon);
            current_dungeon--;
            loadDungeon(DUNGEON_LIST[current_dungeon], dungeon);
        }
        if(nextMove == 5){
            inventoryHandler(inventory, items, stats);
        }
        if(nextMove == 6){
            spellsInspector(spells, stats);
        }
        if(nextMove == 7){
            if(isInInventory(inventory, ITEM_ASTRAL_COMPASS) == 1){
                if(current_dungeon == 0){
                    attron(COLOR_PAIR(items[ITEM_ASTRAL_COMPASS].color) | A_BOLD);
                    mvprintw(48, PADDING_LEFT, "Astral compass: ");
                    attroff(COLOR_PAIR(items[ITEM_ASTRAL_COMPASS].color) | A_BOLD);
                    mvprintw(48, PADDING_LEFT + 16, "You are already at the spawn.");
                    refresh();
                    sleep(2);
                }else if(stats[PLAYER_HEALTH] - ITEM_ASTRAL_COMPASS_HEALTH_COST <= 0){
                    attron(COLOR_PAIR(items[ITEM_ASTRAL_COMPASS].color) | A_BOLD);
                    mvprintw(48, PADDING_LEFT, "Astral compass: ");
                    attroff(COLOR_PAIR(items[ITEM_ASTRAL_COMPASS].color) | A_BOLD);
                    mvprintw(48, PADDING_LEFT + 16, "Recalling to spawn would kill you. You need at least %d health to recall to spawn.", ITEM_ASTRAL_COMPASS_HEALTH_COST);
                    refresh();
                    sleep(3);
                }else{
                    saveDungeon(DUNGEON_LIST[current_dungeon], dungeon);
                    current_dungeon = 0;    
                    loadDungeon(DUNGEON_LIST[current_dungeon], dungeon);
                    stats[PLAYER_HEALTH] -= ITEM_ASTRAL_COMPASS_HEALTH_COST;
                    attron(COLOR_PAIR(items[ITEM_ASTRAL_COMPASS].color) | A_BOLD);
                    mvprintw(48, PADDING_LEFT, "Astral compass: ");
                    attroff(COLOR_PAIR(items[ITEM_ASTRAL_COMPASS].color) | A_BOLD);
                    for(int i = ITEM_ASTRAL_TELEPORT_TIME; i > 0; i--){
                        mvprintw(48, PADDING_LEFT + 16, "In %d seconds, you will reappear at the spawn, but the magic will cost you %d health", i, ITEM_ASTRAL_COMPASS_HEALTH_COST);
                        refresh();
                        sleep(1);
                    }
                }
            }
        }
        refresh();
    }
}

int getFacingEntity(struct DungeonEntity dungeon[DUNGEON_HEIGHT][DUNGEON_WIDTH], int direction){
    int karel_y = getKarelY(dungeon);
    int karel_x = getKarelX(dungeon);
    if(direction == DIRECTION_UP){
        if(karel_y - 1 >= 0){
            return dungeon[karel_y - 1][karel_x].id;
        }
    }else if(direction == DIRECTION_DOWN){
        if(karel_y + 1 < DUNGEON_HEIGHT){
            return dungeon[karel_y + 1][karel_x].id;
        }
    }else if(direction == DIRECTION_LEFT){
        if(karel_x - 1 >= 0){
            return dungeon[karel_y][karel_x - 1].id;
        }
    }else if(direction == DIRECTION_RIGHT){
        if(karel_x + 1 < DUNGEON_WIDTH){
            return dungeon[karel_y][karel_x + 1].id;
        }
    }
    return -1;
}

int getNextMove(){
    int ch = getch();
    if(ch == KEY_UP){
        return DIRECTION_UP;
    }else if(ch == KEY_DOWN){
        return DIRECTION_DOWN;
    }else if(ch == KEY_LEFT){
        return DIRECTION_LEFT;
    }else if(ch == KEY_RIGHT){
        return DIRECTION_RIGHT;
    }else if(ch == 'i' || ch == 'I'){
        return 5;
    }else if(ch == 's' || ch == 'S'){
        return 6;
    }else if(ch == 'b' || ch == 'B'){
        return 7;
    }
    return 0;
}

int handleMove(struct DungeonEntity dungeon[DUNGEON_HEIGHT][DUNGEON_WIDTH], int direction, int stats[STATS_SIZE], int inventory[INVENTORY_SIZE], int spells[SPELLS_SIZE], struct Item items[ITEMS_SIZE]){
    int facing_entity = getFacingEntity(dungeon, direction);
    int karel_y = getKarelY(dungeon);
    int karel_x = getKarelX(dungeon);
    int chests[CHEST_COUNT] = CHESTS_ID;
    int move = 0;

    if(facing_entity == STONE_ID){
        return -1;
    }
    if(facing_entity == MINEABLE_STONE_ID && isInInventory(inventory, ITEM_STONEBREAKER) == 0){
        return -1;
    }
    if(facing_entity == COIN_ID){
        int coins = generateRandomNumber(MIN_BASE_COINS+stats[PLAYER_LEVEL], MAX_BASE_COINS+stats[PLAYER_LEVEL]);
        int coins_multiplier = getCoinMultiplier(inventory, items); 
        stats[PLAYER_MONEY] += coins * coins_multiplier;
    }
    if(isInChest(chests, facing_entity)){
        int chest = openChest(facing_entity-100, inventory, items);
        if(chest == 1){
            switch(direction){
                case DIRECTION_UP:
                    dungeon[karel_y-1][karel_x].id = chests[0];
                    break;
                case DIRECTION_DOWN:
                    dungeon[karel_y+1][karel_x].id = chests[0];
                    break;
                case DIRECTION_LEFT:
                    dungeon[karel_y][karel_x-1].id = chests[0];
                    break;
                case DIRECTION_RIGHT:
                    dungeon[karel_y][karel_x+1].id = chests[0];
                    break;
            }
        }
        return 0;
    }
    if(facing_entity == ENEMY_ID){
        fightEnemy(dungeon, stats, inventory, spells, items, direction);   
        return 0;
    }
    if(facing_entity == TELEPORT_DOWN_ID){
        return 2;
    }
    if(facing_entity == TELEPORT_UP_ID){
        return 1;
    }
    if(facing_entity == SHOP_ID){
        shopHandler(inventory, items, stats);
        return 0;
    }

    if(direction == DIRECTION_UP && karel_y > 0){
        dungeon[karel_y - 1][karel_x].id = KAREL_UP_ID;
        dungeon[karel_y-1][karel_x].render[1] = '^';
        dungeon[karel_y-1][karel_x].color_id = WHITE_ON_BLACK;
        move = 1;
    }else if(direction == DIRECTION_DOWN && karel_y < DUNGEON_HEIGHT - 1){
        dungeon[karel_y + 1][karel_x].id = KAREL_DOWN_ID;
        dungeon[karel_y+1][karel_x].render[1] = 'v';
        dungeon[karel_y+1][karel_x].color_id = WHITE_ON_BLACK;
        move = 1;
    }else if(direction == DIRECTION_LEFT && karel_x > 0){
        dungeon[karel_y][karel_x - 1].id = KAREL_LEFT_ID;
        dungeon[karel_y][karel_x-1].render[1] = '<';
        dungeon[karel_y][karel_x-1].color_id = WHITE_ON_BLACK;
        move = 1;
    }else if(direction == DIRECTION_RIGHT && karel_x < DUNGEON_WIDTH - 1){
        dungeon[karel_y][karel_x + 1].id = KAREL_RIGHT_ID;
        dungeon[karel_y][karel_x+1].render[1] = '>';
        dungeon[karel_y][karel_x+1].color_id = WHITE_ON_BLACK;
        move = 1;
    }
    if(move == 0){
        return -1;
    }
    dungeon[karel_y][karel_x].id = EMPTY_ID;
    dungeon[karel_y][karel_x].render[1] = ' ';
    dungeon[karel_y][karel_x].color_id = BLACK_ON_BLACK;
    
    return 0;
}

int fightEnemy(struct DungeonEntity dungeon[DUNGEON_HEIGHT][DUNGEON_WIDTH], int stats[STATS_SIZE], int inventory[INVENTORY_SIZE], int spells[SPELLS_SIZE], struct Item items[ITEMS_SIZE], int direction){
    printDungeonBorder(RED_ON_RED);
    
    int enemy_health = generateRandomNumber(MIN_ENEMY_HEALTH+stats[PLAYER_LEVEL] * ENEMY_HEALTH_MULTIPLIER, MAX_ENEMY_HEALTH+stats[PLAYER_LEVEL]*ENEMY_HEALTH_MULTIPLIER),
        enemy_damage = generateRandomNumber(MIN_ENEMY_DAMAGE+stats[PLAYER_LEVEL] * ENEMY_DAMAGE_MULTIPLIER, MAX_ENEMY_DAMAGE+stats[PLAYER_LEVEL]*ENEMY_DAMAGE_MULTIPLIER),
        enemy_speed = generateRandomNumber(MIN_ENEMY_SPEED, MAX_ENEMY_SPEED),
        maximum_w_usage = stats[PLAYER_LEVEL] / 5,
        w_usage = 0,
        enemy_attack_back = 100 - stats[PLAYER_LEVEL] * 2,
        player_damage_multiplier = getDamageFromItems(inventory, items, stats),
        player_health_multiplier = getHealthFromItems(inventory, items, stats);

    if(enemy_attack_back < 5){
        enemy_attack_back = 5;
    }

    timeout(enemy_speed);

    for(int i = TIME_TO_START_FIGHT; i > 0; i--){
        clearLines(47, 0, 2);
        attron(COLOR_PAIR(RED_ON_BLACK) | A_BOLD);
        mvprintw(47, 7, "Enemy health: %d | Enemy damage: %d | Enemy attack back in: %d. | Enemy speed %dms", enemy_health, enemy_damage, enemy_attack_back, enemy_speed);
        attroff(COLOR_PAIR(RED_ON_BLACK) | A_BOLD);
        attron(COLOR_PAIR(GREEN_ON_BLACK) | A_BOLD);
        mvprintw(48, 7, "Your health: %d | Health bonus from items: %d | Damage boost from items: %d.", stats[PLAYER_HEALTH], player_health_multiplier, player_damage_multiplier);
        attroff(COLOR_PAIR(GREEN_ON_BLACK) | A_BOLD);
        attron(A_ITALIC);
        mvprintw(50, 7, "Fight starts in %d seconds.", i);
        attroff(A_ITALIC);
        refresh();
        sleep(1.2);
    }

    while(enemy_health > 0 && stats[PLAYER_HEALTH] > 0){
        if(player_health_multiplier < 0){
            player_health_multiplier = 0;
        }
        clearLines(47, 0, 3);
        attron(COLOR_PAIR(RED_ON_BLACK) | A_ITALIC);
        mvprintw(47, 7, "Enemy will fight you back in %d or if you dont attack enemy in %dms.", enemy_attack_back, enemy_speed);
        attroff(COLOR_PAIR(RED_ON_BLACK) | A_ITALIC);
        attron(COLOR_PAIR(RED_ON_BLACK));
        mvprintw(48, 7, "Enemy health: %d", enemy_health);
        attroff(COLOR_PAIR(RED_ON_BLACK));
        attron(COLOR_PAIR(GREEN_ON_BLACK));
        mvprintw(49, 7, "Your health: %d | Health bonus from items: %d | Damage boost from items: %d.", stats[PLAYER_HEALTH], player_health_multiplier, player_damage_multiplier);
        attroff(COLOR_PAIR(GREEN_ON_BLACK));
        refresh();
        int ch = getch();
        clearLines(53, 0, 3);
        if(ch == ERR){
            attron(COLOR_PAIR(BLUE_ON_BLACK) | A_BOLD);
            clearLines(50, 0, 1);
            mvprintw(50, 7, "You missed your chance to attack! Enemy attacks back!"); 
            refresh();
            sleep(0.2);
            attroff(COLOR_PAIR(BLUE_ON_BLACK) | A_BOLD);
            if(player_health_multiplier > 0){
                player_health_multiplier -= enemy_damage;
            }else{
                if(player_health_multiplier < 0){
                        player_health_multiplier = 0;
                    }
                stats[PLAYER_HEALTH] -= enemy_damage; 
            }
        }else{
            clearLines(50, 0, 2);
            refresh();
            ch = tolower(ch);
            if(enemy_attack_back > 0){
                enemy_attack_back--;
            }
            if(enemy_attack_back == 0){
                if(player_health_multiplier > 0){
                    player_health_multiplier -= enemy_damage;
                }else{
                    if(player_health_multiplier < 0){
                        player_health_multiplier = 0;
                    }
                    stats[PLAYER_HEALTH] -= enemy_damage; 
                }
                clearLines(51, 0, 1);
                attron(COLOR_PAIR(RED_ON_BLACK) | A_BOLD);
                mvprintw(53, 7, "Enemy attacked you back for %d damage!", enemy_damage); 
                refresh();
                attroff(COLOR_PAIR(RED_ON_BLACK) | A_BOLD);
                enemy_attack_back = 100 - stats[PLAYER_LEVEL] * 2;
                if(enemy_attack_back < 5){
                    enemy_attack_back = 5;
                }
            }
            switch(ch){
                case 'q':
                    enemy_health -= stats[PLAYER_LEVEL] + Q_BASE_DAMAGE + player_damage_multiplier;
                    if(player_health_multiplier > 0){
                        player_health_multiplier -= (stats[PLAYER_LEVEL] + Q_BASE_COST) / 2;
                    }else{
                        if(player_health_multiplier < 0){
                            player_health_multiplier = 0;
                        }
                        stats[PLAYER_HEALTH] -= (stats[PLAYER_LEVEL] + Q_BASE_COST) / 2;
                    }
                    attron(COLOR_PAIR(GREEN_ON_BLACK) | A_BOLD);
                    mvprintw(51, 7, "You attacked enemy for %d damage!", stats[PLAYER_LEVEL] + Q_BASE_DAMAGE + player_damage_multiplier);
                    attroff(COLOR_PAIR(GREEN_ON_BLACK) | A_BOLD);
                    break;
                case 'w':
                    if(spells[SPELL_W] == SPELL_LOCKED){
                        attron(COLOR_PAIR(RED_ON_BLACK) | A_ITALIC);
                        mvprintw(51, 7, "You haven't learned this spell yet."); 
                        attroff(COLOR_PAIR(RED_ON_BLACK) | A_ITALIC);
                    }else{
                        if(w_usage >= maximum_w_usage){
                            attron(COLOR_PAIR(RED_ON_BLACK) | A_ITALIC);
                            mvprintw(51, 7, "You have used this spell too many times."); 
                            attroff(COLOR_PAIR(RED_ON_BLACK) | A_ITALIC);
                        }else if(stats[PLAYER_HEALTH] >= stats[PLAYER_MAX_HEALTH]){
                            attron(COLOR_PAIR(RED_ON_BLACK) | A_ITALIC);
                            mvprintw(51, 7, "You are already at full health."); 
                            attroff(COLOR_PAIR(RED_ON_BLACK) | A_ITALIC);
                        }else{
                            w_usage++;
                            stats[PLAYER_HEALTH] += W_BASE_HEAL + stats[PLAYER_LEVEL] / 2;
                            attron(COLOR_PAIR(GREEN_ON_BLACK) | A_BOLD);
                            mvprintw(51, 7, "You healed yourself for %d health.", W_BASE_HEAL + stats[PLAYER_LEVEL] / 2); 
                            attroff(COLOR_PAIR(GREEN_ON_BLACK) | A_BOLD);
                        }
                    }
                    break;
                case 'e':
                    if(spells[SPELL_E] == SPELL_LOCKED){
                        attron(COLOR_PAIR(RED_ON_BLACK) | A_ITALIC);
                        mvprintw(51, 7, "You haven't learned this spell yet."); 
                        attroff(COLOR_PAIR(RED_ON_BLACK) | A_ITALIC);
                    }else{
                        enemy_health -= E_BASE_DAMAGE + player_damage_multiplier + stats[PLAYER_LEVEL] + stats[PLAYER_LEVEL];
                        if(player_health_multiplier > 0){
                            player_health_multiplier -= E_BASE_COST + stats[PLAYER_LEVEL];
                        }else{
                            if(player_health_multiplier < 0){
                                player_health_multiplier = 0;
                            }
                            stats[PLAYER_HEALTH] -= E_BASE_COST + stats[PLAYER_LEVEL];
                        }
                        attron(COLOR_PAIR(GREEN_ON_BLACK) | A_BOLD);
                        mvprintw(51, 7, "You attacked enemy for %d damage!", E_BASE_DAMAGE + stats[PLAYER_LEVEL] + player_damage_multiplier);
                        attroff(COLOR_PAIR(GREEN_ON_BLACK) | A_BOLD);
                    }
                    break;
                case 'r':
                    if(spells[SPELL_R] == SPELL_LOCKED){
                        attron(COLOR_PAIR(RED_ON_BLACK) | A_ITALIC);
                        mvprintw(51, 7, "You haven't learned this spell yet."); 
                        attroff(COLOR_PAIR(RED_ON_BLACK) | A_ITALIC);
                    }else{
                        enemy_health -= R_BASE_DAMAGE + stats[PLAYER_LEVEL] + player_damage_multiplier;
                        if(player_health_multiplier > 0){
                            player_health_multiplier -= R_BASE_COST;
                        }else{
                            if(player_health_multiplier < 0){
                                player_health_multiplier = 0;
                            }
                            stats[PLAYER_HEALTH] -= R_BASE_COST;
                        }
                        attron(COLOR_PAIR(GREEN_ON_BLACK) | A_BOLD);
                        mvprintw(51, 7, "You attacked enemy for %d damage!", R_BASE_DAMAGE + stats[PLAYER_LEVEL] + player_damage_multiplier);
                        attroff(COLOR_PAIR(GREEN_ON_BLACK) | A_BOLD);
                    }
                    break;
                default:
                    attron(COLOR_PAIR(RED_ON_BLACK) | A_ITALIC);
                    mvprintw(51, 7, "Invalid spell!"); 
                    attroff(COLOR_PAIR(RED_ON_BLACK) | A_ITALIC);
                    break;
            }
        }
        refresh();

    }
    timeout(-1);

    if(stats[PLAYER_HEALTH] <= 0){
        clearLines(47, 0, 7);
        printDungeonBorder(RED_ON_RED);
        attron(COLOR_PAIR(RED_ON_BLACK) | A_BOLD);
        mvprintw(51, 7, "You have died! Press any key to continue.");
        attroff(COLOR_PAIR(RED_ON_BLACK) | A_BOLD);
        refresh();
        getch();
        mainScreen(stats, inventory, spells, items);
        
    }else{
        int coins_reward = generateRandomNumber(MIN_ENEMY_KILL_COIN_REWARD+stats[PLAYER_LEVEL]/2, MAX_ENEMY_KILL_COIN_REWARD+stats[PLAYER_LEVEL]/2);
        int experience_reward = generateRandomNumber(MIN_ENEMY_KILL_EXPERIENCE_REWARD, MAX_ENEMY_KILL_EXPERIENCE_REWARD);
        clearLines(47, 0, 7);
        printDungeonBorder(GREEN_ON_GREEN);
        attron(COLOR_PAIR(GREEN_ON_BLACK) | A_BOLD);
        mvprintw(48, 7, "You defeated the enemy! You gained %d experience.", experience_reward);    
        attroff(COLOR_PAIR(GREEN_ON_BLACK)| A_BOLD);
        attron(COLOR_PAIR(YELLOW_ON_BLACK) | A_BOLD);
        mvprintw(49, 7, "Coins reward: %d", coins_reward);
        attroff(COLOR_PAIR(YELLOW_ON_BLACK)| A_BOLD);
        mvprintw(51, 7, "Press any key to continue.");
        stats[PLAYER_MONEY] += coins_reward;
        stats[PLAYER_EXPERIENCE] += experience_reward;
        getch();
        switch(direction){
            case DIRECTION_UP:
                dungeon[getKarelY(dungeon)-1][getKarelX(dungeon)].id = EMPTY_ID;
                dungeon[getKarelY(dungeon)-1][getKarelX(dungeon)].render[1] = ' ';
                dungeon[getKarelY(dungeon)-1][getKarelX(dungeon)].color_id = BLACK_ON_BLACK;
                break;
            case DIRECTION_DOWN:
                dungeon[getKarelY(dungeon)+1][getKarelX(dungeon)].id = EMPTY_ID;
                dungeon[getKarelY(dungeon)+1][getKarelX(dungeon)].render[1] = ' ';
                dungeon[getKarelY(dungeon)+1][getKarelX(dungeon)].color_id = BLACK_ON_BLACK;
                break;
            case DIRECTION_LEFT:
                dungeon[getKarelY(dungeon)][getKarelX(dungeon)-1].id = EMPTY_ID;
                dungeon[getKarelY(dungeon)][getKarelX(dungeon)-1].render[1] = ' ';
                dungeon[getKarelY(dungeon)][getKarelX(dungeon)-1].color_id = BLACK_ON_BLACK;
                break;
            case DIRECTION_RIGHT:
                dungeon[getKarelY(dungeon)][getKarelX(dungeon)+1].id = EMPTY_ID;
                dungeon[getKarelY(dungeon)][getKarelX(dungeon)+1].render[1] = ' ';
                dungeon[getKarelY(dungeon)][getKarelX(dungeon)+1].color_id = BLACK_ON_BLACK;
                break;
        }
        refresh();
    }

    

    return 0;

}

