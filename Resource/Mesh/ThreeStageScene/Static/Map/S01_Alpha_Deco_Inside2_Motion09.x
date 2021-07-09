xof 0303txt 0032
template ColorRGBA {
 <35ff44e0-6c7c-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <d3e16e81-7835-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template Material {
 <3d82ab4d-62da-11cf-ab39-0020af71e433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template TextureFilename {
 <a42790e1-7810-11cf-8f52-0040333594a3>
 STRING filename;
}

template Frame {
 <3d82ab46-62da-11cf-ab39-0020af71e433>
 [...]
}

template Matrix4x4 {
 <f6f23f45-7686-11cf-8f52-0040333594a3>
 array FLOAT matrix[16];
}

template FrameTransformMatrix {
 <f6f23f41-7686-11cf-8f52-0040333594a3>
 Matrix4x4 frameMatrix;
}

template Vector {
 <3d82ab5e-62da-11cf-ab39-0020af71e433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template MeshFace {
 <3d82ab5f-62da-11cf-ab39-0020af71e433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template Mesh {
 <3d82ab44-62da-11cf-ab39-0020af71e433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template MeshNormals {
 <f6f23f43-7686-11cf-8f52-0040333594a3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshMaterialList {
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
}

template Coords2d {
 <f6f23f44-7686-11cf-8f52-0040333594a3>
 FLOAT u;
 FLOAT v;
}

template MeshTextureCoords {
 <f6f23f40-7686-11cf-8f52-0040333594a3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}


Material S01_T_Inside_02_Flow {
 1.000000;1.000000;1.000000;1.000000;;
 43.219280;
 0.020000;0.020000;0.020000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "S0_T1.png";
 }
}

Frame PerpStage_InSide__merge_ {
 

 FrameTransformMatrix {
  0.393701,0.000000,0.000000,0.000000,0.000000,-0.000000,-0.393701,0.000000,0.000000,0.393701,-0.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Frame PerpStage_InSide {
  

  FrameTransformMatrix {
   1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,137.919360,18.917622,-5.310000,1.000000;;
  }

  Frame PerpStage_S01_Inside2 {
   

   FrameTransformMatrix {
    1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
   }

   Frame S01_Inside2_Motion {
    

    FrameTransformMatrix {
     1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
    }

    Frame S01_Inside2_Motion09 {
     

     FrameTransformMatrix {
      1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,-0.059982,-0.019999,-0.010000,1.000000;;
     }

     Mesh S01_Inside2_Motion09 {
      24;
      -57.785005;-2.421831;0.296925;,
      51.277293;-2.331346;0.296925;,
      -57.784928;-2.314751;0.296925;,
      51.277283;-2.438467;0.296925;,
      -57.781082;4.606322;0.296925;,
      51.277293;4.702632;0.296925;,
      -57.781024;4.713393;0.296925;,
      51.277283;4.595507;0.296925;,
      -57.785005;-3.867398;-8.755391;,
      51.277293;-3.776914;-8.755391;,
      -57.784928;-3.760318;-8.755391;,
      51.277283;-3.884034;-8.755391;,
      -57.781082;5.405910;-8.755391;,
      51.277293;5.502220;-8.755391;,
      -57.781024;5.512980;-8.755391;,
      51.277283;5.395094;-8.755391;,
      -57.785005;-19.123413;-13.112673;,
      51.277293;-19.032928;-13.112673;,
      -57.784928;-19.016333;-13.112673;,
      51.277283;-19.140050;-13.112673;,
      -57.781082;-10.683345;-13.112673;,
      51.277293;-10.587034;-13.112673;,
      -57.781024;-10.576274;-13.112673;,
      51.277283;-10.694159;-13.112673;;
      12;
      3;0,1,2;,
      3;3,1,0;,
      3;4,5,6;,
      3;7,5,4;,
      3;8,9,10;,
      3;11,9,8;,
      3;12,13,14;,
      3;15,13,12;,
      3;16,17,18;,
      3;19,17,16;,
      3;20,21,22;,
      3;23,21,20;;

      MeshNormals {
       24;
       0.000000;0.000000;1.000000;,
       0.000000;0.000000;1.000000;,
       0.000000;0.000000;1.000000;,
       0.000000;0.000000;1.000000;,
       0.000000;0.000000;1.000000;,
       0.000000;0.000000;1.000000;,
       0.000000;0.000000;1.000000;,
       0.000000;0.000000;1.000000;,
       0.000000;0.000000;1.000000;,
       0.000000;0.000000;1.000000;,
       0.000000;0.000000;1.000000;,
       0.000000;0.000000;1.000000;,
       0.000000;0.000000;1.000000;,
       0.000000;0.000000;1.000000;,
       0.000000;0.000000;1.000000;,
       0.000000;0.000000;1.000000;,
       0.000000;0.000009;1.000000;,
       0.000000;0.000009;1.000000;,
       0.000000;0.000009;1.000000;,
       0.000000;0.000009;1.000000;,
       0.000000;0.000000;1.000000;,
       0.000000;0.000000;1.000000;,
       0.000000;0.000000;1.000000;,
       0.000000;0.000000;1.000000;;
       12;
       3;0,1,2;,
       3;3,1,0;,
       3;4,5,6;,
       3;7,5,4;,
       3;8,9,10;,
       3;11,9,8;,
       3;12,13,14;,
       3;15,13,12;,
       3;16,17,18;,
       3;19,17,16;,
       3;20,21,22;,
       3;23,21,20;;
      }

      MeshMaterialList {
       1;
       12;
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0,
       0;
       { S01_T_Inside_02_Flow }
      }

      MeshTextureCoords c1 {
       24;
       -1.754122;0.812931;,
       -19.052291;0.792576;,
       -1.754131;0.799299;,
       -19.052294;0.806213;,
       -1.754128;0.812890;,
       -19.054242;0.794888;,
       -1.754133;0.799258;,
       -19.054245;0.808527;,
       -1.754122;0.812931;,
       -19.052291;0.792576;,
       -1.754131;0.799299;,
       -19.052294;0.806213;,
       -1.754128;0.812890;,
       -19.054242;0.794888;,
       -1.754133;0.799258;,
       -19.054245;0.808527;,
       -1.754122;0.812931;,
       -19.052291;0.792576;,
       -1.754131;0.799299;,
       -19.052294;0.806213;,
       -1.754128;0.812890;,
       -19.054242;0.794888;,
       -1.754133;0.799258;,
       -19.054245;0.808527;;
      }
     }
    }
   }
  }
 }
}