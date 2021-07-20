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

  Frame PerpStage_S01_Inside3 {
   

   FrameTransformMatrix {
    1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,98.548006,-7.616522,-15.636387,1.000000;;
   }

   Frame S01_Inside3_Motion {
    

    FrameTransformMatrix {
     1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,-98.548006,7.616526,15.636381,1.000000;;
    }

    Frame S01_Inside3_Motion01 {
     

     FrameTransformMatrix {
      1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,98.570022,-7.729015,16.823261,1.000000;;
     }

     Mesh S01_Inside3_Motion01 {
      82;
      13.314865;-0.000002;-0.341577;,
      13.230170;-2.095455;0.342389;,
      13.230170;-2.095455;-0.341889;,
      13.314865;-0.000002;0.342372;,
      12.663191;-4.114522;-0.341577;,
      12.663191;-4.114522;0.342372;,
      11.935107;-6.081242;0.342389;,
      11.935107;-6.081242;-0.341889;,
      10.771950;-7.826283;-0.341577;,
      10.771950;-7.826283;0.342372;,
      9.471755;-9.471757;0.342389;,
      9.471755;-9.471757;-0.341889;,
      7.826286;-10.771955;-0.341577;,
      7.826286;-10.771955;0.342372;,
      6.081243;-11.935108;0.342389;,
      6.081243;-11.935108;-0.341889;,
      4.114520;-12.663191;-0.341577;,
      4.114520;-12.663191;0.342372;,
      2.095453;-13.230170;0.342389;,
      2.095453;-13.230170;-0.341889;,
      0.000000;-13.314869;-0.341577;,
      0.000000;-13.314869;0.342372;,
      -2.095451;-13.230173;0.342389;,
      -2.095454;-13.230173;-0.341889;,
      -4.114520;-12.663194;-0.341577;,
      -4.114515;-12.663194;0.342372;,
      -6.081240;-11.935109;0.342389;,
      -6.081243;-11.935109;-0.341889;,
      -7.826286;-10.771955;-0.341577;,
      -7.826286;-10.771955;0.342372;,
      -9.471756;-9.471758;0.342389;,
      -9.471759;-9.471757;-0.341889;,
      -10.771957;-7.826286;-0.341577;,
      -10.771950;-7.826286;0.342372;,
      -11.935107;-6.081244;0.342389;,
      -11.935109;-6.081244;-0.341889;,
      -12.663191;-4.114522;-0.341577;,
      -12.663191;-4.114522;0.342372;,
      -13.230170;-2.095455;0.342389;,
      -13.230170;-2.095455;-0.341889;,
      -13.314865;-0.000002;-0.341577;,
      -13.314865;-0.000002;0.342372;,
      -13.230170;2.095451;0.342389;,
      -13.230170;2.095451;-0.341889;,
      -12.663191;4.114518;-0.341577;,
      -12.663191;4.114518;0.342372;,
      -11.935107;6.081240;0.342389;,
      -11.935109;6.081240;-0.341889;,
      -10.771957;7.826282;-0.341577;,
      -10.771950;7.826282;0.342372;,
      -9.471756;9.471755;0.342389;,
      -9.471759;9.471755;-0.341889;,
      -7.826286;10.771953;-0.341577;,
      -7.826286;10.771953;0.342372;,
      -6.081240;11.935108;0.342389;,
      -6.081243;11.935108;-0.341889;,
      -4.114520;12.663191;-0.341577;,
      -4.114515;12.663191;0.342372;,
      -2.095451;13.230170;0.342389;,
      -2.095454;13.230170;-0.341889;,
      0.000000;13.314869;-0.341577;,
      0.000000;13.314869;0.342372;,
      2.095453;13.230170;0.342389;,
      2.095453;13.230173;-0.341889;,
      4.114520;12.663194;-0.341577;,
      4.114520;12.663191;0.342372;,
      6.081246;11.935109;0.342389;,
      6.081243;11.935112;-0.341889;,
      7.826286;10.771955;-0.341577;,
      7.826290;10.771955;0.342372;,
      9.471765;9.471757;0.342389;,
      9.471762;9.471757;-0.341889;,
      10.771963;7.826283;-0.341577;,
      10.771963;7.826283;0.342372;,
      11.935118;6.081241;0.342389;,
      11.935116;6.081241;-0.341889;,
      12.663197;4.114520;-0.341577;,
      12.663203;4.114520;0.342372;,
      13.230175;2.095452;0.342389;,
      13.230173;2.095452;-0.341889;,
      13.314865;-0.000002;-0.341577;,
      13.314865;-0.000002;0.342372;;
      80;
      3;0,1,2;,
      3;3,1,0;,
      3;2,1,4;,
      3;4,1,5;,
      3;5,6,4;,
      3;4,6,7;,
      3;7,6,8;,
      3;8,6,9;,
      3;9,10,8;,
      3;8,10,11;,
      3;11,10,12;,
      3;12,10,13;,
      3;13,14,12;,
      3;12,14,15;,
      3;15,14,16;,
      3;16,14,17;,
      3;17,18,16;,
      3;16,18,19;,
      3;19,18,20;,
      3;20,18,21;,
      3;21,22,20;,
      3;20,22,23;,
      3;23,22,24;,
      3;24,22,25;,
      3;25,26,24;,
      3;24,26,27;,
      3;27,26,28;,
      3;28,26,29;,
      3;29,30,28;,
      3;28,30,31;,
      3;31,30,32;,
      3;32,30,33;,
      3;33,34,32;,
      3;32,34,35;,
      3;35,34,36;,
      3;36,34,37;,
      3;37,38,36;,
      3;36,38,39;,
      3;39,38,40;,
      3;40,38,41;,
      3;41,42,40;,
      3;40,42,43;,
      3;43,42,44;,
      3;44,42,45;,
      3;45,46,44;,
      3;44,46,47;,
      3;47,46,48;,
      3;48,46,49;,
      3;49,50,48;,
      3;48,50,51;,
      3;51,50,52;,
      3;52,50,53;,
      3;53,54,52;,
      3;52,54,55;,
      3;55,54,56;,
      3;56,54,57;,
      3;57,58,56;,
      3;56,58,59;,
      3;59,58,60;,
      3;60,58,61;,
      3;61,62,60;,
      3;60,62,63;,
      3;63,62,64;,
      3;64,62,65;,
      3;65,66,64;,
      3;64,66,67;,
      3;67,66,68;,
      3;68,66,69;,
      3;69,70,68;,
      3;68,70,71;,
      3;71,70,72;,
      3;72,70,73;,
      3;73,74,72;,
      3;72,74,75;,
      3;75,74,76;,
      3;76,74,77;,
      3;77,78,76;,
      3;76,78,79;,
      3;79,78,80;,
      3;80,78,81;;

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

      DeclData {
       2;
       2;0;3;0;,
       1;0;5;0;;
       410;
       1065353216,
       3046939130,
       3046263555,
       3240117265,
       1048608252,
       1065146661,
       3189780555,
       0,
       3239592058,
       1035531936,
       1065146661,
       3189780555,
       0,
       3239592058,
       1048608252,
       1065353216,
       3046940045,
       3046263555,
       3240117265,
       1035531936,
       1064532079,
       3198039937,
       0,
       3239066851,
       1048608252,
       1064532079,
       3198039938,
       0,
       3239066851,
       1035531936,
       1063524604,
       3202904452,
       0,
       3238541644,
       1035531936,
       1063524604,
       3202904451,
       0,
       3238541644,
       1048608252,
       1062149055,
       3205921046,
       0,
       3238016437,
       1048608252,
       1062149054,
       3205921046,
       0,
       3238016437,
       1035531936,
       1060439297,
       3207922917,
       0,
       3236979771,
       1035531936,
       1060439297,
       3207922918,
       0,
       3236979771,
       1048608252,
       1058437399,
       3209632702,
       0,
       3235929356,
       1048608252,
       1058437400,
       3209632701,
       0,
       3235929356,
       1035531936,
       1055420762,
       3211008263,
       0,
       3234878942,
       1035531936,
       1055420762,
       3211008263,
       0,
       3234878942,
       1048608252,
       1050556291,
       3212015727,
       0,
       3233828528,
       1048608252,
       1050556292,
       3212015727,
       0,
       3233828528,
       1035531936,
       1042296964,
       3212630307,
       0,
       3232778114,
       1035531936,
       1042296964,
       3212630307,
       0,
       3232778114,
       1048608252,
       887768069,
       3212836864,
       0,
       3231727700,
       1048608252,
       887769439,
       3212836864,
       0,
       3231727700,
       1035531936,
       3189780549,
       3212630309,
       896025178,
       3230677286,
       1035531936,
       3189780591,
       3212630308,
       896025252,
       3230677286,
       1048608252,
       3198039952,
       3212015725,
       904772069,
       3229626872,
       1048608252,
       3198039940,
       3212015727,
       904772060,
       3229626872,
       1035531936,
       3202904417,
       3211008261,
       904865920,
       3227538834,
       1035531936,
       3202904433,
       3211008257,
       904865914,
       3227538834,
       1048608252,
       3205921041,
       3209632706,
       899260186,
       3225438004,
       1048608252,
       3205921041,
       3209632706,
       899260186,
       3225438003,
       1035531936,
       3207922930,
       3207922933,
       908673502,
       3223337176,
       1035531936,
       3207922938,
       3207922924,
       908673549,
       3223337176,
       1048608252,
       3209632705,
       3205921042,
       915557130,
       3221236348,
       1048608252,
       3209632702,
       3205921047,
       915557128,
       3221236348,
       1035531936,
       3211008256,
       3202904439,
       912048895,
       3217045568,
       1035531936,
       3211008258,
       3202904430,
       912048885,
       3217045568,
       1048608252,
       3212015729,
       3198039927,
       898779907,
       3212843912,
       1048608252,
       3212015729,
       3198039929,
       898779909,
       3212843912,
       1035531936,
       3212630309,
       3189780551,
       0,
       3204447035,
       1035531936,
       3212630309,
       3189780551,
       0,
       3204447035,
       1048608252,
       3212836864,
       0,
       0,
       980374656,
       1048608252,
       3212836864,
       0,
       0,
       980374655,
       1035531936,
       3212630309,
       1042296903,
       0,
       1056994633,
       1035531936,
       3212630309,
       1042296902,
       0,
       1056994633,
       1048608252,
       3212015729,
       1050556278,
       898779906,
       1065375582,
       1048608252,
       3212015729,
       1050556277,
       898779906,
       1065375582,
       1035531936,
       3211008257,
       1055420786,
       912048893,
       1069577237,
       1035531936,
       3211008259,
       1055420778,
       912048883,
       1069577237,
       1048608252,
       3209632707,
       1058437392,
       916755554,
       1073760358,
       1048608252,
       3209632704,
       1058437396,
       916755563,
       1073760358,
       1035531936,
       3207922935,
       1060439279,
       912048877,
       1075861187,
       1035531936,
       3207922942,
       1060439273,
       912048915,
       1075861187,
       1048608252,
       3205921044,
       1062149056,
       898779905,
       1077962016,
       1048608252,
       3205921046,
       1062149055,
       898779906,
       1077962016,
       1035531936,
       3202904408,
       1063524615,
       903660278,
       1080062844,
       1035531936,
       3202904426,
       1063524611,
       903660254,
       1080062844,
       1048608252,
       3198039949,
       1064532078,
       906269695,
       1082147052,
       1048608252,
       3198039934,
       1064532080,
       906269684,
       1082147052,
       1035531936,
       3189780601,
       1065146659,
       897230829,
       1083197467,
       1035531936,
       3189780639,
       1065146658,
       897230906,
       1083197467,
       1048608252,
       3022858021,
       1065353216,
       897251629,
       1084247882,
       1048608252,
       3023049769,
       1065353216,
       897251631,
       1084247882,
       1035531936,
       1042296936,
       1065146660,
       910873202,
       1085298296,
       1035531936,
       1042296931,
       1065146660,
       910873198,
       1085298296,
       1048608252,
       1050556275,
       1064532082,
       914064156,
       1086348709,
       1048608252,
       1050556279,
       1064532081,
       914064154,
       1086348709,
       1035531936,
       1055420780,
       1063524610,
       895290265,
       1087399124,
       1035531936,
       1055420756,
       1063524616,
       895290578,
       1087399124,
       1048608252,
       1058437391,
       1062149060,
       3057049001,
       1088449538,
       1048608252,
       1058437393,
       1062149058,
       3057049040,
       1088449538,
       1035531936,
       1060439278,
       1060439288,
       3058326872,
       1089499952,
       1035531936,
       1060439274,
       1060439293,
       3058326882,
       1089499952,
       1048608252,
       1062149053,
       1058437400,
       3046263553,
       1090534703,
       1048608252,
       1062149053,
       1058437400,
       3046263554,
       1090534703,
       1035531936,
       1063524611,
       1055420778,
       3057121241,
       1091059911,
       1035531936,
       1063524609,
       1055420783,
       3057121215,
       1091059911,
       1048608252,
       1064532085,
       1050556253,
       3067834499,
       1091585119,
       1048608252,
       1064532086,
       1050556248,
       3067834506,
       1091585119,
       1035531936,
       1065146667,
       1042296755,
       3064304186,
       1092110325,
       1035531936,
       1065146667,
       1042296760,
       3064304190,
       1092110325,
       1048608252,
       1065353216,
       3046939130,
       3046263555,
       1092635531,
       1048608252,
       1065353216,
       3046940045,
       3046263555,
       1092635531,
       1035531936;
      }
     }
    }
   }
  }
 }
}