
/**
 * @brief Gets coin multiplier from items in inventory
 * @param inventory The player inventory
 * @param items The items in the game
 * @return The coin multiplier
 */
int getCoinMultiplier(int inventory[INVENTORY_SIZE], struct Item items[ITEMS_SIZE]);

/**
 * @brief Gets damage multiplier from items in inventory
 * @param inventory The player inventory
 * @param items The items in the game
 * @return The damage multiplier
 */
int getDamageFromItems(int inventory[INVENTORY_SIZE], struct Item items[ITEMS_SIZE], int stats[STATS_SIZE]);

/**
 * @brief Gets health multiplier from items in inventory
 * @param inventory The player inventory
 * @param items The items in the game
 * @return The health multiplier
 */
int getHealthFromItems(int inventory[INVENTORY_SIZE], struct Item items[ITEMS_SIZE], int stats[STATS_SIZE]);


