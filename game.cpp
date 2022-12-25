#include "game.hpp"
#include "painter.hpp"
#include <cstdlib>

Game::Game()
{
    for (int y = 0; y < window_height; ++y)
        for (int x = 0; x < window_width; ++x)
        {
            field_[x][y].state = closed;
            field_[x][y].hasMine = false;
        }
    for (int i = 0; i < 10; ++i)
    {
        int x, y;
        do
        {
            x = rand() % window_width;
            y = rand() % window_height;
        }
        while (field_[x][y].hasMine);
        field_[x][y].hasMine = true;
    }
}

void Game::draw()
{
    Painter p;
    for (int y = 0; y < window_height; ++y)
        for (int x = 0; x < window_width; ++x)
        {
            switch (field_[x][y].state)
            {
            case closed:
                p.drawClosedField(x, y);
                break;
            case opened:
                if (!field_[x][y].hasMine)
                {
                    int minesAround = 0;
                    for (int yy = y - 1; yy <= y + 1; ++yy)
                        for (int xx = x - 1; xx <= x + 1; ++xx)
                        {
                            if ((xx == x && yy == y) ||
                                xx < 0 || xx >= window_width ||
                                yy < 0 || yy >= window_height)
                                continue;
                            if (field_[xx][yy].hasMine)
                                ++minesAround;
                        }
                    p.drawOpenedField(x, y, minesAround);
                }
                else
                    p.drawMine(x, y);
                break;
            case bomb_flag:
                p.drawFlag(x, y);
                break;
            }
        }
}

void Game::open(int x, int y)
{
    field_[x][y].state = opened;
}

void Game::mark(int x, int y)
{
    switch (field_[x][y].state)
    {
    case opened:
        break;
    case closed:
        field_[x][y].state = bomb_flag;
        break;
    case bomb_flag:
        field_[x][y].state = closed;
        break;
    }
}
