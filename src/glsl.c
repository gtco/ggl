#include "glsl.h"

void ggl_glsl_compile_shaders(struct ggl_glsl *glsl, const char* vertex_fp, const char* fragment_fp)
{
    glsl->vertex_id = 0;
    glsl->fragment_id = 0;
	glsl->program_id = 0;
    
    char *vs_buffer = ggl_glsl_read_file(vertex_fp);
    glsl->vertex_id = glCreateShader(GL_VERTEX_SHADER);
    if (glsl->vertex_id == 0)
    {
        log_err("Failed to create vertex shader id");
    }
    const char* v = vs_buffer;
    glShaderSource(glsl->vertex_id, 1, &v, NULL);
    
	//compile the shader
	glCompileShader(glsl->vertex_id);

    GLint success = 0;
    glGetShaderiv(glsl->vertex_id, GL_COMPILE_STATUS, &success);
    if(success != GL_TRUE)
    {
        GLint maxLength = 0;
        glGetShaderiv(glsl->vertex_id, GL_INFO_LOG_LENGTH, &maxLength);
        
        //The maxLength includes the NULL character
//        GLchar infoLog[maxLength];
//        glGetShaderInfoLog(glsl->vertex_id, maxLength, &maxLength, infoLog);
        
        //We don't need the shader anymore.
        glDeleteShader(glsl->vertex_id);
        
        //Use the infoLog as you see fit.
    }

    char *fs_buffer = ggl_glsl_read_file(fragment_fp);
    glsl->fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
    if (glsl->fragment_id == 0)
    {
        log_err("Failed to create fragment shader id");
    }
    const char* f = fs_buffer;
    glShaderSource(glsl->fragment_id, 1, &f, NULL);
    
	//compile the shader
	glCompileShader(glsl->fragment_id);

    success = 0;
    glGetShaderiv(glsl->fragment_id, GL_COMPILE_STATUS, &success);
    
    if (success != GL_TRUE)
    {
        GLint maxLength = 0;
        glGetShaderiv(glsl->fragment_id, GL_INFO_LOG_LENGTH, &maxLength);
        
        //The maxLength includes the NULL character
//        GLchar infoLog[maxLength];
//        glGetShaderInfoLog(glsl->fragment_id, maxLength, &maxLength, infoLog);
        
        //We don't need the shader anymore.
        glDeleteShader(glsl->fragment_id);
        
        //Use the infoLog as you see fit.
    }
    
    free(vs_buffer);
    free(fs_buffer);
}

void ggl_glsl_link_shaders(struct ggl_glsl *glsl)
{
    //Vertex and fragment shaders are successfully compiled.
    //Now time to link them together into a program.
    //Get a program object.
	glsl->program_id = glCreateProgram();
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


