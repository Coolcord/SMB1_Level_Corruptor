#include "smb1levelgenerator.h"
#include "binarymanipulator.h"
#include <cstdlib>
#include <vector>

//Don't mess with castles until you can end them with an axe!
const int LEVEL_1_1_OBJECTS = 0x000026A0;
const int LEVEL_1_1_ENEMIES = 0x00001F11;
const int LEVEL_1_2_OBJECTS = 0x00002C47;
const int LEVEL_1_2_ENEMIES = 0x000020E8;
const int LEVEL_1_3_OBJECTS = 0x00002705;
const int LEVEL_1_3_ENEMIES = 0x00001F2F;
//const int LEVEL_1_4_OBJECTS = 0x000021C1;
//const int LEVEL_1_4_ENEMIES = 0x00001D80;
const int LEVEL_2_1_OBJECTS = 0x000027DF;
const int LEVEL_2_1_ENEMIES = 0x00001F61;
const int LEVEL_2_2_OBJECTS = 0x00002E57;
const int LEVEL_2_2_ENEMIES = 0x00002181;
const int LEVEL_2_3_OBJECTS = 0x0000275A;
const int LEVEL_2_3_ENEMIES = 0x00001F4C;
//const int LEVEL_2_4_OBJECTS = 0x000022A1;
//const int LEVEL_2_4_ENEMIES = 0x00001DC0;
const int LEVEL_3_1_OBJECTS = 0x0000262B;
const int LEVEL_3_1_ENEMIES = 0x00001EE0;
const int LEVEL_3_2_OBJECTS = 0x00002C14;
const int LEVEL_3_2_ENEMIES = 0x000020C3;
const int LEVEL_3_3_OBJECTS = 0x0000247D;
const int LEVEL_3_3_ENEMIES = 0x00001E69;
//const int LEVEL_3_4_OBJECTS = 0x00002314;
//const int LEVEL_3_4_ENEMIES = 0x00001DEF;
const int LEVEL_4_1_OBJECTS = 0x00002549;
const int LEVEL_4_1_ENEMIES = 0x00001EAB;
const int LEVEL_4_2_OBJECTS = 0x00002CEA;
const int LEVEL_4_2_ENEMIES = 0x00002115;
const int LEVEL_4_3_OBJECTS = 0x000028A1;
const int LEVEL_4_3_ENEMIES = 0x00001FB9;
//const int LEVEL_4_4_OBJECTS = 0x00002222;
//const int LEVEL_4_4_ENEMIES = 0x00001DA7;
const int LEVEL_5_1_OBJECTS = 0x0000284D;
const int LEVEL_5_1_ENEMIES = 0x00001F8C;
const int LEVEL_5_2_OBJECTS = 0x00002AA4;
const int LEVEL_5_2_ENEMIES = 0x00002045;
const int LEVEL_5_3_OBJECTS = 0x00002705; //duplicate of 1-3
const int LEVEL_5_3_ENEMIES = 0x00001F2F; //duplicate of 1-3
//const int LEVEL_5_4_OBJECTS = 0x000022A1; //duplicate of 2-4
//const int LEVEL_5_4_ENEMIES = 0x00001DC0; //duplicate of 2-4
const int LEVEL_6_1_OBJECTS = 0x0000296D;
const int LEVEL_6_1_ENEMIES = 0x00002001;
const int LEVEL_6_2_OBJECTS = 0x0000259C;
const int LEVEL_6_2_ENEMIES = 0x00001EB9;
const int LEVEL_6_3_OBJECTS = 0x00002908;
const int LEVEL_6_3_ENEMIES = 0x00001FDE;
//const int LEVEL_6_4_OBJECTS = 0x000021C1; //duplicate of 1-4
//const int LEVEL_6_4_ENEMIES = 0x00001D80; //duplicate of 1-4
const int LEVEL_7_1_OBJECTS = 0x00002B90;
const int LEVEL_7_1_ENEMIES = 0x0000209E;
//const int LEVEL_7_2_OBJECTS = 0x00002E57; //duplicate of 2-2
//const int LEVEL_7_2_ENEMIES = 0x00002181; //duplicate of 2-2
const int LEVEL_7_3_OBJECTS = 0x0000275A; //duplicate of 2-3
const int LEVEL_7_3_ENEMIES = 0x00001F4C; //duplicate of 2-3
//const int LEVEL_7_4_OBJECTS = 0x00002381;
//const int LEVEL_7_4_ENEMIES = 0x00001E1A;
const int LEVEL_8_1_OBJECTS = 0x00002A11;
const int LEVEL_8_1_ENEMIES = 0x0000200B;
const int LEVEL_8_2_OBJECTS = 0x00002B17;
const int LEVEL_8_2_ENEMIES = 0x00002070;
const int LEVEL_8_3_OBJECTS = 0x000024E0;
const int LEVEL_8_3_ENEMIES = 0x00001E8E;
//const int LEVEL_8_4_OBJECTS = 0x0000240C;
//const int LEVEL_8_4_ENEMIES = 0x00001E2F;

SMB1LevelGenerator::SMB1LevelGenerator()
{
    srand(time(NULL));
}

bool SMB1LevelGenerator::RandomizeAllLevels(std::fstream &file)
{

    std::vector<int> offsets = { LEVEL_1_1_OBJECTS, LEVEL_1_1_ENEMIES,
                                LEVEL_1_2_OBJECTS, LEVEL_1_2_ENEMIES,
                                LEVEL_1_3_OBJECTS, LEVEL_1_3_ENEMIES,
                                LEVEL_2_1_OBJECTS, LEVEL_2_1_ENEMIES,
                                LEVEL_2_2_OBJECTS, LEVEL_2_2_ENEMIES,
                                LEVEL_2_3_OBJECTS, LEVEL_2_3_ENEMIES,
                                LEVEL_3_1_OBJECTS, LEVEL_3_1_ENEMIES,
                                LEVEL_3_2_OBJECTS, LEVEL_3_2_ENEMIES,
                                LEVEL_3_3_OBJECTS, LEVEL_3_3_ENEMIES,
                                LEVEL_4_1_OBJECTS, LEVEL_4_1_ENEMIES,
                                LEVEL_4_2_OBJECTS, LEVEL_4_2_ENEMIES,
                                LEVEL_4_3_OBJECTS, LEVEL_4_3_ENEMIES,
                                LEVEL_5_1_OBJECTS, LEVEL_5_1_ENEMIES,
                                LEVEL_5_2_OBJECTS, LEVEL_5_2_ENEMIES,
                                LEVEL_6_1_OBJECTS, LEVEL_6_1_ENEMIES,
                                LEVEL_6_2_OBJECTS, LEVEL_6_2_ENEMIES,
                                LEVEL_6_3_OBJECTS, LEVEL_6_3_ENEMIES,
                                LEVEL_7_1_OBJECTS, LEVEL_7_1_ENEMIES,
                                LEVEL_8_1_OBJECTS, LEVEL_8_1_ENEMIES,
                                LEVEL_8_2_OBJECTS, LEVEL_8_2_ENEMIES,
                                LEVEL_8_3_OBJECTS, LEVEL_8_3_ENEMIES };

    for (unsigned int i = 0; i <= offsets.size() - 2; i += 2)
    {
        RandomizeLevel(file, offsets.at(i), offsets.at(i + 1));
    }

    return true;
}

bool SMB1LevelGenerator::RandomizeLevel(std::fstream &file, int objectOffset, int EnemyOffset)
{
    std::vector<unsigned char> header = ReadLevelHeader(file, objectOffset - 2);
    std::vector<unsigned char> objects = ReadLevelObjects(file, objectOffset);
    std::vector<unsigned char> enemies = ReadLevelEnemies(file, EnemyOffset);

    //GenerateBasicLevel(header, objects, enemies);
    GenerateTreeLevel(header, objects, enemies);

    //Write Header
    file.clear();
    file.seekp(objectOffset - 2, std::ios_base::beg);
    for (unsigned int i = 0; i < header.size(); ++i)
    {
        file.put(header.at(i));
    }
    //Write Objects
    file.clear();
    file.seekp(objectOffset, std::ios_base::beg);
    for (unsigned int i = 0; i < objects.size(); ++i)
    {
        file.put(objects.at(i));
    }
    //Write Enemies
    file.clear();
    file.seekp(EnemyOffset, std::ios_base::beg);
    for (unsigned int i = 0; i < enemies.size(); ++i)
    {
        file.put(enemies.at(i));
    }

    return true;
}

void SMB1LevelGenerator::GenerateBasicLevel(std::vector<unsigned char> &header, std::vector<unsigned char> &objects, std::vector<unsigned char> &enemies)
{
    //Set everything possible to generics and blanks for now
    header.at(0) = 0x50;
    header.at(1) = 0x21;
    for (unsigned int i = 0; i < objects.size() - 1; i += 2)
    {
        objects.at(i) = 0x0F;
        objects.at(i + 1) = 0x7F;
    }
    if (enemies.size() % 2 == 1)
    {
        for (unsigned int i = 0; i < enemies.size(); ++i)
        {
            if (i == enemies.size() - 1)
                enemies.at(i) = 0xFF;
            else
                enemies.at(i) = 0x18;
        }
    }
    else
    {
        for (unsigned int i = 0; i < enemies.size(); ++i)
        {
            enemies.at(i) = 0x18;
        }
    }

    //Actual algorithm begins

    int currentX = 0x0;
    //int currentY = 0x0;
    int lastX = 0xF;
    //int lastY = 0x0;

    int maxObjects = objects.size();
    int objectsLeft = (maxObjects - 6) / 2; //the last 6 is to ensure that the level can still be finished

    for (int i = 0; i < maxObjects - 1; i += 2)
    {
        std::vector<bool> positionBits = { false, false, false, false, false, false, false, false };
        std::vector<bool> objectBits = { false, false, false, false, false, false, false, false };

        //Handle the end of the level
        if (i == maxObjects - 4)
        {
            //Determine x position
            if (lastX > 0xF)
            {
                objectBits.at(0) = true; //set the page flag to make a new page
                lastX -= 0x10;
                currentX = lastX + 7;
            }
            else
            {
                currentX = lastX + 7;
                if (currentX > 0xF)
                {
                    objectBits.at(0) = true; //set the page flag to make a new page
                    currentX -= 0x10; //reset x offset on new page
                }
            }

            BinaryManipulator::WriteHexDigitToBitVector(positionBits, 0, currentX); //x
            BinaryManipulator::WriteHexDigitToBitVector(positionBits, 4, 0xD); //y
            BinaryManipulator::WriteHexDigitToBitVector(objectBits, 1, 0x4, 1, 3); //Flagpole
            BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x1); //Flagpole

            lastX = currentX;
            objects.at(i) = (short)BinaryManipulator::BitVectorToHex(positionBits);
            objects.at(i + 1) = (short)BinaryManipulator::BitVectorToHex(objectBits);
            continue;
        }
        else if (i == maxObjects - 2)
        {
            //Determine x position
            if (lastX > 0xF)
            {
                objectBits.at(0) = true; //set the page flag to make a new page
                lastX -= 0x10;
                currentX = lastX + 4;
            }
            else
            {
                currentX = lastX + 4;
                if (currentX > 0xF)
                {
                    objectBits.at(0) = true; //set the page flag to make a new page
                    currentX -= 0x10; //reset x offset on new page
                }
            }

            BinaryManipulator::WriteHexDigitToBitVector(positionBits, 0, currentX); //x
            BinaryManipulator::WriteHexDigitToBitVector(positionBits, 4, 0xF); //y
            BinaryManipulator::WriteHexDigitToBitVector(objectBits, 1, 0x2, 1, 3); //Castle
            BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x6); //Castle

            lastX = currentX;
            objects.at(i) = (short)BinaryManipulator::BitVectorToHex(positionBits);
            objects.at(i + 1) = (short)BinaryManipulator::BitVectorToHex(objectBits);
            continue;
        }

        int chance = 0;

        //Determine x position
        if (lastX > 0xF)
        {
            objectBits.at(0) = true; //set the page flag to make a new page
            lastX -= 0x10;

            if (lastX < 0x5)
            {
                currentX = LowballRandomValue(0x1, 0xB) + lastX;
            }
            else
            {
                currentX = LowballRandomValue((lastX + 1), 0xF);
            }
        }
        else
        {
            currentX = LowballRandomValue(0x1, 0xB) + lastX;

            if (currentX > 0xF)
            {
                objectBits.at(0) = true; //set the page flag to make a new page
                currentX -= 0x10; //reset x offset on new page
            }
        }

        //Set the x position
        BinaryManipulator::WriteHexDigitToBitVector(positionBits, 0, currentX);

        //Put Stairs at the end of the level
        if (i == maxObjects - 6)
        {
            if (currentX == 0x0)
            {
                currentX++; //Prevent a bug in the SMB1 engine with the flagpole being placed at the edge of the page
            }
            BinaryManipulator::WriteHexDigitToBitVector(positionBits, 4, 0xF); //y
            BinaryManipulator::WriteHexDigitToBitVector(objectBits, 1, 0xB, 1, 3); //Stairs
            BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x8); //Stairs

            lastX = currentX + 8;
            objects.at(i) = (short)BinaryManipulator::BitVectorToHex(positionBits);
            objects.at(i + 1) = (short)BinaryManipulator::BitVectorToHex(objectBits);
            continue;
        }

        //Determine object to place
        chance = (rand() % 60) + 1;

        if (chance <= 10)
        { //Make a pipe
            BinaryManipulator::WriteHexDigitToBitVector(objectBits, 1, 0x7, 1, 3);

            //Determine height
            chance = (rand() % 30) + 1;
            if (chance <= 10)
            { //Pipe length 2
                BinaryManipulator::WriteHexDigitToBitVector(positionBits, 4, 0x9);
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x1);
            }
            else if (chance <= 20)
            { //Pipe length 3
                BinaryManipulator::WriteHexDigitToBitVector(positionBits, 4, 0x8);
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x2);
            }
            else if (chance <= 30)
            { //Pipe length 4
                BinaryManipulator::WriteHexDigitToBitVector(positionBits, 4, 0x7);
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x3);
            }
            lastX = currentX + 1; //pipes take up two spaces
        }
        else if (chance <= 20)
        { //Make a block that contains something
            BinaryManipulator::WriteHexDigitToBitVector(objectBits, 1, 0x0, 1, 3);

            //Determine block's height
            BinaryManipulator::WriteHexDigitToBitVector(positionBits, 4, 0x7);

            chance = (rand() % 250) + 1;
            if (chance <= 20)
            { //? with Mushroom
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x0);
            }
            else if (chance <= 27)
            { //Brick with Mushroom
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x4);
            }
            else if (chance <= 30)
            { //Brick with star
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x6);
            }
            else if (chance <= 48)
            { //10 coin block
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x7);
            }
            else if (chance <= 50)
            { //Brick with 1-up
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x8);
            }
            else if (chance <= 53)
            { //Invisible block with coin
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x2);
                //mix up the height a bit
                chance = (rand() % 4) + 5; //random number between 5 and 8
                BinaryManipulator::WriteHexDigitToBitVector(positionBits, 4, chance);
            }
            else if (chance <= 54)
            { //Invisible block with 1-up
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x3);
                //mix up the height a bit
                chance = (rand() % 4) + 5; //random number between 5 and 8
                BinaryManipulator::WriteHexDigitToBitVector(positionBits, 4, chance);
            }
            else if (chance <= 200)
            { //? with Coin
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x1);
            }
            else if (chance <= 250)
            { //Brick block
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 1, 0x2, 1, 3);
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x0);
            }
            lastX = currentX;
        }
        else if (chance <= 30)
        { //Make a hole in the ground
            //Holes are always located at 0xC height
            BinaryManipulator::WriteHexDigitToBitVector(positionBits, 4, 0xC);
            BinaryManipulator::WriteHexDigitToBitVector(objectBits, 1, 0x0, 1, 3);

            chance = (rand() % 70) + 1;
            if (chance <= 10)
            { //Hole with length 1
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x0);
                lastX = currentX + 1; //keep the safe zone here for now
            }
            else if (chance <= 20)
            { //Hole with length 2
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x1);
                lastX = currentX + 2; //keep the safe zone here for now
            }
            else if (chance <= 30)
            { //Hole with length 3
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x2);
                lastX = currentX + 3; //keep the safe zone here for now
            }
            else if (chance <= 40)
            { //Hole with length 4
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x3);
                lastX = currentX + 4; //keep the safe zone here for now
            }
            else if (chance <= 50)
            { //Hole with length 5
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x4);
                lastX = currentX + 5; //all holes > 4 in length should have at least one space of "safe zone"
            }
            else if (chance <= 60)
            { //Hole with length 6
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x5);
                lastX = currentX + 6; //all holes > 4 in length should have at least one space of "safe zone"
            }
            else if (chance <= 70)
            { //Hole with length 7
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x6);
                lastX = currentX + 7; //all holes > 4 in length should have at least one space of "safe zone"s
            }
        }
        else if (chance <= 33)
        { //Hoizontal ? Blocks
            //Horizontal Blocks are always located at 0xC
            BinaryManipulator::WriteHexDigitToBitVector(positionBits, 4, 0xC);
            BinaryManipulator::WriteHexDigitToBitVector(objectBits, 1, 0x7, 1, 3);

            chance = (rand() % 70) + 1;
            if (chance <= 10)
            { //Hoizontal ? Blocks with length 2
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x1);
                lastX = currentX + 1;
            }
            else if (chance <= 20)
            { //Hoizontal ? Blocks with length 3
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x2);
                lastX = currentX + 2;
            }
            else if (chance <= 30)
            { //Hoizontal ? Blocks with length 4
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x3);
                lastX = currentX + 3;
            }
            else if (chance <= 40)
            { //Hoizontal ? Blocks with length 5
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x4);
                lastX = currentX + 4;
            }
            else if (chance <= 50)
            { //Hoizontal ? Blocks with length 6
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x5);
                lastX = currentX + 5;
            }
            else if (chance <= 60)
            { //Hoizontal ? Blocks with length 7
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x6);
                lastX = currentX + 6;
            }
            else if (chance <= 70)
            { //Hoizontal ? Blocks with length 7
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x6);
                lastX = currentX + 7;
            }
            //Set the bytes before adding items inside the block row
            objectsLeft--;
            objects.at(i) = (short)BinaryManipulator::BitVectorToHex(positionBits);
            objects.at(i + 1) = (short)BinaryManipulator::BitVectorToHex(objectBits);
            i += AddItemsToBlockRow(maxObjects, objectsLeft, objects, i);
            continue;
        }
        else if (chance <= 40)
        { //Hoizontal Brick Blocks
            BinaryManipulator::WriteHexDigitToBitVector(objectBits, 1, 0x2, 1, 3);

            //Determine block's height
            BinaryManipulator::WriteHexDigitToBitVector(positionBits, 4, 0x7);

            chance = (rand() % 70) + 1;
            if (chance <= 10)
            { //Hoizontal Brick Blocks with length 2
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x1);
                lastX = currentX + 1;
            }
            else if (chance <= 20)
            { //Hoizontal Brick Blocks with length 3
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x2);
                lastX = currentX + 2;
            }
            else if (chance <= 30)
            { //Hoizontal Brick Blocks with length 4
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x3);
                lastX = currentX + 3;
            }
            else if (chance <= 40)
            { //Hoizontal Brick Blocks with length 5
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x4);
                lastX = currentX + 4;
            }
            else if (chance <= 50)
            { //Hoizontal Brick Blocks with length 6
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x5);
                lastX = currentX + 5;
            }
            else if (chance <= 60)
            { //Hoizontal Brick Blocks with length 7
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x6);
                lastX = currentX + 6;
            }
            else if (chance <= 70)
            { //Hoizontal Brick Blocks with length 7
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x6);
                lastX = currentX + 7;
            }
            //Set the bytes before adding items inside the block row
            objectsLeft--;
            objects.at(i) = (short)BinaryManipulator::BitVectorToHex(positionBits);
            objects.at(i + 1) = (short)BinaryManipulator::BitVectorToHex(objectBits);
            i += AddItemsToBlockRow(maxObjects, objectsLeft, objects, i);
            continue;
        }
        else if (chance <= 50)
        { //Stairs
            BinaryManipulator::WriteHexDigitToBitVector(positionBits, 4, 0xF);
            BinaryManipulator::WriteHexDigitToBitVector(objectBits, 1, 0x3, 1, 3);

            chance = (rand() % 50) + 1;
            if (chance <= 10)
            { //Stairs with height 2
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x1);
                lastX = currentX + 1;
            }
            else if (chance <= 20)
            { //Stairs with height 3
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x2);
                lastX = currentX + 2;
            }
            else if (chance <= 30)
            { //Stairs with height 4
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x3);
                lastX = currentX + 3;
            }
            else if (chance <= 40)
            { //Stairs with height 5
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x4);
                lastX = currentX + 4;
            }
            else if (chance <= 50)
            { //Stairs with height 6
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x5);
                lastX = currentX + 5;
            }
            objectsLeft--;
            objects.at(i) = (short)BinaryManipulator::BitVectorToHex(positionBits);
            objects.at(i + 1) = (short)BinaryManipulator::BitVectorToHex(objectBits);

            bool extraBlock = false;
            int size = BinaryManipulator::BitVectorToHex(BinaryManipulator::HexToBitVector(objects.at(i + 1)), 4, 7) + 1;
            chance = (rand() % 20) + 1;
            if (chance <= 10 && objectsLeft > 0)
            { //Add an extra row of blocks at the top of the stairs
                extraBlock = true;
                //Reset the bit arrays
                for (unsigned int j = 0; j < positionBits.size(); j++)
                {
                    positionBits.at(j) = false;
                }
                for (unsigned int j = 0; j < objectBits.size(); j++)
                {
                    objectBits.at(j) = false;
                }

                //Determine the coordinates
                currentX = lastX + 1;
                if (currentX > 0xF)
                {
                    currentX -= 0x10;
                    objectBits.at(0) = true;
                }
                int y = 0xB - size;
                i += 2;

                //Set the bits
                BinaryManipulator::WriteHexDigitToBitVector(positionBits, 0, currentX);
                BinaryManipulator::WriteHexDigitToBitVector(positionBits, 4, y);
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 1, 0x6, 1, 3);
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, (size - 1));

                lastX = currentX;
                objectsLeft--;

                //Write the object
                objects.at(i) = (short)BinaryManipulator::BitVectorToHex(positionBits);
                objects.at(i + 1) = (short)BinaryManipulator::BitVectorToHex(objectBits);
            }

            int holeSize = 0;
            chance = (rand() % 20) + 1;
            if (chance <= 10 && objectsLeft > 0)
            { //Spawn a hole after the stairs
                //Reset the bit arrays
                for (unsigned int j = 0; j < positionBits.size(); ++j)
                {
                    positionBits.at(j) = false;
                }
                for (unsigned int j = 0; j < objectBits.size(); ++j)
                {
                    objectBits.at(j) = false;
                }

                currentX = lastX + 1;
                if (currentX > 0xF)
                {
                    currentX -= 0x10;
                    objectBits.at(0) = true;
                }

                holeSize = 0;
                if (extraBlock)
                {
                    holeSize = (rand() % ((size * 2) - 1)) + 2;
                }
                else
                {
                    holeSize = (rand() % size) + 1;
                }
                i += 2;

                //Set the bits
                BinaryManipulator::WriteHexDigitToBitVector(positionBits, 0, currentX);
                BinaryManipulator::WriteHexDigitToBitVector(positionBits, 4, 0xC);
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 1, 0x0, 1, 3);
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, holeSize);

                lastX = currentX + holeSize + 1; //add one block of "safe zone"
                objectsLeft--;

                //Write the object
                objects.at(i) = (short)BinaryManipulator::BitVectorToHex(positionBits);
                objects.at(i + 1) = (short)BinaryManipulator::BitVectorToHex(objectBits);
            }

            chance = (rand() % 20) + 1;
            if (chance <= 15 && objectsLeft > 0 &&
                ((extraBlock && holeSize > 0 && holeSize < 7) ||
                (holeSize > 0 && holeSize < 4) ||
                (holeSize == 0 && size < 5)))
            { //Add a landing platform
                if (holeSize > 0)
                {
                    lastX--; //remove the safe zone
                }
                else
                {
                    lastX += (rand() % 3) + 2; //there is no hole, so pretend like there is one
                }

                chance = (rand() % 20) + 1;
                if (chance <= 10 && objectsLeft >= 2)
                { //Landing platform is 2 blocks thick
                    if (size == 1)
                    { //Make a horizontal landing platform to save objects
                        //Reset the bit arrays
                        for (unsigned int k = 0; k < positionBits.size(); ++k)
                        {
                            positionBits.at(k) = false;
                        }
                        for (unsigned int k = 0; k < objectBits.size(); ++k)
                        {
                            objectBits.at(k) = false;
                        }

                        currentX = lastX + 1;
                        if (currentX > 0xF)
                        {
                            currentX -= 0x10;
                            objectBits.at(0) = true;
                        }
                        int y = 0xB - size;
                        i += 2;

                        //Set the bits
                        BinaryManipulator::WriteHexDigitToBitVector(positionBits, 0, currentX);
                        BinaryManipulator::WriteHexDigitToBitVector(positionBits, 4, y);
                        BinaryManipulator::WriteHexDigitToBitVector(objectBits, 1, 0x3, 1, 3);
                        BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x1);

                        lastX = currentX;
                        objectsLeft--;

                        //Write the object
                        objects.at(i) = (short)BinaryManipulator::BitVectorToHex(positionBits);
                        objects.at(i + 1) = (short)BinaryManipulator::BitVectorToHex(objectBits);

                        continue; //no need to create any more objects
                    }
                    for (int j = 0; j < 2; ++j)
                    {
                        //Reset the bit arrays
                        for (unsigned int k = 0; k < positionBits.size(); ++k)
                        {
                            positionBits.at(k) = false;
                        }
                        for (unsigned int k = 0; k < objectBits.size(); ++k)
                        {
                            objectBits.at(k) = false;
                        }

                        currentX = lastX + 1;
                        if (currentX > 0xF)
                        {
                            currentX -= 0x10;
                            objectBits.at(0) = true;
                        }
                        int y = 0xB - size;
                        i += 2;

                        //Set the bits
                        BinaryManipulator::WriteHexDigitToBitVector(positionBits, 0, currentX);
                        BinaryManipulator::WriteHexDigitToBitVector(positionBits, 4, y);
                        BinaryManipulator::WriteHexDigitToBitVector(objectBits, 1, 0x6, 1, 3);
                        BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, (size - 1));

                        lastX = currentX;
                        objectsLeft--;

                        //Write the object
                        objects.at(i) = (short)BinaryManipulator::BitVectorToHex(positionBits);
                        objects.at(i + 1) = (short)BinaryManipulator::BitVectorToHex(objectBits);
                    }
                }
                else if (chance <= 20 && objectsLeft >= size)
                { //Landing platform stairs
                    size = (rand() % (size + 1)) + 1;
                    int currentSize = size;

                    chance = (rand() % 20) + 1;
                    if (chance <= 10 && objectsLeft >= (size + 1))
                    { //Add an extra row of blocks at the top of the stairs
                        extraBlock = true;
                        //Reset the bit arrays
                        for (unsigned int j = 0; j < positionBits.size(); ++j)
                        {
                            positionBits.at(j) = false;
                        }
                        for (unsigned int j = 0; j < objectBits.size(); ++j)
                        {
                            objectBits.at(j) = false;
                        }

                        //Determine the coordinates
                        currentX = lastX + 1;
                        if (currentX > 0xF)
                        {
                            currentX -= 0x10;
                            objectBits.at(0) = true;
                        }
                        int y = 0xB - size;
                        i += 2;

                        //Set the bits
                        BinaryManipulator::WriteHexDigitToBitVector(positionBits, 0, currentX);
                        BinaryManipulator::WriteHexDigitToBitVector(positionBits, 4, y);
                        if (size == 1)
                        { //Make a horizontal landing pad to save objects
                            BinaryManipulator::WriteHexDigitToBitVector(objectBits, 1, 0x3, 1, 3);
                            BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x1);
                        }
                        else
                        {
                            BinaryManipulator::WriteHexDigitToBitVector(objectBits, 1, 0x6, 1, 3);
                            BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, (size - 1));
                        }

                        lastX = currentX;
                        objectsLeft--;

                        //Write the object
                        objects.at(i) = (short)BinaryManipulator::BitVectorToHex(positionBits);
                        objects.at(i + 1) = (short)BinaryManipulator::BitVectorToHex(objectBits);

                        if (size == 1)
                        { //No need to spawn anything else
                            continue;
                        }
                    }

                    for (int j = 0; j < size; ++j)
                    { //Spawn the stairs
                        //Reset the bit arrays
                        for (unsigned int k = 0; k < positionBits.size(); ++k)
                        {
                            positionBits.at(k) = false;
                        }
                        for (unsigned int k = 0; k < objectBits.size(); ++k)
                        {
                            objectBits.at(k) = false;
                        }

                        currentX = lastX + 1;
                        if (currentX > 0xF)
                        {
                            currentX -= 0x10;
                            objectBits.at(0) = true;
                        }
                        int y = 0xB - currentSize;
                        i += 2;

                        //Set the bits
                        BinaryManipulator::WriteHexDigitToBitVector(positionBits, 0, currentX);
                        BinaryManipulator::WriteHexDigitToBitVector(positionBits, 4, y);
                        BinaryManipulator::WriteHexDigitToBitVector(objectBits, 1, 0x6, 1, 3);
                        BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, (currentSize - 1));

                        lastX = currentX;
                        currentSize--;
                        objectsLeft--;

                        //Write the object
                        objects.at(i) = (short)BinaryManipulator::BitVectorToHex(positionBits);
                        objects.at(i + 1) = (short)BinaryManipulator::BitVectorToHex(objectBits);
                    }
                }
            }
            continue;
        }
        else if (chance <= 60)
        { //Vertical Blocks
            int size = (rand() % 4) + 1;
            int y = 0xB - size;
            BinaryManipulator::WriteHexDigitToBitVector(positionBits, 4, y);
            BinaryManipulator::WriteHexDigitToBitVector(objectBits, 1, 0x6, 1, 3);
            BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, (size - 1));

            lastX = currentX;
            objectsLeft--;

            //Write the bytes
            objects.at(i) = (short)BinaryManipulator::BitVectorToHex(positionBits);
            objects.at(i + 1) = (short)BinaryManipulator::BitVectorToHex(objectBits);

            for (int j = 0; j < 6 && objectsLeft > 0; j++)
            { //Chain up to six more
                if (objectsLeft <= 0)
                { //Nothing else can be generated
                    break;
                }
                chance = (rand() % 20) + 1;
                if (chance <= 12)
                {
                    int previousSize = size;
                    chance = (rand() % 20) + 1;
                    if (chance <= 10)
                    { //change the size
                        int minSize = size - 4;
                        if (minSize < 0)
                        {
                            minSize = 0;
                        }
                        size = (rand() % (size + 4 - minSize)) + (minSize + 1);
                        if (size > 9)
                        {
                            size = 9;
                        }
                        y = 0xB - size;
                    }
                    if (previousSize == size && size == 1)
                    {
                        int length = BinaryManipulator::BitVectorToHex(objectBits, 4, 7) + 1; //add one to the previous length
                        BinaryManipulator::WriteHexDigitToBitVector(objectBits, 1, 0x3, 1, 3);
                        BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, length);

                        lastX++;

                        //Rewrite the bytes without decrementing objectsLeft
                        objects.at(i) = (short)BinaryManipulator::BitVectorToHex(positionBits);
                        objects.at(i + 1) = (short)BinaryManipulator::BitVectorToHex(objectBits);
                        continue;
                    }
                    //Reset the bit arrays
                    for (unsigned int k = 0; k < positionBits.size(); ++k)
                    {
                        positionBits.at(k) = false;
                    }
                    for (unsigned int k = 0; k < objectBits.size(); ++k)
                    {
                        objectBits.at(k) = false;
                    }

                    currentX = lastX + 1;
                    if (currentX > 0xF)
                    {
                        currentX -= 0x10;
                        objectBits.at(0) = true;
                    }
                    i += 2;

                    BinaryManipulator::WriteHexDigitToBitVector(positionBits, 0, currentX);
                    BinaryManipulator::WriteHexDigitToBitVector(positionBits, 4, y);
                    BinaryManipulator::WriteHexDigitToBitVector(objectBits, 1, 0x6, 1, 3);
                    BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, (size - 1));

                    lastX = currentX;
                    objectsLeft--;

                    //Write the bytes
                    objects.at(i) = (short)BinaryManipulator::BitVectorToHex(positionBits);
                    objects.at(i + 1) = (short)BinaryManipulator::BitVectorToHex(objectBits);
                }
                else
                { //don't try to generate more
                    break;
                }
            }
            continue;
        }

        objectsLeft--;
        //Now set the bytes and move on
        objects.at(i) = (short)BinaryManipulator::BitVectorToHex(positionBits);
        objects.at(i + 1) = (short)BinaryManipulator::BitVectorToHex(objectBits);
    }
}

void SMB1LevelGenerator::GenerateTreeLevel(std::vector<unsigned char> &header, std::vector<unsigned char> &objects, std::vector<unsigned char> &enemies)
{
    //Set everything possible to generics and blanks for now
    header.at(0) = 0x90;
    header.at(1) = 0x11;
    for (unsigned int i = 0; i < objects.size() - 1; i += 2)
    {
        objects.at(i) = 0x0F;
        objects.at(i + 1) = 0x7F;
    }
    if (enemies.size() % 2 == 1)
    {
        for (unsigned int i = 0; i < enemies.size(); ++i)
        {
            if (i == enemies.size() - 1)
                enemies.at(i) = 0xFF;
            else
                enemies.at(i) = 0x18;
        }
    }
    else
    {
        for (unsigned int i = 0; i < enemies.size(); ++i)
        {
            enemies.at(i) = 0x18;
        }
    }


    int currentX = 0x0;
    int currentY = 0xB;
    int lastX = 0xF;
    int lastY = 0xA;

    int maxObjects = objects.size();
    int objectsLeft = (maxObjects - 8) / 2; //the last 8 is to ensure that the level can still be finished

    //Handle the beginning of the level
    objects.at(0) = 0x0F;
    objects.at(1) = 0x26;
    objects.at(2) = 0xFE;
    objects.at(3) = 0x10;

    for (int i = 4; i < maxObjects - 1; i += 2)
    {
        std::vector<bool> positionBits = { false, false, false, false, false, false, false, false };
        std::vector<bool> objectBits = { false, false, false, false, false, false, false, false };

        //Handle the end of the level
        if (i == maxObjects - 4)
        {
            //Determine x position
            if (lastX > 0xF)
            {
                objectBits.at(0) = true; //set the page flag to make a new page
                lastX -= 0x10;
                currentX = lastX + 7;
            }
            else
            {
                currentX = lastX + 7;
                if (currentX > 0xF)
                {
                    objectBits.at(0) = true; //set the page flag to make a new page
                    currentX -= 0x10; //reset x offset on new page
                }
            }

            BinaryManipulator::WriteHexDigitToBitVector(positionBits, 0, currentX); //x
            BinaryManipulator::WriteHexDigitToBitVector(positionBits, 4, 0xD); //y
            BinaryManipulator::WriteHexDigitToBitVector(objectBits, 1, 0x4, 1, 3); //Flagpole
            BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x1); //Flagpole

            lastX = currentX;
            objects.at(i) = (short)BinaryManipulator::BitVectorToHex(positionBits);
            objects.at(i + 1) = (short)BinaryManipulator::BitVectorToHex(objectBits);
            continue;
        }
        else if (i == maxObjects - 2)
        {
            //Determine x position
            if (lastX > 0xF)
            {
                objectBits.at(0) = true; //set the page flag to make a new page
                lastX -= 0x10;
                currentX = lastX + 4;
            }
            else
            {
                currentX = lastX + 4;
                if (currentX > 0xF)
                {
                    objectBits.at(0) = true; //set the page flag to make a new page
                    currentX -= 0x10; //reset x offset on new page
                }
            }

            BinaryManipulator::WriteHexDigitToBitVector(positionBits, 0, currentX); //x
            BinaryManipulator::WriteHexDigitToBitVector(positionBits, 4, 0xF); //y
            BinaryManipulator::WriteHexDigitToBitVector(objectBits, 1, 0x2, 1, 3); //Castle
            BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x6); //Castle

            lastX = currentX;
            objects.at(i) = (short)BinaryManipulator::BitVectorToHex(positionBits);
            objects.at(i + 1) = (short)BinaryManipulator::BitVectorToHex(objectBits);
            continue;
        }

        int chance = 0;

        //Determine x position
        /*
        if (lastX > 0xF)
        {
            objectBits.at(0) = true; //set the page flag to make a new page
            lastX -= 0x10;

            if (lastX < 0x5)
            {
                currentX = LowballRandomValue(0x1, 0xB) + lastX;
            }
            else
            {
                currentX = LowballRandomValue((lastX + 1), 0xF);
            }
        }
        else
        {
            currentX = LowballRandomValue(0x1, 0xB) + lastX;

            if (currentX > 0xF)
            {
                objectBits.at(0) = true; //set the page flag to make a new page
                currentX -= 0x10; //reset x offset on new page
            }
        }
        */
        //DEBUG CODE!!!
        objectBits.at(0) = true;
        currentX = 0x0;

        //Set the x position
        BinaryManipulator::WriteHexDigitToBitVector(positionBits, 0, currentX);

        //Generate Ground at the end of the level
        if (i == maxObjects - 8)
        {
            BinaryManipulator::WriteHexDigitToBitVector(positionBits, 4, 0xE); //y
            BinaryManipulator::WriteHexDigitToBitVector(objectBits, 1, 0x1, 1, 3); //Ground
            BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x1); //Ground

            lastX = currentX + 3; //have at least 3 blocks of safe zone
            objects.at(i) = (short)BinaryManipulator::BitVectorToHex(positionBits);
            objects.at(i + 1) = (short)BinaryManipulator::BitVectorToHex(objectBits);
            continue;
        }
        else if (i == maxObjects - 6) //Stairs at the end of the level
        {
            if (currentX == 0x0)
            {
                currentX++; //Prevent a bug in the SMB1 engine with the flagpole being placed at the edge of the page
            }
            BinaryManipulator::WriteHexDigitToBitVector(positionBits, 4, 0xF); //y
            BinaryManipulator::WriteHexDigitToBitVector(objectBits, 1, 0xB, 1, 3); //Stairs
            BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x8); //Stairs

            lastX = currentX + 8;
            objects.at(i) = (short)BinaryManipulator::BitVectorToHex(positionBits);
            objects.at(i + 1) = (short)BinaryManipulator::BitVectorToHex(objectBits);
            continue;
        }

        //Determine object to place
        chance = (rand() % 60) + 1;
        if (chance <= 60)
        {
            //Tree



            //TEST CODE FOR NOW!!!!
            BinaryManipulator::WriteHexDigitToBitVector(objectBits, 1, 0x1, 1, 3);
            BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0xA);

            currentY--;
            if (currentY == 0) currentY = 0xB;
            //Determine height
            /*
            chance = (rand() % 30) + 1;
            if (chance <= 10)
            {
                BinaryManipulator::WriteHexDigitToBitVector(positionBits, 4, 0x9);
            }
            else if (chance <= 20)
            {
                BinaryManipulator::WriteHexDigitToBitVector(positionBits, 4, 0x8);
            }
            else if (chance <= 30)
            {
                BinaryManipulator::WriteHexDigitToBitVector(positionBits, 4, 0x7);
            }
            */



            BinaryManipulator::WriteHexDigitToBitVector(positionBits, 4, currentY); //y

            lastX = currentX + 0xA; //DEBUG CODE!!!
        }

        objectsLeft--;
        //Now set the bytes and move on
        objects.at(i) = (short)BinaryManipulator::BitVectorToHex(positionBits);
        objects.at(i + 1) = (short)BinaryManipulator::BitVectorToHex(objectBits);
    }
}

int SMB1LevelGenerator::AddItemsToBlockRow(int maxObjects, int &objectsLeft, std::vector<unsigned char> &objects, int blockRow)
{
    bool isBrick = false;
    //The y coordinate will need to be improved upon later for higher block rows
    int y = 0x7; //default y for blocks
    if (BinaryManipulator::BitVectorToHex(BinaryManipulator::HexToBitVector(objects.at(blockRow + 1)), 1, 3) == 0x2)
    {
        isBrick = true;
    }
    int blocks = BinaryManipulator::BitVectorToHex(BinaryManipulator::HexToBitVector(objects.at(blockRow + 1)), 4, 7) + 1;

    int startX = BinaryManipulator::BitVectorToHex(BinaryManipulator::HexToBitVector(objects.at(blockRow)), 0, 3);
    if (isBrick)
    {
        y = BinaryManipulator::BitVectorToHex(BinaryManipulator::HexToBitVector(objects.at(blockRow)), 4, 7);
    }

    int usedObjects = 0;
    bool usedPageFlag = false;
    for (int i = 0; i < blocks && objectsLeft > 0; i++)
    {
        int chance = (rand() % 100) + 1;
        if ((chance <= 12) || (chance <= 20 && isBrick))
        {
            std::vector<bool> positionBits = { false, false, false, false, false, false, false, false };
            std::vector<bool> objectBits = { false, false, false, false, false, false, false, false };

            int x = (startX + i); //determine where to spawn the block
            if (x > 0xF && !usedPageFlag)
            {
                x -= 0x10;
                objectBits.at(0) = true; //move to the next page
                usedPageFlag = true;
            }
            else if (x > 0xF && usedPageFlag)
            {
                x -= 0x10;
            }
            BinaryManipulator::WriteHexDigitToBitVector(positionBits, 0, x); //x coordinate
            BinaryManipulator::WriteHexDigitToBitVector(positionBits, 4, y); //y coordinate
            BinaryManipulator::WriteHexDigitToBitVector(objectBits, 1, 0x0, 1, 3); //block

            if (isBrick)
            {
                chance = (rand() % 100) + 1;
                if (chance <= 20)
                { //? with Mushroom
                    BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x0);
                }
                else if (chance <= 27)
                { //Brick with Mushroom
                    BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x4);
                }
                else if (chance <= 30)
                { //Brick with star
                    BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x6);
                }
                else if (chance <= 48)
                { //10 coin block
                    BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x7);
                }
                else if (chance <= 50)
                { //Brick with 1-up
                    BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x8);
                }
                else if (chance <= 100)
                { //? with Coin
                    BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x1);
                }
            }
            else
            { //only make the block a ? with a mushroom
                BinaryManipulator::WriteHexDigitToBitVector(objectBits, 4, 0x0);
            }

            usedObjects++;
            objectsLeft--;

            //Write the blocks to the byte array
            objects[blockRow + (usedObjects * 2)] = (short)BinaryManipulator::BitVectorToHex(positionBits);
            objects[blockRow + 1 + (usedObjects * 2)] = (short)BinaryManipulator::BitVectorToHex(objectBits);
        }
    }
    return (usedObjects * 2);
}

bool SMB1LevelGenerator::isROMValid(std::fstream &file)
{
    //Compare the header with the NES header
    file.clear();
    file.seekg(0, std::ios_base::beg);
    std::vector<unsigned char> bytes;
    for (int i = 0; i < 16; ++i)
    {
        bytes.push_back((unsigned char)file.get());
    }
    bool isNESROM = true;
    for (int i = 0; i < 4; ++i)
    {
        if (bytes.at(i) != NESHeader.at(i))
        {
            isNESROM = false;
            break;
        }
    }
    return isNESROM;
}

bool SMB1LevelGenerator::isBannedObject(std::vector<unsigned char> &hex)
{
    if (hex.size() != 2)
        return true;
    int y = BinaryManipulator::BinaryStringToHex(BinaryManipulator::HexToBinaryString(hex.at(0)).substr(4));

    switch (y)
    { //The object set changes depending upon the y coordinate
        case 0X0C:
        switch (hex.at(1))
            {
                case 0x10: //Balance's horizontal rope
                case 0x11: //Balance's horizontal rope
                case 0x12: //Balance's horizontal rope
                case 0x13: //Balance's horizontal rope
                case 0x14: //Balance's horizontal rope
                case 0x15: //Balance's horizontal rope
                case 0x16: //Balance's horizontal rope
                case 0x17: //Balance's horizontal rope
                case 0x18: //Balance's horizontal rope
                case 0x19: //Balance's horizontal rope
                case 0x1A: //Balance's horizontal rope
                case 0x1B: //Balance's horizontal rope
                case 0x1C: //Balance's horizontal rope
                case 0x1D: //Balance's horizontal rope
                case 0x1E: //Balance's horizontal rope
                case 0x1F: //Balance's horizontal rope
                    return true;
            }
            break;
        case 0X0D:
        switch (hex.at(1))
            {
                case 0x41: //Flagpole
                case 0x42: //Axe
                case 0x4C: //Unknown
                case 0x4D: //Freeze
                case 0x4E: //Freeze
                case 0x4F: //Freeze
                case 0xC1: //Flagpole
                case 0xC2: //Axe
                case 0xCC: //Unknown
                case 0xCD: //Freeze
                case 0xCE: //Freeze
                case 0xCF: //Freeze
                    return true;
            }
            break;
        case 0x0E:
        switch (hex.at(1))
            {
                case 0x41: //Change background
                case 0x42: //Change background
                case 0x43: //Change background
                case 0x44: //Change background
                case 0x45: //Change background
                case 0x46: //Change background
                case 0x47: //Change background
                case 0xC1: //Change background
                case 0xC2: //Change background
                case 0xC3: //Change background
                case 0xC4: //Change background
                case 0xC5: //Change background
                case 0xC6: //Change background
                case 0xC7: //Change background
                    return true;
            }
            break;
        case 0x0F:
        switch (hex.at(1))
            {
                case 0x00: //Lift's vertical rope
                case 0x01: //Lift's vertical rope
                case 0x02: //Lift's vertical rope
                case 0x03: //Lift's vertical rope
                case 0x04: //Lift's vertical rope
                case 0x05: //Lift's vertical rope
                case 0x06: //Lift's vertical rope
                case 0x07: //Lift's vertical rope
                case 0x08: //Lift's vertical rope
                case 0x09: //Lift's vertical rope
                case 0x0A: //Lift's vertical rope
                case 0x0B: //Lift's vertical rope
                case 0x0C: //Lift's vertical rope
                case 0x0D: //Lift's vertical rope
                case 0x0E: //Lift's vertical rope
                case 0x0F: //Lift's vertical rope
                case 0x10: //Vertical rope to balance lift
                case 0x11: //Vertical rope to balance lift
                case 0x12: //Vertical rope to balance lift
                case 0x13: //Vertical rope to balance lift
                case 0x14: //Vertical rope to balance lift
                case 0x15: //Vertical rope to balance lift
                case 0x16: //Vertical rope to balance lift
                case 0x17: //Vertical rope to balance lift
                case 0x18: //Vertical rope to balance lift
                case 0x19: //Vertical rope to balance lift
                case 0x1A: //Vertical rope to balance lift
                case 0x1B: //Vertical rope to balance lift
                case 0x1C: //Vertical rope to balance lift
                case 0x1D: //Vertical rope to balance lift
                case 0x1E: //Vertical rope to balance lift
                case 0x1F: //Vertical rope to balance lift
                case 0x20: //Castle
                case 0x21: //Castle
                case 0x22: //Castle
                case 0x23: //Castle
                case 0x24: //Castle
                case 0x25: //Castle
                case 0x26: //Castle
                case 0x27: //Castle
                case 0x28: //Castle
                case 0x29: //Castle
                case 0x2A: //Castle
                case 0x2B: //Castle
                case 0x2C: //Castle
                case 0x2D: //Castle
                case 0x2E: //Castle
                case 0x2F: //Castle
                case 0x40: //Long reverse L pipe
                case 0x41: //Long reverse L pipe
                case 0x42: //Long reverse L pipe
                case 0x43: //Long reverse L pipe
                case 0x44: //Long reverse L pipe
                case 0x45: //Long reverse L pipe
                case 0x46: //Long reverse L pipe
                case 0x47: //Long reverse L pipe
                case 0x48: //Long reverse L pipe
                case 0x49: //Long reverse L pipe
                case 0x4A: //Long reverse L pipe
                case 0x4B: //Long reverse L pipe
                case 0x4C: //Long reverse L pipe
                case 0x4D: //Long reverse L pipe
                case 0x4E: //Long reverse L pipe
                case 0x4F: //Long reverse L pipe
                case 0x50: //Vertical balls
                case 0x51: //Vertical balls
                case 0x52: //Vertical balls
                case 0x53: //Vertical balls
                case 0x54: //Vertical balls
                case 0x55: //Vertical balls
                case 0x56: //Vertical balls
                case 0x57: //Vertical balls
                case 0x58: //Vertical balls
                case 0x59: //Vertical balls
                case 0x5A: //Vertical balls
                case 0x5B: //Vertical balls
                case 0x5C: //Vertical balls
                case 0x5D: //Vertical balls
                case 0x5E: //Vertical balls
                case 0x5F: //Vertical balls
                case 0x60: //Nothing
                case 0x61: //Nothing
                case 0x62: //Nothing
                case 0x63: //Nothing
                case 0x64: //Nothing
                case 0x65: //Nothing
                case 0x66: //Nothing
                case 0x67: //Nothing
                case 0x68: //Nothing
                case 0x69: //Nothing
                case 0x6A: //Nothing
                case 0x6B: //Nothing
                case 0x6C: //Nothing
                case 0x6D: //Nothing
                case 0x6E: //Nothing
                case 0x6F: //Nothing
                case 0x70: //Nothing
                case 0x71: //Nothing
                case 0x72: //Nothing
                case 0x73: //Nothing
                case 0x74: //Nothing
                case 0x75: //Nothing
                case 0x76: //Nothing
                case 0x77: //Nothing
                case 0x78: //Nothing
                case 0x79: //Nothing
                case 0x7A: //Nothing
                case 0x7B: //Nothing
                case 0x7C: //Nothing
                case 0x7D: //Nothing
                case 0x7E: //Nothing
                case 0x7F: //Nothing
                case 0x80: //Lift's vertical rope
                case 0x81: //Lift's vertical rope
                case 0x82: //Lift's vertical rope
                case 0x83: //Lift's vertical rope
                case 0x84: //Lift's vertical rope
                case 0x85: //Lift's vertical rope
                case 0x86: //Lift's vertical rope
                case 0x87: //Lift's vertical rope
                case 0x88: //Lift's vertical rope
                case 0x89: //Lift's vertical rope
                case 0x8A: //Lift's vertical rope
                case 0x8B: //Lift's vertical rope
                case 0x8C: //Lift's vertical rope
                case 0x8D: //Lift's vertical rope
                case 0x8E: //Lift's vertical rope
                case 0x8F: //Lift's vertical rope
                case 0x90: //Vertical rope to balance lift
                case 0x91: //Vertical rope to balance lift
                case 0x92: //Vertical rope to balance lift
                case 0x93: //Vertical rope to balance lift
                case 0x94: //Vertical rope to balance lift
                case 0x95: //Vertical rope to balance lift
                case 0x96: //Vertical rope to balance lift
                case 0x97: //Vertical rope to balance lift
                case 0x98: //Vertical rope to balance lift
                case 0x99: //Vertical rope to balance lift
                case 0x9A: //Vertical rope to balance lift
                case 0x9B: //Vertical rope to balance lift
                case 0x9C: //Vertical rope to balance lift
                case 0x9D: //Vertical rope to balance lift
                case 0x9E: //Vertical rope to balance lift
                case 0x9F: //Vertical rope to balance lift
                case 0xA0: //Castle
                case 0xA1: //Castle
                case 0xA2: //Castle
                case 0xA3: //Castle
                case 0xA4: //Castle
                case 0xA5: //Castle
                case 0xA6: //Castle
                case 0xA7: //Castle
                case 0xA8: //Castle
                case 0xA9: //Castle
                case 0xAA: //Castle
                case 0xAB: //Castle
                case 0xAC: //Castle
                case 0xAD: //Castle
                case 0xAE: //Castle
                case 0xAF: //Castle
                case 0xC0: //Long reverse L pipe
                case 0xC1: //Long reverse L pipe
                case 0xC2: //Long reverse L pipe
                case 0xC3: //Long reverse L pipe
                case 0xC4: //Long reverse L pipe
                case 0xC5: //Long reverse L pipe
                case 0xC6: //Long reverse L pipe
                case 0xC7: //Long reverse L pipe
                case 0xC8: //Long reverse L pipe
                case 0xC9: //Long reverse L pipe
                case 0xCA: //Long reverse L pipe
                case 0xCB: //Long reverse L pipe
                case 0xCC: //Long reverse L pipe
                case 0xCD: //Long reverse L pipe
                case 0xCE: //Long reverse L pipe
                case 0xCF: //Long reverse L pipe
                case 0xD0: //Vertical balls
                case 0xD1: //Vertical balls
                case 0xD2: //Vertical balls
                case 0xD3: //Vertical balls
                case 0xD4: //Vertical balls
                case 0xD5: //Vertical balls
                case 0xD6: //Vertical balls
                case 0xD7: //Vertical balls
                case 0xD8: //Vertical balls
                case 0xD9: //Vertical balls
                case 0xDA: //Vertical balls
                case 0xDB: //Vertical balls
                case 0xDC: //Vertical balls
                case 0xDD: //Vertical balls
                case 0xDE: //Vertical balls
                case 0xDF: //Vertical balls
                case 0xE0: //Nothing
                case 0xE1: //Nothing
                case 0xE2: //Nothing
                case 0xE3: //Nothing
                case 0xE4: //Nothing
                case 0xE5: //Nothing
                case 0xE6: //Nothing
                case 0xE7: //Nothing
                case 0xE8: //Nothing
                case 0xE9: //Nothing
                case 0xEA: //Nothing
                case 0xEB: //Nothing
                case 0xEC: //Nothing
                case 0xED: //Nothing
                case 0xEE: //Nothing
                case 0xEF: //Nothing
                case 0xF0: //Nothing
                case 0xF1: //Nothing
                case 0xF2: //Nothing
                case 0xF3: //Nothing
                case 0xF4: //Nothing
                case 0xF5: //Nothing
                case 0xF6: //Nothing
                case 0xF7: //Nothing
                case 0xF8: //Nothing
                case 0xF9: //Nothing
                case 0xFA: //Nothing
                case 0xFB: //Nothing
                case 0xFC: //Nothing
                case 0xFD: //Nothing
                case 0xFE: //Nothing
                case 0xFF: //Nothing
                    return true;
            }
            break;
        default:
        switch (hex.at(1))
            {
                case 0x00: //Sideways pipe
                case 0x09: //Sideways pipe
                case 0x0C: //Reverse L pipe
                case 0x0D: //Flagpole
                case 0x0E: //Nothing
                case 0x0F: //Nothing
                case 0x80: //Sideways pipe
                case 0x8C: //Reverse L pipe
                case 0x8D: //Flagpole
                case 0x8E: //Nothing
                case 0x8F: //Nothing
                    return true;
            }
            break;
    }

    return false;
}

bool SMB1LevelGenerator::isBannedEnemy(std::vector<unsigned char> &hex)
{
    if (hex.size() != 2)
        return true;
    if (BinaryManipulator::BinaryStringToHex(BinaryManipulator::HexToBinaryString(hex.at(0)).substr(4)) == 0xE)
        return true; //Room change of some kind
    switch (hex.at(1))
    {
        case 0x13: //Unknown
        case 0x16: //Crash
        case 0x18: //None
        case 0x19: //None
        case 0x1A: //None
        case 0x23: //None
        case 0x24: //Lift (balance)
        case 0x2D: //Bowser
        case 0x2E: //Unknown
        case 0x2F: //Unknown
        case 0x30: //None
        case 0x31: //None
        case 0x32: //Fake jumping board
        case 0x33: //None
        case 0x34: //Warp zone
        case 0x36: //Crash
        case 0x3F: //None
        case 0x93: //Unknown
        case 0x96: //Crash
        case 0x98: //None
        case 0x99: //None
        case 0x9A: //None
        case 0xB2: //Fake jumping board
        case 0xA3: //None
        case 0xA4: //Lift (balance)
        case 0xAD: //Bowser
        case 0xAE: //Unknown
        case 0xAF: //Unknown
        case 0xB0: //None
        case 0xB1: //None
        case 0xB3: //None
        case 0xB6: //Crash
        case 0xBF: //None
        case 0xD3: //Unknown
        case 0xF4: //Warp zone
        case 0xEE: //Unknown
        case 0xEF: //Unknown
        case 0xF0: //None
        case 0xF1: //None
            return true;
    }
    return false;
}

void SMB1LevelGenerator::RandomizeObjects(std::vector<unsigned char> &objects)
{
    for (unsigned int i = 0; i < objects.size() - 1; i += 2)
    {
        //Make sure the level has a proper ending
        if (i == objects.size() - 4)
        {
            objects.at(i) = 0x6D;
            objects.at(i + 1) = 0xC1; //Flagpole
        }
        else if (i == objects.size() - 2)
        {
            objects.at(i) = 0xAF;
            objects.at(i + 1) = 0x26; //Castle
        }
        else if (BinaryManipulator::BinaryStringToHex(BinaryManipulator::HexToBinaryString(objects.at(i)).substr(4)) == 0xE)
        { //Don't mess with values on level 0xE until they are further understood
            continue;
        }
        else
        {
            if (objects.at(i + 1) <= 0x7F)
            {
                short value = 0x00;
                std::vector<unsigned char> object;
                do
                { //Don't allow it to spawn room changes or hard mode enemies
                    value = (short)(rand() % 0x80);
                    object.clear();
                    object.push_back(objects.at(i));
                    object.push_back(value);
                } while (isBannedObject(object));
                objects.at(i + 1) = value;
            }
            else
            {
                short value = 0x00;
                std::vector<unsigned char> object;
                do
                { //Don't allow it to spawn room changes or hard mode enemies
                    value = (short)((rand() % 0x80) + 0x80);
                    object.clear();
                    object.push_back(objects.at(i));
                    object.push_back(value);
                } while (isBannedObject(object));
                objects.at(i + 1) = value;
            }
        }
    }
}

void SMB1LevelGenerator::RandomizeEnemies(std::vector<unsigned char> &enemies)
{
    unsigned int i = 0;
    while (i < enemies.size() - 1)
    {
        if (enemies.at(i) == 0x0F)
        {
            //Skip page changes for now
            i += 2;
            continue;
        }
        else if (BinaryManipulator::BinaryStringToHex(BinaryManipulator::HexToBinaryString(enemies.at(i)).substr(4)) == 0xE)
        {
            //Skip Room changes for now
            i += 3;
            continue;
        }
        else if (BinaryManipulator::HexToBinaryString(enemies.at(i + 1))[0] == '0')
        { //only generate values with no page flag
            short value = 0x00;
            std::vector<unsigned char> enemy;
            do
            { //Don't allow it to spawn hard mode enemies
                value = (short)(rand() % 0x80);
                enemy.clear();
                enemy.push_back(enemies.at(i));
                enemy.push_back(value);
            } while (isBannedEnemy(enemy) || BinaryManipulator::HexToBinaryString(value)[1] == '1');
            enemies.at(i + 1) = value;
        }
        else
        {
            short value = 0x00;
            std::vector<unsigned char> enemy;
            do
            { //Don't allow it to spawn hard mode enemies
                value = (short)((rand() % 0x80) + 0x80);
                enemy.clear();
                enemy.push_back(enemies.at(i));
                enemy.push_back(value);
            } while (isBannedEnemy(enemy) || BinaryManipulator::HexToBinaryString(value)[1] == '1');
            enemies.at(i + 1) = value;
        }
        i += 2;
    }
}

std::vector<unsigned char> SMB1LevelGenerator::ReadLevelHeader(std::fstream &file, int offset)
{
    file.clear();
    file.seekg(offset, std::ios_base::beg);
    std::vector<unsigned char> header;
    for (int i = 0; i < 2; ++i)
    {
        header.push_back((unsigned char)file.get());
    }
    return header;
}

std::vector<unsigned char> SMB1LevelGenerator::ReadLevelObjects(std::fstream &file, int offset)
{
    //Determine the amount of objects in the level
    file.clear();
    file.seekg(offset, std::ios_base::beg);
    int objectCount = 0;
    while ((unsigned char)file.get() != 0xFD)
    {
        file.get(); //ignore the object byte
        ++objectCount;
    }

    std::vector<unsigned char> objects;
    file.clear();
    file.seekg(offset, std::ios_base::beg);
    for (int i = 0; i < (objectCount * 2); ++i)
    {
        objects.push_back((unsigned char)file.get());
    }

    return objects;
}

std::vector<unsigned char> SMB1LevelGenerator::ReadLevelEnemies(std::fstream &file, int offset)
{
    //Determine the amount of bytes worth of enemies in the level
    file.clear();
    file.seekg(offset, std::ios_base::beg);
    int enemyCountBytes = 0;
    std::vector<unsigned char> check;
    for (int i = 0; i < 2; ++i)
    {
        check.push_back((unsigned char)file.get());
    }
    while (check.at(0) != 0xFF)
    {
        if (BinaryManipulator::BinaryStringToHex(BinaryManipulator::HexToBinaryString(check.at(0)).substr(4)) == 0xE)
        { //Room changes are 3 bytes instead of 2, so handle accordingly
            enemyCountBytes += 3;
            file.get(); //skip the next byte
        }
        else
        {
            enemyCountBytes += 2;
        }
        check.clear();
        for (int i = 0; i < 2; ++i)
        {
            check.push_back((unsigned char)file.get());
        }
    }

    std::vector<unsigned char> enemies;
    file.clear();
    file.seekg(offset, std::ios_base::beg);
    for (int i = 0; i < enemyCountBytes; ++i)
    {
        enemies.push_back((unsigned char)file.get());
    }

    return enemies;
}

int SMB1LevelGenerator::LowballRandomValue(int min, int max)
{
    if (min >= max)
        return max;
    int difference = max - min;
    float change = 0;
    if (difference != 0)
    { //prevent division by 0
        change = (max - min) / difference;
    }
    int value = 0;
    int newMin = 0;
    int newMax = 0;
    int chance = 0;
    chance = (rand() % 100) + 1;
    //Lower values are more likely to be generated
    if (chance <= 35)
    {
        newMin = min;
        newMax = max - (int)(4 * change);
    }
    else if (chance <= 65)
    {
        newMin = min + (int)change;
        newMax = max - (int)(3 * change);
    }
    else if (chance <= 85)
    {
        newMin = min + (int)(2 * change);
        newMax = max - (int)(2 * change);
    }
    else if (chance <= 95)
    {
        newMin = min + (int)(3 * change);
        newMax = max - (int)change;
    }
    else if (chance <= 100)
    {
        newMin = min + (int)(4 * change);
        newMax = max;
    }

    //Fix the values if they are improper
    if (newMin < min)
    {
        newMin = min; //max can't be lower than the default
    }
    if (newMax > max)
    {
        newMax = max; //max can't be higher than the default
    }

    //Check for calculation error
    if (newMin > newMax)
    {
        newMin = min;
        if (newMin > newMax)
        {
            newMax = max;
        }
    }
    if (newMin == newMax)
        return newMax;

    value = (rand() % (newMax - newMin)) + newMin; //generate the value

    return value;
}

