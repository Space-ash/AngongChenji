#ifndef HOMEPAGEVIEW_HPP
#define HOMEPAGEVIEW_HPP

#include <gui_generated/homepage_screen/HomePageViewBase.hpp>
#include <gui/homepage_screen/HomePagePresenter.hpp>

class HomePageView : public HomePageViewBase
{
public:
        HomePageView();
        virtual ~HomePageView() {}
        virtual void setupScreen();
        virtual void tearDownScreen();
		// void handleTickEvent();
		//更新日期和时间
		virtual void updateDate(uint8_t newYear, uint8_t newMonth, uint8_t newDate, uint8_t newWeekDay); 
		virtual void updateTime(uint8_t newHours, uint8_t newMinutes, uint8_t newSeconds);
		
        //更新温湿度、光照度数据上传	
		virtual void updateHomePageInfo(float newHum, float newTem);
            
        /*
        //获取WiFi模组的RSSI值
		virtual void updateWiFiRSSI(uint8_t (&pWiFiInfo)[40], uint16_t newRSSI);
        //连接WiFi
		virtual void connectWiFi();
        //文本与RSSI更新
        void TextAreaAddStr(uint8_t* str, uint32_t len, uint16_t newRSSI);
        */
            
		void ChangeScreen();

/*            
protected:
	  uint8_t textBuf[200];
*/

};

#endif // HOMEPAGEVIEW_HPP
