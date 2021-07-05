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


Material S01_T_Inside_01 {
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

    Frame S01_Inside2_Motion05 {
     

     FrameTransformMatrix {
      1.000000,0.000000,0.000000,0.000000,0.000000,0.698351,-0.715756,0.000000,0.000000,0.715756,0.698351,0.000000,21.930022,13.270001,4.700000,1.000000;;
     }

     Mesh S01_Inside2_Motion05 {
      82;
      7.182669;-2.333787;1.252736;,
      7.459323;-1.181438;-1.278831;,
      7.459323;-1.181438;1.252736;,
      7.182669;-2.333787;-1.278831;,
      6.729153;-3.428671;1.252736;,
      6.729153;-3.428671;-1.278831;,
      6.109944;-4.439130;1.252736;,
      6.109944;-4.439130;-1.278831;,
      5.340287;-5.340282;1.252736;,
      5.340287;-5.340282;-1.278831;,
      4.439136;-6.109939;1.252736;,
      4.439136;-6.109939;-1.278831;,
      3.428677;-6.729148;1.252736;,
      3.428677;-6.729148;-1.278831;,
      2.333793;-7.182665;1.252736;,
      2.333793;-7.182665;-1.278831;,
      1.181444;-7.459319;1.252736;,
      1.181444;-7.459319;-1.278831;,
      0.000003;-7.552302;1.252736;,
      0.000003;-7.552302;-1.278831;,
      -1.181437;-7.459319;1.252736;,
      -1.181437;-7.459319;-1.278831;,
      -2.333787;-7.182666;1.252736;,
      -2.333787;-7.182666;-1.278831;,
      -3.428671;-6.729150;1.252736;,
      -3.428671;-6.729150;-1.278831;,
      -4.439129;-6.109940;1.252736;,
      -4.439129;-6.109940;-1.278831;,
      -5.340282;-5.340284;1.252736;,
      -5.340282;-5.340284;-1.278831;,
      -6.109938;-4.439132;1.252736;,
      -6.109938;-4.439132;-1.278831;,
      -6.729148;-3.428673;1.252736;,
      -6.729148;-3.428673;-1.278831;,
      -7.182664;-2.333790;1.252736;,
      -7.182664;-2.333790;-1.278831;,
      -7.459318;-1.181440;1.252736;,
      -7.459318;-1.181440;-1.278831;,
      -7.552299;-0.000000;1.252736;,
      -7.552299;-0.000000;-1.278831;,
      -7.459318;1.181440;1.252736;,
      -7.459318;1.181440;-1.278831;,
      -7.182664;2.333789;1.252736;,
      -7.182664;2.333789;-1.278831;,
      -6.729148;3.428672;1.252736;,
      -6.729148;3.428672;-1.278831;,
      -6.109940;4.439131;1.252736;,
      -6.109940;4.439131;-1.278831;,
      -5.340282;5.340282;1.252736;,
      -5.340282;5.340282;-1.278831;,
      -4.439131;6.109940;1.252736;,
      -4.439131;6.109940;-1.278831;,
      -3.428672;6.729150;1.252736;,
      -3.428672;6.729150;-1.278831;,
      -2.333789;7.182666;1.252736;,
      -2.333789;7.182666;-1.278831;,
      -1.181440;7.459319;1.252736;,
      -1.181440;7.459319;-1.278831;,
      0.000001;7.552301;1.252736;,
      0.000001;7.552301;-1.278831;,
      1.181441;7.459319;1.252736;,
      1.181441;7.459319;-1.278831;,
      2.333790;7.182666;1.252736;,
      2.333790;7.182666;-1.278831;,
      3.428673;6.729150;1.252736;,
      3.428673;6.729150;-1.278831;,
      4.439132;6.109940;1.252736;,
      4.439132;6.109940;-1.278831;,
      5.340283;5.340283;1.252736;,
      5.340283;5.340283;-1.278831;,
      6.109940;4.439131;1.252736;,
      6.109940;4.439131;-1.278831;,
      6.729149;3.428673;1.252736;,
      6.729149;3.428673;-1.278831;,
      7.182664;2.333790;1.252736;,
      7.182664;2.333790;-1.278831;,
      7.459318;1.181441;1.252736;,
      7.459318;1.181441;-1.278831;,
      7.552299;0.000001;1.252736;,
      7.552299;0.000001;-1.278831;,
      7.459323;-1.181438;1.252736;,
      7.459323;-1.181438;-1.278831;;
      80;
      3;0,1,2;,
      3;3,1,0;,
      3;4,3,0;,
      3;5,3,4;,
      3;6,5,4;,
      3;7,5,6;,
      3;8,7,6;,
      3;9,7,8;,
      3;10,9,8;,
      3;11,9,10;,
      3;12,11,10;,
      3;13,11,12;,
      3;14,13,12;,
      3;15,13,14;,
      3;16,15,14;,
      3;17,15,16;,
      3;18,17,16;,
      3;19,17,18;,
      3;20,19,18;,
      3;21,19,20;,
      3;22,21,20;,
      3;23,21,22;,
      3;24,23,22;,
      3;25,23,24;,
      3;26,25,24;,
      3;27,25,26;,
      3;28,27,26;,
      3;29,27,28;,
      3;30,29,28;,
      3;31,29,30;,
      3;32,31,30;,
      3;33,31,32;,
      3;34,33,32;,
      3;35,33,34;,
      3;36,35,34;,
      3;37,35,36;,
      3;38,37,36;,
      3;39,37,38;,
      3;40,39,38;,
      3;41,39,40;,
      3;42,41,40;,
      3;43,41,42;,
      3;44,43,42;,
      3;45,43,44;,
      3;46,45,44;,
      3;47,45,46;,
      3;48,47,46;,
      3;49,47,48;,
      3;50,49,48;,
      3;51,49,50;,
      3;52,51,50;,
      3;53,51,52;,
      3;54,53,52;,
      3;55,53,54;,
      3;56,55,54;,
      3;57,55,56;,
      3;58,57,56;,
      3;59,57,58;,
      3;60,59,58;,
      3;61,59,60;,
      3;62,61,60;,
      3;63,61,62;,
      3;64,63,62;,
      3;65,63,64;,
      3;66,65,64;,
      3;67,65,66;,
      3;68,67,66;,
      3;69,67,68;,
      3;70,69,68;,
      3;71,69,70;,
      3;72,71,70;,
      3;73,71,72;,
      3;74,73,72;,
      3;75,73,74;,
      3;76,75,74;,
      3;77,75,76;,
      3;78,77,76;,
      3;79,77,78;,
      3;80,79,78;,
      3;81,79,80;;

      MeshNormals {
       82;
       0.951057;-0.309017;0.000000;,
       0.987689;-0.156432;0.000000;,
       0.987689;-0.156432;0.000000;,
       0.951057;-0.309017;0.000000;,
       0.891007;-0.453990;0.000000;,
       0.891007;-0.453990;0.000000;,
       0.809017;-0.587785;0.000000;,
       0.809017;-0.587785;0.000000;,
       0.707107;-0.707107;0.000000;,
       0.707107;-0.707107;0.000000;,
       0.587785;-0.809017;0.000000;,
       0.587785;-0.809017;0.000000;,
       0.453991;-0.891006;0.000000;,
       0.453991;-0.891006;0.000000;,
       0.309017;-0.951057;0.000000;,
       0.309017;-0.951057;0.000000;,
       0.156435;-0.987688;0.000000;,
       0.156435;-0.987688;0.000000;,
       0.000000;-1.000000;0.000000;,
       0.000000;-1.000000;0.000000;,
       -0.156434;-0.987688;0.000000;,
       -0.156434;-0.987688;0.000000;,
       -0.309016;-0.951057;0.000000;,
       -0.309016;-0.951057;0.000000;,
       -0.453991;-0.891007;0.000000;,
       -0.453991;-0.891007;0.000000;,
       -0.587785;-0.809017;0.000000;,
       -0.587785;-0.809017;0.000000;,
       -0.707107;-0.707107;0.000000;,
       -0.707107;-0.707107;0.000000;,
       -0.809017;-0.587785;0.000000;,
       -0.809017;-0.587785;0.000000;,
       -0.891007;-0.453991;0.000000;,
       -0.891007;-0.453991;0.000000;,
       -0.951056;-0.309017;0.000000;,
       -0.951056;-0.309017;0.000000;,
       -0.987688;-0.156434;0.000000;,
       -0.987688;-0.156434;0.000000;,
       -1.000000;0.000000;0.000000;,
       -1.000000;0.000000;0.000000;,
       -0.987688;0.156434;0.000000;,
       -0.987688;0.156434;0.000000;,
       -0.951057;0.309017;0.000000;,
       -0.951057;0.309017;0.000000;,
       -0.891007;0.453990;0.000000;,
       -0.891007;0.453990;0.000000;,
       -0.809017;0.587785;0.000000;,
       -0.809017;0.587785;0.000000;,
       -0.707107;0.707107;0.000000;,
       -0.707107;0.707107;0.000000;,
       -0.587785;0.809017;0.000000;,
       -0.587785;0.809017;0.000000;,
       -0.453991;0.891006;0.000000;,
       -0.453991;0.891006;0.000000;,
       -0.309017;0.951057;0.000000;,
       -0.309017;0.951057;0.000000;,
       -0.156434;0.987688;0.000000;,
       -0.156434;0.987688;0.000000;,
       0.000000;1.000000;0.000000;,
       0.000000;1.000000;0.000000;,
       0.156434;0.987688;0.000000;,
       0.156434;0.987688;0.000000;,
       0.309017;0.951057;0.000000;,
       0.309017;0.951057;0.000000;,
       0.453991;0.891007;0.000000;,
       0.453991;0.891007;0.000000;,
       0.587786;0.809017;0.000000;,
       0.587786;0.809017;0.000000;,
       0.707107;0.707107;0.000000;,
       0.707107;0.707107;0.000000;,
       0.809017;0.587785;0.000000;,
       0.809017;0.587785;0.000000;,
       0.891007;0.453990;0.000000;,
       0.891007;0.453990;0.000000;,
       0.951057;0.309017;0.000000;,
       0.951057;0.309017;0.000000;,
       0.987688;0.156434;0.000000;,
       0.987688;0.156434;0.000000;,
       1.000000;0.000002;0.000000;,
       1.000000;0.000002;0.000000;,
       0.987689;-0.156432;0.000000;,
       0.987689;-0.156432;0.000000;;
       80;
       3;0,1,2;,
       3;3,1,0;,
       3;4,3,0;,
       3;5,3,4;,
       3;6,5,4;,
       3;7,5,6;,
       3;8,7,6;,
       3;9,7,8;,
       3;10,9,8;,
       3;11,9,10;,
       3;12,11,10;,
       3;13,11,12;,
       3;14,13,12;,
       3;15,13,14;,
       3;16,15,14;,
       3;17,15,16;,
       3;18,17,16;,
       3;19,17,18;,
       3;20,19,18;,
       3;21,19,20;,
       3;22,21,20;,
       3;23,21,22;,
       3;24,23,22;,
       3;25,23,24;,
       3;26,25,24;,
       3;27,25,26;,
       3;28,27,26;,
       3;29,27,28;,
       3;30,29,28;,
       3;31,29,30;,
       3;32,31,30;,
       3;33,31,32;,
       3;34,33,32;,
       3;35,33,34;,
       3;36,35,34;,
       3;37,35,36;,
       3;38,37,36;,
       3;39,37,38;,
       3;40,39,38;,
       3;41,39,40;,
       3;42,41,40;,
       3;43,41,42;,
       3;44,43,42;,
       3;45,43,44;,
       3;46,45,44;,
       3;47,45,46;,
       3;48,47,46;,
       3;49,47,48;,
       3;50,49,48;,
       3;51,49,50;,
       3;52,51,50;,
       3;53,51,52;,
       3;54,53,52;,
       3;55,53,54;,
       3;56,55,54;,
       3;57,55,56;,
       3;58,57,56;,
       3;59,57,58;,
       3;60,59,58;,
       3;61,59,60;,
       3;62,61,60;,
       3;63,61,62;,
       3;64,63,62;,
       3;65,63,64;,
       3;66,65,64;,
       3;67,65,66;,
       3;68,67,66;,
       3;69,67,68;,
       3;70,69,68;,
       3;71,69,70;,
       3;72,71,70;,
       3;73,71,72;,
       3;74,73,72;,
       3;75,73,74;,
       3;76,75,74;,
       3;77,75,76;,
       3;78,77,76;,
       3;79,77,78;,
       3;80,79,78;,
       3;81,79,80;;
      }

      MeshMaterialList {
       1;
       80;
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
       0,
       0,
       0,
       0,
       0;
       { S01_T_Inside_01 }
      }

      MeshTextureCoords c1 {
       82;
       -1.370194;0.029439;,
       -1.468624;0.236001;,
       -1.468624;0.029439;,
       -1.370194;0.236001;,
       -1.271763;0.029439;,
       -1.271763;0.236001;,
       -1.173332;0.029439;,
       -1.173332;0.236001;,
       -1.074901;0.029439;,
       -1.074901;0.236001;,
       -0.976469;0.029439;,
       -0.976469;0.236001;,
       -0.878039;0.029439;,
       -0.878039;0.236001;,
       -0.779608;0.029439;,
       -0.779608;0.236001;,
       -0.681177;0.029439;,
       -0.681177;0.236001;,
       -0.582745;0.029439;,
       -0.582745;0.236001;,
       -0.484315;0.029439;,
       -0.484315;0.236001;,
       -0.385883;0.029439;,
       -0.385883;0.236001;,
       -0.287453;0.029439;,
       -0.287453;0.236001;,
       -0.189021;0.029439;,
       -0.189021;0.236001;,
       -0.090590;0.029439;,
       -0.090590;0.236001;,
       0.007840;0.029439;,
       0.007840;0.236001;,
       0.106272;0.029439;,
       0.106272;0.236001;,
       0.204703;0.029439;,
       0.204703;0.236001;,
       0.303134;0.029439;,
       0.303134;0.236001;,
       0.401564;0.029439;,
       0.401564;0.236001;,
       0.499995;0.029439;,
       0.499995;0.236001;,
       0.598427;0.029439;,
       0.598427;0.236001;,
       0.696859;0.029439;,
       0.696859;0.236001;,
       0.795290;0.029439;,
       0.795290;0.236001;,
       0.893722;0.029439;,
       0.893722;0.236001;,
       0.992153;0.029439;,
       0.992153;0.236001;,
       1.090584;0.029439;,
       1.090584;0.236001;,
       1.189016;0.029439;,
       1.189016;0.236001;,
       1.287447;0.029439;,
       1.287447;0.236001;,
       1.385879;0.029439;,
       1.385879;0.236001;,
       1.484310;0.029439;,
       1.484310;0.236001;,
       1.582742;0.029439;,
       1.582742;0.236001;,
       1.681173;0.029439;,
       1.681173;0.236001;,
       1.779604;0.029439;,
       1.779604;0.236001;,
       1.878036;0.029439;,
       1.878036;0.236001;,
       1.976467;0.029439;,
       1.976467;0.236001;,
       2.074899;0.029439;,
       2.074899;0.236001;,
       2.173330;0.029439;,
       2.173330;0.236001;,
       2.271762;0.029439;,
       2.271762;0.236001;,
       2.370193;0.029439;,
       2.370193;0.236001;,
       2.468625;0.029439;,
       2.468625;0.236001;;
      }
     }
    }
   }
  }
 }
}