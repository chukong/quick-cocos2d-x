"precision highp float;\n\
varying highp vec2 v_texCoord;\n\
varying highp vec2 v_leftTexCoord;\n\
varying highp vec2 v_rightTexCoord; \n\
varying highp vec2 v_topTexCoord;\n\
varying highp vec2 v_bottomTexCoord;\n\
\n\
varying highp float v_centerMultiplier;\n\
varying highp float v_edgeMultiplier;\n\
\n\
uniform sampler2D CC_Texture0;\n\
\n\
void main()\n\
{\n\
    mediump vec3 textureColor = texture2D(CC_Texture0, v_texCoord).rgb;\n\
    mediump vec3 leftTexColor = texture2D(CC_Texture0, v_leftTexCoord).rgb;\n\
    mediump vec3 rightTexColor = texture2D(CC_Texture0, v_rightTexCoord).rgb;\n\
    mediump vec3 topTexColor = texture2D(CC_Texture0, v_topTexCoord).rgb;\n\
    mediump vec3 bottomTexColor = texture2D(CC_Texture0, v_bottomTexCoord).rgb;\n\
\n\
	vec3 v1 = leftTexColor * v_edgeMultiplier + rightTexColor * v_edgeMultiplier + topTexColor * v_edgeMultiplier + bottomTexColor * v_edgeMultiplier;\n\
	vec3 v2 = textureColor * v_centerMultiplier - v1;\n\
	vec4 v3 = texture2D(CC_Texture0, v_bottomTexCoord);\n\
\n\
    gl_FragColor = vec4(v2, v3.w);\n\
}";
