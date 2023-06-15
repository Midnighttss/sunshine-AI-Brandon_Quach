#pragma once
#include"raylib.h"
#include "TileCoord.h"

#define MAP_WIDTH 32
#define MAP_HEIGHT 30



enum class Tile
{
	floor =0,
	wall ,
	count,
	player
};


class Tilemap
{
private:
	bool isWalkable[(int)Tile::count];

public:
	float tileSizeX = 32;
	float tileSizeY = 30;
	Color tileColors[(int)Tile::count];

	TileCoord positionOfPlayer;

	Tile GetTile(int x, int y);

	Tile tiles [MAP_WIDTH][MAP_HEIGHT];

	Vector2 GetScreenPositionOfTile(TileCoord coords)
	{
		return { coords.x * tileSizeX,coords.y * tileSizeY };

	}

	Vector2 GetTileAtScreenPosition(Vector2 coords)
	{
		return { coords.x / tileSizeX, coords.y / tileSizeY };
	}

	Tilemap()
	{
		tileColors[(int)Tile::floor] = BROWN;
		tileColors[(int)Tile::wall] = BLACK;

		isWalkable[(int)Tile::floor] = true;

	}

	

	bool isTileWalkable(TileCoord coords)
	{
		if (coords.x>=0 && coords.x < MAP_WIDTH && coords.y >= 0 && coords.y < MAP_HEIGHT)
		{
			Tile tileType = tiles[coords.x][coords.y];
			return isWalkable[static_cast<int>(tileType)];
		}
		return false;
	}


	void Randomize(int chanceOfWall=30)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			for (int y = 0; y < MAP_HEIGHT; y++)
			{
				if (rand()%100+1<chanceOfWall)
				{
					tiles[x][y] = Tile::wall;
				}
				else
				{
					tiles[x][y] = Tile::floor;
				}
			}

			//Randomize the player spawn
			int playerX;
			int playerY;

			do
			{
				playerY = rand() % MAP_HEIGHT;
				playerX = rand() % MAP_WIDTH;
			} while (tiles[playerX][playerY] !=Tile::floor);
			positionOfPlayer = TileCoord(playerX, playerY);
		}
	}


	

	void Draw()
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			for (int y = 0; y < MAP_HEIGHT; y++)
			{
				Tile tileType = tiles[x][y];
				Color tileColor =tileColors[(int)tileType];
				

				DrawRectangle(x * tileSizeX, y * tileSizeY, tileSizeX, tileSizeY, tileColor);

				Vector2 playerPositionOnScreen = GetScreenPositionOfTile(positionOfPlayer);
				DrawRectangle(static_cast<int>(playerPositionOnScreen.x), static_cast<int>(playerPositionOnScreen.y), tileSizeX, tileSizeY, BLUE);
			}
		}
	}

};