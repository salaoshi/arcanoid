/*
Copiright 1999-2002,Sasha Paholkov 
email: Sasha4685847@mail.ru
*/
#include<windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glaux.h>
#include "input.h"
HWND hWnd;
HGLRC hGLRC;
HDC hDC;
unsigned int photo_tex;
unsigned int photo_tex0;
unsigned int photo_tex1;
AUX_RGBImageRec* photo_image;
AUX_RGBImageRec* photo_image0;
AUX_RGBImageRec* photo_image1;
float Qx=0,Qy=0,delta=0.1,left=-1.5,right=1.5,top=1.5,
bottom=-1.5,cameraZ=8.88,cameraX=0,cameraY=0;

int SetWindowPixelFormat()
{
    int m_GLPixelIndex;
    PIXELFORMATDESCRIPTOR pfd;
    pfd.nSize       = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion    = 1;
    pfd.dwFlags   = PFD_DRAW_TO_WINDOW | 
                    PFD_SUPPORT_OPENGL | 
                    PFD_DOUBLEBUFFER;
    pfd.iPixelType     = PFD_TYPE_RGBA;
    pfd.cColorBits     = 32;
    pfd.cRedBits       = 8;
    pfd.cRedShift      = 16;
    pfd.cGreenBits     = 8;
    pfd.cGreenShift    = 8;
    pfd.cBlueBits      = 8;
    pfd.cBlueShift     = 0;
    pfd.cAlphaBits     = 0;
    pfd.cAlphaShift    = 0;
    pfd.cAccumBits     = 64;    
    pfd.cAccumRedBits  = 16;
    pfd.cAccumGreenBits   = 16;
    pfd.cAccumBlueBits    = 16;
    pfd.cAccumAlphaBits   = 0;
    pfd.cDepthBits        = 32;
    pfd.cStencilBits      = 8;
    pfd.cAuxBuffers       = 0;
    pfd.iLayerType        = PFD_MAIN_PLANE;
    pfd.bReserved         = 0;
    pfd.dwLayerMask       = 0;
    pfd.dwVisibleMask     = 0;
    pfd.dwDamageMask      = 0;
    m_GLPixelIndex = ChoosePixelFormat( hDC, &pfd);
    if(m_GLPixelIndex==0) // Let's choose a default index.
    {
     m_GLPixelIndex = 1;    
     if(DescribePixelFormat(hDC,m_GLPixelIndex,sizeof(PIXELFORMATDESCRIPTOR),&pfd)==0)
       return 0;
    }
    if (SetPixelFormat( hDC, m_GLPixelIndex, &pfd)==FALSE)
        return 0;
    return 1;
}

void resize(int width,int heigth)
{
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glViewport(0,0,width,heigth);
//glOrtho(-6,6,-6,6,-2,8);
//glOrtho(-1.5,1.5,-1.5,1.5,2,9);
//glFrustum(-6,6,-6,6,1,6);
gluPerspective(60.0,(GLfloat)heigth/(GLfloat)width,0.1,16.0);
////gluPerspective(60.0,(GLfloat)width/(GLfloat)heigth,0.1,16.0);

gluLookAt(cameraX,cameraY,cameraZ,0,0,0,0,1,0);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
}

void CALLBACK display(void)
{
GLdouble equ[4]={-0.0,0.6,0,1};
GLint i;
GLdouble d=0.2,q=0.13;
static GLint n=0;
static GLdouble  x[10000],y[10000];
static GLdouble coord[3];
static double a=0,b=0,c=0,x1,y1,z1=3.21,dz1=0.022*2,dx1=0.0067,dy1=0.009,x2,y2,z2=2.5,dz2=0.015,dx2=0.023,dy2=0.016;

GLUquadricObj *quadObj;
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
glEnable(GL_TEXTURE_2D);

/*
glTranslated(0,0,3.1);
glRasterPos2d(left,bottom);
glPixelZoom(0.35,0.35);
//glPixelStorei(GL_UNPACK_ALIGNMENT,1);
glDrawPixels(photo_image->sizeX,photo_image->sizeY,GL_RGB,GL_UNSIGNED_BYTE,photo_image->data);
glTranslated(0,0,-3.1);
*/

//glEnable(GL_CLIP_PLANE0);
//glClipPlane(GL_CLIP_PLANE0,equ);
glPointSize(5);
//glLineWidth(2);
glPolygonMode(GL_FRONT,GL_FILL);
//glPolygonMode(GL_BACK,GL_LINE);
//glCullFace(GL_BACK);

x1+=dx1;
if(x1>(right-d)||x1<(left+d))
{
dx1=-dx1;
x1+=dx1*1.6;
}
y1+=dy1;
if(y1>(top-d)||y1<(bottom+d))
{
dy1=-dy1;
y1+=dy1*1.6;
}

z1+=dz1;
/*
if(z1>(6-d)&&(x1>(Qx+q)||x1<(Qx-q)||y1>(Qy+q)||y1<(Qy-q)))
{
x[n]=x1;
y[n]=y1;
if(n!=10000-1)
n+=1;
}
*/
if(z1>(6-d))
 if(x1<(Qx+q)&&x1>(Qx-q)&&y1<(Qy+q)&&y1>(Qy-q))
 //z1=z1
 ;
else
{
x[n]=x1;
y[n]=y1;
if(n!=10000-1)
n+=1;
}
if(z1>(6.0-d)||z1<(1.+d))
{
dz1=-dz1;
z1+=dz1*1.7;
}
a+=0.3;


glColor3d(1,1,1);
//glRotated(a,0,0,1);

glBindTexture(GL_TEXTURE_2D,photo_tex0);

glBegin(GL_POLYGON); 
glColor3d(1,1,1);
glTexCoord2d(0,0);glVertex3f(left,bottom,1);
glTexCoord2d(4,0);glVertex3f(right,bottom,1); 
glTexCoord2d(4,8);glVertex3f(right,top,1);
glTexCoord2d(0,8);glVertex3f(left,top,1); 
glEnd();
//glPopMatrix();
	glBindTexture(GL_TEXTURE_2D,photo_tex);
glBegin(GL_POLYGON); 
glColor3d(1,1,1);
glTexCoord2d(4,0);
glVertex3f(right,top,1); 
glTexCoord2d(4,8);
glVertex3f(right,top,6);
glTexCoord2d(0,8);
glVertex3f(left,top,6); 
glTexCoord2d(0,0);
glVertex3f(left,top,1); 
glEnd();

glBegin(GL_POLYGON); 
//glColor3d(.8,0.7,1);
glTexCoord2d(4,8);
glVertex3f(right,bottom,1); 
glTexCoord2d(0,8);
glVertex3f(left,bottom,1); 
glTexCoord2d(0,0);
glVertex3f(left,bottom,6); 
glTexCoord2d(4,0);
glVertex3f(right,bottom,6);
glEnd();

glBindTexture(GL_TEXTURE_2D,photo_tex0);
glBegin(GL_POLYGON); 
//glColor3d(1,0.7,0);
glTexCoord2d(0,0);
glVertex3f(right,bottom,1); 
glTexCoord2d(8,0);
glVertex3f(right,bottom,6); 
glTexCoord2d(8,8);
glVertex3f(right,top,6); 
glTexCoord2d(0,8);
glVertex3f(right,top,1);
glEnd();

glBegin(GL_POLYGON); 
//glColor3d(0.6,0.6,0);
glTexCoord2d(8,0);
glVertex3f(left,bottom,1); 
glTexCoord2d(8,8);
glVertex3f(left,top,1);
glTexCoord2d(0,8);
glVertex3f(left,top,6); 
glTexCoord2d(0,0);
glVertex3f(left,bottom,6); 
glEnd();
glBindTexture(GL_TEXTURE_2D,photo_tex1);

quadObj=gluNewQuadric();
gluQuadricTexture(quadObj,GL_TRUE);
gluQuadricDrawStyle(quadObj,GLU_FILL);

glPushMatrix();
glTranslated(x1,y1,z1);
glColor3d(0.8,0.1,0.2);
glRotated(180,0,0,1);
glRotated(90,1,0,0);
glRotated(a,0,0,1);
gluSphere(quadObj,d,16,16);
//auxSolidSphere(d);
//auxSolidCube(d);
glPopMatrix();
glDisable(GL_TEXTURE_2D);

glColor3d(1,0,1);
glBegin(GL_LINES); 
if(n!=0)
for(i=0;i<n;i++)
{
glVertex3d(x[i]-0.02*2,y[i],6); 
glVertex3d(x[i]+0.02*2,y[i],6); 
glVertex3d(x[i],y[i]-0.02*2,6); 
glVertex3d(x[i],y[i]+0.02*2,6);
glVertex3d(x[i]-0.015*2,y[i]+0.015*2,6); 
glVertex3d(x[i]+0.015*2,y[i]-0.015*2,6);
glVertex3d(x[i]-0.015*2,y[i]-0.015*2,6); 
glVertex3d(x[i]+0.015*2,y[i]+0.015*2,6);
}
glEnd();

/*
glColor3d(1,0.9,1);
glBegin(GL_LINES); 
glVertex3dv(coord); 
glVertex3d(x1,y1,z1); 
glEnd();
coord[0]=x1;
coord[1]=y1;
coord[2]=z1;
*/
/*
glPushMatrix();
glTranslated(x2,y2,z2);
glColor3d(0.1,0.9,0);
auxSolidSphere(d);
glPopMatrix();
*/

//glEnable(GL_ALPHA_TEST);
//glEnable(GL_BLEND);
//glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

glPushMatrix();
glTranslated(Qx,Qy,0);
glColor4d(1,0.5,1,0.5);
glBegin(GL_POLYGON); 
glVertex3d(-q,-q ,6); 
glVertex3d( q,-q ,6); 
glVertex3d(q, q ,6); 
glVertex3d(-q, q ,6); 
glEnd();
glPopMatrix();
//glDisable(GL_BLEND);
//glDisable(GL_ALPHA_TEST);
glFinish();
SwapBuffers(wglGetCurrentDC());
}
LRESULT CALLBACK WindowFunc(HWND hWnd,UINT msg,WPARAM 
							wParam,LPARAM lParam)
{
//float fogcolor[4]={0.1,0.1,0.1,0.1};
float pos[4]={1,1,7,1};
float dir[3]={0,0,0};

PAINTSTRUCT ps;
switch(msg)
 {
   // сообщение WM_CREATE приходит 
   // один раз при создании окна
   case WM_CREATE:         
   // получаем контекст устройства нашего окна              
   hDC = GetDC(hWnd);    
   // устанавливаем параметры контекста воспроизведения OpenGL
   SetWindowPixelFormat();    
   // создаем контекст воспроизведения OpenGL
   hGLRC = wglCreateContext(hDC);   
   // делаем его текущим
   wglMakeCurrent(hDC, hGLRC);
  // далее см. предыдущий раздел
   	
//	glEnable(GL_FOG);
//	glFogfv(GL_FOG_COLOR,fogcolor);
//	glFogf(GL_FOG_DENSITY,0.1);

    //glEnable(GL_ALPHA_TEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);
    // glEnable(GL_AUTO_NORMAL);
	photo_image=auxDIBImageLoad("tex1.bmp");
		glGenTextures(1,&photo_tex);
		glBindTexture(GL_TEXTURE_2D,photo_tex);
		glTexImage2D(GL_TEXTURE_2D,0,3,
			photo_image->sizeX,
			photo_image->sizeY,
			0,GL_RGB,GL_UNSIGNED_BYTE,
			photo_image->data);	
	
		glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
//	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,/*GL_MODULATE*/GL_DECAL);
//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	
	photo_image0=auxDIBImageLoad("tex.bmp");
	glGenTextures(1,&photo_tex0);
	glBindTexture(GL_TEXTURE_2D,photo_tex0);
	glTexImage2D(GL_TEXTURE_2D,0,3,
			photo_image0->sizeX,
			photo_image0->sizeY,
			0,GL_RGB,GL_UNSIGNED_BYTE,
			photo_image0->data);
	
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);			
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
//	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,/*GL_MODULATE*/GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	photo_image1=auxDIBImageLoad("tex2.bmp");
	glGenTextures(1,&photo_tex1);
	glBindTexture(GL_TEXTURE_2D,photo_tex1);
	glTexImage2D(GL_TEXTURE_2D,0,3,
			photo_image1->sizeX,
			photo_image1->sizeY,
			0,GL_RGB,GL_UNSIGNED_BYTE,
			photo_image1->data);
	
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);			
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
//	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	if(!InitDirectInput (hWnd))
	PostQuitMessage(0);
	break; 
   // это сообщение приходит при уничтожении окна    
   case WM_DESTROY:
   
        // удаляем созданный выше
        // контекст воспроизведения OpenGL
        if (hGLRC) 
        {
            wglMakeCurrent(NULL, NULL);
            wglDeleteContext(hGLRC);
        }
        
        // освобождаем контекст устройства нашего окна
        RemoveDirectInput();
		ReleaseDC(hWnd, hDC);
        PostQuitMessage(0);
        break;
        
   // это сообщение приходит всякий раз,
   // когда нужно перерисовать окно    
   case WM_PAINT:
        BeginPaint(hWnd, &ps);
        display();
        EndPaint(hWnd, &ps);
        break;
        
    
  case WM_SIZE:
     resize( LOWORD(lParam), HIWORD(lParam) );
     break;  
       default:
        return DefWindowProc(hWnd,msg,wParam,lParam);
        }
return 0;
}

int WINAPI WinMain(HINSTANCE hThisInst,
                                   HINSTANCE hPrevInst,
                                   LPSTR str,int nWinMode)
{
MSG msg;
WNDCLASS wcl;
wcl.hInstance=hThisInst;
wcl.lpszClassName = "OpenGLWinClass";
wcl.lpfnWndProc = WindowFunc;
wcl.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
wcl.hIcon = NULL;
wcl.hCursor = LoadCursor(NULL,IDC_ARROW);
wcl.lpszMenuName = NULL;
wcl.cbClsExtra = 0;
wcl.cbWndExtra = 0;
wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
RegisterClass(&wcl);
hWnd = CreateWindow(
  "OpenGLWinClass", 
  "Win32 API S", 
  WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
  00,
  0,
  400,
  400,
  HWND_DESKTOP, NULL,
  hThisInst, NULL);
ShowWindow(hWnd,nWinMode);
UpdateWindow(hWnd);
while(1)
{
  while( PeekMessage(&msg,NULL,0,0,PM_NOREMOVE) ) 
    if(GetMessage(&msg,NULL,0,0))
     { 
      TranslateMessage(&msg);
      DispatchMessage(&msg);
     }
    else
      return 0;
 	ProcessMouse();
	display();
} 
return 0;
}




