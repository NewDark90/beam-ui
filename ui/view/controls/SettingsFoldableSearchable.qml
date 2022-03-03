import QtQuick 2.11
import QtQuick.Controls 1.2
import QtQuick.Controls 2.4
import QtQuick.Controls.Styles 1.2
import QtQuick.Layouts 1.12
import "../utils.js" as Utils
import Beam.Wallet 1.0
import "."

SettingsFoldable {
    id: control

    property bool    found: false
    property string  searchFilter:  ""
    onSearchFilterChanged: function() {
        found = false;
        folded = true;
    }

    visible: searchFilter != "" ? found : true

    function search(str) {
        if (str.search(new RegExp("(" + control.searchFilter + ")", "i")) !== -1) {
            found = true;
            folded = false;
        }
    }

    function getHighlitedText(text, currentIndex = -1) {
        if(control.searchFilter == "")
            return text;
            
        if(!Array.isArray(text)) {
            search(text);
            return Utils.getHighlitedText(text, control.searchFilter, Style.accent_incoming.toString());
        }
        else {
            return text.map( function (el, index) {  
                    if (currentIndex !== index && currentIndex !== -1) {
                        return el;
                    }
                    else {
                        search(el);
                        return Utils.getHighlitedText(el, control.searchFilter, Style.accent_incoming.toString());
                    }
                }
            );
        }
    }
}
