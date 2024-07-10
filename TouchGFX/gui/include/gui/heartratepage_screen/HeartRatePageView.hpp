#ifndef HEARTRATEPAGEVIEW_HPP
#define HEARTRATEPAGEVIEW_HPP

#include <gui_generated/heartratepage_screen/HeartRatePageViewBase.hpp>
#include <gui/heartratepage_screen/HeartRatePagePresenter.hpp>

class HeartRatePageView : public HeartRatePageViewBase
{
public:
    HeartRatePageView();
    virtual ~HeartRatePageView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    //启动健康检测
    virtual void beginHeartRate();	//开始测量脉搏与血氧饱和度
	virtual void openModalHeartRate();	//打开健康监测页面
	virtual void closedModalHeartRate();	//关闭健康监测页面
    //健康监测信息上传
	virtual void updateHeartRateInfo(uint32_t newHeartRate, uint32_t newSPO2);
protected:
};

#endif // HEARTRATEPAGEVIEW_HPP
