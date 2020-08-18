# cub3D
CODAM project Curriculum 2019

- [minilibx](https://github.com/ttshivhula/minilibx)
- [images example](https://github.com/keuhdall/images_example)
- [Raycasting](https://lodev.org/cgtutor/raycasting.html)

- Se usa esta libreria  minilibx_mms_20200219_beta.tgz 

NOTA: asegurarse que en el MAC que se vaya a utilizar se tenga instalado X11 (https://www.xquartz.org/)
- Se usa GNL para leer el mapa
- Puede no haber sprites dentro del proyecto, aun asi el mapa es valido y debe correr
- NO puede haber valores negativos en los colores
- NO puede haber valores faltantes o adicionales en alguna de las variables. Ejempl: los colores tienen 3 valores, la resolucion tiene dos valores.

##  Consideraciones

- Except for the map content, each type of element can be separated by one or
more empty line(s).
_Se refiere a cada elemento del mapa como Resolucion, color, etc. puede estar separado por una o mas lineas vacias_

```
R 1920 1080
NO ./path_to_the_north_texture


SO ./path_to_the_south_texture
WE ./path_to_the_west_texture

EA ./path_to_the_east_texture

S ./path_to_the_sprite_texture
F 220,100,0
C 225,30,0
```

- Except for the map content which always has to be the last, each type of
element can be set in any order in the file.

_Despues del mapa no pueden existir otros elementos, como Resolucion, color, etc, pero si podrian haber espacios_


- Except for the map, each type of information from an element can be separated
by one or more space(s).
_Se refiere a que dentro de cada elemento puede estar separado por uno o mas espacios_

```
F 220  ,     100,      0   
```

- The map must be parsed as it looks like in the file. Spaces are a valid part of
the map, and is up to you to handle. You must be able to parse any kind of
map, as long as it respects the maps rules.

_Pueden existir espacios dentro del mapa, siempre que se respeten las reglas de construccion del mismo_


NOTAS:

I found however that it's much easier to work with vectors and a camera instead: the position of the player is always a vector (an x and a y coordinate), but now, we make the direction a vector as well: so the direction is now determinated by two values: the x and y coordinate of the direction. 



- Matriz de rotacion
https://es.wikipedia.org/wiki/Matriz_de_rotaci%C3%B3n


## USEFUL LINKS

- [Wolfenstein 3D's map renderer](https://www.youtube.com/watch?v=eOCQfxRQ2pY)
- [mlx tutorial](https://harm-smits.github.io/42docs/libs/minilibx.html)

compile in this way


```
gcc main.c -Wall -Wextra -Werror -Lmlx -lmlx -framework OpenGL -framework AppKit

```
- It must have to do make into the mlx folder in order to get libmlx.dylib library, and put it in the root of the project

- [Key codes](https://eastmanreference.com/complete-list-of-applescript-key-codes)
- https://bit-calculator.com/es/desplazamiento-de-bit
- [Permissions bits for open function](https://www.gnu.org/software/libc/manual/html_node/Permission-Bits.html)
- [BMP file format](https://en.wikipedia.org/wiki/BMP_file_format)
- [Example to create BMP file](https://stackoverflow.com/questions/11004868/creating-a-bmp-file-bitmap-in-c)
- [Tutorial 1 BMP](https://engineering.purdue.edu/ece264/17au/hw/HW15)
- [Tutorial 2 MEDIUM BMP, the best option](https://medium.com/sysf/bits-to-bitmaps-a-simple-walkthrough-of-bmp-image-format-765dc6857393)
- [Tutorial 3 BMP](https://web.archive.org/web/20080912171714/http://www.fortunecity.com/skyscraper/windows/364/bmpffrmt.html)