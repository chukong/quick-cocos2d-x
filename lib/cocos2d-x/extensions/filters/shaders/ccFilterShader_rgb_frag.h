 "varying highp vec2 v_texCoord;\n\
 \n\
 uniform sampler2D CC_Texture0;\n\
 \n\
 uniform highp float u_redAdj;\n\
 uniform highp float u_greenAdj;\n\
 uniform highp float u_blueAdj;\n\
 \n\
 void main()\n\
 {\n\
     highp vec4 textureColor = texture2D(CC_Texture0, v_texCoord);\n\
     gl_FragColor = vec4(textureColor.r * u_redAdj, textureColor.g * u_greenAdj, textureColor.b * u_blueAdj, textureColor.a);\n\
 }";
