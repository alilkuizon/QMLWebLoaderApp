import QtQuick

QtObject {
    // 🎨 Colors
    readonly property color primaryColor: "#3498db" // Blue
    readonly property color secondaryColor: "#2ecc71" // Green
    readonly property color accentColor: "#e74c3c" // Red
    readonly property color backgroundColor: "#ecf0f1" // Light Gray
    readonly property color textColor: "#2c3e50" // Dark Gray
    readonly property color borderColor: "#bdc3c7" // Silver
    readonly property color disabledColor: "#95a5a6" // Grayish

    // 🖋️ Fonts
    readonly property string fontFamily: "Arial"
    readonly property int fontSizeSmall: 12
    readonly property int fontSizeMedium: 16
    readonly property int fontSizeLarge: 20
    readonly property int fontSizeExtraLarge: 24

    // 📏 Spacing (Padding & Margins)
    readonly property int paddingSmall: 8
    readonly property int paddingMedium: 12
    readonly property int paddingLarge: 16
    readonly property int marginSmall: 8
    readonly property int marginMedium: 12
    readonly property int marginLarge: 16

    // 📦 Common Component Styles
    readonly property var buttonStyle: ({
                                            "color": primaryColor,
                                            "textColor": "#ffffff",
                                            "borderRadius": 6,
                                            "padding": paddingMedium
                                        })

    readonly property var textFieldStyle: ({
                                               "borderColor": borderColor,
                                               "borderWidth": 1,
                                               "padding": paddingSmall,
                                               "textColor": textColor
                                           })

    readonly property var cardStyle: ({
                                          "backgroundColor": "#ffffff",
                                          "shadowColor": "#dcdcdc",
                                          "borderRadius": 8,
                                          "padding": paddingLarge
                                      })
}
