#include "glsl.h"
#include "asset.h"

void Glsl::init(const char* vertex_fp, const char* fragment_fp)
{
	compile_shaders("shaders/colorShading.vert", "shaders/colorShading.frag");
	bind_attribute();
	link_shaders();
}

void Glsl::compile_shaders(const char* vertex_fp, const char* fragment_fp)
{
	program_id_ = glCreateProgram();
	vertex_id_ = glCreateShader(GL_VERTEX_SHADER);
	fragment_id_ = glCreateShader(GL_FRAGMENT_SHADER);
	compile_shader(vertex_id_, vertex_fp);
    compile_shader(fragment_id_, fragment_fp);
}

void Glsl::bind_attribute()
{
    glBindAttribLocation(program_id_, 0, "vertexPosition");
	glBindAttribLocation(program_id_, 1, "vertexColor");
	glBindAttribLocation(program_id_, 2, "vertexUV");	
}

void Glsl::compile_shader(GLuint id, const char* fp)
{
	assert(id != 0);
	const char *buffer = ggl_asset_load_file(fp);

	glShaderSource(id, 1, &buffer, NULL);
	glCompileShader(id);

	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	debug("GLSL compilation status = %d for %s", success, fp);
	if (success != GL_TRUE)
	{
		GLint log_length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &log_length);

		GLchar* info_log = (GLchar *) malloc(sizeof(char) * (log_length + 1));
		glGetShaderInfoLog(id, log_length, NULL, info_log);

		log_err("File %s : GLSL compilation error %s", fp, info_log);

		free(info_log);

		//We don't need the shader anymore.
		glDeleteShader(id);
	}

	free((void *)buffer);

	// abort on failed compilation
	assert(success == GL_TRUE);
}

void Glsl::link_shaders()
{
    //Vertex and fragment shaders are successfully compiled.
    //Now time to link them together into a program.
    //Get a program object.
    GLuint program = program_id_;
    
    //Attach our shaders to our program
    glAttachShader(program, vertex_id_);
    glAttachShader(program, fragment_id_);
    
    //Link our program
    glLinkProgram(program);
    
    //Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
    if(isLinked == GL_FALSE)
    {
        log_err("Failed to links shaders");
        return;
    }
    
    //Always detach shaders after a successful link.
    glDetachShader(program, vertex_id_);
    glDetachShader(program, fragment_id_);
    
    glDeleteShader(vertex_id_);
    glDeleteShader(fragment_id_);
}

GLint Glsl::get_uniform_location(const char *uniformName)
{
	GLint location = glGetUniformLocation(program_id_, uniformName);

	if (location == GL_INVALID_INDEX)
	{
		debug("glGetUniformLocation returned an invalid index for name %s", uniformName);
	}

	return location;
}

void Glsl::enable_shaders()
{
    glUseProgram(program_id_);
    // vertex position 
    glEnableVertexAttribArray(0);
    // vertex color
	glEnableVertexAttribArray(1);
	// uv
	glEnableVertexAttribArray(2);

}

void Glsl::disable_shaders()
{
    glUseProgram(0);
    // vertex position 
    glDisableVertexAttribArray(0);
    // vertex color    
	glDisableVertexAttribArray(1);
	// uv
	glDisableVertexAttribArray(2);
}

