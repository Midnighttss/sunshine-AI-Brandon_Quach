#pragma once
#include"raylib.h"
#include "TileCoord.h"

#define MAP_WIDTH 32
#define MAP_HEIGHT 24


const int MAPWIDTH = 24;


enum class Tile
{
	floor =0,
	wall ,
	count
};


class Tilemap
{

public:
	float tileSizeX = 32;
	float tileSizeY = 24;
	Color tileColors[(int)Tile::count];


	Tile tiles [MAP_WIDTH][MAP_HEIGHT];
	Vector2 GetScreenPositionOfTile(TileCoord coordinate)
	{
		return { coordinate.x * tileSizeX,coordinate.y * tileSizeY };

	}
	

	Tilemap()
	{
		tileColors[(int)Tile::floor] = BLUE;
		tileColors[(int)Tile::wall] = BLACK;
	}


	void Randomize()
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			for (int y = 0; y < MAP_HEIGHT; y++)
			{
				tiles[x][y] = (Tile)(rand() % (int)Tile::count);
			}
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


			}
		}
	}

};