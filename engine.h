/**************************
 * Object rendering - textures
 *
 **************************/
#include "main_includes.h"
#include <stdbool.h>
#define GRAY_SCALEl 2
#define RGBl 3
#include <string.h>

void append(void **array, size_t *size, size_t *capacity, size_t element_size, void *value) {
    if (*size >= *capacity) {
        *capacity = (*capacity == 0) ? 4 : (*capacity * 2);
        void *new_array = realloc(*array, *capacity * element_size);
        if (!new_array) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        *array = new_array;
    }
    memcpy((char *)(*array) + (*size * element_size), value, element_size);
    (*size)++;
}
 

void ShowPopup(const char* message, const char* title) { MessageBox(NULL, message, title, MB_OK | MB_ICONINFORMATION); }
 /**************************
 * Function deltatime
 *
 **************************/
 
clock_t deltatime;



/**************************
 * Spiral interpriter
 *
 **************************/
/*a = a(x) = x*i
//b= b(x) = x*j
//j=coficent of spiral compression in x
//i=coficent of spiral compression in y
//0 or O1 = feta(x,l) = sin(x+l), O2 = feta(x,t) = cos(x+t) p=t
//g = g(x, l) = tan(0)*a
//d = partial derivative
//s = ihat s(x,y,l,t) = ib*g(x,l)/bx + j*bg(y,t)/by ? */
struct Spiral{
	double j;
	double i;
	double l;
	double p;
	double a;
	double t; 
	double b;
	char baseEQ[100];
	bool definefirst;
};
double AX(double x, struct Spiral i){return x*i.i;}
double BX(double x, struct Spiral j){return x*j.j;}
double* SpiralGenBASE(double a, double b, double l, double t, double x, double z, double w) {
    static double buffer[2];  // Static keeps the variable alive beyond function scope
    buffer[0] = tan(sin(x + l+ 1e-6)) * (a+ 1e-6)+z;
    buffer[1] = tan(cos(x + t+ 1e-6)) * (b+ 1e-6)+w;
    return buffer;
}
#define PI 3.141592653589793
int nthpolygen(double radius, double n, double** xpoints, double** ypoints){
	int i;
	double centerX = 0.0, centerY = 0.0;
    double rotation = 0.0;
	for(i=0; i<=n; i++){
		double angle = (2.0 * PI * i / n);
		*ypoints[i] = radius*sin(angle);
		*xpoints[i] = radius*cos(angle);
	}
}

char* spiralvaluetoformular(double *x, double *y){
	return "he"; //return string. 
}
double findValue(char*stringEquation, char specificCharacter, double *pointerToVar){
	int i; 
	for(i=0; i<=sizeof(stringEquation); i++){
		if(stringEquation[i] == specificCharacter && i!=sizeof(stringEquation)){
			if(stringEquation[i] == '('){
				int j=i;
				char bufferv[sizeof(stringEquation)];
				while(stringEquation[j] != ')'){
					bufferv[j] = stringEquation[j];
					j++;
				}
				int buffervi[sizeof(stringEquation)];
				int r=0;
				while(r<=sizeof(stringEquation)){
					if(bufferv[r] != '.'){
						buffervi[r] = (bufferv[r]);
						buffervi[r]=buffervi[r]-48;
					}
				}
				
			}
		}
	}
}

int reverseDigits(int num) {
    int isNegative = num < 0;
    num = abs(num);
    int rev_num = 0;
    while (num > 0) {
        rev_num = rev_num * 10 + num % 10;
        num = num / 10;
    }
    return isNegative ? -rev_num : rev_num;
}



void spiralomnidirectionalcompute(struct Spiral *object, int *xyzvectora, int *xyzvectorb, double scale){            //x y z 1, x y z 2
	double deltax = xyzvectorb[0] - xyzvectora[0];
	double deltay = xyzvectorb[1] - xyzvectora[1];
	double deltaz = xyzvectorb[2] - xyzvectora[2];
	
	deltax = scale*deltax;
	deltay = scale*deltay;
	deltaz = scale*deltaz;
	object->a = object->a+atan(deltaz/deltax);
	object->b = object->b+atan(deltaz/deltay);
	object->t = object->t+(deltaz/deltax);
	object->l = object->l+(deltaz/deltay);
}

/**************************
 * textures
 *
 **************************/
 //coulor pallets for textures
 #define GRAY_SCALEl 2
 #define RGBl 3
 

/**************************
 * Object rendering
 *
 **************************/

struct mainspiralset{
	int size;
	double *Xs;
    double *Ys;
    int zeta;
    int totalsize;
    double *complexxs;
    double *complexys;
    double **colourr;
    double **colourg;
    double **colourb;
    double **colourbb;
    //rgb
};

struct totalspirals{
	struct mainspiralset sfloor;
	struct Spiral sfloors;
};
void initMainspiralset(struct mainspiralset* obj, int size, int zeta) {
    obj->size = size;
    obj->zeta=zeta;
    obj->Xs = (double*)malloc(size * sizeof(double));
    obj->Ys = (double*)malloc(size * sizeof(double));
    
    obj->complexxs = (double*)malloc(zeta* size * sizeof(double));
    obj->complexys = (double*)malloc(zeta* size * sizeof(double));
    
    obj->colourr = (double**)malloc(zeta* size * sizeof(double));
    obj->colourg = (double**)malloc(zeta* size * sizeof(double));
    obj->colourb = (double**)malloc(zeta* size * sizeof(double));
    obj->colourbb = (double**)malloc(zeta* size * sizeof(double));
}

void copyMainspiralset(struct mainspiralset *dest, struct mainspiralset *src) {
    dest->size = src->size;
    dest->zeta = src->zeta;

    dest->Xs = (double*)malloc(src->size * sizeof(double));
    dest->Ys = (double*)malloc(src->size * sizeof(double));
    dest->complexxs = (double*)malloc(src->zeta * src->size * sizeof(double));
    dest->complexys = (double*)malloc(src->zeta * src->size * sizeof(double));
    dest->colourr = (double**)malloc(src->zeta * src->size * sizeof(double *));
    dest->colourg = (double**)malloc(src->zeta * src->size * sizeof(double*));
    dest->colourb = (double**)malloc(src->zeta * src->size * sizeof(double*));
    dest->colourbb = (double**)malloc(src->zeta * src->size * sizeof(double*));

    if (dest->Xs) memcpy(dest->Xs, src->Xs, src->size * sizeof(double));
    if (dest->Ys) memcpy(dest->Ys, src->Ys, src->size * sizeof(double));
    if (dest->complexxs) memcpy(dest->complexxs, src->complexxs, src->zeta * src->size * sizeof(double));
    if (dest->complexys) memcpy(dest->complexys, src->complexys, src->zeta * src->size * sizeof(double));
    if (dest->colourr) memcpy(dest->colourr, src->colourr, src->zeta * src->size * sizeof(double*));
    if (dest->colourg) memcpy(dest->colourg, src->colourg, src->zeta * src->size * sizeof(double*));
    if (dest->colourb) memcpy(dest->colourb, src->colourb, src->zeta * src->size * sizeof(double*));
    if (dest->colourbb) memcpy(dest->colourbb, src->colourbb, src->zeta * src->size * sizeof(double*));
}

void freeMainspiralset(struct mainspiralset *obj) {
    free(obj->Xs);
    free(obj->Ys);
    free(obj->complexxs);
    free(obj->complexys);
    int i;
    for (i = 0; i < obj->size; i++) {
	    free(obj->colourr[i]);
	    free(obj->colourg[i]);
	    free(obj->colourb[i]);
	    free(obj->colourbb[i]);
	}
	
	free(obj->colourr);
	free(obj->colourg);
	free(obj->colourb);
	free(obj->colourbb);

}

/*buffer[0] = tan(sin(x + l+ 1e-6)) * (a+ 1e-6)+z;
    buffer[1] = tan(cos(x + t+ 1e-6)) * (b+ 1e-6)+w; */ 
void basespiral(double* xs, int sizeofxs, double* ys, double orignx, double origny, struct Spiral s) {
    double a1 = s.a, b1 = s.b, l1 = s.l, t1 = s.t;
    double a2 = s.a, b2 = s.b, l2 = s.l, t2 = s.t;

    if (xs == NULL || ys == NULL) {
        printf("Error: Received unallocated memory for xs/ys.\n");
        return;
    }
	int i;
    for (i = 0; i < sizeofxs; i++) {
        double* spiralResult = SpiralGenBASE(i * a1, i * b1, l1, t1, i, orignx, origny);
        
        if (spiralResult == NULL) {
            printf("Error: SpiralGenBASE() returned NULL.\n");
            break;
        }

        xs[i] = spiralResult[0];  // Correctly storing values
        ys[i] = spiralResult[1];
    }
    
}


int render3dgraphicSPIRALComplexPlain(double* xs, int sizeofxs, double* ys,
                                      double orignx, double origny, int zeta, 
                                      double* complexx, double* complexy, struct Spiral s) {
    // Generates the base spiral, using preallocated memory
    basespiral(xs, sizeofxs, ys, orignx, origny, s);

    int sizeofmainlist = sizeofxs * zeta;

    if (complexx == NULL || complexy == NULL) {
        printf("Error: Received unallocated memory for complexx/complexy.\n");
        return -1;
    }
    // Buffer arrays no longer needed since we use the preallocated memory
    int i;
    for (i = 0; i < sizeofxs; i++) {
        basespiral(&complexx[i * zeta], zeta, &complexy[i * zeta], xs[i], ys[i], s);
    }

    return 0;
}
#define DBL_MAX 0.1
int findclosetcoordinate(double *inputx, double *inputy, int size, double findx, double findy, int *index) {
    if (size <= 0 || inputx == NULL || inputy == NULL || index == NULL) {
        return -1; // error: bad input
    }
    if (1==1){
    	double minDistance = DBL_MAX;
	    int indexOfSmallest = 0;
		int  i;
		//ShowPopup(":< 14234qq debug", "insfombia error cause yes!");
	    for (i = 0; i < size; i++) {
	        double dx = inputx[i] - findx;
	        double dy = inputy[i] - findy;
	        double dist = sqrt(dx * dx + dy * dy);
	
	        if (dist < minDistance) {
	            minDistance = dist;
	            indexOfSmallest = i;
	        }
	    }
		//ShowPopup(":< 14234qq debug", "insfombia error cause yes!");
	    *index = indexOfSmallest;
	}else{
		ShowPopup("exception triggered in find index", "insfombia error cause yes!");
		*index  = size;
	}
    return 0;
}
struct Textures{
	char * filepath; 
	int height; 
	int width;
	int COLOURPALLET;
	double **texture3dArray; //  = {hieght, {width: cords{}, rgb or grayscale colours{}}}
};
int BasespiralTextureEncoder(){

	return 0; //return spiral that follows cords and colours and hieght and width
}
#pragma pack(push, 1)  // Ensure struct alignment for BMP headers
typedef struct {
    unsigned char bfType[2];  // "BM"
    unsigned int bfSize;
    unsigned short bfReserved1;
    unsigned short bfReserved2;
    unsigned int bfOffBits;   // Pixel data offset
} BMPHeader;

typedef struct {
    unsigned int biSize;
    int width;
    int height;
    unsigned short biPlanes;
    unsigned short biBitCount;  // Bits per pixel (24 or 32)
    unsigned int biCompression;
    unsigned int biSizeImage;
    int biXPelsPerMeter;
    int biYPelsPerMeter;
    unsigned int biClrUsed;
    unsigned int biClrImportant;
} BMPInfoHeader;
#pragma pack(pop)

int getBMPTextures(char* filename, double ***textures, int* widthr, int* heightr) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
    	ShowPopup("er file open not", "error");
        printf("Error: Cannot open file.\n");
        return 1;
    }
    BMPHeader bmpHeader;
    BMPInfoHeader bmpInfo;
    fread(&bmpHeader, sizeof(BMPHeader), 1, fp);
    fread(&bmpInfo, sizeof(BMPInfoHeader), 1, fp);

    if (bmpHeader.bfType[0] != 'B' || bmpHeader.bfType[1] != 'M') {
        printf("Error: Not a valid BMP file.\n");
        ShowPopup("bad dmp file", "error");
        fclose(fp);
        return 1;
    }

    int width = bmpInfo.width;
    int height = bmpInfo.height;
    int bytesPerPixel = bmpInfo.biBitCount / 8;
    int rowSize = ((bmpInfo.biBitCount * width + 31) / 32) * 4;
    int dataSize = rowSize * height;

    unsigned char *pixels = (unsigned char*)malloc(dataSize);
    if (fread(pixels, 1, dataSize, fp) != dataSize) {
        printf("Error: Unexpected EOF while reading pixel data.\n");
        ShowPopup("unexpl eof while red", "error");
        free(pixels);
        fclose(fp);
        return 1;
    }
    fclose(fp);
    int rows = width * height;
    *widthr = bmpInfo.width;
    *heightr = bmpInfo.height;
    *textures = (double**)malloc(rows * sizeof(double*));
    int i;
    for (i = 0; i < rows; i++) {
        (*textures)[i] = (double*)calloc(5, sizeof(double));
    }
	int y; 
    for (y = 0; y < height; y++) {
    	int  x;
        for (x = 0; x < width; x++) {
            int row = height - 1 - y;
            int index = row * rowSize + x * bytesPerPixel;
            int i = y * width + x;

            (*textures)[i][0] = x;
            (*textures)[i][1] = y;
            (*textures)[i][2] = pixels[index + 2]; // R
            (*textures)[i][3] = pixels[index + 1]; // G
            (*textures)[i][4] = pixels[index];     // B
        }
    }
	if (textures[0] == NULL || textures[0][2] == 0) {
    ShowPopup("debug", "Texture array not initialized correctly");
	}
	
    free(pixels);
    return 0;
}


 
/**************************
 * Object rendering - world layout matricies
 *
 **************************/
//world matrix coordinate system keys for objects
#define VOIDO 32  //      32
#define FLOORO 70 //'int F
//feel like should be defined as a char with eq F*10
//.. ect

struct worldmatrix{                  //top bottom side pollar views
	double * boolstuffexr;   //x, r
	double * boolstuffexfeta; //feta
	double * boolstuffexzeta; //feta
	size_t xrs;
	size_t xrc;
	
	double * boolstuffexrf;   //the actuall floora value consistant with that that for pixles and stuff so that is not too fussed about i just need to figure out how to not loss information
	double * boolstuffexfetaf;
	double * boolstuffexzetaf;   //later change type to int 
	size_t xrfs;
	size_t xrfc;
	
	int * localindexxs;
	
	double * boolstuffezr;
	double * boolstuffezfeta;
	double * boolstuffezzeta;
	size_t zrs;
	size_t zrc;
	
	double * boolstuffezrf;
	double * boolstuffezfetaf;
	double * boolstuffezzetaf;
	size_t zrfs;
	size_t zrfc;
	
	int * localindexzs;
	
	
	double * boolstuff;     //object are in bitmap occurding to thier values FLOORO for eg
	float scale;         //do not forget that this is float
}; //pollar

struct cameraview{//pollar
	double * stuffenfeta;
	double * stuffenfi;
	double * stuffenr;
	double * stuff;
};
struct visibledomain{
	double cameramaxfeta;          //0.60 woulbe 60*2 = 1.20      expresed in 60/360
	double cameramaxfi;
	double cameramaxr; //probs not needed render distance   expressed in units i in worlmatrix
	
	
	double cameraorintationvx;     //xyz to make vector 
	double cameraorintationvy;
	double cameraorintationvz; //based on carisian plane where thing point basicly like compas compute based on cursor
	
	
	double camerax;
	double cameray;             //player position
	double cameraz; 
	struct worldmatrix ww1;
	struct cameraview pp;
};
int frompollar(){
	return 0;
}
int topollar(){
	return 0;
}
int loadvisibledomain(struct visibledomain *VDA){
	VDA->cameramaxfeta = 60/360;
	VDA->cameramaxfi = 60/360;
	VDA->cameramaxr = 20;
	VDA->camerax=0;
	VDA->cameray=0;
	VDA->cameraz=0;
	VDA->ww1.scale = 2; //where the this means that 0.2 expansion and 2 means a compression of 2 units per one length of boolstuffex
	return 0;
}
/**************************
 * Object rendering - assets
 *
 **************************/
int characterXcords;
int characterYcords;

struct object{
	int weight;
	int lenx;
	int leny;
	double ** vectorisedmodel;// list, vectorised form, x,y,z,rgb(3)
	double relativecoordinates[6]; //x,y,z, pitch, yaw, role
	struct Textures texture; 
};
void initObject(struct object* obj, int weight) {
    obj->weight = weight;
    
    obj->vectorisedmodel = (double**)malloc(weight * sizeof(double**));
    int i,j;
    for (i = 0; i < weight; i++) {
        obj->vectorisedmodel[i] = (double*)malloc(6 * sizeof(double*));
    }
}

// Free object after use
void freeObject(struct object* obj) {
	int i,j;
    for (i = 0; i < obj->weight; i++) {
        free(obj->vectorisedmodel[i]);
    }
    free(obj->vectorisedmodel);
}


struct totalassets{
	struct object floor;
	
};
void convertmodelto2darrayslices(){
	//future me problem tell me when you here
}
void getcorrdsCharacter(){
	//windows shiniagins for controlling xcords, ycords and camera pitch as well as if tern right or not (all mouse positon) chat gpt do
}

struct buttons{
	//all buttons and thier coordinates 
};
struct responsiveGuiObjects{
	int activatingcoords;
	struct object gui;
	int activatingVK;
	struct buttons button;
};
int customeobjectfloor(struct totalassets *floor){
	//char* path = "textures//floor.BMP";
	floor->floor.texture.filepath = "..\\spiralenginev3\\textures\\floor.BMP";
	double *** rettextarray = &floor->floor.texture.texture3dArray;
	int ret = getBMPTextures(floor->floor.texture.filepath, rettextarray, &floor->floor.texture.width, &floor->floor.texture.height);
	if(ret == 1){
		ShowPopup("could not lo11ad floor asset error at loading texture :<", "insfombia error cause yes!");
		return 1;
	}
	if(floor->floor.texture.width < 1){
		ShowPopup("width below 1", "insfombia error cause yes!");
		return 1;
	}else if(floor->floor.texture.height < 1){
		ShowPopup("width not below 1 but it is actually hieght that is", "insfombia error cause yes!");
		return 1;
	}
	//ShowPopup("could not lo11ad floor asset :<", "insfombia error cause yes!");
	//struct totalassets floor;
	int weight=floor->floor.texture.width * floor->floor.texture.height; // no stretch currently
	initObject(&floor->floor, weight);
	int i;
	floor->floor.relativecoordinates[0] = 0;
	floor->floor.relativecoordinates[1] = 0;
	floor->floor.relativecoordinates[2] = 0;
	
	floor->floor.relativecoordinates[3] = 0;
	floor->floor.relativecoordinates[4] = 0;
	floor->floor.relativecoordinates[5] = 0;
	for(i=0; i<=weight-1; i++){
		//ShowPopup(":< 10 debug", "insfombia error cause yes!");
		//ShowPopup("could not lo11ad floor asset :<", "insfombia error cause yes!");
		floor->floor.vectorisedmodel[i][0] = floor->floor.texture.texture3dArray[i][0];
		floor->floor.vectorisedmodel[i][1] = floor->floor.texture.texture3dArray[i][1];
		floor->floor.vectorisedmodel[i][2] = 0;          //how impliment now well tilt goes first i suppose
		floor->floor.vectorisedmodel[i][3] = floor->floor.texture.texture3dArray[i][2];
		floor->floor.vectorisedmodel[i][4] = floor->floor.texture.texture3dArray[i][3];
		floor->floor.vectorisedmodel[i][5] = floor->floor.texture.texture3dArray[i][4];
		//floor->floor.vectorisedmodel[i][6] = 0.0f;
			
	}
	
	return 0;
} // works fine so far
//loadable assets
const char LLAS[2] ={0,FLOORO};
void renderassetoverlay(){
	int i;
	for(i=0; i< sizeof(LLAS)-1; i++){
		
	}
}
void getcorrdsTerrian(char* assetsloaded, struct visibledomain *VDA, struct totalassets *totalass, struct totalspirals *allspirals){
	//ok first we need to look at objects dimensions by creating a contour thiga maggig and loaded in the object into VDA, saving the countors
	//then we convert everything to pollar coordinates, all seems shrinple
	int i;
	char appendixvaribles[sizeof(assetsloaded)] = "";
	for(i=0; i<sizeof(assetsloaded)-1; i++){
		switch (assetsloaded[i]){
			case (char)VOIDO:
				appendixvaribles[i] = (char)VOIDO;
				//do stuff
			case (char)FLOORO:
				appendixvaribles[i] = (char)FLOORO;
				//generate a circle of diameter floor bigger and then do findclosetcoordinate for like a 5 points on that circle (pentigon)
				//for each orientation apply the math for sqeezing vertial matrixies from first found edges through locating the most isolated values on the spiral
				//then create a bitmap scalled version
				
				//generating pentigon
				int n = allspirals->sfloor.zeta;
				double pointsx[n];
				double pointsy[n];
				int k;
				int pindex[n];
				int r=0;
				int feta=0;
				int zeta = 0;
				nthpolygen(totalass->floor.weight,n,(double**)pointsx, (double**)pointsy);
				for(k=0; k<=n; k++){
					findclosetcoordinate(
					    allspirals->sfloor.complexxs,
					    allspirals->sfloor.complexys,
					    allspirals->sfloor.totalsize,
					    pointsx[n],
					    pointsy[n],
					    &pindex[n]
					);                    // ok so round and the eq is r=sqr(x^2 +y2), feta = tan-1(y/x), z=z
					r=(int)pow(pow(totalass->floor.relativecoordinates[0]+allspirals->sfloor.complexxs[pindex[n] ],2)+pow(totalass->floor.relativecoordinates[1]+allspirals->sfloor.complexxs[pindex[n] ],2),0.5);
					feta=(int)atan((totalass->floor.relativecoordinates[0]+allspirals->sfloor.complexxs[pindex[n] ])/ (totalass->floor.relativecoordinates[1]+allspirals->sfloor.complexxs[pindex[n] ]));
					zeta = (int)(totalass->floor.relativecoordinates[2]);
					append((void **)&VDA->ww1.boolstuffexr, &VDA->ww1.xrs, &VDA->ww1.xrc, sizeof(int), &r);
					size_t n = VDA->ww1.xrs - 1;
					double temp;
					temp = FLOORO;
					append((void **)&VDA->ww1.boolstuffexrf, &VDA->ww1.xrfs, &VDA->ww1.xrfc, sizeof(double), &temp);
					temp = feta;
					append((void **)&VDA->ww1.boolstuffexfeta, &VDA->ww1.xrfs, &VDA->ww1.xrfc, sizeof(double), &temp);
					temp = FLOORO;
					append((void **)&VDA->ww1.boolstuffexfetaf, &VDA->ww1.xrfs, &VDA->ww1.xrfc, sizeof(double), &temp);
					temp = zeta;
					append((void **)&VDA->ww1.boolstuffexzeta, &VDA->ww1.xrfs, &VDA->ww1.xrfc, sizeof(double), &temp);
					temp = FLOORO;
					append((void **)&VDA->ww1.boolstuffexzetaf, &VDA->ww1.xrfs, &VDA->ww1.xrfc, sizeof(double), &temp);
					append((void **)&VDA->ww1.localindexxs, &VDA->ww1.xrfs, &VDA->ww1.xrfc, sizeof(int), &k);
				}
				//rotate thing once or not at all just go through all and make knew really quickly how about threads 
				//now apply the spiral alg to the points to see how changed
				//then fill the polar things with it 
				//then you finish in this function for this case, and you can do more latyer
				//ok so the vector we need to apply is 0, 1, -3
				int xyzstart[3] = {0,0,0};
				int xyzend[3] = {0, 1, -100};
				spiralomnidirectionalcompute(&allspirals->sfloors, xyzstart, xyzend, 1);
				double ** axs = &allspirals->sfloor.Xs;
				double ** ays = &allspirals->sfloor.Ys;
				double ** acomplexx = &allspirals->sfloor.complexxs;
				double ** acomplexy = &allspirals->sfloor.complexys;
				render3dgraphicSPIRALComplexPlain(*axs, allspirals->sfloor.size, *ays, 0, 0, allspirals->sfloor.zeta, *acomplexx, *acomplexy, allspirals->sfloors);
				xyzend[1] = -1;
				xyzend[2] = +100;
				spiralomnidirectionalcompute(&allspirals->sfloors, xyzstart, xyzend, 1);
				nthpolygen(totalass->floor.weight,n,(double**)pointsx, (double**)pointsy);
				for (k = 0; k <= n; k++) {
					findclosetcoordinate(
						allspirals->sfloor.complexxs,
						allspirals->sfloor.complexys,
						allspirals->sfloor.totalsize,
						pointsx[n],
						pointsy[n],
						&pindex[n]
					);
					// Compute cylindrical coordinates
					r = (int)pow(
						pow(totalass->floor.relativecoordinates[0] + allspirals->sfloor.complexxs[pindex[n]], 2) +
						pow(totalass->floor.relativecoordinates[1] + allspirals->sfloor.complexys[pindex[n]], 2),
						0.5
					);
					feta = (int)atan(
						(totalass->floor.relativecoordinates[0] + allspirals->sfloor.complexxs[pindex[n]]) /
						(totalass->floor.relativecoordinates[1] + allspirals->sfloor.complexys[pindex[n]])
					);
					zeta = (int)(totalass->floor.relativecoordinates[2]);
					append((void **)&VDA->ww1.boolstuffezr, &VDA->ww1.zrs, &VDA->ww1.zrc, sizeof(int), &r);
					size_t idx = VDA->ww1.zrs - 1;
					double temp;
					temp = FLOORO;
					append((void **)&VDA->ww1.boolstuffezrf, &VDA->ww1.zrfs, &VDA->ww1.zrfc, sizeof(double), &temp);
					temp = feta;
					append((void **)&VDA->ww1.boolstuffezfeta, &VDA->ww1.zrfs, &VDA->ww1.zrfc, sizeof(double), &temp);
					temp = FLOORO;
					append((void **)&VDA->ww1.boolstuffezfetaf, &VDA->ww1.zrfs, &VDA->ww1.zrfc, sizeof(double), &temp);
					temp = zeta;
					append((void **)&VDA->ww1.boolstuffezzeta, &VDA->ww1.zrfs, &VDA->ww1.zrfc, sizeof(double), &temp);
					temp = FLOORO;
					append((void **)&VDA->ww1.boolstuffezzetaf, &VDA->ww1.zrfs, &VDA->ww1.zrfc, sizeof(double), &temp);
					append((void **)&VDA->ww1.localindexzs, &VDA->ww1.xrfs, &VDA->ww1.xrfc, sizeof(int), &k);
				}
		}
	}
}

/**************************
 * Object rendering - masks
 *
 **************************/
 
int blur(){
	return 0;
}

int sharpen(){
	return 0;
}

int smoothen(struct object *ob1){
	
	return 0;
}


void allobjectsrender(struct visibledomain *VDA, struct mainspiralset *main, struct totalspirals *allspirals){
	 //make find function that see feta and angle and finds in that space, also since is the vda is a mess you should really be useing the coordinates findering to get indexes using filters 
	 //onces filters have been found you should the make a funny map of the objects closests ( a wall)
	 //then based on distance put into main, and thier pixles get calculate due to light which for now is nothing
	 //lets get working
	 //first fillter the positions (angles using max min function and hash mapps)
	 //once that is complete you can use distance to complete everything ewlse 
	 
	 /*ok so the plan is that we take the VDA, 
	 then we create two lists one has the indexes the other the values right, 
	 the we can place the index in the actuall indexes, 
	 sort the main array with the values for the greates value
	 generating the values in scope according to the unit circle 
	 then we can extract the neccarty values right :/ 
	 
	 i ment the neccary angles and we find the limits of that so that it is in range of our range 
	 we also need the player coordinates and camera orination regarding this mess however that is the unit circle oritation scheme which is just multpling the base coordinates by and angle
	 to get the requried position of shining things, light will copy this mechanic later so that only in certrain radius 
	 */
	 int TSOVIEW =  sizeof(VDA->ww1.boolstuffexrf);
	 
	int xri[TSOVIEW];
//	int xfetai[TSOVIEW];
//	int xzetai[TSOVIEW];
//	
//	double TONTIxr[TSOVIEW];
//	double TONTIxfeta[TSOVIEW];
//	double TONTIxzeta[TSOVIEW];
	//process the blockage of like light and entities here before actually go in and slowly sorting through all of them, make 0logn alg
	//compute valid poistions based on camera angles and distance 
	double deltacamerx = VDA->camerax - VDA->cameraorintationvx;
	double deltacamery = VDA->cameray - VDA->cameraorintationvy;
	double deltacamerz = VDA->cameraz - VDA->cameraorintationvz;
	
	double dynamiccamerafeta  = atan(deltacamerz/deltacamerx);           // VDA->pp.camera
	double dynamiccamerazeta  = atan(deltacamerz/deltacamery);
	double renderdistance = 20;
	float renderdistancescale=1;
	int i;
	int indexj =0;
	for(i=0; i<=TSOVIEW-1;i++){//ok so add if statements to make sure that in range 
		if((VDA->ww1.boolstuffexfeta[i]>=dynamiccamerafeta&& VDA->ww1.boolstuffexzeta[i]>=dynamiccamerazeta) || (VDA->ww1.boolstuffexfeta[i]<= - dynamiccamerafeta&& VDA->ww1.boolstuffexzeta[i] <= -dynamiccamerazeta)){
			//then ok and print
			xri[indexj] = i;
			indexj++;
			//put onto main
			//edit funny pixles   //finial stretch nearly to render your darn pixel
		}
		
	} //maybe maybe not
	double scalex =1;
	double scaley =1;
	for(i=0; i<=sizeof(xri)/sizeof(int); i++){
		switch((int)VDA->ww1.boolstuffexrf[xri[i]]){
			case VOIDO:
				//do nothing ignore
				break;
			case FLOORO:
				//maybe find function to find where the best place of placemenet is and give coordinates. 
				
				//make me a function that first takes the scale to m of the main pollar coords, then takes and fills main with the coordinates, and colours,
				//this is done through the sctruct of floor
				
				//maybe use find function or not use find function instead look at distance and stuff then find?, yes probably 
				//this is a probability because i need a probability of the probibily
				//ok so first of all we need to render
				//scale the coordinates
				scalex =1;
				scaley =1;
				double tempxmain = (VDA->ww1.boolstuffexfeta[xri[i]]) * scalex; //lighting VDA->ww1.boolstuffexr
				double tempymain = (VDA->ww1.boolstuffexzeta[xri[i]]) * scaley;
				
				//then take int of tempxmain and take scale of zeta, then make string like and add to stuff
				main->complexxs[(int)tempxmain] = tempxmain;
				main->complexys[(int)tempymain] = tempymain;
				
				//integrate textures
				
				main->colourr[(int)tempxmain] = allspirals->sfloor.colourr[VDA->ww1.localindexzs[xri[i]]];
				main->colourg[(int)tempxmain] = allspirals->sfloor.colourg[VDA->ww1.localindexzs[xri[i]]];
				main->colourb[(int)tempxmain] = allspirals->sfloor.colourb[VDA->ww1.localindexzs[xri[i]]];
				break;
		}
	}
	//main compression function    ha ah ah h ha ha a add 

	
	//use memcpy to copy the neccary or just assign induxes
	
	
}

/**************************
 * animations      (Ihate them)
 
 
 so, we have to import them or animate
 them with physics like the colours,
 
 
 ok so we make it so that joins are free mooving and 
 the characters that have join objects mean that these object can tug stuff
 but they are spirals 
 
 so basiclly a water engine that behaves not like water 
 *
 **************************/
 
 
 
 



