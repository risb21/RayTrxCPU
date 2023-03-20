#include <iostream>
#include <vector>
#include <thread>
#include "vec3.h"
#include "colour.h"

using namespace std;

/* Function for each thread to execute, sets colour of each pixel */
void thread_fn(colour *arr, int x, int y, int mx, int my) {
    arr[y*mx + x] = colour( float(x) / mx, float(y) / my, 0.2);
}

int main() {

    // Thread block dimensions
    int tx = 4;
    int ty = 4;

    // Image dimensions
    int dimx = 512;
    int dimy = 512;

    cout << "Making a " << dimx << "x" << dimy << " image\n";

    // Allocating the pixel array on the heap
    colour *parr = (colour *) malloc(dimy * dimx * sizeof(colour));

    // Failed to allocate pixel array
    if (!parr) {
        cout << stderr << ": Out of memory!\n";
        exit(1);
    }

    // thread block which will set colour of
    // ty*tx pixels at a time
    thread tarr[ty][tx];

    // Thread blocks iteration
    for (int by = 0; by < dimy/ty; by++) {
        for (int bx = 0; bx < dimx/tx; bx++) {
            // Threads iteration
            for (int thry = 0; thry < ty; thry++) {
                for (int thrx = 0; thrx < tx; thrx++) {
                    tarr[thry][thrx] = thread(thread_fn, parr, bx*tx + thrx, by*ty + thry, dimx, dimy);
                    tarr[thry][thrx].join();
                }
            }
        }
    }

    cout << "Processing done, copying to file\n";

    /* Writing output to a .ppm file */
    FILE* ppm;
    char writefile[] = "result4.ppm";
    ppm = fopen(writefile, "w");
    fprintf(ppm, "P3\n%d %d\n255\n", dimx, dimy);
    
    for (int i = 0; i < dimy; i++) {
        for (int j = 0; j < dimx; j++) {
            write_colour(ppm, parr[i*dimx + j]);
        }
    }
    fclose(ppm);
    cout << "Written into " << writefile << endl;
    
}