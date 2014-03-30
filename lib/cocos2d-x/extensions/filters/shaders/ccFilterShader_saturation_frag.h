"varying highp vec2 v_texCoord;\n\
\n\
uniform sampler2D CC_Texture0;\n\
uniform lowp float u_saturation;\n\
\n\
const mediump vec3 luminanceWeighting = vec3(0.2125, 0.7154, 0.0721);\n\
\n\
void main()\n\
{\n\
   lowp vec4 textureColor = texture2D(CC_Texture0, v_texCoord);\n\
   lowp float luminance = dot(textureColor.rgb, luminanceWeighting);\n\
   lowp vec3 greyScaleColor = vec3(luminance);\n\
   \n\
   gl_FragColor = vec4(mix(greyScaleColor, textureColor.rgb, u_saturation), textureColor.w);\n\
}";

