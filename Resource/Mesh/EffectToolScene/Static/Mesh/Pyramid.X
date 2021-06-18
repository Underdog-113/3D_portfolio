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


Material _Pyramid001default {
 0.588000;0.588000;0.588000;1.000000;;
 10.000000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;
}

Frame Pyramid001_0 {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh Pyramid001_0 {
  17;
  -0.025000;-0.025000;0.000000;,
  0.000000;0.000000;-1.500000;,
  0.025000;-0.025000;0.000000;,
  0.025000;-0.025000;0.000000;,
  0.000000;0.000000;-1.500000;,
  0.025000;0.025000;0.000000;,
  0.025000;0.025000;0.000000;,
  0.000000;0.000000;-1.500000;,
  -0.025000;0.025000;0.000000;,
  -0.025000;0.025000;0.000000;,
  0.000000;0.000000;-1.500000;,
  -0.025000;-0.025000;0.000000;,
  0.000000;0.000000;0.000000;,
  -0.025000;-0.025000;0.000000;,
  0.025000;-0.025000;0.000000;,
  0.025000;0.025000;0.000000;,
  -0.025000;0.025000;0.000000;;
  8;
  3;0,1,2;,
  3;3,4,5;,
  3;6,7,8;,
  3;9,10,11;,
  3;12,13,14;,
  3;12,14,15;,
  3;12,15,16;,
  3;12,16,13;;

  MeshMaterialList {
   1;
   8;
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0;
   { _Pyramid001default }
  }

  DeclData {
   2;
   2;0;3;0;,
   1;0;5;0;;
   85;
   0,
   3212834534,
   3163063213,
   0,
   1065353216,
   0,
   3212834534,
   3163063213,
   1056964608,
   0,
   0,
   3212834534,
   3163063213,
   1065353216,
   1065353216,
   1065350886,
   0,
   3163063213,
   0,
   1065353216,
   1065350886,
   0,
   3163063213,
   1056964608,
   0,
   1065350886,
   0,
   3163063213,
   1065353216,
   1065353216,
   0,
   1065350886,
   3163063213,
   0,
   1065353216,
   0,
   1065350886,
   3163063213,
   1056964608,
   0,
   0,
   1065350886,
   3163063213,
   1065353216,
   1065353216,
   3212834534,
   0,
   3163063213,
   0,
   1065353216,
   3212834534,
   0,
   3163063213,
   1056964608,
   0,
   3212834534,
   0,
   3163063213,
   1065353216,
   1065353216,
   0,
   0,
   1065353216,
   1056964608,
   1056964608,
   0,
   0,
   1065353216,
   0,
   0,
   0,
   0,
   1065353216,
   1065353216,
   0,
   0,
   0,
   1065353216,
   1065353216,
   1065353216,
   0,
   0,
   1065353216,
   0,
   1065353216;
  }
 }
}