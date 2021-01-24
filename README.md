# Mines ParisTech - UE 12 - Programmation en `C++`

## Projet du premier semestre - Louis-Justin TALLOT

## Encodage et décodage de code Morse


### Getting started

In Linux, launch a `bash` session, `cd` in a clean directory, and type : 

```bash

git clone https://https://github.com/LouisJustinTALLOT/projet-CPP-Morse

cd projet-CPP-Morse

make
```
and you are ready to go ! The program is launched by doing `./main`.

### How to use 

All the inputs have to be placed in `./in`: 
- `./in/txt` for the `.txt` files containing some english text you want to decode
- `./in/wav` for the `.wav` files containing some Morse to be decoded 


All the outputs will be placed in `./out`: 
- `./out/txt` for the `.txt` files containing some english text that has been decoded
- `./out/wav` for the `.wav` files containing some Morse to be decoded 


#### To encode some text : 

- either you type it directly : `./main Some text to decode`
- or your enter it in a `.txt` file in `./in/txt`, for example `input_23.txt` : `./main input_23.txt`

The program will print you the Morse output and tell you the name of the audio file it generated in `./out/wav`.

#### To decode some Morse

- either you type it directly : `./main - .... .. ...   .. ...   .-   - . ... -   ..-. .. .-.. .`
- or your enter a `.wav` file in `./in/wav`, for example `input_23.wav` : `./main input_23.wav`

The program will print you the textual output and tell you the name of the audio file it generated in `./out/txt`.

### Testing

- if you only run `./main` without any arguments, some testing commands will be run, and a `output.wav` generated.
- in `./tests` are some shell files that can run tests with the already existing files in `./in`.
:warning: the last 2 tests will only run if there are pre-existing files in the `./in` directory. For example you can run : 
    - `./tests/test_morse_bash.sh`
    - `./tests/test_text_bash.sh`
    - `./tests/test_morse_in.sh`
    - `./tests/test_text_in.sh`


To get rid of the initial files in `./in`, you can use a shell script : 
```bash
# in main directory
bash clean_start.sh
```

### Development 

You can improve this project : simply change as you want the `.cpp` files in `./src`, with the header files located in `./src`, and compile with `make` !

You can get `make` on Ubuntu by doing `sudo apt-get install make`.