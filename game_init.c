#include "global.h"
#include "game_init.h"
#include "game.h"
#include "map_handler.h"
#include "utility.h"
#include "render.h"
#include "items.h"

void prepareGame(int stats[STATS_SIZE], int inventory[INVENTORY_SIZE], int spells[SPELLS_SIZE]){
    prepareNCurses();
    prepareColors();
    generateDungeons();
    prepareStats(stats);
    prepareInventory(inventory);
    prepareSpells(spells);
}

void prepareNCurses(){
    srand(time(NULL));
    initscr();
    noecho();
    curs_set(0);
    start_color();
    cbreak();
    keypad(stdscr, TRUE);
}

void prepareColors(){
    int dungeon_rgb[RGB] = DUNGEON_BORDER_RGB;
    init_color(DUNGEON_BORDER_ID_COLOR, dungeon_rgb[0], dungeon_rgb[1], dungeon_rgb[2]);
    init_pair(DUNGEON_BORDER_COLOR, DUNGEON_BORDER_ID_COLOR, DUNGEON_BORDER_ID_COLOR);

    int stone_rgb[RGB] = STONE_RGB;
    init_color(STONE_ID_COLOR, stone_rgb[0], stone_rgb[1], stone_rgb[2]);
    init_pair(STONE_COLOR, STONE_ID_COLOR, STONE_ID_COLOR);

    int mineable_stone_rgb[RGB] = MINEABLE_STONE_RGB;
    init_color(MINEABLE_STONE_ID_COLOR, mineable_stone_rgb[0], mineable_stone_rgb[1], mineable_stone_rgb[2]);
    init_pair(MINEABLE_STONE_COLOR, MINEABLE_STONE_ID_COLOR, MINEABLE_STONE_ID_COLOR);

    int chest_rgb[RGB] = CHEST_RGB;
    init_color(CHEST_ID_COLOR, chest_rgb[0], chest_rgb[1], chest_rgb[2]);
    init_pair(CHEST_COLOR, CHEST_ID_COLOR, CHEST_ID_COLOR);    

    int orange_rgb[RGB] = ORANGE_RGB;
    init_color(ORANGE_ID_COLOR, orange_rgb[0], orange_rgb[1], orange_rgb[2]);
    init_pair(ORANGE_ON_BLACK, ORANGE_ID_COLOR, COLOR_BLACK);

    init_pair(WHITE_ON_BLACK, COLOR_WHITE, COLOR_BLACK);
    init_pair(RED_ON_BLACK, COLOR_RED, COLOR_BLACK);
    init_pair(GREEN_ON_BLACK, COLOR_GREEN, COLOR_BLACK);
    init_pair(YELLOW_ON_BLACK, COLOR_YELLOW, COLOR_BLACK);
    init_pair(BLUE_ON_BLACK, COLOR_BLUE, COLOR_BLACK);
    init_pair(MAGENTA_ON_BLACK, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(CYAN_ON_BLACK, COLOR_CYAN, COLOR_BLACK);
    init_pair(WHITE_ON_WHITE, COLOR_WHITE, COLOR_WHITE);
    init_pair(MAGENTA_ON_MAGENTA, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(CYAN_ON_CYAN, COLOR_CYAN, COLOR_CYAN);
    init_pair(RED_ON_RED, COLOR_RED, COLOR_RED);
    init_pair(GREEN_ON_GREEN, COLOR_GREEN, COLOR_GREEN);
    init_pair(YELLOW_ON_YELLOW, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(BLUE_ON_BLUE, COLOR_BLUE, COLOR_BLUE);
    init_pair(BLACK_ON_BLACK, COLOR_BLACK, COLOR_BLACK);
}

void prepareStats(int stats[STATS_SIZE]){
    stats[PLAYER_HEALTH] = 100;
    stats[PLAYER_LEVEL] = 1;
    stats[PLAYER_MONEY] = 50;
    stats[PLAYER_MAX_HEALTH] = 100;
    stats[PLAYER_EXPERIENCE] = 0;
}

void prepareInventory(int inventory[INVENTORY_SIZE]){
    inventory[ITEM_1] = NO_ITEM;
    inventory[ITEM_2] = NO_ITEM;
    inventory[ITEM_3] = NO_ITEM;
}

void prepareSpells(int spells[SPELLS_SIZE]){
    spells[SPELL_Q] = SPELL_UNLOCKED;
    spells[SPELL_W] = SPELL_LOCKED;
    spells[SPELL_E] = SPELL_LOCKED;
    spells[SPELL_R] = SPELL_LOCKED;
}

void prepareItems(struct Item items[ITEMS_SIZE]){
// ITEM 0
    items[NO_ITEM].id = NO_ITEM;
    strcpy(items[NO_ITEM].name, "Empty");
    strcpy(items[NO_ITEM].description, " ");
    // DAMAGE
    items[NO_ITEM].base_damage = 0;
    items[NO_ITEM].plus_level_damage = 0;
    items[NO_ITEM].multiply_level_damage = 0;
    // HEALTH
    items[NO_ITEM].base_health = 0;
    items[NO_ITEM].plus_level_health = 0;
    items[NO_ITEM].multiply_level_health = 0;
    // COINS
    items[NO_ITEM].coins = 0;
    items[NO_ITEM].coins_multiplier = 0;
    // CONSUMABLE
    items[NO_ITEM].isConsumable = 0;
    items[NO_ITEM].coinsOnConsume = 0;
    items[NO_ITEM].healthOnConsume = 0;
    items[NO_ITEM].experienceOnConsume = 0;
    // UTILITY
    items[NO_ITEM].color = WHITE_ON_BLACK;

// ITEM 1
    items[ITEM_BERSERKER_AXE].id = ITEM_BERSERKER_AXE;
    strcpy(items[ITEM_BERSERKER_AXE].name, "Berserker's Axe");
    strcpy(items[ITEM_BERSERKER_AXE].description, "Deals 10 additional damage to enemies");
    // DAMAGE
    items[ITEM_BERSERKER_AXE].plus_level_damage = 0;
    items[ITEM_BERSERKER_AXE].base_damage = 10;
    items[ITEM_BERSERKER_AXE].multiply_level_damage = 0;
    // HEALTH
    items[ITEM_BERSERKER_AXE].base_health = 0;
    items[ITEM_BERSERKER_AXE].plus_level_health = 0;
    items[ITEM_BERSERKER_AXE].multiply_level_health = 0;
    // COINS
    items[ITEM_BERSERKER_AXE].coins = 0;
    items[ITEM_BERSERKER_AXE].coins_multiplier = 0;
    // CONSUMABLE
    items[ITEM_BERSERKER_AXE].isConsumable = 0;
    items[ITEM_BERSERKER_AXE].coinsOnConsume = 0;
    items[ITEM_BERSERKER_AXE].healthOnConsume = 0;
    items[ITEM_BERSERKER_AXE].experienceOnConsume = 0;
    // UTILITY
    items[ITEM_BERSERKER_AXE].color = BLUE_ON_BLACK;

// ITEM 2
    items[ITEM_LONGSWORD].id = ITEM_LONGSWORD;
    strcpy(items[ITEM_LONGSWORD].name, "Longsword");
    strcpy(items[ITEM_LONGSWORD].description, "Deals 5 additional damage to enemies");
    // DAMAGE
    items[ITEM_LONGSWORD].base_damage = 5;
    items[ITEM_LONGSWORD].plus_level_damage = 0;
    items[ITEM_LONGSWORD].multiply_level_damage = 0;
    // HEALTH
    items[ITEM_LONGSWORD].base_health = 0;
    items[ITEM_LONGSWORD].plus_level_health = 0;
    items[ITEM_LONGSWORD].multiply_level_health = 0;
    // COINS
    items[ITEM_LONGSWORD].coins = 0;
    items[ITEM_LONGSWORD].coins_multiplier = 0;
    // CONSUMABLE
    items[ITEM_LONGSWORD].isConsumable = 0;
    items[ITEM_LONGSWORD].coinsOnConsume = 0;
    items[ITEM_LONGSWORD].healthOnConsume = 0;
    items[ITEM_LONGSWORD].experienceOnConsume = 0;
    // UTILITY
    items[ITEM_LONGSWORD].color = BLUE_ON_BLACK;

// ITEM 3
    items[ITEM_VENOMSHARD_DAGGER].id = ITEM_VENOMSHARD_DAGGER;
    strcpy(items[ITEM_VENOMSHARD_DAGGER].name, "Venomshard Dagger");
    strcpy(items[ITEM_VENOMSHARD_DAGGER].description, "Deals 10 + your level additional damage to enemies");
    // DAMAGE
    items[ITEM_VENOMSHARD_DAGGER].plus_level_damage = 10;
    items[ITEM_VENOMSHARD_DAGGER].base_damage = 0;
    items[ITEM_VENOMSHARD_DAGGER].multiply_level_damage = 0;
    // HEALTH
    items[ITEM_VENOMSHARD_DAGGER].base_health = 0;
    items[ITEM_VENOMSHARD_DAGGER].plus_level_health = 0;
    items[ITEM_VENOMSHARD_DAGGER].multiply_level_health = 0;
    // COINS
    items[ITEM_VENOMSHARD_DAGGER].coins = 0;
    items[ITEM_VENOMSHARD_DAGGER].coins_multiplier = 0;
    // CONSUMABLE
    items[ITEM_VENOMSHARD_DAGGER].isConsumable = 0;
    items[ITEM_VENOMSHARD_DAGGER].coinsOnConsume = 0;
    items[ITEM_VENOMSHARD_DAGGER].healthOnConsume = 0;
    items[ITEM_VENOMSHARD_DAGGER].experienceOnConsume = 0;
    // UTILITY
    items[ITEM_VENOMSHARD_DAGGER].color = BLUE_ON_BLACK;

// ITEM 4
    items[ITEM_THUNDER_HAMMER].id = ITEM_THUNDER_HAMMER;
    strcpy(items[ITEM_THUNDER_HAMMER].name, "Thunder Hammer");
    strcpy(items[ITEM_THUNDER_HAMMER].description, "Deals 2 * your level additional damage to enemies");
    // DAMAGE
    items[ITEM_THUNDER_HAMMER].plus_level_damage = 0;
    items[ITEM_THUNDER_HAMMER].base_damage = 0;
    items[ITEM_THUNDER_HAMMER].multiply_level_damage = 2;
    // HEALTH
    items[ITEM_THUNDER_HAMMER].base_health = 0;
    items[ITEM_THUNDER_HAMMER].plus_level_health = 0;
    items[ITEM_THUNDER_HAMMER].multiply_level_health = 0;
    // COINS
    items[ITEM_THUNDER_HAMMER].coins = 0;
    items[ITEM_THUNDER_HAMMER].coins_multiplier = 0;
    // CONSUMABLE
    items[ITEM_THUNDER_HAMMER].isConsumable = 0;
    items[ITEM_THUNDER_HAMMER].coinsOnConsume = 0;
    items[ITEM_THUNDER_HAMMER].healthOnConsume = 0;
    items[ITEM_THUNDER_HAMMER].experienceOnConsume = 0;
    // UTILITY
    items[ITEM_THUNDER_HAMMER].color = BLUE_ON_BLACK;

// ITEM 5
    items[ITEM_STONEBREAKER].id = ITEM_STONEBREAKER;
    strcpy(items[ITEM_STONEBREAKER].name, "Stonebreaker");
    strcpy(items[ITEM_STONEBREAKER].description, "You can break specific stones with this item");
    // DAMAGE
    items[ITEM_STONEBREAKER].plus_level_damage = 0;
    items[ITEM_STONEBREAKER].base_damage = 0;
    items[ITEM_STONEBREAKER].multiply_level_damage = 0;
    // HEALTH
    items[ITEM_STONEBREAKER].base_health = 0;
    items[ITEM_STONEBREAKER].plus_level_health = 0;
    items[ITEM_STONEBREAKER].multiply_level_health = 0;
    // COINS
    items[ITEM_STONEBREAKER].coins = 0;
    items[ITEM_STONEBREAKER].coins_multiplier = 0;
    // CONSUMABLE
    items[ITEM_STONEBREAKER].isConsumable = 0;
    items[ITEM_STONEBREAKER].coinsOnConsume = 0;
    items[ITEM_STONEBREAKER].healthOnConsume = 0;
    items[ITEM_STONEBREAKER].experienceOnConsume = 0;
    // UTILITY
    items[ITEM_STONEBREAKER].color = MAGENTA_ON_BLACK;

// ITEM 6
    items[ITEM_PHOENIX_STONE].id = ITEM_PHOENIX_STONE;
    strcpy(items[ITEM_PHOENIX_STONE].name, "Phoenix Stone");
    strcpy(items[ITEM_PHOENIX_STONE].description, "Gives you 20 additional health");
    // DAMAGE
    items[ITEM_PHOENIX_STONE].plus_level_damage = 0;
    items[ITEM_PHOENIX_STONE].base_damage = 0;
    items[ITEM_PHOENIX_STONE].multiply_level_damage = 0;
    // HEALTH
    items[ITEM_PHOENIX_STONE].base_health = 20;
    items[ITEM_PHOENIX_STONE].plus_level_health = 0;
    items[ITEM_PHOENIX_STONE].multiply_level_health = 0;
    // COINS
    items[ITEM_PHOENIX_STONE].coins = 0;
    items[ITEM_PHOENIX_STONE].coins_multiplier = 0;
    // CONSUMABLE
    items[ITEM_PHOENIX_STONE].isConsumable = 0;
    items[ITEM_PHOENIX_STONE].coinsOnConsume = 0;
    items[ITEM_PHOENIX_STONE].healthOnConsume = 0;
    items[ITEM_PHOENIX_STONE].experienceOnConsume = 0;
    // UTILITY
    items[ITEM_PHOENIX_STONE].color = BLUE_ON_BLACK;

// ITEM 7
    items[ITEM_HEALING_POTION].id = ITEM_HEALING_POTION;
    strcpy(items[ITEM_HEALING_POTION].name, "Healing Potion");
    strcpy(items[ITEM_HEALING_POTION].description, "Consume to heal 20 health");
    // DAMAGE
    items[ITEM_HEALING_POTION].plus_level_damage = 0;
    items[ITEM_HEALING_POTION].base_damage = 0;
    items[ITEM_HEALING_POTION].multiply_level_damage = 0;
    // HEALTH
    items[ITEM_HEALING_POTION].base_health = 0;
    items[ITEM_HEALING_POTION].plus_level_health = 0;
    items[ITEM_HEALING_POTION].multiply_level_health = 0;
    // COINS
    items[ITEM_HEALING_POTION].coins = 0;
    items[ITEM_HEALING_POTION].coins_multiplier = 0;
    // CONSUMABLE
    items[ITEM_HEALING_POTION].isConsumable = 1;
    items[ITEM_HEALING_POTION].coinsOnConsume = 0;
    items[ITEM_HEALING_POTION].healthOnConsume = 20;
    items[ITEM_HEALING_POTION].experienceOnConsume = 0;
    // UTILITY
    items[ITEM_HEALING_POTION].color = GREEN_ON_BLACK;

// ITEM 8
    items[ITEM_ASTRAL_COMPASS].id = ITEM_ASTRAL_COMPASS;
    strcpy(items[ITEM_ASTRAL_COMPASS].name, "Astral Compass");
    strcpy(items[ITEM_ASTRAL_COMPASS].description, "Teleports you to a spawn but takes 10 health");
    // DAMAGE
    items[ITEM_ASTRAL_COMPASS].plus_level_damage = 0;
    items[ITEM_ASTRAL_COMPASS].base_damage = 0;
    items[ITEM_ASTRAL_COMPASS].multiply_level_damage = 0;
    // HEALTH
    items[ITEM_ASTRAL_COMPASS].base_health = 0;
    items[ITEM_ASTRAL_COMPASS].plus_level_health = 0;
    items[ITEM_ASTRAL_COMPASS].multiply_level_health = 0;
    // COINS
    items[ITEM_ASTRAL_COMPASS].coins = 0;
    items[ITEM_ASTRAL_COMPASS].coins_multiplier = 0;
    // CONSUMABLE
    items[ITEM_ASTRAL_COMPASS].isConsumable = 0;
    items[ITEM_ASTRAL_COMPASS].coinsOnConsume = 0;
    items[ITEM_ASTRAL_COMPASS].healthOnConsume = 0;
    items[ITEM_ASTRAL_COMPASS].experienceOnConsume = 0;
    // UTILITY
    items[ITEM_ASTRAL_COMPASS].color = MAGENTA_ON_BLACK;

// ITEM 9
    items[ITEM_EXP_POTION].id = ITEM_EXP_POTION;
    strcpy(items[ITEM_EXP_POTION].name, "Elixir of Mastery");
    strcpy(items[ITEM_EXP_POTION].description, "Consume to gain 100 experience and 5 health");
    // DAMAGE
    items[ITEM_EXP_POTION].plus_level_damage = 0;
    items[ITEM_EXP_POTION].base_damage = 0;
    items[ITEM_EXP_POTION].multiply_level_damage = 0;
    // HEALTH
    items[ITEM_EXP_POTION].base_health = 0;
    items[ITEM_EXP_POTION].plus_level_health = 0;
    items[ITEM_EXP_POTION].multiply_level_health = 0;
    // COINS
    items[ITEM_EXP_POTION].coins = 0;
    items[ITEM_EXP_POTION].coins_multiplier = 0;
    // CONSUMABLE
    items[ITEM_EXP_POTION].isConsumable = 1;
    items[ITEM_EXP_POTION].coinsOnConsume = 0;
    items[ITEM_EXP_POTION].healthOnConsume = 5;
    items[ITEM_EXP_POTION].experienceOnConsume = 100;
    // UTILITY
    items[ITEM_EXP_POTION].color = GREEN_ON_BLACK;

// ITEM 10
    items[ITEM_CLAIRVOYANT_ORB].id = ITEM_CLAIRVOYANT_ORB;
    strcpy(items[ITEM_CLAIRVOYANT_ORB].name, "Claivoyant Orb");
    strcpy(items[ITEM_CLAIRVOYANT_ORB].description, "Shows approximate enemy health and damage");
    // DAMAGE
    items[ITEM_CLAIRVOYANT_ORB].plus_level_damage = 0;
    items[ITEM_CLAIRVOYANT_ORB].base_damage = 0;
    items[ITEM_CLAIRVOYANT_ORB].multiply_level_damage = 0;
    // HEALTH
    items[ITEM_CLAIRVOYANT_ORB].base_health = 0;
    items[ITEM_CLAIRVOYANT_ORB].plus_level_health = 0;
    items[ITEM_CLAIRVOYANT_ORB].multiply_level_health = 0;
    // COINS
    items[ITEM_CLAIRVOYANT_ORB].coins = 0;
    items[ITEM_CLAIRVOYANT_ORB].coins_multiplier = 0;
    // CONSUMABLE
    items[ITEM_CLAIRVOYANT_ORB].isConsumable = 0;
    items[ITEM_CLAIRVOYANT_ORB].coinsOnConsume = 0;
    items[ITEM_CLAIRVOYANT_ORB].healthOnConsume = 0;
    items[ITEM_CLAIRVOYANT_ORB].experienceOnConsume = 0;
    // UTILITY
    items[ITEM_CLAIRVOYANT_ORB].color = MAGENTA_ON_BLACK;

// ITEM 11
    items[ITEM_GEM_JUICE].id = ITEM_GEM_JUICE;
    strcpy(items[ITEM_GEM_JUICE].name, "Gem Juice");
    strcpy(items[ITEM_GEM_JUICE].description, "Consume to gain 50 coins");
    // DAMAGE
    items[ITEM_GEM_JUICE].plus_level_damage = 0;
    items[ITEM_GEM_JUICE].base_damage = 0;
    items[ITEM_GEM_JUICE].multiply_level_damage = 0;
    // HEALTH
    items[ITEM_GEM_JUICE].base_health = 0;
    items[ITEM_GEM_JUICE].plus_level_health = 0;
    items[ITEM_GEM_JUICE].multiply_level_health = 0;
    // COINS
    items[ITEM_GEM_JUICE].coins = 0;
    items[ITEM_GEM_JUICE].coins_multiplier = 0;
    // CONSUMABLE
    items[ITEM_GEM_JUICE].isConsumable = 1;
    items[ITEM_GEM_JUICE].coinsOnConsume = 50;
    items[ITEM_GEM_JUICE].healthOnConsume = 0;
    items[ITEM_GEM_JUICE].experienceOnConsume = 0;
    // UTILITY
    items[ITEM_GEM_JUICE].color = GREEN_ON_BLACK;

// ITEM 12
    items[ITEM_GOLDEN_APPLE].id = ITEM_GOLDEN_APPLE;
    strcpy(items[ITEM_GOLDEN_APPLE].name, "Golden Apple");
    strcpy(items[ITEM_GOLDEN_APPLE].description, "Consume to gain 100 coins");
    // DAMAGE
    items[ITEM_GOLDEN_APPLE].plus_level_damage = 0;
    items[ITEM_GOLDEN_APPLE].base_damage = 0;
    items[ITEM_GOLDEN_APPLE].multiply_level_damage = 0;
    // HEALTH
    items[ITEM_GOLDEN_APPLE].base_health = 0;
    items[ITEM_GOLDEN_APPLE].plus_level_health = 0;
    items[ITEM_GOLDEN_APPLE].multiply_level_health = 0;
    // COINS
    items[ITEM_GOLDEN_APPLE].coins = 0;
    items[ITEM_GOLDEN_APPLE].coins_multiplier = 0;
    // CONSUMABLE
    items[ITEM_GOLDEN_APPLE].isConsumable = 1;
    items[ITEM_GOLDEN_APPLE].coinsOnConsume = 100;
    items[ITEM_GOLDEN_APPLE].healthOnConsume = 0;
    items[ITEM_GOLDEN_APPLE].experienceOnConsume = 0;
    // UTILITY
    items[ITEM_GOLDEN_APPLE].color = GREEN_ON_BLACK;

// ITEM 13
    items[ITEM_ARCANE_NECTAR].id = ITEM_ARCANE_NECTAR;
    strcpy(items[ITEM_ARCANE_NECTAR].name, "Arcane Nectar");
    strcpy(items[ITEM_ARCANE_NECTAR].description, "Consume to gain 300 experience, 300 health, 300 coins");
    // DAMAGE
    items[ITEM_ARCANE_NECTAR].plus_level_damage = 0;
    items[ITEM_ARCANE_NECTAR].base_damage = 0;
    items[ITEM_ARCANE_NECTAR].multiply_level_damage = 0;
    // HEALTH
    items[ITEM_ARCANE_NECTAR].base_health = 0;
    items[ITEM_ARCANE_NECTAR].plus_level_health = 0;
    items[ITEM_ARCANE_NECTAR].multiply_level_health = 0;
    // COINS
    items[ITEM_ARCANE_NECTAR].coins = 0;
    items[ITEM_ARCANE_NECTAR].coins_multiplier = 0;
    // CONSUMABLE
    items[ITEM_ARCANE_NECTAR].isConsumable = 1;
    items[ITEM_ARCANE_NECTAR].coinsOnConsume = 300;
    items[ITEM_ARCANE_NECTAR].healthOnConsume = 300;
    items[ITEM_ARCANE_NECTAR].experienceOnConsume = 300;
    // UTILITY
    items[ITEM_ARCANE_NECTAR].color = GREEN_ON_BLACK;

// ITEM 14
    items[ITEM_FORTUNE_RELIC].id = ITEM_FORTUNE_RELIC;
    strcpy(items[ITEM_FORTUNE_RELIC].name, "Fortune Relic");
    strcpy(items[ITEM_FORTUNE_RELIC].description, "Multiplies coins you pick up by 2");
    // DAMAGE
    items[ITEM_FORTUNE_RELIC].plus_level_damage = 0;
    items[ITEM_FORTUNE_RELIC].base_damage = 0;
    items[ITEM_FORTUNE_RELIC].multiply_level_damage = 0;
    // HEALTH
    items[ITEM_FORTUNE_RELIC].base_health = 0;
    items[ITEM_FORTUNE_RELIC].plus_level_health = 0;
    items[ITEM_FORTUNE_RELIC].multiply_level_health = 0;
    // COINS
    items[ITEM_FORTUNE_RELIC].coins = 0;
    items[ITEM_FORTUNE_RELIC].coins_multiplier = 2;
    // CONSUMABLE
    items[ITEM_FORTUNE_RELIC].isConsumable = 0;
    items[ITEM_FORTUNE_RELIC].coinsOnConsume = 0;
    items[ITEM_FORTUNE_RELIC].healthOnConsume = 0;
    items[ITEM_FORTUNE_RELIC].experienceOnConsume = 0;
    // UTILITY
    items[ITEM_FORTUNE_RELIC].color = BLUE_ON_BLACK;

// ITEM 15
    items[ITEM_BLOOD_STONE_AMULET].id = ITEM_BLOOD_STONE_AMULET;
    strcpy(items[ITEM_BLOOD_STONE_AMULET].name, "Blood Stone Amulet");
    strcpy(items[ITEM_BLOOD_STONE_AMULET].description, "Gives you 20 + level additional health");
    // DAMAGE
    items[ITEM_BLOOD_STONE_AMULET].plus_level_damage = 0;
    items[ITEM_BLOOD_STONE_AMULET].base_damage = 0;
    items[ITEM_BLOOD_STONE_AMULET].multiply_level_damage = 0;
    // HEALTH
    items[ITEM_BLOOD_STONE_AMULET].base_health = 0;
    items[ITEM_BLOOD_STONE_AMULET].plus_level_health = 20;
    items[ITEM_BLOOD_STONE_AMULET].multiply_level_health = 0;
    // COINS
    items[ITEM_BLOOD_STONE_AMULET].coins = 0;
    items[ITEM_BLOOD_STONE_AMULET].coins_multiplier = 0;
    // CONSUMABLE
    items[ITEM_BLOOD_STONE_AMULET].isConsumable = 0;
    items[ITEM_BLOOD_STONE_AMULET].coinsOnConsume = 0;
    items[ITEM_BLOOD_STONE_AMULET].healthOnConsume = 0;
    items[ITEM_BLOOD_STONE_AMULET].experienceOnConsume = 0;
    // UTILITY
    items[ITEM_BLOOD_STONE_AMULET].color = BLUE_ON_BLACK;

// ITEM 16 
    items[ITEM_VITALITY_ESSENCE].id = ITEM_VITALITY_ESSENCE;
    strcpy(items[ITEM_VITALITY_ESSENCE].name, "Vitality Rune");
    strcpy(items[ITEM_VITALITY_ESSENCE].description, "Gives you 2 * your level additional health");
    // DAMAGE
    items[ITEM_VITALITY_ESSENCE].plus_level_damage = 0;
    items[ITEM_VITALITY_ESSENCE].base_damage = 0;
    items[ITEM_VITALITY_ESSENCE].multiply_level_damage = 0;
    // HEALTH
    items[ITEM_VITALITY_ESSENCE].base_health = 0;
    items[ITEM_VITALITY_ESSENCE].plus_level_health = 0;
    items[ITEM_VITALITY_ESSENCE].multiply_level_health = 2;
    // COINS
    items[ITEM_VITALITY_ESSENCE].coins = 0;
    items[ITEM_VITALITY_ESSENCE].coins_multiplier = 0;
    // CONSUMABLE
    items[ITEM_VITALITY_ESSENCE].isConsumable = 0;
    items[ITEM_VITALITY_ESSENCE].coinsOnConsume = 0;
    items[ITEM_VITALITY_ESSENCE].healthOnConsume = 0;
    items[ITEM_VITALITY_ESSENCE].experienceOnConsume = 0;
    // UTILITY
    items[ITEM_VITALITY_ESSENCE].color = BLUE_ON_BLACK;

// ITEM 17
    items[ITEM_POWER_STONE_RING].id = ITEM_POWER_STONE_RING;
    strcpy(items[ITEM_POWER_STONE_RING].name, "Power Stone Ring");
    strcpy(items[ITEM_POWER_STONE_RING].description, "Gives you 25 additional health and 15 damage");
    // DAMAGE
    items[ITEM_POWER_STONE_RING].plus_level_damage = 0;
    items[ITEM_POWER_STONE_RING].base_damage = 15;
    items[ITEM_POWER_STONE_RING].multiply_level_damage = 0;
    // HEALTH
    items[ITEM_POWER_STONE_RING].base_health = 25;
    items[ITEM_POWER_STONE_RING].plus_level_health = 0;
    items[ITEM_POWER_STONE_RING].multiply_level_health = 0;
    // COINS
    items[ITEM_POWER_STONE_RING].coins = 0;
    items[ITEM_POWER_STONE_RING].coins_multiplier = 0;
    // CONSUMABLE
    items[ITEM_POWER_STONE_RING].isConsumable = 0;
    items[ITEM_POWER_STONE_RING].coinsOnConsume = 0;
    items[ITEM_POWER_STONE_RING].healthOnConsume = 0;
    items[ITEM_POWER_STONE_RING].experienceOnConsume = 0;
    // UTILITY
    items[ITEM_POWER_STONE_RING].color = BLUE_ON_BLACK;

// ITEM 18
    items[ITEM_WARRIORS_CREST].id = ITEM_WARRIORS_CREST;
    strcpy(items[ITEM_WARRIORS_CREST].name, "Warrior's Crest");
    strcpy(items[ITEM_WARRIORS_CREST].description, "Gives you additional 2 * your level health and 1 + level damage");
    // DAMAGE
    items[ITEM_WARRIORS_CREST].plus_level_damage = 1;
    items[ITEM_WARRIORS_CREST].base_damage = 0;
    items[ITEM_WARRIORS_CREST].multiply_level_damage = 0;
    // HEALTH
    items[ITEM_WARRIORS_CREST].base_health = 0;
    items[ITEM_WARRIORS_CREST].plus_level_health = 2;
    items[ITEM_WARRIORS_CREST].multiply_level_health = 0;
    // COINS
    items[ITEM_WARRIORS_CREST].coins = 0;
    items[ITEM_WARRIORS_CREST].coins_multiplier = 0;
    // CONSUMABLE
    items[ITEM_WARRIORS_CREST].isConsumable = 0;
    items[ITEM_WARRIORS_CREST].coinsOnConsume = 0;
    items[ITEM_WARRIORS_CREST].healthOnConsume = 0;
    items[ITEM_WARRIORS_CREST].experienceOnConsume = 0;
    // UTILITY
    items[ITEM_WARRIORS_CREST].color = BLUE_ON_BLACK;
}

int menu(){
    printAsciTitleArt();
    int selected_line = 0;

    attron(COLOR_PAIR(BLUE_ON_BLACK));
    mvprintw(ASCI_HEIGHT+5, 161 / 2 - 9, "> Start New Game <"); 
    attroff(COLOR_PAIR(BLUE_ON_BLACK));
    mvprintw(ASCI_HEIGHT+7, 161 / 2 - 4, "Tutorial");          
    mvprintw(ASCI_HEIGHT+9, 161 / 2 - 5, "Leave Game");

    while(1){
        int ch = getch();
        if(ch == KEY_UP && selected_line > 0){
            selected_line-=1;
        }else if(ch == KEY_DOWN && selected_line < 3){
            selected_line+=1; 
        }else if(ch == 10){
            return selected_line;
        }

        if(selected_line == 0){
            clearLines(ASCI_HEIGHT+5, 0, 10);
            attron(COLOR_PAIR(BLUE_ON_BLACK));
            mvprintw(ASCI_HEIGHT+5, 161 / 2 - 9, "> Start New Game <"); 
            attroff(COLOR_PAIR(BLUE_ON_BLACK));
            mvprintw(ASCI_HEIGHT+7, 161 / 2 - 4, "Tutorial");          
            mvprintw(ASCI_HEIGHT+9, 161 / 2 - 5, "Leave Game");
        }else if(selected_line == 1){
            clearLines(ASCI_HEIGHT+5, 0, 10);
            mvprintw(ASCI_HEIGHT+5, 161 / 2 - 7, "Start New Game"); 
            attron(COLOR_PAIR(BLUE_ON_BLACK));
            mvprintw(ASCI_HEIGHT+7, 161 / 2 - 6, "> Tutorial < ");    
            attroff(COLOR_PAIR(BLUE_ON_BLACK));      
            mvprintw(ASCI_HEIGHT+9, 161 / 2 - 5, "Leave Game");
        }else if(selected_line == 2){
            clearLines(ASCI_HEIGHT+5, 0, 10);
            mvprintw(ASCI_HEIGHT+5, 161 / 2 - 7, "Start New Game"); 
            mvprintw(ASCI_HEIGHT+7, 161 / 2 - 4, "Tutorial"); 
            attron(COLOR_PAIR(BLUE_ON_BLACK));         
            mvprintw(ASCI_HEIGHT+9, 161 / 2 - 7, "> Leave Game <");
            attroff(COLOR_PAIR(BLUE_ON_BLACK));
        }

        refresh();
    }
    return selected_line;
}