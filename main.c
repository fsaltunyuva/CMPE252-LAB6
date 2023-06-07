#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SHAPES 50

/* type definitions come here */
typedef struct {
    double x;
    double y;
    double z;
} point_t;

typedef struct {
    point_t center;
    double radius;
} sphere_t;

typedef struct {
    point_t center;
    double side;
} cube_t;

typedef struct {
    point_t center;
    double base_side_length;
    double height;
} square_prism_t;

typedef union {
    cube_t cube;
    square_prism_t square_prism;
    sphere_t sphere;
} shape3d_data_t;

typedef enum {
    CUBE, SQUARE_PRISM, SPHERE
} class_t;

typedef struct {
    class_t type;
    shape3d_data_t shape;
} shape_t;


/* function prototypes*/
int scanShape(FILE *filep, shape_t *objp);
int loadShapes(shape_t shapes[]);
void printShape(const shape_t *objp);
int isInside(const point_t *ptp, const point_t *ptp2, const shape_t *objp);

//Q1 Main
/*
int main()
{
    shape_t shapes[MAX_SHAPES];
    int numOfShapes = loadShapes(shapes);

    printf("\nShapes:\n");
    for (int i = 0; i < numOfShapes; i++)
        printShape(&shapes[i]);

    return 0;
}
 */

//Q2 Main
int main()
{
    shape_t shapes[MAX_SHAPES];
    int numOfShapes = loadShapes(shapes);

    printf("\nShapes 3D:\n");
    for (int i = 0; i < numOfShapes; i++)
        printShape(&shapes[i]);

    point_t pt,pt2;
    printf("\nEnter x,y and z coordinate of the start point of line: ");
    scanf("%lf %lf %lf",&pt.x,&pt.y,&pt.z);
    printf("\nEnter x,y and z coordinate of the end point of line: ");
    scanf("%lf %lf %lf",&pt2.x,&pt2.y,&pt2.z);

    printf("\nThe Line from <%.2lf %.2lf %.2lf>  to <%.2lf %.2lf %.2lf> is inside the following shapes:\n",pt.x,pt.y, pt.z ,pt2.x,pt2.y, pt2.z);
    for (int i = 0; i < numOfShapes; i++)
        if (isInside(&pt,&pt2,&shapes[i]))
            printShape(&shapes[i]);


    return 0;
}
//Q2 Main

int scanShape(FILE *filep, shape_t *objp){
    char line[128];
    while(fgets(line, sizeof (line), filep) != NULL){
        //Splitting the current line by " " and storing elements in *array
        char *p = strtok(line, " ");
        char *array[6];
        int i = 0;
        while (p != NULL) {
            array[i++] = p;
            p = strtok(NULL, " ");
        }
        //Splitting the current line by " " and storing elements in *array
        if(strcmp(array[0], "cube") == 0){;
            (objp->shape).cube.center.x = atof(array[1]);
            (objp->shape).cube.center.y = atof(array[2]);
            (objp->shape).cube.center.z = atof(array[3]);
            (objp->shape).cube.side = atof(array[4]);

            objp->type = (class_t) 0;
            return 1;
        }
        else if(strcmp(array[0], "square_prism") == 0){
            (objp->shape).square_prism.center.x = atof(array[1]);
            (objp->shape).square_prism.center.y = atof(array[2]);
            (objp->shape).square_prism.center.z = atof(array[3]);
            (objp->shape).square_prism.base_side_length = atof(array[4]);
            (objp->shape).square_prism.height = atof(array[5]);

            objp->type = (class_t) 1;
            return 1;
        }
        else if(strcmp(array[0], "sphere") == 0){
            (objp->shape).sphere.center.x = atof(array[1]);
            (objp->shape).sphere.center.y = atof(array[2]);
            (objp->shape).sphere.center.z = atof(array[3]);
            (objp->shape).sphere.radius = atof(array[4]);

            objp->type = (class_t) 2;
            return 1;
        }
        else{
            return 0;
        }
        break;
    }
    return 0;
}

int loadShapes(shape_t shapes[]) {
    char fileName[64];
    printf("Enter the file name to read: ");
    scanf("%s", fileName);
    printf("\nOpening %s", fileName);
    printf("\nLoading complete");

    FILE *ptr = fopen(fileName, "r");

    int currentIndex = 0;
    shape_t obj;
    int numberOfShapedRead = 0;

    while(scanShape(ptr, &obj) != 0) {
        shapes[currentIndex++] = obj;
        numberOfShapedRead++;
    }

    printf("\nClosing %s", fileName);
    fclose(ptr);

    return numberOfShapedRead;
}

void printShape(const shape_t *objp){
    if(objp->type == (class_t) 0){
        printf("Cube: <%.2lf %.2lf %.2lf> <%.2lf>\n", objp->shape.cube.center.x,
               objp->shape.cube.center.y, objp->shape.cube.center.z, objp->shape.cube.side);
    }
    else if(objp->type == (class_t) 1){
        printf("Square_prism: <%.2lf %.2lf %.2lf> <%.2lf %.2lf>\n", objp->shape.square_prism.center.x, objp->shape.square_prism.center.y
        , objp->shape.square_prism.center.z, objp->shape.square_prism.base_side_length, objp->shape.square_prism.height);
    }
    else if (objp->type == (class_t) 2){
        printf("Sphere: <%.2lf %.2lf %.2lf> <%.2lf>\n", objp->shape.sphere.center.x, objp->shape.sphere.center.y,
               objp->shape.sphere.center.z, objp->shape.sphere.radius);
    }
}

int isInside(const point_t *ptp1, const point_t *ptp2, const shape_t *objp){

    if(objp->type == 0){ //If it is cube
        double x_min = objp->shape.cube.center.x - objp->shape.cube.side/2;
        double x_max = objp->shape.cube.center.x + objp->shape.cube.side/2;

        double y_min = objp->shape.cube.center.y - objp->shape.cube.side/2;
        double y_max = objp->shape.cube.center.y + objp->shape.cube.side/2;

        double z_min = objp->shape.cube.center.z - objp->shape.cube.side/2;
        double z_max = objp->shape.cube.center.z + objp->shape.cube.side/2;

        if(x_min <= ptp1->x && x_max>=ptp1->x && x_min <= ptp2->x && x_max>=ptp2->x
        &&
        y_min <= ptp1->y && y_max>=ptp1->y && y_min <= ptp2->y && y_max>=ptp2->y
        &&
        z_min <= ptp1->z && z_max>=ptp1->z && z_min <= ptp2->z && z_max>=ptp2->z){
            return 1;
        }
        else return 0;
    }
    else if (objp->type == 1){ //If it is square prism
        double x_min = objp->shape.square_prism.center.x - objp->shape.square_prism.base_side_length/2;
        double x_max = objp->shape.square_prism.center.x + objp->shape.square_prism.base_side_length/2;

        double y_min = objp->shape.square_prism.center.y - objp->shape.square_prism.base_side_length/2;
        double y_max = objp->shape.square_prism.center.y + objp->shape.square_prism.base_side_length/2;

        double z_min = objp->shape.square_prism.center.z - objp->shape.square_prism.height/2;
        double z_max = objp->shape.square_prism.center.z + objp->shape.square_prism.height/2;

        if(x_min <= ptp1->x && x_max>=ptp1->x && x_min <= ptp2->x && x_max>=ptp2->x
           &&
           y_min <= ptp1->y && y_max>=ptp1->y && y_min <= ptp2->y && y_max>=ptp2->y
           &&
           z_min <= ptp1->z && z_max>=ptp1->z && z_min <= ptp2->z && z_max>=ptp2->z){
            return 1;
        }
        else return 0;

    }
    else if(objp->type == 2) { //If it is sphere
        double distance_p1_to_center = sqrt(pow(ptp1->x - objp->shape.sphere.center.x, 2) + pow(ptp1->y - objp->shape.sphere.center.y, 2) + pow(ptp1->z - objp->shape.sphere.center.z, 2));
        double distance_p2_to_center = sqrt(pow(ptp2->x - objp->shape.sphere.center.x, 2) + pow(ptp2->y - objp->shape.sphere.center.y, 2) + pow(ptp2->z - objp->shape.sphere.center.z, 2));
        if(distance_p1_to_center <= objp->shape.sphere.radius && objp->shape.sphere.radius >= distance_p2_to_center){
            return 1;
        }
        else return 0;
    }

}
