#version 330 core

struct Material 
{
    vec3 ambient;
    sampler2D diffuseMap;
    vec3 specular;
    float shininess;
};

struct DirectionalLight
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse; 
	vec3 specular;
};

struct PointLight
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse; 
	vec3 specular;

	float constant;
	float linear;
	float exponent;
};

struct SpotLight
{
	vec3 position;
	vec3 direction;
	float cosInnerCone;
	float cosOuterCone;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	int on;

	float constant;
	float linear;
	float exponent;
};
  
 in vec3 vertexNormal; 
 in vec3 vertexFragmentPos; 
 in vec2 vertexTextureCoordinate;

#define MAX_POINT_LIGHTS 3

out vec4 fragmentColor;

uniform DirectionalLight naturalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLight;
uniform Material material;
uniform vec3 viewPos; 

vec3 calcDirectionalLightColor(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 calcPointLightColor(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 calcSpotLightColor(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{ 
	vec3 normal = normalize(vertexNormal);  
	vec3 viewDir = normalize(viewPos - vertexFragmentPos);

    // Ambient ----------------------------------------------------------------------------------
	vec3 ambient = spotLight.ambient * material.ambient * vec3(texture(material.diffuseMap, vertexTextureCoordinate));
	vec3 outColor = vec3(0.0f);	

	outColor += calcDirectionalLightColor(naturalLight, normal, viewDir);

   for(int i = 0; i < MAX_POINT_LIGHTS; i++)
        outColor += calcPointLightColor(pointLights[i], normal, vertexFragmentPos, viewDir);  

	// If the light isn't on then just return 0 for diffuse and specular colors
	if (spotLight.on == 1)
		outColor += calcSpotLightColor(spotLight, normal, vertexFragmentPos, viewDir);

	fragmentColor = vec4(ambient + outColor, 1.0f);
}

vec3 calcDirectionalLightColor(DirectionalLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);  
	// Diffuse ------------------------------------------------------------------------- --------
    	float NdotL = max(dot(normal, lightDir), 0.0);
    	vec3 diffuse = light.diffuse * NdotL * vec3(texture(material.diffuseMap, vertexTextureCoordinate));
    
     	// Specular - Blinn-Phong ------------------------------------------------------------------
	vec3 halfDir = normalize(lightDir + viewDir);
	float NDotH = max(dot(normal, halfDir), 0.0f);
	vec3 specular = light.specular * material.specular * pow(NDotH, material.shininess);

	return (diffuse + specular);
}

//-----------------------------------------------------------------------------------------------
// Calculate the point light effect and return the resulting diffuse and specular color summation
//-----------------------------------------------------------------------------------------------
vec3 calcPointLightColor(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);

	// Diffuse ----------------------------------------------------------------------------------
    	float NdotL = max(dot(normal, lightDir), 0.0);
    	vec3 diffuse = light.diffuse * NdotL * vec3(texture(material.diffuseMap, vertexTextureCoordinate));
    
     	// Specular - Blinn-Phong ------------------------------------------------------------------
	vec3 halfDir = normalize(lightDir + viewDir);
	float NDotH = max(dot(normal, halfDir), 0.0f);
	vec3 specular = light.specular * material.specular * pow(NDotH, material.shininess);

	// Attenuation using Kc, Kl, Kq -------------------------------------------------------------
	float d = length(light.position - vertexFragmentPos);
	float attenuation = 1.0f / (light.constant + light.linear * d + light.exponent * (d * d));

	diffuse *= attenuation;
	specular *= attenuation;
	
	return (diffuse + specular);
}

vec3 calcSpotLightColor(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
	vec3 spotDir  = normalize(light.direction);

	float cosDir = dot(-lightDir, spotDir);  
	float spotIntensity = smoothstep(light.cosOuterCone, light.cosInnerCone, cosDir);

	// Diffuse ----------------------------------------------------------------------------------
   	float NdotL = max(dot(normal, lightDir), 0.0);
    	vec3 diffuse = spotLight.diffuse * NdotL * vec3(texture(material.diffuseMap, vertexTextureCoordinate));
    
     	// Specular - Blinn-Phong ------------------------------------------------------------------
	vec3 halfDir = normalize(lightDir + viewDir);
	float NDotH = max(dot(normal, halfDir), 0.0f);
	vec3 specular = light.specular * material.specular * pow(NDotH, material.shininess);

	// Attenuation using Kc, Kl, Kq -------------------------------------------------------------
	float d = length(light.position - vertexFragmentPos);
	float attenuation = 1.0f / (light.constant + light.linear * d + light.exponent * (d * d));

	diffuse *= attenuation * spotIntensity;
	specular *= attenuation * spotIntensity;
	
	return (diffuse + specular);
}

