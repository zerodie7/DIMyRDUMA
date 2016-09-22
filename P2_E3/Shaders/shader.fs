#version 330 core
struct Material {
    float shininess;
};


struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;  
in vec3 Normal;
in vec2 TexCoords;
  
out vec4 color;

uniform sampler2D texture_diffuse1;
uniform vec3 viewPos;
uniform Light light;  
uniform Material material;

void main()
{
    // Ambient
    vec3 ambient = light.ambient * vec3(texture(texture_diffuse1, TexCoords));
  	
    // Diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse1, TexCoords));
    
    // Specular
    float specularStrength = 0.5f;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * vec3(texture(texture_diffuse1, TexCoords)));
    
    //color = vec4(ambient + diffuse + specular, 1.0f);
    color = vec4(ambient + diffuse, 1.0f);
}
 