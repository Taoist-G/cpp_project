# cpp_project
**SUSTech CS205 C/C++ Program Design Project**

可执行文件：mySokuban

可执行文件运行指令：
```
./mySokuban
```
主菜单页面：
```
Welcome to Sokoban!
1. Level 1
2. Level 2
3. Level 3
4. Level 4
5. Level 5
6. Load game
E. Exit
Select level : 
```
输入数字1-5进入不同难度地图，或者输入数字6并输入文件名读取存档（例：test1）。

地图元素及操作信息：
```
| Map information:                                   |
| P: Player         p: Player on checkpoint          |
| B: Box            b: Box on storage point          |
| In: InternalBox   in: InternalBox on storage point |
| =: Checkpoint     -: Storage point                 |
| #: Wall           X: Infinity space                |

| Game operator:                                     |
| R: Restart        Q: Quit(Back to menu)            |
| W/A/S/D: Move                                      |
| U:Undo            Z:Save game                      |
```
输入Z对当前游戏进度进行存档，需要输入存档文件名。

游戏胜利条件：
```
玩家位于玩家检测点处，所有箱子检测点处都有箱子（在我们的游戏中，箱子数量可能多于箱子检测点数）。
```
**注**：
```
2-infinite space 和 empty space 只能进不能出。箱子进入以上空间会被判定为丢失。
```