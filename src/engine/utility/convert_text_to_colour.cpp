#include <engine/utility/convert_text_to_colour.h>

constexpr uint64_t hash(std::string_view str) {
    uint64_t hash = 0;
    for (char c : str) {
        hash = (hash * 131) + c;
    }
    return hash;
}

constexpr uint64_t operator"" _hash(const char* str, size_t len) {
    return hash(std::string_view(str, len));
}

Color convertTextToColour(std::string stringColour) {
    Color finalColour = raylib::Color::RayWhite();

    switch (hash(stringColour)) {
        case "BLACK"_hash:
            finalColour = raylib::Color::Black();
            break;

        case "LIGHTGRAY"_hash:
            finalColour = raylib::Color::White();
            break;

        case "GRAY"_hash:
            finalColour = raylib::Color::Gray();
            break;

        case "DARKGRAY"_hash:
            finalColour = raylib::Color::DarkGray();
            break;
        
        case "YELLOW"_hash:
            finalColour = raylib::Color::Yellow();
            break;

        case "GOLD"_hash:
            finalColour = raylib::Color::Gold();
            break;

        case "ORANGE"_hash:
            finalColour = raylib::Color::Orange();
            break;

        case "PINK"_hash:
            finalColour = raylib::Color::Pink();
            break;

        case "RED"_hash:
            finalColour = raylib::Color::Red();
            break;
        
        case "MAROON"_hash:
            finalColour = raylib::Color::Maroon();
            break;

        case "GREEN"_hash:
            finalColour = raylib::Color::Green();
            break;

        case "LIME"_hash:
            finalColour = raylib::Color::Lime();
            break;

        case "DARKGREEN"_hash:
            finalColour = raylib::Color::DarkGreen();
            break;

        case "SKYBLUE"_hash:
            finalColour = raylib::Color::SkyBlue();
            break;
        
        case "BLUE"_hash:
            finalColour = raylib::Color::Blue();
            break;

        case "DARKBLUE"_hash:
            finalColour = raylib::Color::DarkBlue();
            break;

        case "PURPLE"_hash:
            finalColour = raylib::Color::Purple();
            break;

        case "VIOLET"_hash:
            finalColour = raylib::Color::Violet();
            break;

        case "DARKPURPLE"_hash:
            finalColour = raylib::Color::DarkPurple();
            break;
        
        case "BEIGE"_hash:
            finalColour = raylib::Color::Beige();
            break;

        case "BROWN"_hash:
            finalColour = raylib::Color::Brown();
            break;
        
        case "DARKBROWN"_hash:
            finalColour = raylib::Color::DarkBrown();
            break;
        
        case "BLANK"_hash:
            finalColour = raylib::Color::Blank();
            break;

        case "MAGENTA"_hash:
            finalColour = raylib::Color::Magenta();
            break;

        case "RAYWHITE"_hash:
            finalColour = raylib::Color::RayWhite();
            break;

        default:
            finalColour = raylib::Color::RayWhite();
            break;
    }

    return finalColour;
}