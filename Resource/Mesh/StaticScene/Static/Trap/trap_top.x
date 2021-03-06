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

template MeshMaterialList {
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
}

template VertexElement {
 <f752461c-1e23-48f6-b9f8-8350850f336f>
 DWORD Type;
 DWORD Method;
 DWORD Usage;
 DWORD UsageIndex;
}

template DeclData {
 <bf22e553-292c-4781-9fea-62bd554bdd93>
 DWORD nElements;
 array VertexElement Elements[nElements];
 DWORD nDWords;
 array DWORD data[nDWords];
}


Material Spike {
 1.000000;1.000000;1.000000;1.000000;;
 43.219280;
 0.020000;0.020000;0.020000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "Spike.png";
 }
}

Frame Trap_Spike_Special {
 

 FrameTransformMatrix {
  0.492126,0.000000,0.000000,0.000000,0.000000,-0.000000,-0.492126,0.000000,0.000000,0.492126,-0.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Frame Spike {
  

  FrameTransformMatrix {
   1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,-0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
  }

  Frame Model_11 {
   

   FrameTransformMatrix {
    1.000000,0.000000,0.000000,0.000000,0.000000,-0.000000,1.000000,0.000000,0.000000,-1.000000,-0.000000,0.000000,0.137489,0.142373,0.012992,1.000000;;
   }

   Mesh Model_11 {
    24;
    0.069272;0.000000;0.056677;,
    -0.069272;-0.000000;-0.056677;,
    0.056677;0.000000;0.069272;,
    -0.056677;-0.000000;-0.069272;,
    -0.044082;0.000000;0.069272;,
    -0.069272;0.000000;0.044082;,
    -0.217528;0.000000;0.056677;,
    -0.356072;-0.000000;-0.056677;,
    -0.230123;0.000000;0.069272;,
    -0.343477;-0.000000;-0.069272;,
    -0.330882;0.000000;0.069272;,
    -0.356072;0.000000;0.044082;,
    -0.217528;0.000000;0.352719;,
    -0.356072;-0.000000;0.239364;,
    -0.230123;0.000000;0.365314;,
    -0.343477;-0.000000;0.226769;,
    -0.330882;0.000000;0.365314;,
    -0.356072;0.000000;0.340124;,
    0.069272;0.000000;0.352719;,
    -0.069272;-0.000000;0.239364;,
    0.056677;0.000000;0.365314;,
    -0.056677;-0.000000;0.226769;,
    -0.044082;0.000000;0.365314;,
    -0.069272;0.000000;0.340124;;
    16;
    3;0,1,2;,
    3;3,1,0;,
    3;2,1,4;,
    3;4,1,5;,
    3;6,7,8;,
    3;9,7,6;,
    3;8,7,10;,
    3;10,7,11;,
    3;12,13,14;,
    3;15,13,12;,
    3;14,13,16;,
    3;16,13,17;,
    3;18,19,20;,
    3;21,19,18;,
    3;20,19,22;,
    3;22,19,23;;

    MeshMaterialList {
     1;
     16;
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
     0,
     0,
     0,
     0,
     0;
     { Spike }
    }

    DeclData {
     2;
     2;0;3;0;,
     1;0;5;0;;
     120;
     0,
     1065353216,
     0,
     1058310244,
     1033900704,
     0,
     1065353216,
     0,
     1061195319,
     1049874742,
     0,
     1065353216,
     0,
     1057988758,
     1036469632,
     0,
     1065353216,
     0,
     1061516811,
     1049232508,
     0,
     1065353216,
     0,
     1057988758,
     1048590276,
     0,
     1065353216,
     0,
     1058631730,
     1049874742,
     0,
     1065353216,
     0,
     1058310244,
     1033900704,
     0,
     1065353216,
     0,
     1061195319,
     1049874742,
     0,
     1065353216,
     0,
     1057988758,
     1036469632,
     0,
     1065353216,
     0,
     1061516811,
     1049232508,
     0,
     1065353216,
     0,
     1057988758,
     1048590276,
     0,
     1065353216,
     0,
     1058631730,
     1049874742,
     0,
     1065353216,
     0,
     1058310244,
     1033900704,
     0,
     1065353216,
     0,
     1061195319,
     1049874742,
     0,
     1065353216,
     0,
     1057988758,
     1036469632,
     0,
     1065353216,
     0,
     1061516811,
     1049232508,
     0,
     1065353216,
     0,
     1057988758,
     1048590276,
     0,
     1065353216,
     0,
     1058631730,
     1049874742,
     0,
     1065353216,
     0,
     1058310244,
     1033900704,
     0,
     1065353216,
     0,
     1061195319,
     1049874742,
     0,
     1065353216,
     0,
     1057988758,
     1036469632,
     0,
     1065353216,
     0,
     1061516811,
     1049232508,
     0,
     1065353216,
     0,
     1057988758,
     1048590276,
     0,
     1065353216,
     0,
     1058631730,
     1049874742;
    }
   }
  }
 }
}