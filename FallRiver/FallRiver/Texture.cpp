
#include "Texture.h"
#include "ViewManager.h"

Texture::Texture()
{
	filename[0] = '\0';	
	ref = 0;					
	texture = nullptr;				
	Width = 0;					
	Height = 0;	
}