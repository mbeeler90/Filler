# filler

## About
Filler is an AI project where the goal is to be the last player to put a piece (with a random size and shape) sent by a Virtual Machine. To put a piece it needs to overlap with one (and only one) piece already placed.

## Stragegy
- Create a heat map that indicates how close a field is to the opponent's pieces.
- Place the piece on the field to get as closely as possible to the opponent's pieces in order to surround the opponent.

## Compiling
Run `make` to compile an executable called fillit.

## Usage
`./resources/filler_vm -f ./resources/maps/[MAP] -p1 ./[P1_NAME] -p2 ./[P2_NAME]`
