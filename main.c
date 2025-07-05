/**************************
 * Includes
 *
 **************************/

#include "main_includes.h"
/**************************
 * Function Declarations
 *
 **************************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
WPARAM wParam, LPARAM lParam);
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC);

void setOrthoProjection(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double aspectRatio = (double)width / height;

    if (aspectRatio >= 1.0) {
        glOrtho(-aspectRatio, aspectRatio, -1.0, 1.0, -1.0, 1.0);
    } else {
        glOrtho(-1.0, 1.0, -1.0 / aspectRatio, 1.0 / aspectRatio, -1.0, 1.0);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int openGLplotSpiral(struct mainspiralset *main, 
int length, HDC hDC, 
int maxSize, double theta, double relativer){ // fin for now
	glViewport(0, 0, maxSize, maxSize);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    int i;
    double list[2];
    for(i = 0; i < length; i++) {
//		long double XS = (main->complexxs[i]+ maxSize/2);
//		long double YS = (main->complexys[i]+ maxSize/2);
//        long double norm_x = (2.000 * XS / maxSize) - 1.0000;
//        long double norm_y = (2.000 * YS / maxSize) - 1.0000;
        // Assuming maxSize is the full width/height of the OpenGL view in pixels
		// and the spiral coordinates are centered at (0, 0)
		//ShowPopup("pain", "pains");
		long double XS = main->complexxs[i];
		long double YS = main->complexys[i];

		// Proper normalization to [-1, 1] assuming coordinates go from -maxSize/2 to +maxSize/2
		long double norm_x = (XS / (maxSize / 2));
		long double norm_y = (YS / (maxSize / 2));
		
		// Clamp values to avoid rendering glitches
		if (norm_x < -1.0) norm_x = -1.0;
		if (norm_x > 1.0) norm_x = 1.0;
		if (norm_y < -1.0) norm_y = -1.0;
		if (norm_y > 1.0) norm_y = 1.0;

		if (norm_x < -1 || norm_x > 1 || norm_y < -1 || norm_y > 1) {
    		printf("WARNING: Vertex out of bounds at index %d: (%f, %f)\n", i, norm_x, norm_y);
    		ShowPopup("pain", "pains");
		}
		if (main->colourr[i] == NULL || main->colourg[i] == NULL || main->colourb[i] == NULL) {
		    glColor3f(0.0f, 0.0f, 0.0f);  // fail-safe black
		} else if (*(main->colourr[i]) == 0.0 && *(main->colourg[i]) == 0.0 && *(main->colourb[i]) == 0.0) {
		    glColor3f(0.0f, 0.0f, 0.0f);  // still black
		} else {
		    glColor3f(*(main->colourr[i]), *(main->colourg[i]), *(main->colourb[i]));
		}

        glVertex2f(norm_x, norm_y);
    }
    glEnd();
    SwapBuffers(hDC);
    return 0;
}

int objectTospiralCoordinates(struct object *ob1, struct mainspiralset *object, struct Spiral *objects){ //PLus animation computational struct as well
	//map it already
	//ok ok so we  need to convert a coordinates of a texture into a spiral and fill in in the gaps or something or we just create a spiral and fill stuff in 
	//create spiral thing with proper things
	int size = ob1->texture.width * ob1->texture.height;
	if(size < 1){
		ShowPopup("EMERGANCY", "insfombia error cause yes!");
	}
    int zeta=500;
    initMainspiralset(object, size, zeta);
    if(objects->definefirst){
    	objects->a = 0.1;
	    objects->b = 0.1; //ob1->texture.width / ob1->texture.height; 
	    objects->l = 0;
	    objects->t = 0; 
	}
	double ** axs = &object->Xs;
	double ** ays = &object->Ys;
	double ** acomplexx = &object->complexxs;
	double ** acomplexy = &object->complexys;
    render3dgraphicSPIRALComplexPlain(*axs, object->size, *ays, 0, 0, object->zeta, *acomplexx, *acomplexy, *objects);
    //here fill stuff in and tweek coordinates to the one that is generated in form loop
    int i;
    int pindex;
    //instead of find we use math to locate the nearest equivilant by getting stuff nah
    for(i=0; i<size -1 ; i++){
    	//ok we got it, make a dictionary from the coordinates and find the matching on without c++ headrs :<
    	//cords ob1->vectorisedmodel[i][0] -2 -3 
    	int ret =0;
    	ret = findclosetcoordinate(*acomplexx, *acomplexy, object->size*object->zeta, ob1->vectorisedmodel[i][0], ob1->vectorisedmodel[i][1], &pindex);
    	if(ret == -1){
    		ShowPopup(":< 14234 debug", "insfombia error cause yes!");
    		break;
		}else if(pindex >= (object->size)*object->zeta && pindex < 0){
			pindex=0;
			ShowPopup("pindex out of range", "insfombia error cause yes!");
		}
		
    	object->colourr[pindex] = &ob1->vectorisedmodel[i][3];  // Assign pointer to red
		object->colourg[pindex] = &ob1->vectorisedmodel[i][4];  // Assign pointer to green
		object->colourb[pindex] = &ob1->vectorisedmodel[i][5];  // Assign pointer to blue
		object->colourbb[pindex] = &ob1->vectorisedmodel[i][6]; // Assign pointer to another color component (e.g., alpha)

    	//Sleep(100);
    	//free(ob1->vectorisedmodel[i]);
    	
	}
	//free(ob1->vectorisedmodel);
	//ShowPopup(":< 14234 debug", "insfombia error cause yes!");
	object->zeta=zeta;
	object->size=size;
	return 0;
    //first using bool operator  than using a mask
}
int configuresingularobjects(struct totalassets *totalass, struct mainspiralset *main, bool firstload, struct totalspirals *allspirals, struct visibledomain *VDA){
	ShowPopup("could not load fl33oor asset rrr -2 :<", "insfombia error cause yes!");
	if(firstload){
		char totalobjectsloaded[1] = ""; //add more to the thing index
		int ret = customeobjectfloor(totalass);
		if(ret == 1){
			ShowPopup("could not load fl33oor asset :<", "insfombia error cause yes!");
			return 1;
		} // if not return zero
		else{
			//ShowPopup("could not load fl33oor asset :<", "insfombia error cause yes!");
			totalobjectsloaded[0] = 'F';
		}
		//+ other objects
		//ShowPopup("could not load floor asset :<", "insfombia error cause yes!");
		//render said objects
		if(totalobjectsloaded[0] == 'F'){
			allspirals->sfloors.definefirst = true;
			//compute vector smoosh factors based on position needed
			ShowPopup("could not load fl33oor asset rrr -1 :<", "insfombia error cause yes!");
			int ret2 = objectTospiralCoordinates(&totalass->floor, &allspirals->sfloor, &allspirals->sfloors);
			ShowPopup("could not load fl33oor asset rrr 0 :<", "insfombia error cause yes!");
			if(ret2 == 1 || ret2 == -1){
				exit(-1);
			}
			/*what do is shrimple as that 
			first we get all camera angles and positions cheack if our object is in view not load if is not
			then we cheack it physics and update the position even tho not nessory if it anchored then ignor that too
			then we uppend it to main based on ray traccing and other objects blocking it if any exceptions occrured previously we don't update it toom main
			if any objects that is blocking it and the object is transparrent we added it to main
			if physics don't change we don't compute physics
			*/
			//maybe make function, yes that is exactly what i shall do
			//getcorrdsTerrian(); //start herer 
		}else if(1!=1){
				//load other ++
				1+1;
		}
		ShowPopup("could not load fl33oor asset rrr 1 :<", "insfombia error cause yes!");
		getcorrdsTerrian(totalobjectsloaded,VDA, totalass, allspirals);
		ShowPopup("could not load fl33oor asset  rrr 2:<", "insfombia error cause yes!");
		allobjectsrender(VDA,main, allspirals);
		ShowPopup("could not load fl33oor asset rrr 3 start render:<", "insfombia error cause yes!");
		//compute camera
		
		
		//on the pollar matrix
		//overlay main
	}else{
		char totalobjectsloaded[1] = ""; //add more to the thing index
		bool hasnotloaded = false;
		if(totalass->floor.weight == 0){
			hasnotloaded=true;
			int ret = customeobjectfloor(totalass);
			if(ret == 1){
				ShowPopup("could not load fl33oor asset :<", "insfombia error cause yes!");
				return 1;
			} // if not return zero
			else{
				//ShowPopup("could not load fl33oor asset :<", "insfombia error cause yes!");
				totalobjectsloaded[0] = 'F';
			}
		}else{
			totalobjectsloaded[0] = 'F';
		}
		if(totalobjectsloaded[0] == 'F'){
			//ShowPopup("could not load fl33oor asset :<", "insfombia error cause yes!");
			//load floor
			if(hasnotloaded){
				allspirals->sfloors.definefirst = false;
				int ret2 = objectTospiralCoordinates(&totalass->floor, &allspirals->sfloor, &allspirals->sfloors);
				if(ret2 == 1 || ret2 == -1){
				exit(-1);
			}   }
			//do physics for it here and overlays here aswell 
		}
			//compute vector smoosh factors based on position needed
		else{
			1+1;
		}
		getcorrdsTerrian(totalobjectsloaded,VDA, totalass, allspirals);
		allobjectsrender(VDA,main, allspirals);
		//compute camera  
		//on the pollar matrix
		//overlay main
	}
	
	
	return 0;
}
void firstload(struct mainspiralset *main, struct Spiral *mains, int sizex, int sizey, struct totalassets *totalass, struct totalspirals *allspirals, struct visibledomain *VDA){
    int size=sizex+sizey;
    int zeta=500; //impliment a varible scalling for ultimate preformance
    initMainspiralset(main, size, zeta);
    mains->a = 1;
    mains->b = 1; //+ (size/sizey);
    mains->l = 0;//theta;
    mains->t = 0; //1*(size/sizey); 
    double ** axs = &main->Xs;
	double ** ays = &main->Ys;
	double ** acomplexx = &main->complexxs;
	double ** acomplexy = &main->complexys;
    render3dgraphicSPIRALComplexPlain(*axs, main->size, *ays, 0, 0, main->zeta, *acomplexx, *acomplexy, *mains);
	
	//load textures
	int ret = configuresingularobjects(totalass, main, true, allspirals, VDA);
	if(ret == 1){
		ShowPopup("die metale gru, for referance if you do see this your computer is not hacked the engine just could't render stuff correctly which means alot more bugs exists which i though i fixed'", "insfombia error cause yes!");
	}
	main->totalsize = main->size * main->zeta;
}
void objectrenderingEngine(int maxsize, HDC hDC, double theta, struct mainspiralset *main, struct Spiral *mains, struct totalassets *totalass, struct totalspirals *allspirals, struct visibledomain*VDA){
	/*stepps:
	s1 load assets and textures, load where stuff is well not really
	s2 load phyiscs and interactions
	s3 create a render
	s4 track and move thing player and thing related*/
	bool firstload = false; 
	/*find the closest value to the appropriate texture) */
	/* OpenGL animation code goes here8*/
	//recompute per frame
	//if statement statemenet update frames with delta time
	if(deltatime*1000 > 120){
		//skip process frames compute physics and camera changes with input 
		Sleep(10); //for now
	}else{
		//recompute the thing withoutphysics and render 
		int ret = configuresingularobjects(totalass, main, firstload, allspirals, VDA);
		if(ret == 1){
			ShowPopup("die metale gru, for referance if you do see this your computer is not hacked the engine just could't render stuff correctly which means alot more bugs exists which i though i fixed'", "insfombia error cause yes!");
		}
	}
    
	openGLplotSpiral(main, main->totalsize, hDC, maxsize, theta, 1);
    SwapBuffers(hDC);
}

/**************************
 * WinMain
 *
 **************************/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow) {
    WNDCLASS wc;
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;        
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    /* register window class */
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "SpiralEngine";
    RegisterClass(&wc);

    /* Get screen size */
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    /* create main window */
    int maxsize = 500;
    struct mainspiralset main;
    struct Spiral mains;
    struct totalassets totalass;
    struct totalspirals allspirals;
    struct visibledomain VDA;
    
    hWnd = CreateWindow("SpiralEngine", "OpenGL Sample", 
                        WS_OVERLAPPEDWINDOW | WS_MINIMIZEBOX | WS_VISIBLE,
                        (screenWidth - maxsize) / 2, (screenHeight - maxsize) / 2, screenWidth, screenHeight,
                        NULL, NULL, hInstance, NULL);
	/*hWnd = CreateWindow("SpiralEngine", "OpenGL Sample", 
                        WS_OVERLAPPEDWINDOW | WS_MINIMIZEBOX | WS_VISIBLE,
                        ( maxsize) / 2, ( maxsize) / 2, maxsize, maxsize,
                        NULL, NULL, hInstance, NULL);*/

    /* enable OpenGL for the window */
    EnableOpenGL(hWnd, &hDC, &hRC);

	loadvisibledomain(&VDA);
    //into gui function
    //set up game while in gui with loading screen
    firstload(&main, &mains, screenHeight-maxsize /2, screenWidth-maxsize /2, &totalass, &allspirals, &VDA);
    /* program main loop */
    while (!bQuit) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                bQuit = TRUE;
            } else {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        } else {
        	//update deltatime
        	playerkeys();
        	deltatime = clock() - deltatime;
//        	if(deltatime*1000 < 60 && deltatime*1000 != 60){
//        		//Sleep((60-deltatime*1000)/1000);
//			}                   no cap for now
        	//render
            objectrenderingEngine(maxsize, hDC, theta, &main, &mains, &totalass, &allspirals, &VDA);
            SwapBuffers(hDC);
            //mains.t = -theta;
            //mains.a = 1/(sin(theta)*10);
            //theta += 0.1f;
        }
    }

    /* shutdown OpenGL */
    DisableOpenGL(hWnd, hDC, hRC);
    DestroyWindow(hWnd);

    return msg.wParam;
}


/********************
 * Window Procedure
 *
 ********************/

#define CUSTOM_BUTTON_ID 1

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CREATE:
        CreateWindow("BUTTON", "Custom Fit", 
                     WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                     10, 10, 100, 30, 
                     hWnd, (HMENU)CUSTOM_BUTTON_ID, 
                     (HINSTANCE)GetWindowLongPtr(hWnd, GWLP_HINSTANCE), NULL);
        return 0;

    case WM_COMMAND:
        if (LOWORD(wParam) == CUSTOM_BUTTON_ID) {
            MessageBox(hWnd, "Custom Fit Button Clicked!", "Info", MB_OK);
        }
        return 0;

    case WM_CLOSE:
        PostQuitMessage(0);
        return 0;

    case WM_DESTROY:
        return 0;

    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE) {
            PostQuitMessage(0);
            return 0;
        }
        return 0;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}



/*******************
 * Enable OpenGL
 *
 *******************/

void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC (hWnd);

    /* set the pixel format for the DC */
    ZeroMemory (&pfd, sizeof (pfd));
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | 
    PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat (*hDC, &pfd);
    SetPixelFormat (*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext( *hDC );
    wglMakeCurrent( *hDC, *hRC );

}

//mapikng textures onto spirals is gonna be hell isn't it
/******************
 * Disable OpenGL
 *
 ******************/

void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}
