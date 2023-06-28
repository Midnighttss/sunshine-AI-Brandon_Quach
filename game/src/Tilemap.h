#pragma once
#include"raylib.h"
#include "TileCoord.h"
#include<vector>

#define MAP_WIDTH 32
#define MAP_HEIGHT 22



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
	float tileSizeY = 32;
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

	};

	std::vector<TileCoord> GetAllTraversableTiles()
	{

	}
	Tile GetTile(TileCoord tilePos); // get the tile at the specified coordinate in the grid

	void SetTile(TileCoord tilePos, Tile value);  // set the tile at the specified coordinate in the grid

	bool ContainsTile(TileCoord tilePosition); // returns true if the coordinate is inside the grid, false otherwise

	bool IsTraversableAt(TileCoord tilePosition); // Returns true if the specified tile is in the level and walkable, false otherwise

	int GetCostForTile(TileCoord tilePositon)  // having this function makes it easier to change costs per tile the future
	{
		return 1;
	}

	Vector2 GetScreenPosOfTileCentered(TileCoord tilePos); //Convert from a tile coordinate to a screen position in middle of tile

	Vector2 GetScreenPosOfTile(TileCoord tilePosition); //Convert from a tile coordinate to a screen position at top left corner of tile

	TileCoord GetTileAtScreenPos(Vector2 positionOnScreen); //Find a tile coordinate given a position on the screen over a tile

	std::vector<TileCoord> GetAllTiles(); // return all tile positions


	std::vector<TileCoord> GetTraversableTilesAdjacentTo(TileCoord tilePos); // For a given TileCoord, return all TileCoords which are adjacent and are traversable

	/////////////////////////////////////////////////////////////////////////////////////
	// Drawing functions ////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////

	void DrawTiles(); // Draw all tiles

	void DrawBorders(Color color = BLACK); // Draw lines between tiles

	void DrawAdjacencies(); // Draw lines indicating which tiles are connected to which others

	void DrawCoordinates(); // Write the TileCoordinate on each tile

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