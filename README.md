# cub3D

CODAM project Curriculum 2019/2020 - My first RayCaster with miniLibX

This project is inspired by the world-famous eponymous 90’s game, which
was the first FPS ever. It will enable you to explore ray-casting. The goal was to
make a dynamic view inside a maze.

This project contained mandatory part and some bonuses.

## Mandatory part

### How to run it

- Run ```make```

- Run the executable ```cub3D``` and choose a valid map
```
$ ./cub3D ./<file name of your choise with a valid map>
```
- For screenshot add ```--save```
```
$ ./cub3D ./<file name of your choise with a valid map> --save
```

### Movements

- ```W``` move forward
- ```A``` move backward
- ```S``` move rigth
- ```D``` move left
- ```🠈``` look left
- ```🠊``` look right

## Bonus part

### How to run it

- Run ```make bonus```

- Run the executable ```cub3D``` and choose a bonus valid map
```
$ ./cub3D ./<file name of your choise with a bonus valid map>
```
- For screenshot add ```--save```
```
$ ./cub3D ./<file name of your choise with a bonus valid map> --save
```
### Bonuses implemented

- Wall collisions.
- Floor and ceiling texture.
- Ability to look up and down.
- Jump and crouch.
- More items in the maze.
- Object collisions.
- Rotate the point of view with the mouse: look up, look down, look left, look right

### Movements

Including the movements for mandatory part, bonus part has the following extra movements:
- ```🠉``` look up
- ```🠋``` look down
- ```Space key``` jump
- ```Left Shift``` crouch

```
Mouse movements
   🠉
 🠈  🠊
   🠋

```
