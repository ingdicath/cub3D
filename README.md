# cub3D
CODAM project Curriculum 2019

- [minilibx](https://github.com/ttshivhula/minilibx)
- [images example](https://github.com/keuhdall/images_example)

- Se usa esta libreria  minilibx_mms_20200219_beta.tgz
- Se usa GNL para leer el mapa
- Puede no haber sprites dentro del proyecto, aun asi el mapa es valido y debe correr
- NO puede haber valores negativos en los colores
- NO puede haber valores faltantes o adicionales en alguna de las variables. Ejempl: los colores tienen 3 valores, la resolucion tiene dos valores.

##  Consideraciones

- Except for the map content, each type of element can be separated by one or
more empty line(s).
_Se refiere a cada elemento del mapa como Resolucion, color, etc. puede estar separado por una o mas lineas vacias_

'''
R 1920 1080
NO ./path_to_the_north_texture


SO ./path_to_the_south_texture
WE ./path_to_the_west_texture

EA ./path_to_the_east_texture

S ./path_to_the_sprite_texture
F 220,100,0
C 225,30,0
'''

- Except for the map content which always has to be the last, each type of
element can be set in any order in the file.

_Despues del mapa no pueden existir otros elementos, como Resolucion, color, etc_


- Except for the map, each type of information from an element can be separated
by one or more space(s).
_Se refiere a que dentro de cada elemento puede estar separado por uno o mas espacios_
F 220  ,     100,      0   


- The map must be parsed as it looks like in the file. Spaces are a valid part of
the map, and is up to you to handle. You must be able to parse any kind of
map, as long as it respects the maps rules.


