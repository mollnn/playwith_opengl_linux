#version 330 core
in vec2 TexCoord;
in float offset_v_;

out vec4 color;

// Texture samplers
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;


void main()
{
	// Linearly interpolate between both textures (second texture is only slightly combined)
	color = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, vec2(TexCoord.x,TexCoord.y+offset_v_)), 0.2);
}