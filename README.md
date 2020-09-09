# cub3D

***CODAM project Curriculum 2019/2020 - My first RayCaster with miniLibX***

This project is inspired by the world-famous eponymous 90’s game, which
was the first FPS ever. It will enable you to explore ray-casting. The goal was to
make a dynamic view inside a maze.

This project contained mandatory part and some bonuses.


## Mandatory part

- It is allowed to use both XPM and PNG images.
- The map must to have a '.cub' extension.

### How to start

- Build :hammer: with ```make```

- Run the executable ```cub3D``` and choose a valid map
```
$ ./cub3D ./<file name path with a valid map>
```
- For screenshot add ```--save```
```
$ ./cub3D ./<file name path with a valid map> --save
```

### Actions

| Key           | Action        | 
| ------------- |---------------| 
|    `W`    | move forward  | 
|    `A`    | move left     | 
|    `S`    | move backward | 
|    `D`    | move rigth    |
|  :arrow_left:   | look left    |
|  :arrow_right: | look right   |

```ESC``` or click on the red button :red_circle: to exit the game.

## Bonus part :star:



### How to start

- Build :hammer: with ```make bonus```

- Run the executable ```cub3D``` and choose a bonus valid map
```
$ ./cub3D ./<file name path with a bonus valid map>
```
- For screenshot add ```--save```
```
$ ./cub3D ./<file name path with a bonus valid map> --save
```
### Bonuses implemented

- Wall collisions.
- Floor and ceiling texture.
- Ability to look up and down.
- Jump and crouch.
- More items in the maze.
- Object collisions.
- Rotate the point of view with the mouse: look up, look down, look left, look right

![Demo bonus part](demo/bonus_demo.gif)

### Actions

Including the movements for mandatory part, bonus part has the following extra movements:
- :arrow_up: &nbsp; look up
- :arrow_down: &nbsp; look down
- ```SPACE``` jump
- ```LShift``` crouch
- Mouse movements

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp; :arrow_up:<br>
&nbsp;&nbsp;&nbsp;&nbsp;:arrow_left: &nbsp; :arrow_right: <br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp; :arrow_down: <br>

## Resources :books:

More info in the Wiki!
