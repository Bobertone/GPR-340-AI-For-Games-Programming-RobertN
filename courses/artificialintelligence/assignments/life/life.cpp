#include <iostream>
#include <vector>
#include <stack>
#include <string>
using namespace std;
vector<bool> vCurrent, vNext;
int columns, rows, steps;

void ReadMatrix()
{
  vCurrent.resize(columns*rows);
  vNext.resize(columns*rows);

  string line;
  getline(cin,line);
  for(int r=0; r<rows;r++)
  {
    getline(cin, line);
    for(int c=0; c<columns; c++) {
      if (line[c] == '.')
        vCurrent[r * columns + c] = false;
      else if (line[c] == '#')
        vCurrent[r * columns + c] = true;
      else
        throw "this should never happen 1";
    }
  }
}

void PrintMatrix()
{
  for(int r=0; r<rows;r++)
  {
    for(int c=0; c<columns; c++) {
      if (!vCurrent[r * columns + c])
        cout << '.';
      else if (vCurrent[r * columns + c])
        cout << '#';
    }
    cout << endl;
  }
}

int CountNeighbors(int xTarget,int yTarget)
{
  int neighbors = 0;
  for(int x = xTarget-1; x <= xTarget+1; x++)  {
    for(int y = yTarget-1; y <= yTarget+1; y++) {
      if (x == xTarget && y == yTarget) continue;
      int xx = x;
      int yy = y;
      if (x < 0)
        xx=columns-1;
      if (y < 0)
        yy=rows-1;
      if(x>=columns)
        xx = 0;
      if(y>=rows)
        yy=0;

//      if (x >= 0 && y >= 0 && x < columns && y < rows)
      {  // if within bounds... this could be done at the bottom but eh this should work
        if (vCurrent[yy * columns + xx]) {
          neighbors++;
          continue;
        }  // check state of element in current vector
      }
//      // the following code accounts for wrapping to neighbors across edges
//      else if (x < 0)  // if x is too small
//      {
//        if (y >= rows) {
//          if (vCurrent[0 * columns + rows]) {
//            neighbors++;
//          }
//        }  // and if y is too big
//        else if (y < 0) {
//          if (vCurrent[rows * columns + rows]) {
//            neighbors++;
//          }
//        }  // and if y is too small
//        else {
//          if (vCurrent[y * columns + rows]) {
//            neighbors++;
//          }
//        }
//      } else if (x >= columns)  // if x is too big
//      {
//        if (y >= rows) {
//          if (vCurrent[0 * columns + 0]) {
//            neighbors++;
//          }
//        }  // and if y is too big
//        else if (y < 0) {
//          if (vCurrent[rows * columns + 0]) {
//            neighbors++;
//          }
//        }  // and if y is too small
//        else {
//          if (vCurrent[y * columns + 0]) {
//            neighbors++;
//          }
//        }
//      } else {
//        if (y >= rows) {
//          if (vCurrent[0 * columns + x]) {
//            neighbors++;
//          }
//        }  // if y is too big
//        else if (y < 0) {
//          if (vCurrent[rows * columns + x]) {
//            neighbors++;
//          }
//        }  // if y is too small
//        else {
//          throw "this should never happen 2";
//        }  // in this case, the target is not out of bounds, which should have already been handled.
      }
    }
  return neighbors;
}

void step()
{
  for(int y = 0; y < rows; y++)
  {
    for(int x = 0; x < columns; x++)
    {
      bool isAlive = vCurrent[x+y*columns];
      int neighbors = CountNeighbors(x,y);

      if(isAlive)
      {
        //Any live cell with fewer than two live neighbours dies, as if by underpopulation.
        if(neighbors<2){ vNext[x+y*columns] = false; }
        //Any live cell with two or three live neighbours lives on to the next generation.
        if(neighbors==2||neighbors==3){ vNext[x+y*columns] = true; }
        //Any live cell with more than three live neighbours dies, as if by overpopulation.
        if(neighbors>3){vNext[x+y*columns] = false; }
      }
      else
      {
        //Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
        if(neighbors==3){vNext[x+y*columns] = true;}
      }
    }
  }
}

int main(){

  cin >> columns >> rows >> steps;
  ReadMatrix();
  for(int i = 0; i < steps; i++)
  {
    step();
    vCurrent = vNext;
  }
  PrintMatrix();

};

