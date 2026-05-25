  #version 330 core

  uniform sampler2D Texture0;
  uniform sampler2D Texture1;
  
  varying vec2 TexCoord0;
  //-------------------
  void main()
  {  
     vec4 texel0, texel1, resultColor;
     //-------------------
     texel0 = texture2D(Texture0, TexCoord0);
     texel1 = texture2D(Texture1, TexCoord0);
     //-------------------
     resultColor = mix(texel0, texel1, texel0.a);
     gl_FragColor = resultColor;
  }