//Chương trình vẽ 1 hình lập phương đơn vị theo mô hình lập trình OpenGL hiện đại

#include "Angel.h"  /* Angel.h là file tự phát triển (tác giả Prof. Angel), có chứa cả khai báo includes glew và freeglut*/
// Hop nhat

// remember to prototype
void generateGeometry(void);
void initGPUBuffers(void);
void shaderSetup(void);
void display(void);
void keyboard(unsigned char key, int x, int y);


typedef vec4 point4;
typedef vec4 color4;
using namespace std;

// Số các đỉnh của các tam giác
const int NumPoints = 36;

point4 points[NumPoints]; /* Danh sách các đỉnh của các tam giác cần vẽ*/
color4 colors[NumPoints]; /* Danh sách các màu tương ứng cho các đỉnh trên*/
point4 vertices[8]; /* Danh sách 8 đỉnh của hình lập phương*/
color4 vertex_colors[8]; /*Danh sách các màu tương ứng cho 8 đỉnh hình lập phương*/
vec3 normals[5000];
GLuint program, model_loc, projection_loc, view_loc;

mat4 mv;
mat4  model, nang, cuatutrai, xoay, cuatuphai, dccanh, dccanh1, dccanh2, dcmaynang, nanggo, khoango, kichthuoc, kichthuocmayduc, dich;

GLfloat quaytt, quaytt1 = 0, quaytt2, quaytutrai = 0, quaytuphai, quaymaynang, nangthanhgo, quaykhoan;
GLfloat l = -1.0, r = 1.0;
GLfloat bottom = -1.0, top = 1.0;
//GLfloat zNear = 1, zFar = 10;
GLfloat zNear = 1, zFar = 10.0;
GLfloat dcc[] = { 0,0 };
GLfloat dcc1[] = { 0,0 };
GLfloat   theta[] = { 0,0,0 };


// Mã màu
vec4 black = color4(0.0, 0.0, 0.0, 1.0); // black
vec4 red = color4(1.0, 0.0, 0.0, 1.0); // red
vec4 yellow = color4(1.0, 1.0, 0.0, 1.0); // yellow
vec4 green = color4(0.0, 1.0, 0.0, 1.0); // green
vec4 blue = color4(0.0, 0.0, 1.0, 1.0); // blue
vec4 magenta = color4(1.0, 0.0, 1.0, 1.0); // magenta
vec4 white = color4(1.0, 1.0, 1.0, 1.0); // white
vec4 cyan = color4(0.0, 1.0, 1.0, 1.0); // cyan
vec4 orange = color4(1, 0.6, 0); // orange




/* Khởi tạo các tham số chiếu sáng - tô bóng*/
point4 light_position(0.0, 0.0, 1.0, 0.0);
color4 light_ambient(0.2, 0.2, 0.2, 1.0);
color4 light_diffuse(1.0, 1.0, 1.0, 1.0);
color4 light_specular(1.0, 1.0, 1.0, 1.0);

color4 material_ambient(1.0, 1.0, 1.0, 1.0);
color4 material_diffuse(1.0, 0.8, 0.0, 1.0);
color4 material_specular(1.0, 0.8, 0.0, 1.0);
float material_shininess = 100.0;

color4 ambient_product = light_ambient * material_ambient;
color4 diffuse_product = light_diffuse * material_diffuse;
color4 specular_product = light_specular * material_specular;



void initCube()
{
	// Gán giá trị tọa độ vị trí cho các đỉnh của hình lập phương
	vertices[0] = point4(-0.5, -0.5, 0.5, 1.0);
	vertices[1] = point4(-0.5, 0.5, 0.5, 1.0);
	vertices[2] = point4(0.5, 0.5, 0.5, 1.0);
	vertices[3] = point4(0.5, -0.5, 0.5, 1.0);
	vertices[4] = point4(-0.5, -0.5, -0.5, 1.0);
	vertices[5] = point4(-0.5, 0.5, -0.5, 1.0);
	vertices[6] = point4(0.5, 0.5, -0.5, 1.0);
	vertices[7] = point4(0.5, -0.5, -0.5, 1.0);

	// Gán giá trị màu sắc cho các đỉnh của hình lập phương	
	vertex_colors[0] = color4(0.0, 0.0, 0.0, 1.0); // black
	vertex_colors[1] = color4(1.0, 0.0, 0.0, 1.0); // red
	vertex_colors[2] = color4(1.0, 1.0, 0.0, 1.0); // yellow
	vertex_colors[3] = color4(0.0, 1.0, 0.0, 1.0); // green
	vertex_colors[4] = color4(0.0, 0.0, 1.0, 1.0); // blue
	vertex_colors[5] = color4(1.0, 0.0, 1.0, 1.0); // magenta
	vertex_colors[6] = color4(1.0, 1.0, 1.0, 1.0); // white
	vertex_colors[7] = color4(0.0, 1.0, 1.0, 1.0); // cyan
}
int Index = 0;
void quad(int a, int b, int c, int d)  /*Tạo một mặt hình lập phương = 2 tam giác, gán màu cho mỗi đỉnh tương ứng trong mảng colors*/
{
	vec4 u = vertices[b] - vertices[a];
	vec4 v = vertices[c] - vertices[b];
	vec3 normal = normalize(cross(u, v));
	normals[Index] = normal; colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; Index++;
	normals[Index] = normal; colors[Index] = vertex_colors[a]; points[Index] = vertices[b]; Index++;
	normals[Index] = normal; colors[Index] = vertex_colors[a]; points[Index] = vertices[c]; Index++;
	normals[Index] = normal; colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; Index++;
	normals[Index] = normal; colors[Index] = vertex_colors[a]; points[Index] = vertices[c]; Index++;
	normals[Index] = normal; colors[Index] = vertex_colors[a]; points[Index] = vertices[d]; Index++;
}
void makeColorCube(void)  /* Sinh ra 12 tam giác: 36 đỉnh, 36 màu*/

{
	quad(1, 0, 3, 2);
	quad(2, 3, 7, 6);
	quad(3, 0, 4, 7);
	quad(6, 5, 1, 2);
	quad(4, 5, 6, 7);
	quad(5, 4, 0, 1);
}
void generateGeometry(void)
{
	initCube();
	makeColorCube();
}


void initGPUBuffers(void)
{
	// Tạo một VAO - vertex array object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Tạo và khởi tạo một buffer object
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors) + sizeof(normals), NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors), sizeof(normals), normals);
}

void shaderSetup(void)
{
	// Nạp các shader và sử dụng chương trình shader
	program = InitShader("vshader1.glsl", "fshader1.glsl");   // hàm InitShader khai báo trong Angel.h
	glUseProgram(program);

	// Khởi tạo thuộc tính vị trí đỉnh từ vertex shader
	GLuint loc_vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(loc_vPosition);
	glVertexAttribPointer(loc_vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	GLuint loc_vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(loc_vColor);
	glVertexAttribPointer(loc_vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points)));

	GLuint loc_vNormal = glGetAttribLocation(program, "vNormal");
	glEnableVertexAttribArray(loc_vNormal);
	glVertexAttribPointer(loc_vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points) + sizeof(colors)));

	glUniform4fv(glGetUniformLocation(program, "AmbientProduct"), 1, ambient_product);
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniform4fv(glGetUniformLocation(program, "SpecularProduct"), 1, specular_product);
	glUniform4fv(glGetUniformLocation(program, "LightPosition"), 1, light_position);
	glUniform1f(glGetUniformLocation(program, "Shininess"), material_shininess);


	model_loc = glGetUniformLocation(program, "Model");
	projection_loc = glGetUniformLocation(program, "Projection");
	view_loc = glGetUniformLocation(program, "View");

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 1.0);        /* Thiết lập màu trắng là màu xóa màn hình*/
}

// Hàm để tô màu đối tượng
void to_mau(color4 color) {
	material_diffuse = color;  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
}
mat4 model_view, base_model;


// Hàm để vẽ 
void ve() {
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);    /*Vẽ các tam giác*/
}

// Vẽ không gian 
void nennha() {
	to_mau(green);
	mv = Translate(0, -2, 0.5) * Scale(10, 0.05, 6);
	ve();
}
void nennha1() {
	to_mau(white);
	mv = Translate(0, -1.97, 0.5) * Scale(1, 0.01, 6);
	ve();
}
void nennha2() {
	to_mau(white);
	mv = Translate(0, -1.97, 0.5) * Scale(10, 0.01, 1);
	ve();
}
void tuongsau() {
	to_mau(cyan);
	mv = Translate(0, -0.5, -2.5) * Scale(10, 3, 0.05);
	ve();
}
void nhaxuong() {
	nennha();
	nennha1();
	nennha2();
	tuongsau();
}

//vẽ dong ho
void matdongho() {
	to_mau(white);
	mv = Translate(2.5, -0.3, -2.45) * Scale(0.8, 0.8, 0.05);
	ve();
}
GLfloat gio_rotate = 90.0f;
GLfloat phut_rotate = 120.0f;
void kimgio() {
	to_mau(black);
	mv = Translate(2.5, -0.3, -2.45) * RotateZ(gio_rotate) * Translate(0.18 / 2, 0.0, 0.02) * Scale(0.18, 0.02, 0.02);
	ve();
}
void kimphut() {
	to_mau(black);
	mv = Translate(2.5, -0.3, -2.45) * RotateZ(phut_rotate) * Translate(0.15, 0.0, 0.02) * Scale(0.3, 0.02, 0.02);
	ve();
}
void dongho() {
	matdongho();
	kimgio();
	kimphut();
}

//vẽ tủ------------------------------------------------------
void ct1() {
	mv = Translate(-3.25, -1.2, -1.4) * Scale(0.6, 1.6, 0.03);
	material_diffuse = vec4(0.5, 0.7, 0.1, 0.1);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;

	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dccanh * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void tc1() {
	mv = Translate(-3.25, -1.2, -1.35) * Scale(0.6 * 0.1, 0.03 * 1.5, 1.6 * 0.01);
	material_diffuse = vec4(0.8, 0.2, 0, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;

	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dccanh * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void tc2() {
	mv = Translate(-2.75, -1.2, -1.35) * Scale(0.6 * 0.1, 0.03 * 1.5, 1.6 * 0.01);
	material_diffuse = vec4(0.8, 0.2, 0, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;

	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dccanh1 * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void ct2() {
	mv = Translate(-2.65, -1.2, -1.4) * Scale(0.6, 1.6, 0.03);
	material_diffuse = vec4(0.5, 0.7, 0.1, 0.1);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;

	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dccanh1 * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void ns1() {
	mv = Translate(-3, -1.2, -2.2) * Scale(1.2, 1.6, 0.02);
	material_diffuse = vec4(0.8, 0.2, 0, 1);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;

	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void ns2() {
	mv = Translate(-3, -1.95, -1.8) * Scale(1.2, 0.02, 0.8);
	material_diffuse = vec4(1, 1, 0, 1);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;

	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void nst() {
	mv = Translate(-3, -1.65, -1.8) * Scale(1.2, 0.02, 0.8);
	material_diffuse = vec4(1, 1, 0, 1);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;

	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void nst1() {
	mv = Translate(-3, -1.35, -1.8) * Scale(1.2, 0.02, 0.8);
	material_diffuse = vec4(1, 1, 0, 1);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;

	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void ns3() {
	mv = Translate(-3, -0.4, -1.8) * Scale(1.2, 0.02, 0.8);
	material_diffuse = vec4(1, 1, 0, 1);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;

	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void ns4() {
	mv = Translate(-3.58, -1.2, -1.8) * Scale(0.02 * 2, 1.6, 0.8);
	material_diffuse = vec4(1, 1, 0, 1);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;

	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void ns5() {
	mv = Translate(-2.38, -1.2, -1.8) * Scale(0.02 * 2, 1.6, 0.8);
	material_diffuse = vec4(1, 1, 0, 1);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;

	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

void hienthiCaiTu()
{
	ct1();
	ct2();
	tc1();
	tc2();
	ns1();
	ns2();
	nst();
	nst1();
	ns3();
	ns4();
	ns5();
	dccanh = Translate(-3.55, -1.2, -1.4) * RotateY(dcc[0]) * Translate(3.55, 1.2, 1.4);
	dccanh1 = Translate(-2.35, -1.2, -1.4) * RotateY(dcc1[0]) * Translate(2.35, 1.2, 1.4);

}

// vẽ bàn
void khoiban(GLfloat w, GLfloat h, GLfloat l, GLfloat k)
{
	mv = Translate(w, h, l) * RotateY(k) * Scale(0.7, 0.02, 0.7);
	material_diffuse = vec4(1, 1, 0, 1);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void hienthiban()
{
	for (int i = 0; i < 20; i++)
	{
		khoiban(-1.35, -1.3, -1.8, (6 * i));
	}
}
void chanban1() {
	mv = Translate(-1.35, -1.7, -1.8) * RotateX(-45.0) * Scale(0.05, 1.0, 0.05);
	material_diffuse = vec4(1, 1, 0, 1);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;

	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void chanban2() {
	mv = Translate(-1.35, -1.7, -1.8) * RotateX(45.0) * Scale(0.05, 1.0, 0.05);
	material_diffuse = vec4(1, 1, 0, 1);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;

	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void chanban3() {
	mv = Translate(-1.35, -1.7, -1.8) * RotateZ(-45.0) * Scale(0.05, 1.0, 0.05);
	material_diffuse = vec4(1, 1, 0, 1);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;

	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void chanban4() {
	mv = Translate(-1.35, -1.7, -1.8) * RotateZ(45.0) * Scale(0.05, 1.0, 0.05);
	material_diffuse = vec4(1, 1, 0, 1);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;

	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

void ban()
{
	hienthiban();
	chanban1();
	chanban2();
	chanban3();
	chanban4();

}

//xe nâng
void thanxe()
{
	mv = Translate(1.3, -1.45, -1.5) * Scale(1.5, 0.8, 1);;
	material_diffuse = vec4(1, 0.2, 0, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dcmaynang * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void thanduoi()
{
	mv = Translate(0.1, -1.65, -1.5) * Scale(1, 0.4, 1);;
	material_diffuse = vec4(1, 0.2, 0, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dcmaynang * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void tru1()
{
	mv = Translate(-0.25, -0.45, -1.85) * Scale(0.3, 2, 0.3);;
	material_diffuse = vec4(0, 0, 0, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dcmaynang * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void tru2()
{
	mv = Translate(-0.25, -0.45, -1.15) * Scale(0.3, 2, 0.3);;
	material_diffuse = vec4(0, 0, 0, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dcmaynang * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void tru3()
{
	mv = Translate(-0.25, 0.65, -1.5) * Scale(0.3, 0.3, 1);;
	material_diffuse = vec4(1, 1, 1, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dcmaynang * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void banhxenang(GLfloat a, GLfloat b, GLfloat c, GLfloat y)
{
	mv = Translate(a, b, c) * RotateZ(y) * Scale(0.5, 0.5, 0.2);
	material_diffuse = vec4(0, 0, 0, 0);  // mau vat

	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dcmaynang * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void thanhngang1()
{
	mv = Translate(-0.85, -1.5, -1.85) * Scale(1, 0.1, 0.1);;
	material_diffuse = vec4(1, 1, 1, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dcmaynang * nanggo * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void thanhngang2()
{
	mv = Translate(-0.85, -1.5, -1.15) * Scale(1, 0.1, 0.1);;
	material_diffuse = vec4(1, 1, 1, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dcmaynang * nanggo * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void go(GLfloat a, GLfloat b, GLfloat c, GLfloat y)
{
	mv = Translate(a, b, c) * RotateZ(y) * Scale(0.5, 0.5, 1.5);
	material_diffuse = vec4(1.5, 0.75, 0, 0);  // mau vat

	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dcmaynang * nanggo * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void thanhmai1()
{
	mv = Translate(0.6, -0.3, -1.95) * Scale(0.1, 1.5, 0.1);;
	material_diffuse = vec4(0, 0, 1, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dcmaynang * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void thanhmai2()
{
	mv = Translate(0.6, -0.3, -1.05) * Scale(0.1, 1.5, 0.1);;
	material_diffuse = vec4(0, 0, 1, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dcmaynang * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void thanhmai3()
{
	mv = Translate(1.9, -0.3, -1.95) * Scale(0.1, 1.5, 0.1);;
	material_diffuse = vec4(0, 0, 1, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dcmaynang * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void thanhmai4()
{
	mv = Translate(1.9, -0.3, -1.05) * Scale(0.1, 1.5, 0.1);;
	material_diffuse = vec4(0, 0, 1, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dcmaynang * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void mai()
{
	mv = Translate(1.3, 0.45, -1.5) * Scale(1.8, 0.05, 1);;
	material_diffuse = vec4(1, 0.2, 1, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dcmaynang * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
//cua 
float cuatay;
void cotcuatay()
{
	mv = Translate(3.5, -1.83, 1.9 + cuatay) * Scale(0.01, 0.01, 0.9);;
	material_diffuse = vec4(1, 1, 1, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void taycam()
{
	mv = Translate(3.5, -1.83, 1.45 + cuatay) * Scale(0.3, 0.01, 0.01);;
	material_diffuse = vec4(1, 1, 1, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void taycam1()
{
	mv = Translate(3.5, -1.83, 2.35 + cuatay) * Scale(0.3, 0.01, 0.01);;
	material_diffuse = vec4(1, 1, 1, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

void luoicuatay()
{
	mv = Translate(3.5, -1.83, 1.9 + cuatay) * Scale(0.1, 0.01, 0.7);;
	material_diffuse = vec4(1, 1, 1, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void gocua(GLfloat a, GLfloat b, GLfloat c, GLfloat y)
{
	mv = Translate(a, b, c) * RotateX(y) * Scale(1.5, 0.3, 0.3);
	material_diffuse = vec4(1.5, 0.75, 0, 0);  // mau vat

	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void cua() {

	cotcuatay();
	luoicuatay();
	taycam();
	taycam1();
	for (int i = 0; i < 20; i++)
	{

		gocua(2.9, -1.8, 2.0, (3 * i));
	}
}
void xenang()
{
	thanxe();
	thanduoi();
	for (int i = 0; i < 20; i++)
	{
		banhxenang(0.1, -1.65, -0.95, (6 * i));
		banhxenang(0.1, -1.65, -2.05, (6 * i));
		banhxenang(1.7, -1.65, -0.95, (6 * i));
		banhxenang(1.7, -1.65, -2.05, (6 * i));
		go(-0.85, -1.1, -1.55, (6 * i));
	}
	tru1();
	tru2();
	tru3();
	thanhngang1();
	thanhngang2();
	nanggo = Translate(0, nangthanhgo, 0);
	dcmaynang = RotateY(180.0) * Translate(3 + quaymaynang, 0, 1.15);
	thanhmai1();
	thanhmai2();
	thanhmai3();
	thanhmai4();
	mai();
}


//bàn đục
void matban()
{
	mv = Translate(2.35, -1.3, -0.6) * Scale(1.8, 0.05, 1);
	material_diffuse = vec4(1, 0.2, 0, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * kichthuoc * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void chanban5()
{
	mv = Translate(1.65, -1.65, -0.95) * Scale(0.1, 0.75, 0.1);;
	material_diffuse = vec4(1, 0.2, 0, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * kichthuoc * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void chanban6()
{
	mv = Translate(1.65, -1.65, -0.25) * Scale(0.1, 0.75, 0.1);;
	material_diffuse = vec4(1, 0.2, 0, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * kichthuoc * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void chanban7()
{
	mv = Translate(3.05, -1.65, -0.95) * Scale(0.1, 0.75, 0.1);;
	material_diffuse = vec4(1, 0.2, 0, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * kichthuoc * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void chanban8()
{
	mv = Translate(3.05, -1.65, -0.25) * Scale(0.1, 0.75, 0.1);;
	material_diffuse = vec4(1, 0.2, 0, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * kichthuoc * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void matghe()
{
	mv = Translate(2.35, -1.5, -1.6) * Scale(0.6, 0.05, 0.6);;
	material_diffuse = vec4(1, 0.2, 0, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * kichthuoc * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void changhe1()
{
	mv = Translate(2.09, -1.75, -1.35) * Scale(0.06, 0.5, 0.06);;
	material_diffuse = vec4(1, 0.5, 0.1, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * kichthuoc * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void changhe2()
{
	mv = Translate(2.53, -1.75, -1.35) * Scale(0.06, 0.5, 0.06);;
	material_diffuse = vec4(1, 0.5, 0.1, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * kichthuoc * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void changhe3()
{
	mv = Translate(2.09, -1.55, -1.85) * Scale(0.06, 0.9, 0.06);;
	material_diffuse = vec4(1, 0.5, 0.1, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * kichthuoc * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void changhe4()
{
	mv = Translate(2.53, -1.55, -1.85) * Scale(0.06, 0.9, 0.06);;
	material_diffuse = vec4(1, 0.5, 0.1, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * kichthuoc * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void thanhghe()
{
	mv = Translate(2.33, -1, -1.85) * Scale(0.6, 0.3, 0.07);;
	material_diffuse = vec4(1, 0.5, 0.1, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * kichthuoc * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void banduc()
{
	matban();
	chanban5();
	chanban6();
	chanban7();
	chanban8();
	matghe();
	changhe1();
	changhe2();
	changhe3();
	changhe4();
	thanhghe();
	kichthuoc = Translate(1, -0.5, -0.5) * Scale(0.7, 0.7, 0.7);
}
//máy đục
void daymayduc()
{
	mv = Translate(2.35, -1.15, -0.6) * Scale(0.8, 0.3, 0.5);;
	material_diffuse = vec4(1, 1, 0.5, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * kichthuocmayduc * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void thanmayduc1()
{
	mv = Translate(2.65, -0.75, -0.6) * Scale(0.2, 0.8, 0.2);;
	material_diffuse = vec4(1, 1, 0.5, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * kichthuocmayduc * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void thanmayduc2()
{
	mv = Translate(2.55, -0.3, -0.6) * RotateZ(60) * Scale(0.2, 0.4, 0.2);;
	material_diffuse = vec4(1, 1, 0.5, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * kichthuocmayduc * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void diakhoan(GLfloat a, GLfloat b, GLfloat c, GLfloat y)
{
	mv = Translate(a, b, c) * RotateY(y) * Scale(0.3, 0.4, 0.3);
	material_diffuse = vec4(0.8, 0.75, 0.5, 0);  // mau vat

	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * kichthuocmayduc * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void muikhoan(GLfloat a, GLfloat b, GLfloat c, GLfloat y)
{
	mv = Translate(a, b, c) * RotateY(y) * Scale(0.02, 0.5, 0.02);
	material_diffuse = vec4(0, 0, 0, 0);  // mau vat

	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * khoango * kichthuocmayduc * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void gokhoan(GLfloat a, GLfloat b, GLfloat c, GLfloat y)
{
	mv = Translate(a, b, c) * RotateX(y) * Scale(0.2, 0.2, 0.2);
	material_diffuse = vec4(1, 0.3, 0.5, 0);  // mau vat

	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * kichthuocmayduc * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void canso()
{
	mv = Translate(2.9, -0.45, -0.6) * Scale(0.4, 0.1, 0.1);;
	material_diffuse = vec4(1, 0, 1, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;
	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * khoango * kichthuocmayduc * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void mayduc()
{
	daymayduc();
	thanmayduc1();
	thanmayduc2();
	for (int i = 0; i < 20; i++)
	{
		diakhoan(2.25, -0.3, -0.6, (6 * i));
		muikhoan(2.25, -0.4, -0.6, (6 * i));
		gokhoan(2.25, -0.9, -0.6, (6 * i));
	}
	canso();
	khoango = Translate(0.0, quaykhoan, 0);
	kichthuocmayduc = Translate(1, -0.5, -0.5) * Scale(0.7, 0.7, 0.7);
}


void de()
{
	mv = Translate(0.0, -1.7, 1.9) * Scale(1.0f, .06f, 0.2f);

	material_diffuse = vec4(1.56, 1.44, 1.58, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;

	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dich * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
float quaycua1;
void luoicua1()
{
	mv = Translate(0.0, -1.7, 2.0) * Scale(0.06f, .2f, .01f) * Translate(0.0098, 0.003f, 0.0f) * RotateZ(quaycua1) * Translate(-.0098, -0.003f, 0.0);

	material_diffuse = vec4(0.1, 0.5, 0.7, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;

	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dich * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void luoicua2()
{
	mv = Translate(0.0, -1.7, 2.0) * Scale(0.2f, .06f, .01f) * Translate(0.0098, 0.003f, 0.0f) * RotateZ(quaycua1) * Translate(-.0098, -0.003f, 0.0);

	material_diffuse = vec4(0.1, 0.5, 0.7, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;

	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dich * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void de2()
{
	mv = Translate(0.0, -1.7, 2.12) * Scale(1.0f, .06f, 0.2f);;

	material_diffuse = vec4(1.56, 1.44, 1.58, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;

	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dich * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
float day;
void vanbao()
{
	mv = Translate(-2.0 + day, -1.5, 2.65) * Scale(1.2f, .1f, 0.25f);;

	material_diffuse = vec4(1.5, 0.75, 0, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;

	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void vachngan()
{
	mv = Translate(-2.0, -1.5, 2.3) * Scale(1.3f, .1f, 0.01f);;

	material_diffuse = vec4(0.1, 0.5, 0.7, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;

	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void de3()
{
	mv = Translate(-0.5, -1.7, 2.3) * Scale(0.7f, .06f, 1.0f);;

	material_diffuse = vec4(1.56, 1.44, 1.58, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;

	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dich * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

void de4()
{
	mv = Translate(0.5, -1.7, 2.3) * Scale(0.7f, .06f, 1.0f);;

	material_diffuse = vec4(1.56, 1.44, 1.58, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;

	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dich * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
float quaycua;
void trucxoay()
{
	mv = Translate(0.0, -1.7, 2.3) * Scale(0.04f, 0.04f, 0.85f) * Translate(0.0098, 0.003f, 0.0f) * RotateZ(quaycua) * Translate(-.0098, -0.003f, 0.0);

	material_diffuse = vec4(0.1, 0.5, 0.7, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;

	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dich * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void tru()
{
	mv = Translate(-0.5, -1.9, 1.9) * Scale(0.03f, .3f, 0.03f);;

	material_diffuse = vec4(0.1, 0.5, 0.7, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;

	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dich * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void deke()
{
	mv = Translate(0.0, -1.85, 2.47) * Scale(0.6f, .3f, 0.6f);;

	material_diffuse = vec4(0.1, 0.5, 0.7, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;

	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dich * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void dedo()
{
	mv = Translate(0.5, -1.9, 1.9) * Scale(0.03f, .3f, 0.03f);;

	material_diffuse = vec4(0.1, 0.5, 0.7, 0);  // mau vat
	diffuse_product = light_diffuse * material_diffuse;

	glUniform4fv(glGetUniformLocation(program, "DiffuseProduct"), 1, diffuse_product);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dich * mv);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}





// Chân vòng xoay
void maybao() {
	dich = Translate(-2.1, 0.1, 0.1);
	de();
	de2();
	de3();
	de4();
	trucxoay();
	vachngan();
	luoicua1();
	luoicua2();
	deke();
	tru();
	dedo();
	vanbao();
}

//xe nâng
mat4 robot;
mat4 dichRobot;
// Ngực
void Nguc()
{
	mat4 ctm = Scale(1.8, 1.0, 1.0);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dichRobot * robot * ctm);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

// bụng
void Bung(GLfloat x, GLfloat y, GLfloat z)
{
	mat4 ctm = Translate(x, y, z) * Scale(1.5, 1.0, 0.8);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dichRobot * robot * ctm);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

// Cổ
void Co(GLfloat x, GLfloat y, GLfloat z)
{
	mat4 ctm = Translate(x, y, z) * Scale(0.3, 0.3, 0.3);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dichRobot * robot * ctm);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

// đầu
void Dau(GLfloat x, GLfloat y, GLfloat z)
{
	mat4 ctm = Translate(x, y, z) * Scale(0.8, 0.8, 0.8);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dichRobot * robot * ctm);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

// cánh tay
mat4 modelDiChuyenTay;
void CanhTay(GLfloat x, GLfloat y, GLfloat z,
	GLfloat a, GLfloat b, GLfloat c,
	GLfloat d, GLfloat e, GLfloat f,
	GLfloat m, GLfloat n, GLfloat o)
{
	mat4 ctm = RotateX(0);

	ctm = ctm * Translate(x, y, z) * Scale(0.8, 0.8, 0.8);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dichRobot * modelDiChuyenTay * robot * ctm);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	ctm = ctm * Translate(a, b, c) * Scale(0.625, 1.0625, 0.625);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dichRobot * modelDiChuyenTay * robot * ctm);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	ctm = ctm * Translate(d, e, f) * Scale(1, 1, 1);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dichRobot * modelDiChuyenTay * robot * ctm);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	ctm = ctm * Translate(m, n, o) * Scale(1.4, 0.7, 1.4);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dichRobot * modelDiChuyenTay * robot * ctm);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}

// chân
mat4 modelDiChuyenChan;
void Chan(GLfloat x, GLfloat y, GLfloat z,
	GLfloat a, GLfloat b, GLfloat c,
	GLfloat d, GLfloat e, GLfloat f,
	GLfloat m, GLfloat n, GLfloat o)
{
	mat4 ctm = RotateX(0);

	ctm = Translate(x, y, z) * Scale(0.8, 0.8, 0.8);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dichRobot * modelDiChuyenChan * robot * ctm);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	ctm = ctm * Translate(a, b, c) * Scale(0.875, 1.5, 0.875);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dichRobot * modelDiChuyenChan * robot * ctm);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	ctm = ctm * RotateX(0);

	ctm = ctm * Translate(d, e, f) * Scale(1, 1.2, 1);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dichRobot * modelDiChuyenChan * robot * ctm);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	ctm = ctm * Translate(m, n, o) * Scale(8 / 7, 0.5, 1.6);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dichRobot * modelDiChuyenChan * robot * ctm);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void Channgoi(GLfloat x, GLfloat y, GLfloat z,
	GLfloat a, GLfloat b, GLfloat c,
	GLfloat d, GLfloat e, GLfloat f,
	GLfloat m, GLfloat n, GLfloat o)
{
	mat4 ctm = RotateX(0);

	ctm = Translate(x, y, z) * Scale(0.8, 0.8, 0.8);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dichRobot * modelDiChuyenChan * robot * ctm);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	ctm = ctm * Translate(a, b, c) * Scale(0.875, 1.5, 0.875);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dichRobot * modelDiChuyenChan * robot * ctm);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	ctm = ctm * RotateX(100);

	ctm = ctm * Translate(d, e, f) * Scale(1, 1.2, 1);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dichRobot * modelDiChuyenChan * robot * ctm);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

	ctm = ctm * Translate(m, n, o) * Scale(8 / 7, 0.5, 1.6);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, model * dichRobot * modelDiChuyenChan * robot * ctm);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}


// vẽ đầu
void FullDau()
{
	Co(0, 0.65, 0.1);
	Dau(0, 1.15, 0.3);
}

float diChuyenChan;
float diChuyentay;
float diChuyentayngc;
int daoChan;
int daochan1;
int daochanngc;

// vẽ tay
void FullTay()
{
	modelDiChuyenTay = Translate(0, 0.55, 0) * RotateX(diChuyenChan) * Translate(0, -0.55, 0);
	CanhTay(1.3, 0, 0, 0, -0.825, 0, 0, -0.85, 0, 0, -0.775, 0);
	modelDiChuyenTay = Translate(0, 0.55, 0) * RotateX(-diChuyenChan) * Translate(0, -0.55, 0);
	CanhTay(-1.3, 0, 0, 0, -0.825, 0, 0, -0.85, 0, 0, -0.775, 0);
}

// vẽ chân
void FullChan()
{
	modelDiChuyenChan = Translate(0, 0.35, 0) * RotateX(diChuyenChan) * Translate(0, -0.35, 0);
	Chan(-0.415, -1.9, 0, 0, -1.05, 0, 0, -1.1, 0.4, 0, -0.7, 0.1);
	modelDiChuyenChan = Translate(0, 0.35, 0) * RotateX(-diChuyenChan) * Translate(0, -0.35, 0);
	Chan(0.415, -1.9, 0, 0, -1.05, 0, 0, -1.1, 0.4, 0, -0.7, 0.1);
}
void FullChanngoi()
{
	modelDiChuyenChan = Translate(0, 0.2, 0.0);
	Channgoi(-0.415, -1.9, 0, 0, -1.05, 0, 0, -1.1, 0.4, 0, -0.7, 0.1);
	modelDiChuyenChan = Translate(0, 0.2, 0.0);
	Channgoi(0.415, -1.9, 0, 0, -1.05, 0, 0, -1.1, 0.4, 0, -0.7, 0.1);
}
void FullTaycua()
{
	modelDiChuyenTay = Translate(0, 0.55, 0) * RotateX(diChuyentay) * Translate(0, -0.55, 0);
	CanhTay(1.3, 0, 0, 0, -0.825, 0, 0, -0.85, 0, 0, -0.775, 0);
	modelDiChuyenTay = Translate(0, 0.55, 0) * RotateX(diChuyentay) * Translate(0, -0.55, 0);
	CanhTay(-1.3, 0, 0, 0, -0.825, 0, 0, -0.85, 0, 0, -0.775, 0);
}
void FullTaycuangc()
{
	modelDiChuyenTay = Translate(0, 0.55, 0) * RotateX(-diChuyentayngc) * Translate(0, -0.55, 0);
	CanhTay(1.3, 0, 0, 0, -0.825, 0, 0, -0.85, 0, 0, -0.775, 0);
	modelDiChuyenTay = Translate(0, 0.55, 0) * RotateX(-diChuyentayngc) * Translate(0, -0.55, 0);
	CanhTay(-1.3, 0, 0, 0, -0.825, 0, 0, -0.85, 0, 0, -0.775, 0);
}
// Khởi tạo các biến robot auto
float robotTheta = 0;
float percentRobotTheta = 0.1;
float powerRobot = 0.005;
float turnOfRobot = 1;
int daoChieuDiChuyen = 0;
float diChuyenRobot;

void Robot()
{
	// Chỉnh màu cho robot
	to_mau(white);

	// robot 1
	dichRobot = Translate(0, -0.9, -1.0) *
		Translate(diChuyenRobot, 0, 0) *
		RotateY(daoChieuDiChuyen) * RotateY(90) *
		Scale(0.25, 0.25, 0.25);
	robot = Scale(0.8, 0.8, 0.8);
	Nguc();
	Bung(0, -1, 0);
	FullDau();
	FullTay();
	FullChan();

	// robot 2
	dichRobot = Translate(0, -0.9, 1.7) *
		Translate(-diChuyenRobot, 0, 0) *
		RotateY(daoChieuDiChuyen) * RotateY(-90) *
		Scale(0.25, 0.25, 0.25);
	robot = Scale(0.8, 0.8, 0.8);
	Nguc();
	Bung(0, -1, 0);
	FullDau();
	FullTay();
	FullChan();

	// robot 3 mẹ
	dichRobot = Translate(1.5, -0.9, 1) *
		Translate(0, 0, diChuyenRobot) *
		RotateY(daoChieuDiChuyen) * RotateY(0) *
		Scale(0.25, 0.25, 0.25);
	robot = Scale(0.8, 0.8, 0.8);
	Nguc();
	Bung(0, -1, 0);
	FullDau();
	FullTay();
	FullChan();

	// robot 3 con


}

void robotngoicua() {
	dichRobot = Translate(3.5, -1.4, 1.4) *
		Scale(0.25, 0.25, 0.25);
	robot = Scale(0.6, 0.6, 0.6);
	Nguc();
	Bung(0, -1, 0);
	FullDau();
	FullTaycua();
	FullChanngoi();

	dichRobot = Translate(3.5, -1.4, 2.46) * RotateY(180) *
		Scale(0.25, 0.25, 0.25);
	robot = Scale(0.6, 0.6, 0.6);
	Nguc();
	Bung(0, -1, 0);
	FullDau();
	FullTaycuangc();
	FullChanngoi();

	cua();
}

float check1 = 1;
// Ham xu ly Robot di bộ
void robotDiBo(void)
{
	if (turnOfRobot == 1) {
		// Biến di chuyển nhanh chậm
		if (percentRobotTheta < 2.3)
			percentRobotTheta += 0.005;
		// Biến đổi chiều chuyển động 
		if (daoChieuDiChuyen == 0) {
			diChuyenRobot += powerRobot * percentRobotTheta;
			if (diChuyenRobot > 1.8)  daoChieuDiChuyen = 180;
		}
		if (daoChieuDiChuyen == 180) {
			diChuyenRobot -= powerRobot * percentRobotTheta;
			if (diChuyenRobot < -1.8)  daoChieuDiChuyen = 0;
		}
		// Biến đổi di chuyển tay, chân( đánh tay, chân )
		if (daoChan == 0) {
			diChuyenChan += 1.0;
			if (diChuyenChan > 8)  daoChan = 1;
		}
		if (daoChan == 1) {
			diChuyenChan -= 1.0;
			if (diChuyenChan < -8)  daoChan = 0;
		}

		if (check1 == 0) {
			quaycua += 10;
			quaycua1 += 15;
		}

	}
	glutPostRedisplay();
}
int batdau;

void ngoicua(void) {
	if (batdau == 1) {
		if (daochan1 == 0) {
			diChuyentay += 1.0;
			cuatay -= 0.01;
			if (diChuyentay > 0)  daochan1 = 1;
		}
		if (daochan1 == 1) {
			cuatay += 0.01;
			diChuyentay -= 1.0;
			if (diChuyentay < -9)  daochan1 = 0;
		}
		if (daochanngc == 0) {
			diChuyentayngc -= 1.0;
			if (diChuyentayngc < -10)  daochanngc = 1;
		}
		if (daochanngc == 1) {
			diChuyentayngc += 1.0;
			if (diChuyentayngc > 10)  daochanngc = 0;

		}
	}

}
void xuLyAuto(void) {
	robotDiBo();
	ngoicua();
}
//xenang




void congxuong() {

	maybao();
	xuLyAuto();
	Robot();
	robotngoicua();
	cua();
}



GLfloat cam_pos_x = 0;
GLfloat cam_pos_y = 0;
GLfloat cam_pos_z = 2;
/// Ve Hien thi
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	nhaxuong();
	dongho();
	ban();
	hienthiCaiTu();
	xenang();
	banduc();
	mayduc();
	congxuong();

	/*maybao();*/

	model = Translate(0, -1.97, -0.5) * RotateX(theta[1]) * Translate(0, 1.97, 0.5) * RotateY(theta[2]) * RotateZ(theta[3]);;
	// view
	point4 eye(0.0, 3.0, 2.0, 1.0);
	point4 at(0.0, 0.0, 0.0, 1.0);
	vec4 up(0.0, 1.0, 0.0, 1.0);
	mat4 mv = LookAt(eye, at, up);
	glUniformMatrix4fv(view_loc, 1, GL_TRUE, mv);
	// projection
	mat4 projection = Frustum(l, r, bottom, top, zNear, zFar);
	glUniformMatrix4fv(projection_loc, 1, GL_TRUE, projection);
	glutSwapBuffers();


}

void spinCube() {
	if (quaytt1 == 1) {
		quaytt += 7;
		if (quaytt > 360.0) {
			quaytt -= 360.0;
		}
	}
	gio_rotate -= 0.05 / 12;
	phut_rotate -= 0.05;


	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{

	switch (key) {
	case 'a': zNear *= 1.1f; zFar *= 1.1f; break;
	case 'A': zNear *= 0.9f; zFar *= 0.9f; break;

		// camera xuống
	case 'o':
		cam_pos_y -= 0.03f;
		break;
		// camera lên
	case 'i':

		cam_pos_y += 0.03f;
		break;
	case 'n': // goc nhin tran nha
		theta[1] = 0;
		break;
	case 'x':
		theta[1] += 5;
		if (theta[1] > 360) theta[1] -= 360;
		break;
	case 'X':
		theta[1] -= 5;
		if (theta[1] > 360) theta[1] -= 360;
		break;
	case 'y':
		theta[2] += 5;
		if (theta[2] > 360) theta[2] -= 360;
		break;
	case 'Y':
		theta[2] -= 5;
		if (theta[2] > 360) theta[2] -= 360;
		break;
	case 'z':
		theta[3] += 5;
		if (theta[3] > 360) theta[3] -= 360;
		break;
	case 'Z':
		theta[3] -= 5;
		if (theta[3] > 360) theta[3] -= 360;
		break;

	case 't': // đóng mở cửa phải tủ
		dcc[0] -= 5;
		if (dcc[0] - 5 <= -90) dcc[0] = -90;
		glutPostRedisplay();
		break;
	case 'T':
		dcc[0] += 5;
		if (dcc[0] + 5 >= 0) dcc[0] = 0;
		glutPostRedisplay();
		break;
	case 'p': // đóng mở cửa trái tủ
		dcc1[0] += 5;
		if (dcc1[0] + 5 >= 90) dcc1[0] = 90;
		glutPostRedisplay();
		break;
	case 'P':
		dcc1[0] -= 5;
		if (dcc1[0] - 5 <= 0) dcc1[0] = 0;
		glutPostRedisplay();
		break;

	case 'r': // khoan
		quaykhoan -= 0.05;
		if (quaykhoan <= -0.3) { quaykhoan = -0.3; }
		glutPostRedisplay();
		break;
	case 'R':// khoan
		quaykhoan += 0.05;
		if (quaykhoan >= 0) { quaykhoan = 0; }
		glutPostRedisplay();
		break;
	case 'm': // xe đi
		quaymaynang -= 0.05;
		if (quaymaynang >= 1) { quaymaynang = 1; }
		glutPostRedisplay();
		break;
	case 'M':// xe về
		if (quaymaynang <= 0) { quaymaynang += 0.05; }
		glutPostRedisplay();
		break;
	case 'g': // nâng gỗ
		nangthanhgo += 0.05;
		if (nangthanhgo >= 1.5) { nangthanhgo = 1.5; }
		glutPostRedisplay();
		break;
	case 'G':// hạ gỗ
		nangthanhgo -= 0.05;
		if (nangthanhgo <= 0) { nangthanhgo = 0; }
		glutPostRedisplay();
		break;
	case 'u':
		check1 = 0;



		break;
	case 'U':
		check1 = 1;
	case 'k':

		batdau
			= 1;
		break;
	case 'K':

		batdau
			= 0;
		break;

	case 'w':

		day += 0.1;

		break;
	case 's':

		day -= 0.1;

		break;


	}

}




void SpecialFunc(int key, int x, int y) {
	switch (key)
	{
	case GLUT_KEY_RIGHT:
		cam_pos_x += 0.03f;

		//cam_moved = true;
		break;
	case GLUT_KEY_LEFT:
		cam_pos_x -= 0.03f;

		//cam_moved = true;
		break;
	case GLUT_KEY_UP:
		cam_pos_z -= 0.03f;

		//cam_moved = true;
		break;
	case GLUT_KEY_DOWN:
		cam_pos_z += 0.03f;

		break;
	}

	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	// main function: program starts here

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(640, 640);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Ve nha suong");

	glewInit();

	generateGeometry();
	initGPUBuffers();
	shaderSetup();

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(spinCube);

	glutSpecialFunc(SpecialFunc);

	glutMainLoop();
	return 0;
}




