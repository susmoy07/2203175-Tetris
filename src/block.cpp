#include "block.h"
#include <cmath>

Block::Block()
{
    cellSize = 30;
    rotationState = 0;
    colors = GetCellColors();
    rowOffset = 0;
    columnOffset = 0;
}

void Block::Draw(int offsetX, int offsetY)
{
    std::vector<Position> tiles = GetCellPositions();
    for (Position item : tiles)
    {
        Color c = colors[id];
        float glow = (sin(GetTime() * 3.0f) + 1.0f) * 0.5f;  // pulsates from 0 to 1
        c.r = fmin(255, c.r + 50 * glow);
        c.g = fmin(255, c.g + 50 * glow);
        c.b = fmin(255, c.b + 50 * glow);

        DrawRectangle(item.column * cellSize + offsetX, item.row * cellSize + offsetY,
                      cellSize - 1, cellSize - 1, c);
    }
}

void Block::Move(int rows, int columns)
{
    rowOffset += rows;
    columnOffset += columns;
}

std::vector<Position> Block::GetCellPositions()
{
    std::vector<Position> tiles = cells[rotationState];
    std::vector<Position> movedTiles;
    for (Position item : tiles)
    {
        Position newPos = Position(item.row + rowOffset, item.column + columnOffset);
        movedTiles.push_back(newPos);
    }
    return movedTiles;
}

void Block::Rotate()
{
    rotationState++;
    if (rotationState == (int)cells.size())
    {
        rotationState = 0;
    }
}

void Block::UndoRotation()
{
    rotationState--;
    if (rotationState == -1)
    {
        rotationState = cells.size() - 1;
    }
}
