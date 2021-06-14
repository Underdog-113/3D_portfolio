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


Material _Plane001default {
 0.588000;0.588000;0.588000;1.000000;;
 10.000000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;
}

Frame Plane001_0 {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh Plane001_0 {
  10;
  -16.193661;-0.777777;6.553802;,
  -32.209322;1.814825;-6.464697;,
  -32.209322;1.814813;6.553802;,
  -16.193661;-0.777765;-6.464697;,
  -0.178009;-1.814833;6.553802;,
  -0.178009;-1.814821;-6.464697;,
  15.837650;-0.777777;6.553802;,
  15.837650;-0.777765;-6.464697;,
  32.209309;1.814813;6.553802;,
  32.209309;1.814825;-6.464697;;
  8;
  3;0,1,2;,
  3;3,1,0;,
  3;4,3,0;,
  3;5,3,4;,
  3;6,5,4;,
  3;7,5,6;,
  3;8,7,6;,
  3;9,7,8;;

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
   { _Plane001default }
  }

  DeclData {
   2;
   2;0;3;0;,
   1;0;5;0;;
   50;
   1038487753,
   1065247020,
   0,
   1061036260,
   1053370738,
   1042522666,
   1065137624,
   0,
   1065142835,
   1044813192,
   1042522666,
   1065137624,
   0,
   1065142835,
   1053370740,
   1038487753,
   1065247020,
   0,
   1061036260,
   1044813184,
   0,
   1065353216,
   0,
   1056894768,
   1053370738,
   0,
   1065353216,
   0,
   1056894768,
   1044813184,
   3185742506,
   1065250229,
   0,
   1048681619,
   1053370738,
   3185742506,
   1065250229,
   0,
   1048681623,
   1044813184,
   3189778881,
   1065146728,
   0,
   994076327,
   1053370738,
   3189778881,
   1065146728,
   0,
   994076516,
   1044813180;
  }
 }
}