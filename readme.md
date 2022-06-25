# Building

## Dependencies:
### Ubuntu
```
apt install gcc liballegro5.2 liballegro-image5.2 liballegro-audio5.2 liballegro_acodec5.2
```
### Arch
```
pacman -S gcc allegro
```

## Build with:
```
gcc solitaire.c -lallegro -lallegro_image -lallegro_audio -lallegro_acodec -lallegro_font -o solitaire -Wall -Werror
```
Or if using `cmake`, you can build with:
```
cmake .
```
