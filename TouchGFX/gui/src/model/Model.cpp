#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#if defined LINK_HARDWARE 	//TuchGFX仿真与实际硬件操作隔离
	//头文件包含
	extern "C"
	{
	#include "user_app.h"
	}
	extern RTC_DateTypeDef gSystemDate;  //获取日期结构体
	extern RTC_TimeTypeDef gSystemTime;   //获取时间结构体
	extern gTask_MarkEN gTaskEnMark;  //系统任务使能标识
	extern volatile uint8_t gLastTimeSeconds;	//上一次的时间	
	extern volatile float pitch,roll,yaw; //欧拉角
	// extern volatile SHT20_TemRH_Val gTemRH_Val;
    extern volatile HDC1080_TemRH_Val gTemRH_Val;
	extern volatile StruLTR553_Val gLTR553_Val;	//AP3216数据结构
	extern gTask_BitDef gTaskStateBit;  //任务执行过程中使用到的标志位
	//
	extern wifiRSSI ao_wifiRSSI;
	extern volatile uint16_t gFiveKeyVal; //五向键原始值：0V/0.5V/1.0V/1.5V/2.0V
	extern volatile uint16_t gCurrentVal;	//资源扩展板电流，通道IN8   
	extern volatile uint16_t gVoltageVal;	//资源扩展板电压，通道IN9        
	extern volatile uint16_t gChipTempVal; //内部参考电压，通道IN12  
	extern volatile uint16_t gVrefVal;		//内部参考电压，通道IN13   	
	extern volatile uint16_t gVbatVal;		//RTC电池电压，通道IN14   
	// extern volatile uint16_t gNixieShowData;	//数码管显示的数据
	//
	volatile uint8_t gLastTimeSeconds = 0;	//上一次的时间	 
	volatile uint16_t gLastFiveKey = 0;	//上一次的按键值 
	volatile uint8_t gLastChipTemp = 0;	//上一次的温度值	
	//
	extern uint8_t gWiFiInfo[40];	//用于通知View界面的Text文本显示
	extern volatile uint8_t gBacklightVal;	//背光值，默认50%
	extern int32_t n_heart_rate;   //heart rate value=n_heart_rate/4,采样率100sps,max30102设置4点求平均
	extern int32_t n_sp02; //SPO2 value
	extern int8_t ch_spo2_valid;   //indicator to show if the SP02 calculation is valid
	extern int8_t  ch_hr_valid;    //indicator to show if the heart rate calculation is valid
	extern int8_t KeyChangeScreen;
#else //Designer仿真
	#include <ctime>
	#ifndef _MSC_VER
	#include <sys/time.h>
	#endif /* _MSC_VER*/
	//
	volatile uint8_t gBacklightVal = 50;	//背光值，默认50%
#endif

// 定义状态机状态
enum FallState {
    NORMAL,
    TILTING,
    FALLING
};

// 全局变量
FallState currentState = NORMAL;
uint32_t tiltStartTime = 0;
const uint32_t TILT_DURATION_THRESHOLD = 2000; // 持续时间阈值，单位毫秒

// 定义正常工作的姿态范围
const int YAW_NORMAL_MIN = -20;
const int YAW_NORMAL_MAX = 80;
const int PITCH_NORMAL_MIN = -60;
const int PITCH_NORMAL_MAX = 20;
const int ROLL_NORMAL_MIN = -80;
const int ROLL_NORMAL_MAX = 80;

// 定义跌倒姿态的阈值
const int FALL_ROLL_THRESHOLD = 120;

/**********************************TouchGFX与底层间的访问**********************************/
Model::Model() : modelListener(0)
{

}
//
void Model::tick()
{
	static uint8_t tickCount = 0;	//减少数据上传的次数，优化界面刷新
	tickCount++;	
#if defined LINK_HARDWARE
	//更新日期与时间
	if(gTaskEnMark.UPDATE_TIME_EN && (gSystemTime.Seconds != gLastTimeSeconds))	//每秒同步一次界面时间
	{
		modelListener->updateDate(gSystemDate.Year,gSystemDate.Month,gSystemDate.Date,gSystemDate.WeekDay);
		modelListener->updateTime(gSystemTime.Hours, gSystemTime.Minutes, gSystemTime.Seconds);
		//更新新值
		gLastTimeSeconds = gSystemTime.Seconds;	
        
	}
	//更新芯片参数
	if(gTaskEnMark.UPDATE_CHIPINFO_EN && (abs(gChipTempVal-gLastChipTemp) >= 1))	//温度变化超过1度
	{
		modelListener->updateChipInfor(gChipTempVal, gVrefVal, gVbatVal);	//更新芯片温度、参考电压、Vbat
		//更新新值
		gLastChipTemp=gChipTempVal;
	}
    
	// 更新欧拉角
    if (gTaskEnMark.UPDATE_SIX_AXIS_EN) // 六轴界面活动时上传
    {
        modelListener->updateSixAxis(pitch, roll, yaw);
        switch (currentState) {
            case NORMAL:
                if ((roll > FALL_ROLL_THRESHOLD || roll < -FALL_ROLL_THRESHOLD) ||
                    (yaw < YAW_NORMAL_MIN || yaw > YAW_NORMAL_MAX) ||
                    (pitch < PITCH_NORMAL_MIN || pitch > PITCH_NORMAL_MAX)) {
                    currentState = TILTING;
                    tiltStartTime = HAL_GetTick();
                }
                break;

            case TILTING:
                if ((roll <= FALL_ROLL_THRESHOLD && roll >= -FALL_ROLL_THRESHOLD) &&
                    (yaw >= YAW_NORMAL_MIN && yaw <= YAW_NORMAL_MAX) &&
                    (pitch >= PITCH_NORMAL_MIN && pitch <= PITCH_NORMAL_MAX)) {
                    currentState = NORMAL;
                } else if ((HAL_GetTick() - tiltStartTime) > TILT_DURATION_THRESHOLD) {
                    currentState = FALLING;
                    HAL_GPIO_WritePin(RUN_BEEP_GPIO_Port, RUN_BEEP_Pin, GPIO_PIN_SET); // 打开蜂鸣器
                }
                break;

            case FALLING:
                if ((roll <= FALL_ROLL_THRESHOLD && roll >= -FALL_ROLL_THRESHOLD) &&
                    (yaw >= YAW_NORMAL_MIN && yaw <= YAW_NORMAL_MAX) &&
                    (pitch >= PITCH_NORMAL_MIN && pitch <= PITCH_NORMAL_MAX)) {
                    currentState = NORMAL;
                    HAL_GPIO_WritePin(RUN_BEEP_GPIO_Port, RUN_BEEP_Pin, GPIO_PIN_RESET); // 关闭蜂鸣器
                }
                // 保持蜂鸣器在FALLING状态时持续报警
                else {
                    HAL_GPIO_WritePin(RUN_BEEP_GPIO_Port, RUN_BEEP_Pin, GPIO_PIN_SET); // 打开蜂鸣器
                }
                break;
        }
    }
    
	/*
    //获取WiFi模组的RSSI值
	if((gTaskEnMark.UPDATE_WIFI_RSSI_EN) && (gTaskEnMark.UPDATE_TIME_EN))	//只有在系统主页时，才进行WiFi的RSSI数据读取
	{
		modelListener->updateWiFiRSSI(gWiFiInfo, ao_wifiRSSI.gRSSI);
	}
    */
    //获取WiFi模组的RSSI值
	if((gTaskEnMark.UPDATE_WIFI_RSSI_EN) && (gTaskEnMark.UPDATE_APP_TASK_EN))	//只有在APP页面时，进行WiFi的RSSI数据读取
	{
		modelListener->updateWiFiRSSI(gWiFiInfo, ao_wifiRSSI.gRSSI);
	}
    
	//更新五向键数据
	if(gTaskEnMark.UPDATE_FIVEKEY_EN && (abs(gFiveKeyVal-gLastFiveKey) >= 12))	// 3.3*12/4095 = 11.7mV 
	{
		modelListener->updateFiveKey(gFiveKeyVal);
		//更新新值
		gLastFiveKey = gFiveKeyVal;
	}
    
    /*
	//APP页面的数据更新使能
	if(gTaskEnMark.UPDATE_APP_TASK_EN)	
	{
		if(gTaskStateBit.ExtFIRE)//检测到火焰与使能火焰状态更新
			modelListener->updateFireStatus(true);	//更新火焰状态
		else
			modelListener->updateFireStatus(false);	//更新火焰状态
		//电压、电流、温湿度、光照度数据上传
		if(!(tickCount % 5))	//降低界面刷新负担
			modelListener->updateAppPageInfo(gCurrentVal, gVoltageVal, gTemRH_Val.Humidity, gTemRH_Val.Temperature, gLTR553_Val.ALS);
	}
    */
    //APP页面的数据更新使能
	if(gTaskEnMark.UPDATE_APP_TASK_EN)	
	{
		if(gTaskStateBit.ExtFIRE) //检测到火焰与使能火焰状态更新
        {
            modelListener->updateFireStatus(true);	//更新火焰状态
            HAL_GPIO_WritePin(RUN_BEEP_GPIO_Port,RUN_BEEP_Pin,GPIO_PIN_SET);	//打开蜂鸣器
        }
		else
		{	
            modelListener->updateFireStatus(false);	//更新火焰状态
            HAL_GPIO_WritePin(RUN_BEEP_GPIO_Port,RUN_BEEP_Pin,GPIO_PIN_RESET);	//关闭蜂鸣器
        }
		//电压、电流、光照度数据上传
		if(!(tickCount % 5))	//降低界面刷新负担
			modelListener->updateAppPageInfo(gCurrentVal, gVoltageVal, gLTR553_Val.ALS);
	}
    //Home页面的数据更新使能
	if(gTaskEnMark.UPDATE_TIME_EN)	
	{
		//温湿度数据上传
		if(!(tickCount % 5))	//降低界面刷新负担
			modelListener->updateHomePageInfo(gTemRH_Val.Humidity, gTemRH_Val.Temperature);
	}
    
    
	//健康监测信息上传
	if(gTaskEnMark.UPDATE_HEART_RATE_EN)	
	{
		//send samples and calculation result to terminal program through UART
		if(ch_hr_valid || ch_spo2_valid)
		{
			modelListener->updateHeartRateInfo(n_heart_rate/4, n_sp02);
		}
		//
		if(gTaskStateBit.Max30102)	//单次测量完成，清除标志
		{
			ch_hr_valid =0;
			ch_spo2_valid=0;
			gTaskStateBit.Max30102 = 0;
			gTaskEnMark.UPDATE_HEART_RATE_EN = 0;
		}
	}
#else //Designer仿真
		timeval timenow;
		gettimeofday(&timenow, NULL);
		//仿真更新时间
		modelListener->updateTime((timenow.tv_sec / 60 / 60) % 24,(timenow.tv_sec / 60) % 60,timenow.tv_sec % 60);
#endif
}

/*
//直流风扇操作
void Model::setDCFanStatus(bool state)
{
	#if defined LINK_HARDWARE
	if(state == true)	
		HAL_GPIO_WritePin(FAN_GPIO_Port,FAN_Pin,GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(FAN_GPIO_Port,FAN_Pin,GPIO_PIN_RESET);
#endif
}
*/

//ApplicationPageView界面的FIRE任务的状态
void Model::ApplicationPageViewFireTask(bool enable)
{
	#if defined LINK_HARDWARE
	if(enable == true)	
		gTaskEnMark.UPDATE_APP_TASK_EN = 1;	//任务使能
	else
		gTaskEnMark.UPDATE_APP_TASK_EN = 0;	//任务清除
#endif
}
//HomePageView的任务的状态
void Model::HomePageViewTask(bool enable)
{
	#if defined LINK_HARDWARE
	if(enable == true)	
		gTaskEnMark.UPDATE_TIME_EN = 1;	//任务使能
	else
		gTaskEnMark.UPDATE_TIME_EN = 0;	//任务清除
#endif
}
//FiveKeyPageView的任务的状态
void Model::FiveKeyPageViewTask(bool enable)
{
	#if defined LINK_HARDWARE
	if(enable == true)	
		gTaskEnMark.UPDATE_FIVEKEY_EN = 1;	//任务使能
	else
		gTaskEnMark.UPDATE_FIVEKEY_EN = 0;	//任务清除
#endif
}
//设置健康监测任务
void Model::HeartRateTaskEnable(bool newStatus)
{
	#if defined LINK_HARDWARE
	if(newStatus == true)	
		gTaskEnMark.UPDATE_HEART_RATE_EN = 1;	//任务使能
	else
		gTaskEnMark.UPDATE_HEART_RATE_EN = 0;	//任务清除
#endif
}
//SettingPageView的任务的状态
void Model::SettingPageViewTask(bool enable)
{
#if defined LINK_HARDWARE
	if(enable == true)	
		gTaskEnMark.UPDATE_CHIPINFO_EN = 1;	//任务使能
	else
		gTaskEnMark.UPDATE_CHIPINFO_EN = 0;	//任务清除
#endif
}
//SixAxisPageView的任务的状态
void Model::SixAxisPageViewTask(bool enable)
{
#if defined LINK_HARDWARE
	if(enable == true)	
		gTaskEnMark.UPDATE_SIX_AXIS_EN = 1;	//任务使能
	else
		gTaskEnMark.UPDATE_SIX_AXIS_EN = 0;	//任务清除
#endif
}

/*
//数码管显示任务使能
void Model::NixieTubeTaskEnable(bool newStatus)
{
#if defined LINK_HARDWARE
	if(newStatus == true)	
		gTaskEnMark.UPDATE_NIXIE_SHOW_EN = 1;	//任务使能
	else
		gTaskEnMark.UPDATE_NIXIE_SHOW_EN = 0;	//任务清除
#endif
}
//数码管显示任务使能
void Model::setNixieTubeValue(uint16_t showValue)
{
#if defined LINK_HARDWARE
	gNixieShowData = showValue;	//更新数码管显示值
#endif
}
*/

//ApplicationPageView界面的WiFiModalLink的任务的状态
void Model::ApplicationPageViewWiFiModalLinkTask(bool enable)
{
#if defined LINK_HARDWARE
	if(enable == true)	
		gTaskEnMark.UPDATE_WIFI_RSSI_EN = 1;	//任务使能
	else
		gTaskEnMark.UPDATE_WIFI_RSSI_EN = 0;	//任务清除
#endif
}
//设置背光亮度
void Model::setBacklightValue(uint8_t value)
{
#if defined LINK_HARDWARE
    // No actual interaction with HW in this demo
    // Interact with actual HW/drivers to achieve this
    if (value != gBacklightVal)
    {
        gBacklightVal = value;
				Update_Backlight(gBacklightVal);	//设置背光
    }
#else 
    if (value != gBacklightVal)
    {
        gBacklightVal = value;
    }
#endif
}
//获取背光亮度
uint8_t Model::getBacklightValue()
{
#if defined LINK_HARDWARE
    return gBacklightVal;
#else 
		return gBacklightVal;	//仿真
#endif
}
//振动电机操作
void Model::setMotorStatus()
{
#if defined LINK_HARDWARE
		HAL_GPIO_TogglePin(EXT_MOTOR_GPIO_Port,EXT_MOTOR_Pin);	//振动电机状态的翻转	
#endif
}

