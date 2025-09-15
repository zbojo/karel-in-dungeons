#include <ncurses.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

// DUNGEONS 
#define DUNGEON_LIST (const char *[]) {"dungeons/spawn.txt", "dungeons/dungeon_1.txt", "dungeons/dungeon_2.txt", "dungeons/dungeon_3.txt", "dungeons/dungeon_4.txt", "dungeons/dungeon_5.txt", "dungeons/dungeon_6.txt"}

// MAP SIZE
#define DUNGEON_WIDTH 25
#define DUNGEON_HEIGHT 17

// INVENTORY
#define INVENTORY_SIZE 3
#define ITEM_1 0
#define ITEM_2 1
#define ITEM_3 2

// SPELLS
#define SPELLS_SIZE 4
#define MAX_SPELL_NAME 20
#define MAX_SPELL_DESCRIPTION 100
#define SPELL_LOCKED 0
#define SPELL_UNLOCKED 1    
#define SPELL_Q 0
#define SPELL_W 1
#define SPELL_E 2
#define SPELL_R 3
#define SPELL_LIST (const char *[]) {"Firebolt", "Healing Touch", "Chain Lightning", "Meteor Storm"}
#define Q_BASE_DAMAGE 2
#define Q_BASE_COST 1
#define W_BASE_HEAL 1
#define E_BASE_DAMAGE 35
#define E_BASE_COST 15
#define R_BASE_DAMAGE 50
#define R_BASE_COST 25
#define W_SPELL_LVL_UNLOCK 8
#define E_SPELL_LVL_UNLOCK 18
#define R_SPELL_LVL_UNLOCK 30

// ITEMS
#define MAX_ITEM_NAME 100
#define MAX_ITEM_DESCRIPTION 200
#define ITEMS_SIZE 19
struct Item {
    int id;
    char name[MAX_ITEM_NAME];
    char description[MAX_ITEM_DESCRIPTION];
    // DAMAGE
    int base_damage;
    int plus_level_damage;
    int multiply_level_damage;
    // HEALTH
    int base_health;
    int plus_level_health;
    int multiply_level_health;
    // COINS
    int coins;
    int coins_multiplier;
    // CONSUMABLE
    int isConsumable;
    int coinsOnConsume;
    int healthOnConsume;
    int experienceOnConsume;
    // UTILITY
    int color;
};
#define NO_ITEM 0
#define ITEM_LONGSWORD 1 //ok
#define ITEM_BERSERKER_AXE 2 //ok
#define ITEM_VENOMSHARD_DAGGER 3 
#define ITEM_THUNDER_HAMMER 4 //ok
#define ITEM_STONEBREAKER 5
#define ITEM_PHOENIX_STONE 6 //ok
#define ITEM_HEALING_POTION 7 //ok
#define ITEM_EXP_POTION 9 //ok
#define ITEM_CLAIRVOYANT_ORB 10//ok
#define ITEM_GEM_JUICE 11//ok
#define ITEM_GOLDEN_APPLE 12//ok
#define ITEM_ARCANE_NECTAR 13//ok
#define ITEM_FORTUNE_RELIC 14//ok
#define ITEM_BLOOD_STONE_AMULET 15//ok
#define ITEM_VITALITY_ESSENCE 16//ok
#define ITEM_POWER_STONE_RING 17//ok
#define ITEM_WARRIORS_CREST 18

#define ITEM_ASTRAL_COMPASS 8
#define ITEM_ASTRAL_COMPASS_HEALTH_COST 10
#define ITEM_ASTRAL_TELEPORT_TIME 5


// STATS
#define STATS_SIZE 5
#define PLAYER_HEALTH 0
#define PLAYER_LEVEL 1
#define PLAYER_MONEY 2
#define PLAYER_MAX_HEALTH 3 
#define PLAYER_EXPERIENCE 4

// FARBY
#define RGB 3
#define WHITE_ON_BLACK 0
#define RED_ON_BLACK 1
#define GREEN_ON_BLACK 2
#define YELLOW_ON_BLACK 3
#define BLUE_ON_BLACK 4
#define MAGENTA_ON_BLACK 5
#define CYAN_ON_BLACK 6
#define WHITE_ON_WHITE 7
#define MAGENTA_ON_MAGENTA 8
#define CYAN_ON_CYAN 9
#define RED_ON_RED 10
#define GREEN_ON_GREEN 11
#define YELLOW_ON_YELLOW 12
#define BLUE_ON_BLUE 13
#define BLACK_ON_BLACK 19

#define DUNGEON_BORDER_RGB {200, 200, 200}
#define DUNGEON_BORDER_COLOR 14
#define DUNGEON_BORDER_ID_COLOR 20
#define STONE_RGB {500, 500, 500}
#define STONE_COLOR 15
#define STONE_ID_COLOR 21
#define MINEABLE_STONE_RGB {350, 350, 350}
#define MINEABLE_STONE_COLOR 16
#define MINEABLE_STONE_ID_COLOR 22
#define CHEST_RGB {831, 674, 533}
#define CHEST_COLOR 17
#define CHEST_ID_COLOR 23
#define ORANGE_RGB {1000, 647, 0}
#define ORANGE_ON_BLACK 18
#define ORANGE_ID_COLOR 24

// DIRECTIONS
#define DIRECTION_UP 1
#define DIRECTION_DOWN 2
#define DIRECTION_LEFT 3
#define DIRECTION_RIGHT 4

// DUNGEON 
#define RENDER_STRING 3
#define EMPTY_ID 0
#define STONE_ID 1
#define MINEABLE_STONE_ID 2
#define COIN_ID 3
#define ENEMY_ID 4
#define KAREL_UP_ID 5
#define KAREL_DOWN_ID 6
#define KAREL_LEFT_ID 7
#define KAREL_RIGHT_ID 8
#define TELEPORT_UP_ID 9
#define TELEPORT_DOWN_ID 10
#define SHOP_ID 11
#define CHESTS_ID {100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119}
#define CHEST_COUNT 20
struct DungeonEntity {
    int id;
    char render[RENDER_STRING];
    int color_id;
};

// ASCIART
#define ASCI_HEIGHT 7
#define OFFSET_TOP 12

// UTILITY
#define PADDING_LEFT 7
#define PADDING_BETWEEN 4
#define MIN_BASE_COINS 5
#define MAX_BASE_COINS 20
#define TIME_TO_START_FIGHT 4
#define MIN_SCREEN_HEIGHT 55
#define MIN_SCREEN_WIDTH 200

// ENEMY
#define MIN_ENEMY_HEALTH 50
#define MAX_ENEMY_HEALTH 100
#define ENEMY_HEALTH_MULTIPLIER 8
#define MIN_ENEMY_DAMAGE 5
#define MAX_ENEMY_DAMAGE 10
#define ENEMY_DAMAGE_MULTIPLIER 2
#define MIN_ENEMY_KILL_COIN_REWARD 10
#define MAX_ENEMY_KILL_COIN_REWARD 20
#define MIN_ENEMY_KILL_EXPERIENCE_REWARD 35
#define MAX_ENEMY_KILL_EXPERIENCE_REWARD 75
#define MIN_ENEMY_SPEED 500
#define MAX_ENEMY_SPEED 1000

// SHOP
#define SHOP_HEAL_POTION_COST 150
#define SHOP_EXP_POTION_COST 280
#define SHOP_STONE_BREAKER_COST 2750


