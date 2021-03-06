#include <windows.h>      
#include <gl/glut.h>      
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define GL_PI  (3.1415f)  
#define oneRad (1.5*GL_PI)

int i = 0;
GLdouble myEyes = 80.0f;

static GLdouble axix = 0.0, axiy = 0.0, z = 0.0;

float fMoonRot = 0.0f;//月球
float fAdamRot = 0.0f;//水星
float fEarthRot = 0.0f;//地球
float fMarsRot = 0.0f;//火星
float fMarsatellite1 = 0.0f;//火星有两颗小卫星
float fMarsatellite2 = 0.0f;//火星有两颗小卫星
float fHesperRot = 0.0f;//金星
float fJupiterRot = 0.0f;//木星
float fSaturnRot = 0.0f;//土星
float fSaturn1 = 0.0f;//土星卫星
float fUranusRot = 0.0f;//天王星
float fNeptuneRot = 0.0f;//海王星


GLfloat  whiteLight[] = { 0.2f,0.2f,0.2f,1.0f };
GLfloat  lightPos[] = { 0.0f,0.0f,0.0f,1.0f };

void sun() {
	//draw the sun 
	glColor3ub(255, 50, 0);
	glRotatef(fEarthRot / 25.4, 0.0f, 1.0f, 0.0f);
	glDisable(GL_LIGHTING);   //turn off    
	glutSolidSphere(25.0f, 200.0f, 200.0f);
	glEnable(GL_LIGHTING);    //turn on   
	glLightfv(GL_LIGHT7, GL_POSITION, lightPos);
}

void Adam()
{
	//绘制水星  
	glPushMatrix();
	glColor3ub(0, 0, 255);
	glRotatef(fAdamRot, 0.0f, 1.0f, 0.0f);
	glTranslatef(30.0f, 0.0f, 0.0f);
	glutSolidSphere(2.0f, 200.0f, 200.0f);       //水星半径是地球的40% 即2  
	fAdamRot += 4.152f;                        //水星公转周期为地球24.08% ,即4.152  
	if (fAdamRot >= 365.0f)
		fAdamRot = 0.0f;
	glPopMatrix();
}

void Hesper() {
	glPushMatrix();
	glColor3ub(255, 215, 0);
	glRotatef(fHesperRot, 0.0f, 1.0f, 0.0f);
	glTranslatef(40.0f, 0.0f, 0.0f);
	//Hesper's radius is 95% of the earth's, 4.75 
	glutSolidSphere(4.75f, 200.0f, 200.0f);
	//Hesper's period of revolution is 61.56% of the earth's, 1.62
	fHesperRot += 1.62f;
	if (fHesperRot >= 365.0f)
		fHesperRot = 0.0f;
	glPopMatrix();
}

void Earth_Moon() {
	//绘制地球,所有运行参数以地球为标准  
	glPushMatrix();
	glColor3ub(0, 0, 255);
	glRotatef(fEarthRot, 0.0f, 1.0f, 0.0f);
	glTranslatef(365.0f, 0.0f, 0.0f);           //设地球周期365  
	glutSolidSphere(5.0f, 20.0f, 20.0f);       //设地球半径5  

	//根据基于地球的坐标进行旋转，并绘制月球      
	glColor3ub(200, 200, 200);
	glRotatef(fMoonRot, 0.0f, 1.0f, 0.0f);
	glTranslatef(5.0f, 0.0f, 0.0f);          // 不断平移
	fMoonRot += 13.3f;                     //月球的公转周期 27.3 天  365/27.3==13.3  
	if (fMoonRot >= 365.0f)                 // 月球半径是地球的3/11   即1.363     
		fMoonRot = 0.0f;
	glutSolidSphere(1.363f, 200.0f, 200.0f);
	glPopMatrix();                         //出栈后值变化，要在下一次循环中才有效   
	fEarthRot += 1.0f;
	if (fEarthRot >= 365.0f)
		fEarthRot = 0.0f;
}


void Mars(){
	//绘制火星
	glPushMatrix();
	glColor3ub(255, 0, 0);
	glRotatef(fMarsRot, 0.0f, 1.0f, 0.0f);
	glTranslatef(65.0f, 0.0f, 0.0f);
	glutSolidSphere(2.65f, 200.0f, 200.0f);       //火星半径是地球的53% 即2.65

	glPushMatrix();
	//根据基于火星的坐标进行旋转，并绘制火卫一   
	glColor3ub(255, 100, 100);
	glRotatef(fMarsatellite1, 0.0f, 1.0f, 0.0f);
	glTranslatef(2.0f, 0.0f, 2.0f);
	fMarsatellite1 += 13.3f;
	if (fMarsatellite1 >= 365.0f)
		fMarsatellite1 = 0.0f;
	glutSolidSphere(0.963f, 200.0f, 200.0f);
	glPopMatrix();

	glPushMatrix();
	//根据基于火星的坐标进行旋转，并绘制火卫二     
	glColor3ub(255, 200, 200);
	glRotatef(fMarsatellite2, 0.0f, 1.0f, 0.0f);
	glTranslatef(-3.0f, 0.0f, -3.0f);
	fMarsatellite2 += 13.3f;
	if (fMarsatellite2 >= 365.0f)
		fMarsatellite2 = 0.0f;
	glutSolidSphere(1.20f, 200.0f, 200.0f);
	glPopMatrix();

	fMarsRot += 0.5f;                           //火星公转周期为地球2倍
	if (fMarsRot >= 365.0f)
		fMarsRot = 0.0f;
	glPopMatrix();
}


void Jupiter(){
	//绘制木星  
	glPushMatrix();
	glColor3ub(200, 100, 0);
	glRotatef(fJupiterRot, 0.0f, 1.0f, 0.0f);
	glTranslatef(100.0f, 0.0f, 0.0f);
	glutSolidSphere(17.0f, 200.0f, 200.0f);       //木星半径是地球的11.21倍 即56.05  为了美观，定为17 

	glPushMatrix();
	glColor3ub(250, 180, 0);
	glRotatef(70.0f, 1.0f, 0.0f, 0.0f);             //环旋转70度 
	glutSolidTorus(1.42, 20, 10, 100);             //效果上看，第一个参数是圆环的宽度
	glPopMatrix();

	fJupiterRot += 0.15f;                     //木星公转周期为地球11.87倍 ,即0.084  为了明显，设为0.15
	if (fJupiterRot >= 365.0f)
		fJupiterRot = 0.0f;
	glPopMatrix();
}

void Saturn(){
	//绘制土星  
	glPushMatrix();
	glColor3ub(73, 60, 32);
	glRotatef(fSaturnRot, 0.0f, 1.0f, 0.0f);
	glTranslatef(148.0f, 0.0f, 0.0f);
	glutSolidSphere(15.0f, 200.0f, 200.0f);       //土星半径是地球的9.45倍 即47.25 为了美观，定为15  
	//绘制土卫一

	glPushMatrix();
	glColor3ub(255, 200, 200);
	glRotatef(fSaturn1, 0.0f, 1.0f, 0.0f);
	glTranslatef(-17.0f, 0.0f, -17.0f);
	fSaturn1 += 6.4f;
	if (fSaturn1 >= 365.0f)
		fSaturn1 = 0.0f;
	glutSolidSphere(1.20f, 200.0f, 200.0f);
	glPopMatrix();

	glPushMatrix();
	glColor3ub(200, 200, 100);
	glRotatef(70.0f, 1.0f, 0.0f, 0.0f);             //环旋转70度 
	glutSolidTorus(1.42, 25, 10, 100);             //效果上看，第一个参数是圆环的宽度
	glPopMatrix();

	fSaturnRot += 0.03f;                        //土星公转周期为地球29.47倍 ,即0.03  
	if (fSaturnRot >= 365.0f)
		fSaturnRot = 0.0f;
	glPopMatrix();
}
void UranusRot(){
	//绘制天王星  
	glPushMatrix();
	glColor3ub(0, 180, 100);
	glRotatef(fUranusRot, 0.0f, 1.0f, 0.0f);
	glTranslatef(202.0f, 0.0f, 0.0f);
	glutSolidSphere(15.0f, 200.0f, 200.0f);       //天王星半径是地球的倍 即4.01，即15    
	glPushMatrix();
	glColor3ub(0, 100, 0);
	glRotatef(150.0f, 1.0f, 0.0f, 0.0f);             //环旋转度 
	glutSolidTorus(1.0, 20, 10, 100);             //效果上看，第一个参数是圆环的宽度
	glPopMatrix();

	fUranusRot += 0.03f;                        //天王星公转周期为地球84.06倍 ,即0.0124  
	if (fUranusRot >= 365.0f)
		fUranusRot = 0.0f;
	glPopMatrix();
}

void Neptune(){
	//绘制海王星  
	glPushMatrix();
	glColor3ub(0, 0, 215);
	glRotatef(fNeptuneRot, 0.0f, 1.0f, 0.0f);
	glTranslatef(240.0f, 0.0f, 0.0f);
	glutSolidSphere(19.45f, 200.0f, 200.0f);       //海王星半径是地球的倍 即3.89，即19.45    
	fNeptuneRot += 2.17f;                       //天王星公转周期为地球46%倍 ,即2.17  
	if (fUranusRot >= 365.0f)
		fNeptuneRot = 0.0f;
	glPopMatrix();
}

void RenderScene(void){
	GLfloat fAspect;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(myEyes, 1.2, 1.0, 6000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -300.0f);
	sun();
	Adam();
	Hesper();
	Earth_Moon();
	Mars();
	Jupiter();
	Saturn();
	UranusRot();
	Neptune();
	glPopMatrix();
	glutSwapBuffers();
	
}








void SetupRC(void) {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_LIGHTING);                             //启动光源      
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight); //使用whiteLght所指定的环境光      
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);         //0号光源的位置      
	glEnable(GL_LIGHT0);
}

int mSecond = 10;
void TimerFunc(int value) {
	glutPostRedisplay();
	glutTimerFunc(mSecond, TimerFunc, 1);
}





void ChangeSize(GLsizei w, GLsizei h) {
	GLfloat fAspect;
	if (h == 0) h = 1;
	glViewport(0, 0, w, h);
	fAspect = (GLfloat)w / (GLfloat)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(myEyes, fAspect, 1.0, 6000);
	glutSwapBuffers();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void myIdle() {
}

void keyFunc(unsigned char ch, int, int) {
	if ('w'==ch  || 'W'==ch ) {
		mSecond += 2;
		if (mSecond < 0)mSecond = -mSecond; 
		glutSwapBuffers();
		printf("mSecond:%d\n", mSecond);
	}
	if ('s' == ch || 'S'==ch) {
		mSecond -= 2;
		if (mSecond < 0)mSecond = -mSecond;
		glutSwapBuffers();
		printf("mSecond:%d\n", mSecond);
	}
	if ('R' == ch || 'r'==ch) {
		mSecond = 10;
		fMoonRot = 0.0f;
		fAdamRot = 0.0f;
		fEarthRot = 0.0f;
		fMarsRot = 0.0f;
		fMarsatellite1 = 0.0f;
		fMarsatellite2 = 0.0f;
		fHesperRot = 0.0f;
		fJupiterRot = 0.0f;
		fSaturnRot = 0.0f;
		fSaturn1 = 0.0f;
		fUranusRot = 0.0f;
		fNeptuneRot = 0.0f;
		system("cls");
		printf("The mSecond (%d) and all rotation angle has been reset!\n", mSecond);
	}

	if ('a' == ch || 'A' == ch) {
		fMoonRot = fMoonRot + oneRad;
		fAdamRot = fAdamRot + oneRad;
		fEarthRot = fEarthRot + oneRad;
		fMarsRot = fMarsRot + oneRad;
		fMarsatellite1 = fMarsatellite1 + oneRad;
		fMarsatellite2 =  fMarsatellite2 + oneRad;
		fHesperRot = fHesperRot + oneRad;
		fJupiterRot =  fJupiterRot + oneRad;
		fSaturnRot =  fSaturnRot + oneRad;
		fSaturn1 = fSaturn1 + oneRad;
		fUranusRot =  fUranusRot + oneRad;
		fNeptuneRot =  fNeptuneRot + oneRad;
		//printf("rotation angle - oneRad\n");
	}

	if ('d' == ch || 'D' == ch) {
		
		fMoonRot = fMoonRot- oneRad;
		fAdamRot = fAdamRot - oneRad;
		fEarthRot = fEarthRot - oneRad;
		fMarsRot = fMarsRot - oneRad;
		fMarsatellite1 = fMarsatellite1 - oneRad;
		fMarsatellite2 = fMarsatellite2 - oneRad;
		fHesperRot = fHesperRot - oneRad;
		fJupiterRot = fJupiterRot - oneRad;
		fSaturnRot = fSaturnRot - oneRad;
		fSaturn1 = fSaturn1 - oneRad;
		fUranusRot = fUranusRot - oneRad;
		fNeptuneRot = fNeptuneRot - oneRad;
		//printf("rotation angle + oneRad\n");
	}

	if ('J' == ch || 'j' == ch) {
		axix += 1.0;
		glutPostRedisplay();
	}
	if ('L' == ch || 'l' == ch) {
		axix -= 1.0;
		glutPostRedisplay();
	}
	
	if ('I' == ch || 'i' == ch) {
		myEyes=myEyes+20.0f;
		glOrtho(0, 0, 0, 0, -1, 1);
		//gluPerspective(myEyes, 1, 1.0, 6000);
		printf("new position of myEyes:%4.1f\n", myEyes);
		glutPostRedisplay();

	}
	if ('K' == ch || 'k' == ch) {
		myEyes=myEyes-20.0f;
		glutSwapBuffers();
		printf("new position of myEyes:%4.1f\n", myEyes);
		glutPostRedisplay();
	}
}


int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Orthographic Projection");
	glutKeyboardFunc(keyFunc);
	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	SetupRC();
	glutTimerFunc(250, TimerFunc, 1);
	glutMainLoop();
	return 0;
}
