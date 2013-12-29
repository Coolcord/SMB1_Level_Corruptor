#ifndef SMB1LEVELGENERATOR_H
#define SMB1LEVELGENERATOR_H

#include <fstream>
#include <vector>

class SMB1LevelGenerator
{
public:
    SMB1LevelGenerator();
    bool RandomizeAllLevels(std::fstream &file);
    bool isROMValid(std::fstream &file);
private:
    bool RandomizeLevel(std::fstream &file, int objectOffset, int EnemyOffset);
    void GenerateBasicLevel(std::vector<unsigned char> &header, std::vector<unsigned char> &objects, std::vector<unsigned char> &enemies);
    void GenerateTreeLevel(std::vector<unsigned char> &header, std::vector<unsigned char> &objects, std::vector<unsigned char> &enemies);
    int AddItemsToBlockRow(int maxObjects, int &objectsLeft, std::vector<unsigned char> &objects, int blockRow);
    bool isBannedObject(std::vector<unsigned char> &hex);
    bool isBannedEnemy(std::vector<unsigned char> &hex);
    void RandomizeObjects(std::vector<unsigned char> &objects);
    void RandomizeEnemies(std::vector<unsigned char> &enemies);
    std::vector<unsigned char> ReadLevelHeader(std::fstream &file, int offset);
    std::vector<unsigned char> ReadLevelObjects(std::fstream &file, int offset);
    std::vector<unsigned char> ReadLevelEnemies(std::fstream &file, int offset);
    int LowballRandomValue(int min, int max);
    std::vector<unsigned char> NESHeader = { 0x4E, 0x45, 0x53, 0x1A };
};

#endif // SMB1LEVELGENERATOR_H
