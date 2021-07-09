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


Material Mat_S01_Screen04 {
 1.000000;1.000000;1.000000;1.000000;;
 43.219280;
 0.020000;0.020000;0.020000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "S01_Screen02.png";
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

    Frame S01_Screen04 {
     

     FrameTransformMatrix {
      1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.310000,1.000000;;
     }

     Mesh S01_Screen04 {
      18;
      -8.164453;14.571782;5.642485;,
      -6.785869;16.958122;1.948712;,
      -6.785869;16.958107;5.642485;,
      -8.164453;14.571800;1.948712;,
      6.779805;17.014739;5.642485;,
      8.158388;14.628434;1.948712;,
      8.158388;14.628418;5.642485;,
      6.779805;17.014757;1.948712;,
      -3.890742;18.694355;5.642485;,
      -1.900576;18.694387;1.948712;,
      -1.900576;18.694355;5.642485;,
      -3.890742;18.694387;1.948712;,
      0.089619;18.694355;5.642485;,
      0.089619;18.694387;1.948712;,
      2.079805;18.694387;1.948712;,
      2.079805;18.694355;5.642485;,
      4.070000;18.694355;5.642485;,
      4.070000;18.694387;1.948712;;
      12;
      3;0,1,2;,
      3;3,1,0;,
      3;4,5,6;,
      3;7,5,4;,
      3;8,9,10;,
      3;11,9,8;,
      3;9,12,10;,
      3;13,12,9;,
      3;14,12,13;,
      3;15,12,14;,
      3;15,14,16;,
      3;16,14,17;;

      MeshNormals {
       18;
       0.865894;-0.500228;-0.000002;,
       0.865894;-0.500228;-0.000002;,
       0.865894;-0.500228;-0.000002;,
       0.865894;-0.500228;-0.000002;,
       -0.865894;-0.500228;-0.000002;,
       -0.865894;-0.500228;-0.000002;,
       -0.865894;-0.500228;-0.000002;,
       -0.865894;-0.500228;-0.000002;,
       0.000000;-1.000000;-0.000009;,
       0.000000;-1.000000;-0.000009;,
       0.000000;-1.000000;-0.000009;,
       0.000000;-1.000000;-0.000009;,
       0.000000;-1.000000;-0.000009;,
       0.000000;-1.000000;-0.000009;,
       0.000000;-1.000000;-0.000009;,
       0.000000;-1.000000;-0.000009;,
       0.000000;-1.000000;-0.000009;,
       0.000000;-1.000000;-0.000009;;
       12;
       3;0,1,2;,
       3;3,1,0;,
       3;4,5,6;,
       3;7,5,4;,
       3;8,9,10;,
       3;11,9,8;,
       3;9,12,10;,
       3;13,12,9;,
       3;14,12,13;,
       3;15,12,14;,
       3;15,14,16;,
       3;16,14,17;;
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
       { Mat_S01_Screen04 }
      }

      MeshTextureCoords c1 {
       18;
       -0.945119;0.500100;,
       -0.412185;0.999942;,
       -0.412185;0.500100;,
       -0.945119;0.999942;,
       -0.617059;0.500100;,
       -0.087483;0.999942;,
       -0.087483;0.500100;,
       -0.617059;0.999942;,
       0.002586;0.500100;,
       0.499994;0.999942;,
       0.499994;0.500100;,
       0.002586;0.999942;,
       0.998495;0.500100;,
       0.998495;0.999942;,
       0.499994;0.999942;,
       0.499994;0.500100;,
       0.002586;0.500100;,
       0.002586;0.999942;;
      }

      MeshTextureCoords c2 {
       18;
       0.399562;0.572933;,
       0.444520;0.503344;,
       0.444520;0.572933;,
       0.399562;0.503344;,
       0.299420;0.572933;,
       0.344378;0.503344;,
       0.344378;0.572933;,
       0.299420;0.503344;,
       0.291629;0.646836;,
       0.329123;0.577247;,
       0.329123;0.646836;,
       0.291629;0.577246;,
       0.366616;0.646836;,
       0.366616;0.577247;,
       0.404110;0.577247;,
       0.404110;0.646836;,
       0.441603;0.646836;,
       0.441603;0.577247;;
      }
     }
    }
   }
  }
 }
}