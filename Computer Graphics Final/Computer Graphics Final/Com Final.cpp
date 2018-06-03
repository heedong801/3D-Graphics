#include <GL/glut.h>
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Digitalv.h"
#pragma comment(lib, "winmm.lib")  //���� ��
MCI_OPEN_PARMS m_mciOpenParms;
MCI_PLAY_PARMS m_mciPlayParms;
DWORD m_dwDeviceID;
MCI_OPEN_PARMS mciOpen;
MCI_PLAY_PARMS mciPlay;

int dwID;

int Time = 0;  //���� �ð� ����
int half_width;
int half_height;
int bullet_num = 30;
int totalspeed = 100;
int rbullet_num1 = 0;
int rbullet_num2 = 0;
int rbullet_num3 = 0;
int rbullet_num4 = 0;
int rbullet_num5 = 0;
int rbullet_num6 = 0;
int rbullet_num7 = 0;
int rbullet_num8 = 0;
int startflag = 0; //���� ����� ������ 'N'��ư�� �ߺ� �Է��� ���� ���� �÷���
int start = 0;//���� ���� ����(0=���� ���� ��,1=���� ��, 2=���� ��)
int tick1 = 0;
int tick2 = 200;
int tick3 = 400;
int tick4 = 400;
int tick5 = 100;
int tick6 = 150;
int tick7 = 150;
int tick8 = 0;
static int old_x, old_y;

const float sensitivity = 0.009; //���콺 ȸ�� �� ī�޶� ȸ�� �ӵ�
const float walk_speed = 0.8;  //�̵� �ӵ� 

bool bullet_flag = false;
bool robot1_flag = false;
bool robot2_flag = false;
bool robot3_flag = false;
bool robot4_flag = false;
bool robot5_flag = false;
bool robot6_flag = false;
bool robot7_flag = false;
bool robot8_flag = false;
float cxangle = 0.0;
float cyangle = 0.0;
float crossview[3] = { 0, };
float bullet_emission[] = { 0.0,0.0,0.0f };
float robot_emission[] = { 1.0f, 0.1f, 0.1f, 1.0f };
float gun_emission[] = { 0.0f,0.0f,0.0f };
float box_emission[] = { 0.0,0,0.4f };
float box2_emission[] = { 0.0,0.2,0.0f };
float box3_emission[] = { 0.2,0.3,0.0f };
float box4_emission[] = { 0.0,0.3,0.2f };
float cross_emission[] = { 0.0f, 0.5f, 0.0f, 1.0f };
float no_mat[] = { 0.4,0.3,0.3,1.0 };
float temp_pos[3] = { -400, 0, 600 }; //ī�޶� ��ġ
float temp_view[3] = { 0.1f, 0.0f, 0.0f };//ī�޶� ��
float cam_pos[3] = { -400, 100, 600 }; //ī�޶� ��ġ
float cam_view[3] = { 0.1f, 0.0f, 0.0f };//ī�޶� ��
float tick1_pos[3] = { -400, 0, 600 }; // �κ�1 �Ѿ˽� ���� ��ġ
float tick2_pos[3] = { -400, 0, 600 }; // �κ�2 �Ѿ˽� ���� ��ġ
float tick3_pos[3] = { -400, 0, 600 }; // �κ�3 �Ѿ˽� ���� ��ġ
float tick4_pos[3] = { -400, 0, 600 }; // �κ�4 �Ѿ˽� ���� ��ġ
float tick5_pos[3] = { -400, 0, 600 }; // ���� �Ѿ˽� ���� ��ġ
float tick6_pos[3] = { -400, 0, 600 }; // ���� �Ѿ˽� ���� ��ġ
float tick7_pos[3] = { -400, 0, 600 }; // ���� �Ѿ˽� ���� ��ġ
float tick8_pos[3] = { -400, 0, 600 }; // �ʻ�� �Ѿ˽� ���� ��ġ
float temp[3] = { 0, };

typedef struct circle
{
	float x;
	float y;
	float z;
	float r;
}Circle;
typedef struct _Part
{
	float x;
	float y;
	float z;
	float lie;
	float speed;
	BOOL fall;
}Part;

typedef struct rect
{
	float fx;
	float bx;
	float lz;
	float rz;
}RECTobj;
RECTobj firstobj = { 0, };
RECTobj secondobj = { 0, };
RECTobj thirdobj = { 0, };
RECTobj fourthobj = { 0, };
RECTobj fifthobj = { 0, };
RECTobj charobj = { 0, };
Circle bossbullet[10];
Circle bossbullet2[10];

typedef struct _Enemy
{
	int life;		//���� ����
	int lie;         //������ ���� �÷���
					 //ĳ���� ��ġ
	float x;
	float y;
	float z;
	float see[3];      //ĳ���Ͱ� �ٶ󺸴� ���⺤��
	float robotangle;   //ĳ���Ͱ� ���� ������ ����
	float firstangle;   //ĳ���Ͱ� ó�� ���� �ִ� ����
	float shotangle;   //ĳ���� ��ü�¿� ������ ����
	float movedie;      //ĳ���� �׾����� �ڷ� ���� ����
	BOOL moveflag;      //ĳ���� ��ü�¿� ������ �÷���
	BOOL die;         //�׾��� �÷���


	Part particle[300];
}Enemy;

Circle a = { 0, };
Circle b = { 0, };
Circle robotbullet1 = { 0, };
Circle robotbullet2 = { 0, };
Circle robotbullet3 = { 0, };
Circle robotbullet4 = { 0, };
Circle robotbullet5 = { 0, };
Circle robotbullet6 = { 0, };
Circle robotbullet7 = { 0, };




Enemy arr[5];

GLuint bg_arr[5]; //��� �ؽ���
GLuint num_arr[10];   //���� �ؽ���
GLuint roundnum = 1; // ���� ����
GLuint box_arr[3]; //�ڽ� �ؽ���
GLuint partdex;   //��ƼŬ �ε���

void SetupRC();   //�ʱ� ����
void Mouse(int button, int state, int x, int y);
void RegistCallback();  //callback�Լ����� ��Ƴ��� �Լ�
void Keyboard(unsigned char key, int x, int y);  //Ű���� �ݹ� �Լ�
void Display();
void GetNormal(GLfloat* x, GLfloat* y, GLfloat* z);
void LogoDraw();   //���� ���۽� �ΰ� �׸��� �Լ�
void MainTimer(int value);      //���� �ð� �Լ�
void normalize(float *v); //������ǥ�� ����ȭ ��Ű�� �Լ�
void rotate_view(float *view, float angle, float x, float y, float z);  //���콺 ȸ�� �� ȭ�� ��ȯ �Լ�
void motion(int x, int y);  //Ű���� �Է� �� ������ �Լ�
void reshape(int width, int height);  //reshape �ݹ� �Լ�
void camLook();  //���� �� ������ǥ ���� �Լ�
void updateKeys(); //Ű���� ������ 
void SkyBox();    //����� �Ǵ� ������ü ����
void TimeDraw(int x, int y, int z); //�ð� ���
void MyLightInit();  //���� ���� �Լ�
void boxdraw();
void Gameover(); //�������� ȭ��
void Gamestart(); //���ӽ��� ȭ��


int main(int argc, char** argv)
{
	//mciSendString("play data\\bgm.wav", NULL, 0, 0);  //�����
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1200, 600);
	glutCreateWindow("Goinmul");
	SetupRC();
	MyLightInit();  //���� ����
	RegistCallback();  //���� �ݹ��Լ� ȣ��
	glutMainLoop();
	return 0;
}

void init()
{

	Time = 0;  //���� �ð� ����

	bullet_num = 30;
	totalspeed = 100;
	rbullet_num1 = 0;
	rbullet_num2 = 0;
	rbullet_num3 = 0;
	rbullet_num4 = 0;
	rbullet_num5 = 0;
	rbullet_num6 = 0;
	rbullet_num7 = 0;
	startflag = 0; //���� ����� ������ 'N'��ư�� �ߺ� �Է��� ���� ���� �÷���
	start = 0;//���� ���� ����(0=���� ���� ��,1=���� ��, 2=���� ��)
	tick1 = 0;
	tick2 = 200;
	tick3 = 400;
	tick4 = 400;
	tick5 = 100;
	tick6 = 300;
	tick7 = 0;


	bullet_flag = false;
	robot1_flag = false;
	robot2_flag = false;
	robot3_flag = false;
	robot4_flag = false;
	robot5_flag = false;
	robot6_flag = false;
	robot7_flag = false;


	cxangle = 0.0;
	cyangle = 0.0;
	crossview[3] = { 0, };



	temp_pos[0] = -400;
	temp_pos[1] = 0;
	temp_pos[2] = 600;
	//ī�޶� ��ġ
	temp_view[0] = 0.1f;
	temp_view[1] = 0.0f;
	temp_view[2] = 0.0f;
	//ī�޶� ��
	cam_pos[0] = -400;
	cam_pos[1] = 100;
	cam_pos[2] = 600;
	//ī�޶� ��ġ
	cam_view[0] = 0.1f;
	cam_view[1] = 0.0f;
	cam_view[2] = 0.0f;
	//ī�޶� ��
	tick1_pos[0] = -400;
	tick1_pos[1] = 0;
	tick1_pos[2] = 600; // �κ�1 �Ѿ˽� ���� ��ġ
	tick2_pos[0] = -400;
	tick2_pos[1] = 0;
	tick2_pos[2] = 600;
	tick3_pos[0] = -400;
	tick3_pos[1] = 0;
	tick3_pos[2] = 600;
	tick4_pos[0] = -400;
	tick4_pos[1] = 0;
	tick4_pos[2] = 600;
	tick5_pos[0] = -400;
	tick5_pos[1] = 0;
	tick5_pos[2] = 600;
	tick6_pos[0] = -400;
	tick6_pos[1] = 0;
	tick6_pos[2] = 600;
	tick7_pos[0] = -400;
	tick7_pos[1] = 0;
	tick7_pos[2] = 600;

	temp[0] = 0;
	temp[1] = 0;
	temp[2] = 0;






	a = { 0, };
	b = { 0, };
	robotbullet1 = { 0, };
	robotbullet2 = { 0, };
	robotbullet3 = { 0, };
	robotbullet4 = { 0, };

	robotbullet5 = { 0, };
	robotbullet6 = { 0, };
	robotbullet7 = { 0, };
	arr[0] = { 0, };
	arr[1] = { 0, };
	arr[2] = { 0, };
	arr[3] = { 0, };

	SetupRC();
	partdex = 0; //��ƼŬ �ε���
}

void obstacle1()
{
	glPushMatrix();
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, box_arr[0]);
	glBegin(GL_QUADS);
	//ť��
	glMaterialfv(GL_FRONT, GL_EMISSION, box_emission);

	glVertex3f(-200, -400, 800);//�ո�
	glVertex3f(-100, -400, 800);
	glVertex3f(-100, 300, 800);
	glVertex3f(-200, 300, 800);

	glVertex3f(-100, -400, 800); //������
	glVertex3f(-100, -400, 300);
	glVertex3f(-100, 300, 300);
	glVertex3f(-100, 300, 800);

	glVertex3f(-200, 300, 800); // ����
	glVertex3f(-100, 300, 800);
	glVertex3f(-100, 300, 300);
	glVertex3f(-200, 300, 300);

	glVertex3f(-200, -400, 300); // �޸�
	glVertex3f(-200, -400, 800);
	glVertex3f(-200, 300, 800);
	glVertex3f(-200, 300, 300);

	glVertex3f(-100, -400, 300); // �޸�
	glVertex3f(-200, -400, 300);
	glVertex3f(-200, 300, 300);
	glVertex3f(-100, 300, 300);

	glEnd();
	glPopMatrix();
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
}

void obstacle2()
{
	glPushMatrix();
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, box_arr[0]);
	glBegin(GL_QUADS);
	//ť��
	glMaterialfv(GL_FRONT, GL_EMISSION, box2_emission);

	glVertex3f(100, -400, 500);//�ո�
	glVertex3f(200, -400, 500);
	glVertex3f(200, 300, 500);
	glVertex3f(100, 300, 500);

	glVertex3f(200, -400, 500); //������
	glVertex3f(200, -400, -100);
	glVertex3f(200, 300, -100);
	glVertex3f(200, 300, 500);

	glVertex3f(100, 300, 500); // ����
	glVertex3f(200, 300, 500);
	glVertex3f(200, 300, -100);
	glVertex3f(100, 300, -100);

	glVertex3f(100, -400, -100); // �޸�
	glVertex3f(100, -400, 500);
	glVertex3f(100, 300, 500);
	glVertex3f(100, 300, -100);

	glVertex3f(200, -400, -100); // �޸�
	glVertex3f(100, -400, -100);
	glVertex3f(100, 300, -100);
	glVertex3f(200, 300, -100);

	glEnd();
	glPopMatrix();
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
}

void obstacle3()
{
	glPushMatrix();
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, box_arr[0]);
	glBegin(GL_QUADS);
	//ť��
	glMaterialfv(GL_FRONT, GL_EMISSION, box3_emission);

	glVertex3f(1100, -400, 600);//�ո�
	glVertex3f(1200, -400, 600);
	glVertex3f(1200, 300, 600);
	glVertex3f(1100, 300, 600);

	glVertex3f(1200, -400, 600); //������
	glVertex3f(1200, -400, -100);
	glVertex3f(1200, 300, -100);
	glVertex3f(1200, 300, 600);

	glVertex3f(1100, 300, 600); // ����
	glVertex3f(1200, 300, 600);
	glVertex3f(1200, 300, -100);
	glVertex3f(1100, 300, -100);

	glVertex3f(1100, -400, -100); // �޸�
	glVertex3f(1100, -400, 600);
	glVertex3f(1100, 300, 600);
	glVertex3f(1100, 300, -100);

	glVertex3f(1200, -400, -100); // �޸�
	glVertex3f(1100, -400, -100);
	glVertex3f(1100, 300, -100);
	glVertex3f(1200, 300, -100);

	glEnd();
	glPopMatrix();
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
}
void obstacle4()
{
	glPushMatrix();
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, box_arr[0]);
	glBegin(GL_QUADS);
	//ť��
	glMaterialfv(GL_FRONT, GL_EMISSION, box3_emission);

	glVertex3f(1100, -400, 1500);//�ո�
	glVertex3f(1200, -400, 1500);
	glVertex3f(1200, 300, 1500);
	glVertex3f(1100, 300, 1500);

	glVertex3f(1200, -400, 1500); //������
	glVertex3f(1200, -400, 800);
	glVertex3f(1200, 300, 800);
	glVertex3f(1200, 300, 1500);

	glVertex3f(1100, 300, 1500); // ����
	glVertex3f(1200, 300, 1500);
	glVertex3f(1200, 300, 800);
	glVertex3f(1100, 300, 800);

	glVertex3f(1100, -400, 800); // �޸�
	glVertex3f(1100, -400, 1500);
	glVertex3f(1100, 300, 1500);
	glVertex3f(1100, 300, 800);

	glVertex3f(1200, -400, 800); // �޸�
	glVertex3f(1100, -400, 800);
	glVertex3f(1100, 300, 800);
	glVertex3f(1200, 300, 800);

	glEnd();
	glPopMatrix();
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
}

void obstacle5()
{
	glPushMatrix();
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, box_arr[0]);
	glBegin(GL_QUADS);
	//ť��
	glMaterialfv(GL_FRONT, GL_EMISSION, box4_emission);

	glVertex3f(1500, -400, 1000);//�ո�
	glVertex3f(1600, -400, 1000);
	glVertex3f(1600, 300, 1000);
	glVertex3f(1500, 300, 1000);

	glVertex3f(1600, -400, 1000); //������
	glVertex3f(1600, -400, 500);
	glVertex3f(1600, 300, 500);
	glVertex3f(1600, 300, 1000);

	glVertex3f(1500, 300, 1000); // ����
	glVertex3f(1600, 300, 1000);
	glVertex3f(1600, 300, 500);
	glVertex3f(1500, 300, 500);

	glVertex3f(1500, -400, 500); // �޸�
	glVertex3f(1500, -400, 1000);
	glVertex3f(1500, 300, 1000);
	glVertex3f(1500, 300, 500);

	glVertex3f(1600, -400, 500); // �޸�
	glVertex3f(1500, -400, 500);
	glVertex3f(1500, 300, 500);
	glVertex3f(1600, 300, 500);

	glEnd();
	glPopMatrix();
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
}
int Colliderect(Circle* a, RECTobj* b)
{
	if ((a->x >= b->fx) && (a->x <= b->bx) && (a->z >= b->lz) && (a->z <= b->rz))
		return 1;
	else
		return 0;
}
int CollideCircle(Circle* a, Circle* b)
{
	if (abs(sqrt(pow(b->x - a->x, 2) + pow(b->y - a->y, 2) + pow(b->z - a->z, 2))) <= a->r + b->r)
		return 1;
	else
		return 0;
}
void normalize(float *v) //������ǥ�� ����ȭ ��Ű�� �Լ�
{
	float magnitude = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	v[0] /= magnitude;
	v[1] /= magnitude;
	v[2] /= magnitude;
}
void camLook()   //���� �� ������ǥ ���� �Լ�
{
	gluLookAt(
		cam_pos[0], cam_pos[1], cam_pos[2],
		cam_pos[0] + cam_view[0], cam_pos[1] + cam_view[1], cam_pos[2] + cam_view[2],
		0.0f, 1.0f, 0.0f);
}
void rotate_view(float *view, float angle, float x, float y, float z) //���콺 ȸ�� �� ȭ�� ��ȯ �Լ�
{
	float new_x;
	float new_y;
	float new_z;

	float c = cos(angle);
	float s = sin(angle);

	new_x = (x*x*(1 - c) + c)   * view[0];
	new_x += (x*y*(1 - c) - z*s)   * view[1];
	new_x += (x*z*(1 - c) + y*s)   * view[2];

	new_y = (y*x*(1 - c) + z*s)   * view[0];
	new_y += (y*y*(1 - c) + c)   * view[1];
	new_y += (y*z*(1 - c) - x*s)   * view[2];

	new_z = (x*z*(1 - c) - y*s)   * view[0];
	new_z += (y*z*(1 - c) + x*s)   * view[1];
	new_z += (z*z*(1 - c) + c)   * view[2];

	view[0] = new_x;
	view[1] = new_y;
	view[2] = new_z;

	normalize(view);

}
void updateKeys() //Ű���� ������ 
{

	if ((GetAsyncKeyState('W') & 0x8000) || (GetAsyncKeyState('A') & 0x8000) || (GetAsyncKeyState('S') & 0x8000) || (GetAsyncKeyState('D') & 0x8000))
	{
		totalspeed = 10;
	}
	else if (!(GetAsyncKeyState('W') & 0x8000) || !(GetAsyncKeyState('A') & 0x8000) || !(GetAsyncKeyState('S') & 0x8000) || !(GetAsyncKeyState('D') & 0x8000))
	{
		totalspeed = 100;
	}
	if (cam_pos[0]>-490 && cam_pos[0]<3950 && cam_pos[2]>-160 && cam_pos[2]<1300)  //����� �Ǵ� ���� ����� �������� ���ϵ��� ��� ����
	{
		if (GetAsyncKeyState('W')) {
			cam_pos[0] += cam_view[0] * walk_speed;
			cam_pos[2] += cam_view[2] * walk_speed;
		}
		if (GetAsyncKeyState('S')) {
			cam_pos[0] -= cam_view[0] * walk_speed;
			cam_pos[2] -= cam_view[2] * walk_speed;
		}
		if (GetAsyncKeyState('A')) {
			cam_pos[0] += cam_view[2] * walk_speed;
			cam_pos[2] -= cam_view[0] * walk_speed;
		}
		if (GetAsyncKeyState('D')) {
			cam_pos[0] -= cam_view[2] * walk_speed;
			cam_pos[2] += cam_view[0] * walk_speed;
		}
	}



	if (cam_pos[2] <= -160) //���� ���� ���� ���
	{
		if (GetAsyncKeyState('W')) {
			cam_pos[0] -= cam_view[0] * walk_speed;
			cam_pos[2] -= cam_view[2] * walk_speed;
		}
		if (GetAsyncKeyState('S')) {
			cam_pos[0] += cam_view[0] * walk_speed;
			cam_pos[2] += cam_view[2] * walk_speed;
		}
		if (GetAsyncKeyState('A')) {
			cam_pos[0] -= cam_view[2] * walk_speed;
			cam_pos[2] += cam_view[0] * walk_speed;
		}
		if (GetAsyncKeyState('D')) {
			cam_pos[0] += cam_view[2] * walk_speed;
			cam_pos[2] -= cam_view[0] * walk_speed;
		}
	}
	else if (cam_pos[0] >= 3950) //���� ���� ���� ���
	{
		if (GetAsyncKeyState('W')) {
			cam_pos[0] -= cam_view[0] * walk_speed;
			cam_pos[2] -= cam_view[2] * walk_speed;
		}
		if (GetAsyncKeyState('S')) {
			cam_pos[0] += cam_view[0] * walk_speed;
			cam_pos[2] += cam_view[2] * walk_speed;
		}
		if (GetAsyncKeyState('A')) {
			cam_pos[0] -= cam_view[2] * walk_speed;
			cam_pos[2] += cam_view[0] * walk_speed;
		}
		if (GetAsyncKeyState('D')) {
			cam_pos[0] += cam_view[2] * walk_speed;
			cam_pos[2] -= cam_view[0] * walk_speed;
		}
	}
	else if (cam_pos[2] >= 1300) //������ ���� ���� ���
	{
		if (GetAsyncKeyState('W')) {
			cam_pos[0] -= cam_view[0] * walk_speed;
			cam_pos[2] -= cam_view[2] * walk_speed;
		}
		if (GetAsyncKeyState('S')) {
			cam_pos[0] += cam_view[0] * walk_speed;
			cam_pos[2] += cam_view[2] * walk_speed;
		}
		if (GetAsyncKeyState('A')) {
			cam_pos[0] -= cam_view[2] * walk_speed;
			cam_pos[2] += cam_view[0] * walk_speed;
		}
		if (GetAsyncKeyState('D')) {
			cam_pos[0] += cam_view[2] * walk_speed;
			cam_pos[2] -= cam_view[0] * walk_speed;
		}
	}
	else if (cam_pos[0] <= -480) //���� ���� ���� ���
	{
		if (GetAsyncKeyState('W')) {
			cam_pos[0] -= cam_view[0] * walk_speed;
			cam_pos[2] -= cam_view[2] * walk_speed;
		}
		if (GetAsyncKeyState('S')) {
			cam_pos[0] += cam_view[0] * walk_speed;
			cam_pos[2] += cam_view[2] * walk_speed;
		}
		if (GetAsyncKeyState('A')) {
			cam_pos[0] -= cam_view[2] * walk_speed;
			cam_pos[2] += cam_view[0] * walk_speed;
		}
		if (GetAsyncKeyState('D')) {
			cam_pos[0] += cam_view[2] * walk_speed;
			cam_pos[2] -= cam_view[0] * walk_speed;
		}
	}

	//if ((cam_pos[2] <= 820) && (cam_pos[0] >= -200) && (cam_pos[0] <=-100)) //��ֹ� �����ʺ��� �ε��� ���
	//{
	//	if (GetAsyncKeyState('W')) {
	//		cam_pos[0] -= cam_view[0] * walk_speed;
	//		cam_pos[2] -= cam_view[2] * walk_speed;
	//	}
	//	if (GetAsyncKeyState('S')) {
	//		cam_pos[0] += cam_view[0] * walk_speed;
	//		cam_pos[2] += cam_view[2] * walk_speed;
	//	}
	//	if (GetAsyncKeyState('A')) {
	//		cam_pos[0] -= cam_view[2] * walk_speed;
	//		cam_pos[2] += cam_view[0] * walk_speed;
	//	}
	//	if (GetAsyncKeyState('D')) {
	//		cam_pos[0] += cam_view[2] * walk_speed;
	//		cam_pos[2] -= cam_view[0] * walk_speed;
	//	}
	//}
	if ((cam_pos[0] >= -210) && (cam_pos[0] <= -110) && (cam_pos[2] >= 310) && (cam_pos[2] <= 810)) //���� ���� �ε�ģ ���
	{
		if (GetAsyncKeyState('W')) {
			cam_pos[0] -= cam_view[0] * walk_speed;
			cam_pos[2] -= cam_view[2] * walk_speed;
		}
		if (GetAsyncKeyState('S')) {
			cam_pos[0] += cam_view[0] * walk_speed;
			cam_pos[2] += cam_view[2] * walk_speed;
		}
		if (GetAsyncKeyState('A')) {
			cam_pos[0] -= cam_view[2] * walk_speed;
			cam_pos[2] += cam_view[0] * walk_speed;
		}
		if (GetAsyncKeyState('D')) {
			cam_pos[0] += cam_view[2] * walk_speed;
			cam_pos[2] -= cam_view[0] * walk_speed;
		}
	}
	if ((cam_pos[0] >= 90) && (cam_pos[0] <= 210) && (cam_pos[2] >= -110) && (cam_pos[2] <= 510)) //��ֹ�2�� �ε�ģ ���
	{
		if (GetAsyncKeyState('W')) {
			cam_pos[0] -= cam_view[0] * walk_speed;
			cam_pos[2] -= cam_view[2] * walk_speed;
		}
		if (GetAsyncKeyState('S')) {
			cam_pos[0] += cam_view[0] * walk_speed;
			cam_pos[2] += cam_view[2] * walk_speed;
		}
		if (GetAsyncKeyState('A')) {
			cam_pos[0] -= cam_view[2] * walk_speed;
			cam_pos[2] += cam_view[0] * walk_speed;
		}
		if (GetAsyncKeyState('D')) {
			cam_pos[0] += cam_view[2] * walk_speed;
			cam_pos[2] -= cam_view[0] * walk_speed;
		}
	}
	if ((cam_pos[0] >= 1090) && (cam_pos[0] <= 1210) && (cam_pos[2] >= -110) && (cam_pos[2] <= 610)) //��ֹ�3�� �ε�ģ ���
	{
		if (GetAsyncKeyState('W')) {
			cam_pos[0] -= cam_view[0] * walk_speed;
			cam_pos[2] -= cam_view[2] * walk_speed;
		}
		if (GetAsyncKeyState('S')) {
			cam_pos[0] += cam_view[0] * walk_speed;
			cam_pos[2] += cam_view[2] * walk_speed;
		}
		if (GetAsyncKeyState('A')) {
			cam_pos[0] -= cam_view[2] * walk_speed;
			cam_pos[2] += cam_view[0] * walk_speed;
		}
		if (GetAsyncKeyState('D')) {
			cam_pos[0] += cam_view[2] * walk_speed;
			cam_pos[2] -= cam_view[0] * walk_speed;
		}
	}
	if ((cam_pos[0] >= 1090) && (cam_pos[0] <= 1210) && (cam_pos[2] >= 810) && (cam_pos[2] <= 1510)) //��ֹ�3�� �ε�ģ ���
	{
		if (GetAsyncKeyState('W')) {
			cam_pos[0] -= cam_view[0] * walk_speed;
			cam_pos[2] -= cam_view[2] * walk_speed;
		}
		if (GetAsyncKeyState('S')) {
			cam_pos[0] += cam_view[0] * walk_speed;
			cam_pos[2] += cam_view[2] * walk_speed;
		}
		if (GetAsyncKeyState('A')) {
			cam_pos[0] -= cam_view[2] * walk_speed;
			cam_pos[2] += cam_view[0] * walk_speed;
		}
		if (GetAsyncKeyState('D')) {
			cam_pos[0] += cam_view[2] * walk_speed;
			cam_pos[2] -= cam_view[0] * walk_speed;
		}
	}
	if ((cam_pos[0] >= 1490) && (cam_pos[0] <= 1610) && (cam_pos[2] >= 510) && (cam_pos[2] <= 1010)) //��ֹ�3�� �ε�ģ ���
	{
		if (GetAsyncKeyState('W')) {
			cam_pos[0] -= cam_view[0] * walk_speed;
			cam_pos[2] -= cam_view[2] * walk_speed;
		}
		if (GetAsyncKeyState('S')) {
			cam_pos[0] += cam_view[0] * walk_speed;
			cam_pos[2] += cam_view[2] * walk_speed;
		}
		if (GetAsyncKeyState('A')) {
			cam_pos[0] -= cam_view[2] * walk_speed;
			cam_pos[2] += cam_view[0] * walk_speed;
		}
		if (GetAsyncKeyState('D')) {
			cam_pos[0] += cam_view[2] * walk_speed;
			cam_pos[2] -= cam_view[0] * walk_speed;
		}
	}
}
void bulletsound()
{

	sndPlaySoundA("data\\gun-shot.wav", SND_ASYNC | SND_NODEFAULT | SND_NOSTOP);

}
void reloadsound()
{
	sndPlaySoundA("data\\guncock.wav", SND_ASYNC | SND_NODEFAULT);
}

void headbreaksound()
{
	sndPlaySoundA("data\\glass-break.wav", SND_ASYNC | SND_NODEFAULT);
}
void doubleshotsound()
{
	if (cam_pos[0] >2000)
		sndPlaySoundA("data\\doubleshot.wav", SND_ASYNC | SND_NODEFAULT);
}

void shotgunsound()
{
	if (cam_pos[0] > 2000)
		sndPlaySoundA("data\\shotgun.wav", SND_ASYNC | SND_NODEFAULT);
}
void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		bullet_flag = true;

		bulletsound();

		temp_pos[0] = cam_pos[0];
		temp_pos[1] = cam_pos[1];
		temp_pos[2] = cam_pos[2];
		temp_view[0] = cam_view[0];
		temp_view[1] = cam_view[1];
		temp_view[2] = cam_view[2];
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{


	}
}
void motion(int x, int y) //Ű���� �Է� �� ������ �Լ�
{
	float rot_x, rot_y;
	float rot_axis[3];

	x -= half_width;
	y -= half_height;

	rot_x = -(float)(x - old_x) * sensitivity;
	rot_y = -(float)(y - old_y) * sensitivity;

	old_x = x;
	old_y = y;

	rotate_view(cam_view, rot_x, 0.0f, 1.0f, 0.0f);  //���콺 �¿� ȸ��

	rot_axis[0] = -cam_view[2];
	rot_axis[1] = 0.0f;
	rot_axis[2] = cam_view[0];

	normalize(rot_axis);

	rotate_view(cam_view, rot_y, rot_axis[0], rot_axis[1], rot_axis[2]);  //���콺 ���� ȸ��
	cxangle = x;
	cyangle = y;
}

void RegistCallback()  //callback�Լ����� ��Ƴ��� �Լ�
{
	//InitDraw();
	glutTimerFunc(totalspeed, MainTimer, 1);
	glutMouseFunc(Mouse);
	glutDisplayFunc(Display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(Keyboard);
	glutPassiveMotionFunc(motion);   //���콺�� ������ �� ���� 
}
void reshape(int width, int height)//reshape �ݹ� �Լ�
{
	half_height = height / 2;
	half_width = width / 2;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, ((float)glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT)), 1.0f, 5000.0f); //���� ����
	glViewport(0, 0, width, height); // ���� ����Ʈ �ʱ�ȭ
}

void Display() //���÷���
{
	glutSetCursor(GLUT_CURSOR_NONE);  //���콺 Ŀ���� ����
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	updateKeys();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(450, 1600 / 800, 20, 2000);   //���� ����
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if (start == 0)             //���� ������
	{
		gluLookAt(300, -300, -100, 300, -300, -200, 0.0f, 1.0f, 0.0f);  //���� ���� �� ȭ���� ��Ÿ���� ���� ������ ��ġ�� �ٶ󺸵��� ����
		Gamestart();//���� ȭ��
		SkyBox();  //����� �Ǵ� ������ü ���� ����
		LogoDraw(); //���� ���� �� �ΰ� �׷���
	}
	if (start == 1)   //���� ��
	{

		GLfloat LightPosition0[] = { cam_pos[0],cam_pos[1],cam_pos[2] };  //���� �� ������ ��ġ
		glLightfv(GL_LIGHT0, GL_POSITION, LightPosition0);  //���� 
		camLook();  //���� ���� �� ���� ����
		SkyBox();
		boxdraw();  //���� ���� ���� ����
	}
	TimeDraw(410, -180, 630);  //���� �ð�(5��)�� ���� �׷���
	glPopMatrix();    //SkyBox ��
	if (start == 2)  //���� ���� ��
		Gameover();//���� ��ȭ��
	glutPostRedisplay();
	glutSwapBuffers();   //���� ����
}
void Keyboard(unsigned char key, int x, int y) //Ű���� ���
{
	switch (key)
	{
	case 'p':   //���� ó�� ����� �Է��ϴ� ��ư
				//sndPlaySound("data\\game.wav", SND_ASYNC);//���� �÷���
				//quiz(103);
		start = 1;
		break;
	case 'r':
		reloadsound();
		break;
	case 'q':
		exit(0);
	}

}
void LogoDraw()  //���� ���۽� �ΰ� �׸��� �Լ�
{
	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_DST_COLOR, GL_ZERO);   //�ΰ��� ����� ������
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, box_arr[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(150, -310, -190);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(450, -310, -190);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(450, -250, -190);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(150, -250, -190);
	glEnd();
	glPopMatrix();
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
	glDisable(GL_BLEND);
}

void Gamestart() //���ӽ��� ȭ��
{
	int i = 0;
	char *text = "Welcome to Our game";

	glPushMatrix();
	glTranslatef(240, -320, -200);
	glColor3f(1, 1, 1);
	glRasterPos2f(0, 0);
	for (i = 0; i<strlen(text); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);  //bitmap��Ʈ ���
	}
	glPopMatrix();

	text = "We are battleground junpro team";

	glPushMatrix();
	glTranslatef(240, -340, -200);
	glColor3f(1, 1, 1);
	glRasterPos2f(0, 0);
	for (i = 0; i<strlen(text); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);  //bitmap��Ʈ ���
	}
	glPopMatrix();

	text = "Computer Graphics Final Project";

	glPushMatrix();
	glTranslatef(240, -240, -200);
	glColor3f(1, 1, 1);
	glRasterPos2f(0, 0);
	for (i = 0; i<strlen(text); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);  //bitmap��Ʈ ���
	}
	glPopMatrix();

	text = "if u want to play the game, Press p key";

	glPushMatrix();
	glTranslatef(240, -360, -200);
	glColor3f(1, 1, 1);
	glRasterPos2f(0, 0);
	for (i = 0; i<strlen(text); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);  //bitmap��Ʈ ���
	}
	glPopMatrix();

	text = "Made by Kimheedong and his friend";

	glPushMatrix();
	glTranslatef(240, -380, -200);
	glColor3f(1, 1, 1);
	glRasterPos2f(0, 0);
	for (i = 0; i<strlen(text); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);  //bitmap��Ʈ ���
	}
	glPopMatrix();
}
void Gameover() //�������� ȭ��
{
	//sndPlaySound("data\\ending2.wav", SND_ASYNC);
	glDisable(GL_LIGHTING); //������ ���ָ鼭 ���� �ؽ��� ���� ��Ÿ��
	glutTimerFunc(6000, exit, 1); //6�� �� ���α׷� ����
}

void MainTimer(int value) //���� �ð� �Լ�
{
	static float tmp[3];
	int check = 0;


	if (bullet_flag)
		bullet_num += 20;
	if (bullet_num > 800) {
		bullet_num = 30;
		bullet_flag = false;
	}
	for (int i = 0; i < 5; i++)
	{
		if (!arr[i].die)
		{
			tmp[0] = cam_pos[0] - arr[i].x;
			tmp[1] = cam_pos[1] - arr[i].y;
			tmp[2] = cam_pos[2] - arr[i].z;
			tmp[3] = cam_pos[2] - arr[i].z;
			GetNormal(&tmp[0], &tmp[1], &tmp[2]);



			arr[i].robotangle = arr[i].see[0] * tmp[0] + arr[i].see[1] * tmp[1] + arr[i].see[2] * tmp[2];
			arr[i].robotangle = 180 / (3.141592) *acos(arr[i].robotangle);

			if (arr[i].x <= cam_pos[0])
				arr[i].robotangle *= -1;
		}
	}

	for (int i = 0; i < 5; i++)
	{
		int tmp;
		a = { arr[i].x,100,arr[i].z,30 };
		b = { temp_pos[0] + bullet_num * temp_view[0], temp_pos[1] + bullet_num * temp_view[1], temp_pos[2] + bullet_num * temp_view[2],1 };

		if (CollideCircle(&a, &b) == 1)
		{
			if (i == 4)
			{
				arr[i].life--;
				if (arr[i].life == 0)
				{
					arr[i].die = TRUE;
					headbreaksound();
				}
			}
			else
			{
				arr[i].die = TRUE;
				headbreaksound();
			}
		}

		if (!arr[i].die)
		{
			if (arr[i].moveflag)
			{
				arr[i].shotangle++;
				if (arr[i].shotangle > 30)
					arr[i].moveflag = FALSE;
			}
			else
			{
				arr[i].shotangle--;
				if (arr[i].shotangle < -30)
					arr[i].moveflag = TRUE;
			}
		}
		else
		{
			check = 0;
			for (int j = 0; j < 300; j++)
			{
				if (arr[i].particle[j].lie == 0)
				{
					if (arr[i].particle[j].x >= 0)
						arr[i].particle[j].x++;
					else
						arr[i].particle[j].x--;
					if (arr[i].particle[j].y >= 0)
						arr[i].particle[j].y++;
					else
						arr[i].particle[j].y--;
					if (arr[i].particle[j].z >= 0)
						arr[i].particle[j].z++;
					else
						arr[i].particle[j].z--;

					if (arr[i].particle[j].x > 10 || arr[i].particle[j].x < -10 || arr[i].particle[j].y > 30 || arr[i].particle[j].y < -30 || arr[i].particle[j].z > 10 || arr[i].particle[j].z < -10)
						arr[i].particle[j].lie = 1;
				}
				else
				{
					if (arr[i].particle[j].y + arr[i].y + 500 >= 0 && arr[i].particle[j].fall == FALSE)
					{
						arr[i].particle[j].y -= 5;

					}
					else if (arr[i].lie != 2)
					{
						check++;
						arr[i].particle[j].y = -400;
						arr[i].particle[j].fall = TRUE;
					}
					if (check == 300)
					{
						if (arr[i].lie != 2)
							arr[i].lie = 1;
					}
				}
			}
			if (arr[i].lie == 1)
			{
				arr[i].movedie -= 5;
				if (arr[i].movedie < -90)
					arr[i].lie = 2;

			}
		}
	}



	if (!arr[0].die)
	{
		tick1++;
		if (tick1 > 500) {
			tick1_pos[0] = cam_pos[0];
			tick1_pos[1] = cam_pos[1];
			tick1_pos[2] = cam_pos[2];
			tick1 = 0;
			robot1_flag = true;
		}
		if (robot1_flag) {
			rbullet_num1 += 5;
			if (rbullet_num1 >= 1200)
			{
				rbullet_num1 = 0;
				robot1_flag = false;
				//printf("%f \n",robotbullet1.z);
			}
		}

	}

	if (!arr[1].die)
	{
		tick2++;
		if (tick2 > 500) {
			tick2_pos[0] = cam_pos[0];
			tick2_pos[1] = cam_pos[1];
			tick2_pos[2] = cam_pos[2];
			tick2 = 0;
			robot2_flag = true;
		}
		if (robot2_flag) {
			rbullet_num2 += 5;
			if (rbullet_num2 >= 1200)
			{
				rbullet_num2 = 0;
				robot2_flag = false;
				//printf("%f \n", robotbullet2.z);
			}
		}
	}
	if (!arr[2].die)
	{
		tick3++;
		if (tick3 > 500) {
			tick3_pos[0] = cam_pos[0];
			tick3_pos[1] = cam_pos[1];
			tick3_pos[2] = cam_pos[2];
			tick3 = 0;
			robot3_flag = true;
		}
		if (robot3_flag) {
			rbullet_num3 += 5;
			if (rbullet_num3 >= 1200)
			{
				rbullet_num3 = 0;
				robot3_flag = false;
				//printf("%f \n", robotbullet3.z);
			}
		}
	}

	if (!arr[3].die)
	{
		tick4++;
		if (tick4 > 500) {
			tick4_pos[0] = cam_pos[0];
			tick4_pos[1] = cam_pos[1];
			tick4_pos[2] = cam_pos[2];
			tick4 = 0;
			robot4_flag = true;
		}
		if (robot4_flag) {
			rbullet_num4 += 5;
			if (rbullet_num4 >= 1200)
			{
				rbullet_num4 = 0;
				robot4_flag = false;
				//printf("%f \n", robotbullet3.z);
			}
		}
	}
	if (!arr[4].die)
	{
		tick5++;
		tick6++;
		tick7++;
		tick8++;
		if (tick5 > 400) {
			doubleshotsound();
			tick5_pos[0] = cam_pos[0];
			tick5_pos[1] = cam_pos[1];
			tick5_pos[2] = cam_pos[2];
			tick5 = 0;
			robot5_flag = true;
		}
		if (tick6 > 400) {
			tick6_pos[0] = cam_pos[0];
			tick6_pos[1] = cam_pos[1];
			tick6_pos[2] = cam_pos[2];
			tick6 = 0;
			robot6_flag = true;
		}
		if (tick8 > 1500)
		{
			shotgunsound();
			tick8_pos[0] = cam_pos[0];
			tick8_pos[1] = cam_pos[1];
			tick8_pos[2] = cam_pos[2];
			for (int i = 0; i < 10; ++i)
			{
				bossbullet[i].x = tick8_pos[0] + rand() % 100 - 200;
				bossbullet[i].y = tick8_pos[1] + rand() % 100 - 200;
				bossbullet[i].z = tick8_pos[2] + rand() % 100 - 200;
			}
			tick8 = 0;
			robot8_flag = true;
		}
		if (robot5_flag) {
			rbullet_num5 += 5;
			if (rbullet_num5 >= 1000)
			{
				rbullet_num5 = 0;
				robot5_flag = false;
				//printf("%f \n", robotbullet3.z);
			}
		}
		if (robot6_flag) {
			rbullet_num6 += 5;
			if (rbullet_num6 >= 1000)
			{
				rbullet_num6 = 0;
				robot6_flag = false;
				//printf("%f \n", robotbullet3.z);
			}
		}
		if (robot8_flag) {
			rbullet_num8 += 5;
			if (rbullet_num8 >= 1000)
			{
				rbullet_num8 = 0;
				robot8_flag = false;
				//printf("%f \n", robotbullet3.z);
			}
		}
	}

	glutTimerFunc(totalspeed, MainTimer, 1);   //1�ʸ���
}
void TimeDraw(int x, int y, int z) // �ð� ���
{
	int s;
	s = (Time % 60) % 10;

	glEnable(GL_BLEND);
	glBlendFunc(GL_DST_COLOR, GL_ZERO);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, num_arr[s]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + 175, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + 175, y + 140, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + 175, y + 140, z - 90);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + 175, y, z - 90);
	glEnd();

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
	glDisable(GL_BLEND);
}
void boss()
{
	glPushMatrix();
	glTranslatef(arr[4].x, 100, arr[4].z);

	if (arr[4].die)
	{
		glPushMatrix();
		for (int j = 0; j < 300; j++)
		{
			glTranslatef(arr[4].particle[j].x, 0, arr[4].particle[j].z);
			glPushMatrix();
			glTranslatef(0, arr[4].particle[j].y, 0);
			glutSolidCube(10);
			glPopMatrix();
		}
		glPopMatrix();
	}

	glRotatef(-arr[4].robotangle, 0, 1, 0);


	glPushMatrix();
	glTranslatef(0, -400, -0);
	glRotatef(arr[4].movedie, 1, 0, 0);
	glTranslatef(0, 400, -0);

	glPushMatrix();
	glTranslatef(0, -200, 0);
	glRotatef(arr[4].shotangle, 0, 0, 1);
	glTranslatef(0, 200, -0);

	//��
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_EMISSION, gun_emission);
	glColor3f(0, 0, 0);
	glTranslated(-30, -10, 160);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 4, 1);
	glutSolidCube(10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(-45, -10, 140);
	glRotatef(90, 0, 0, 1);
	glScalef(1, 4, 1);
	glutSolidCube(10);
	glPopMatrix();
	glMaterialfv(GL_FRONT, GL_EMISSION, robot_emission);

	//��
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(-30, -10, 160);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 4, 1);
	glutSolidCube(10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(-45, -10, 140);
	glRotatef(90, 0, 0, 1);
	glScalef(1, 4, 1);
	glutSolidCube(10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(30, -10, 160);
	glRotatef(90, 1, 0, 0);
	glScalef(1, 4, 1);
	glutSolidCube(10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslated(45, -10, 140);
	glRotatef(90, 0, 0, 1);
	glScalef(1, 4, 1);
	glutSolidCube(10);
	glPopMatrix();

	if (!arr[4].die)
	{
		//����
		glPushMatrix();
		glColor3f(1, 1, 0);
		glTranslated(0, -50, 0);
		glRotated(90, 1, 0, 0);
		glutSolidCone(30, 50, 30, 30);
		glPopMatrix();

		glPushMatrix();
		glColor3f(1, 1, 0);
		glTranslated(0, 15, 0);
		glRotated(-90, 1, 0, 0);
		glutSolidCone(30, 50, 30, 30);
		glPopMatrix();


		//�Ӹ�
		glPushMatrix();
		glColor3f(1, 0, 0);
		glScalef(1, 1.1, 1);
		glutSolidSphere(30, 30, 30);
		glPopMatrix();
	}
	//��
	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(0, -100, 0);
	glScalef(2, 3, 1);
	glutSolidCube(40);
	glPopMatrix();

	//���� ���
	glPushMatrix();
	glColor3f(0, 0, 1);
	glTranslatef(-60, -20, 20);
	glRotatef(-40, 0, 1, 0);
	glRotatef(40, 1, 0, 0);
	glScalef(1, 4, 1);
	glutSolidCube(20);
	glPopMatrix();
	//������ ���
	glPushMatrix();
	glColor3f(0, 0, 1);
	glTranslatef(60, -20, 20);
	glRotatef(40, 0, 1, 0);
	glRotatef(40, 1, 0, 0);
	glScalef(1, 4, 1);
	glutSolidCube(20);
	glPopMatrix();

	//���� �Ϲ�
	glPushMatrix();
	glColor3f(0, 0, 1);
	glTranslatef(-60, 0, 85);
	glRotatef(100, 1, 0, 0);
	glRotatef(-20, 0, 0, 1);
	glScalef(1, 5, 1);
	glutSolidCube(20);
	glPopMatrix();
	//������ �Ϲ�
	glPushMatrix();
	glColor3f(0, 0, 1);
	glTranslatef(60, 0, 85);
	glRotatef(100, 1, 0, 0);
	glRotatef(20, 0, 0, 1);
	glScalef(1, 5, 1);
	glutSolidCube(20);
	glPopMatrix();

	glPopMatrix();

	//���
	glPushMatrix();
	glColor3f(0, 1, 1);
	glTranslatef(0, -180, 0);
	glScalef(4, 2, 2);
	glutSolidCube(20);
	glPopMatrix();

	//���ʾ�����
	glPushMatrix();
	glColor3f(0, 1, 1);
	glTranslatef(-20, -180, -15);
	glScalef(1.2, 1, 1.2);
	glutSolidSphere(18, 30, 30);
	glPopMatrix();
	//���ʾ�����
	glPushMatrix();
	glColor3f(0, 1, 1);
	glTranslatef(20, -180, -15);
	glScalef(1.2, 1, 1.2);
	glutSolidSphere(18, 30, 30);
	glPopMatrix();


	//�� ���Ƹ�
	glPushMatrix();
	glColor3f(1, 0, 1);
	glTranslated(30, -230, 20);
	glRotatef(-30, 1, 0, 0);
	glRotatef(10, 0, 0, 1);
	glScalef(1.5, 4.5, 1.5);
	glutSolidCube(20);
	glPopMatrix();

	//���� ���Ƹ�
	glPushMatrix();
	glColor3f(1, 0, 1);
	glTranslated(-30, -230, 20);
	glRotatef(-30, 1, 0, 0);
	glRotatef(-10, 0, 0, 1);
	glScalef(1.5, 4.5, 1.5);
	glutSolidCube(20);
	glPopMatrix();

	//�� �ٸ�
	glPushMatrix();
	glColor3f(1, 0, 1);
	glTranslated(25, -325, 10);
	glRotatef(30, 1, 0, 0);
	glRotatef(-10, 0, 0, 1);
	glScalef(1.5, 8, 1.5);
	glutSolidCube(20);
	glPopMatrix();

	//���� �ٸ�
	glPushMatrix();
	glColor3f(1, 0, 1);
	glTranslated(-25, -325, 10);
	glRotatef(30, 1, 0, 0);
	glRotatef(10, 0, 0, 1);
	glScalef(1.5, 8, 1.5);
	glutSolidCube(20);
	glPopMatrix();

	glPopMatrix();

	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glPopMatrix();

}
void robot(float x, float z)
{
	for (int i = 0; i < 4; i++)
	{
		glPushMatrix();
		glTranslatef(arr[i].x, 100, arr[i].z);

		if (arr[i].die)
		{
			glPushMatrix();
			for (int j = 0; j < 300; j++)
			{
				glTranslatef(arr[i].particle[j].x, 0, arr[i].particle[j].z);
				glPushMatrix();
				glTranslatef(0, arr[i].particle[j].y, 0);
				glutSolidCube(10);
				glPopMatrix();
			}
			glPopMatrix();
		}

		glRotatef(-arr[i].robotangle, 0, 1, 0);


		glPushMatrix();
		glTranslatef(0, -400, -0);
		glRotatef(arr[i].movedie, 1, 0, 0);
		glTranslatef(0, 400, -0);

		glPushMatrix();
		glTranslatef(0, -200, 0);
		glRotatef(arr[i].shotangle, 0, 0, 1);
		glTranslatef(0, 200, -0);

		//��
		glPushMatrix();

		glMaterialfv(GL_FRONT, GL_EMISSION, gun_emission);
		glColor3f(0, 0, 0);
		glTranslated(-30, -10, 160);
		glRotatef(90, 1, 0, 0);
		glScalef(1, 4, 1);
		glutSolidCube(10);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0, 0, 0);
		glTranslated(-45, -10, 140);
		glRotatef(90, 0, 0, 1);
		glScalef(1, 4, 1);
		glutSolidCube(10);
		glPopMatrix();
		glMaterialfv(GL_FRONT, GL_EMISSION, robot_emission);

		if (!arr[i].die)
		{
			//�Ӹ�
			glPushMatrix();
			glColor3f(1, 0, 0);
			glScalef(1, 1.1, 1);
			glutSolidSphere(30, 30, 30);
			glPopMatrix();
		}

		//��
		glPushMatrix();
		glColor3f(0, 1, 0);
		glTranslatef(0, -100, 0);
		glScalef(2, 3, 1);
		glutSolidCube(40);
		glPopMatrix();

		//���� ���
		glPushMatrix();
		glColor3f(0, 0, 1);
		glTranslatef(-60, -20, 20);
		glRotatef(-40, 0, 1, 0);
		glRotatef(40, 1, 0, 0);
		glScalef(1, 4, 1);
		glutSolidCube(20);
		glPopMatrix();
		//������ ���
		glPushMatrix();
		glColor3f(0, 0, 1);
		glTranslatef(60, -80, 10);
		glRotatef(25, 0, 0, 1);
		glRotatef(-15, 1, 0, 0);
		glScalef(1, 4, 1);
		glutSolidCube(20);
		glPopMatrix();

		//���� �Ϲ�
		glPushMatrix();
		glColor3f(0, 0, 1);
		glTranslatef(-60, 0, 85);
		glRotatef(100, 1, 0, 0);
		glRotatef(-20, 0, 0, 1);
		glScalef(1, 5, 1);
		glutSolidCube(20);
		glPopMatrix();
		//������ �Ϲ�
		glPushMatrix();
		glColor3f(0, 0, 1);
		glTranslatef(40, -140, 25);
		glRotatef(-45, 0, 0, 1);
		glRotatef(-10, 1, 0, 0);
		glScalef(1, 5, 1);
		glutSolidCube(20);
		glPopMatrix();

		glPopMatrix();

		//���
		glPushMatrix();
		glColor3f(0, 1, 1);
		glTranslatef(0, -180, 0);
		glScalef(4, 2, 2);
		glutSolidCube(20);
		glPopMatrix();

		//���ʾ�����
		glPushMatrix();
		glColor3f(0, 1, 1);
		glTranslatef(-20, -180, -15);
		glScalef(1.2, 1, 1.2);
		glutSolidSphere(18, 30, 30);
		glPopMatrix();
		//���ʾ�����
		glPushMatrix();
		glColor3f(0, 1, 1);
		glTranslatef(20, -180, -15);
		glScalef(1.2, 1, 1.2);
		glutSolidSphere(18, 30, 30);
		glPopMatrix();


		//�� ���Ƹ�
		glPushMatrix();
		glColor3f(1, 0, 1);
		glTranslated(30, -230, 20);
		glRotatef(-30, 1, 0, 0);
		glRotatef(10, 0, 0, 1);
		glScalef(1.5, 4.5, 1.5);
		glutSolidCube(20);
		glPopMatrix();

		//���� ���Ƹ�
		glPushMatrix();
		glColor3f(1, 0, 1);
		glTranslated(-30, -230, 20);
		glRotatef(-30, 1, 0, 0);
		glRotatef(-10, 0, 0, 1);
		glScalef(1.5, 4.5, 1.5);
		glutSolidCube(20);
		glPopMatrix();

		//�� �ٸ�
		glPushMatrix();
		glColor3f(1, 0, 1);
		glTranslated(25, -325, 10);
		glRotatef(30, 1, 0, 0);
		glRotatef(-10, 0, 0, 1);
		glScalef(1.5, 8, 1.5);
		glutSolidCube(20);
		glPopMatrix();

		//���� �ٸ�
		glPushMatrix();
		glColor3f(1, 0, 1);
		glTranslated(-25, -325, 10);
		glRotatef(30, 1, 0, 0);
		glRotatef(10, 0, 0, 1);
		glScalef(1.5, 8, 1.5);
		glutSolidCube(20);
		glPopMatrix();

		glPopMatrix();

		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		glPopMatrix();
	}
}

void boxdraw()// O,X�ڽ� ���
{
	robot(0, 0);
	boss();
	glPushMatrix();
	//glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
	glMaterialfv(GL_FRONT, GL_EMISSION, cross_emission);
	
	glPopMatrix();
	obstacle1();
	obstacle2();
	obstacle3();
	obstacle4();
	obstacle5();
	glPushMatrix();
	glDisable(GL_CULL_FACE);
	//glMaterialfv(GL_FRONT, GL_EMISSION, cross_emission);
	glTranslatef(cam_pos[0] + bullet_num * cam_view[0], cam_pos[1] + bullet_num * cam_view[1], cam_pos[2] + bullet_num * cam_view[2]);
	glScalef(0.1, 0.1, 0.1);

	glutSolidSphere(10, 10, 10);

	glPopMatrix();

	glPushMatrix();
	for (int i = 0; i < 5; ++i)
	{
		glPushMatrix();
		if (i == 0) {
			a = { arr[i].x,100,arr[i].z,0 };

			temp[0] = { tick1_pos[0] - a.x };
			temp[1] = { tick1_pos[1] - a.y };
			temp[2] = { tick1_pos[2] - a.z };

			GetNormal(&temp[0], &temp[1], &temp[2]);
			for (int k = 1; k < rbullet_num1; k += 15)
			{
				glPushMatrix();
				glTranslatef(arr[i].x + k * temp[0], arr[i].y + k * temp[1], arr[i].z + k * temp[2]);
				if ((!arr[i].die) && (rbullet_num1 != 0))
				{
					glMaterialfv(GL_FRONT, GL_EMISSION, robot_emission);
					glutSolidSphere(3, 10, 10);
					glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
				}
				glPopMatrix();
			}
			glTranslatef(arr[i].x + rbullet_num1 * temp[0], arr[i].y + rbullet_num1 * temp[1], arr[i].z + rbullet_num1 * temp[2]);
			if ((!arr[i].die) && (rbullet_num1 != 0))
			{
				glMaterialfv(GL_FRONT, GL_EMISSION, bullet_emission);
				glutSolidSphere(10, 10, 10);
				glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
			}
			else
			{
				rbullet_num1 = 0;
				robot1_flag = false;
			}
			glPopMatrix();
		}
		else if (i == 1) {
			a = { arr[i].x,100,arr[i].z,0 };

			temp[0] = { tick2_pos[0] - a.x };
			temp[1] = { tick2_pos[1] - a.y };
			temp[2] = { tick2_pos[2] - a.z };

			GetNormal(&temp[0], &temp[1], &temp[2]);

			for (int k = 1; k < rbullet_num2; k += 15)
			{
				glPushMatrix();
				glTranslatef(arr[i].x + k * temp[0], arr[i].y + k * temp[1], arr[i].z + k * temp[2]);
				if ((!arr[i].die) && (rbullet_num2 != 0))
				{
					glMaterialfv(GL_FRONT, GL_EMISSION, robot_emission);
					glutSolidSphere(3, 10, 10);
					glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
				}
				glPopMatrix();
			}

			glTranslatef(arr[i].x + rbullet_num2 * temp[0], arr[i].y + rbullet_num2 * temp[1], arr[i].z + rbullet_num2 * temp[2]);
			if ((!arr[i].die) && (rbullet_num2 != 0))
			{
				glMaterialfv(GL_FRONT, GL_EMISSION, bullet_emission);
				glutSolidSphere(10, 10, 10);
				glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
			}
			else
			{
				rbullet_num2 = 0;
				robot2_flag = false;
			}
			glPopMatrix();
		}
		else if (i == 2) {
			a = { arr[i].x,100,arr[i].z,0 };

			temp[0] = { tick3_pos[0] - a.x };
			temp[1] = { tick3_pos[1] - a.y };
			temp[2] = { tick3_pos[2] - a.z };

			GetNormal(&temp[0], &temp[1], &temp[2]);
			for (int k = 1; k < rbullet_num3; k += 15)
			{
				glPushMatrix();
				glTranslatef(arr[i].x + k * temp[0], arr[i].y + k * temp[1], arr[i].z + k * temp[2]);
				if ((!arr[i].die) && (rbullet_num3 != 0))
				{
					glMaterialfv(GL_FRONT, GL_EMISSION, robot_emission);
					glutSolidSphere(3, 10, 10);
					glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
				}
				glPopMatrix();
			}
			glTranslatef(arr[i].x + rbullet_num3 * temp[0], arr[i].y + rbullet_num3 * temp[1], arr[i].z + rbullet_num3 * temp[2]);
			if ((!arr[i].die) && (rbullet_num3 != 0))
			{
				glMaterialfv(GL_FRONT, GL_EMISSION, bullet_emission);
				glutSolidSphere(10, 10, 10);
				glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
			}
			else
			{
				rbullet_num3 = 0;
				robot3_flag = false;
			}
			glPopMatrix();
		}
		else if (i == 3) {
			a = { arr[i].x,100,arr[i].z,0 };

			temp[0] = { tick4_pos[0] - a.x };
			temp[1] = { tick4_pos[1] - a.y };
			temp[2] = { tick4_pos[2] - a.z };

			GetNormal(&temp[0], &temp[1], &temp[2]);
			for (int k = 1; k < rbullet_num4; k += 15)
			{
				glPushMatrix();
				glTranslatef(arr[i].x + k * temp[0], arr[i].y + k * temp[1], arr[i].z + k * temp[2]);
				if ((!arr[i].die) && (rbullet_num4 != 0))
				{
					glMaterialfv(GL_FRONT, GL_EMISSION, robot_emission);
					glutSolidSphere(3, 10, 10);
					glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
				}
				glPopMatrix();
			}
			glTranslatef(arr[i].x + rbullet_num4 * temp[0], arr[i].y + rbullet_num4 * temp[1], arr[i].z + rbullet_num4 * temp[2]);
			if ((!arr[i].die) && (rbullet_num4 != 0))
			{
				glMaterialfv(GL_FRONT, GL_EMISSION, bullet_emission);
				glutSolidSphere(10, 10, 10);
				glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
			}
			else
			{
				rbullet_num4 = 0;
				robot4_flag = false;
			}
			glPopMatrix();
		}
		else if (i == 4) {
			a = { arr[i].x,100,arr[i].z,0 };

			temp[0] = { tick5_pos[0] - a.x };
			temp[1] = { tick5_pos[1] - a.y };
			temp[2] = { tick5_pos[2] - a.z };

			GetNormal(&temp[0], &temp[1], &temp[2]);
			for (int k = 1; k < rbullet_num5; k += 15)
			{
				glPushMatrix();
				glTranslatef(arr[i].x + k * temp[0], arr[i].y + k * temp[1], arr[i].z + k * temp[2]);
				if ((!arr[i].die) && (rbullet_num5 != 0))
				{
					glMaterialfv(GL_FRONT, GL_EMISSION, robot_emission);
					glutSolidSphere(3, 10, 10);
					glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
				}
				glPopMatrix();
			}
			glTranslatef(arr[i].x + rbullet_num5 * temp[0], arr[i].y + rbullet_num5 * temp[1], arr[i].z + rbullet_num5 * temp[2]);
			if ((!arr[i].die) && (rbullet_num5 != 0))
			{
				glMaterialfv(GL_FRONT, GL_EMISSION, bullet_emission);
				glutSolidSphere(10, 10, 10);
				glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
			}
			else
			{
				rbullet_num5 = 0;
				robot5_flag = false;
			}
			glPopMatrix();
			glPushMatrix();
			a = { arr[i].x,100,arr[i].z,0 };

			temp[0] = { tick6_pos[0] - a.x };
			temp[1] = { tick6_pos[1] - a.y };
			temp[2] = { tick6_pos[2] - a.z };

			GetNormal(&temp[0], &temp[1], &temp[2]);
			for (int k = 1; k < rbullet_num6; k += 15)
			{
				glPushMatrix();
				glTranslatef(arr[i].x + k * temp[0], arr[i].y + k * temp[1], arr[i].z + k * temp[2]);
				if ((!arr[i].die) && (rbullet_num6 != 0))
				{
					glMaterialfv(GL_FRONT, GL_EMISSION, robot_emission);
					glutSolidSphere(3, 10, 10);
					glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
				}
				glPopMatrix();
			}
			glTranslatef(arr[i].x + rbullet_num6 * temp[0], arr[i].y + rbullet_num6 * temp[1], arr[i].z + rbullet_num6 * temp[2]);
			if ((!arr[i].die) && (rbullet_num6 != 0))
			{
				glMaterialfv(GL_FRONT, GL_EMISSION, bullet_emission);
				glutSolidSphere(10, 10, 10);
				glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
			}
			else
			{
				rbullet_num6 = 0;
				robot6_flag = false;
			}
			glPopMatrix();
			for (int j = 0; j < 10; ++j)
			{
				glPushMatrix();
				a = { arr[4].x,100,arr[4].z,0 };

				temp[0] = { bossbullet[j].x - a.x };
				temp[1] = { bossbullet[j].y - a.y };
				temp[2] = { bossbullet[j].z - a.z };

				GetNormal(&temp[0], &temp[1], &temp[2]);
				glTranslatef(arr[4].x + rbullet_num8 * temp[0], arr[4].y + rbullet_num8 * temp[1], arr[4].z + rbullet_num8 * temp[2]);
				if ((!arr[4].die) && (rbullet_num8 != 0))
				{
					glMaterialfv(GL_FRONT, GL_EMISSION, bullet_emission);
					glutSolidSphere(10, 10, 10);
					glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
				}
				else
				{
					rbullet_num8 = 0;
					robot8_flag = false;
				}
				glPopMatrix();
			}
		}


	}
	glPopMatrix();

	for (int i = 0; i < 5; ++i)
	{

		if (i == 0) {
			a = { arr[i].x,100,arr[i].z,0 };

			temp[0] = { tick1_pos[0] - a.x };
			temp[1] = { tick1_pos[1] - a.y };
			temp[2] = { tick1_pos[2] - a.z };

			GetNormal(&temp[0], &temp[1], &temp[2]);
			robotbullet1 = { arr[i].x + rbullet_num1 * temp[0], arr[i].y + rbullet_num1 * temp[1], arr[i].z + rbullet_num1 * temp[2],10 };
		}
		else if (i == 1) {
			a = { arr[i].x,100,arr[i].z,0 };

			temp[0] = { tick2_pos[0] - a.x };
			temp[1] = { tick2_pos[1] - a.y };
			temp[2] = { tick2_pos[2] - a.z };

			GetNormal(&temp[0], &temp[1], &temp[2]);
			robotbullet2 = { arr[i].x + rbullet_num2 * temp[0], arr[i].y + rbullet_num2 * temp[1], arr[i].z + rbullet_num2 * temp[2],10 };
		}
		else if (i == 2) {
			a = { arr[i].x,100,arr[i].z,0 };

			temp[0] = { tick3_pos[0] - a.x };
			temp[1] = { tick3_pos[1] - a.y };
			temp[2] = { tick3_pos[2] - a.z };

			GetNormal(&temp[0], &temp[1], &temp[2]);
			robotbullet3 = { arr[i].x + rbullet_num3 * temp[0], arr[i].y + rbullet_num3 * temp[1], arr[i].z + rbullet_num3 * temp[2],10 };
		}
		else if (i == 3) {
			a = { arr[i].x,100,arr[i].z,0 };

			temp[0] = { tick4_pos[0] - a.x };
			temp[1] = { tick4_pos[1] - a.y };
			temp[2] = { tick4_pos[2] - a.z };

			GetNormal(&temp[0], &temp[1], &temp[2]);
			robotbullet4 = { arr[i].x + rbullet_num4 * temp[0], arr[i].y + rbullet_num4 * temp[1], arr[i].z + rbullet_num4 * temp[2],10 };
		}
		else if (i == 4) {
			a = { arr[i].x,100,arr[i].z,0 };

			temp[0] = { tick5_pos[0] - a.x };
			temp[1] = { tick5_pos[1] - a.y };
			temp[2] = { tick5_pos[2] - a.z };

			GetNormal(&temp[0], &temp[1], &temp[2]);
			robotbullet5 = { arr[i].x + rbullet_num5 * temp[0], arr[i].y + rbullet_num5 * temp[1], arr[i].z + rbullet_num5 * temp[2],10 };

			a = { arr[i].x,100,arr[i].z,0 };

			temp[0] = { tick6_pos[0] - a.x };
			temp[1] = { tick6_pos[1] - a.y };
			temp[2] = { tick6_pos[2] - a.z };

			GetNormal(&temp[0], &temp[1], &temp[2]);
			robotbullet6 = { arr[i].x + rbullet_num6 * temp[0], arr[i].y + rbullet_num6 * temp[1], arr[i].z + rbullet_num6 * temp[2],10 };

			for (int j = 0; j < 10; ++j)
			{
				a = { arr[4].x,100,arr[4].z,0 };

				temp[0] = { bossbullet[j].x - a.x };
				temp[1] = { bossbullet[j].y - a.y };
				temp[2] = { bossbullet[j].z - a.z };

				GetNormal(&temp[0], &temp[1], &temp[2]);
				bossbullet2[j] = { arr[4].x + rbullet_num8 * temp[0], arr[4].y + rbullet_num8 * temp[1], arr[4].z + rbullet_num8 * temp[2],10 };

			}
		}
		//printf("%f\n", b.z);
		a = { cam_pos[0],cam_pos[1],cam_pos[2],100 };
		if (!arr[0].die)
		{
			if (CollideCircle(&a, &robotbullet1) == 1)
			{

				//printf("�� ������1 \n");
				start--;
				init();
			}
		}
		if (!arr[1].die)
		{
			if (CollideCircle(&a, &robotbullet2) == 1)
			{

				//printf("�� ������2 \n");
				start--;
				init();
			}
		}
		if (!arr[2].die)
		{
			if (CollideCircle(&a, &robotbullet3) == 1)
			{

				//printf("�� ������3 \n");
				start--;
				init();
			}
		}
		if (!arr[3].die)
		{
			if (CollideCircle(&a, &robotbullet4) == 1)
			{

				//printf("�� ������3 \n");
				start--;
				init();
			}
		}
		if (!arr[4].die)
		{
			if ((CollideCircle(&a, &robotbullet5) == 1) || (CollideCircle(&a, &robotbullet6) == 1))
			{

				//printf("�� ������3 \n");
				start--;
				init();
			}
			for (int j = 0; j < 10; ++j)
			{
				if (CollideCircle(&a, &bossbullet2[j]) == 1)
				{

					//printf("�� ������3 \n");
					start--;
					init();
				}
			}
		}
		firstobj = { -200,-100,300,800 };
		secondobj = { 100,200,-100,500 };
		thirdobj = { 1100,1200,-100,600 };
		fourthobj = { 1100,1200,800,1500 };
		fifthobj = { 1500,1600,500,1000 };
		if (!arr[0].die)
		{
			if (Colliderect(&robotbullet1, &firstobj) == 1)
			{
				printf("�� ���̾� ���׾�~1\n");
				tick1 = 0;
				robot1_flag = false;
				rbullet_num1 = 0;
			}
		}
		if (!arr[1].die)
		{
			if (Colliderect(&robotbullet2, &firstobj) == 1)
			{
				printf("�� ���̾� ���׾�~2\n");
				tick2 = 0;
				robot2_flag = false;
				rbullet_num2 = 0;
			}
		}
		if (!arr[2].die)
		{
			if (Colliderect(&robotbullet3, &firstobj) == 1)
			{
				printf("�� ���̾� ���׾�~3\n");
				tick3 = 0;
				robot3_flag = false;
				rbullet_num3 = 0;
			}
		}
		if (!arr[3].die)
		{
			if (Colliderect(&robotbullet4, &firstobj) == 1)
			{
				printf("�� ���̾� ���׾�~3\n");
				tick4 = 0;
				robot4_flag = false;
				rbullet_num4 = 0;
			}
		}

		if (!arr[0].die)
		{
			if (Colliderect(&robotbullet1, &secondobj) == 1)
			{
				printf("�� ���̾� ���׾�~1\n");
				tick1 = 0;
				robot1_flag = false;
				rbullet_num1 = 0;
			}
		}
		if (!arr[1].die)
		{
			if (Colliderect(&robotbullet2, &secondobj) == 1)
			{
				printf("�� ���̾� ���׾�~2\n");
				tick2 = 0;
				robot2_flag = false;
				rbullet_num2 = 0;
			}
		}
		if (!arr[2].die)
		{
			if (Colliderect(&robotbullet3, &secondobj) == 1)
			{
				printf("�� ���̾� ���׾�~3\n");
				tick3 = 0;
				robot3_flag = false;
				rbullet_num3 = 0;
			}
		}
		if (!arr[3].die)
		{
			if (Colliderect(&robotbullet4, &secondobj) == 1)
			{
				printf("�� ���̾� ���׾�~3\n");
				tick4 = 0;
				robot4_flag = false;
				rbullet_num4 = 0;
			}
		}
		if (!arr[0].die)
		{
			if (Colliderect(&robotbullet1, &thirdobj) == 1)
			{
				printf("�� ���̾� ���׾�~1\n");
				tick1 = 0;
				robot1_flag = false;
				rbullet_num1 = 0;
			}
		}
		if (!arr[1].die)
		{
			if (Colliderect(&robotbullet2, &thirdobj) == 1)
			{
				printf("�� ���̾� ���׾�~2\n");
				tick2 = 0;
				robot2_flag = false;
				rbullet_num2 = 0;
			}
		}
		if (!arr[2].die)
		{
			if (Colliderect(&robotbullet3, &thirdobj) == 1)
			{
				printf("�� ���̾� ���׾�~3\n");
				tick3 = 0;
				robot3_flag = false;
				rbullet_num3 = 0;
			}
		}
		if (!arr[3].die)
		{
			if (Colliderect(&robotbullet4, &thirdobj) == 1)
			{
				printf("�� ���̾� ���׾�~3\n");
				tick4 = 0;
				robot4_flag = false;
				rbullet_num4 = 0;
			}
		}
		if (!arr[0].die)
		{
			if (Colliderect(&robotbullet1, &fourthobj) == 1)
			{
				printf("�� ���̾� ���׾�~1\n");
				tick1 = 0;
				robot1_flag = false;
				rbullet_num1 = 0;
			}
		}
		if (!arr[1].die)
		{
			if (Colliderect(&robotbullet2, &fourthobj) == 1)
			{
				printf("�� ���̾� ���׾�~2\n");
				tick2 = 0;
				robot2_flag = false;
				rbullet_num2 = 0;
			}
		}
		if (!arr[2].die)
		{
			if (Colliderect(&robotbullet3, &fourthobj) == 1)
			{
				printf("�� ���̾� ���׾�~3\n");
				tick3 = 0;
				robot3_flag = false;
				rbullet_num3 = 0;
			}
		}
		if (!arr[3].die)
		{
			if (Colliderect(&robotbullet4, &fourthobj) == 1)
			{
				printf("�� ���̾� ���׾�~3\n");
				tick4 = 0;
				robot4_flag = false;
				rbullet_num4 = 0;
			}
		}
		if (!arr[0].die)
		{
			if (Colliderect(&robotbullet1, &fifthobj) == 1)
			{
				printf("�� ���̾� ���׾�~1\n");
				tick1 = 0;
				robot1_flag = false;
				rbullet_num1 = 0;
			}
		}
		if (!arr[1].die)
		{
			if (Colliderect(&robotbullet2, &fifthobj) == 1)
			{
				printf("�� ���̾� ���׾�~2\n");
				tick2 = 0;
				robot2_flag = false;
				rbullet_num2 = 0;
			}
		}
		if (!arr[2].die)
		{
			if (Colliderect(&robotbullet3, &fifthobj) == 1)
			{
				printf("�� ���̾� ���׾�~3\n");
				tick3 = 0;
				robot3_flag = false;
				rbullet_num3 = 0;
			}
		}
		if (!arr[3].die)
		{
			if (Colliderect(&robotbullet4, &fifthobj) == 1)
			{
				printf("�� ���̾� ���׾�~3\n");
				tick4 = 0;
				robot4_flag = false;
				rbullet_num4 = 0;
			}
		}
	}


	firstobj = { -200,-100,300,800 };
	secondobj = { 100,200,-100,500 };
	thirdobj = { 1100,1200,-100,600 };
	if (Colliderect(&b, &firstobj) == 1)
	{
		//printf("�浹�ǳ�?\n");
		bullet_flag = false;
		bullet_num = 30;
	}
	if (Colliderect(&b, &secondobj) == 1)
	{
		//printf("�浹�ǳ�?\n");
		bullet_flag = false;
		bullet_num = 30;
	}
	if (Colliderect(&b, &thirdobj) == 1)
	{
		//printf("�浹�ǳ�?\n");
		bullet_flag = false;
		bullet_num = 30;
	}
	if (Colliderect(&b, &fourthobj) == 1)
	{
		//printf("�浹�ǳ�?\n");
		bullet_flag = false;
		bullet_num = 30;
	}
	if (Colliderect(&b, &fifthobj) == 1)
	{
		//printf("�浹�ǳ�?\n");
		bullet_flag = false;
		bullet_num = 30;
	}
	//printf("%f \t %f \t %f \n", b.x, b.y, b.z, b.r);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}
void SkyBox() //����� �Ǵ� ������ü ����
{
	glPushMatrix();
	//glMaterialfv(GL_FRONT, GL_EMISSION, cross_emission);
	//��� �޸�
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, bg_arr[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-500, -400, -200);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(4000, -400, -200);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(4000, 600, -200);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-500, 600, -200);
	glEnd();

	//��� ����
	glBindTexture(GL_TEXTURE_2D, bg_arr[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-500, 600, 1400);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-500, 600, -200);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(4000, 600, -200);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(4000, 600, 1400);
	glEnd();

	//��� �ظ�
	glBindTexture(GL_TEXTURE_2D, bg_arr[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-500, -400, 1400);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(4000, -400, 1400);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(4000, -400, -200);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-500, -400, -200);
	glEnd();

	//��� ���ʸ�
	glBindTexture(GL_TEXTURE_2D, bg_arr[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-500, 600, 1400);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-500, -400, 1400);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-500, -400, -400);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-500, 600, -400);
	glEnd();

	//��� �����ʸ�
	glBindTexture(GL_TEXTURE_2D, bg_arr[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(4000, 600, 1400);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(4000, 600, -400);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(4000, -400, -400);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(4000, -400, 1400);
	glEnd();

	//��� �ո�
	glBindTexture(GL_TEXTURE_2D, bg_arr[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-500, -400, 1400);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-500, 600, 1400);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(4000, 600, 1400);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(4000, -400, 1400);
	glEnd();

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glPopMatrix();
	//glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
}
void MyLightInit()//���� ���� �Լ�
{
	glEnable(GL_DEPTH_TEST); //���� ���
	glEnable(GL_CULL_FACE);   //���� ����
	glFrontFace(GL_CCW); //�ݽð�
	glCullFace(GL_BACK); //�ĸ� ����

	GLfloat global_ambient[] = { 0.1,0.1,0.1,1.0 };

	GLfloat light0_ambient[] = { 0.5,0.4,0.3,1.0 };
	GLfloat light0_diffuse[] = { 0.8,0.7,0.6,1.0 };
	GLfloat light0_specular[] = { 0.8,1.0,1.0,1.0 };

	GLfloat material_ambient[] = { 0.4,0.4,0.4,1.0 };
	GLfloat material_diffuse[] = { 0.9,0.9,0.9,1.0 };
	GLfloat material_specular[] = { 1.0,1.0,1.0,1.0 };
	GLfloat material_shininess[] = { 25.0 };


	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);

	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, material_shininess);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
}

void GetNormal(GLfloat* x, GLfloat* y, GLfloat* z)
{
	GLfloat normal[3];
	// ����ȭ
	GLfloat l = sqrt(*x * *x + *y * *y + *z * *z);
	*x = *x / l; *y = *y / l; *z = *z / l;
}
void SetupRC()
{
	mciOpen.lpstrElementName = "data\\bgm.wav"; // ���� ��� �Է�
	mciOpen.lpstrDeviceType = "mpegvideo";

	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE,
		(DWORD)(LPVOID)&mciOpen);

	dwID = mciOpen.wDeviceID;



	mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, // play & repeat
		(DWORD)(LPVOID)&m_mciPlayParms);


	//mciSendString("play data\\bgm.wav", NULL, 0, 0);  //�����
	srand((unsigned)time(NULL));

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 300; j++)
		{
			arr[i].particle[j].x = rand() % 10 - 5;
			arr[i].particle[j].y = rand() % 10 - 5;
			arr[i].particle[j].z = rand() % 10 - 5;
			arr[i].particle[j].speed = rand() % 2;
		}
	}
	//ó�� ���� �������� ���� �ִ´�.
	arr[0].x = 400;
	arr[0].y = 100;
	arr[0].z = 0;
	arr[0].see[0] = 0;
	arr[0].see[1] = 0;
	arr[0].see[2] = 1;
	arr[0].moveflag = rand() % 2;;

	//�� ��° ���� ���� (ĳ���� ���۹���)�� ���� �ִ´�.
	arr[1].x = 1200;
	arr[1].y = 100;
	arr[1].z = 700;
	arr[1].see[0] = 0;
	arr[1].see[1] = 0;
	arr[1].see[2] = 1;
	arr[1].moveflag = rand() % 2;

	//�� ��° ���� ������ ���� �ִ´�.
	arr[2].x = 2200;
	arr[2].y = 100;
	arr[2].z = 1200;
	arr[2].see[0] = 0;
	arr[2].see[1] = 0;
	arr[2].see[2] = 1;
	arr[2].moveflag = rand() % 2;


	//�� ��° ���� ������ ���� �ִ´�.
	arr[3].x = 2200;
	arr[3].y = 100;
	arr[3].z = 200;
	arr[3].see[0] = 0;
	arr[3].see[1] = 0;
	arr[3].see[2] = 1;
	arr[3].moveflag = rand() % 2;

	//�ټ� ��° ����
	arr[4].x = 3500;
	arr[4].y = 100;
	arr[4].z = 500;
	arr[4].see[0] = 0;
	arr[4].see[1] = 0;
	arr[4].see[2] = 1;
	arr[4].moveflag = 0;
	arr[4].life = 10;
}