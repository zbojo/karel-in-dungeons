/**
 * @brief Initializes ncurses
 */
void prepareNCurses();

/**
 * @brief Initializes colors
 */
void prepareColors();

/**
 * @brief Prepares the game (stats, inventory, spells, items, ...)
 * @param stats The player stats
 * @param inventory The player inventory
 * @param spells The player spells
 */
void prepareGame(int stats[STATS_SIZE], int inventory[INVENTORY_SIZE], int spells[SPELLS_SIZE]);

/**
 * @brief Prepares the player stats
 * @param stats The player stats
 */
void prepareStats(int stats[STATS_SIZE]); 

/**
 * @brief Prepares the player inventory
 * @param inventory The player inventory
 */
void prepareInventory(int inventory[INVENTORY_SIZE]);

/**
 * @brief Prepares the player spells
 * @param spells The player spells
 */
void prepareSpells(int spells[SPELLS_SIZE]);

/**
 * @brief Prepares the items in the game
 */
void prepareItems(struct Item items[ITEMS_SIZE]);

/**
 * @brief Handles the main menu
 * @return 0 - start game, 1 - tutorial, 2 - exit 
 */
int menu();