<<<<<<< HEAD
//threads rotate 

/**************************
 * spiral orientation thread compute 
 *
 **************************/
#include "main_includes.h"
#include <stdbool.h>

DWORD WINAPI myThreadFunction(LPVOID arguments) {
    struct mainspiralset *spiral = (struct mainspiralset*)arguments[0];
    struct Spiral *objects = (struct Spiral*)arguments[1];
    struct Spiral *input = (struct Spiral*)arguments[2];
    
	return 0;
}

int change_orientation_spiral(struct mainspiralset* spiral, struct Spiral *object, int allignmentx, int allignmenty, int allighnmentz){
	//ok first we make loop with thread wait and compute the math
	//then make two threads back and fround to shorten time by two
	struct Spiral inputobj;
	inputobj.a = 0
	inputobj.b
	inputobj.i
	inputobj.j
	inputobj.t
	inputobj.l
	inputobj.p;
	
	HANDLE threads[2];   // handles for both threads
    void* args[2] = {spiral, objects, }; // thread IDs or arguments

    // Create two threads
    for (int i = 0; i < 2; i++) {
        threads[i] = CreateThread(
            NULL,           // security
            0,              // stack size
            threadFunction, // function to run
            &args[i],       // pointer to unique argument
            0,              // default flags
            NULL);          // thread ID (optional)

        if (threads[i] == NULL) {
            printf("Failed to create thread %d\n", i + 1);
            return 1;
        }
    }

    // Wait for both threads to finish
    WaitForMultipleObjects(2, threads, TRUE, INFINITE);

    // Clean up
    CloseHandle(threads[0]);
    CloseHandle(threads[1]);
	
	
}

=======
//threads rotate 

/**************************
 * spiral orientation thread compute 
 *
 **************************/
#include "main_includes.h"
#include <stdbool.h>

DWORD WINAPI myThreadFunction(LPVOID arguments) {
    struct mainspiralset *spiral = (struct mainspiralset*)arguments[0];
    struct Spiral *objects = (struct Spiral*)arguments[1];
    struct Spiral *input = (struct Spiral*)arguments[2];
    
	return 0;
}

int change_orientation_spiral(struct mainspiralset* spiral, struct Spiral *object, int allignmentx, int allignmenty, int allighnmentz){
	//ok first we make loop with thread wait and compute the math
	//then make two threads back and fround to shorten time by two
	struct Spiral inputobj;
	inputobj.a = 0
	inputobj.b
	inputobj.i
	inputobj.j
	inputobj.t
	inputobj.l
	inputobj.p;
	
	HANDLE threads[2];   // handles for both threads
    void* args[2] = {spiral, objects, }; // thread IDs or arguments

    // Create two threads
    for (int i = 0; i < 2; i++) {
        threads[i] = CreateThread(
            NULL,           // security
            0,              // stack size
            threadFunction, // function to run
            &args[i],       // pointer to unique argument
            0,              // default flags
            NULL);          // thread ID (optional)

        if (threads[i] == NULL) {
            printf("Failed to create thread %d\n", i + 1);
            return 1;
        }
    }

    // Wait for both threads to finish
    WaitForMultipleObjects(2, threads, TRUE, INFINITE);

    // Clean up
    CloseHandle(threads[0]);
    CloseHandle(threads[1]);
	
	
}

>>>>>>> c3fdc3af2b19719bbc8db391f9a43f7964aaaee5
