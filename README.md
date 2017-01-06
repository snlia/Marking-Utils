A small util to mark points in image.

## Install

    $mkdir build
    $cd build
    $cmake ../src
    $make


## Useage

    $./main your_jpg_name

Use `hjkl` to move the cursor, `i` to mark the points, `u` to redraw the last marking, `q` to save & return

your image should be puts in `data` directory, while the result will be placed in `data/your_jpg_name.dat`
