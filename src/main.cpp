
// Lib
#include <pch.h>

// class
#include <Map.h>
#include <MiniMap.h>
#include <Ghost.h>
#include <Scene.h>
#include <fps_camera.h>

using namespace std;

// Constants
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 512
#define CANVAS_WIDTH 512
#define CANVAS_HEIGHT 512

// Function prototypes
void init_opengl(GLFWwindow *wnd);
void set_3D_projection();
static void on_error_callback(int error, const char *description);
static void on_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
static void on_resize_callback(GLFWwindow *window, int width, int height);
static void on_mouse_position_callback(GLFWwindow *window, double x, double y);
static void on_mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
void run(GLFWwindow *wnd);
void process_keys(GLFWwindow *wnd);
void update(GLFWwindow *wnd);
void render(GLFWwindow *wnd);

float mx;
float my;
// Player player;
Camera camera;
Scene scene;
Map map;
MiniMap minimap;
Ghost ghost;

bool firstMouse = true;
float lastX = CANVAS_WIDTH / 2, lastY = CANVAS_HEIGHT / 2;

void init_opengl(GLFWwindow *wnd)
{

	glfwMakeContextCurrent(wnd);
	glfwSetKeyCallback(wnd, on_key_callback);
	glfwSetWindowSizeCallback(wnd, on_resize_callback);
	glfwSetCursorPosCallback(wnd, on_mouse_position_callback);
	glfwSetMouseButtonCallback(wnd, on_mouse_button_callback);

	glfwSetWindowAspectRatio(wnd, 1, 1);
	glfwSetInputMode(wnd, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// OpenGL states
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glPointSize(5.0);
	glLineWidth(2.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glFrontFace(GL_CCW);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void set_2D_projection()
{
	// Set projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(
		0, CANVAS_WIDTH,
		0, CANVAS_HEIGHT,
		-1.0, 1.0);
}

void set_3D_projection()
{
	glMatrixMode(GL_PROJECTION);
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	GLfloat fov = 70.0f;
	GLfloat z_near = 0.1f;
	GLfloat z_far = 1000.0f;
	GLfloat aspect = float(viewport[2]) / float(viewport[3]);
	GLfloat fh = tan(float(fov / 360.0f * 3.14159265358f)) * z_near;
	GLfloat fw = fh * aspect;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-fw, fw, -fh, fh, z_near, z_far);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

static void on_error_callback(int error, const char *description)
{
	cout << "on_error_callback : " << endl;
	cout << "  code : " << error << endl;
	cout << "  description : " << description << endl;
}

static void on_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	// cout << "on_key_callback : " << key << ", " << scancode << ", " << action << ", " << mods << endl;

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

static void on_resize_callback(GLFWwindow *window, int width, int height)
{
	// cout << "on_resize_callback : " << width << ", " << height << endl;

	// Set viewport
	glViewport(0, 0, width, height);

	// set_2D_projection();

	// Set projection matrix
	// set_3D_projection();
}

void on_mouse_position_callback(GLFWwindow *window, double x, double y)
{
	// cout << "on_mouse_callback : " << x << ", " << y << endl;
	mx = x;
	my = CANVAS_HEIGHT - y;
}

void on_mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
	// cout << "on_mouse_button_callback : " << button << ", " << action << ", " << mods << endl;
}

void run(GLFWwindow *wnd)
{
	cout << "Start runing the main loop..." << endl;
	while (!glfwWindowShouldClose(wnd))
	{
		process_keys(wnd);
		update(wnd);
		render(wnd);
	}
}

void process_keys(GLFWwindow *wnd)
{
	// Process keyboard
	camera.ProcessKeyboard(wnd);

	if (firstMouse)
	{
		lastX = mx;
		lastY = my;
		firstMouse = false;
	}

	float xoffset = mx - lastX;
	float yoffset = -my + lastY;
	lastX = mx;
	lastY = my;
	if (xoffset == 512 || yoffset == -256)
	{
		xoffset = 0;
		yoffset = 0;
	}
	camera.ProcessMouseMovement(xoffset, yoffset, GL_TRUE);
}

void update(GLFWwindow *wnd)
{
	// get player position to draw
	float cx, cy, cz;
	camera.getPosition(&cx, &cy, &cz);

	bool check = map.checkCollision(&cx, &cy, &cz);
	camera.updateCollision(check);

	minimap.updatePosition(&cx, &cy, &cz, G);

	ghost.chasePlayer(&cx, &cy, &cz);

	// get ghost position to draw
	float gx, gy, gz;
	ghost.getPosition(&gx, &gy, &gz);
	minimap.updatePosition(&gx, &gy, &gz, R);

	// get door position
	float dx, dy, dz;
	map.getDoorPos(&dx, &dy, &dz);

	// scene check logic to show gameover or survive
	scene.updateLogic(&cx, &cz,
					  &gx, &gz,
					  &dx, &dz);
}

void render(GLFWwindow *wnd)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// 3D section
	set_3D_projection();

	// camera or player
	camera.render();
	// camera.Debug(); // return log from class atrribute

	// render map
	map.render();
	ghost.render();
	// ghost.Debug(); // return log from class atrribute

	// 2D section
	glLoadIdentity();
	set_2D_projection();
	minimap.render();
	scene.render();

	glfwSwapBuffers(wnd);
	glfwPollEvents();
}

int main()
{

	GLFWwindow *gl_wnd;

	// Create OpenGL window
	glfwSetErrorCallback(on_error_callback);
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
	gl_wnd = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "The Escape", NULL, NULL);
	if (!gl_wnd)
	{
		glfwTerminate();
		cout << "Cannot initialize OpenGL!" << endl;
		system("PAUSE");
		exit(EXIT_FAILURE);
	}

	// Initialize OpenGL's states
	init_opengl(gl_wnd);
	srand(time(NULL));

	// load texture
	map.loadTexture();
	ghost.loadTexture();
	scene.loadTexture();

	map.setDoorPos(-255.0, 0.0, 210.0);
	map.setDoorRot(180.0);

	camera.setPosition(-230.0, 0.0, -220.0);
	camera.setDegree(0.0, -90.0, 0.0);

	ghost.setPosition(220, -20.0, -220);
	ghost.setDegree(0.0, 0.0, 0.0);

	// Enter main loop
	run(gl_wnd);

	// Done.
	// system("PAUSE");
	return 0;
}
