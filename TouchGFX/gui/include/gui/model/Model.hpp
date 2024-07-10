#ifndef MODEL_HPP
#define MODEL_HPP
extern "C" {
#include "stdint.h"
}
class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }
    void tick();
		void toggleBL();
		//控制设备翻转状态
    void setMotorStatus();
		void ChangeScreen();
		// void setDCFanStatus(bool state);
		uint8_t getBacklightValue();	//获取背光值
        void setBacklightValue(uint8_t value);	//设置背光值
		//HomePageView的任务的状态
		void HomePageViewTask(bool enable);
		//FiveKeyPageView的任务的状态
		void FiveKeyPageViewTask(bool enable);	
		//SettingPageView的任务的状态
		void SettingPageViewTask(bool enable);
		//SixAxisPageView的任务的状态
		void SixAxisPageViewTask(bool enable);	
		//健康监测任务使能
		void HeartRateTaskEnable(bool newStatus);
		//ApplicationPageView界面的FIRE任务的状态
		void ApplicationPageViewFireTask(bool enable);	
		
        /*
        //数码管显示任务使能
		void NixieTubeTaskEnable(bool newStatus);
		//数码管显示值设置
		void setNixieTubeValue(uint16_t showValue);
        */
        
		//ApplicationPageView界面的WiFiModalLink的任务的状态
		void ApplicationPageViewWiFiModalLinkTask(bool enable);	
protected:
    ModelListener* modelListener;
//		FrontendApplication& application() {
//        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
//    }
};

#endif // MODEL_HPP
