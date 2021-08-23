#pragma once
#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum class Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 3.0f;
const GLfloat SENSITIVITY = 0.15f;
const GLfloat ZOOM = 45.0f;

class Camera
{
public:
	struct CameraData {
		glm::vec3 position;
		glm::vec3 front;
		glm::vec3 up;
		glm::vec3 right;
		glm::vec3 worldUp;
		GLfloat yaw, pitch;
		GLfloat moveSpeed, mouseSens, zoom;
	};

	Camera(
		glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
		GLfloat yaw = YAW, GLfloat pitch = PITCH);
	Camera(
		GLfloat posX, GLfloat posY, GLfloat posZ,
		GLfloat upX, GLfloat upY, GLfloat upZ,
		GLfloat yaw = YAW, GLfloat pitch = PITCH);
	glm::mat4 getViewMatrix();
	void keyboardEvent(Camera_Movement direction, GLfloat deltaTime);
	void mouseMovmentEvent(GLfloat offX, GLfloat offY, GLboolean constrainPitch = true);
	void mouseScrollEvent(GLfloat offY);
	CameraData getCameraData();
private:
	void updateCameraVerctors();
	CameraData cameraData;
};

