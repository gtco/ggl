#include "asset.h"

const char *ggl_asset_load_file(const char* file_path)
{
    FILE *fp;
    long sz;
    uint8_t *buffer;
    
    fp = fopen(file_path , "rb");
    if (!fp)
    {
    	perror(file_path);
    	return false;
    } 
    
    fseek(fp, 0L, SEEK_END);
    sz = ftell(fp);
    rewind(fp);
    
    /* allocate memory for entire content */
    buffer = calloc(1, sz+1);
    if (!buffer)
    {
		fclose(fp);
    	debug("Memory alloc fails %s", file_path);
    	return false;
    } 
    
    /* copy the file into the buffer */
    if(1 != fread(buffer, sz, 1, fp))
    {
        fclose(fp);
        free(buffer);
        debug("Entire read fails %s", file_path);
        return false;
    }
    
    fclose(fp);
	return (const char*) buffer;
}
