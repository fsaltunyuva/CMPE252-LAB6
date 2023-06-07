#include <stdio.h>
#include <math.h>
#include <string.h>

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
    sphere_t sphere; //PDF'Te buraası da cube yazıyor
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

int main()
{
    shape_t shapes[MAX_SHAPES];
    int numOfShapes = loadShapes(shapes);

    printf("\nShapes:\n");
    for (int i = 0; i < numOfShapes; i++)
        printShape(&shapes[i]);

    return 0;
}

int scanShape(FILE *filep, shape_t *objp){
    char line[128];
    while(fgets(line, sizeof (line), filep)){

        //Splitting the current line by " " and storing elements in *array
        char *p = strtok(line, " ");
        char *array[5];
        int i = 0;
        while (p != NULL) {
            array[i++] = p;
            p = strtok(NULL, " ");
        }
        //Splitting the current line by " " and storing elements in *array

        if(strcmp(array[0], "cube") == 0){
            //objp->shape.cube.center =
            objp->type = (class_t) 0;
        }
        else if(strcmp(array[0], "square_prism") == 0){
            //objp->shape.square_prism.
            objp->type = (class_t) 1;
        }
        else if(strcmp(array[0], "sphere") == 0){
            //objp->shape.sphere.
            objp->type = (class_t) 2;
        }
    }
    return 1;
}

int loadShapes(shape_t shapes[]) {
    return 1;
}

void printShape(const shape_t *objp){
    if(objp->type == (class_t) 0){
        printf("Cube: <%.2lf %.2lf %.2lf> <%.2lf>", objp->shape.cube.center.x,
               objp->shape.cube.center.y, objp->shape.cube.center.z, objp->shape.cube.side);
    }
    else if(objp->type == (class_t) 1){
        printf("Square_prism: <%.2lf %.2lf %.2lf> <%.2lf %.2lf>", objp->shape.square_prism.center.x, objp->shape.square_prism.center.y
        , objp->shape.square_prism.center.z, objp->shape.square_prism.base_side_length, objp->shape.square_prism.height);
    }
    else if (objp->type == (class_t) 2){
        printf("Sphere: <%.2lf %.2lf %.2lf> <%.2lf>", objp->shape.sphere.center.x, objp->shape.sphere.center.y,
               objp->shape.sphere.center.z, objp->shape.sphere.radius);
    }
}
