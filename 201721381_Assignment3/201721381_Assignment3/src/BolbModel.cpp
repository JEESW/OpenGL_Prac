

#include "GL/glew.h"
#include "glm/glm.hpp"
#include <iostream>
#include <fstream>
#include "../BaseCodes/Mesh.h"
#include "BolbModel.h"


///////////////////////////////////////////////
// Two-Triangle

static GLuint g_bolb_vao;
static GLuint g_bolb_vbo_pos;
static GLuint g_bolb_vbo_color;
static GLuint g_bolb_vbo_normal;
static GLuint g_bolb_index_buf;

static Mesh g_bolb_mesh;

void InitBolbModel()
{
	g_bolb_mesh.ReadObjFormatFile("../Data/bolb.obj");

	g_bolb_mesh.TriangulateAndUniformizeBuffers();

	g_bolb_mesh.ScaleUniformlyVertices(0.3f);
	g_bolb_mesh.TranslateVertices(glm::vec3(6.f, 0.f, 0.f));

	// Vertex Array Object
	glGenVertexArrays(1, &g_bolb_vao);
	glBindVertexArray(g_bolb_vao);


	// Position VBO
	glGenBuffers(1, &g_bolb_vbo_pos);
	glBindBuffer(GL_ARRAY_BUFFER, g_bolb_vbo_pos);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * g_bolb_mesh.num_points(), g_bolb_mesh.points(), GL_STATIC_DRAW);

	// Color VBO
	glGenBuffers(1, &g_bolb_vbo_color);
	glBindBuffer(GL_ARRAY_BUFFER, g_bolb_vbo_color);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * g_bolb_mesh.num_points(), g_bolb_mesh.colors(), GL_STATIC_DRAW);

	// Normal VBO
	glGenBuffers(1, &g_bolb_vbo_normal);
	glBindBuffer(GL_ARRAY_BUFFER, g_bolb_vbo_normal);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * g_bolb_mesh.num_points(), g_bolb_mesh.normals(), GL_STATIC_DRAW);


	// Index Buffer Object
	glGenBuffers(1, &g_bolb_index_buf);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_bolb_index_buf);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 3 * g_bolb_mesh.num_triangles(), g_bolb_mesh.triangle_ids(), GL_STATIC_DRAW);


	// Vertex Attribute
	glBindBuffer(GL_ARRAY_BUFFER, g_bolb_vbo_pos);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, g_bolb_vbo_color);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, g_bolb_vbo_normal);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
}


void DrawBolbModel()
{
	glBindVertexArray(g_bolb_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_bolb_index_buf);
	glDrawElements(GL_TRIANGLES, g_bolb_mesh.num_triangles() * 3, GL_UNSIGNED_INT, NULL);
}


void DeleteBolbModel()
{
	glDeleteBuffers(1, &g_bolb_vbo_pos);
	glDeleteBuffers(1, &g_bolb_vbo_normal);
	glDeleteBuffers(1, &g_bolb_index_buf);
	glDeleteVertexArrays(1, &g_bolb_vao);
}




