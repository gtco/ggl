#include "camera2d.h"

Camera2d::Camera2d() : position_(0.0f, 0.0f), camera_matrix_(1.0f), requires_update_(true), screen_width_(1), screen_height_(1), ortho_matrix_(1.0f)
{
}

Camera2d::~Camera2d()
{
}

void Camera2d::init(int screen_width, int screen_height)
{
	screen_height_ = screen_height;
	screen_width_ = screen_width;
	ortho_matrix_ = glm::ortho(0.0f, (float)screen_width_, 0.0f, (float)screen_height_);
}

void Camera2d::set_position(glm::vec2 & position)
{
	position_ = position;
}

void Camera2d::set_scale(float scale)
{
}

void Camera2d::update()
{
	if (requires_update_)
	{
		glm::vec3 translate(-position_.x, -position_.y, 0.0f);
		camera_matrix_ = glm::translate(ortho_matrix_, translate);
		glm::vec3 scale(scale_, scale_, 0.0f);
		camera_matrix_ = glm::scale(camera_matrix_, scale);
	}
}
