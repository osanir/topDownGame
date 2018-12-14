#!/bin/bash

g++ src/*.cpp -o game -lsfml-graphics -lsfml-window -lsfml-system -lGL -lsfml-audio
./game