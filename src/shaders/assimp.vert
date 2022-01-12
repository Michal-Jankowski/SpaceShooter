#version 460 core

#include structs.incl

layout(location = 0) in vec3 verPos;
layout(location = 1) in vec2 verTexCoord;
layout(location = 2) in vec3 verNormal;
layout(location = 3) in vec3 verTangent;
layout(location = 4) in vec3 verBitangent;

out VS_OUT{
	vec2 verTexCoord;
	vec3 verNormal;
	vec4 worldPosition;
	vec4 cameraSpacePosition;

	TangentSpace tangentSpace;
} vs_out;

uniform vec3 cameraPosition;
uniform Matrices matrices;
uniform Material material;
uniform DiffuseLight diffuseLight;


void main() 
{
	mat4 MV_Matrix = matrices.viewMatrix * matrices.modelMatrix;
	mat4 MVP_matrix = matrices.projectionMatrix * MV_Matrix;

	vs_out.verTexCoord = verTexCoord;
	vs_out.verNormal = matrices.normalMatrix * verNormal;
	vs_out.worldPosition = matrices.modelMatrix * vec4(verPos, 1.0);
	vs_out.cameraSpacePosition = MV_Matrix * vec4(verPos, 1.0);

	if(material.useNormalMap){
		vec3 T = normalize(vec3(matrices.modelMatrix * vec4(verTangent, 0.0)));
		vec3 B = normalize(vec3(matrices.modelMatrix * vec4(verBitangent, 0.0)));
		vec3 N = normalize(vec3(matrices.modelMatrix * vec4(verNormal, 0.0)));
		mat3 TBN = transpose(mat3(T, B, N));
		vs_out.tangentSpace.diffusePos = normalize(TBN * diffuseLight.direction.xyz); //sic!
		vs_out.tangentSpace.camPos = normalize(TBN * cameraPosition);
		vs_out.tangentSpace.worldPos = normalize(TBN * vs_out.worldPosition.xyz);
	}
	else {
		vs_out.tangentSpace.diffusePos = diffuseLight.direction;
	}

	gl_Position = MVP_matrix * vec4(verPos, 1.0);
}