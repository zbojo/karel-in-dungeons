
/**
 * @brief Load a dungeon from a file
 */
void loadDungeon(const char *filename, struct DungeonEntity dungeon[DUNGEON_HEIGHT][DUNGEON_WIDTH]);

/**
 * @brief Save a dungeon to a file
 */
void saveDungeon(const char *filename, struct DungeonEntity dungeon[DUNGEON_HEIGHT][DUNGEON_WIDTH]);

/**
 * @brief Generate a dungeons
 */
void generateDungeons();