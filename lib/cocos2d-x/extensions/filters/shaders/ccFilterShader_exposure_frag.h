"varying mediump vec2 v_texCoord;\n\
\n\
uniform sampler2D CC_Texture0;\n\
uniform highp float u_exposure;\n\
\n\
void main()\n\
{\n\
    highp vec4 textureColor = texture2D(CC_Texture0, v_texCoord);\n\
    gl_FragColor = vec4(textureColor.rgb * pow(2.0, u_exposure), textureColor.w);\n\
}";

