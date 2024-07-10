/* DO NOT EDIT THIS FILE */
/* This file is autogenerated by the text-database code generator */

#include <stdarg.h>
#include <touchgfx/TextProvider.hpp>
#include <touchgfx/Texts.hpp>
#include <touchgfx/TypedText.hpp>
#include <touchgfx/Unicode.hpp>
#include <touchgfx/hal/HAL.hpp>
#include <touchgfx/lcd/LCD.hpp>
#include <texts/TypedTextDatabase.hpp>

uint16_t touchgfx::Font::getStringWidth(const touchgfx::Unicode::UnicodeChar* text, ...) const
{
    va_list pArg;
    va_start(pArg, text);
    uint16_t width = getStringWidthLTR(TEXT_DIRECTION_LTR, text, pArg);
    va_end(pArg);
    return width;
}

uint16_t touchgfx::Font::getStringWidth(touchgfx::TextDirection textDirection, const touchgfx::Unicode::UnicodeChar* text, ...) const
{
    va_list pArg;
    va_start(pArg, text);
    uint16_t width = getStringWidthLTR(textDirection, text, pArg);
    va_end(pArg);
    return width;
}

touchgfx::Unicode::UnicodeChar touchgfx::TextProvider::getNextLigature(TextDirection direction)
{
    if (fontGsubTable && nextCharacters.peekChar())
    {
        substituteGlyphs();
        if (nextCharacters.peekChar(1) == 0x093F) // Hindi I-matra
        {
            nextCharacters.replaceAt1(nextCharacters.peekChar());
            nextCharacters.replaceAt0(0x093F);
        }
    }
    return getNextChar();
}

void touchgfx::TextProvider::initializeInternal()
{
    fillInputBuffer();
}

void touchgfx::LCD::drawString(touchgfx::Rect widgetArea, const touchgfx::Rect& invalidatedArea, const touchgfx::LCD::StringVisuals& stringVisuals, const touchgfx::Unicode::UnicodeChar* format, ...)
{
    va_list pArg;
    va_start(pArg, format);
    drawStringLTR(widgetArea, invalidatedArea, stringVisuals, format, pArg);
    va_end(pArg);
}

// Default TypedTextDatabase
extern const touchgfx::TypedText::TypedTextData* const typedTextDatabaseArray[];

TEXT_LOCATION_FLASH_PRAGMA
KEEP extern const touchgfx::Unicode::UnicodeChar texts_all_languages[] TEXT_LOCATION_FLASH_ATTRIBUTE = {
    0x57, 0x61, 0x69, 0x74, 0x20, 0x66, 0x6f, 0x72, 0x20, 0x63, 0x6f, 0x6e, 0x6e, 0x65, 0x63, 0x74, 0x69, 0x6f, 0x6e, 0x0, // @0 "Wait for connection"
    0x2, 0x3a, 0x2, 0x0, // @20 "<>:<>"
    0x2, 0x2e, 0x2, 0x0, // @24 "<>.<>"
    0x2, 0x2e, 0x2, 0x56, 0x0, // @28 "<>.<>V"
    0x2, 0x25, 0x0, // @33 "<>%"
    0x57, 0x3a, 0x20, 0x2, 0x0, // @36 "W: <>"
    0x70b9, 0x51fb, 0x53, 0x54, 0x41, 0x52, 0x54, 0x5f00, 0x59cb, 0x6d4b, 0x91cf, 0x0, // @41 "??START????"
    0x5065, 0x5eb7, 0x4fe1, 0x606f, 0x83b7, 0x53d6, 0x4e2d, 0x2e, 0x2e, 0x2e, 0x0, // @53 "???????..."
    0x2, 0x62, 0x70, 0x6d, 0x0, // @64 "<>bpm"
    0x2, 0x6c, 0x75, 0x78, 0x0, // @69 "<>lux"
    0x4e, 0x65, 0x77, 0x20, 0x54, 0x65, 0x78, 0x74, 0x0, // @74 "New Text"
    0x2, 0x2e, 0x0, // @83 "<>."
    0x2b, 0x31, 0x38, 0x30, 0x2e, 0x30, 0x0, // @86 "+180.0"
    0x2, 0x41, 0x0, // @93 "<>A"
    0x2, 0xb0, 0x0, // @96 "<>?"
    0x2, 0x2103, 0x0, // @99 "<>?"
    0x30, 0x2e, 0x30, 0x30, 0x31, 0x0, // @102 "0.001"
    0x31, 0x32, 0x30, 0x30, 0x30, 0x0, // @108 "12000"
    0x30, 0x30, 0x30, 0x30, 0x0, // @114 "0000"
    0x32, 0x30, 0x32, 0x33, 0x0, // @119 "2023"
    0x32, 0x39, 0x2e, 0x35, 0x0, // @124 "29.5"
    0x35, 0x36, 0x2e, 0x33, 0x0, // @129 "56.3"
    0x31, 0x30, 0x30, 0x0, // @134 "100"
    0x31, 0x32, 0x0, // @138 "12"
    0x31, 0x36, 0x0, // @141 "16"
    0x32, 0x35, 0x0, // @144 "25"
    0x33, 0x38, 0x0, // @147 "38"
    0x35, 0x30, 0x0 // @150 "50"
};

TEXT_LOCATION_FLASH_PRAGMA
KEEP extern const uint32_t indicesGb[] TEXT_LOCATION_FLASH_ATTRIBUTE;

// Array holding dynamically installed languages
struct TranslationHeader
{
    uint32_t offset_to_texts;
    uint32_t offset_to_indices;
    uint32_t offset_to_typedtext;
};
static const TranslationHeader* languagesArray[1] = { 0 };

// Compiled and linked in languages
static const uint32_t* const staticLanguageIndices[] = {
    indicesGb
};

touchgfx::LanguageId touchgfx::Texts::currentLanguage = static_cast<touchgfx::LanguageId>(0);
static const touchgfx::Unicode::UnicodeChar* currentLanguagePtr = 0;
static const uint32_t* currentLanguageIndices = 0;

void touchgfx::Texts::setLanguage(touchgfx::LanguageId id)
{
    const touchgfx::TypedText::TypedTextData* currentLanguageTypedText = 0;
    if (id < 1)
    {
        if (languagesArray[id] != 0)
        {
            // Dynamic translation is added
            const TranslationHeader* translation = languagesArray[id];
            currentLanguagePtr = (const touchgfx::Unicode::UnicodeChar*)(((const uint8_t*)translation) + translation->offset_to_texts);
            currentLanguageIndices = (const uint32_t*)(((const uint8_t*)translation) + translation->offset_to_indices);
            currentLanguageTypedText = (const touchgfx::TypedText::TypedTextData*)(((const uint8_t*)translation) + translation->offset_to_typedtext);
        }
        else
        {
            // Compiled and linked in languages
            currentLanguagePtr = texts_all_languages;
            currentLanguageIndices = staticLanguageIndices[id];
            currentLanguageTypedText = typedTextDatabaseArray[id];
        }
    }

    if (currentLanguageTypedText)
    {
        currentLanguage = id;
        touchgfx::TypedText::registerTypedTextDatabase(currentLanguageTypedText,
                                                       TypedTextDatabase::getFonts(), TypedTextDatabase::getInstanceSize());
    }
}

void touchgfx::Texts::setTranslation(touchgfx::LanguageId id, const void* translation)
{
    languagesArray[id] = (const TranslationHeader*)translation;
}

const touchgfx::Unicode::UnicodeChar* touchgfx::Texts::getText(TypedTextId id) const
{
    return &currentLanguagePtr[currentLanguageIndices[id]];
}
