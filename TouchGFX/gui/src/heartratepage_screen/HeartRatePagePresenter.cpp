#include <gui/heartratepage_screen/HeartRatePageView.hpp>
#include <gui/heartratepage_screen/HeartRatePagePresenter.hpp>

HeartRatePagePresenter::HeartRatePagePresenter(HeartRatePageView& v)
    : view(v)
{

}

void HeartRatePagePresenter::activate()
{

}

void HeartRatePagePresenter::deactivate()
{

}

//设置健康监测任务
void HeartRatePagePresenter::HeartRateTaskState(bool newStatus)
{
		if(newStatus == true)
			model->HeartRateTaskEnable(true);
		else
			model->HeartRateTaskEnable(false);
}
//健康监测信息上传
void HeartRatePagePresenter::updateHeartRateInfo(uint32_t newHeartRate, uint32_t newSPO2)
{
		view.updateHeartRateInfo(newHeartRate, newSPO2);
}