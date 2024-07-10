/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef HEARTRATEPAGEVIEWBASE_HPP
#define HEARTRATEPAGEVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/heartratepage_screen/HeartRatePagePresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/ToggleButton.hpp>
#include <touchgfx/containers/ModalWindow.hpp>
#include <touchgfx/widgets/Button.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>
#include <touchgfx/widgets/TextArea.hpp>

class HeartRatePageViewBase : public touchgfx::View<HeartRatePagePresenter>
{
public:
    HeartRatePageViewBase();
    virtual ~HeartRatePageViewBase();
    virtual void setupScreen();

    /*
     * Virtual Action Handlers
     */
    virtual void openModalHeartRate()
    {
        // Override and implement this function in HeartRatePage
    }
    virtual void closedModalHeartRate()
    {
        // Override and implement this function in HeartRatePage
    }
    virtual void beginHeartRate()
    {
        // Override and implement this function in HeartRatePage
    }

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Image heartrate_background;
    touchgfx::ToggleButton heartrate_page_measure;
    touchgfx::ModalWindow modalHeartRate;
    touchgfx::Button measureHeartRate;
    touchgfx::TextAreaWithOneWildcard textPulse;
    touchgfx::TextAreaWithOneWildcard textSPOZ;
    touchgfx::TextArea textInfo;
    touchgfx::Button closedHeartRateModal;
    touchgfx::ToggleButton Back2Home;
    touchgfx::ToggleButton toggleButton1;

    /*
     * Wildcard Buffers
     */
    static const uint16_t TEXTPULSE_SIZE = 4;
    touchgfx::Unicode::UnicodeChar textPulseBuffer[TEXTPULSE_SIZE];
    static const uint16_t TEXTSPOZ_SIZE = 4;
    touchgfx::Unicode::UnicodeChar textSPOZBuffer[TEXTSPOZ_SIZE];

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<HeartRatePageViewBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

};

#endif // HEARTRATEPAGEVIEWBASE_HPP