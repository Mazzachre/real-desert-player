import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import desert 1.0

Window {
	id: playerWindow
	title: "Desert Player"
	visible: true

	Button {
		anchors.verticalCenter: parent.verticalCenter
		anchors.horizontalCenter: parent.horizontalCenter
		width: 90
		height: 30
		text: App.isFullScreen ? "Window" : "Fullscreen"
		onClicked: App.toggleFullScreen()
		focusPolicy: Qt.NoFocus
	}

}
