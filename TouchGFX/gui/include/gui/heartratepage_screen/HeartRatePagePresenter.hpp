#ifndef HEARTRATEPAGEPRESENTER_HPP
#define HEARTRATEPAGEPRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class HeartRatePageView;

class HeartRatePagePresenter : public touchgfx::Presenter, public ModelListener
{
public:
    HeartRatePagePresenter(HeartRatePageView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~HeartRatePagePresenter() {};
        
    //健康监测任务使能
	virtual void HeartRateTaskState(bool newStatus);
	//健康监测信息上传
	virtual void updateHeartRateInfo(uint32_t newHeartRate, uint32_t newSPO2);

private:
    HeartRatePagePresenter();

    HeartRatePageView& view;
};

#endif // HEARTRATEPAGEPRESENTER_HPP
