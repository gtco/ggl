#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera2d
{
public:
	Camera2d();
	~Camera2d();

	void init(int screen_height, int screen_width);

	void set_position(glm::vec2 position);
	void set_scale(float scale);

    glm::vec2 get_position() { return position_; };
	float get_scale() { return scale_; };
	glm::mat4 get_camera_matrix() { return camera_matrix_; };
	glm::mat4 get_ortho_matrix() { return ortho_matrix_; };

	void update();
    
private:
	int screen_width_;
	int screen_height_;
	float scale_;
	glm::vec2 position_;
	glm::mat4 camera_matrix_;
	glm::mat4 ortho_matrix_;
	bool requires_update_;
};
