#include "global.h"
#include "game_init.h"
#include "game.h"
#include "map_handler.h"
#include "utility.h"
#include "render.h"
#include "items.h"

int getCoinMultiplier(int inventory[INVENTORY_SIZE], struct Item items[ITEMS_SIZE]){
    int multiplier = 0;
    for(int i = 0; i < INVENTORY_SIZE; i++){
        if(inventory[i] != 0){
            multiplier += items[inventory[i]].coins_multiplier;
        }
    }
    if(multiplier == 0) multiplier = 1;
    return multiplier;
}

int getDamageFromItems(int inventory[INVENTORY_SIZE], struct Item items[ITEMS_SIZE], int stats[STATS_SIZE]){
    int damage = 0;
    for(int i = 0; i < INVENTORY_SIZE; i++){
        if(inventory[i] != -1){
            if(items[inventory[i]].isConsumable == 0){
                if(items[inventory[i]].multiply_level_damage > 0){
                    damage += items[inventory[i]].base_damage + items[inventory[i]].multiply_level_damage * stats[PLAYER_LEVEL];
                }
                if(items[inventory[i]].plus_level_damage > 0){
                    damage += stats[PLAYER_LEVEL] + items[inventory[i]].plus_level_damage;
                }
                if(items[inventory[i]].base_damage > 0){
                    damage += items[inventory[i]].base_damage;
                }
            }
        }
    }
    
    return damage;
}

int getHealthFromItems(int inventory[INVENTORY_SIZE], struct Item items[ITEMS_SIZE], int stats[STATS_SIZE]){
    int health = 0;
    for(int i = 0; i < INVENTORY_SIZE; i++){
        if(inventory[i] != -1){
            if(items[inventory[i]].isConsumable == 0){
                if(items[inventory[i]].multiply_level_health > 0){
                    health += items[inventory[i]].base_health + items[inventory[i]].multiply_level_health * stats[PLAYER_LEVEL];
                }else{
                    health += items[inventory[i]].base_health + items[inventory[i]].plus_level_health;
                }
            }
        }
    }
    return health;
}




