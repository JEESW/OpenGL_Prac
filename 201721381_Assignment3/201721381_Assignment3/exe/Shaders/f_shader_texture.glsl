#version 330

in vec4 fs_color;
in vec2 fs_uv;
in vec3 fs_normal;
in vec3 fs_eye_dir;

uniform int shading_mode = 1;

layout (location = 0) out vec4 color;

uniform vec3 light_position;
uniform vec3 light_dir;
uniform vec3 light_dir2;
uniform float light_cos_cutoff;
uniform vec3 I_l;

uniform sampler2D tex0;
uniform bool flag_texture;

void main()
{
	float I_a = 0.05f;
	float shininess_n = 50.f;
	vec3 K_a = vec3(1.f, 1.f, 1.f);
	vec3 K_d = vec3(1.f, 1.f, 1.f);
	vec3 K_s = vec3(0.3f, 0.3f, 0.3f);

	vec3 L = normalize(light_position-fs_eye_dir);
	vec3 N = normalize(fs_normal);
	vec3 V = normalize(-fs_eye_dir);
	vec3 H = (L+V)/length(L+V);
	vec3 Sd = normalize(-light_dir);

	
	vec3 ambient = I_a * K_a;
	vec3 diffuse = I_l * K_d * max(0.f, dot(L, N));
	vec3 specular = I_l * K_s * pow(max(0.f, dot(N, H)), shininess_n);

	if ( dot(Sd, L) < light_cos_cutoff )
	{
		diffuse = vec3(0, 0, 0);
		specular = vec3(0, 0, 0);
	}

	if (flag_texture)
		color = vec4((ambient + diffuse + specular), 1.f) * texture(tex0, fs_uv);
	else
		color = vec4((ambient + diffuse + specular), 1.f) * fs_color;

	if (shading_mode == 2)
	{
		vec3 L2 = normalize(-light_dir2);
		vec3 N2 = normalize(fs_normal);
		vec3 V2 = normalize(-fs_eye_dir);
		vec3 H2 = (L+V)/length(L+V);
	
		vec3 ambient2 = I_a * K_a;
		vec3 diffuse2 = I_l * K_d * max(0.f, dot(L2, N2));
		vec3 specular2 = I_l * K_s * pow(max(0.f, dot(N2, H2)), shininess_n);

		if (flag_texture)
			color = color + vec4((ambient2 + diffuse2 + specular2), 1.f) * texture(tex0, fs_uv);
		else
			color = color + vec4((ambient2 + diffuse2 + specular2), 1.f) * fs_color;
	}
}