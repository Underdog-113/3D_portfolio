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


Material _SmokeTrail_Plane02default {
 0.588000;0.588000;0.588000;1.000000;;
 10.000000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;
}

Frame SmokeTrail_Plane02_0 {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh SmokeTrail_Plane02_0 {
  12;
  -0.500000;0.002313;0.000000;,
  0.500000;0.433013;-5.000000;,
  -0.500000;0.433013;-5.000000;,
  0.500000;0.002313;0.000000;,
  0.248497;0.433013;0.000000;,
  0.000000;-0.433013;-5.000000;,
  0.500000;0.433013;-5.000000;,
  -0.251503;-0.433013;0.000000;,
  -0.250436;0.433013;0.000000;,
  0.000000;-0.433013;-5.000000;,
  -0.500000;0.433013;-5.000000;,
  0.249563;-0.433013;0.000000;;
  6;
  3;0,1,2;,
  3;3,1,0;,
  3;4,5,6;,
  3;7,5,4;,
  3;8,9,10;,
  3;11,9,8;;

  MeshMaterialList {
   1;
   6;
   0,
   0,
   0,
   0,
   0,
   0;
   { _SmokeTrail_Plane02default }
  }

  DeclData {
   2;
   2;0;3;0;,
   1;0;5;0;;
   60;
   0,
   1065291316,
   1034929017,
   1065353216,
   0,
   0,
   1065291316,
   1034929017,
   0,
   1065353216,
   0,
   1065291316,
   1034929017,
   0,
   0,
   0,
   1065291316,
   1034929017,
   1065353216,
   1065353216,
   1063091729,
   3204432361,
   1026703946,
   1065353216,
   0,
   1063091729,
   3204432361,
   1026703946,
   0,
   1065353216,
   1063091729,
   3204432361,
   1026703946,
   0,
   0,
   1063091729,
   3204432361,
   1026703946,
   1065353216,
   1065353216,
   1063091942,
   1056948951,
   3174097691,
   1065353216,
   0,
   1063091942,
   1056948951,
   3174097691,
   0,
   1065353216,
   1063091941,
   1056948955,
   3174097692,
   0,
   0,
   1063091941,
   1056948955,
   3174097692,
   1065353216,
   1065353216;
  }
 }
}