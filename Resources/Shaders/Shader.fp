#version 410

in vec4 outColor;

out vec4 fragColor;
void main(){
	fragColor = outColor;
  //fragColor = vec4(1.0f,0.0f,0.0f,1.0f);
}
