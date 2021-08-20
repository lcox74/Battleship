# Battleship

Terminal based battleship where you verse an AI. In typical battleship
tradition, the game is turn based and requires coordinates to try to
hit the enemies ships.

The playing field will look like the following:

```
  1 2 3 4 5 6 7 8 9 10
A . . . . . . . . . .
B . . . . . . . . . .
C . . . . . . . . . .
D . . . . . . . . . .
E . . . . . . . . . .
F . . . . . . . . . .
G . . . . . . . . . .
H . . . . . . . . . .
I . . . . . . . . . .
======================
  1 2 3 4 5 6 7 8 9 10
A . . . . . . . . . .
B . . . . . . . . . .
C . . . . . . . . . .
D . . . . . . . . . .
E . . . . . . . . . .
F . . . . . . . . . .
G . . . . . . . . . .
H . . . . . . . . . .
I . . . . . . . . . .
```

Where the top field is the enemy teritory and the bottom is the players.
The game starts with the player selecting where to place their boats, the
choice of boats are the following:

| Number | Boat       | Size |
| ------ | ---------- | ---- |
| 1      | Carrier    | 5    |
| 2      | Battleship | 4    |
| 3      | Cruiser    | 3    |
| 4      | Submarine  | 3    |
| 5      | Destroyer  | 2    |

Placement of boats require the following syntax: 
`<Boat Number><Coordinate><Direction>`. Boat number comes from the table 
above, coordinates must have be a letter followed by a number, i.e. `A1` for
the top left. Directions can be one of the following up(`U`), down(`D`), 
left(`L`), right(`R`). An example for a boat placement would be: `1B3D`.
Which would create a Carrier at `B3` facing down.
```  
  1 2 3 4 5 6 7 8 9 10
A . . . . . . . . . .
B . . b . . . . . . .
C . . b . . . . . . .
D . . b . . . . . . .
E . . b . . . . . . .
F . . b . . . . . . .
G . . . . . . . . . .
H . . . . . . . . . .
I . . . . . . . . . .
```
