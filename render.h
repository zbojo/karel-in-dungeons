/** 
 * @brief Prints the dungeon to the screen
 * @param dungeon The 2D array of DungeonEntity structs that represent the dungeon
*/
void printDungeon(struct DungeonEntity dungeon[DUNGEON_HEIGHT][DUNGEON_WIDTH]);

/** 
 * @brief Prints borders around the dungeon, inventory, stats, and spells
 * @param color_dungeon_border The color of the dungeon border
 * @param color_inventory_border The color of the inventory border
 * @param color_stats_border The color of the stats border
 * @param color_spells_border The color of the spells border
*/
void printLayout(int color_dungeon_border, int color_inventory_border, int color_stats_border, int color_spells_border);

/** 
 * @brief Prints the player data to the screen
 * @param stats The player stats
 * @param inventory The player inventory
 * @param spells All the spells in the game
 * @param items All the items in the game
*/
void printData(int stats[STATS_SIZE], int inventory[INVENTORY_SIZE], int spells[SPELLS_SIZE], struct Item items[ITEMS_SIZE]);

/** 
 * @brief Prints the border around the dungeon
 * @param color_dungeon_border The color of the dungeon border
*/
void printDungeonBorder(int color_dungeon_border);

/** 
 * @brief Prints the border around the inventory
 * @param color_inventory_border The color of the inventory border
*/
void printInventoryBorder(int color_inventory_border);

/** 
 * @brief Prints the border around the stats
 * @param color_stats_border The color of the stats border
*/
void printStatsBorder(int color_stats_border);

/** 
 * @brief Prints the border around the spells
 * @param color_spells_border The color of the spells border
*/
void printSpellsBorder(int color_spells_border);

/** 
 * @brief Prints the inventory content 
 * @param inventory The player inventory
*/
void printInventoryContent(int inventory[INVENTORY_SIZE], struct Item items[ITEMS_SIZE]);

/** 
 * @brief Prints the stats content 
 * @param stats The player stats
*/
void printStatsContent(int stats[STATS_SIZE]);

/** 
 * @brief Prints the spells content 
 * @param spells The player spells
*/
void printSpellsContent(int spells[SPELLS_SIZE]);

/** 
 * @brief Prints the extra slot border
 * @param color_extra_slot_border The color of the extra slot border
*/
void printExtraSlotBorder(int color_extra_slot_border);