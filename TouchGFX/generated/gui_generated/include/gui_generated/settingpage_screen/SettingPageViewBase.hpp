/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SETTINGPAGEVIEWBASE_HPP
#define SETTINGPAGEVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/settingpage_screen/SettingPagePresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/ToggleButton.hpp>
#include <touchgfx/containers/Slider.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

class SettingPageViewBase : public touchgfx::View<SettingPagePresenter>
{
public:
    SettingPageViewBase();
    virtual ~SettingPageViewBase();
    virtual void setupScreen();

    /*
     * Virtual Action Handlers
     */
    virtual void newBacklightValueHandler(int value)
    {
        // Override and implement this function in SettingPage
    }

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Image image1;
    touchgfx::ToggleButton toggleButton1;
    touchgfx::Slider sliderScreenBacklight;
    touchgfx::TextAreaWithOneWildcard textBackLight;
    touchgfx::TextAreaWithOneWildcard textChipTemp;
    touchgfx::TextAreaWithTwoWildcards textChipVref;
    touchgfx::TextAreaWithTwoWildcards textChipVbat;

    /*
     * Wildcard Buffers
     */
    static const uint16_t TEXTBACKLIGHT_SIZE = 4;
    touchgfx::Unicode::UnicodeChar textBackLightBuffer[TEXTBACKLIGHT_SIZE];
    static const uint16_t TEXTCHIPTEMP_SIZE = 3;
    touchgfx::Unicode::UnicodeChar textChipTempBuffer[TEXTCHIPTEMP_SIZE];
    static const uint16_t TEXTCHIPVREFBUFFER1_SIZE = 2;
    touchgfx::Unicode::UnicodeChar textChipVrefBuffer1[TEXTCHIPVREFBUFFER1_SIZE];
    static const uint16_t TEXTCHIPVREFBUFFER2_SIZE = 3;
    touchgfx::Unicode::UnicodeChar textChipVrefBuffer2[TEXTCHIPVREFBUFFER2_SIZE];
    static const uint16_t TEXTCHIPVBATBUFFER1_SIZE = 2;
    touchgfx::Unicode::UnicodeChar textChipVbatBuffer1[TEXTCHIPVBATBUFFER1_SIZE];
    static const uint16_t TEXTCHIPVBATBUFFER2_SIZE = 3;
    touchgfx::Unicode::UnicodeChar textChipVbatBuffer2[TEXTCHIPVBATBUFFER2_SIZE];

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<SettingPageViewBase, const touchgfx::AbstractButton&> buttonCallback;
    touchgfx::Callback<SettingPageViewBase, const touchgfx::Slider&, int> sliderValueChangedCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);
    void sliderValueChangedCallbackHandler(const touchgfx::Slider& src, int value);

};

#endif // SETTINGPAGEVIEWBASE_HPP
