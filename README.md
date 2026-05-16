# ChessPatterns

> [!NOTE]
> This project is inspired by Numberphile's recent chess-spiral videos:
> [Red & Black Knights](https://www.numberphile.com/videos/red-black-knights) on the main channel and
> the extra [Amazing Chessboard Patterns](https://youtu.be/VgmDuBCayPw) video on Numberphile2.

ChessPatterns generates PNG images from chess-piece placement rules on a square spiral board. Each cell is visited in spiral order, and pieces are placed when the target cell is empty and not seen by any other piece type.

## Build

```sh
make
```

This builds the `generator` executable.

## Usage

```sh
./generator -setup setup/KK.txt -width 255 -out out/KK.png
```

Options:

```text
-help              Print help
-width <int>       Board width, default 255
-setup <str>       Setup file to load
-move-dir <str>    Directory containing move files, default ./setup/moves/
-out <str>         Output PNG path, or auto, default auto
```

Example setups are in `setup/`, and generated images are written to `out/`.

## Rules

The board is indexed by a square spiral centered in the image. The program cycles through the pieces listed in the setup file. Each piece keeps its own current position in the spiral scan.

For a piece's turn:

1. Scan forward through the spiral.
2. Skip occupied cells.
3. Skip cells seen by any other piece type.
4. Place the piece on the first legal cell.
5. Mark every cell reachable by that piece's move offsets as seen by that piece.

Empty cells render white. Occupied cells use the RGB color from the setup file.

## File Formats

Move files live in `setup/moves/`. Each line is one relative move:

```text
dx dy
```

Example, `setup/moves/KNIGHT.txt`:

```text
 1  2
 2  1
 2 -1
 1 -2
-1 -2
-2  1
-2 -1
-1  2
```

Setup files live in `setup/`. Each line names a move file, without `.txt`, followed by an RGB color:

```text
MOVE_NAME r g b
```

Example, `setup/KK.txt`:

```text
KNIGHT 0 0 0
KNIGHT 255 0 0
```

That creates two piece types with the same knight move set: one black and one red.

## Third-Party Code

- [`thirdparties/flag.h`](thirdparties/flag.h) comes from [`tsoding/flag.h`](https://github.com/tsoding/flag.h), a C command-line flag parser.
- [`thirdparties/stb_image_write.h`](thirdparties/stb_image_write.h) comes from [`nothings/stb`](https://github.com/nothings/stb) and is used to write PNG images.
