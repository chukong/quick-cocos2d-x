"varying mediump vec2 v_texCoord;\n\
\n\
uniform sampler2D CC_Texture0;\n\
uniform mediump float u_brightness;\n\
\n\
void main()\n\
{\n\
 lowp vec4 textureColor = texture2D(CC_Texture0, v_texCoord);\n\
 gl_FragColor = vec4((textureColor.rgb + vec3(u_brightness)), textureColor.w);\n\
}";
