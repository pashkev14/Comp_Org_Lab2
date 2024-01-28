#include <conio.h>
#include <dos.h>

int x1 = 15,
y1 = 10,
x2 = 65,
y2 = 20,
S = 1,
T = 1400,
num_colors = 16,
i,
j;

char* colors[] = {
"BLACK", "BLUE", "GREEN", "CYAN", "RED", "MAGENTA", "BROWN", "LIGHTGRAY",
"DARKGRAY", "LIGHTBLUE", "LIGHTGREEN", "LIGHTCYAN", "LIGHTRED", "LIGHTMAGENTA", "YELLOW", "WHITE"
};

void scroll(int direction, char l_row, char l_col, char r_row, char r_col, char attr) {
    union REGS r;
    if (direction) {
        r.h.al = S + 1; r.h.ah = direction;
    }
    else {
        r.h.al = 0; r.h.ah = 6;
    }
    r.h.ch = l_row; r.h.cl = l_col; r.h.dh = r_row;
    r.h.dl = r_col; r.h.bh = (attr * num_colors);
    int86(0x10, &r, &r);
}

int main() {
    clrscr();

    window(x1, y1, x2, y2);

    for (i = 0; i < num_colors; i++) {
        for (j = 0; j < num_colors; j++) {
            gotoxy(1, 1);

            textbackground(i);
            textcolor(j);
            cprintf("BG: %02x, FG: %s", i, colors[j]);

            delay(T);
            scroll(7, y1 - 1, x1 - 1, y2 - 1, x2 - 1, i);
        }
    }

    clrscr();

    return 0;
}