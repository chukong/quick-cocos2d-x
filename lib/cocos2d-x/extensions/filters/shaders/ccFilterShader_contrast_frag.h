"varying mediump vec2 v_texCoord;\n\
\n\
uniform sampler2D CC_Texture0;\n\
uniform lowp float u_contrast;\n\
\n\
void main()\n\
{\n\
    lowp vec4 textureColor = texture2D(CC_Texture0, v_texCoord);\n\
    gl_FragColor = vec4(((textureColor.rgb - vec3(0.5)) * u_contrast + vec3(0.5)), textureColor.w);\n\
}";

