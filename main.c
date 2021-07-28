
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"
unsigned int bg2;


GLint osq[3][4] = {{0, 1, 1, 0}, {0, 0, 1, 1}, {1, 1, 1, 1}};
GLint nsq[3][4] = {{0, 1, 1, 0}, {0, 0, 1, 1}, {1, 1, 1, 1}};
GLint tsq[3][4] = {{0, 1, 1, 0}, {0, 0, 1, 1}, {1, 1, 1, 1}};
GLint scalem[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
GLint transm[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
GLint *a;
GLint n;
char type = 'r';
char order = 'a';
int font = 0;

static GLfloat theta[] = {0.0, 0.0, 0.0};
static GLint axis = 0;
clock_t start, finish;

void display();
void multiply(char);
void scale(int);
void translate(int);
void randomize();
void cube();
void drawtext(int, int, int, char *);
void bsort(int[], int);
void delay(int);
void quickSort(int[], int, int, int);
int partition(int[], int, int, int);
void msgtext(int, int, int, char *);
void swap(int *, int *);
void heapify(int[], int, int);

void heapifyd(int[], int, int);

void display()
{
    int i;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    switch (type)
    {
    case 'r':
        drawtext(0, n, 0, "Array to be sorted");
        break;
    case 'q':
        drawtext(0, n, 0, "Quick Sort | Execution time in ms=");
        break;
    case 'b':
        drawtext(0, n, 0, "Bubble Sort | Execution time in ms=");
        break;
    case 's':
        drawtext(0, n, 0, "Selection Sort | Execution time in ms=");
        break;
    case 'i':
        drawtext(0, n, 0, "Insertion Sort | Execution time in ms=");
        break;
    case 'm':
        drawtext(0, n, 0, "Merge Sort | Execution time in ms=");
        break;
    }
    for (i = 0; i < n; i++)
    {
        scale(a[i]);
        translate(i);
        nsq[0][0] = 0 + 2 * i;
        nsq[1][0] = 0;
        nsq[0][1] = 1 + 2 * i;
        nsq[1][1] = 0;
        cube();
    }
    glFlush();
    glutSwapBuffers();
}



void drawtext(int x, int y, int z, char *s)
{
    int i, j;
    char t[10];
    char *u = malloc(strlen(s) + 20);
    for (i = 0; i < strlen(u); i++)
        u[i] = ' ';
    if (type != 'r')
    {
        sprintf(t, "%d", (int)((clock() - start) / 1000));
        strcat(u, s);
        strcat(u, t);
        glColor3f(1.0, 1.0, 1.0);
        glRasterPos3i(x, y, z);
        for (i = 0; u[i] != '\0'; i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, u[i]);
    }
    else
    {
        glColor3f(1.0, 1.0, 1.0);
        glRasterPos3i(x, y, z);
        for (i = 0; s[i] != '\0'; i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
        char m[150];
        sprintf(m, "%s", "1. Bubble | 2. Quick | 3. Selection | 4. Insertion | 5. Merge");
        glRasterPos3i(x, y + 4, z);
        for (i = 0; m[i] != '\0'; i++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, m[i]);
    }
}

void bsort(int a[], int n)
{
    int i, j, x, y, temp;
    for (i = 0; i < n; i++)
        for (j = i + 1; j < n; j++)
        {
            if (order == 'a')
            {
                if (a[i] > a[j])
                {
                    temp = a[i];
                    a[i] = a[j];
                    a[j] = temp;
                    display();
			
                }
            }
            if (order == 'd')
            {
                if (a[i] < a[j])
                {
                    temp = a[i];
                    a[i] = a[j];
                    a[j] = temp;

                    display();
                }
            }
	
            delay(2000);
        }
}

void delay(int d)
{
    clock_t start = clock();
    while (clock() < start + d*10)
    {
    }
}

void quickSort(int a[], int n, int low, int high)
{
    if (low < high)
    {
        int pi = partition(a, n, low, high);
        quickSort(a, n, low, pi - 1);
        quickSort(a, n, pi + 1, high);
    }
}

extern int partition(int a[], int n, int low, int high)
{
    int pivot = a[high];
    int i = (low - 1), j;

    for (j = low; j <= high - 1; j++)
    {
        if (order == 'a')
        {
            if (a[j] <= pivot)
            {
                i++;
                swap(&a[i], &a[j]);
                display();
                delay(2000);
            }
        }
        if (order == 'd')
        {
            if (a[j] >= pivot)
            {
                i++;
                swap(&a[i], &a[j]);
                display();
                delay(2000);
            }
        }
    }
    swap(&a[i + 1], &a[high]);
    display();
    delay(3000);
    return (i + 1);
}

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void selectionSort(int a[], int n)
{
    int i, j, min_idx;
    for (i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
        {
            if (order == 'a')
            {
                if (a[j] < a[min_idx])
                    min_idx = j;
            }
            else
            {
                if (a[j] > a[min_idx])
                    min_idx = j;
            }
        }
        swap(&a[min_idx], &a[i]);
        delay(10000);
        display();
    }
}

void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        if (order == 'a')
        {
            while (j >= 0 && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j = j - 1;
                display();
                delay(1000);
            }
        }
        else
        {
            while (j >= 0 && arr[j] < key)
            {
                arr[j + 1] = arr[j];
                j = j - 1;
                display();
                delay(1000);
            }
        }

        arr[j + 1] = key;
    }
}


void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (order == 'a')
        {
            if (L[i] <= R[j])
            {
                arr[k] = L[i];
                display();
                delay(1000);
                i++;
            }
            else
            {
                arr[k] = R[j];
                display();
                delay(1000);
                j++;
            }
        }
        else
        {
            if (L[i] >= R[j])
            {
                arr[k] = L[i];
                display();
                delay(1000);
                i++;
            }
            else
            {
                arr[k] = R[j];
                display();
                delay(1000);
                j++;
            }
        }

        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        display();
        delay(1000);
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        display();
        delay(1000);
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void cube()
{
    glColor3f(0.0, 0.8, 0.8);
    glBegin(GL_POLYGON);
    glVertex3i(nsq[0][0], nsq[1][0], 0);
    glVertex3i(nsq[0][1], nsq[1][1], 0);
    glVertex3i(nsq[0][2], nsq[1][2], 0);
    glVertex3i(nsq[0][3], nsq[1][3], 0);
    glEnd();

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3i(nsq[0][0], nsq[1][0], 0);
    glVertex3i(nsq[0][3], nsq[1][3], 0);
    glVertex3i(nsq[0][3], nsq[1][3], 1);
    glVertex3i(nsq[0][0], nsq[1][0], 1);
    glEnd();

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3i(nsq[0][1], nsq[1][1], 0);
    glVertex3i(nsq[0][2], nsq[1][2], 0);
    glVertex3i(nsq[0][2], nsq[1][2], 1);
    glVertex3i(nsq[0][1], nsq[1][1], 1);
    glEnd();

    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3i(nsq[0][0], nsq[1][0], 1);
    glVertex3i(nsq[0][1], nsq[1][1], 1);
    glVertex3i(nsq[0][2], nsq[1][2], 1);
    glVertex3i(nsq[0][3], nsq[1][3], 1);
    glEnd();

    glColor3f(1.0, 0.0, 0.5);
    glBegin(GL_POLYGON);
    glVertex3i(nsq[0][2], nsq[1][2], 0);
    glVertex3i(nsq[0][3], nsq[1][3], 0);
    glVertex3i(nsq[0][3], nsq[1][3], 1);
    glVertex3i(nsq[0][2], nsq[1][2], 1);
    glEnd();

    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3i(nsq[0][0], nsq[1][0], 0);
    glVertex3i(nsq[0][1], nsq[1][1], 0);
    glVertex3i(nsq[0][1], nsq[1][1], 1);
    glVertex3i(nsq[0][0], nsq[1][0], 1);
    glEnd();
}

void multiply(char x)
{
    int i, j, k;
    if (x == 's')
    {
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 4; j++)
            {
                nsq[i][j] = 0;
                for (k = 0; k < 4; k++)
                    nsq[i][j] += scalem[i][k] * osq[k][j];
            }
        }
        for (i = 0; i < 3; i++)
            for (j = 0; j < 4; j++)
                tsq[i][j] = nsq[i][j];
    }
    else
    {
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 4; j++)
            {
                nsq[i][j] = 0;
                for (k = 0; k < 4; k++)
                    nsq[i][j] += transm[i][k] * tsq[k][j];
            }
        }
    }
}

void scale(int i)
{
    scalem[1][1] = i + 1;
    multiply('s');
}

void translate(int i)
{
    transm[0][2] = 2 * i;
    multiply('t');
}

void keys(unsigned char key, int x, int y)
{
    if (key == 13)
    {
        type = 'r';
        randomize(a, n);
    }
    if (key == '0')
    {
        type = 'r';
        randomize(a, n);
    }
    if (key == '1')
    {
        type = 'b';
        start = clock();
        bsort(a, n);
    }
    if (key == '2')
    {
        type = 'q';
        start = clock();
        quickSort(a, n, 0, n - 1);
    }
   
    if (key == '3')
    {
        type = 's';
        start = clock();
        selectionSort(a, n);
        display();
    }
    if (key == '4')
    {
        type = 'i';
        start = clock();
        insertionSort(a, n);
        display();
    }
    
    if (key == '5')
    {
        type = 'm';
        start = clock();
        mergeSort(a, 0, n);
        display();
    }
}

void SpecialInput(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
    {
        axis = 1;
        theta[axis] += 0.5;
        if (theta[axis] >= 360.0)
            theta[axis] -= 360.0;
        glRotatef(theta[0], 1.0, 0.0, 0.0);
        display();
    }
    if (key == GLUT_KEY_DOWN)
    {
        axis = 1;
        theta[axis] += 0.5;
        if (theta[axis] >= 360.0)
            theta[axis] -= 360.0;
        glRotatef(-theta[0], 1.0, 0.0, 0.0);
        display();
    }
    if (key == GLUT_KEY_LEFT)
    {
        axis = 0;
        theta[axis] += 0.5;
        if (theta[axis] >= 360.0)
            theta[axis] -= 360.0;
        glRotatef(theta[1], 0.0, 1.0, 0.0);
        display();
    }
    if (key == GLUT_KEY_RIGHT)
    {
        axis = 0;
        theta[axis] += 0.5;
        if (theta[axis] >= 360.0)
            theta[axis] -= 360.0;
        glRotatef(-theta[1], 0.0, 1.0, 0.0);
        display();
    }
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat)h / (GLfloat)w, 2.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
    else
        glOrtho(-2.0 * (GLfloat)h / (GLfloat)w, 2.0 * (GLfloat)h / (GLfloat)w, -2.0, 2.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

void randomize()
{
    srand(time(NULL));
    int i;
    for (i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        swap(&a[i], &a[j]);
    }
    display();
}

void myInit()
{
 
 
   
   
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.5, 0.5, 0.5, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(0, 2 * n, 0, n, 0, n);
}

void menu(int n)
{
    switch (n)
    {
    case 1:
        order = 'a';
        display();
        break;
    case 2:
        order = 'd';
        display();
        break;
    }
}
/*
void timer(int value)
{
    glutPostRedisplay();
}
void displayScene2()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_TEXTURE_2D);
   
    
    glEnable(GL_TEXTURE_2D);
    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, bg2);
    glBegin(GL_QUADS);
    glVertex3f(0, 0, 10);
    glTexCoord2f(0, 0);
    glVertex3f(0, 500, 10);
    glTexCoord2f(0, 1);
    glVertex3f(500, 500, 10);
glTexCoord2f(1, 1);
    glVertex3f(500, 0, 10);
    glTexCoord2f(1, 0);
    glEnd();
    glFlush();
    glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();
}
*/

/* void loadBackground(void)
{
    glGenTextures(1, &bg2);
    glBindTexture(GL_TEXTURE_2D, bg2);
    // set the bg1 wrapping/filtering options (on the currently bound bg1 object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the bg1
    int width, height, nrChannels;
    unsigned char *data = stbi_load("Scene_2_Final.png", &width, &height, &nrChannels, STBI_rgb_alpha);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        //glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
       
    }
    stbi_image_free(data);
}

*/


int main(int argc, char **argv)
{
    printf("Enter the number of elements you'd like to see: ");
    scanf("%d", &n);
    int i;
    a = malloc((n + 1) * sizeof(int));
    for (i = 0; i < n; i++)
        a[i] = i;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
glutInitWindowSize(1024, 720);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Sorting Algorithm");
//glutDisplayFunc(displayScene2);
    //loadBackground();
    
    //glutTimerFunc(500, timer, 0);
    glutCreateMenu(menu);
    glutAddMenuEntry("Ascending", 1);
    glutAddMenuEntry("Descending", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    myInit();
    randomize();
    glutReshapeFunc(myReshape);
    glutKeyboardFunc(keys);
    glutSpecialFunc(SpecialInput);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
