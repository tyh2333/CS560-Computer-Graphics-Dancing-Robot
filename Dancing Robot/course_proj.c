#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <GLUT/glut.h>
#define PI 3.14159
#define BODY_HEIGHT 5.0
#define BODY_RADIUS 1.5
#define HEAD_HEIGHT 2.0
#define HEAD_RADIUS 1.5
#define UPPER_ARM_HEIGHT 3.0
#define LOWER_ARM_HEIGHT 2.0
#define UPPER_ARM_RADIUS  0.6
#define LOWER_ARM_RADIUS  0.5
#define LOWER_LEG_HEIGHT 3.0
#define UPPER_LEG_HEIGHT 3.0
#define UPPER_LEG_RADIUS  0.6
#define LOWER_LEG_RADIUS  0.5
#define SHOULDER_RADIUS 0.65
#define JOINT_RADIUS 0.75
GLfloat theta[11] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 180.0, 0.0, 180.0, 0.0};
GLfloat theta_freq[11];
GLfloat theta_max[11];
GLfloat theta_min[11];
GLfloat mat_ambient[] = {0.1, 0.1, 0.1, 1.0};
GLfloat mat_diffuse[] = {0.7, 0.7, 0.7, 1.0};
GLfloat mat_specular[]= {0.4, 0.4, 0.4, 1.0};
GLfloat mat_shininess={100.0};
int flag_dance = 0;
GLUquadricObj*t, /// body
             *gl, /// glass bot
             *h,  /// head
             *lua, /// left  upper aram
             *lla, /// left  lower aram
             *rua, /// right upper aram
             *rla, /// right lower aram
             *lul, /// left  upper leg
             *rul, /// right upper leg
             *lll, /// left  lower leg
             *rll; /// right lower leg
/// 躯干
void body(){
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    ///(*obj, base, top, height, slices, stacks)
    gluCylinder(t, BODY_RADIUS, BODY_RADIUS * 1.5, BODY_HEIGHT,10,10);
    glPopMatrix();
}
/// 头
void head(){
    glPushMatrix();
    glTranslatef(0.0, 0.5 * HEAD_HEIGHT,0.0);
    glScalef(HEAD_RADIUS, HEAD_HEIGHT, HEAD_RADIUS);
    gluSphere(h,1.0,10,10);
    glPopMatrix();
}
/// 头带
void glass_bot(){
    glPushMatrix();
    glTranslatef(0.0, 0.5*HEAD_HEIGHT,0.075);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(gl,HEAD_RADIUS, HEAD_RADIUS, HEAD_HEIGHT/2,10,10);
    glPopMatrix();
}
/// 腰带
void waist(){
    glPushMatrix();
    gluCylinder(gl,1.2 * BODY_RADIUS, 1.2 * BODY_RADIUS, BODY_RADIUS/2,10,10);
    glPopMatrix();
}
/// 肩关节
void shoulder_joints()
{
    glPushMatrix();
    glScalef(SHOULDER_RADIUS, SHOULDER_RADIUS, SHOULDER_RADIUS);
    gluSphere(h,1.0,10,10);
    glPopMatrix();
}
/// 肘关节
void elbow_joints(){
    glPushMatrix();
    glScalef(SHOULDER_RADIUS/1.2, SHOULDER_RADIUS/1.2, SHOULDER_RADIUS/1.2);
    gluSphere(h,1.0,10,10);
    glPopMatrix();
}
/// 手
void palms(){
    glPushMatrix();
    glScalef(SHOULDER_RADIUS/1.3, SHOULDER_RADIUS/1.3, SHOULDER_RADIUS/1.3);
    gluSphere(h,1.0,10,10);
    glPopMatrix();
}
/// 腿关节
void leg_joints(){
    glPushMatrix();
    glScalef(JOINT_RADIUS, JOINT_RADIUS, JOINT_RADIUS);
    gluSphere(h,1.0,10,10);
    glPopMatrix();
}
/// 膝关节
void knee_joints()
{
    glPushMatrix();
    glScalef(JOINT_RADIUS, JOINT_RADIUS, JOINT_RADIUS);
    gluSphere(h,1.0,10,10);
    glPopMatrix();
}
/// 左大臂：圆柱
void left_upper_arm(){
    gluCylinder(lua,UPPER_ARM_RADIUS*1.2, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT,10,10);
}
/// 左小臂：圆柱
void left_lower_arm(){
    gluCylinder(lla,LOWER_ARM_RADIUS*1.1, LOWER_ARM_RADIUS, LOWER_ARM_HEIGHT,10,10);
}
/// 右大臂：圆柱
void right_upper_arm(){
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(rua,UPPER_ARM_RADIUS*1.2, UPPER_ARM_RADIUS, UPPER_ARM_HEIGHT,10,10);
    glPopMatrix();
}
/// 右小臂：圆柱
void right_lower_arm(){
    glPushMatrix();
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluCylinder(rla,LOWER_ARM_RADIUS*1.1, LOWER_ARM_RADIUS, LOWER_ARM_HEIGHT,10,10);
    glPopMatrix();
}
/// 左大腿：圆柱
void left_upper_leg(){
    glColor3f(1.0,0.0,1.0);
    glPushMatrix();
    glRotatef(-120.0, 1.0, 0.0, 0.0);
    gluCylinder(lul,UPPER_LEG_RADIUS*1.2, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT,10,10);
    glPopMatrix();
}
/// 左小腿：圆柱
void left_lower_leg()
{
    glColor3f(1.0,0.0,0.0);
    glPushMatrix();
    glTranslatef(0.0,-0.25,-UPPER_LEG_HEIGHT/2);
    glRotatef(-70.0, 1.0, 0.0, 0.0);
    gluCylinder(lll,LOWER_LEG_RADIUS, LOWER_LEG_RADIUS*1.5, LOWER_LEG_HEIGHT,10,10);
    glPopMatrix();
}
/// 右大腿：圆柱
void right_upper_leg()
{
    glColor3f(1.0f,0.0f,1.0f);
    glPushMatrix();
    glRotatef(-120.0, 1.0, 0.0, 0.0);
    gluCylinder(rul,UPPER_LEG_RADIUS*1.2, UPPER_LEG_RADIUS, UPPER_LEG_HEIGHT,10,10);
    glPopMatrix();
}
/// 右小腿: 圆柱
void right_lower_leg()
{
    glColor3f(1.0,0.0,0.0);
    glPushMatrix();
    glTranslatef(0.0,-0.25,-UPPER_LEG_HEIGHT/2);
    glRotatef(-70.0, 1.0, 0.0, 0.0);
    gluCylinder(rll,LOWER_LEG_RADIUS, LOWER_LEG_RADIUS*1.5, LOWER_LEG_HEIGHT,10,10);
    glPopMatrix();
}
/// 脚
void feets(){
    glPushMatrix();
    glScalef(SHOULDER_RADIUS, SHOULDER_RADIUS, SHOULDER_RADIUS);
    gluSphere(h,1.2,10,10);
    glPopMatrix();
}

void display(void){
    GLfloat rot_x = 0.0, rot_y = 0.0, rot_z = 0.0;
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(0.0, 0.0, 0.0);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);
    /// set camera
    gluLookAt(0.0,0.0,10.0,0.0,0.0,0.0,0.0,1.0,0.0);
    glTranslatef(0.0, 0.0, 10);
    if(flag_dance==1){ rot_x=1.0; rot_y=0.0; rot_z=0.0;}
    if(flag_dance==2){ rot_x=1.0; rot_y=1.0; rot_z=0.0;}
    if(flag_dance==3){ rot_x=1.0; rot_y=1.0; rot_z=1.0;}
    if(flag_dance==4){ rot_x=1.0; rot_y=1.0; rot_z=1.0;}
    if(flag_dance==5){ rot_x=0.0; rot_y=0.0; rot_z=0.0;}
    if(flag_dance==6){ rot_x=0.0; rot_y=1.0; rot_z=0.0;}
    if(flag_dance==7){ rot_x=0.0; rot_y=1.0; rot_z=1.0;}
    if(flag_dance==8){ rot_x=0.0; rot_y=0.0; rot_z=1.0;}
    /// ************************** body 整体转动  *************************
    glTranslatef(0.0, -2.0, 0.0);
    glRotatef(theta[0], 0.0, 1.0, 0.0);
    body(); /// 躯干
    /// ************************** waist  *************************
    glPushMatrix();
    glTranslatef(0.0, 1.0,0.075);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    waist();
    glPopMatrix();
    /// ************************** head  *************************
    glPushMatrix();
    glTranslatef(0.0, BODY_HEIGHT+0.5*HEAD_HEIGHT, 0.0);
    glRotatef(theta[1], 1.0, 0.0, 0.0);
    glRotatef(theta[2], 0.0, 1.0, 0.0);
    glTranslatef(0.0, -0.5*HEAD_HEIGHT, 0.0);
    head(); /// 头
    glass_bot(); /// 头环
    glPopMatrix();
    /// ************************** left and right shoulder joints *************************
    glPushMatrix();
    glTranslatef(1.5*BODY_RADIUS, 0.9 * BODY_HEIGHT, 0.0);
    shoulder_joints();
    glTranslatef(-3.0*BODY_RADIUS, 0.0, 0.0);
    shoulder_joints();
    glPopMatrix();
    /// ************************** left and right leg  joints   *************************
    glPushMatrix();
    glTranslatef(BODY_RADIUS, 0.0, 0.0);
    leg_joints();
    glTranslatef(-2 * BODY_RADIUS, 0.0, 0.0); /// 取2是因为之前向x轴正方向移动了 一个半径长度。
    leg_joints();
    glPopMatrix();
    /// ************************** whole left arm *************************
    glPushMatrix();
    glTranslatef(-(BODY_RADIUS+UPPER_ARM_RADIUS), 0.9*BODY_HEIGHT, 0.0);
    glRotatef(theta[3], rot_x, rot_y, rot_z);
    left_upper_arm(); /// 左上臂
    glTranslatef(0.0, 0.0, UPPER_ARM_HEIGHT);
    elbow_joints();   /// 左胳膊肘
    glRotatef(theta[4], rot_x, rot_y, rot_z);
    left_lower_arm(); /// 左小臂
    glTranslatef(0.0, 0.0, LOWER_ARM_HEIGHT);
    palms();          /// 左手
    glPopMatrix();
    /// ************************** whole right arm *************************
    glPushMatrix();
    glTranslatef(BODY_RADIUS+UPPER_ARM_RADIUS, 0.9*BODY_HEIGHT, 0.0);
    glRotatef(theta[5], rot_x, rot_y, rot_z);
    right_upper_arm(); /// 右大臂
    glTranslatef(0.0, UPPER_ARM_HEIGHT, 0.0);
    elbow_joints(); /// 右胳膊肘
    glRotatef(theta[6], rot_x, rot_y, rot_z);
    glColor3f(1.0,1.0,1.0);
    right_lower_arm(); /// 右小臂
    glTranslatef(0.0, LOWER_ARM_HEIGHT, 0.0);
    palms();  /// 右手
    glPopMatrix();
    /// ************************** whole left leg *************************
    glPushMatrix();
    glTranslatef(-(BODY_RADIUS), 0.1*UPPER_LEG_HEIGHT, 0.0);
    glRotatef(theta[7], rot_x, 0.0, 0.0);
    left_upper_leg(); /// 左大腿
    glTranslatef(0.0, UPPER_LEG_HEIGHT, -1.5);
    knee_joints(); /// 左膝盖
    glTranslatef(0.0, 0.0, 1.5);
    glRotatef(theta[8], 1.0, 0.0, 0.0);
//    glRotatef(theta[8], rot_x, rot_y, rot_z);
    left_lower_leg(); /// 左小腿
    glTranslatef(0.0, LOWER_LEG_HEIGHT, 0.0);
    feets();  /// 左脚
    glPopMatrix();
    /// ************************** whole right leg *************************///
    glPushMatrix();
    glTranslatef((BODY_RADIUS), 0.1*UPPER_LEG_HEIGHT, 0.0);
    glRotatef(theta[9], rot_x, 0.0, 0.0);
    right_upper_leg(); /// 右大腿
    glTranslatef(0.0, UPPER_LEG_HEIGHT, -1.5);
    knee_joints();/// 右膝盖
    glTranslatef(0.0, 0.0, 1.5);
    glRotatef(theta[10], 1.0, 0.0, 0.0);
    right_lower_leg(); /// 右小腿
    glTranslatef(0.0, LOWER_LEG_HEIGHT, 0.0);
    feets();  /// 右脚
    glPopMatrix();
    /// ************************** end *************************///
    glFlush();
    glutSwapBuffers();
    /// glDisable(GL_TEXTURE_2D);
}
/// Caluculate angle
float getAngle(float freq, float min, float max, float time){
    return (max - min) * sin(freq * PI * time) + 0.5 * (max + min);
}

static void idle(void){
    GLfloat seconds = glutGet(GLUT_ELAPSED_TIME)/1000.0;
    srand(time(NULL));
    mat_specular[0] = (rand()% 10) * 0.09;
    mat_specular[1] = (rand()% 10) * 0.06;
    mat_specular[2] = (rand()% 10) * 0.03;
    mat_ambient[0] = (rand()% 10) * 0.09;
    mat_ambient[1] = (rand()% 10) * 0.06;
    mat_ambient[2] = (rand()% 10) * 0.03;
    mat_diffuse[0] = (rand()% 10) * 0.09;
    mat_diffuse[1] = (rand()% 10) * 0.06;
    mat_diffuse[2] = (rand()% 10) * 0.03;
    printf("time : %f s\n", seconds);
//    flag_dance =1;
    if(seconds >= 2.0)  flag_dance =1;
    if(seconds >= 4.0) flag_dance =2;
    if(seconds >= 6.0) flag_dance =3;
    if(seconds >= 8.0) flag_dance =4;
    if(seconds >= 10.0) flag_dance =5;
    if(seconds >= 12.0) flag_dance =6;
    if(seconds >= 14.0) flag_dance =7;
    if(seconds >= 16.0) flag_dance =8;
    if(seconds >= 18.0)  flag_dance =7;
    if(seconds >= 20.0) flag_dance =6;
    if(seconds >= 22.0) flag_dance =5;
    if(seconds >= 24.0) flag_dance =4;
    if(seconds >= 26.0) flag_dance =3;
    if(seconds >= 28.0) flag_dance =2;
    if(seconds >= 30.0) flag_dance =1;
    if(seconds >= 32.0) flag_dance = rand()%8;
    /// moving upper arms and legs
    if((seconds>= 5.0 && seconds<= 10.0)
    || (seconds>= 15.0 && seconds<= 20.0)
    || (seconds>= 25.0 && seconds<= 30.0)){
        theta[3] = getAngle(theta_freq[3], theta_min[3],theta_max[3], seconds);
        theta[5] = getAngle(theta_freq[5], theta_min[5],theta_max[5], seconds);
        theta[7] = getAngle(theta_freq[7], theta_min[7],theta_max[7], seconds);
        theta[9] = getAngle(theta_freq[9], theta_min[9],theta_max[9], seconds);
    }
    /// moving lower arms and legs
    if((seconds>= 0.000001 && seconds<= 6.0)
       || (seconds>= 8.0 && seconds<= 16.0)
       || (seconds>= 18.0 && seconds<= 26.0)
       || (seconds >= 30)) {
        theta[0] = getAngle(theta_freq[0], theta_min[0],theta_max[0], seconds);
        theta[1] = getAngle(theta_freq[1], theta_min[1],theta_max[1], seconds);
        theta[4] = getAngle(theta_freq[4], theta_min[4],theta_max[4], seconds);
        theta[6] = getAngle(theta_freq[6], theta_min[6],theta_max[6], seconds);
        theta[8] = getAngle(theta_freq[8], theta_min[8],theta_max[8], seconds);
        theta[10] = getAngle(theta_freq[10], theta_min[10],theta_max[10], seconds);
    }

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT3);
    glutPostRedisplay();
}
/// My reshape
void reshape(int w, int h){
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-10.0, 10.0, -10.0 * (GLfloat) h / (GLfloat) w,
                10.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-10.0 * (GLfloat) w / (GLfloat) h,
                10.0 * (GLfloat) w / (GLfloat) h, -10.0, 10.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
/// init light things
void light_init(){
    /// light 1
    GLfloat light_ambient1[]={0.0, 0.0, 0.0, 1.0};
    GLfloat light_diffuse1[]={1.0, 1.0, 1.0, 1.0};
    GLfloat light_specular1[]={1.0, 1.0, 1.0, 1.0};
    GLfloat light_position1[]={10.0, 10.0, 10.0, 0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient1);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse1);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular1);
    ///light 2
    GLfloat light_ambient2[]={0.0, 0.0, 0.0, 1.0};
    GLfloat light_diffuse2[]={1.0, 1.0, 1.0, 1.0};
    GLfloat light_specular2[]={1.0, 1.0, 1.0, 1.0};
    GLfloat light_position2[]={-10.0, 10.0, 10.0, 0.0};
    glLightfv(GL_LIGHT3, GL_POSITION, light_position2);
    glLightfv(GL_LIGHT3, GL_AMBIENT, light_ambient2);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, light_diffuse2);
    glLightfv(GL_LIGHT3, GL_SPECULAR, light_specular2);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    /// 指定“目标像素与当前像素在z方向上值大小比较”的函数，符合该函数关系的目标像素才进行绘制，否则对目标像素不予绘制。
    glDepthFunc(GL_LEQUAL); /// GL_LEQUAL,如果输入的深度值小于或等于参考值，则通过
    glEnable(GL_DEPTH_TEST);/// 启用“深度测试”
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
}
/// init rotation angles
void rotate_init(){
    /// Setting the min, max and frequency for body parts
    for(int i = 0;i < 11; i++){
        theta_min[i]  = 0.0;
        theta_max[i]  = 0.0;
        theta_freq[i] = 0.0;
    }
    theta_freq[0] = 0.8; theta_max[0] = 30;    theta_min[0] = -30;
    theta_freq[1] = 2.0; theta_max[1] = 15.0;  theta_min[1] = -5.0;
    theta_freq[3] = 2.0; theta_max[3] = -100.0; theta_min[3] = 0.0;  /// 左大臂
    theta_freq[5] = 2.0; theta_max[5] = 100.0;  theta_min[5] = 0.0;  /// 右大臂
    theta_freq[4] = 2.0; theta_max[4] = -35.0; theta_min[4] = -10.0;/// 左小臂
    theta_freq[6] = 2.0; theta_max[6] = -35.0; theta_min[6] = -10.0;/// 右小臂
    theta_freq[7] = 2.0; theta_max[7] = 200.0; theta_min[7] = 160.0;/// 左大腿
    theta_freq[9] = 2.0; theta_max[9] = 160.0; theta_min[9] = 200.0;/// 右大腿
    theta_freq[8] = 2.0; theta_max[8] = -35.0; theta_min[8] = -10.0;/// 左小腿
    theta_freq[10] = 2.0; theta_max[10] = -35.0; theta_min[10] = -10.0;/// 右小腿

}
/// init quadrics style : GLU_FILL
void style_init(){
    /// allocate quadrics with filled drawing style: GLU_FILL 填充模式
    h   = gluNewQuadric(); gluQuadricDrawStyle(h, GLU_FILL);
    t   = gluNewQuadric(); gluQuadricDrawStyle(t, GLU_FILL);
    gl  = gluNewQuadric(); gluQuadricDrawStyle(gl, GLU_FILL);
    lua = gluNewQuadric(); gluQuadricDrawStyle(lua, GLU_FILL);
    lla = gluNewQuadric(); gluQuadricDrawStyle(lla, GLU_FILL);
    rua = gluNewQuadric(); gluQuadricDrawStyle(rua, GLU_FILL);
    rla = gluNewQuadric(); gluQuadricDrawStyle(rla, GLU_FILL);
    lul = gluNewQuadric(); gluQuadricDrawStyle(lul, GLU_FILL);
    lll = gluNewQuadric(); gluQuadricDrawStyle(lll, GLU_FILL);
    rul = gluNewQuadric(); gluQuadricDrawStyle(rul, GLU_FILL);
    rll = gluNewQuadric(); gluQuadricDrawStyle(rll, GLU_FILL);
}
///********* menu things ***********///
void menu(int id){
    if(id == 0)
        exit(0);
}
void make_menu(){
    glutCreateMenu(menu);
    glutAddMenuEntry("exit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
///********* main function ***********///
int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("dancing robot");
    light_init(); style_init(); rotate_init(); /// init light, style and rotate
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    make_menu();
    glutMainLoop();
    return 0;
}
