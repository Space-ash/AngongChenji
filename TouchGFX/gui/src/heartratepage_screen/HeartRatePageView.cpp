#include <gui/heartratepage_screen/HeartRatePageView.hpp>
#include <texts\TextKeysAndLanguages.hpp>

HeartRatePageView::HeartRatePageView()
{

}

void HeartRatePageView::setupScreen()
{
    HeartRatePageViewBase::setupScreen();
}

void HeartRatePageView::tearDownScreen()
{
    HeartRatePageViewBase::tearDownScreen();
}

//健康监测信息上传
void HeartRatePageView::updateHeartRateInfo(uint32_t newHeartRate, uint32_t newSPO2)
{
		//更新脉搏
		Unicode::snprintf(textPulseBuffer, TEXTPULSE_SIZE, "%d",newHeartRate);
	  textPulse.invalidate();
		//更新血氧饱和度
		Unicode::snprintf(textSPOZBuffer, TEXTSPOZ_SIZE, "%d",newSPO2);
	  textSPOZ.invalidate();
		//测量提示-重新测量
		textInfo.setTypedText(TypedText(T_TEXTINFO1));
		textInfo.invalidate();
}
//启动健康检测
void HeartRatePageView::beginHeartRate()
{
	//使能健康监测任务
	presenter->HeartRateTaskState(true);	//健康监测任务使能
	//测量提示-信息读取中
	textInfo.setTypedText(TypedText(T_TEXTINFO2));
	textInfo.invalidate();
}
//打开健康检测页面
void HeartRatePageView::openModalHeartRate()
{

	//显示健康检测页面
	modalHeartRate.show();
}
//退出健康检测页面
void HeartRatePageView::closedModalHeartRate()
{
	//关闭健康监测任务
	presenter->HeartRateTaskState(false);	//健康监测任务禁能
	//隐藏健康检测页面
	modalHeartRate.hide();
}
