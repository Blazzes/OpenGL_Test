#include "Camera.h"
#include <iostream>
Camera::Camera(glm::vec3 pos, glm::vec3 up, GLfloat yaw, GLfloat pitch) :
	cameraData({
	pos,
	glm::vec3(0.0f,0.0f,-1.0f),
	glm::vec3(0.0f,0.0f,0.0f),
	glm::vec3(0.0f,0.0f,0.0f),
	up,
	yaw, pitch, SPEED, SENSITIVITY, ZOOM})
{
	updateCameraVerctors();
	std::cout << "Camera Create" << std::endl;
}

Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch) :
	cameraData({
	glm::vec3(posX, posY, posZ),
	glm::vec3(0.0f,0.0f,-1.0f),
	glm::vec3(0.0f,0.0f,0.0f),
	glm::vec3(0.0f,0.0f,0.0f),
	glm::vec3(upX, upY, upZ),
	yaw, pitch, SPEED, SENSITIVITY, ZOOM })
{
	updateCameraVerctors();
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(cameraData.position, cameraData.position + cameraData.front, cameraData.up);
}

void Camera::keyboardEvent(Camera_Movement direction, GLfloat deltaTime)
{
	GLfloat velocity = cameraData.moveSpeed * deltaTime;
	switch (direction)
	{
	case Camera_Movement::FORWARD:
		cameraData.position += cameraData.front * velocity;
		break;
	case Camera_Movement::BACKWARD:
		cameraData.position -= cameraData.front * velocity;
		break;
	case Camera_Movement::LEFT:
		cameraData.position -= cameraData.right * velocity;
		break; 
	case Camera_Movement::RIGHT:
		cameraData.position += cameraData.right * velocity;
		break;
	default:
		break;
	}

}

void Camera::mouseMovmentEvent(GLfloat offX, GLfloat offY, GLboolean constrainPitch)
{
	offX *= cameraData.mouseSens;
	offY *= cameraData.mouseSens;

	cameraData.yaw += offX;
	cameraData.pitch += offY;

	if (constrainPitch)
	{
		if (cameraData.pitch > 89.0f)
			cameraData.pitch = 89.0f;
		if (cameraData.pitch < -89.0f)
			cameraData.pitch = -89.0f;
	}

	updateCameraVerctors();
}

void Camera::mouseScrollEvent(GLfloat offY)
{
	if (cameraData.zoom >= 1.0f && cameraData.zoom <= 45.0f)
		cameraData.zoom -= offY;
	if (cameraData.zoom <= 1.0f)
		cameraData.zoom = 1.0f;
	if (cameraData.zoom >= 45.0f)
		cameraData.zoom = 45.0f;
}

Camera::CameraData Camera::getCameraData()
{
	return cameraData;
}

void Camera::updateCameraVerctors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(cameraData.pitch)) * cos(glm::radians(cameraData.yaw));
	front.y = sin(glm::radians(cameraData.pitch));
	front.z = cos(glm::radians(cameraData.pitch)) * sin(glm::radians(cameraData.yaw));
	cameraData.front = glm::normalize(front);

	cameraData.right = glm::normalize(glm::cross(cameraData.front, cameraData.worldUp));
	cameraData.up = glm::normalize(glm::cross(cameraData.right, cameraData.front));
	std::cout << cameraData.position.x << "  " << cameraData.position.y << "  " << cameraData.position.z << std::endl;
}
