xof 0303txt 0032
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


Frame Plane002 {
 

 FrameTransformMatrix {
  -0.001607,0.000000,-0.475509,0.000000,0.000000,1.000000,0.000000,0.000000,0.997639,0.000000,-0.003371,0.000000,0.000000,0.000000,-15.918301,1.000000;;
 }

 Mesh Plane002 {
  8;
  -33.341587;0.000000;0.743596;,
  -11.113863;0.000000;0.743596;,
  -33.341587;0.000000;-0.743596;,
  -11.113863;0.000000;-0.743596;,
  11.113861;0.000000;0.743596;,
  11.113861;0.000000;-0.743596;,
  33.341584;0.000000;0.743596;,
  33.341584;0.000000;-0.743596;;
  6;
  3;0,1,2;,
  3;3,2,1;,
  3;1,4,3;,
  3;5,3,4;,
  3;4,6,5;,
  3;7,5,6;;

  MeshMaterialList {
   1;
   6;
   0,
   0,
   0,
   0,
   0,
   0;

   Material  {
    0.694118;0.345098;0.105882;1.000000;;
    0.000000;
    0.000000;0.000000;0.000000;;
    0.000000;0.000000;0.000000;;
   }
  }

  DeclData {
   2;
   2;0;3;0;,
   1;0;5;0;;
   40;
   0,
   1065353216,
   0,
   1065370503,
   0,
   0,
   1065353216,
   0,
   1059795384,
   0,
   0,
   1065353216,
   0,
   1065370503,
   1065353216,
   0,
   1065353216,
   0,
   1059795384,
   1065353216,
   0,
   1065353216,
   0,
   1051372202,
   3137801728,
   0,
   1065353216,
   0,
   1051372202,
   1065318642,
   0,
   1065353216,
   0,
   0,
   3137801728,
   0,
   1065353216,
   0,
   0,
   1065318642;
  }
 }
}