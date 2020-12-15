#include<iostream>
#include<vector>
#include<iomanip>
#include<stdexcept>
using namespace std;

const int kSize = 8;

class Maze {
 public:
  //使用固定迷宫
  void SetFixedMaze();
  //手动设置迷宫
 void SetMaze();
 void SetEntrance();
 void SetExit();

 int GetEntranceX() { return _extrance_row; }
 int GetEntranceY() { return _extrance_col; }

 //搜索
 void Dfs(int x,int y);

 //输出
 void PrintMaze();
 void PrintAnswer();
 private:
 vector<vector<char>> _maze;
  vector<vector<bool>> _is_traversed;
  vector<vector<int>> _step = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
  vector<vector<int>> _answer;
  vector<vector<vector<int>>> _all_paths;
  int _row;
  int _col;
  //迷宫入口
  int _extrance_row;
  int _extrance_col;
  //迷宫出口
  int _exit_row;
  int _exit_col;
};

void Maze::SetFixedMaze() { 
  vector<char> a = {'#', '#', '#', '#', '#', '#', '#'};
  _maze.push_back(a);
  a = {'#', '0', '#', '0', '0', '0', '#'};
  _maze.push_back(a);
  a = {'#', '0', '#', '0', '#', '#', '#'};
  _maze.push_back(a);
  a = {'#', '0', '0', '0', '#', '0', '#'};
  _maze.push_back(a);
  a = {'#', '0', '#', '0', '0', '0', '#'};
  _maze.push_back(a);
  a = {'#', '0', '#', '0', '#', '0', '#'};
  _maze.push_back(a);
  a = {'#', '#', '#', '#', '#', '#', '#'};
  _maze.push_back(a);
  for (int i = 0; i <kSize ; i++) {
    vector<bool> a(8,false);
    _is_traversed.push_back(a);
  }
  _extrance_col = 1;
  _extrance_row = 1;
  _exit_col = 5;
  _exit_row = 5;
  _answer.push_back({_extrance_row, _extrance_col});
  return;
}

void Maze::SetMaze() {
  int col, row;
  std::cout << "Please enter the number of rows and columns of maze" << std::endl;
  std::cout << "Number of lines:";
  std::cin >> _row;
  std::cout << "Number of columns:";
  std::cin >> _col;
  for (int i = 0; i < _row; i++) {
    vector<char> a;
    vector<bool> b;
    _maze.push_back(a);
    _is_traversed.push_back(b);
    for (int j = 0; j < _col; j++) {
      char ch;
      std::cin >> ch;

      _maze[i].push_back(ch);
      _is_traversed[i].push_back(false);
    }
  }
  return;
}

void Maze::SetEntrance() {
  std::cout << "Please enter the entry coordinate (if the coordinate is (1,1), then enter 1,1)";
  std::cin >> _extrance_row >> _extrance_col;
  _answer.push_back({_extrance_row, _extrance_col});
}

void Maze::SetExit() {
  std::cout << "Please enter the exit coordinate (if the coordinate is (1,1), then enter 1,1)";
  std::cin >> _exit_row >> _exit_col;
}

void Maze::Dfs(int x, int y) {
  _is_traversed[x][y] = true;
  for (int i = 0; i < 4; i++) {
    int new_x = x + _step[i][0];
    int new_y = y + _step[i][1];
    vector<int> temp = {new_x, new_y};
    _answer.push_back(temp);
    if (new_x == _exit_row && new_y == _exit_col) {
      _all_paths.push_back(_answer);
    }
    if (_maze[new_x][new_y] == '0' && new_x >= 0 && new_y >= 0 &&
        _is_traversed[new_x][new_y] == false)
      Dfs(new_x, new_y);
    _answer.pop_back();
  }
  _is_traversed[x][y] = false;
  return;
}

void Maze::PrintMaze() {
  cout << "Maze map:" << endl;
  cout << "   ";
  for (int j = 0; j < _maze.size(); j++) {
    cout << setw(6) << setiosflags(ios::right)  << "column "<< j;
  }
  cout << endl;
  for (int i = 0; i < _maze.size(); i++) {
    cout  << "row "<< i;
    for (int j = 0; j < _maze[i].size(); j++) {
      cout << setw(8) <<setiosflags(ios::right)<< _maze[i][j];
    }
    cout << endl<<endl;
  }
  return;
}

void Maze::PrintAnswer() {
  cout << "Maze path:" << endl;
  for (int i = 0; i < _all_paths.size(); i++) {
    for (int j = 0; j < _all_paths[i].size(); j++) {
      cout << '<' <<_all_paths[i][j][0] << ',' << _all_paths[i][j][1] << '>';
      if (j != _all_paths[i].size() - 1) cout << " ---> ";
    }
    cout << endl;
  }
  return;
}

void Solve() {
  Maze maze;
  
  std::cout<<"Manual input labyrinth(enter A) or fixed labyrinth(enter B):";
  
  char judge;
  std::cin>>judge;
  if(judge == 'A') {
  //手动输入迷宫
  maze.SetMaze();
  maze.SetEntrance();
  maze.SetExit();
  }
  else if(judge=='B'){
  //固定迷宫
  maze.SetFixedMaze();
  }
  else throw invalid_argument("Wrong Input");

  maze.PrintMaze();

  maze.Dfs(maze.GetEntranceX(), maze.GetEntranceY());

  maze.PrintAnswer();
  return;
}

int main(void) { 
  Solve();
  system("pause");
  return 0; 
}