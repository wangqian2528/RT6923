
//体型检测功能只有四个全身自动程序才具备
//力度较强的全身自动
const WALK_KNEAD_KNOCK_MOTOR_STRUCT_AUTO AutoFunctionStretch[] = {
//  {BACK_SUB_MODE_PRESS,WALK_LOCATE_ABSULATE,0,KNEAD_STOP_AT_MIN,0,KNOCK_STOP,0,0,SPEED_1,_3D_PROGRAM,AXIS_WEAKEST,_3D_SPEED_3,0}, //按摩椅到达拉腿位置，机芯到达最低处 
//  {BACK_SUB_MODE_WAVELET,WALK_LOCATE_PARK,0,KNEAD_RUN,0,KNOCK_RUN,0,0,SPEED_4,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_3,0},        //充气，拉腿准备阶段
//  {BACK_SUB_MODE_PRESS,WALK_LOCATE_ABSULATE,WAIST_POSITION,KNEAD_STOP_AT_MIN,0,KNOCK_STOP,8,2,SPEED_1,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_3,0}, //拉腿
//  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,0,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,AXIS_STRONGEST,_3D_SPEED_3,0}	//加压时间	
  {BACK_SUB_MODE_PRESS,WALK_LOCATE_ABSULATE           ,0,KNEAD_STOP_AT_MED,0,KNOCK_STOP,0,0,SPEED_1,_3D_PROGRAM,AXIS_MIDDLE  ,_3D_SPEED_7,0}, //按摩椅到达拉腿位置，机芯到达最低处 
  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK               ,0,KNEAD_RUN        ,0,KNOCK_STOP,0,0,SPEED_2,_3D_PROGRAM,AXIS_MIDDLE,_3D_SPEED_7,0},
  {BACK_SUB_MODE_PRESS,WALK_LOCATE_ABSULATE,POSITION_T4 ,KNEAD_STOP_AT_MIN,0,KNOCK_STOP,8,2,SPEED_1,_3D_PROGRAM,AXIS_MIDDLE  ,_3D_SPEED_7,0}, //拉腿
  {BACK_SUB_MODE_PRESS,WALK_LOCATE_PARK               ,30,KNEAD_STOP_AT_MIN,0,KNOCK_STOP,8,2,SPEED_1,_3D_PROGRAM,AXIS_STRONGER,_3D_SPEED_5,30}, //拉腿
  {BACK_SUB_MODE_PRESS,WALK_LOCATE_PARK               ,0,KNEAD_STOP       ,0,KNOCK_STOP,8,2,SPEED_1,_3D_PROGRAM,AXIS_MIDDLE  ,_3D_SPEED_4,0}, //拉腿
  
  
  
};


const WALK_KNEAD_KNOCK_MOTOR_STRUCT_AUTO AutoFunctionStretch1[] = {
  
  {BACK_SUB_MODE_PRESS,WALK_LOCATE_ABSULATE,0,KNEAD_STOP_AT_MIN,0,KNOCK_STOP,0,0,SPEED_1,_3D_PROGRAM,AXIS_WEAKEST,_3D_SPEED_7,0}, //按摩椅到达拉腿位置，机芯到达最低处 
  {BACK_SUB_MODE_WAVELET,WALK_LOCATE_PARK,0,KNEAD_RUN,0,KNOCK_RUN,0,0,SPEED_4,_3D_PROGRAM,_3D_2,_3D_SPEED_3,0},        //充气，拉腿准备阶段
  {BACK_SUB_MODE_PRESS,WALK_LOCATE_ABSULATE,WAIST_POSITION,KNEAD_STOP_AT_MIN,0,KNOCK_STOP,8,2,SPEED_1,_3D_PROGRAM,_3D_2,_3D_SPEED_3,0}, //拉腿
  {BACK_SUB_MODE_KNEAD,WALK_LOCATE_PARK,0,KNEAD_RUN,0,KNOCK_STOP,0,0,SPEED_3,_3D_PROGRAM,_3D_2,_3D_SPEED_3,0}	//加压时间	
   
};