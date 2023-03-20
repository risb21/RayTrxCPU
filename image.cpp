#include <iostream>
#include <vector>
#include <thread>

using namespace std;

/* Function for each thread to execute, sets colour of each pixel */
void thread_fn(unsigned char *arr, int x, int y, int mx, int my) {
    arr[(y*mx + x)*3 + 0] = char(float(x) / mx * 255.99);
    arr[(y*mx + x)*3 + 1] = char(float(y) / my * 255.99);
    arr[(y*mx + x)*3 + 2] = char(float(0.2 * 255.99));
}

int main() {

    // Thread block dimensions
    int tx = 4;
    int ty = 4;

    // Image dimensions
    int dimx = 1200;
    int dimy = 600;

    cout << "Making a " << dimx << "x" << dimy << " image\n";

    // Allocating the pixel array on the heap
    unsigned char *farr = (unsigned char *) malloc(dimy * dimx * 3 * sizeof(unsigned char));

    // Failed to allocate pixel array
    if (!farr) {
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
                    tarr[thry][thrx] = thread(thread_fn, farr, bx*tx + thrx, by*ty + thry, dimx, dimy);
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

    int r, g, b;
    
    for (int i = 0; i < dimy; i++) {
        for (int j = 0; j < dimx; j++) {
            r = int(farr[(i*dimx + j)*3 + 0]);
            g = int(farr[(i*dimx + j)*3 + 1]);
            b = int(farr[(i*dimx + j)*3 + 2]);
            fprintf(ppm, "%d %d %d\n", r, g, b);
        }
    }
    fclose(ppm);
    cout << "Written into " << writefile << endl;
    
}