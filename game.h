/** 
 * @brief Handles the game loop and the game logic
 * @param stats The player stats
 * @param inventory The player inventory
 * @param spells The player spells
*/
void game(int stats[STATS_SIZE], int inventory[INVENTORY_SIZE], int spells[SPELLS_SIZE], struct Item items[ITEMS_SIZE]);

/** 
 * @brief Gets the next move from the player
 * @return 1 - up, 2 - down, 3 - left, 4 - right, 5 - inventory, 6 - spells, 7 - recall to spawn
*/
int getNextMove();

/** 
 * @brief Gets the entity the player is facing
 * @param dungeon The dungeon
 * @param direction The direction the player is facing
 * @return The entity the player is facing
*/
int getFacingEntity(struct DungeonEntity dungeon[DUNGEON_HEIGHT][DUNGEON_WIDTH], int direction);

/** 
 * @brief Handles the game logic for moving the player
 * @param dungeon The dungeon
 * @param direction The direction the player is moving
 * @param stats The player stats
 * @param inventory The player inventory
 * @param spells The player spells
 * @param items The items in the game
 * @return -1 invalid move, 0 valid move, 1 teleport to next dungeon, 2 teleport to previous dungeon
*/
int handleMove(struct DungeonEntity dungeon[DUNGEON_HEIGHT][DUNGEON_WIDTH], int direction, int stats[STATS_SIZE], int inventory[INVENTORY_SIZE], int spells[SPELLS_SIZE], struct Item items[ITEMS_SIZE]);

/** 
 * @brief Handles the player fighting an enemy
 * @param dungeon The dungeon
 * @param stats The player stats
 * @param inventory The player inventory
 * @param spells The player spells
 * @param items The items in the game
 * @param direction The direction the player is facing
 * @return 1 if the player won, 0 if the player lost
*/
int fightEnemy(struct DungeonEntity dungeon[DUNGEON_HEIGHT][DUNGEON_WIDTH], int stats[STATS_SIZE], int inventory[INVENTORY_SIZE], int spells[SPELLS_SIZE], struct Item items[ITEMS_SIZE], int direction);

