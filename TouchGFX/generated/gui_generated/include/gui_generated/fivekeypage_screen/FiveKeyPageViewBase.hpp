/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef FIVEKEYPAGEVIEWBASE_HPP
#define FIVEKEYPAGEVIEWBASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/fivekeypage_screen/FiveKeyPagePresenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <touchgfx/widgets/ToggleButton.hpp>
#include <touchgfx/widgets/TextAreaWithWildcard.hpp>

class FiveKeyPageViewBase : public touchgfx::View<FiveKeyPagePresenter>
{
public:
    FiveKeyPageViewBase();
    virtual ~FiveKeyPageViewBase();
    virtual void setupScreen();

protected:
    FrontendApplication& application() {
        return *static_cast<FrontendApplication*>(touchgfx::Application::getInstance());
    }

    /*
     * Member Declarations
     */
    touchgfx::Box __background;
    touchgfx::Image FiveKeyBackground;
    touchgfx::ToggleButton BackPrevious;
    touchgfx::ToggleButton BackHomePage;
    touchgfx::Image FiveKeyImage;
    touchgfx::TextAreaWithTwoWildcards textFiveKeyVal;

    /*
     * Wildcard Buffers
     */
    static const uint16_t TEXTFIVEKEYVALBUFFER1_SIZE = 2;
    touchgfx::Unicode::UnicodeChar textFiveKeyValBuffer1[TEXTFIVEKEYVALBUFFER1_SIZE];
    static const uint16_t TEXTFIVEKEYVALBUFFER2_SIZE = 5;
    touchgfx::Unicode::UnicodeChar textFiveKeyValBuffer2[TEXTFIVEKEYVALBUFFER2_SIZE];

private:

    /*
     * Callback Declarations
     */
    touchgfx::Callback<FiveKeyPageViewBase, const touchgfx::AbstractButton&> buttonCallback;

    /*
     * Callback Handler Declarations
     */
    void buttonCallbackHandler(const touchgfx::AbstractButton& src);

};

#endif // FIVEKEYPAGEVIEWBASE_HPP
