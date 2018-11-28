

#include "temperature.h"


//#ifdef adc_temperaute_feedback
const unsigned short temp[71+30]={
  32371 ,
  30781,29278,27856,26512,25240,24035,22895,21815,20791,19821,//1-10¶È
  
  18901,18029 ,17202,16417,15672,14964,14292,13654,13048,12471,      //11-20¶È

  11923,11402,10907,10435,10000,9559,9153 ,8765,8397,8045 ,  //21-30¶È
  
  7710,7391,7086,6796,6519,6255,6003,5762,5532 ,5313 ,  //31-40¶È
  
  5103,4903,4712,4529,4354,4187,4027,3874,3728,3588,  //41-50¶È
    
  3453, 3325,3202,3084,2972,2864,2760,2661 ,2565,2474,//51-60¶È
  
  2387,2303,2222,2145,2070,1999,1931,1865,1802,1741,  //61-70¶È
  //------------------------------------------------------------------
    1683,1627,1573,1521,1471,1423,1377,1332,1290,1248,  //71-80¶È
      
      1209,1171,1134,1098,1065,1031,1000,969,940,911,  //81-90¶È  
          884,858,832,807,784,761,739,717,696,677  //91-100¶È   
        
      
};


signed char  ADC_CHECK_TEMPERATUER(unsigned int w_dat)
{
  signed char temp=-1;
  unsigned int w_dat_buf=w_dat/100;
  
   unsigned int w_dat_buf2=w_dat/10;
   
  if(w_dat_buf>=190)//1-10¶È
  {
      if(w_dat_buf<=202)temp=10;
      else if(w_dat_buf<=212)temp=9;
      else if(w_dat_buf<=223)temp=8;
       else if(w_dat_buf<=234)temp=7;
        else if(w_dat_buf<=246)temp=6;
        else if(w_dat_buf<=258)temp=5;
	else if(w_dat_buf<=271)temp=4;
	else if(w_dat_buf<=285)temp=3;
	else if(w_dat_buf<=299)temp=2;
	else if(w_dat_buf<=300)temp=1;
	else temp=0;
	
    
    
    
    
  }
  else if(w_dat_buf>=120 &&w_dat_buf<190) //11-20¶È
  {
      if(w_dat_buf<=126)temp=20;
      else if(w_dat_buf<=133)temp=19;
      else if(w_dat_buf<=139)temp=18;
       else if(w_dat_buf<=145)temp=17;
        else if(w_dat_buf<=152)temp=16;
        else if(w_dat_buf<=160)temp=15;
	else if(w_dat_buf<=168)temp=14;
	else if(w_dat_buf<=176)temp=13;
	else if(w_dat_buf<=184)temp=12;
	else //if(w_dat_buf<=180)
          temp=11;
	
    
    
  }
  else if(w_dat_buf>=80 &&w_dat_buf<120)////21-30¶È
  {
       if(w_dat_buf<=82)temp=30;
      else if(w_dat_buf<=85)temp=29;
      else if(w_dat_buf<=89)temp=28;
       else if(w_dat_buf<=93)temp=27;
        else if(w_dat_buf<=98)temp=26;
        else if(w_dat_buf<=102)temp=25;
	else if(w_dat_buf<=106)temp=24;
	else if(w_dat_buf<=111)temp=23;
	else if(w_dat_buf<=116)temp=22;
	else //if(w_dat_buf<=120)
          temp=21;
    
    
  }
  
  else if(w_dat_buf>=53 &&w_dat_buf<80)//// //31-40¶È
  {
       if(w_dat_buf<=54)temp=40;
      else if(w_dat_buf<=56)temp=39;
      else if(w_dat_buf<=59)temp=38;
       else if(w_dat_buf<=61)temp=37;
        else if(w_dat_buf<=64)temp=36;
        else if(w_dat_buf<=66)temp=35;
	else if(w_dat_buf<=69)temp=34;
	else if(w_dat_buf<=73)temp=33;
	else if(w_dat_buf<=75)temp=32;
	else 
          //if(w_dat_buf<81)
          temp=31;
    
    
  }
  else if(w_dat_buf>=35 &&w_dat_buf<53)//// //41-50¶È
  {
    
        if(w_dat_buf<=37)temp=50;
        else if(w_dat_buf<=38)temp=49;
        else if(w_dat_buf<=39)temp=48;
        else if(w_dat_buf<=40)temp=47;
        else if(w_dat_buf<=42)temp=46;
        else if(w_dat_buf<=44)temp=45;
	else if(w_dat_buf<=46)temp=44;
	else if(w_dat_buf<=48)temp=43;
	else if(w_dat_buf<=50)temp=42;
	else 
          //if(w_dat_buf<56)
          temp=41;
    
    
    
  } 
  else if(w_dat_buf>=24 &&w_dat_buf<35)//// ////51-60¶È
  {
    
          if(w_dat_buf<=25)temp=60;
        else if(w_dat_buf<=26)temp=59;
        else if(w_dat_buf<=27)temp=58;
        else if(w_dat_buf<=27)temp=57;
        else if(w_dat_buf<=28)temp=56;
        else if(w_dat_buf<=29)temp=55;
	else if(w_dat_buf<=30)temp=54;
	else if(w_dat_buf<=31)temp=53;
	else if(w_dat_buf<=34)temp=52;
	else 
          //if(w_dat_buf<40)
            temp=51;
    
  } 
  else if(w_dat_buf>=17 &&w_dat_buf<24) //61-70¶È
  {

       if(w_dat_buf2<=177)temp=70;
       else if(w_dat_buf2<=183)temp=69;
       else if(w_dat_buf2<=189)temp=68;
       else if(w_dat_buf2<=196)temp=67;
       else if(w_dat_buf2<=203)temp=66;
       else if(w_dat_buf2<=210)temp=65;
       else if(w_dat_buf2<=218)temp=64;
       else if(w_dat_buf2<=226)temp=63;
         else if(w_dat_buf2<=234)temp=62;
	 else temp=61;
       
       
    
  }
  
    else if(w_dat_buf>=12 &&w_dat_buf<17) //71-80¶È
  {
       /*if(w_dat_buf2<=160)temp=80;
       else if(w_dat_buf2<=165)temp=79;
       else if(w_dat_buf2<=170)temp=78;
       else if(w_dat_buf2<=174)temp=77;
       else if(w_dat_buf2<=179)temp=76;
       else if(w_dat_buf2<=185)temp=75;
       else if(w_dat_buf2<=191)temp=74;
       else if(w_dat_buf2<=196)temp=73;
         else if(w_dat_buf2<=202)temp=72;
	 else */
           temp=71;
       
       
    
  }
      else if(w_dat_buf>=9 &&w_dat_buf<12) //81-90¶È
  {/*
       if(w_dat_buf2<=120)temp=90;
       else if(w_dat_buf2<=124)temp=89;
       else if(w_dat_buf2<=128)temp=88;
       else if(w_dat_buf2<=131)temp=87;
       else if(w_dat_buf2<=135)temp=86;
       else if(w_dat_buf2<=139)temp=85;
       else if(w_dat_buf2<=143)temp=84;
       else if(w_dat_buf2<=147)temp=83;
         else if(w_dat_buf2<=151)temp=82;
	 else 
           */
           
           temp=81;
       
       
    
  }
   else if(w_dat_buf>=6 &&w_dat_buf<9) //91-100¶È
  {
    
    temp=91;
    
  }
  
 /*   unsigned int w_dat_buf_2=w_dat/1000;//uint K
  unsigned int w_temp_buf;
  unsigned char index=71;
  unsigned char by_i;
  unsigned char by_i_2;
  signed char temp;
  
  // for(unsigned char i=0;i<71;i++)
   //{
    // if(w_temp_buf=)
     
     
     
  // }
      if((temp[index/2]/1000)==w_dat_buf_2)//35¶È
      {
	temp=index/2;
	return temp;
	
      }
      else if((temp[index/2]/1000)>w_dat_buf_2)//>35¶È , ×èÖµÐ¡£¬ÎÂ¶È¸ß£¬
      {
	
	for(by_i=36,by_i<index;by_i++)
	{
	   if(temp[by_i]==w_dat_buf_2)
	   {
	     by_i_2=by_i;
	     
	     
	     
	   }
	  
	  
	  
	}
	
	
	
      }
        else if((temp[index/2]/1000)<w_dat_buf_2)//<35¶È
      {
	
	
	
      }
  
  
  */
  
  
  
  return  temp;
  
  
  
  
}

//#endif