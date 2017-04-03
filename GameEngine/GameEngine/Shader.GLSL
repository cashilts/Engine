
attribute vec3 vertex;
attribute vec3 normal;
attribute vec2 TexCoord;
attribute vec2 Index;
attribute vec2 Weight;

uniform mat4 ModelView;
uniform mat4 Projection;
uniform mat4 Bone[30];
uniform mat4 invTBone[30];

varying vec2 TexCoord0;
varying vec3 EyeNormal;

void main()
{
 vec4 newVertex;
 vec4 newNormal;
 int index;
 index = int(Index.x);
 newVertex = (Bone[index] * vec4(vertex,1))*Weight.x;
 newNormal = (Bone[index] * vec4(normal,0.0)) * Weight.x;
 index = int(Index.y);
 newVertex = (Bone[index] * vec4(vertex,1)) * Weight.y + newVertex;
 newNormal = (Bone[index] * vec4(normal,0.0)) * Weight.y + newNormal;
 EyeNormal = vec3(ModelView * newNormal);
 gl_Position = gl_ModelViewProjectionMatrix * newVertex;
 TexCoord0 = TexCoord;
}
