//Semestre 2019 - 2
 /*
 García Callejas Ricardo
 Grupo 1
 Visual Studio 2017
Proyecto 1
 */
#include "Main.h"
float xi=0;
float yi = 0;
float xf = 0;
float yf = 0;
float largo = 0;
float alto = 0;
float transZ = 0.0f;
float transX = 0.0f;
float transY = 0.0f;
float linea1[4] = { 0,0,0,0 };
float l1i[4] = { 0,0,0,0 };
float l1f[4] = { 0,0,0,0 };
int dibuja = 0;

void InitGL ( GLvoid )     // Inicializamos parametros
{
	//glShadeModel(GL_FLAT);							// Habilitamos Smooth Shading
	glClearColor(0.2f, 0.4f, 0.0f, 0.0f);				// Negro de fondo
	//glClearDepth(1.0f);									// Configuramos Depth Buffer
	//glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	//glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	
	
}

void vector(float l1[4], float l2[4],float linea[4], float xi, float xf, float yi, float yf)
{
	if (linea[0] < xi)
		l1[0] = 1;
	if (linea[0] > xf)
		l1[2] = 1;
	if (linea[1] < yi)
		l1[1] = 1;
	if (linea[1] > yf)
		l1[3] = 1;
	if (linea[2] < xi)
		l2[0] = 1;
	if (linea[2] > xf)
		l2[2] = 1;
	if (linea[3] < yi)
		l2[1] = 1;
	if (linea[3] > yf)
		l2[3] = 1;
}
int oplog(float l1[4], float l2[4],float linea[4])
{

	float lres[4] = { 0,0,0,0 };
	for ( int i = 0; i < 4; i++)
	{
		if (l1[i] || l2[i])
			lres[i] = 1;
	}
	if (lres[0] == 0 && lres[1] == 0 && lres[2] == 0 && lres[3] == 0)
	{
		printf("\n La linea se dibuja");
		return 1;
	}
	else {
		for (int i = 0; i < 4; i++)
		{
			if (l1[i] && l2[i])
				lres[i] = 0;
		}

		if (lres[0] == 0 && lres[1] == 0 && lres[2] == 0 && lres[3] == 0)
		{
			printf("\n La linea se descarta");
			return 0;
		}
		else
		{		printf("\n La linea se recorta");
		return 2;
		}
	}

}
void recorta(float l[4], float xi, float xf, float yi, float yf)
{
	float laux = 0;
	float laux2 = 0;
	float usup = 0;
	float uder = 0;
	float uizq = 0;
	float uinf = 0;
	int cont = 0;
	
	//limite sup
	glBegin(GL_LINES);
	glColor3f(1.0, 1.0, 1.0);
	usup = (yf - l[1]) / (l[3] - l[1]);
	if (usup > 0 && usup < 1)
	{
		laux2 = yf;
		laux = l[0] + usup * (l[2] - l[0]);
		printf("\nLimite suo valor de l[0]=%f,valor de l[1]=%f,valor de l[2]=%f,valor de l[3]=%f", laux, laux2, l[2], l[3]);
		if (laux <= xf && laux >= xi && laux2 <= yf && laux2 >= yi)
		{
			glVertex3f(laux, laux2, 0.0);
			cont++;
		}
	}
	uinf = (yi - l[1]) / (l[3] - l[1]);
	if (uinf > 0 && uinf < 1)
	{
		laux2 = yi;
		laux = l[0] + uinf * (l[2] - l[0]);
		printf("\nLimite inf valor de l[0]=%f,valor de l[1]=%f,valor de l[2]=%f,valor de l[3]=%f", laux, laux2, l[2], l[3]);
		if (laux <= xf && laux >= xi && laux2 <= yf && laux2 >= yi)
		{
			glVertex3f(laux, laux2, 0.0);
			cont++;
		}
	}
	uizq = (xi - l[0]) / (l[2] - l[0]);
	if (uizq > 0 && uizq < 1)
	{
		laux = xi;
		laux2 = l[1] + uizq * (l[3] - l[1]); ;
		printf("\nLimite izq valor de l[0]=%f,valor de l[1]=%f,valor de l[2]=%f,valor de l[3]=%f", laux, laux2, l[2], l[3]);
		if (laux <= xf && laux >= xi && laux2 <= yf && laux2 >= yi)
		{
			glVertex3f(laux, laux2, 0.0);
			cont++;
		}
	}
	uder = (xf - l[0]) / (l[2] - l[0]);
	if (uder > 0 && uder < 1)
	{
		laux = xf;
		laux2 = l[1] + uder * (l[3] - l[1]);
		printf("\nLimite der valor de l[0]=%f,valor de l[1]=%f,valor de l[2]=%f,valor de l[3]=%f", laux, laux2, l[2], l[3]);
		if (laux<=xf && laux>=xi && laux2<=yf && laux2>=yi)
		{
			glVertex3f(laux, laux2, 0.0);
			cont++;
		}
	}
	if (cont == 1 || cont == 2)
	{
		if (l[2] < l[0] && l[3] < l[1]) {
			glVertex3f(l[0], l[1], 0.0);
			glVertex3f(laux, laux2, 0.0);
		}
		else {
			glVertex3f(l[2], l[3], 0.0);
			glVertex3f(laux, laux2, 0.0);
		}
	}
	glEnd();
}

void display ( void )   // Creamos la funcion donde se dibuja
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Limiamos pantalla y Depth Buffer	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();									// Reinicializamos la actual matriz Modelview

	//Poner aqui codigo ha dibujar
	glTranslatef(transX, transY, transZ);
	glBegin(GL_POLYGON);
	glColor3f(0.6, 0.6, 0.6);
	glVertex3f(xi, yf, 0.0);
	glVertex3f(xf, yf, 0.0);
	glVertex3f(xf, yf+1, 0.0);
	glVertex3f(xi, yf+1, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.6, 0.6, 0.6);
	glVertex3f(xi, yf+1, 0.0);
	glVertex3f(xi-1, yf+1, 0.0);
	glVertex3f(xi-1, yi , 0.0);
	glVertex3f(xi , yi , 0.0);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.6, 0.6, 0.6);
	glVertex3f(xf, yf + 1, 0.0);
	glVertex3f(xf + 1, yf + 1, 0.0);
	glVertex3f(xf + 1, yi, 0.0);
	glVertex3f(xf, yi , 0.0);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.6, 0.6, 0.6);
	glVertex3f(xi-1, yi, 0.0);
	glVertex3f(xf+1, yi, 0.0);
	glVertex3f(xf+1, yi - (largo*1.5), 0.0);
	glVertex3f(xi-1, yi - (largo*1.5), 0.0);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(xi+3, yi - 1, 0.0);
	glVertex3f(xi + 2, yi - 1, 0.0);
	glVertex3f(xi + 2, yi - 2, 0.0);
	glVertex3f(xi+3, yi - 2, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(xi + 3, yi - 2, 0.0);
	glVertex3f(xi + 2, yi - 2, 0.0);
	glVertex3f(xi + 2, yi - 3, 0.0);
	glVertex3f(xi + 3, yi - 3, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(xi + 2, yi - 1.5, 0.0);
	glVertex3f(xi + 1.5, yi - 1.5, 0.0);
	glVertex3f(xi + 1.5, yi - 2.5, 0.0);
	glVertex3f(xi + 2, yi - 2.5, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(xi + 3, yi - 1.5, 0.0);
	glVertex3f(xi + 3.5, yi - 1.5, 0.0);
	glVertex3f(xi + 3.5, yi - 2.5, 0.0);
	glVertex3f(xi + 3, yi - 2.5, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(xf - 2, yi - 1.5, 0.0);
	glVertex3f(xf - 3, yi - 1.5, 0.0);
	glVertex3f(xf- 3, yi - 2.5, 0.0);
	glVertex3f(xf - 2, yi - 2.5, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(xf - 2.5, yi - 3.5, 0.0);
	glVertex3f(xf - 3.5, yi - 3.5, 0.0);
	glVertex3f(xf - 3.5, yi - 4.5, 0.0);
	glVertex3f(xf - 2.5, yi - 4.5, 0.0);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(xi+(largo/2), (yi - (largo*1.5)+1), 0.0);
	glVertex3f(xi + (largo / 2), (yi - (largo*1.5)+2), 0.0);
	glVertex3f(xi+((largo+3) / 2), (yi - (largo*1.5)+2), 0.0);
	glVertex3f(xi+((largo+3) / 2), (yi - (largo*1.5)+1), 0.0);
	glEnd();
	if (dibuja == 1)
	{   
		glBegin(GL_LINES);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(linea1[0], linea1[1], 0.0);
		glVertex3f(linea1[2], linea1[3], 0.0);
		glEnd();
	}
	if (dibuja == 2)
	{
		recorta(linea1, xi, xf, yi, yf);
	}

	
	
	glFlush();
}

void reshape ( int width , int height )   // Creamos funcion Reshape
{
	if (height==0)										// Prevenir division entre cero
	{
		height=1;
	}

	glViewport(0,0,width,height);

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Ortogonal
	glOrtho(-30,30,-30,30,-10,10);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();									
}
void keyboard(unsigned char key, int x, int y)  // Create Keyboard Function
{
	switch (key) {
	case 'q':
	case 'Q':
		transZ += 0.3f;
		break;
	case 'e':
	case 'E':
		transZ -= 0.3f;
		break;
	case 'a':
	case 'A':
		transX += 0.3f;
		break;
	case 'd':
	case 'D':
		transX -= 0.3f;
		break;
	case 'w':
	case 'W':
		transY += 0.3f;
		break;
	case 's':
	case 'S':
		transY -= 0.3f;
		break;
	case 27:        // Cuando Esc es presionado...
		exit(0);   // Salimos del programa
		break;
	default:        // Cualquier otra
		break;
	}
	glutPostRedisplay();
}

int main ( int argc, char** argv )   // Main Function
{
	//Ventana
	printf("Ingresa las coordenadas iniciales de tu ventana separadas por una coma");
	scanf_s("%f,%f", &xi, &yi);
	printf("Ingresa el largo y el alto de tu ventana separados por una coma");
	scanf_s("%f,%f", &largo, &alto);
	xf = xi + largo;
	yf = yi + alto;
	printf("Ingresa las coordenadas iniciales de la linea1");
	scanf_s("%f,%f", &linea1[0], &linea1[1]);
	printf("Ingresa las coordenadas finales de la linea1");
	scanf_s("%f,%f", &linea1[2], &linea1[3]);
	vector(l1i,l1f, linea1, xi, xf, yi, yf);
	printf("\nLos valores de l1i son:%.0f,%.0f,%.0f,%.0f", l1i[0], l1i[1], l1i[2], l1i[3] );
	printf("\nLos valores de l1f son:%.0f,%.0f,%.0f,%.0f", l1f[0], l1f[1], l1f[2], l1f[3]);
	dibuja = oplog(l1i, l1f,linea1);
	printf("dibuja vale %d", dibuja);
  glutInit            (&argc, argv); // Inicializamos OpenGL
  glutInitDisplayMode (GLUT_RGBA | GLUT_SINGLE); // Display Mode (Clores RGB y alpha | Buffer Sencillo )
  glutInitWindowSize  (1000, 700);	// Tamaño de la Ventana
  glutInitWindowPosition (0, 0);	//Posicion de la Ventana
  glutCreateWindow    ("Proyecto 1"); // Nombre de la Ventana
  InitGL ();						// Parametros iniciales de la aplicacion
  glutDisplayFunc     ( display );  //Indicamos a Glut función de dibujo
  glutReshapeFunc     ( reshape );	//Indicamos a Glut función en caso de cambio de tamano
  glutKeyboardFunc	  (keyboard);	//Indicamos a Glut función de manejo de teclado
  glutMainLoop        ( );          // 



  return 0;
}

