#include "glsl.h"

void ggl_glsl_compile_shaders(struct ggl_glsl *glsl, const char* vertex_fp, const char* fragment_fp)
{
	glsl->program_id = glCreateProgram();
	glsl->vertex_id = glCreateShader(GL_VERTEX_SHADER);
	glsl->fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
	ggl_glsl_compile_shader(glsl->vertex_id, vertex_fp);
    ggl_glsl_compile_shader(glsl->fragment_id, fragment_fp);
}

void ggl_glsl_compile_shader(GLuint id, const char* fp)
{
	assert(id != 0);
	char *buffer = ggl_glsl_read_file(fp);

	glShaderSource(id, 1, &buffer, NULL);
	glCompileShader(id);

	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	debug("GLSL compilation status = %d for %s", success, fp);
	if (success != GL_TRUE)
	{
		GLint log_length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &log_length);

		GLchar* info_log = malloc(sizeof(char) * (log_length + 1));
		glGetShaderInfoLog(id, log_length, NULL, info_log);

		log_err("File %s : GLSL compilation error %s", fp, info_log);

		free(info_log);

		//We don't need the shader anymore.
		glDeleteShader(id);
	}

	free(buffer);
}

void ggl_glsl_link_shaders(struct ggl_glsl *glsl)
{
    //Vertex and fragment shaders are successfully compiled.
    //Now time to link them together into a program.
    //Get a program object.
    GLuint program = glsl->program_id;
    
    //Attach our shaders to our program
    glAttachShader(program, glsl->vertex_id);
    glAttachShader(program, glsl->fragment_id);
    
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
    glDetachShader(program, glsl->vertex_id);
    glDetachShader(program, glsl->fragment_id);
    
    glDeleteShader(glsl->vertex_id);
    glDeleteShader(glsl->fragment_id);
}

void ggl_glsl_bind_attribute(struct ggl_glsl *glsl)
{
    glBindAttribLocation(glsl->program_id, 0, "vertexPosition");
	glBindAttribLocation(glsl->program_id, 1, "vertexColor");
}

char *ggl_glsl_read_file(const char* file_path)
{
    FILE *fp;
    long lSize;
    char *buffer;
    
    fp = fopen ( file_path , "rb" );
    if( !fp ) perror(file_path),exit(1);
    
    fseek( fp , 0L , SEEK_END);
    lSize = ftell( fp );
    rewind( fp );
    
    /* allocate memory for entire content */
    buffer = calloc( 1, lSize+1 );
    if( !buffer ) fclose(fp),fputs("memory alloc fails",stderr),exit(1);
    
    /* copy the file into the buffer */
    if( 1!=fread( buffer , lSize, 1 , fp) )
        fclose(fp),free(buffer),fputs("entire read fails",stderr),exit(1);
    
    /* do your work here, buffer is a string contains the whole text */
    
    fclose(fp);
    return buffer;
}

void ggl_glsl_destroy(struct ggl_glsl *glsl)
{
    assert (glsl != NULL);
    free(glsl);
}
