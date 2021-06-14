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


Material _SmokeTrail_Plane03default {
 0.588000;0.588000;0.588000;1.000000;;
 10.000000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;
}

Frame SmokeTrail_Plane03_0 {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh SmokeTrail_Plane03_0 {
  12;
  -0.500000;0.001157;-0.002003;,
  0.500000;-4.113620;-2.875000;,
  -0.500000;-4.113620;-2.875000;,
  0.500000;0.001157;-0.002003;,
  0.248497;0.216506;-0.375000;,
  0.000000;-4.546633;-2.125000;,
  0.500000;-4.113620;-2.875000;,
  -0.251503;-0.216506;0.375000;,
  -0.250436;0.216506;-0.375000;,
  0.000000;-4.546633;-2.125000;,
  -0.500000;-4.113620;-2.875000;,
  0.249563;-0.216506;0.375000;;
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
   { _SmokeTrail_Plane03default }
  }

  DeclData {
   2;
   2;0;3;0;,
   1;0;5;0;;
   60;
   0,
   1058180609,
   3209815609,
   1065353216,
   0,
   0,
   1058180609,
   3209815609,
   0,
   1065353216,
   0,
   1058180609,
   3209815609,
   0,
   0,
   0,
   1058180609,
   3209815609,
   1065353216,
   1065353216,
   1063091729,
   3193514444,
   1055433271,
   1065353216,
   0,
   1063091729,
   3193514444,
   1055433271,
   0,
   1065353216,
   1063091729,
   3193514444,
   1055433271,
   0,
   0,
   1063091729,
   3193514444,
   1055433271,
   1065353216,
   1065353216,
   1063091941,
   1046050499,
   3202911507,
   1065353216,
   0,
   1063091941,
   1046050499,
   3202911507,
   0,
   1065353216,
   1063091941,
   1046050499,
   3202911510,
   0,
   0,
   1063091941,
   1046050499,
   3202911510,
   1065353216,
   1065353216;
  }
 }
}