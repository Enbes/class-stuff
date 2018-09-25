// Two-Dimensional Simple Triangle
// Written by dmc 
// last-modified: Wed Sep 19 11:20:44 2012
//
// Designed to demonstrate smooth shading of vertex colors 
// by using a varying parameter in the vertex shader

#include <iostream>
#include <Angel.h>

// How many points are needed to specify the triangle
// Why 6?
const int NumPoints = 44;

// Data storage for our geometry for the triangles
vec3 points[NumPoints];

// Location for shader variable for position of triangle
GLint posLoc;

// This function initializes the particular things for this program
void myinit()
{
  // 4-point star
  points[0]=vec3(100.0/3, 100.0/3, 0.0);
  points[1]=vec3(200.0/3, 100.0/3, 0.0);
  points[2]=vec3(130.0/3, 130.0/3, 0.0);
  points[3]=vec3(100.0/3, 200.0/3, 0.0);
  points[4]=vec3( 70.0/3, 130.0/3, 0.0);
  points[5]=vec3(  0.0/3, 100.0/3, 0.0);
  points[6]=vec3( 70.0/3,  70.0/3, 0.0);
  points[7]=vec3(100.0/3,   0.0/3, 0.0);
  points[8]=vec3(130.0/3,  70.0/3, 0.0);
  points[9]=vec3(200.0/3, 100.0/3, 0.0);

  // point
  points[10]=vec3(100.0, 100.0, 0.0);

  // small 4-point
  points[11]=vec3(100.0/5, 100.0/5, 0.0);
  points[12]=vec3(200.0/5, 100.0/5, 0.0);
  points[13]=vec3(130.0/5, 130.0/5, 0.0);
  points[14]=vec3(100.0/5, 200.0/5, 0.0);
  points[15]=vec3( 70.0/5, 130.0/5, 0.0);
  points[16]=vec3(  0.0/5, 100.0/5, 0.0);
  points[17]=vec3( 70.0/5,  70.0/5, 0.0);
  points[18]=vec3(100.0/5,   0.0/5, 0.0);
  points[19]=vec3(130.0/5,  70.0/5, 0.0);
  points[20]=vec3(200.0/5, 100.0/5, 0.0);

  // point
  points[21]=vec3(100.0, 100.0, 0.0);

  // colors
  for (int i = 22; i < 32; ++i) {
  	points[i]=vec3(1, 1, 1);
  }

  points[32]=vec3(1, 0.1, 0.1);

  for (int i = 33; i < 43; ++i) {
  	points[i]=vec3(1, 1, 0.2);
  }

  points[43]=vec3(0.3, 0.3, 1);

  // attributes
  glClearColor(0.1, 0.1, 0.1, 0.5);
}

// This function initializes the buffers and shaders
void init()
{
  // Create a vertex array object
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
    
  // Create and initialize a buffer object
  GLuint buffer;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

  // Load shaders and use the resulting shader program
  GLuint program = InitShader("vshaderTriangle2.glsl", "fshaderTriangle.glsl");
  glUseProgram(program);

  // Initialize the vertex position attribute from the vertex shader
  GLint loc = glGetAttribLocation(program, "vPosition");
  glEnableVertexAttribArray(loc);
  glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0,
			BUFFER_OFFSET(0));

  // Initialize the colors for the vertices for the fragment shader.
  GLuint col=  glGetAttribLocation(program, "vColor");
  glEnableVertexAttribArray(col);

  // 3 points, each is 3 floating point coordinates after which is the
  // color data.
  // glVertexAttribPointer(col, 3, GL_FLOAT, GL_FALSE, 0,
		// 	BUFFER_OFFSET(3*3*sizeof(float)));

  posLoc = glGetUniformLocation(program, "pos");
  if (posLoc==-1){
    std::cerr << "Unable to find posLoc in shader.\n";
    exit(EXIT_FAILURE);
  }

  // Or you could use the following (since the color data is halfway through the vector):
  glVertexAttribPointer(col, 3, GL_FLOAT, GL_FALSE, 0,
			BUFFER_OFFSET(sizeof(points)/2));
}  

// The only required callback, it must draw everything when called.
extern "C" void display()
{
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_BLEND);
  glEnable(GL_POINT_SMOOTH);  

  glClear(GL_COLOR_BUFFER_BIT);              // clear the window

  // place white 4-point stars
  for (int i = 0; i < 15; ++i) {
    glUniform2f(posLoc, rand()%850, rand()%850);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 10);
  }

  // place red point-stars
  for (int i = 0; i < 15; ++i) {
    glUniform2f(posLoc, rand()%850, rand()%850);          
    glPointSize(5);                         
    glDrawArrays(GL_POINTS, 10, 1);
  }

  // place small yellow 4-point stars
  for (int i = 0; i < 15; ++i) {
    glUniform2f(posLoc, rand()%850, rand()%850);       
    glDrawArrays(GL_TRIANGLE_FAN, 11, 10); 
  }

  // place blue point-stars
  for (int i = 0; i < 15; ++i) {
    glUniform2f(posLoc, rand()%850, rand()%850);          
    glPointSize(5);                         
    glDrawArrays(GL_POINTS, 21, 1);
  }

  glFlush();                                 // clear buffers
}

int main(int argc, char** argv)
{
  // Standard GLUT initialization
  glutInit(&argc,argv);
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA); // default, not needed
  glutInitWindowSize(600,600);                   // 600 x 600 pixel window
  glutInitWindowPosition(0,0);                   // place window top left on display
  glutCreateWindow("Triangle Display");          // window title

  // Add callbacks here, only required is displayFunc
  glutDisplayFunc(display);                      // display callback
						 // invoked when
						 // window opened 

  // Initialize the "magic" that glues all the code together.
  glewInit();

  myinit();             // set attributes
  init();               // set up shaders and display environment
  glutMainLoop();       // enter event loop

  return(EXIT_SUCCESS); // return successful exit code
}
