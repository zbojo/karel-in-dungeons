/**
 * @brief Prints the title art to the screen
 */
void printAsciTitleArt();

/**
 * @brief Clears multiple lines from the screen
 * @param y The y position to start clearing
 * @param x The x position to start clearing
 * @param count The number of lines to clear
 */
void clearLines(int y, int x, int lines);

/**
 * @brief Gets the y position of Karel
 * @param dungeon The dungeon
 * @return The y position of Karel
 */
int getKarelY(struct DungeonEntity dungeon[DUNGEON_HEIGHT][DUNGEON_WIDTH]);

/**
 * @brief Gets the x position of Karel
 * @param dungeon The dungeon
 * @return The x position of Karel
 */
int getKarelX(struct DungeonEntity dungeon[DUNGEON_HEIGHT][DUNGEON_WIDTH]);

/**
 * @brief Checks if an item is in the inventory
 * @param inventory The player inventory
 * @param item_id The item id to check
 * @return 1 if the item is in the inventory, 0 otherwise
 */
int isInInventory(int inventory[INVENTORY_SIZE], int item_id);

/**
 * @brief Checks if a input is in the chest array
 * @param chests The chest array
 * @param chest_id The chest id to check
 * @return 1 if the input is in the chest array, 0 otherwise
 */
int isInChest(int chests[CHEST_COUNT], int chest_id);

/**
 * @brief Generates a random number between min and max
 * @param min The minimum number
 * @param max The maximum number
 * @return The random number
 */
int generateRandomNumber(int min, int max);

/**
 * @brief Display main screen menu
 * @param stats The player stats
 * @param inventory The player inventory
 * @param spells The player spells
 * @param items The items available in the game
 */
void mainScreen(int stats[STATS_SIZE], int inventory[INVENTORY_SIZE], int spells[SPELLS_SIZE], struct Item items[ITEMS_SIZE]);

/**
 * @brief Handle inventory actions
 * @param inventory The player inventory
 * @param items The items available in the game
 * @param stats The player stats
 */
void inventoryHandler(int inventory[INVENTORY_SIZE], struct Item items[ITEMS_SIZE], int stats[STATS_SIZE]);

/**
 * @brief Inspects the player spells
 * @param spells The player spells
 * @param stats The player stats
 */
void spellsInspector(int spells[SPELLS_SIZE], int stats[STATS_SIZE]);

/**
 * @brief Handle player experience (level up)
 */
void experienceHandler(int stats[STATS_SIZE], int spells[SPELLS_SIZE]);

/**
 * @brief Handle shop actions
 * @param inventory The player inventory
 * @param items The items available in the game
 * @param stats The player stats
 */
void shopHandler(int inventory[INVENTORY_SIZE], struct Item items[ITEMS_SIZE], int stats[STATS_SIZE]);

/**
 * @brief Prints titles in spawn dungeons behind the border
 */
void spawnInfo();

/**
 * @brief Handle chest opening
 * @param chest_id The chest id - 100
 * @param inventory The player inventory
 * @param items The items available in the game
 * @return 0 if the chest wasn't looted, 1 if the chest was looted
 */
int openChest(int chest_id, int inventory[INVENTORY_SIZE], struct Item items[ITEMS_SIZE]);

/**
 * @brief Prints data when player has Clairvoyant Orb - special item
 */
void printClair(int stats[STATS_SIZE]);

/**
 * @brief Prints tutorial
 */
void tutorial();

/**
 * @brief Checks if the terminal has the required size and color support
 * @return 0 - good requirements, 1 - wrong terminal size, 2 - no color support
 */
int checkRequirements();
