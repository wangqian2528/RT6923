//
////舒展按摩（宽幅度按摩）中等力度
//const WALK_KNEAD_KNOCK_MOTOR_STRUCT_AUTO AutoFunction3[] = 
//{	
//  //揉捶同步到肩部（低速）
//  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PressNeck,0,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_2,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},	
//  {BACK_SUB_MODE_PRESS,WALK_SHOULDER_WAIST_1_10,0,KNEAD_STOP,0,KNOCK_STOP,0,0,SPEED_1,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_5,0},
//  {BACK_SUB_MODE_KNOCK,WALK_LOCATE_PARK,20,KNEAD_RUN_STOP_AT_MIN,0,KNOCK_RUN_WIDTH,0,0,SPEED_4,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
//  {BACK_SUB_MODE_KNOCK,WALK_LOCATE_PARK,20,KNEAD_RUN_STOP_AT_MED,0,KNOCK_RUN_WIDTH,0,0,SPEED_4,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
//  {BACK_SUB_MODE_KNOCK,WALK_LOCATE_PARK,20,KNEAD_RUN_STOP_AT_MIN,0,KNOCK_RUN_WIDTH,0,0,SPEED_4,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
//  {BACK_SUB_MODE_KNOCK,WALK_LOCATE_PARK,20,KNEAD_RUN_STOP_AT_MED,0,KNOCK_RUN_WIDTH,0,0,SPEED_4,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
//  {BACK_SUB_MODE_KNOCK,WALK_LOCATE_PARK,20,KNEAD_RUN_STOP_AT_MIN,0,KNOCK_RUN_WIDTH,0,0,SPEED_4,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
//  
//  //指压到顶//10
//  {BACK_SUB_MODE_PRESS,WALK_LOCATE_TOP,0,KNEAD_STOP_AT_MIN,0,KNOCK_STOP,0,0,SPEED_1,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
//  //{BACK_SUB_MODE_SOFT_KNOCK,WALK_LOCATE_PARK,50,KNEAD_STOP,0,KNOCK_RUN_STOP,1,4,SPEED_3,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
// {BACK_SUB_MODE_PRESS,WALK_LOCATE_NeckMed,0,KNEAD_STOP_AT_MIN,0,KNOCK_STOP,0,0,SPEED_1,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
// 
//  
//  //颈部组合
//  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_NeckMed,0,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_2,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
//  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,40,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
//  //搓背  
//  {BACK_SUB_MODE_RUBBING,WALK_LOCATE_ABSULATE,0,KNEAD_RUN_RUBBING,0,KNOCK_STOP,0,0,SPEED_6,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_7,0},
//  {BACK_SUB_MODE_RUBBING,WALK_LOCATE_PressNeck,0,KNEAD_RUN_RUBBING,0,KNOCK_STOP,0,0,SPEED_6,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_7,0},
//
//  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_ABSULATE,0,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_6,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
//  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,80,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_4,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
//  //腰部定点捶打//54
//  {BACK_SUB_MODE_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP_AT_MIN,0,KNOCK_RUN_WIDTH,20,0,SPEED_3,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
//  {BACK_SUB_MODE_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,30,0,SPEED_4,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
//  {BACK_SUB_MODE_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,40,0,SPEED_4,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
//  //等待
//  {BACK_SUB_MODE_PRESS,WALK_LOCATE_PARK,2,KNEAD_STOP,0,KNOCK_STOP,0,0,SPEED_1,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
//  {BACK_SUB_MODE_KNOCK,WALK_LOCATE_PARK,0,KNEAD_RUN_STOP_AT_MED,1,KNOCK_RUN_WIDTH,20,0,SPEED_3,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
//  {BACK_SUB_MODE_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,30,0,SPEED_4,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
//  {BACK_SUB_MODE_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,40,0,SPEED_4,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
//  //等待
//  {BACK_SUB_MODE_PRESS,WALK_LOCATE_PARK,2,KNEAD_STOP,0,KNOCK_STOP,0,0,SPEED_1,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
//  //揉捏定点
//  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,50,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_5,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
//  //局部揉捶同步//63
//  {BACK_SUB_MODE_WAVELET,WALK_LOCATE_ABSULATE,40,KNEAD_RUN,0,KNOCK_RUN,0,0,SPEED_4,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
//  {BACK_SUB_MODE_WAVELET,WALK_LOCATE_PARK,30,KNEAD_RUN,0,KNOCK_RUN,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_7,0},
//  {BACK_SUB_MODE_WAVELET,WALK_LOCATE_ABSULATE,80,KNEAD_RUN,0,KNOCK_RUN,0,0,SPEED_3,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
//  {BACK_SUB_MODE_WAVELET,WALK_LOCATE_PARK,30,KNEAD_RUN,0,KNOCK_RUN,0,0,SPEED_3,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_7,0},
//  {BACK_SUB_MODE_WAVELET,WALK_LOCATE_ABSULATE,40,KNEAD_RUN,0,KNOCK_RUN,0,0,SPEED_3,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
//  {BACK_SUB_MODE_WAVELET,WALK_LOCATE_PARK,30,KNEAD_RUN,0,KNOCK_RUN,0,0,SPEED_3,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_7,0},
//  {BACK_SUB_MODE_WAVELET,WALK_LOCATE_ABSULATE,0,KNEAD_RUN,0,KNOCK_RUN,0,0,SPEED_4,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
//  {BACK_SUB_MODE_WAVELET,WALK_LOCATE_PARK,30,KNEAD_RUN,0,KNOCK_RUN,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_7,0},
//  
//} ;
//
//
//
//
//
/////*
////工作减压 为职场人士匠心打造独特按摩程序，根据职场阶层人士长期伏案工作出差等特点、舒缓筋骨、恢复体力。
////*/
////const WALK_KNEAD_KNOCK_MOTOR_STRUCT_AUTO AutoFunction3[] = 
////{
////  /*
////  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_SHOULDER,0,KNEAD_STOP_AT_MED,0,KNOCK_STOP,0,0,SPEED_2,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,5},
////  {BACK_SUB_MODE_KNEAD,WALK_SHOULDER_WAIST_1_10,0,KNEAD_STOP_AT_MED,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_7,5},
////  {BACK_SUB_MODE_KNEAD,WALK_SHOULDER_WAIST_2_10,0,KNEAD_STOP_AT_MED,0,KNOCK_STOP,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_7,5},
////  {BACK_SUB_MODE_KNEAD,WALK_SHOULDER_WAIST_3_10,0,KNEAD_STOP_AT_MED,0,KNOCK_STOP,0,0,SPEED_5,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_7,5},
////  {BACK_SUB_MODE_KNEAD,WALK_SHOULDER_WAIST_4_10,0,KNEAD_STOP_AT_MED,0,KNOCK_STOP,0,0,SPEED_6,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_7,5},
////  {BACK_SUB_MODE_KNEAD,WALK_SHOULDER_WAIST_5_10,0,KNEAD_STOP_AT_MED,0,KNOCK_STOP,0,0,SPEED_5,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_7,5},
////  {BACK_SUB_MODE_KNEAD,WALK_SHOULDER_WAIST_6_10,0,KNEAD_STOP_AT_MED,0,KNOCK_STOP,0,0,SPEED_4,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,5},
////  {BACK_SUB_MODE_KNEAD,WALK_SHOULDER_WAIST_7_10,0,KNEAD_STOP_AT_MED,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_WEAKER,_3D_SPEED_7,5},
////  {BACK_SUB_MODE_KNEAD,WALK_SHOULDER_WAIST_8_10,0,KNEAD_STOP_AT_MED,0,KNOCK_STOP,0,0,SPEED_2,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,5},
////  {BACK_SUB_MODE_KNEAD,WALK_SHOULDER_WAIST_9_10,0,KNEAD_STOP_AT_MED,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_7,5},
////  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_WAIST,0,KNEAD_STOP_AT_MED,0,KNOCK_STOP,0,0,SPEED_5,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_7,5},
//// */
////
////  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_SHOULDER,0,KNEAD_STOP_AT_MED,0,KNOCK_STOP,0,0,SPEED_2,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,5},
////  {BACK_SUB_MODE_KNEAD,WALK_SHOULDER_WAIST_1_10,0,KNEAD_RUN_STOP_AT_MED,1,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_7,5},
////  {BACK_SUB_MODE_KNEAD,WALK_SHOULDER_WAIST_2_10,0,KNEAD_RUN_STOP_AT_MAX,1,KNOCK_STOP,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_7,5},
////  {BACK_SUB_MODE_KNEAD,WALK_SHOULDER_WAIST_3_10,0,KNEAD_RUN_STOP_AT_MED,1,KNOCK_STOP,0,0,SPEED_5,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_7,5},
////  {BACK_SUB_MODE_KNEAD,WALK_SHOULDER_WAIST_4_10,0,KNEAD_RUN_STOP_AT_MAX,1,KNOCK_STOP,0,0,SPEED_6,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_7,5},
////  {BACK_SUB_MODE_KNEAD,WALK_SHOULDER_WAIST_5_10,0,KNEAD_RUN_STOP_AT_MED,1,KNOCK_STOP,0,0,SPEED_5,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_7,5},
////  {BACK_SUB_MODE_KNEAD,WALK_SHOULDER_WAIST_6_10,0,KNEAD_RUN_STOP_AT_MAX,1,KNOCK_STOP,0,0,SPEED_4,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,5},
////  {BACK_SUB_MODE_KNEAD,WALK_SHOULDER_WAIST_7_10,0,KNEAD_RUN_STOP_AT_MED,1,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_WEAKER,_3D_SPEED_7,5},
////  {BACK_SUB_MODE_KNEAD,WALK_SHOULDER_WAIST_8_10,0,KNEAD_RUN_STOP_AT_MAX,1,KNOCK_STOP,0,0,SPEED_2,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,5},
////  {BACK_SUB_MODE_KNEAD,WALK_SHOULDER_WAIST_9_10,0,KNEAD_RUN_STOP_AT_MED,1,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_7,5},
////  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_WAIST,0,KNEAD_RUN_STOP_AT_MAX,1,KNOCK_STOP,0,0,SPEED_5,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_7,5},
////
////  {BACK_SUB_MODE_WAVELET,WALK_LOCATE_ABSULATE,0,KNEAD_RUN,0,KNOCK_RUN,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_WAVELET,WALK_LOCATE_PARK,0,KNEAD_RUN,0,KNOCK_RUN,0,0,SPEED_4,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,30},
////  {BACK_SUB_MODE_WAVELET,WALK_LOCATE_PARK,0,KNEAD_RUN,0,KNOCK_RUN,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_7,30},
////  {BACK_SUB_MODE_WAVELET,WALK_LOCATE_PARK,0,KNEAD_RUN,0,KNOCK_RUN,0,0,SPEED_4,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,30},
////  {BACK_SUB_MODE_WAVELET,WALK_LOCATE_PARK,0,KNEAD_RUN,0,KNOCK_RUN,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_7,30},
////  {BACK_SUB_MODE_WAVELET,WALK_LOCATE_PARK,0,KNEAD_RUN,0,KNOCK_RUN,0,0,SPEED_4,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,30},
////  {BACK_SUB_MODE_WAVELET,WALK_LOCATE_PARK,0,KNEAD_RUN,0,KNOCK_RUN,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_7,30},
////  {BACK_SUB_MODE_WAVELET,WALK_LOCATE_PARK,0,KNEAD_RUN,0,KNOCK_RUN,0,0,SPEED_4,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,30},
////  {BACK_SUB_MODE_WAVELET,WALK_LOCATE_PARK,0,KNEAD_RUN,0,KNOCK_RUN,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_7,30},
////  {BACK_SUB_MODE_WAVELET,WALK_LOCATE_PARK,0,KNEAD_RUN,0,KNOCK_RUN,0,0,SPEED_4,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,30},
////  {BACK_SUB_MODE_WAVELET,WALK_LOCATE_PARK,0,KNEAD_RUN,0,KNOCK_RUN,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_7,30},
////   //揉捶同步到肩部
////  {BACK_SUB_MODE_WAVELET,WALK_SHOULDER_WAIST_1_10,0,KNEAD_RUN,0,KNOCK_RUN,0,0,SPEED_2,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
//// //201507
////  //上提   揉捏宽度：窄
////  {BACK_SUB_MODE_PRESS,WALK_LOCATE_SHOULDER,0,KNEAD_STOP         ,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_WEAKER,_3D_SPEED_5,0},
////  {BACK_SUB_MODE_PRESS,WALK_LOCATE_SHOULDER,0 ,KNEAD_STOP_AT_MIN,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_5,0},
////  {BACK_SUB_MODE_PRESS,WALK_LOCATE_Ear,0,KNEAD_STOP         ,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_5,0},
////  {BACK_SUB_MODE_PRESS,WALK_LOCATE_PARK,20,KNEAD_STOP                ,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_5,20},
////  
////  {BACK_SUB_MODE_PRESS,WALK_LOCATE_SHOULDER,0,KNEAD_STOP         ,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_WEAKER,_3D_SPEED_5,0}, 
////  {BACK_SUB_MODE_PRESS,WALK_LOCATE_Ear,0,KNEAD_STOP         ,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_5,0},
////  {BACK_SUB_MODE_PRESS,WALK_LOCATE_PARK,20,KNEAD_STOP                ,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_5,20},
//// //add 
////  //{BACK_SUB_MODE_PRESS,WALK_LOCATE_SHOULDER,0,KNEAD_STOP         ,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_5,0},
////  //{BACK_SUB_MODE_PRESS,WALK_LOCATE_NeckMed,0,KNEAD_STOP         ,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_5,0}, 
////  {BACK_SUB_MODE_PRESS,WALK_LOCATE_SHOULDER,0,KNEAD_STOP         ,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_5,0},
////  {BACK_SUB_MODE_PRESS,WALK_LOCATE_PARK,20,KNEAD_STOP                ,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_5,20},
////  {BACK_SUB_MODE_PRESS,WALK_SHOULDER_WAIST_1_10,0,KNEAD_STOP     ,0,KNOCK_STOP,0,0,SPEED_1,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_5,0},
////  {BACK_SUB_MODE_PRESS,WALK_LOCATE_PARK,20,KNEAD_STOP                ,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_5,20},
////  {BACK_SUB_MODE_PRESS,WALK_SHOULDER_WAIST_1_9,0,KNEAD_STOP     ,0,KNOCK_STOP,0,0,SPEED_1,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_5,0},
////  {BACK_SUB_MODE_PRESS,WALK_LOCATE_PARK,20,KNEAD_STOP                ,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_5,20},
////
//// {BACK_SUB_MODE_PRESS,WALK_LOCATE_SHOULDER,0,KNEAD_STOP         ,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_5,0}, 
//// {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,0,KNEAD_RUN_STOP_AT_MIN,2,KNOCK_STOP,0,0,SPEED_1,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_5,0},
////  //指压到顶
////  //{BACK_SUB_MODE_PRESS,WALK_LOCATE_PressNeck,0,KNEAD_STOP           ,0,KNOCK_STOP,0,0,SPEED_1,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK     ,0,KNEAD_RUN_STOP_AT_MIN,1,KNOCK_STOP,0,0,SPEED_1,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_PRESS,WALK_LOCATE_SHOULDER ,0,KNEAD_STOP           ,0,KNOCK_STOP,0,0,SPEED_2,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNOCK,WALK_LOCATE_PARK     ,0,KNEAD_STOP           ,0,KNOCK_RUN,40,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK     ,0,KNEAD_RUN_STOP_AT_MIN,3,KNOCK_STOP,0,0,SPEED_1,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_7,0},
////  
////
////
//////指压到顶
////  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,20,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_PRESS,WALK_LOCATE_SHOULDER,0,KNEAD_STOP,0,KNOCK_STOP,0,0,SPEED_1,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_7,10},
////  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,0,KNEAD_RUN_STOP_AT_MIN,1,KNOCK_STOP,0,0,SPEED_1,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
////  
////  //轻敲到肩部
////  {BACK_SUB_MODE_PRESS,WALK_LOCATE_PressNeck,0,KNEAD_STOP,0,KNOCK_STOP,0,0,SPEED_2,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
////  
////  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,60,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_2,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_NeckMed,0,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,60,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_2,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
////  //揉捏
////  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,0,KNEAD_RUN_STOP_AT_MIN,1,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
////  
////  //指压到顶
////  {BACK_SUB_MODE_PRESS,WALK_LOCATE_SHOULDER,0,KNEAD_STOP,0,KNOCK_STOP,0,0,SPEED_1,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,0,KNEAD_RUN_STOP_AT_MIN,1,KNOCK_STOP,0,0,SPEED_1,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_PRESS,WALK_LOCATE_PressNeck,0,KNEAD_STOP,0,KNOCK_STOP,0,0,SPEED_2,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,40,0,SPEED_3,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,0,KNEAD_RUN_STOP_AT_MIN,5,KNOCK_STOP,0,0,SPEED_1,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_7,0},
////  
////  {BACK_SUB_MODE_PRESS,WALK_LOCATE_SHOULDER,0,KNEAD_STOP,0,KNOCK_STOP,0,0,SPEED_1,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,0,KNEAD_RUN_STOP_AT_MIN,1,KNOCK_STOP,0,0,SPEED_1,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_PRESS,WALK_LOCATE_PressNeck,0,KNEAD_STOP,0,KNOCK_STOP,0,0,SPEED_2,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,40,0,SPEED_3,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,0,KNEAD_RUN_STOP_AT_MIN,5,KNOCK_STOP,0,0,SPEED_1,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_7,0},
////  
////  {BACK_SUB_MODE_PRESS,WALK_LOCATE_SHOULDER,0,KNEAD_STOP,0,KNOCK_STOP,0,0,SPEED_1,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,0,KNEAD_RUN_STOP_AT_MIN,1,KNOCK_STOP,0,0,SPEED_1,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_PRESS,WALK_LOCATE_PressNeck,0,KNEAD_STOP,0,KNOCK_STOP,0,0,SPEED_2,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,40,0,SPEED_3,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,0,KNEAD_RUN_STOP_AT_MIN,5,KNOCK_STOP,0,0,SPEED_1,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_7,0},
////  
////  //搓背  
////  {BACK_SUB_MODE_RUBBING,WALK_LOCATE_ABSULATE,0,KNEAD_RUN_RUBBING,0,KNOCK_STOP,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_RUBBING,WALK_LOCATE_PressNeck,0,KNEAD_RUN_RUBBING,0,KNOCK_STOP,0,0,SPEED_5,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_RUBBING,WALK_LOCATE_ABSULATE,WAIST_POSITION,KNEAD_RUN_RUBBING,0,KNOCK_STOP,0,0,SPEED_6,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_RUBBING,WALK_LOCATE_PressNeck,0,KNEAD_RUN_RUBBING,0,KNOCK_STOP,0,0,SPEED_5,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_RUBBING,WALK_LOCATE_ABSULATE,WAIST_POSITION,KNEAD_RUN_RUBBING,0,KNOCK_STOP,0,0,SPEED_4,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
////  
////  
////  //行进式揉捏到底
////  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_NeckMed,0,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,20,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_7,0},
////  
////  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_SHOULDER,0,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,20,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_7,0},
////  
////  {BACK_SUB_MODE_KNEAD,WALK_SHOULDER_WAIST_1_10,0,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,20,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_7,0},
////  
////  {BACK_SUB_MODE_KNEAD,WALK_SHOULDER_WAIST_3_10,0,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,20,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_7,0},
////  
////  {BACK_SUB_MODE_KNEAD,WALK_SHOULDER_WAIST_5_10,0,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,20,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_7,0},
////  
////  {BACK_SUB_MODE_KNEAD,WALK_SHOULDER_WAIST_7_10,0,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,20,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_7,0},
////  
////  {BACK_SUB_MODE_KNEAD,WALK_SHOULDER_WAIST_9_10,0,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,20,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_7,0},
////  
////  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_WAIST,0,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,20,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_7,0},
////  
////  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_ABSULATE,0,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,20,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_7,0},
////  //腰部定点敲打
////  {BACK_SUB_MODE_PRESS,WALK_LOCATE_WAIST,0,KNEAD_STOP,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,30,0,SPEED_3,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,35,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,40,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,40,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,40,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,35,0,SPEED_4,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,30,0,SPEED_3,_3D_PROGRAM,AXIS_WEAKER,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,0,KNEAD_RUN_STOP_AT_MAX,5,KNOCK_STOP,0,0,SPEED_4,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,30,0,SPEED_3,_3D_PROGRAM,AXIS_WEAKER,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,35,0,SPEED_4,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,40,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,40,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,40,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,35,0,SPEED_4,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,30,0,SPEED_3,_3D_PROGRAM,AXIS_WEAKER,_3D_SPEED_7,0},
////  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,0,KNEAD_RUN_STOP_AT_MIN,5,KNOCK_STOP,0,0,SPEED_4,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
////  
//// 
////} ;
////


/*
工作减压 为职场人士匠心打造独特按摩程序，根据职场阶层人士长期伏案工作出差等特点、舒缓筋骨、恢复体力。
*/
const WALK_KNEAD_KNOCK_MOTOR_STRUCT_AUTO AutoFunction3[] = 
{
  
  
  {BACK_SUB_MODE_PRESS,WALK_LOCATE_SHOULDER,0,KNEAD_STOP_AT_MED,0,KNOCK_STOP,0,0,SPEED_2,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_5,5},
  {BACK_SUB_MODE_PRESS,WALK_SHOULDER_WAIST_1_10,0,KNEAD_STOP_AT_MED,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_5,5},
  {BACK_SUB_MODE_PRESS,WALK_SHOULDER_WAIST_2_10,0,KNEAD_STOP_AT_MED,0,KNOCK_STOP,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_5,5},
  {BACK_SUB_MODE_PRESS,WALK_SHOULDER_WAIST_3_10,0,KNEAD_STOP_AT_MED,0,KNOCK_STOP,0,0,SPEED_5,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_5,5},
  {BACK_SUB_MODE_PRESS,WALK_SHOULDER_WAIST_4_10,0,KNEAD_STOP_AT_MED,0,KNOCK_STOP,0,0,SPEED_6,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_5,5},
  {BACK_SUB_MODE_PRESS,WALK_SHOULDER_WAIST_5_10,0,KNEAD_STOP_AT_MED,0,KNOCK_STOP,0,0,SPEED_5,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_5,5},
  {BACK_SUB_MODE_PRESS,WALK_SHOULDER_WAIST_6_10,0,KNEAD_STOP_AT_MED,0,KNOCK_STOP,0,0,SPEED_4,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_5,5},
  {BACK_SUB_MODE_PRESS,WALK_SHOULDER_WAIST_7_10,0,KNEAD_STOP_AT_MED,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_WEAKER,_3D_SPEED_5,5},
  {BACK_SUB_MODE_PRESS,WALK_SHOULDER_WAIST_8_10,0,KNEAD_STOP_AT_MED,0,KNOCK_STOP,0,0,SPEED_2,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_5,5},
  {BACK_SUB_MODE_PRESS,WALK_SHOULDER_WAIST_9_10,0,KNEAD_STOP_AT_MED,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_5,5},
  {BACK_SUB_MODE_PRESS,WALK_LOCATE_WAIST,0,KNEAD_STOP_AT_MED,0,KNOCK_STOP,0,0,SPEED_5,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_5,5},
  
  {BACK_SUB_MODE_WAVELET,WALK_LOCATE_ABSULATE,0,KNEAD_RUN,0,KNOCK_RUN,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_5,0},
  {BACK_SUB_MODE_WAVELET,WALK_LOCATE_PARK,0,KNEAD_RUN,0,KNOCK_RUN,0,0,SPEED_4,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_5,30},
  {BACK_SUB_MODE_WAVELET,WALK_LOCATE_PARK,0,KNEAD_RUN,0,KNOCK_RUN,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_5,30},
  {BACK_SUB_MODE_WAVELET,WALK_LOCATE_PARK,0,KNEAD_RUN,0,KNOCK_RUN,0,0,SPEED_4,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_5,30},
  {BACK_SUB_MODE_WAVELET,WALK_LOCATE_PARK,0,KNEAD_RUN,0,KNOCK_RUN,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_5,30},
  {BACK_SUB_MODE_WAVELET,WALK_LOCATE_PARK,0,KNEAD_RUN,0,KNOCK_RUN,0,0,SPEED_4,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_5,30},
  {BACK_SUB_MODE_WAVELET,WALK_LOCATE_PARK,0,KNEAD_RUN,0,KNOCK_RUN,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_5,30},
  {BACK_SUB_MODE_WAVELET,WALK_LOCATE_PARK,0,KNEAD_RUN,0,KNOCK_RUN,0,0,SPEED_4,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_5,30},
  {BACK_SUB_MODE_WAVELET,WALK_LOCATE_PARK,0,KNEAD_RUN,0,KNOCK_RUN,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_5,30},
  {BACK_SUB_MODE_WAVELET,WALK_LOCATE_PARK,0,KNEAD_RUN,0,KNOCK_RUN,0,0,SPEED_4,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_5,30},
  {BACK_SUB_MODE_WAVELET,WALK_LOCATE_PARK,0,KNEAD_RUN,0,KNOCK_RUN,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_5,30},
   //揉捶同步到肩部
  {BACK_SUB_MODE_WAVELET,WALK_LOCATE_SHOULDER,0,KNEAD_RUN,0,KNOCK_RUN,0,0,SPEED_2,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_5,0},
  //指压到顶
  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,20,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_5,0},
  {BACK_SUB_MODE_PRESS,WALK_LOCATE_SHOULDER,0,KNEAD_STOP,0,KNOCK_STOP,0,0,SPEED_1,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_5,10},
  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,0,KNEAD_RUN_STOP_AT_MIN,1,KNOCK_STOP,0,0,SPEED_1,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_5,0},
  
  //轻敲到肩部
  {BACK_SUB_MODE_PRESS,WALK_LOCATE_PressNeck,0,KNEAD_STOP,0,KNOCK_STOP,0,0,SPEED_2,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_5,0},
  
  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,60,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_2,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_5,0},
  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_NeckMed,0,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_5,0},
  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,60,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_2,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_5,0},
  //揉捏
  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,0,KNEAD_RUN_STOP_AT_MIN,1,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_5,0},
  
  //指压到顶
  {BACK_SUB_MODE_PRESS,WALK_LOCATE_SHOULDER,0,KNEAD_STOP,0,KNOCK_STOP,0,0,SPEED_1,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_5,0},
  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,0,KNEAD_RUN_STOP_AT_MIN,1,KNOCK_STOP,0,0,SPEED_1,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_5,0},
  {BACK_SUB_MODE_PRESS,WALK_LOCATE_PressNeck,0,KNEAD_STOP,0,KNOCK_STOP,0,0,SPEED_2,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_5,0},
  {BACK_SUB_MODE_SOFT_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,40,0,SPEED_3,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_5,0},
  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,0,KNEAD_RUN_STOP_AT_MIN,5,KNOCK_STOP,0,0,SPEED_1,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_5,0},
  
  {BACK_SUB_MODE_PRESS,WALK_LOCATE_SHOULDER,0,KNEAD_STOP,0,KNOCK_STOP,0,0,SPEED_1,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_5,0},
  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,0,KNEAD_RUN_STOP_AT_MED,1,KNOCK_STOP,0,0,SPEED_1,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_5,0},
  {BACK_SUB_MODE_PRESS,WALK_LOCATE_PressNeck,0,KNEAD_STOP,0,KNOCK_STOP,0,0,SPEED_2,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_5,0},
  {BACK_SUB_MODE_SOFT_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,40,0,SPEED_3,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_5,0},
  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,0,KNEAD_RUN_STOP_AT_MIN,5,KNOCK_STOP,0,0,SPEED_1,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_5,0},
  
  {BACK_SUB_MODE_PRESS,WALK_LOCATE_SHOULDER,0,KNEAD_STOP,0,KNOCK_STOP,0,0,SPEED_1,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_5,0},
  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,0,KNEAD_RUN_STOP_AT_MED,1,KNOCK_STOP,0,0,SPEED_1,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_5,0},
  {BACK_SUB_MODE_PRESS,WALK_LOCATE_PressNeck,0,KNEAD_STOP,0,KNOCK_STOP,0,0,SPEED_2,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_5,0},
  {BACK_SUB_MODE_SOFT_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,40,0,SPEED_3,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_5,0},
  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,0,KNEAD_RUN_STOP_AT_MIN,5,KNOCK_STOP,0,0,SPEED_1,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_5,0},
  
  //搓背  
  {BACK_SUB_MODE_RUBBING,WALK_LOCATE_ABSULATE,0,KNEAD_RUN_RUBBING,0,KNOCK_STOP,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_5,0},
  {BACK_SUB_MODE_RUBBING,WALK_LOCATE_PressNeck,0,KNEAD_RUN_RUBBING,0,KNOCK_STOP,0,0,SPEED_5,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_5,0},
  {BACK_SUB_MODE_RUBBING,WALK_LOCATE_ABSULATE,WAIST_POSITION,KNEAD_RUN_RUBBING,0,KNOCK_STOP,0,0,SPEED_6,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_5,0},
  {BACK_SUB_MODE_RUBBING,WALK_LOCATE_PressNeck,0,KNEAD_RUN_RUBBING,0,KNOCK_STOP,0,0,SPEED_5,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_5,0},
  {BACK_SUB_MODE_RUBBING,WALK_LOCATE_ABSULATE,WAIST_POSITION,KNEAD_RUN_RUBBING,0,KNOCK_STOP,0,0,SPEED_4,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_5,0},
  
  
  //行进式揉捏到底
  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_NeckMed,0,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_5,0},
  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,20,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_5,0},
  
  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_SHOULDER,0,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_5,0},
  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,20,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_5,0},
  
  {BACK_SUB_MODE_KNEAD,WALK_SHOULDER_WAIST_1_10,0,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_5,0},
  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,20,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_5,0},
  
  {BACK_SUB_MODE_KNEAD,WALK_SHOULDER_WAIST_3_10,0,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_5,0},
  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,20,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_5,0},
  
  {BACK_SUB_MODE_KNEAD,WALK_SHOULDER_WAIST_5_10,0,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_5,0},
  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,20,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_5,0},
  
  {BACK_SUB_MODE_KNEAD,WALK_SHOULDER_WAIST_7_10,0,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_5,0},
  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,20,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_5,0},
  
  {BACK_SUB_MODE_KNEAD,WALK_SHOULDER_WAIST_9_10,0,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_5,0},
  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,20,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_5,0},
  
  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_WAIST,0,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_5,0},
  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,20,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_5,0},
  
  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_ABSULATE,0,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_5,0},
  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,20,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_5,0},
  //腰部定点敲打
  {BACK_SUB_MODE_PRESS,WALK_LOCATE_WAIST,0,KNEAD_STOP,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_5,0},
  {BACK_SUB_MODE_SOFT_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,30,0,SPEED_3,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_5,0},
  {BACK_SUB_MODE_SOFT_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,35,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_5,0},
  {BACK_SUB_MODE_SOFT_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,40,0,SPEED_5,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_5,0},
  {BACK_SUB_MODE_SOFT_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,40,0,SPEED_6,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_5,0},
  {BACK_SUB_MODE_SOFT_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,40,0,SPEED_5,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_5,0},
  {BACK_SUB_MODE_SOFT_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,35,0,SPEED_4,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_5,0},
  {BACK_SUB_MODE_SOFT_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,30,0,SPEED_3,_3D_PROGRAM,AXIS_WEAKER,_3D_SPEED_5,0},
  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,0,KNEAD_RUN_STOP_AT_MED,5,KNOCK_STOP,0,0,SPEED_4,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_5,0},
  {BACK_SUB_MODE_SOFT_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,30,0,SPEED_3,_3D_PROGRAM,AXIS_WEAKER,_3D_SPEED_5,0},
  {BACK_SUB_MODE_SOFT_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,35,0,SPEED_4,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_5,0},
  {BACK_SUB_MODE_SOFT_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,40,0,SPEED_5,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_5,0},
  {BACK_SUB_MODE_SOFT_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,40,0,SPEED_6,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_5,0},
  {BACK_SUB_MODE_SOFT_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,40,0,SPEED_5,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_5,0},
  {BACK_SUB_MODE_SOFT_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,35,0,SPEED_4,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_5,0},
  {BACK_SUB_MODE_SOFT_KNOCK,WALK_LOCATE_PARK,0,KNEAD_STOP,0,KNOCK_RUN,30,0,SPEED_3,_3D_PROGRAM,AXIS_WEAKER,_3D_SPEED_5,0},
  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,0,KNEAD_RUN_STOP_AT_MIN,5,KNOCK_STOP,0,0,SPEED_4,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_5,0},

} ;


