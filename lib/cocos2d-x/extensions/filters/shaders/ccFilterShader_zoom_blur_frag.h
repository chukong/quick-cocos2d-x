"varying highp vec2 v_texCoord;\n\
\n\
uniform sampler2D CC_Texture0;\n\
\n\
uniform highp vec2 u_blurCenter;\n\
uniform highp float u_blurSize;\n\
\n\
void main()\n\
{\n\
    // TODO: Do a more intelligent scaling based on resolution here\n\
    highp vec2 samplingOffset = 1.0/100.0 * (u_blurCenter - v_texCoord) * u_blurSize;\n\
    \n\
    lowp vec4 fragmentColor = texture2D(CC_Texture0, v_texCoord) * 0.18;\n\
    fragmentColor += texture2D(CC_Texture0, v_texCoord + samplingOffset) * 0.15;\n\
    fragmentColor += texture2D(CC_Texture0, v_texCoord + (2.0 * samplingOffset)) *  0.12;\n\
    fragmentColor += texture2D(CC_Texture0, v_texCoord + (3.0 * samplingOffset)) * 0.09;\n\
    fragmentColor += texture2D(CC_Texture0, v_texCoord + (4.0 * samplingOffset)) * 0.05;\n\
    fragmentColor += texture2D(CC_Texture0, v_texCoord - samplingOffset) * 0.15;\n\
    fragmentColor += texture2D(CC_Texture0, v_texCoord - (2.0 * samplingOffset)) *  0.12;\n\
    fragmentColor += texture2D(CC_Texture0, v_texCoord - (3.0 * samplingOffset)) * 0.09;\n\
    fragmentColor += texture2D(CC_Texture0, v_texCoord - (4.0 * samplingOffset)) * 0.05;\n\
    \n\
    gl_FragColor = fragmentColor;\n\
}";
