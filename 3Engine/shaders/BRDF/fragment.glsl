#version 330 core

in vec4 ex_Color;
in vec2 ex_TexCoord;
in vec3 ex_Normal;
in vec3 ex_Eye;

out vec4 out_Color;

uniform SharedMatrices {
    mat4 ViewMatrix;
    mat4 ProjectionMatrix;
};

uniform vec4 BaseColor;
uniform float Metallic;
uniform float Roughness;

uniform samplerCube cube_tex;

const float PI = 3.1415926535897932384626433832795;
const float PI_2 = 1.57079632679489661923;
const float PI_4 = 0.785398163397448309616;

vec4 Lambert(vec4 color) {
    return vec4(color.xyz/PI, color.w);
}

vec3 SpecularIBL( vec3 SpecularColor, float roughness, vec3 N, vec3 V );
vec3 DeffuseFresnel(vec3 diffuseColor, float roughness, vec3 N, vec3 V);

void main(void)
{
	vec3 e = normalize(ex_Eye);
	vec3 n = normalize(ex_Normal);

	mat4 invV = inverse(ViewMatrix);

    vec3 l = normalize(vec3(-1, -1, -1));
	vec3 h = normalize(l + e);

//	vec3 reflected = reflect(-e, n);
//	reflected = vec3(invV * vec4(reflected, 0.0));
//  vec4 reflection = texture(cube_tex, reflected);

//	float ratio = 1.0 /1.3333;
//	vec3 refracted = refract(-e, n, ratio);
//	refracted = vec3(invV * vec4(refracted, 0.0));


    float roughness = Roughness;

//    vec4 diffuse = Lambert(BaseColor);
    vec4 diffuse = vec4(DeffuseFresnel(BaseColor.xyz, roughness, n, e),
                        BaseColor.w);

    vec3 specularTint = mix(vec3(0.15,0.15,0.15), BaseColor.xyz, Metallic);
    vec4 specular = vec4(SpecularIBL(specularTint, roughness, n, e),
                        BaseColor.w);

    out_Color = (1 - Metallic) * diffuse + specular;
}

// Diffuse

vec3 DeffuseFresnel(vec3 diffuseColor, float roughness, vec3 N, vec3 V) {
    float VoN = dot(V, N);

    float FD90 = 0.5 + 2 * pow(VoN,2) * roughness;

    vec3 lambert = diffuseColor/PI;
    float fresnel = pow((1 + (FD90 - 1) * pow( 1-VoN, 5) ), 2);

    return lambert * fresnel;
}

// Specular

float UG1(float NoV, float roughness) {
    float k = pow(roughness + 1 , 2) / 8;

    return NoV / NoV * (1-k) + k;
}

float UG(float NoV, float NoL, float roughness) {
    return UG1(NoV, roughness) * UG1(NoL, roughness);
}

float radicalInverse_VdC(uint bits) {
    bits = (bits << 16u) | (bits >> 16u);
    bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
    bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
    bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
    bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);
    return float(bits) * 2.3283064365386963e-10; // / 0x100000000
}

vec2 hammersley2d(uint i, uint N)
{
    return vec2(float(i)/float(N), radicalInverse_VdC(i));
}

vec3 ImportanceSampleGGX( vec2 Xi, float roughness, vec3 N )
{
    float a = roughness * roughness;
    float Phi = 2 * PI * Xi.x;
    float CosTheta = sqrt( (1 - Xi.y) / ( 1 + (a*a - 1) * Xi.y ) );
    float SinTheta = sqrt( 1 - CosTheta * CosTheta );
    vec3 H;
    H.x = SinTheta * cos( Phi );
    H.y = SinTheta * sin( Phi );
    H.z = CosTheta;
    vec3 UpVector = abs(N.z) < 0.999 ? vec3(0,0,1) : vec3(1,0,0);
    vec3 TangentX = normalize( cross( UpVector, N ) );
    vec3 TangentY = cross( N, TangentX );
    // Tangent to world space
    return TangentX * H.x + TangentY * H.y + N * H.z;
}

const uint NumberOfSamples = uint(128);

vec3 SpecularIBL( vec3 SpecularColor, float roughness, vec3 N, vec3 V )
{
	mat4 invV = inverse(ViewMatrix);
    vec3 SpecularLighting = vec3(0);
    const uint NumSamples = uint(NumberOfSamples);
    for( uint i = uint(0); i < NumSamples; i++ )
    {
        vec2 Xi = hammersley2d( i, NumSamples );
        vec3 H = ImportanceSampleGGX( Xi, roughness, N );
        vec3 L = 2 * dot( V, H ) * H - V;
        float NoV = clamp( dot( N, V ) ,0.0,1.0);
        float NoL = clamp( dot( N, L ) ,0.0,1.0);
        float NoH = clamp( dot( N, H ) ,0.0,1.0);
        float VoH = clamp( dot( V, H ) ,0.0,1.0);
        if( NoL > 0 )
        {
	        L = vec3(invV * vec4(L, 0.0));
            vec3 SampleColor = texture(cube_tex, L).rgb;
            float G = UG( NoV, NoL, roughness);
            float Fc = pow( 1 - VoH, 5 );
            vec3 F = (1 - Fc) * SpecularColor + Fc;
            // Incident light = SampleColor * NoL
            // Microfacet specular = D*G*F / (4*NoL*NoV)
            // pdf = D * NoH / (4 * VoH)
            SpecularLighting += SampleColor * F * G * VoH / (NoH * NoV);
        }
    }
    return SpecularLighting / NumSamples;
}