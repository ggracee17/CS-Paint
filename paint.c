// CS Paint
// paint.c
//
// This program was written by Xingyu Shen (z5211156) on 18/10/2019.
//
// Version 1.0.0 (2019-10-08): Assignment released.
// Version 1.0.1 (2019-10-18): Scan in command & draw a line.
// Version 1.0.2 (2019-10-19): Keep scanning inputs. Consider directions. Draw line function.
// Version 1.0.3 (2019-10-24): Draw vertical & horizontal lines. Check input. Fill square.
// Version 2.0.1 (2019-10-25): Draw diagonal lines. Negative Distances.
// Change shade. Fixed style. Copy Paste.
// Version 2.0.2 (2019-10-26): Ellipse Drawing.
// Overlapping copy paste. Modified style & overlapping paste. 
// Draw hollow ellipse.

#include <stdio.h>
#include <math.h>

// The dimensions of the canvas
#define N_ROWS 20
#define N_COLS 36

// Shades
#define BLACK 0
#define WHITE 4

// Commands
#define LINE 1
#define SQUARE 2
#define SHADE 3
#define COPYPASTE 4
#define ELLIPSE 0
#define HOLLOW 0

// Directions
#define UP 0
#define RIGHT 90
#define DOWN 180
#define LEFT 270
#define BOTTOMLEFT 45
#define TOPLEFT 135
#define TOPRIGHT 225
#define BOTTOMRIGHT 315

#define HALFCIRCLE 180

// True and false for checking inputs
#define TRUE 1
#define FALSE 0

// Display the canvas.
void displayCanvas(int canvas[N_ROWS][N_COLS]);

// Clear the canvas by setting every pixel to be white.
void clearCanvas(int canvas[N_ROWS][N_COLS]);

int checkInput(
    int start_row, int start_col, 
    int end_row, int end_col
);

// Change to the opposite direction 
// if length is negative.
int swapDirection(int direction);

int changeShade(int shade, int new_shade);

// Functions for drawing lines
void drawVertical(
    int top_row, int col, 
    int length, 
    int shade, 
    int canvas[N_ROWS][N_COLS]
);

void drawHorizontal(
    int row, int left_col, 
    int length, 
    int shade, 
    int canvas[N_ROWS][N_COLS]
);

void drawDiagonalRight(
    int top_row, int left_col, 
    int length, 
    int shade, 
    int canvas[N_ROWS][N_COLS]
);

void drawDiagonalLeft(
    int top_row, int right_col, 
    int length, 
    int shade, 
    int canvas[N_ROWS][N_COLS]
);

void drawLine(
    int start_row, int start_col, 
    int length, 
    int direction, 
    int shade, 
    int canvas[N_ROWS][N_COLS]
);


// Functions for drawing squares
void drawSquare(
    int start_row, int start_col, 
    int length, 
    int shade, 
    int canvas[N_ROWS][N_COLS]
);

void fillSquare(
    int start_row, int start_col, 
    int length, 
    int direction, 
    int shade, 
    int canvas[N_ROWS][N_COLS]
);


// Functions for copy and paste
void copyVertical(
    int start_row, int start_col,
    int target_row, int target_col,
    int length,
    int canvas[N_ROWS][N_COLS],
    int clipboard[N_ROWS][N_COLS]
);

void copyHorizontal(
    int start_row, int start_col,
    int target_row, int target_col,
    int length,
    int canvas[N_ROWS][N_COLS],
    int clipboard[N_ROWS][N_COLS]
);

void copyLine(
    int start_row, int start_col, 
    int target_row, int target_col,
    int length, int direction, 
    int canvas[N_ROWS][N_COLS],
    int clipboard[N_ROWS][N_COLS]
);

void copySquare(
    int top_start_row, int start_col,
    int target_row, int target_col,
    int length,
    int canvas[N_ROWS][N_COLS],
    int clipboard[N_ROWS][N_COLS]
);

void copyPaste(
    int start_row, int start_col,
    int target_row, int target_col,
    int length,
    int direction,
    int canvas[N_ROWS][N_COLS],
    int clipboard[N_ROWS][N_COLS]
);


// Function for drawing ellipse
double distance(
    int row1, int col1, 
    int row2, int col2
);

void drawEllipse(
    int focus_1_row, int focus_1_col,
    int focus_2_row, int focus_2_col,
    double focal_length, 
    int shade,
    int canvas[N_ROWS][N_COLS]
);

int checkEllipse(
    int row, int col,
    int focus_1_row, int focus_1_col,
    int focus_2_row, int focus_2_col,
    double focal_length
);

void drawEdge(
    int row, int col,
    int focus_1_row, int focus_1_col,
    int focus_2_row, int focus_2_col,
    double focal_length, 
    int shade,
    int canvas[N_ROWS][N_COLS]
);

void drawHollowEllipse(
    int focus_1_row, int focus_1_col,
    int focus_2_row, int focus_2_col,
    double focal_length, 
    int shade,
    int canvas[N_ROWS][N_COLS]
);



int main(void) {
    int canvas[N_ROWS][N_COLS];
    int clipboard[N_ROWS][N_COLS];

    clearCanvas(canvas);
    clearCanvas(clipboard);

    int command; 
    int start_row, start_col; 
    int length, direction; 
    int new_shade;
    int target_row, target_col;
    int focus_1_row, focus_1_col;
    int focus_2_row, focus_2_col;
    double focal_length;
    int fill;
    int shade = BLACK;
    
    while (scanf("%d", &command) == 1) {
        if (command == SHADE) {
            scanf("%d", &new_shade);
            shade = changeShade(shade, new_shade);
        } else if (command == LINE) {
            scanf(
                "%d %d %d %d", 
                &start_row, &start_col, 
                &length, 
                &direction
            );
            drawLine(
                start_row, start_col, 
                length, 
                direction, 
                shade, 
                canvas
            ); 
        } else if (command == SQUARE) {
            scanf(
                "%d %d %d %d", 
                &start_row, &start_col, 
                &length, 
                &direction
            );
            fillSquare(
                start_row, start_col, 
                length, 
                direction, 
                shade, 
                canvas
            );
        } else if (command == COPYPASTE) {
            scanf(
                "%d %d %d %d %d %d", 
                &start_row, &start_col, 
                &length, 
                &direction,
                &target_row, &target_col
            );
            copyPaste(
                start_row, start_col,                
                target_row, target_col,
                length, 
                direction,
                canvas, clipboard
            );
        } else if (command == ELLIPSE) {
            scanf(
                "%d %d %d %d %lf %d", 
                &focus_1_row, &focus_1_col,
                &focus_2_row, &focus_2_col,
                &focal_length,
                &fill
            );
            if (fill == HOLLOW) {
                drawHollowEllipse(
                    focus_1_row, focus_1_col,
                    focus_2_row, focus_2_col,
                    focal_length,
                    shade,
                    canvas
                );
            } else {
                drawEllipse(
                    focus_1_row, focus_1_col,
                    focus_2_row, focus_2_col,
                    focal_length,
                    shade,
                    canvas
                );
            }            
        }
    }
                    
    displayCanvas(canvas);
            
    return 0;
}



// Displays the canvas, by printing the integer value stored
// in each element of the 2-dimensional canvas array.
void displayCanvas(int canvas[N_ROWS][N_COLS]) {
    int row = 0;
    while (row < N_ROWS) {
        int col = 0;
        while (col < N_COLS) {
            printf("%d ", canvas[row][col]);
            col++;
        }
        row++;
        printf("\n");
    }
}


// Sets the entire canvas to be blank, 
// by setting each element in the
// 2-dimensional canvas array to be WHITE.
void clearCanvas(int canvas[N_ROWS][N_COLS]) {
    int row = 0;
    while (row < N_ROWS) {
        int col = 0;
        while (col < N_COLS) {
            canvas[row][col] = WHITE;
            col++;
        }
        row++;
    }
}


// Check if inputs are within the boundray of canvas, 
// return TRUE if within boundary and FALSE if not.
int checkInput(
    int start_row, int start_col, 
    int end_row, int end_col
) {
    if (
        start_row >= 0 && start_row < N_ROWS &&
        start_col >= 0 && start_col < N_COLS &&
        end_row >= 0 && end_row < N_ROWS &&
        end_col >= 0 && end_col < N_COLS                                  
    ) {
        return TRUE;
    } else {
        return FALSE;
    }          
}


// Check whether length is in the negative direction,
// if so change to the opposite direction.
int swapDirection(int direction) {
    int new_direction;
    if (direction % 360 < HALFCIRCLE) {
        new_direction = direction % 360 + HALFCIRCLE;
    } else {
        new_direction = direction % 360 - HALFCIRCLE;
    }   
    return new_direction;
}


// If input is valid, add or decrease shade accordingly;
// otherwise shade remain unchanged.
int changeShade(int shade, int new_shade) {
    if (
        shade + new_shade >= BLACK && 
        shade + new_shade <= WHITE
    ) {
        shade = shade + new_shade;
    }
    return shade;
}


// Draw vertical lines in downwards direction,
// given the starting pixel and length. 
// Check if inputs are valid before drawing.
void drawVertical(
    int top_row, int col, 
    int length, int shade, 
    int canvas[N_ROWS][N_COLS]
) {    
    int shift = length - 1;
    int bottom_row = top_row + shift;
    
    int check_input = checkInput(
        top_row, col, 
        bottom_row, col
    );
    if (check_input == TRUE) {
        int row = top_row;
        while (row < top_row + length) {        
            canvas[row][col] = shade;
            row++;
        }
    }    
}


// Draw horizontal lines from left to right, 
// check if inputs are valid.
void drawHorizontal(
    int row, int left_col, 
    int length, int shade, 
    int canvas[N_ROWS][N_COLS]
) {
    int shift = length - 1;
    int right_col = left_col + shift;
    
    int check_input = checkInput(
        row, left_col, 
        row, right_col
    );
    if (check_input == TRUE) {
        int col = left_col;
        while (col < left_col + length) {
            canvas[row][col] = shade;
            col++;
        }
    }    
}


// Draw diagonal lines from top left to bottom right, 
// check if inputs are valid.
void drawDiagonalRight(
    int top_row, int left_col, 
    int length, int shade, 
    int canvas[N_ROWS][N_COLS]
) {
    int shift = length - 1;
    int bottom_row = top_row + shift;
    int right_col = left_col + shift;
    
    int check_input = checkInput(
        top_row, left_col, bottom_row, right_col
    );
    if (check_input == TRUE) {
        int row = top_row;
        int col = left_col;
        while (row < top_row + length) {
            if (col < left_col + length) {
                canvas[row][col] = shade;
                col++;
            }
            row++;
        }
    }    
}


// Draw diagonal lines from top right to bottom left,
// check if inputs are valid.
void drawDiagonalLeft(
    int top_row, int right_col, 
    int length, int shade, 
    int canvas[N_ROWS][N_COLS]
) {
    int shift = length - 1;
    int bottom_row = top_row + shift;
    int left_col = right_col - shift;
    
    int check_input = checkInput(
        top_row, left_col, bottom_row, right_col
    );
    if (check_input == TRUE) {
        int row = top_row;
        int col = right_col;
        while (row < top_row + length) {
            if (col > right_col - length) {
                canvas[row][col] = shade;
                col--;
            }
            row++;
        }
    }    
}


// Draws straight lines in the directions of 
// up, down, left or right,
// or draw diagonal lines on a 45 degree angle.
void drawLine(
    int start_row, int start_col, 
    int length, int direction, 
    int shade, 
    int canvas[N_ROWS][N_COLS]
) {
    if (length < 0) {
        direction = swapDirection(direction);
        length = -length;
    }    
    
    int shift = length - 1;
    if (direction % 360 == UP) {
        int top_row = start_row - shift;
        drawVertical(
            top_row, start_col, 
            length, shade, 
            canvas
        );                
    } else if (direction % 360 == RIGHT) {
        drawHorizontal(
            start_row, start_col, 
            length, shade, 
            canvas
        );
    } else if (direction % 360 == DOWN) {
        drawVertical(
            start_row, start_col, 
            length, shade, 
            canvas
        );
    } else if (direction % 360 == LEFT) {
        int left_col = start_col - shift;
        drawHorizontal(
            start_row, left_col, 
            length, shade, 
            canvas
        );  

    } else if (direction % 360 == BOTTOMLEFT) {
        // draw diagonal line starting at bottom left
        int top_row = start_row - shift;
        int right_col = start_col + shift; 
        drawDiagonalLeft(
            top_row, right_col, 
            length, shade, 
            canvas
        );
    } else if (direction % 360 == TOPLEFT) {
        drawDiagonalRight(
            start_row, start_col, 
            length, shade, 
            canvas
        );
    } else if (direction % 360 == TOPRIGHT) {
        drawDiagonalLeft(
            start_row, start_col, 
            length, shade, 
            canvas
        );
    } else if (direction % 360 == BOTTOMRIGHT) {
        int top_row = start_row - shift;
        int left_col = start_col - shift;
        drawDiagonalRight(
            top_row, left_col, 
            length, shade, 
            canvas
        );
    }
}


// Draw squares that start at top left and end at bottom right,
// given starting pixel and length.
// Check if the square is inside canvas before drawing.
void drawSquare(
    int top_row, int left_col, 
    int length, int shade, 
    int canvas[N_ROWS][N_COLS]
) {
    int shift = length -1;
    int bottom_row = top_row + shift;
    int right_col = left_col + shift;
    
    int check_input = checkInput(
        top_row, left_col, 
        bottom_row, right_col
    );
    if (check_input == TRUE) {
        int row = top_row;
        while (row < top_row + length) {
            drawHorizontal(
                row, left_col, 
                length, shade, 
                canvas
            );
            row++;
        }        
    }    
}


// Fill square or draw line according to given direction that
// determines a starting point. 
void fillSquare(
    int start_row, int start_col, 
    int length, 
    int direction, 
    int shade, 
    int canvas[N_ROWS][N_COLS]
) {

    if (length < 0) {
        direction = swapDirection(direction);
        length = -length;
    }
    
    int shift = length - 1;  
    if (
        direction % 360 == UP || 
        direction % 360 == RIGHT || 
        direction % 360 == DOWN || 
        direction % 360 == LEFT
    ) {
        drawLine(
            start_row, start_col, 
            length, 
            direction, 
            shade, 
            canvas
        );

    } else if (direction % 360 == BOTTOMLEFT) {
        // draw square with starting pixel at bottom left
        int top_row = start_row - shift; 
        drawSquare(
            top_row, start_col, 
            length, shade, 
            canvas
        );
    } else if (direction % 360 == TOPLEFT) {
        drawSquare(
            start_row, start_col, 
            length, shade, 
            canvas
        );
    } else if (direction % 360 == TOPRIGHT) {
        int left_col = start_col - shift;
        drawSquare(
            start_row, left_col, 
            length, shade, 
            canvas
        );
    } else if (direction % 360 == BOTTOMRIGHT) {
        int top_row = start_row - shift;
        int left_col = start_col - shift;
        drawSquare(
            top_row, left_col, 
            length, shade, 
            canvas
        );
    } 
}


// Copy a vertical line and paste it onto the clipboard,
// check if start and target positions are valid.
void copyVertical(
    int start_row, int start_col,
    int target_row, int target_col,
    int length,
    int canvas[N_ROWS][N_COLS],
    int clipboard[N_ROWS][N_COLS]
) {
    int shift = length - 1;   
    int bottom_start_row = start_row + shift;
    int bottom_target_row = target_row + shift;
    
    int check_start = checkInput(
        start_row, start_col, 
        bottom_start_row, start_col
    );    
    int check_target = checkInput(
        target_row, target_col, 
        bottom_target_row, target_col
    );
    
    if (check_start == TRUE && check_target == TRUE) {
        // i and j are current columns of target and start line
        int i = target_row;
        int j = start_row;
        while (i < target_row + length) {
            clipboard[i][target_col] = canvas[j][start_col];
            i++;
            j++;
        }
    }
}


// Copy a horizontal line and paste it onto the clipboard,
// check if start and target positions are valid.
void copyHorizontal(
    int start_row, int start_col,
    int target_row, int target_col,
    int length,
    int canvas[N_ROWS][N_COLS],
    int clipboard[N_ROWS][N_COLS]
) {
    int shift = length - 1;
    int right_start_col = start_col + shift;    
    int right_target_col = target_col + shift;
    
    int check_start = checkInput(
        start_row, start_col, 
        start_row, right_start_col
    );
    int check_target = checkInput(
        target_row, target_col, 
        target_row, right_target_col
    );
    
    if (check_start == TRUE && check_target == TRUE) {
        // i and j are current columns of target and start line
        int i = target_col;
        int j = start_col;
        while (i < target_col + length) {
            clipboard[target_row][i] = canvas[start_row][j];
            i++;
            j++;
        }
    }
}


// Copy a line with directions up, right, down or left
void copyLine(
    int start_row, int start_col, 
    int target_row, int target_col,
    int length, int direction, 
    int canvas[N_ROWS][N_COLS],
    int clipboard[N_ROWS][N_COLS]
) {
    if (length < 0) {
        direction = swapDirection(direction);
        length = -length;
    }
    
    int shift = length - 1;
    if (direction % 360 == UP) {
        int top_start_row = start_row - shift;
        int top_target_row = target_row - shift;
        copyVertical(
            top_start_row, start_col, 
            top_target_row, target_col,
            length,
            canvas, clipboard
        );        
    } else if (direction % 360 == RIGHT) {
        copyHorizontal(
            start_row, start_col, 
            target_row, target_col,
            length,
            canvas, clipboard
        );
    } else if (direction % 360 == DOWN) {
        copyVertical(
            start_row, start_col, 
            target_row, target_col,
            length,
            canvas, clipboard
        );
    } else if (direction % 360 == LEFT) {
        int left_start_col = start_col - shift;
        int left_target_col = target_col - shift;
        copyHorizontal(
            start_row, left_start_col, 
            target_row, left_target_col,
            length,
            canvas, clipboard
        );
    }
}


// Copy a square that starts at top left and end at bottom right,
// check if start and target positions are valid before copying.
void copySquare(
    int top_start_row, int start_col,
    int target_row, int target_col,
    int length,
    int canvas[N_ROWS][N_COLS],
    int clipboard[N_ROWS][N_COLS]
) {
    int shift = length - 1;        
    
    int bottom_start_row = top_start_row + shift;
    int right_start_col = start_col + shift;    
    int bottom_target_row = target_row + shift;
    int right_target_col = target_col + shift;
        
    int check_start = checkInput(
        top_start_row, start_col, 
        bottom_start_row, right_start_col
    );
    int check_target = checkInput(
        target_row, target_col, 
        bottom_target_row, right_target_col
    );
    
    if (check_start == TRUE && check_target == TRUE) {
        int start_row = top_start_row;
        while (start_row < top_start_row + length) {
            copyHorizontal(
                start_row, start_col, 
                target_row, target_col,
                length,
                canvas, clipboard
            );            
            start_row++;
            target_row++;
        }
    }
}

// Copy square or line from canvas to clipboard
// in the same start position, then paste 
// from clipboard to canvas at target position. 
void copyPaste(
    int start_row, int start_col,
    int target_row, int target_col,
    int length,
    int direction,
    int canvas[N_ROWS][N_COLS],
    int clipboard[N_ROWS][N_COLS]
) {
    if (length < 0) {
        direction = swapDirection(direction);
        length = -length;
    }
    
    int shift = length - 1;
    if (
        direction % 360 == UP || 
        direction % 360 == RIGHT || 
        direction % 360 == DOWN || 
        direction % 360 == LEFT
    ) {        
        copyLine(
            start_row, start_col, 
            start_row, start_col,
            length, 
            direction, 
            canvas, clipboard           
        );                                              
        copyLine(
            start_row, start_col, 
            target_row, target_col,
            length, 
            direction, 
            clipboard, canvas           
        );                
    } else if (direction % 360 == BOTTOMLEFT) {
        int top_start_row = start_row - shift;
        int top_target_row = target_row - shift;
        copySquare(
            top_start_row, start_col,
            top_start_row, start_col,
            length,
            canvas, clipboard
        );        
        copySquare(
            top_start_row, start_col,
            top_target_row, target_col,
            length,
            clipboard, canvas
        );
    } else if (direction % 360 == TOPLEFT) {
        copySquare(
            start_row, start_col,
            start_row, start_col,
            length,
            canvas, clipboard
        );               
        copySquare(
            start_row, start_col,
            target_row, target_col,
            length,
            clipboard, canvas
        );        
    } else if (direction % 360 == TOPRIGHT) {
        int left_start_col = start_col - shift;
        int left_target_col = target_col - shift;
        copySquare(
            start_row, left_start_col,
            start_row, left_start_col,
            length,
            canvas, clipboard
        );                               
        copySquare(
            start_row, left_start_col,
            target_row, left_target_col,
            length,
            clipboard, canvas
        );        
    } else if (direction % 360 == BOTTOMRIGHT) {
        int top_start_row = start_row - shift;
        int top_target_row = target_row - shift;
        int left_start_col = start_col - shift;
        int left_target_col = target_col - shift;                
        copySquare(
            top_start_row, left_start_col,
            top_start_row, left_start_col,
            length,
            canvas, clipboard
        );                                                             
        copySquare(
            top_start_row, left_start_col,
            top_target_row, left_target_col,
            length,
            clipboard, canvas
        );        
    }
}


// Calculate the distance between two points 
// (row1, col1) and (row2, col2).
double distance(int row1, int col1, int row2, int col2) {
    int row_dist = row2 - row1;
    int col_dist = col2 - col1;
    return sqrt((row_dist * row_dist) + (col_dist * col_dist));
}


// Draw ellipse given two focus pixels and a focal length.
// All pixels will be indluded when the sum of their distances to 
// two focus points is equal to or less than twice the given length.
void drawEllipse(
    int focus_1_row, int focus_1_col,
    int focus_2_row, int focus_2_col,
    double focal_length, 
    int shade,
    int canvas[N_ROWS][N_COLS]
) {
    double focus_1_distance, focus_2_distance;
    double sum_distance;
    
    int pixel_row = 0;    
    while (pixel_row < N_ROWS) {
        int pixel_col = 0;
        while (pixel_col < N_COLS) {
            focus_1_distance = distance(
                focus_1_row, focus_1_col, 
                pixel_row, pixel_col
            );
            
            focus_2_distance = distance(
                pixel_row, pixel_col,
                focus_2_row, focus_2_col
            );
            
            sum_distance = focus_1_distance + focus_2_distance;
            
            if (sum_distance <= 2 * focal_length) {
                canvas[pixel_row][pixel_col] = shade;
            }
            pixel_col++;           
        }
        pixel_row++;
    }               
}


// Check whether a pixel is within a given ellipse
int checkEllipse(
    int row, int col,
    int focus_1_row, int focus_1_col,
    int focus_2_row, int focus_2_col,
    double focal_length
) {
    double focus_1_distance, focus_2_distance;
    double sum_distance;
    
    focus_1_distance = distance(
        focus_1_row, focus_1_col, 
        row, col
    );    
    focus_2_distance = distance(
        row, col,
        focus_2_row, focus_2_col
    );    
    sum_distance = focus_1_distance + focus_2_distance;
    
    if (sum_distance <= 2 * focal_length) {
        return TRUE;
    } else {
        return FALSE;
    }      
}


// Check all four directions around the pixel
// and only colour the pixel if more than one
// direction is not in the ellipse.
void drawEdge(
    int row, int col,
    int focus_1_row, int focus_1_col,
    int focus_2_row, int focus_2_col,
    double focal_length, 
    int shade,
    int canvas[N_ROWS][N_COLS]
) {
    if (checkEllipse(
            row, col,
            focus_1_row, focus_1_col,
            focus_2_row, focus_2_col,
            focal_length
        ) == TRUE
    ) {
        int counter = 0;
        // check directions up, right, down and left
        if (checkEllipse(
                row - 1, col,
                focus_1_row, focus_1_col,
                focus_2_row, focus_2_col,
                focal_length
            ) == FALSE
        ) {
            counter++;
        } else if (
            checkEllipse(
                row, col + 1,
                focus_1_row, focus_1_col,
                focus_2_row, focus_2_col,
                focal_length
            ) == FALSE
        ) {
            counter++;
        } else if (
            checkEllipse(
                row + 1, col,
                focus_1_row, focus_1_col,
                focus_2_row, focus_2_col,
                focal_length
            ) == FALSE
        ) {
            counter++;
        } else if (
            checkEllipse(
                row, col - 1,
                focus_1_row, focus_1_col,
                focus_2_row, focus_2_col,
                focal_length
            ) == FALSE
        ) {
            counter++;
        }

        if (counter > 0) {
            canvas[row][col] = shade;
        }
    }
}           


// Draw hollow ellipses with only the edges.
// Check all pixels in the canvas to determine 
// whether an edge should be drawn.
void drawHollowEllipse(
    int focus_1_row, int focus_1_col,
    int focus_2_row, int focus_2_col,
    double focal_length, 
    int shade,
    int canvas[N_ROWS][N_COLS]
) {
    int row = 0;    
    while (row < N_ROWS) {
        int col = 0;
        while (col < N_COLS) {
            drawEdge(
                row, col,
                focus_1_row, focus_1_col,
                focus_2_row, focus_2_col,
                focal_length,
                shade,
                canvas
            );
            col++;           
        }
        row++;
    }
}
