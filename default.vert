#version 330 core

layout(location = 0) in vec3 aPos;

uniform vec3 u_position;
uniform vec3 u_scale;
uniform vec3 u_rotation;
uniform vec3 u_camera;


void main() {
	
	mat4 position = mat4(
		1.0,			0.0,			0.0,			0.0,
		0.0,			1.0,			0.0,			0.0,
		0.0,			0.0,			1.0,			0.0,
		u_position.x,	u_position.y,	u_position.z,	1.0
	);

	mat4 scale = mat4(
		u_scale.x,		0.0,			0.0,			0.0,
		0.0,			u_scale.y,		0.0,			0.0,
		0.0,			0.0,			u_scale.z,		0.0,
		0.0,			0.0,			0.0,			1.0
	);

	mat4 view = mat4(
		1.0,			0.0,			0.0,			0.0,
		0.0,			1.0,			0.0,			0.0,
		0.0,			0.0,			1.0,			0.0,
		-u_camera.x,	-u_camera.y,	-u_camera.z,	1.0
	);

    gl_Position = view * position * scale * vec4(aPos,1.0);
}