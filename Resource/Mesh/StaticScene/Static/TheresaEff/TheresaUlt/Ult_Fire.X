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


Material Material__30 {
 1.000000;1.000000;1.000000;1.000000;;
 10.000000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "Ult_Fire.png";
 }
}

Frame Plane004 {
 

 FrameTransformMatrix {
  -0.000000,0.000000,-1.485627,0.000000,-1.485627,-0.000000,0.000000,0.000000,-0.000000,1.485627,0.000000,0.000000,0.000000,0.000000,-0.000000,1.000000;;
 }

 Mesh Plane004 {
  4;
  -0.000000;2.045978;-0.017268;,
  0.000000;-2.045978;3.516056;,
  -0.000000;-2.045976;-0.017269;,
  0.000000;2.045976;3.516058;;
  2;
  3;0,1,2;,
  3;1,0,3;;

  MeshMaterialList {
   1;
   2;
   0,
   0;
   { Material__30 }
  }

  DeclData {
   2;
   2;0;3;0;,
   1;0;5;0;;
   20;
   1065353216,
   697615257,
   3019898880,
   1029114432,
   1064472412,
   1065353216,
   697615257,
   3019898880,
   1064472412,
   1029114432,
   1065353216,
   697615257,
   3019898880,
   1064472412,
   1064472412,
   1065353216,
   697615257,
   3019898880,
   1029114432,
   1029114432;
  }
 }
}