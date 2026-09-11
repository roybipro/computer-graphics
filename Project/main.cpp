// Interplanetary Outposts - immediate-mode OpenGL / GLUT project.
// Click the rocket to travel from Jupiter Outpost to Saturn Ring Station.
// macOS build: g++ -std=c++11 -DGL_SILENCE_DEPRECATION main.cpp -o interplanetary -framework OpenGL
// -framework GLUT
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#include <cmath>
#include <cstdlib>

const float PI = 3.14159265f;
const int WORLD_W = 1280, WORLD_H = 720;
int windowW = WORLD_W, windowH = WORLD_H;
float blink = 0, travel = 0, roverPhase = 0;
float astronautOffset = 0;
// 0 = Jupiter scene, 1 = space-flight transition, 2 = Saturn scene.
int scene = 0, travelDirection = 1;
void c(float r, float g, float b) { glColor3f(r, g, b); }
void rect(float x, float y, float X, float Y, float r, float g, float b) {
    c(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(X, y);
    glVertex2f(X, Y);
    glVertex2f(x, Y);
    glEnd();
}
void shape(const float p[][2], int n, float r, float g, float b) {
    c(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) glVertex2f(p[i][0], p[i][1]);
    glEnd();
}
void disk(float x, float y, float rad, float r, float g, float b, int n = 64) {
    c(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        float a = 2 * PI * i / n;
        glVertex2f(x + cos(a) * rad, y + sin(a) * rad);
    }
    glEnd();
}
void oval(float x, float y, float rx, float ry, float r, float g, float b, int n = 64) {
    c(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i < n; i++) {
        float a = 2 * PI * i / n;
        glVertex2f(x + cos(a) * rx, y + sin(a) * ry);
    }
    glEnd();
}
void stroke(float x, float y, float X, float Y, float w, float r, float g, float b) {
    glLineWidth(w);
    c(r, g, b);
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(X, Y);
    glEnd();
}
void text(float x, float y, const char* s, void* font = GLUT_BITMAP_HELVETICA_12) {
    c(.92f, .94f, .98f);
    glRasterPos2f(x, y);
    for (; *s; s++) glutBitmapCharacter(font, *s);
}
void star(float x, float y, float z) { rect(x - z / 2, y - z / 2, x + z / 2, y + z / 2, .94f, .95f, 1); }

void drawSky() {
    rect(0, 0, WORLD_W, WORLD_H, .018f, .02f, .045f);
    rect(0, 260, WORLD_W, 720, .025f, .028f, .06f);
    const float s[][3] = {{66, 660, 3},   {112, 605, 2},  {168, 687, 4},  {230, 640, 2},  {270, 689, 2},
                          {314, 660, 4},  {356, 618, 2},  {412, 685, 3},  {452, 650, 2},  {498, 698, 3},
                          {540, 628, 3},  {584, 680, 2},  {625, 650, 5},  {667, 700, 2},  {711, 624, 2},
                          {755, 680, 4},  {799, 637, 2},  {846, 696, 4},  {892, 648, 2},  {936, 684, 3},
                          {980, 633, 3},  {1024, 700, 2}, {1072, 654, 4}, {1118, 686, 2}, {1170, 640, 3},
                          {1217, 688, 2}, {1248, 612, 4}, {55, 550, 2},   {185, 533, 2},  {337, 550, 2},
                          {470, 525, 3},  {608, 560, 2},  {744, 529, 2},  {870, 549, 2},  {1000, 520, 3},
                          {1136, 553, 2}, {1230, 540, 2}};
    for (unsigned i = 0; i < sizeof(s) / sizeof(s[0]); i++) star(s[i][0], s[i][1], s[i][2]);
    for (int i = 0; i < 4; i++) {
        float x = 390 + i * 160, y = 585 + (i % 2) * 38;
        stroke(x - 10, y, x + 10, y, 1, .9f, .93f, 1);
        stroke(x, y - 10, x, y + 10, 1, .9f, .93f, 1);
        disk(x, y, 2, 1, 1, 1, 12);
    }
}
void drawSun() {
    disk(-18, 570, 150, .14f, .09f, .03f, 10);
    disk(-18, 570, 115, .32f, .20f, .05f, 10);
    disk(-18, 570, 84, .72f, .47f, .11f, 10);
    disk(-18, 570, 55, 1, .77f, .25f, 16);
    disk(-18, 570, 39, 1, .96f, .62f, 28);
}
void drawJupiter() {
    const float x = 405, y = 505, r = 150;
    disk(x, y, r, .77f, .36f, .15f, 90);
    glEnable(GL_STENCIL_TEST);
    glClear(GL_STENCIL_BUFFER_BIT);
    glStencilFunc(GL_ALWAYS, 1, 1);
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    disk(x, y, r, 1, 1, 1, 90);
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glStencilFunc(GL_EQUAL, 1, 1);
    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
    rect(220, 601, 590, 579, .91f, .60f, .38f);
    rect(220, 576, 590, 560, .98f, .79f, .57f);
    rect(220, 557, 590, 531, .76f, .28f, .10f);
    rect(220, 529, 590, 510, .94f, .58f, .32f);
    rect(220, 506, 590, 482, .98f, .78f, .57f);
    rect(220, 479, 590, 456, .76f, .29f, .12f);
    rect(220, 452, 590, 429, .95f, .61f, .38f);
    rect(220, 426, 590, 407, .98f, .77f, .58f);
    disk(456, 475, 33, .69f, .22f, .09f, 36);
    disk(456, 475, 18, .57f, .14f, .06f, 30);
    glDisable(GL_STENCIL_TEST);
    const float a[][2] = {{330, 642}, {407, 654}, {384, 600}, {315, 584}};
    shape(a, 4, .88f, .47f, .25f);
    const float b[][2] = {{455, 600}, {538, 574}, {535, 516}, {468, 534}};
    shape(b, 4, .67f, .26f, .13f);
}
void drawSaturn() {
    const float x = 946, y = 508;
    oval(x, y, 260, 72, .68f, .51f, .33f, 80);
    oval(x, y, 202, 49, .025f, .027f, .055f, 80);
    disk(x, y, 126, .87f, .66f, .38f, 72);
    const float a[][2] = {{860, 602}, {937, 634}, {928, 505}, {862, 463}};
    shape(a, 4, .98f, .79f, .47f);
    const float b[][2] = {{937, 634}, {1045, 603}, {1024, 496}, {928, 505}};
    shape(b, 4, .79f, .59f, .34f);
    const float d[][2] = {{864, 455}, {928, 505}, {954, 382}, {883, 400}};
    shape(d, 4, .95f, .73f, .42f);
    glPushMatrix();
    glTranslatef(x, y, 0);
    glRotatef(-11, 0, 0, 1);
    oval(0, 0, 264, 22, .49f, .35f, .25f, 80);
    oval(0, 0, 222, 13, .91f, .69f, .40f, 80);
    oval(0, 0, 168, 6, .34f, .25f, .20f, 80);
    glPopMatrix();
}
void mountains() {
    rect(0, 0, 1280, 250, .36f, .23f, .29f);
    const float far[][2] = {{0, 220},    {74, 258},   {145, 235},  {207, 276},  {278, 230},
                            {345, 260},  {422, 228},  {512, 268},  {605, 224},  {688, 254},
                            {770, 230},  {846, 265},  {931, 226},  {1014, 260}, {1093, 230},
                            {1170, 270}, {1280, 226}, {1280, 170}, {0, 170}};
    shape(far, 19, .73f, .47f, .45f);
    const float mid[][2] = {{0, 165},    {110, 219},  {193, 165},  {285, 225}, {392, 159}, {478, 214},
                            {563, 157},  {645, 217},  {737, 162},  {828, 216}, {915, 155}, {1010, 212},
                            {1100, 155}, {1190, 218}, {1280, 166}, {1280, 78}, {0, 78}};
    shape(mid, 17, .91f, .58f, .34f);
    const float near[][2] = {{0, 92},    {105, 162},  {188, 82},  {274, 144}, {365, 69}, {459, 143},
                             {566, 57},  {663, 134},  {752, 72},  {841, 145}, {943, 68}, {1028, 132},
                             {1130, 57}, {1210, 139}, {1280, 95}, {1280, 0},  {0, 0}};
    shape(near, 17, .42f, .27f, .39f);
    const float f1[][2] = {{0, 0}, {188, 82}, {274, 0}};
    shape(f1, 3, .27f, .18f, .31f);
    const float f2[][2] = {{274, 0}, {365, 69}, {459, 0}};
    shape(f2, 3, .55f, .33f, .39f);
    const float f3[][2] = {{841, 0}, {943, 68}, {1028, 0}};
    shape(f3, 3, .27f, .18f, .31f);
}
void beacon(float x, float y, float h) {
    stroke(x, y, x, y + h, 3, .20f, .24f, .32f);
    float g = .45f + .55f * (.5f + .5f * sin(blink));
    disk(x, y + h + 5, 6, .95f * g, .06f * g, .03f * g, 18);
}
void engine(float x, float y, float s) {
    const float f[][2] = {{x - 8 * s, y}, {x + 8 * s, y}, {x, y - 42 * s}};
    shape(f, 3, .18f, .78f, .98f);
    const float i[][2] = {{x - 4 * s, y}, {x + 4 * s, y}, {x, y - 25 * s}};
    shape(i, 3, .75f, .97f, 1);
}
void drawJupiterBase() {
    oval(282, 245, 220, 34, .20f, .23f, .32f, 48);
    rect(94, 245, 470, 276, .65f, .67f, .75f);
    const float hull[][2] = {{94, 245}, {470, 245}, {438, 205}, {130, 205}};
    shape(hull, 4, .22f, .25f, .34f);
    const float belly[][2] = {{186, 205}, {382, 205}, {352, 172}, {218, 172}};
    shape(belly, 4, .12f, .15f, .23f);
    disk(282, 280, 104, .66f, .69f, .78f, 40);
    rect(178, 248, 386, 278, .69f, .71f, .78f);
    rect(106, 236, 458, 250, .11f, .14f, .21f);
    for (int i = 0; i < 9; i++) rect(130 + i * 34, 238, 151 + i * 34, 247, 1, .69f, .14f);
    rect(260, 362, 278, 402, .70f, .72f, .80f);
    beacon(269, 402, 37);
    beacon(157, 278, 46);
    beacon(400, 278, 46);
    engine(142, 205, 1);
    engine(282, 172, 1.25f);
    engine(422, 205, 1);
    text(177, 188, "JUPITER OUTPOST");
}
void drawSaturnBase() {
    oval(1004, 245, 142, 34, .16f, .19f, .28f, 48);
    oval(1004, 255, 128, 31, .55f, .59f, .68f, 48);
    oval(1004, 255, 92, 18, .10f, .13f, .20f, 48);
    rect(975, 255, 1033, 276, .39f, .43f, .54f);
    disk(1004, 288, 49, .58f, .62f, .72f, 28);
    rect(955, 251, 1053, 267, .12f, .15f, .23f);
    for (int i = 0; i < 6; i++) rect(958 + i * 16, 254, 968 + i * 16, 261, 1, .69f, .14f);
    beacon(1004, 337, 28);
    engine(932, 235, .65f);
    engine(1075, 235, .65f);
    const float l[][2] = {{925, 276}, {878, 298}, {887, 312}, {939, 287}};
    shape(l, 4, .08f, .22f, .49f);
    const float r[][2] = {{1082, 276}, {1130, 298}, {1122, 312}, {1068, 287}};
    shape(r, 4, .08f, .22f, .49f);
    text(936, 188, "SATURN RING STATION");
}
void drawDrone(float x, float y, float s) {
    oval(x, y, 42 * s, 15 * s, .28f, .31f, .42f, 24);
    const float top[][2] = {{x - 22 * s, y}, {x + 22 * s, y}, {x, y + 25 * s}};
    shape(top, 3, .60f, .64f, .74f);
    rect(x - 23 * s, y - 4 * s, x + 23 * s, y + 3 * s, .12f, .14f, .20f);
    for (int i = 0; i < 3; i++) disk(x - 12 * s + i * 12 * s, y - s, 3 * s, 1, .66f, .12f, 12);
    engine(x, y - 12 * s, .65f * s);
}
void drawRover(float x, float y, float s, float r, float g, float b) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(s, s, 1);
    rect(-58, 4, 58, 29, r, g, b);
    const float top[][2] = {{-38, 29}, {-20, 43}, {31, 43}, {48, 29}};
    shape(top, 4, r + .08f, g + .08f, b + .08f);
    rect(-46, 30, 40, 34, .10f, .18f, .34f);
    stroke(-28, 34, -45, 70, 3, .08f, .24f, .52f);
    stroke(-23, 34, -40, 70, 3, .11f, .36f, .72f);
    beacon(25, 42, 16);
    rect(43, 15, 51, 23, 1, .66f, .12f);
    for (int i = 0; i < 4; i++) {
        disk(-42 + i * 28, 2, 13, .07f, .08f, .12f, 18);
        disk(-42 + i * 28, 2, 5, .50f, .52f, .62f, 18);
    }
    glPopMatrix();
}
void drawAstronaut(float x, float y, float s) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(s, s, 1);
    rect(-16, 0, -4, 48, .66f, .68f, .74f);
    rect(4, 0, 16, 48, .66f, .68f, .74f);
    rect(-19, -3, -3, 5, .08f, .10f, .15f);
    rect(3, -3, 19, 5, .08f, .10f, .15f);
    rect(-22, 46, 22, 108, .83f, .84f, .88f);
    rect(-30, 57, -21, 97, .18f, .20f, .27f);
    rect(21, 57, 30, 97, .18f, .20f, .27f);
    rect(-18, 60, 18, 101, .89f, .89f, .91f);
    rect(-10, 73, -3, 85, .13f, .15f, .21f);
    rect(6, 73, 13, 85, .13f, .15f, .21f);
    disk(0, 125, 27, .87f, .88f, .91f, 24);
    disk(0, 128, 20, .08f, .11f, .16f, 24);
    rect(-21, 103, 21, 111, .22f, .24f, .31f);
    glPopMatrix();
}
void drawSign(float x, float y, const char* label) {
    rect(x, y, x + 176, y + 66, .37f, .39f, .46f);
    rect(x + 7, y + 7, x + 169, y + 58, .06f, .07f, .11f);
    text(x + 20, y + 31, label, GLUT_BITMAP_HELVETICA_18);
}
void drawDish(float x, float y) {
    rect(x - 10, y, x + 10, y + 62, .66f, .68f, .76f);
    const float bowl[][2] = {{x - 38, y + 65}, {x + 20, y + 48}, {x + 44, y + 68}, {x + 7, y + 89}};
    shape(bowl, 4, .70f, .71f, .80f);
    stroke(x + 3, y + 71, x + 40, y + 101, 2, .25f, .27f, .34f);
    disk(x + 42, y + 103, 4, .95f, .07f, .03f, 14);
}
void drawRocket(float x, float y, bool flame, int dir) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef((float)dir, 1, 1);
    const float body[][2] = {{-13, 0}, {13, 0}, {13, 57}, {0, 82}, {-13, 57}};
    shape(body, 5, .87f, .89f, .94f);
    const float nose[][2] = {{-13, 57}, {13, 57}, {0, 82}};
    shape(nose, 3, .92f, .16f, .08f);
    disk(0, 43, 6, .10f, .62f, .90f, 18);
    const float f1[][2] = {{-13, 19}, {-30, 4}, {-13, 4}};
    shape(f1, 3, .18f, .29f, .56f);
    const float f2[][2] = {{13, 19}, {30, 4}, {13, 4}};
    shape(f2, 3, .18f, .29f, .56f);
    if (flame) {
        const float f[][2] = {{-7, 0}, {7, 0}, {0, -30}};
        shape(f, 3, 1, .53f, .06f);
    }
    glPopMatrix();
}
void jupiterGround() {
    rect(0, 0, 1280, 260, .42f, .18f, .13f);
    const float a[][2] = {{0, 245},    {80, 290},   {152, 252},  {240, 305}, {340, 245}, {440, 290},
                          {545, 238},  {650, 285},  {747, 241},  {853, 289}, {950, 245}, {1050, 297},
                          {1150, 244}, {1280, 286}, {1280, 120}, {0, 120}};
    shape(a, 16, .86f, .37f, .19f);
    const float b[][2] = {{0, 160},    {107, 216},  {204, 154},  {316, 209}, {410, 142},
                          {513, 205},  {613, 145},  {723, 213},  {824, 148}, {926, 210},
                          {1030, 140}, {1138, 214}, {1280, 155}, {1280, 0},  {0, 0}};
    shape(b, 15, .50f, .18f, .16f);
}
void saturnGround() {
    rect(0, 0, 1280, 270, .17f, .18f, .31f);
    const float a[][2] = {{0, 242},    {95, 282},   {185, 230},  {280, 278}, {369, 225}, {470, 280},
                          {570, 231},  {670, 276},  {765, 221},  {858, 276}, {950, 226}, {1050, 284},
                          {1158, 225}, {1280, 266}, {1280, 116}, {0, 116}};
    shape(a, 16, .50f, .43f, .63f);
    const float b[][2] = {{0, 142},    {118, 210},  {202, 130},  {312, 204}, {410, 126},
                          {522, 196},  {612, 130},  {722, 208},  {816, 126}, {923, 202},
                          {1017, 125}, {1128, 210}, {1280, 136}, {1280, 0},  {0, 0}};
    shape(b, 15, .27f, .25f, .43f);
    const float f[][2] = {{658, 0}, {816, 126}, {923, 0}};
    shape(f, 3, .65f, .57f, .74f);
}
void shadow(float x, float y, float rx, float ry) { oval(x, y, rx, ry, .13f, .10f, .15f, 40); }
void jupiterSurfaceTexture() {
    // Faceted dune shapes and dark contact shadows give the orange terrain depth.
    const float a[][2] = {{12, 87}, {117, 141}, {207, 91}, {159, 49}};
    shape(a, 4, .64f, .23f, .17f);
    const float b[][2] = {{174, 71}, {296, 140}, {389, 84}, {319, 41}};
    shape(b, 4, .72f, .28f, .16f);
    const float d[][2] = {{444, 81}, {548, 150}, {650, 95}, {575, 48}};
    shape(d, 4, .61f, .22f, .16f);
    const float e[][2] = {{738, 70}, {848, 145}, {953, 88}, {888, 43}};
    shape(e, 4, .72f, .29f, .17f);
    const float f[][2] = {{1013, 73}, {1126, 143}, {1238, 91}, {1170, 39}};
    shape(f, 4, .62f, .23f, .17f);
    const float ridge[][2] = {{0, 181},   {146, 196},  {278, 180},  {430, 198},  {584, 176},  {742, 197},
                              {890, 179}, {1039, 197}, {1190, 178}, {1280, 188}, {1280, 168}, {0, 166}};
    shape(ridge, 12, .96f, .51f, .26f);
    shadow(284, 171, 176, 17);
    shadow(550, 191, 74, 10);
    shadow(700, 94, 70, 8);
    shadow(865, 35, 46, 7);
}
void saturnSurfaceTexture() {
    // Cool ice plates, lilac ridges and long violet shadows distinguish Saturn's ground.
    const float a[][2] = {{0, 68}, {116, 142}, {199, 72}, {136, 18}};
    shape(a, 4, .35f, .32f, .52f);
    const float b[][2] = {{230, 80}, {345, 151}, {448, 79}, {369, 24}};
    shape(b, 4, .58f, .51f, .68f);
    const float d[][2] = {{481, 68}, {590, 142}, {694, 72}, {615, 16}};
    shape(d, 4, .35f, .31f, .50f);
    const float e[][2] = {{924, 76}, {1030, 154}, {1146, 76}, {1064, 17}};
    shape(e, 4, .37f, .33f, .53f);
    const float f[][2] = {{1100, 59}, {1212, 138}, {1280, 88}, {1280, 12}};
    shape(f, 4, .59f, .52f, .69f);
    const float ice[][2] = {{0, 187},   {164, 202},  {293, 178},  {436, 203},  {587, 181},  {739, 205},
                            {906, 180}, {1051, 202}, {1215, 180}, {1280, 192}, {1280, 173}, {0, 168}};
    shape(ice, 12, .70f, .61f, .75f);
    shadow(1004, 171, 128, 14);
    shadow(840, 190, 47, 8);
    shadow(604, 96, 58, 7);
    shadow(770, 31, 45, 7);
}
void drawJupiterScene() {
    drawSky();
    drawSun();
    // From Jupiter Outpost, Saturn is the planet visible in the sky.
    drawSaturn();
    jupiterGround();
    jupiterSurfaceTexture();
    drawJupiterBase();
    // Extra connected laboratory pods make Jupiter's base broad and industrial.
    disk(540, 256, 43, .78f, .80f, .86f, 24);
    rect(497, 212, 583, 256, .74f, .76f, .83f);
    rect(458, 238, 497, 250, .13f, .16f, .23f);
    rect(583, 238, 628, 250, .13f, .16f, .23f);
    beacon(540, 290, 30);
    drawDrone(694, 364, .85f);
    drawRover(620 + sin(roverPhase) * 75, 104, .78f, .75f, .77f, .82f);
    drawAstronaut(865 + astronautOffset, 44, .85f);
    drawSign(1018, 57, "JUPITER BASE 01");
    drawRocket(350, 280, false, 1);
    text(42, 674, "JUPITER", GLUT_BITMAP_HELVETICA_18);
    text(44, 646, "ORANGE CLOUD OUTPOST");
    text(506, 40, "CLICK ROCKET: BEGIN SPACE FLIGHT");
}
void drawSaturnScene() {
    drawSky();
    // From Saturn Ring Station, Jupiter is the planet visible in the sky.
    drawJupiter();
    disk(210, 548, 42, .45f, .42f, .48f, 18);
    disk(197, 560, 12, .30f, .28f, .35f, 12);
    saturnGround();
    saturnSurfaceTexture();
    drawSaturnBase();
    drawDish(842, 250);
    // Saturn's rover and astronaut use a cooler palette, unlike the Jupiter outpost crew.
    drawDrone(728, 364, .75f);
    drawRover(604 - sin(roverPhase) * 70, 106, .56f, .70f, .71f, .78f);
    drawAstronaut(770 + astronautOffset, 38, .88f);
    drawSign(1017, 57, "SATURN BASE 01");
    drawRocket(1010, 280, false, -1);
    text(1010, 674, "SATURN", GLUT_BITMAP_HELVETICA_18);
    text(946, 646, "RING RESEARCH STATION");
    text(490, 40, "CLICK ROCKET: RETURN THROUGH SPACE");
}
void drawTransition() {
    drawSky();
    text(489, 650, "DEEP SPACE TRANSIT", GLUT_BITMAP_HELVETICA_18);
    text(475, 620, "JUPITER OUTPOST  ->  SATURN RING STATION");
    // Distant departure and destination planets are visible only during this flight scene.
    disk(95, 365, 66, .74f, .32f, .13f, 40);
    oval(1185, 380, 87, 21, .67f, .49f, .30f, 40);
    disk(1185, 380, 52, .87f, .66f, .38f, 40);
    oval(1185, 380, 88, 10, .49f, .35f, .25f, 40);
    float x = travelDirection == 1 ? 150 + 980 * travel : 1130 - 980 * travel;
    float y = 305 + sin(travel * PI) * 250;
    for (int i = 1; i < 6; i++) {
        float tail = x - travelDirection * i * 30;
        stroke(tail, y - 8, tail - travelDirection * 20, y - 8, 2, .22f, .55f, .94f);
    }
    drawRocket(x, y, true, travelDirection);
    text(515, 40, "ROCKET IS CROSSING THE STARFIELD");
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (scene == 0)
        drawJupiterScene();
    else if (scene == 1)
        drawTransition();
    else
        drawSaturnScene();
    glutSwapBuffers();
}
void reshape(int w, int h) {
    windowW = w;
    windowH = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WORLD_W, 0, WORLD_H);
    glMatrixMode(GL_MODELVIEW);
}
void timer(int) {
    blink += .10f;
    roverPhase += .035f;
    if (scene == 1) {
        travel += .008f;
        if (travel >= 1) {
            scene = travelDirection == 1 ? 2 : 0;
            travel = 0;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}
void mouse(int b, int state, int mx, int my) {
    if (b != GLUT_LEFT_BUTTON || state != GLUT_DOWN || scene == 1) return;
    float x = mx * (float)WORLD_W / windowW, y = (windowH - my) * (float)WORLD_H / windowH;
    float rx = scene == 0 ? 350 : 1010;
    if (fabs(x - rx) < 45 && y > 245 && y < 385) {
        travelDirection = scene == 0 ? 1 : -1;
        travel = 0;
        scene = 1;
    }
}
void key(unsigned char k, int, int) {
    const float moveAmount = 18.0f;

    if (k == 'a' || k == 'A') astronautOffset -= moveAmount;
    if (k == 'd' || k == 'D') astronautOffset += moveAmount;
    if (astronautOffset < -320.0f) astronautOffset = -320.0f;
    if (astronautOffset > 320.0f) astronautOffset = 320.0f;
    if (k == 27 || k == 'q' || k == 'Q') std::exit(0);

    glutPostRedisplay();
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_STENCIL);
    glutInitWindowSize(WORLD_W, WORLD_H);
    glutCreateWindow("Interplanetary Outposts: Jupiter to Saturn");
    glClearColor(.015f, .018f, .04f, 1);
    reshape(WORLD_W, WORLD_H);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutKeyboardFunc(key);
    glutTimerFunc(16, timer, 0);
    glutMainLoop();
    return 0;
}
